//
// Created by EDY on 2023/11/16.
//

#ifndef IMANDROIDCDEMO_JNI_JSON_OBJARR_UTIL_H
#define IMANDROIDCDEMO_JNI_JSON_OBJARR_UTIL_H

#include <jni.h>

#include <map>
#include <string>

namespace v2im {
    namespace jni {
            class JSONObjectJNI {
            public:
                static jobject optNewJObject(JNIEnv *env, const jobject &obj);

                static jobject optJObject(JNIEnv *env, const jobject &obj, const std::string &key);

                static int optJsonInt(JNIEnv *env, const jobject &obj, const std::string &key);

                static long optJsonLong(JNIEnv *env, const jobject &obj, const std::string &key);

                static double optJsonDouble(JNIEnv *env, const jobject &obj, const std::string &key);

                static bool optJsonBoolean(JNIEnv *env, const jobject &obj, const std::string &key);

                static jstring optJsonString(JNIEnv *env, const jobject &obj, const std::string &key);

                static jobject optJson2JArr(JNIEnv *env, const jobject &obj, const std::string &key);
            };

            class JSONArrayJNI {
            public:
                static int jArr2Length(JNIEnv *env, const jobject &arr);

                static jobject optJArr2JsonObj(JNIEnv *env, const jobject &arr, const int index);
            };

    }
}


#endif //IMANDROIDCDEMO_JNI_JSON_OBJARR_UTIL_H
