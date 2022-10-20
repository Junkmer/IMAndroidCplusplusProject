//
// Created by EDY on 2022/9/16.
//

#ifndef IMCPLUSPLUSDEMO_JAVA_BASIC_JNI_H
#define IMCPLUSPLUSDEMO_JAVA_BASIC_JNI_H

#include <jni.h>
#include <map>
#include <string>
#include <vector>
#include <V2TIMBuffer.h>

namespace v2im {
    namespace jni {
        class IntegerJni {
        public:
            static bool Init(JNIEnv *env);
            static jobject NewIntegerObj(int value);
            static int IntValue(jobject intObj);
            static int MIN_VALUE();
            static int MAX_VALUE();
        public:
            static jclass j_cls_;
            static std::map<std::string, jmethodID> methodIdMap_;
            static std::map<std::string, jfieldID> fieldIdMap_;
        };

        class LongJni {
        public:
            static bool Init(JNIEnv *env);
            static jobject NewLongObj(long value);
            static jobject NewUInt64(uint16_t value);
            static long LongValue(jobject longObj);
            static uint64_t UInt64Value(jobject longObj);
            static long MIN_VALUE();
            static long MAX_VALUE();

        public:
            static jclass j_cls_;
            static std::map<std::string, jmethodID> methodIdMap_;
            static std::map<std::string, jfieldID> fieldIdMap_;
        };

        class ByteJni{
        public:
            static jbyteArray Cuint8_t2JByteArray(JNIEnv *env, const uint8_t *data, size_t size);
            static V2TIMBuffer JByteArray2V2TIMBuffer(JNIEnv *env,jbyteArray byteArray);
        };

        class StringJni {
        public:
            static bool Init(JNIEnv *env);
            static std::string Jstring2Cstring(JNIEnv *env, const jstring &jstr);
            static jstring Cstring2Jstring(JNIEnv *env, const std::string &cstr);
            static jbyteArray Cstring2JbyteArray(JNIEnv *env, const std::string &cstr);
            static V2TIMBuffer Jstring2V2TIMBuffer(JNIEnv *env, jstring const &jstr);
            static std::string JbyteArray2Cstring(JNIEnv *env, const jbyteArray &byteArr);
            static jstring Cuint8_t2Jstring(JNIEnv *env, const uint8_t *data, size_t size);
        public:
            static jclass j_cls_;
            static std::map<std::string, jmethodID> methodIdMap_;
        };

        class ArrayListJni {
        public:
            static bool Init(JNIEnv *env);
            static jobject NewArrayList();
            static bool Add(jobject listObj, jobject obj);
            static jobject Get(jobject listObj, int i);
            static int Size(jobject listObj);
            static std::vector<std::string> JStringListToCoreVector(jobject);
            static std::vector<uint32_t> JIntListToCoreVector(jobject);

        public:
            static jclass j_cls_;
            static jclass list_cls_;
            static std::map<std::string, jmethodID> methodIdMap_;
        };

        class HashMapJni {
        public:
            static bool Init(JNIEnv *env);
            static jobject NewHashMap();
            static bool Put(jobject mapObj, jobject key, jobject value);
            static jobject Get(jobject mapObj, jobject key);
            static int Size(jobject mapObj);
            static jobject entrySet(jobject mapObj);
            static jobject iterator(jobject setObj);
            static bool hasNext(jobject iteratorObj);
            static jobject next(jobject iteratorObj);
            static jobject getKey(jobject entryObj);
            static jobject getValue(jobject entryObj);

        public:
            static jclass jHashMapCls_;
            static jclass jSetCls_;
            static jclass jIteratorCls_;
            static jclass jEntryCls_;
            static std::map<std::string, jmethodID> methodIdMap_;
        };

        inline bool HandleOccerredExcept(JNIEnv *jniEnv) {
            jthrowable exception = jniEnv->ExceptionOccurred();
            if (NULL != exception) {
                jniEnv->ExceptionDescribe();
                jniEnv->ExceptionClear();
                return true;
            }
            return false;
        }
    }// namespace v2im
}// namespace jni


#endif //IMCPLUSPLUSDEMO_JAVA_BASIC_JNI_H
