//
// Created by Junker on 2022/8/22.
//

#include "jni_util.h"

namespace v2im {
    namespace jni {
        namespace util {

            int getIntValue(JNIEnv *env, jclass j_cls, jobject j_obj, const char *field_name) {
                if (nullptr == env || nullptr == j_cls || nullptr == j_obj || nullptr == field_name) {
                    return 0;
                }
                jfieldID fieldId = env->GetFieldID(j_cls, field_name, "I");
                return env->GetIntField(j_obj, fieldId);
            }

            long getLongValue(JNIEnv *env, jclass j_cls, jobject object, const char *field_name) {
                if (nullptr == env || nullptr == j_cls || nullptr == object || nullptr == field_name) {
                    return 0;
                }
                jfieldID fieldID = env->GetFieldID(j_cls, field_name, "J");
                return env->GetLongField(object, fieldID);
            }

            std::string getStringValue(JNIEnv *env, jclass j_cls, jobject j_obj, const char *field_name) {
                if (nullptr == env || nullptr == j_cls || nullptr == j_obj || nullptr == field_name) {
                    return "";
                }
                jfieldID fieldID = env->GetFieldID(j_cls, field_name, "Ljava/lang/String;");
                auto j_str = static_cast<jstring>(env->GetObjectField(j_obj, fieldID));
                if (j_str) {
                    int size = env->GetStringUTFLength(j_str);
                    const char *value = env->GetStringUTFChars(j_str, NULL);

                    std::string result(value, size);

                    env->ReleaseStringUTFChars(j_str, value);
                    env->DeleteLocalRef(j_str);

                    return result;
                }
                return "";
            }

            int RegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods, int numMethods) {
                jclass clazz;
                clazz = env->FindClass(className);
                if (nullptr == clazz) {
                    return JNI_FALSE;
                }

                if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
                    env->DeleteLocalRef(clazz);
                    return JNI_FALSE;
                }

                env->DeleteLocalRef(clazz);
                return JNI_TRUE;
            }
        }
    }
}