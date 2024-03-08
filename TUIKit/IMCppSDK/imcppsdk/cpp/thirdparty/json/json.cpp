#include <stdlib.h>
#include <string.h>

#include <algorithm>
#include <cctype>
#include <cerrno>
#include <climits>
#include <cstdio>
#include <cstdlib>
#include <functional>
#include <stack>
#include <string>
#include <sstream>
#include <iomanip>

#include "json.h"


#ifndef WIN32
#define _stricmp strcasecmp
#endif

#ifdef _MSC_VER
#define snprintf sprintf_s
#endif

#define nullptr (0)
using namespace json;

namespace {
    // the max size of json parameter
    static const uint64_t kMaxJsonStringSize = 2 * 1024 * 1024;
}

namespace json {
enum StackDepthType { InObject, InArray };
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// Helper functions
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static std::string Trim(const std::string& str) {
    std::string s = str;

    // remove white space in front
    s.erase(s.begin(),
            std::find_if(s.begin(), s.end(), [](unsigned char c) { return !isspace(c); }));

    // remove trailing white space
    s.erase(
        std::find_if(s.rbegin(), s.rend(), [](unsigned char c) { return !isspace(c); }).base(),
        s.end());

    return s;
}

// Finds the position of the first " character that is NOT preceeded immediately by a \ character.
// In JSON, \" is valid and has a different meaning than the escaped " character.
static size_t GetQuotePos(const std::string& str, size_t start_pos = 0) {
    bool found_slash = false;
    for (size_t i = start_pos; i < str.length(); i++) {
        char c = str[i];
        if ((c == '\\') && !found_slash) {
            found_slash = true;
            continue;
        } else if ((c == '\"') && !found_slash)
            return i;

        found_slash = false;
    }

    return std::string::npos;
}

// Returns true if ch is a control character (in range [1,31]).
static inline bool isControlCharacter(char ch) { 
    return ch > 0 && ch <= 0x1F; 
}

static std::string escapeJSONString(const std::string& str) {
    std::string s = "";

    for (std::string::size_type i = 0; i < str.length(); i++) {
        char c = str[i];

        switch (c) {
            case '"':
            case '\\':
            case '/':
                s.push_back('\\');
                s.push_back(c);
                break;

            case '\t':
                s.append("\\t");
                break;

            case '\n':
                s.append("\\n");
                break;

            case '\r':
                s.append("\\r");
                break;

            case '\b':
                s.append("\\b");
                break;

            case '\f':
                s.append("\\f");
                break;

            default:
                if ((isControlCharacter(c)) || (c == 0)) {
                    std::stringstream ss;
                    ss << "\\u" << std::hex << std::uppercase << std::setfill('0')
                       << std::setw(4) << static_cast<int>(c);
                    s += ss.str();
                }
                else {
                    s.push_back(c);
                }
                break;
        }
    }

    return s;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Value::Value(const Value& v) : mValueType(v.mValueType) {
    switch (mValueType) {
        case StringVal:
            mStringVal = v.mStringVal;
            break;
        case IntVal:
            mIntVal = v.mIntVal;
            mFloatVal = (float)v.mIntVal;
            mDoubleVal = (double)v.mIntVal;
            mInt64Val = (long long)v.mIntVal;
            mUInt64Val = (unsigned long long)v.mIntVal;
            break;
        case FloatVal:
            mFloatVal = v.mFloatVal;
            mIntVal = (int)v.mFloatVal;
            mDoubleVal = (double)v.mFloatVal;
            mInt64Val = (long long)v.mFloatVal;
            mUInt64Val = (unsigned long long)v.mFloatVal;
            break;
        case DoubleVal:
            mDoubleVal = v.mDoubleVal;
            mIntVal = (int)v.mDoubleVal;
            mFloatVal = (float)v.mDoubleVal;
            mInt64Val = (long long)v.mDoubleVal;
            mUInt64Val = (unsigned long long)v.mDoubleVal;
            break;
        case BoolVal:
            mBoolVal = v.mBoolVal;
            break;
        case ObjectVal:
            mObjectVal = v.mObjectVal;
            break;
        case ArrayVal:
            mArrayVal = v.mArrayVal;
            break;
        case Int64Val:
            mInt64Val = v.mInt64Val;
            mIntVal = (int)v.mInt64Val;
            mFloatVal = (float)v.mInt64Val;
            mDoubleVal = (double)v.mInt64Val;
            mUInt64Val = (unsigned long long)v.mInt64Val;
            break;
        case UInt64Val:
            mUInt64Val = v.mUInt64Val;
            mIntVal = (int)v.mUInt64Val;
            mFloatVal = (float)v.mUInt64Val;
            mDoubleVal = (double)v.mUInt64Val;
            mInt64Val = (long long)v.mUInt64Val;
            break;
        default:
            break;
    }
}

Value::Value()
    : mValueType(NULLVal),
      mIntVal(0),
      mFloatVal(0),
      mDoubleVal(0),
      mInt64Val(0),
      mUInt64Val(0),
      mBoolVal(false) {}
Value::Value(ValueType type)
    : mValueType(type),
      mIntVal(0),
      mFloatVal(0),
      mDoubleVal(0),
      mInt64Val(0),
      mUInt64Val(0),
      mBoolVal(false) {}
Value::Value(int v)
    : mValueType(IntVal),
      mIntVal(v),
      mFloatVal((float)v),
      mDoubleVal((double)v),
      mInt64Val((long long)v),
      mUInt64Val((unsigned long long)v),
      mBoolVal(false) {}
Value::Value(long long v)
    : mValueType(Int64Val),
      mIntVal((int)v),
      mFloatVal((float)(double)v),
      mDoubleVal((double)v),
      mInt64Val(v),
      mUInt64Val((unsigned long long)v),
      mBoolVal(false) {}      
Value::Value(unsigned long long v)
    : mValueType(UInt64Val),
      mIntVal((int)v),
      mFloatVal((float)(double)v),
      mDoubleVal((double)v),
      mInt64Val((long long)v),
      mUInt64Val(v),
      mBoolVal(false) {}
Value::Value(float v)
    : mValueType(FloatVal),
      mIntVal((int)v),
      mFloatVal(v),
      mDoubleVal((double)v),
      mInt64Val((long long)v),
      mUInt64Val((unsigned long long)v),
      mBoolVal(false) {}
Value::Value(double v)
    : mValueType(DoubleVal),
      mIntVal((int)v),
      mFloatVal((float)v),
      mDoubleVal(v),
      mInt64Val((long long)v),
      mUInt64Val((unsigned long long)v),
      mBoolVal(false) {}
Value::Value(const std::string& v)
    : mValueType(StringVal),
      mIntVal(),
      mFloatVal(),
      mDoubleVal(),
      mInt64Val(),
      mUInt64Val(),
      mStringVal(v),
      mBoolVal(false) {}
Value::Value(const char* v)
    : mValueType(StringVal),
      mIntVal(),
      mFloatVal(),
      mDoubleVal(),
      mInt64Val(),
      mUInt64Val(),
      mStringVal(v),
      mBoolVal(false) {}
Value::Value(const Object& v)
    : mValueType(ObjectVal),
      mIntVal(),
      mFloatVal(),
      mDoubleVal(),
      mInt64Val(),
      mUInt64Val(),
      mObjectVal(v),
      mBoolVal(false) {}
Value::Value(const Array& v)
    : mValueType(ArrayVal),
      mIntVal(),
      mFloatVal(),
      mDoubleVal(),
      mInt64Val(),
      mUInt64Val(),
      mArrayVal(v),
      mBoolVal(false) {}
Value::Value(bool v)
    : mValueType(BoolVal), mIntVal(), mFloatVal(), mDoubleVal(), mInt64Val(), mUInt64Val(), mBoolVal(v) {}
Value::~Value() {}

Value& Value::operator=(const Value& v) {
    if (&v == this) return *this;

    mValueType = v.mValueType;

    switch (mValueType) {
        case StringVal:
            mStringVal = v.mStringVal;
            break;
        case IntVal:
            mIntVal = v.mIntVal;
            mFloatVal = (float)v.mIntVal;
            mDoubleVal = (double)v.mIntVal;
            mInt64Val = (long long)v.mIntVal;
            mUInt64Val = (unsigned long long)v.mIntVal;
            break;
        case FloatVal:
            mFloatVal = v.mFloatVal;
            mIntVal = (int)v.mFloatVal;
            mDoubleVal = (double)v.mDoubleVal;
            mInt64Val = (long long)v.mFloatVal;
            mUInt64Val = (unsigned long long)v.mFloatVal;
            break;
        case DoubleVal:
            mDoubleVal = v.mDoubleVal;
            mIntVal = (int)v.mDoubleVal;
            mFloatVal = (float)v.mDoubleVal;
            mInt64Val = (long long)v.mDoubleVal;
            mUInt64Val = (unsigned long long)v.mDoubleVal;
            break;
        case BoolVal:
            mBoolVal = v.mBoolVal;
            break;
        case ObjectVal:
            mObjectVal = v.mObjectVal;
            break;
        case ArrayVal:
            mArrayVal = v.mArrayVal;
            break;
        case Int64Val:
            mInt64Val = v.mInt64Val;
            mIntVal = (int)v.mInt64Val;
            mFloatVal = (float)v.mInt64Val;
            mDoubleVal = (double)v.mInt64Val;
            mUInt64Val = (unsigned long long)v.mInt64Val;
            break;
        case UInt64Val:
            mUInt64Val = v.mUInt64Val;
            mIntVal = (int)v.mUInt64Val;
            mFloatVal = (float)v.mUInt64Val;
            mDoubleVal = (double)v.mUInt64Val;
            mInt64Val = (long long)v.mUInt64Val;
            break;
        default:
            break;
    }

    return *this;
}

Value& Value::operator[](size_t idx) {
    // if (mValueType != ArrayVal)
    // 	throw std::runtime_error("json mValueType==ArrayVal required");

    return mArrayVal[idx];
}

const Value& Value::operator[](size_t idx) const {
    // if (mValueType != ArrayVal)
    // 	throw std::runtime_error("json mValueType==ArrayVal required");

    return mArrayVal[idx];
}

Value& Value::operator[](const std::string& key) {
    // if (mValueType != ObjectVal)
    // 	throw std::runtime_error("json mValueType==ObjectVal required");

    return mObjectVal[key];
}

Value& Value::operator[](const char* key) {
    // if (mValueType != ObjectVal)
    // 	throw std::runtime_error("json mValueType==ObjectVal required");

    return mObjectVal[key];
}

const Value& Value::operator[](const char* key) const {
    // if (mValueType != ObjectVal)
    // 	throw std::runtime_error("json mValueType==ObjectVal required");

    return mObjectVal[key];
}

const Value& Value::operator[](const std::string& key) const {
    // if (mValueType != ObjectVal)
    // 	throw std::runtime_error("json mValueType==ObjectVal required");

    return mObjectVal[key];
}

void Value::Clear() { mValueType = NULLVal; }

size_t Value::size() const {
    if ((mValueType != ObjectVal) && (mValueType != ArrayVal)) return 1;

    return mValueType == ObjectVal ? mObjectVal.size() : mArrayVal.size();
}

bool Value::HasKey(const std::string& key) const {
    // if (mValueType != ObjectVal)
    // 	throw std::runtime_error("json mValueType==ObjectVal required");

    return mObjectVal.HasKey(key);
}

int Value::HasKeys(const std::vector<std::string>& keys) const {
    // if (mValueType != ObjectVal)
    // 	throw std::runtime_error("json mValueType==ObjectVal required");

    return mObjectVal.HasKeys(keys);
}

int Value::HasKeys(const char** keys, int key_count) const {
    // if (mValueType != ObjectVal)
    // 	throw std::runtime_error("json mValueType==ObjectVal required");

    return mObjectVal.HasKeys(keys, key_count);
}

int Value::ToInt() const {
    // if (!IsNumeric())
    // 	throw std::runtime_error("json mValueType==IsNumeric() required");

    return mIntVal;
}

float Value::ToFloat() const {
    // if (!IsNumeric())
    // 	throw std::runtime_error("json mValueType==IsNumeric() required");

    return mFloatVal;
}

double Value::ToDouble() const {
    // if (!IsNumeric())
    // 	throw std::runtime_error("json mValueType==IsNumeric() required");

    return mDoubleVal;
}

long long Value::ToInt64() const { return mInt64Val; }

unsigned long long Value::ToUInt64() const { return mUInt64Val; }

bool Value::ToBool() const {
    // if (mValueType != BoolVal)
    // 	throw std::runtime_error("json mValueType==BoolVal required");

    return mBoolVal;
}

const std::string& Value::ToString() const {
    // if (mValueType != StringVal)
    // 	throw std::runtime_error("json mValueType==StringVal required");

    return mStringVal;
}

Object Value::ToObject() const {
    // if (mValueType != ObjectVal)
    // 	throw std::runtime_error("json mValueType==ObjectVal required");

    return mObjectVal;
}

Array Value::ToArray() const {
    // if (mValueType != ArrayVal)
    // 	throw std::runtime_error("json mValueType==ArrayVal required");

    return mArrayVal;
}

Value::operator int() const {
    // if (!IsNumeric())
    // 	throw std::runtime_error("json mValueType==IsNumeric() required");

    return mIntVal;
}

Value::operator float() const {
    // if (!IsNumeric())
    // 	throw std::runtime_error("json mValueType==IsNumeric() required");

    return mFloatVal;
}

Value::operator double() const {
    // if (!IsNumeric())
    // 	throw std::runtime_error("json mValueType==IsNumeric() required");

    return mDoubleVal;
}

Value::operator long long() const {

    return mInt64Val;
}

Value::operator unsigned long long() const {
    // if (!IsNumeric())
    // 	throw std::runtime_error("json mValueType==IsNumeric() required");

    return mUInt64Val;
}

Value::operator bool() const {
    // if (mValueType != BoolVal)
    // 	throw std::runtime_error("json mValueType==BoolVal required");

    return mBoolVal;
}

Value::operator std::string() const {
    // if (mValueType != StringVal)
    // 	throw std::runtime_error("json mValueType==StringVal required");

    return mStringVal;
}

Value::operator Object() const {
    // if (mValueType != ObjectVal)
    // 	throw std::runtime_error("json mValueType==ObjectVal required");

    return mObjectVal;
}

Value::operator Array() const {
    // if (mValueType != ArrayVal)
    // 	throw std::runtime_error("json mValueType==ArrayVal required");

    return mArrayVal;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Array::Array() {}

Array::Array(const Array& a) : mValues(a.mValues) {}

Array::~Array() {}

Array& Array::operator=(const Array& a) {
    if (&a == this) return *this;

    Clear();
    mValues = a.mValues;

    return *this;
}

Value& Array::operator[](size_t i) { return mValues[i]; }

const Value& Array::operator[](size_t i) const { return mValues[i]; }

Array::ValueVector::const_iterator Array::begin() const { return mValues.begin(); }

Array::ValueVector::const_iterator Array::end() const { return mValues.end(); }

Array::ValueVector::iterator Array::begin() { return mValues.begin(); }

Array::ValueVector::iterator Array::end() { return mValues.end(); }

void Array::push_back(const Value& v) { mValues.push_back(v); }

void Array::insert(size_t index, const Value& v) { mValues.insert(mValues.begin() + index, v); }

size_t Array::size() const { return mValues.size(); }

void Array::Clear() { mValues.clear(); }

Array::ValueVector::iterator Array::find(const Value& v) {
    return std::find(mValues.begin(), mValues.end(), v);
}

Array::ValueVector::const_iterator Array::find(const Value& v) const {
    return std::find(mValues.begin(), mValues.end(), v);
}

bool Array::HasValue(const Value& v) const { return find(v) != end(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
Object::Object() {}

Object::Object(const Object& obj) : mValues(obj.mValues) {}

Object& Object::operator=(const Object& obj) {
    if (&obj == this) return *this;

    Clear();
    mValues = obj.mValues;

    return *this;
}

Object::~Object() {}

Value& Object::operator[](const std::string& key) { return mValues[key]; }

const Value& Object::operator[](const std::string& key) const {
    ValueMap::const_iterator it = mValues.find(key);
    return it->second;
}

Value& Object::operator[](const char* key) { return mValues[key]; }

const Value& Object::operator[](const char* key) const {
    ValueMap::const_iterator it = mValues.find(key);
    return it->second;
}

Object::ValueMap::const_iterator Object::begin() const { return mValues.begin(); }

Object::ValueMap::const_iterator Object::end() const { return mValues.end(); }

Object::ValueMap::iterator Object::begin() { return mValues.begin(); }

Object::ValueMap::iterator Object::end() { return mValues.end(); }

Object::ValueMap::iterator Object::find(const std::string& key) { return mValues.find(key); }

Object::ValueMap::const_iterator Object::find(const std::string& key) const {
    return mValues.find(key);
}

bool Object::HasKey(const std::string& key) const { return find(key) != end(); }

int Object::HasKeys(const std::vector<std::string>& keys) const {
    for (size_t i = 0; i < keys.size(); i++) {
        if (!HasKey(keys[i])) return (int)i;
    }

    return -1;
}

int Object::HasKeys(const char** keys, int key_count) const {
    for (int i = 0; i < key_count; i++)
        if (!HasKey(keys[i])) return i;

    return -1;
}

void Object::Clear() { mValues.clear(); }

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::string SerializeArray(const Array& a);

std::string SerializeValue(const Value& v) {
    std::string str;

    static const int BUFF_SZ = 500;
    char buff[BUFF_SZ];
    std::stringstream ss;
    switch (v.GetType()) {
        case IntVal:
            snprintf(buff, BUFF_SZ, "%d", (int)v);
            str = buff;
            break;
        case FloatVal:
            snprintf(buff, BUFF_SZ, "%f", (float)v);
            str = buff;
            break;
        case DoubleVal:
            ss << std::setprecision(16) << (double)v;
            str = ss.str();
            break;
        case BoolVal:
            str = v ? "true" : "false";
            break;
        case NULLVal:
            str = "null";
            break;
        case ObjectVal:
            str = Serialize(v);
            break;
        case ArrayVal:
            str = SerializeArray(v);
            break;
        case StringVal:
            str = std::string("\"") + escapeJSONString((std::string)v) + std::string("\"");
            break;
        case Int64Val:
            snprintf(buff, BUFF_SZ, "%lld", (long long)v);
            str = buff;
            break;
        case UInt64Val:
            snprintf(buff, BUFF_SZ, "%llu", (unsigned long long)v);
            str = buff;
            break;
    }

    return str;
}

std::string SerializeArray(const Array& a) {
    std::string str = "[";

    bool first = true;
    for (size_t i = 0; i < a.size(); i++) {
        const Value& v = a[i];
        if (!first) str += std::string(",");

        str += SerializeValue(v);

        first = false;
    }

    str += "]";
    return str;
}

std::string json::Serialize(const Value& v) {
    std::string str;

    bool first = true;

    if (v.GetType() == ObjectVal) {
        str = "{";
        Object obj = v.ToObject();
        for (Object::ValueMap::const_iterator it = obj.begin(); it != obj.end(); ++it) {
            if (!first) str += std::string(",");

            str += std::string("\"") + it->first + std::string("\":") + SerializeValue(it->second);
            first = false;
        }

        str += "}";
    } else if (v.GetType() == ArrayVal) {
        str = "[";
        Array a = v.ToArray();
        for (Array::ValueVector::const_iterator it = a.begin(); it != a.end(); ++it) {
            if (!first) str += std::string(",");

            str += SerializeValue(*it);
            first = false;
        }

        str += "]";
    }
    // else it's not valid JSON, as a JSON data structure must be an array or an object. We'll
    // return an empty string.

    return str;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
static Value DeserializeArray(std::string& str, std::stack<StackDepthType>& depth_stack);
static Value DeserializeObj(const std::string& _str, std::stack<StackDepthType>& depth_stack);

static Value DeserializeInternal(const std::string& _str, std::stack<StackDepthType>& depth_stack) {
    Value v;

    std::string str = Trim(_str);
    if (str[0] == '{') {
        // Error: Began with a { but doesn't end with one
        if (str[str.length() - 1] != '}') return Value();

        depth_stack.push(InObject);
        v = DeserializeObj(str, depth_stack);
        if ((v.GetType() == NULLVal) || (depth_stack.top() != InObject)) return v;

        depth_stack.pop();
    } else if (str[0] == '[') {
        // Error: Began with a [ but doesn't end with one
        if (str[str.length() - 1] != ']') return Value();

        depth_stack.push(InArray);
        v = DeserializeArray(str, depth_stack);
        if ((v.GetType() == NULLVal) || (depth_stack.top() != InArray)) return v;

        depth_stack.pop();
    } else {
        // Will never get here unless _str is not valid JSON
        return Value();
    }

    return v;
}

static size_t GetEndOfArrayOrObj(const std::string& str, std::stack<StackDepthType>& depth_stack) {
    size_t i = 1;
    bool in_quote = false;
    size_t original_count = depth_stack.size();

    for (; i < str.length(); i++) {
        if (str[i] == '\"') {
             int j = i - 1;
             int count = 0;
             while(j > 0 && str[j] == '\\') { 
                    ++count;
                    --j;
             } 
             if(0 == count % 2 ){
                in_quote = !in_quote;
             }
        } else if (!in_quote) {
            if (str[i] == '[')
                depth_stack.push(InArray);
            else if (str[i] == '{')
                depth_stack.push(InObject);
            else if (str[i] == ']') {
                StackDepthType t = depth_stack.top();
                if (t != InArray) {
                    // expected to be closing an array but instead we're inside an object block.
                    // Example problem: {]}
                    return std::string::npos;
                }

                size_t count = depth_stack.size();
                depth_stack.pop();
                if (count == original_count) break;
            } else if (str[i] == '}') {
                StackDepthType t = depth_stack.top();
                if (t != InObject) {
                    // expected to be closing an object but instead we're inside an array.
                    // Example problem: [}]
                    return std::string::npos;
                }

                size_t count = depth_stack.size();
                depth_stack.pop();
                if (count == original_count) break;
            }
        }
    }

    // 如果是非法输入，最后可能匹配失败，如 [12"3]，此时需检查返回值是否越界
    if (i < str.length()) {
        return i;
    } else {
        return std::string::npos;
    }
}

bool DecodeUnicodeCodePoint(const std::string &str, int &skip_ahead, unsigned int &unicode) {

    if (str.length() < 5) {
        return false;
    }

    std::string hex_str = str.substr(1, 4);
    char *hex_end;
    unicode = std::strtoul(hex_str.c_str(), &hex_end, 16);
    if (hex_end - hex_str.c_str() < 4) {
        return false;
    }
    skip_ahead = 5;

    if (unicode >= 0xD800 && unicode <= 0xDBFF) {
        // surrogate pairs
        if (str.length() >= 11 && str[4] == '\\' && str[5] == 'u') {
            skip_ahead += 6;

            hex_str = str.substr(7, 4);
            unsigned int surrogatePair;
            surrogatePair = std::strtoul(hex_str.c_str(), &hex_end, 16);
            if (hex_end - hex_str.c_str() < 4) {
                return false;
            }

            unicode = 0x10000 + ((unicode & 0x3FF) << 10) + (surrogatePair & 0x3FF);
        } else {
            return false;
        }
    }

    return true;
}

// Converts a unicode code-point to UTF-8.
static inline std::string CodePointToUTF8(unsigned int codepoint) {
    std::string result;

    // based on description from http://en.wikipedia.org/wiki/UTF-8

    if (codepoint <= 0x7f) {
        result.resize(1);
        result[0] = static_cast<char>(codepoint);
    } else if (codepoint <= 0x7FF) {
        result.resize(2);
        result[1] = static_cast<char>(0x80 | (0x3f & codepoint));
        result[0] = static_cast<char>(0xC0 | (0x1f & (codepoint >> 6)));
    } else if (codepoint <= 0xFFFF) {
        result.resize(3);
        result[2] = static_cast<char>(0x80 | (0x3f & codepoint));
        result[1] = static_cast<char>(0x80 | (0x3f & (codepoint >> 6)));
        result[0] = static_cast<char>(0xE0 | (0xf & (codepoint >> 12)));
    } else if (codepoint <= 0x10FFFF) {
        result.resize(4);
        result[3] = static_cast<char>(0x80 | (0x3f & codepoint));
        result[2] = static_cast<char>(0x80 | (0x3f & (codepoint >> 6)));
        result[1] = static_cast<char>(0x80 | (0x3f & (codepoint >> 12)));
        result[0] = static_cast<char>(0xF0 | (0x7 & (codepoint >> 18)));
    }

    return result;
}


static std::string UnescapeJSONString(const std::string &str, bool *had_error) {
    std::string s = "";

    for (std::string::size_type i = 0; i < str.length(); i++) {
        char c = str[i];        
        if (c == '\\') {

            if (i + 1 < str.length()) {
                int skip_ahead = 1;

                switch (str[i + 1]) {
                    case '"':
                        s.push_back('\"');
                        break;
                    case '\\':
                        s.push_back('\\');
                        break;
                    case '/':
                        s.push_back('/');
                        break;
                    case 't':
                        s.push_back('\t');
                        break;
                    case 'n':
                        s.push_back('\n');
                        break;
                    case 'r':
                        s.push_back('\r');
                        break;
                    case 'b':
                        s.push_back('\b');
                        break;
                    case 'f':
                        s.push_back('\f');
                        break;
                    case 'u':{
                        unsigned int unicode = 0;
                        if (DecodeUnicodeCodePoint(str.substr(i + 1), skip_ahead, unicode)) {
                            s += CodePointToUTF8(unicode);
                        } else {
                            *had_error = true;
                            return "";
                        }
                        break;
                    } 
                    default:
                        *had_error = true;
                        return "";
                }

                i += skip_ahead;
            } else {
                *had_error = true;
                return "";
            }
        } else
            s.push_back(c);
    }

    // 返回时，对字符串首尾的空字符不做处理
    return s;
}

static Value DeserializeValue(std::string& str, bool* had_error,
                              std::stack<StackDepthType>& depth_stack) {
    Value v;

    *had_error = false;
    str = Trim(str);

    if (str.length() == 0) return v;

    if (str[0] == '[') {
        // This value is an array, determine the end of it and then deserialize the array
        depth_stack.push(InArray);
        size_t i = GetEndOfArrayOrObj(str, depth_stack);
        if (i == std::string::npos) {
            *had_error = true;
            return Value();
        }

        std::string array_str = str.substr(0, i + 1);
        v = Value(DeserializeArray(array_str, depth_stack));
        str = str.substr(i + 1, str.length());
    } else if (str[0] == '{') {
        // This value is an object, determine the end of it and then deserialize the object
        depth_stack.push(InObject);
        size_t i = GetEndOfArrayOrObj(str, depth_stack);

        if (i == std::string::npos) {
            *had_error = true;
            return Value();
        }

        std::string obj_str = str.substr(0, i + 1);
        v = Value(DeserializeInternal(obj_str, depth_stack));
        str = str.substr(i + 1, str.length());
    } else if (str[0] == '\"') {
        // This value is a string
        size_t end_quote = GetQuotePos(str, 1);
        if (end_quote == std::string::npos) {
            *had_error = true;
            return Value();
        }

        v = Value(UnescapeJSONString(str.substr(1, end_quote - 1), had_error));
        if (*had_error) {
            return Value();
        }
        str = str.substr(end_quote + 1, str.length());
    } else {
        // it's not an object, string, or array so it's either a boolean or a number or null.
        // Numbers can contain an exponent indicator ('e') or a decimal point.
        bool has_dot = false;
        bool has_e = false;
        std::string temp_val;
        size_t i = 0;
        bool found_digit = false;
        bool found_first_valid_char = false;

        for (; i < str.length(); i++) {
            if (str[i] == '.') {
                if (!found_digit) {
                    // As per JSON standards, there must be a digit preceding a decimal point
                    *had_error = true;
                    return Value();
                }

                has_dot = true;
            } else if ((str[i] == 'e') || (str[i] == 'E')) {
                if ((_stricmp(temp_val.c_str(), "fals") != 0) &&
                    (_stricmp(temp_val.c_str(), "tru") != 0)) {
                    // it's not a boolean, check for scientific notation validity. This will also
                    // trap booleans with extra 'e' characters like falsee/truee
                    if (!found_digit) {
                        // As per JSON standards, a digit must precede the 'e' notation
                        *had_error = true;
                        return Value();
                    } else if (has_e) {
                        // multiple 'e' characters not allowed
                        *had_error = true;
                        return Value();
                    }

                    has_e = true;
                }
            } else if (str[i] == ']') {
                if (depth_stack.empty() || (depth_stack.top() != InArray)) {
                    *had_error = true;
                    return Value();
                }

                depth_stack.pop();
            } else if (str[i] == '}') {
                if (depth_stack.empty() || (depth_stack.top() != InObject)) {
                    *had_error = true;
                    return Value();
                }

                depth_stack.pop();
            } else if (str[i] == ',')
                break;
            else if ((str[i] == '[') || (str[i] == '{')) {
                // error, we're supposed to be processing things besides arrays/objects in here
                *had_error = true;
                return Value();
            }

            if (!std::isspace(str[i])) {
                if (std::isdigit(str[i])) found_digit = true;

                found_first_valid_char = true;
                temp_val += str[i];
            }
        }

        // store all floating point as doubles. This will also set the float and int values as well.
        if (_stricmp(temp_val.c_str(), "true") == 0)
            v = Value(true);
        else if (_stricmp(temp_val.c_str(), "false") == 0)
            v = Value(false);
        else if (has_e || has_dot) {
            char* end_char;
            errno = 0;
            double d = strtod(temp_val.c_str(), &end_char);
            if ((errno != 0) || (*end_char != '\0')) {
                // invalid conversion or out of range
                *had_error = true;
                return Value();
            }
            std::stringstream ss(temp_val);
            ss >> d;

            v = Value(d);
        } else if (_stricmp(temp_val.c_str(), "null") == 0)
            v = Value();
        else {
            // Check if the value is beyond the size of an int and if so, store it as a double
            char* end_char;
            errno = 0;
            long long ival = strtoll(temp_val.c_str(), &end_char, 10);

            if (*end_char != '\0') {
                // invalid character sequence, not a number
                *had_error = true;
                return Value();
            } else if ((errno == ERANGE) && ((ival == LLONG_MAX) || (ival == LLONG_MIN))) {
                // value is out of range for a long int, should be a double then. See if we can
                // convert it correctly.
                errno = 0;
                unsigned long long ullVal = strtoull(temp_val.c_str(), &end_char, 10);
                if ((errno != 0) || (*end_char != '\0')) {
                    // error in conversion or it's too big for a unsigned long long
                    *had_error = true;
                    return Value();
                }

                v = Value(ullVal);
                //				errno = 0;
                //				double dval = strtod(temp_val.c_str(), &end_char);
                //				if ((errno != 0) || (*end_char != '\0'))
                //				{
                //					// error in conversion or it's too big for a
                //double 					*had_error = true; 					return Value();
                //				}
                //
                //				v = Value(dval);
            } else if ((ival >= INT_MIN) && (ival <= INT_MAX)) {
                // valid int range
                v = Value((int)ival);
            } else if ((ival >= LLONG_MIN) && (ival <= LLONG_MAX)) {
                // valid long long  range
                v = Value(ival);
            } else {
                // probably running on a very old OS since this block implies that long isn't the
                // same size as int. int is guaranteed to be at least 16 bits and long 32
                // bits...however nowadays they're almost always the same 32 bit size. But it's
                // possible someone is running this on a very old architecture so for correctness,
                // we'll error out here
                *had_error = true;
                return Value();
            }
        }

        str = str.substr(i, str.length());
    }

    return v;
}

static Value DeserializeArray(std::string& str, std::stack<StackDepthType>& depth_stack) {
    Array a;
    bool had_error = false;

    str = Trim(str);

    // Arrays begin and end with [], so if we don't find one, it's an error
    if ((str[0] == '[') && (str[str.length() - 1] == ']'))
        str = str.substr(1, str.length() - 2);
    else
        return Value();

    // extract out all values from the array (remember, a value can also be an array or an object)
    while (str.length() > 0) {
        str = Trim(str);
        std::string tmp;

        size_t i = 0;
        bool between_quote = false;
        for (; i < str.length(); i++) {
            // If we get to an object or array, parse it:
            if ((str[i] == '{') || (str[i] == '[')) {
                Value v = DeserializeValue(str, &had_error, depth_stack);
                if (had_error) return Value();

                if (v.GetType() != NULLVal) a.push_back(v);

                break;
            }

            // 判断是否在处于双引号之间
            if (str[i] == '\"') {
                if (0 == i) {
                    between_quote = true;
                } else {
                    int j = i - 1;
                    // 当引号前边的转义字符为偶数个时，当前引号为结束符
                    bool end_quote = true;
                    while(j > 0 && str[j] == '\\') { 
                        end_quote = !end_quote;
                        --j;
                    }

                    if(true == end_quote){
                        between_quote = false;
                    }
                }
            }

            bool terminate_parsing = false;

            if (((str[i] == ',') || (str[i] == ']'))) {
                if (false == between_quote) {
                    terminate_parsing = true;  // hit the end of a value, parse it in the next block
                } else {
                    tmp += str[i];
                }
            } else {
                // keep grabbing chars to build up the value
                tmp += str[i];
            }

            if (i == str.length() - 1){
                terminate_parsing = true;  // end of string, finish parsing
            }
                    
            if (terminate_parsing) {
                Value v = DeserializeValue(tmp, &had_error, depth_stack);
                if (had_error) return Value();

                if (v.GetType() != NULLVal) a.push_back(v);

                str = str.substr(i + 1, str.length());
                break;
            }
        }
    }

    return a;
}

static Value DeserializeObj(const std::string& _str, std::stack<StackDepthType>& depth_stack) {
    Object obj;

    std::string str = Trim(_str);

    // Objects begin and end with {} so if we don't find a pair, it's an error
    if ((str[0] != '{') && (str[str.length() - 1] != '}'))
        return Value();
    else
        str = str.substr(1, str.length() - 2);

    // Get all key/value pairs in this object...
    while (str.length() > 0) {
        // Get the key name
        size_t start_quote_idx = GetQuotePos(str);
        size_t end_quote_idx = GetQuotePos(str, start_quote_idx + 1);
        size_t colon_idx = str.find(':', end_quote_idx);

        if ((start_quote_idx == std::string::npos) || (end_quote_idx == std::string::npos) ||
            (colon_idx == std::string::npos))
            return Value();  // can't find key name

        std::string key = str.substr(start_quote_idx + 1, end_quote_idx - start_quote_idx - 1);
        if (key.length() == 0) return Value();

        bool had_error = false;
        str = str.substr(colon_idx + 1, str.length());

        // We have the key, now extract the value from the string
        obj[key] = DeserializeValue(str, &had_error, depth_stack);
        if (had_error) return Value();
    }

    return obj;
}

Value json::Deserialize(const std::string& str) {
    std::stack<StackDepthType> depth_stack;
    return DeserializeInternal(str, depth_stack);
}

Value json::Deserialize(const char *str) {
    if (str && *str && strnlen(str, kMaxJsonStringSize) < kMaxJsonStringSize) {
       return Deserialize(std::string(str));
    } else {
        return json::Value();
    }
}