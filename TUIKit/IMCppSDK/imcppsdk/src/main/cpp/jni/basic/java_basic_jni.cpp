//
// Created by EDY on 2022/9/16.
//

#include "java_basic_jni.h"
#include "jni_helper.h"

namespace v2im {
    namespace jni {

        //////////////////////////////////// IntegerJni ////////////////////////////////////

        jclass IntegerJni::j_cls_ = nullptr;
        std::map<std::string, jmethodID> IntegerJni::methodIdMap_;
        std::map<std::string, jfieldID> IntegerJni::fieldIdMap_;

        bool IntegerJni::Init(JNIEnv *env) {
            if (j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("java/lang/Integer");
            if (nullptr == cls) {
                return false;
            }

            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "<init>", "(I)V");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["constructor"] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "intValue", "()I");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["intValue"] = jmethod;

            jfieldID jfield = nullptr;
            jfield = env->GetStaticFieldID(j_cls_,"MIN_VALUE", "I");
            if (nullptr == jfield){
                return false;
            }
            fieldIdMap_["MIN_VALUE"] = jfield;

            jfield = env->GetStaticFieldID(j_cls_,"MAX_VALUE", "I");
            if (nullptr == jfield){
                return false;
            }
            fieldIdMap_["MAX_VALUE"] = jfield;

            return true;
        }

        jobject IntegerJni::NewIntegerObj(int value) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }

            jobject intObj = env->NewObject(j_cls_, methodIdMap_["constructor"], (jint) value);
            return intObj;
        }

        int IntegerJni::IntValue(jobject intObj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return 0;
            }

            if (!intObj) return 0;
            return env->CallIntMethod(intObj, methodIdMap_["intValue"]);
        }

        int IntegerJni::MIN_VALUE(){
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return 0;
            }

            return  env->GetStaticIntField(j_cls_,fieldIdMap_["MIN_VALUE"]);
        }

        int IntegerJni::MAX_VALUE(){
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return 0;
            }

            return  env->GetStaticIntField(j_cls_,fieldIdMap_["MAX_VALUE"]);
        }

        //////////////////////////////////// LongJni ////////////////////////////////////

        jclass LongJni::j_cls_ = nullptr;
        std::map<std::string, jmethodID> LongJni::methodIdMap_;
        std::map<std::string, jfieldID> LongJni::fieldIdMap_;

        bool LongJni::Init(JNIEnv *env) {
            if (j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("java/lang/Long");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "<init>", "(J)V");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["constructor"] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "longValue", "()J");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["longValue"] = jmethod;

            jfieldID jfield = nullptr;
            jfield = env->GetStaticFieldID(j_cls_,"MIN_VALUE", "J");
            if (nullptr == jfield){
                return false;
            }
            fieldIdMap_["MIN_VALUE"] = jfield;

            jfield = env->GetStaticFieldID(j_cls_,"MAX_VALUE", "J");
            if (nullptr == jfield){
                return false;
            }
            fieldIdMap_["MAX_VALUE"] = jfield;

            return true;
        }

        jobject LongJni::NewLongObj(long value) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }

            jobject longObj = env->NewObject(j_cls_, methodIdMap_["constructor"], (jlong) value);
            return longObj;
        }

        jobject LongJni::NewUInt64(uint16_t value) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }
            jobject longObj = env->NewObject(j_cls_, methodIdMap_["constructor"], (jlong) value);
            return longObj;
        }

        long LongJni::LongValue(jobject longObj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return 0;
            }

            if (!longObj) return 0;

            return env->CallLongMethod(longObj, methodIdMap_["longValue"]);
        }

        uint64_t LongJni::UInt64Value(jobject longObj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return 0;
            }

            if (!longObj) return 0;

            return (uint64_t) env->CallLongMethod(longObj, methodIdMap_["longValue"]);
        }

        long LongJni::MIN_VALUE(){
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return 0;
            }

            return  env->GetStaticLongField(j_cls_,fieldIdMap_["MIN_VALUE"]);
        }

        long LongJni::MAX_VALUE(){
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return 0;
            }

            return  env->GetStaticLongField(j_cls_,fieldIdMap_["MAX_VALUE"]);
        }

        //////////////////////////////////// ByteJni ////////////////////////////////////

        jbyteArray ByteJni::Cuint8_t2JByteArray(JNIEnv *env, const uint8_t *data, size_t size) {

            jbyteArray customDataJni = env->NewByteArray((jsize) size);

            env->SetByteArrayRegion(customDataJni, 0, (jsize) size, (jbyte *) data);

            return customDataJni;
        }

        V2TIMBuffer ByteJni::JByteArray2V2TIMBuffer(JNIEnv *env, jbyteArray byteArray) {

            auto *elements = (jbyte *) env->GetByteArrayElements(byteArray, 0);
            jsize arrayLength = env->GetArrayLength(byteArray);

            auto *bytearr = (uint8_t *) elements;
            auto size =(size_t) arrayLength;

            return {bytearr,size};
        }

        //////////////////////////////////// StringJni ////////////////////////////////////

        jclass StringJni::j_cls_ = nullptr;
        std::map<std::string, jmethodID> StringJni::methodIdMap_;

        bool StringJni::Init(JNIEnv *env) {
            if (j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("java/lang/String");
            if (nullptr == cls) {
                return false;
            }

            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;
            jmethod = env->GetMethodID(j_cls_, "<init>", "([BLjava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["constructor"] = jmethod;

            return true;
        }

        std::string StringJni::Jstring2Cstring(JNIEnv *env, jstring const &jstr) {
            if (nullptr == jstr) {
                return "";
            }

            auto len = (size_t) env->GetStringUTFLength(jstr);
            auto *chars = (char *) env->GetStringUTFChars(jstr, 0);
            std::string cstr(chars, len);
            env->ReleaseStringUTFChars(jstr, chars);

            return cstr;
        }

        jstring StringJni::Cstring2Jstring(JNIEnv *env, const std::string &cstr) {
            if (!Init(env)) {
                return nullptr;
            }

            jbyteArray bytes = env->NewByteArray((jsize) cstr.size());
            if (nullptr == bytes) {
                if (env->ExceptionCheck()) {
                    env->ExceptionDescribe();
                    env->ExceptionClear();
                    return nullptr;
                }
            }

            env->SetByteArrayRegion(bytes, 0, (jsize) cstr.size(), (jbyte *) cstr.c_str());
            jstring encoding = env->NewStringUTF("utf-8");

            auto *jstr = (jstring) env->NewObject(j_cls_, methodIdMap_["constructor"], bytes, encoding);
            env->DeleteLocalRef(bytes);
            env->DeleteLocalRef(encoding);
            return jstr;
        }

        jbyteArray StringJni::Cstring2JbyteArray(JNIEnv *env, const std::string &cstr) {
            auto len = cstr.size();
            jbyteArray byteArr = env->NewByteArray(len);
            if (nullptr == byteArr) {
                if (env->ExceptionCheck()) {
                    env->ExceptionDescribe();
                    env->ExceptionClear();
                    return nullptr;
                }
            }

            env->SetByteArrayRegion(byteArr, 0, (jsize) len, (jbyte *) cstr.data());
            return byteArr;
        }

        V2TIMBuffer StringJni::Jstring2V2TIMBuffer(JNIEnv *env, jstring const &jstr) {
            auto len = (jsize) env->GetStringUTFLength(jstr);
            auto *chars = (char *) env->GetStringUTFChars(jstr, 0);

            auto *bytearr = (uint8_t *) chars;
            auto size =(size_t) len;

            return {bytearr,size};
        }

        std::string StringJni::JbyteArray2Cstring(JNIEnv *env, const jbyteArray &byteArr) {
            if (nullptr == byteArr) return "";

            auto len = (size_t) env->GetArrayLength(byteArr);
            auto *chars = env->GetByteArrayElements(byteArr, 0);
            std::string cstr((char *) chars, len);
            env->ReleaseByteArrayElements(byteArr, chars, 0);
            return cstr;
        }

        jstring StringJni::Cuint8_t2Jstring(JNIEnv *env, const uint8_t *data, size_t size) {
            if (!Init(env)){
                return nullptr;
            }

            jbyteArray bytes = env->NewByteArray((jsize) size);
            env->SetByteArrayRegion(bytes, 0, (jsize) size, (jbyte *) data);
            jstring encoding = env->NewStringUTF("utf-8");

            auto *jstr = (jstring) env->NewObject(j_cls_, methodIdMap_["constructor"], bytes, encoding);
            env->DeleteLocalRef(bytes);
            env->DeleteLocalRef(encoding);
            return jstr;
        }

        //////////////////////////////////// ArrayListJni ////////////////////////////////////

        jclass ArrayListJni::j_cls_ = nullptr;
        jclass ArrayListJni::list_cls_ = nullptr;
        std::map<std::string, jmethodID> ArrayListJni::methodIdMap_;

        bool ArrayListJni::Init(JNIEnv *env) {
            if (j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("java/util/ArrayList");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);
            if (nullptr == j_cls_) {
                return false;
            }

            jmethodID jmethod = nullptr;
            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["constructor"] = jmethod;

            cls = env->FindClass("java/util/List");
            if (nullptr == cls) {
                return false;
            }
            list_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);
            if (nullptr == list_cls_) {
                return false;
            }

            jmethod = env->GetMethodID(list_cls_, "add", "(Ljava/lang/Object;)Z");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["add"] = jmethod;

            jmethod = env->GetMethodID(list_cls_, "get", "(I)Ljava/lang/Object;");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["get"] = jmethod;

            jmethod = env->GetMethodID(list_cls_, "size", "()I");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["size"] = jmethod;

            return true;
        }

        jobject ArrayListJni::NewArrayList() {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }
            jobject listObj = env->NewObject(j_cls_, methodIdMap_["constructor"]);
            return listObj;
        }

        bool ArrayListJni::Add(jobject listObj, jobject obj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return false;
            }

            if (!listObj || !obj) return false;
            return env->CallBooleanMethod(listObj, methodIdMap_["add"], obj);
        }

        jobject ArrayListJni::Get(jobject listObj, int i) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }
            return env->CallObjectMethod(listObj, methodIdMap_["get"], i);
        }

        int ArrayListJni::Size(jobject listObj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return 0;
            }

            if (!listObj) return 0;

            return env->CallIntMethod(listObj, methodIdMap_["size"]);
        }

        std::vector<std::string> ArrayListJni::JStringListToCoreVector(jobject jobj) {
            std::vector<std::string> vector_data;
            if (NULL == jobj) return vector_data;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            auto len = ArrayListJni::Size(jobj);
            for (int i = 0; i < len; ++i) {
                auto item_object = (jstring)ArrayListJni::Get(jobj, i);
                auto size = (size_t) env->GetStringUTFLength(item_object);
                auto *chars = (char *) env->GetStringUTFChars(item_object, 0);
                std::string cstr(chars, size);
                env->ReleaseStringUTFChars(item_object, chars);
                if (cstr.empty()) {
                    continue;
                }

                vector_data.push_back(cstr);
            }
            return vector_data;
        }

        std::vector<uint32_t> ArrayListJni::JIntListToCoreVector(jobject jobj) {
            std::vector<uint32_t> vector_data;
            if (NULL == jobj) return vector_data;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            auto len = ArrayListJni::Size(jobj);
            for (int i = 0; i < len; ++i) {
                jobject item_object = ArrayListJni::Get(jobj, i);
                uint32_t value = IntegerJni::IntValue(item_object);
                vector_data.push_back(value);
                env->DeleteLocalRef(item_object);
            }

            return vector_data;
        }

        //////////////////////////////////// HashMapJni ////////////////////////////////////

        jclass HashMapJni::jHashMapCls_;
        jclass HashMapJni::jSetCls_;
        jclass HashMapJni::jIteratorCls_;
        jclass HashMapJni::jEntryCls_;
        std::map<std::string, jmethodID> HashMapJni::methodIdMap_;

        bool HashMapJni::Init(JNIEnv *env) {
            if (jHashMapCls_ && jSetCls_ && jIteratorCls_ && jEntryCls_) {
                return true;
            }

            jclass hashMapCls = env->FindClass("java/util/HashMap");
            if (nullptr == hashMapCls) {
                return false;
            }
            jHashMapCls_ = (jclass) env->NewGlobalRef(hashMapCls);

            jclass setCls = env->FindClass("java/util/Set");
            if (nullptr == setCls) {
                return false;
            }
            jSetCls_ = (jclass) env->NewGlobalRef(setCls);

            jclass iteratorCls = env->FindClass("java/util/Iterator");
            if (nullptr == iteratorCls) {
                return false;
            }
            jIteratorCls_ = (jclass) env->NewGlobalRef(iteratorCls);

            jclass entryCls = env->FindClass("java/util/Map$Entry");// 内部类使用$符号表示
            if (nullptr == entryCls) {
                return false;
            }
            jEntryCls_ = (jclass) env->NewGlobalRef(entryCls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(jHashMapCls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["constructor"] = jmethod;

            jmethod = env->GetMethodID(hashMapCls, "put", "(Ljava/lang/Object;Ljava/lang/Object;)Ljava/lang/Object;");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["put"] = jmethod;

            jmethod = env->GetMethodID(hashMapCls, "get", "(Ljava/lang/Object;)Ljava/lang/Object;");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["get"] = jmethod;

            jmethod = env->GetMethodID(hashMapCls, "size", "()I");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["size"] = jmethod;

            jmethod = env->GetMethodID(hashMapCls, "entrySet", "()Ljava/util/Set;");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["entrySet"] = jmethod;

            jmethod = env->GetMethodID(setCls, "iterator", "()Ljava/util/Iterator;");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["iterator"] = jmethod;

            jmethod = env->GetMethodID(iteratorCls, "hasNext", "()Z");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["hasNext"] = jmethod;

            jmethod = env->GetMethodID(iteratorCls, "next", "()Ljava/lang/Object;");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["next"] = jmethod;

            jmethod = env->GetMethodID(entryCls, "getKey", "()Ljava/lang/Object;");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["getKey"] = jmethod;

            jmethod = env->GetMethodID(entryCls, "getValue", "()Ljava/lang/Object;");
            if (nullptr == jmethod) {
                return false;
            }
            methodIdMap_["getValue"] = jmethod;
            return true;
        }

        jobject HashMapJni::NewHashMap() {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }

            jobject hashMapObj = env->NewObject(jHashMapCls_, methodIdMap_["constructor"]);
            return hashMapObj;
        }

        bool HashMapJni::Put(jobject mapObj, jobject key, jobject value) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return false;
            }

            if (!mapObj || !key) return false;

            jobject obj = env->CallObjectMethod(mapObj, methodIdMap_["put"], key, value);
            if (obj) {
                env->DeleteLocalRef(obj);
                return true;
            }
            return false;
        }

        jobject HashMapJni::Get(jobject mapObj, jobject key) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }

            if (!mapObj || !key) return nullptr;

            return env->CallObjectMethod(mapObj, methodIdMap_["get"], key);
        }

        int HashMapJni::Size(jobject mapObj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return 0;
            }

            if (!mapObj) return 0;

            return env->CallIntMethod(mapObj, methodIdMap_["size"]);
        }

        jobject HashMapJni::entrySet(jobject mapObj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }

            if (!mapObj) return nullptr;

            return env->CallObjectMethod(mapObj, methodIdMap_["entrySet"]);
        }

        jobject HashMapJni::iterator(jobject setObj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }

            if (!setObj) return nullptr;

            return env->CallObjectMethod(setObj, methodIdMap_["iterator"]);
        }

        bool HashMapJni::hasNext(jobject iteratorObj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return false;
            }

            if (!iteratorObj) return false;

            return env->CallBooleanMethod(iteratorObj, methodIdMap_["hasNext"]);
        }

        jobject HashMapJni::next(jobject iteratorObj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }

            if (!iteratorObj) return nullptr;

            return env->CallObjectMethod(iteratorObj, methodIdMap_["next"]);
        }

        jobject HashMapJni::getKey(jobject entryObj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }

            if (!entryObj) return nullptr;

            return env->CallObjectMethod(entryObj, methodIdMap_["getKey"]);
        }

        jobject HashMapJni::getValue(jobject entryObj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!Init(env)) {
                return nullptr;
            }

            if (!entryObj) return nullptr;

            return env->CallObjectMethod(entryObj, methodIdMap_["getValue"]);
        }

    }// namespace v2im
}// namespace jni