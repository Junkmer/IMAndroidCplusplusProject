//
// Created by EDY on 2023/11/16.
//

#include "jni_json_objarr_util.h"
#include "jni_helper.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
            jobject JSONObjectJNI::optJObject(JNIEnv *env, const jobject &obj, std::string const &key) {
                jclass clazz = env->GetObjectClass(obj);
                jmethodID jmethodId = env->GetMethodID(clazz, "optJSONObject", "(Ljava/lang/String;)Lorg/json/JSONObject;");
                return env->CallObjectMethod(obj, jmethodId, StringJni::Cstring2Jstring(env,key));
            }

            int JSONObjectJNI::optJsonInt(JNIEnv *env, const jobject &obj, std::string const &key) {
                jclass clazz = env->GetObjectClass(obj);
                jmethodID jmethodId = env->GetMethodID(clazz, "optInt", "(Ljava/lang/String;)I");
                return env->CallIntMethod(obj, jmethodId, StringJni::Cstring2Jstring(env,key));
            }

            long JSONObjectJNI::optJsonLong(JNIEnv *env, const jobject &obj, std::string const &key) {
                jclass clazz = env->GetObjectClass(obj);
                jmethodID jmethodId = env->GetMethodID(clazz, "optLong", "(Ljava/lang/String;)J");
                return env->CallLongMethod(obj, jmethodId, StringJni::Cstring2Jstring(env,key));
            }

            double JSONObjectJNI::optJsonDouble(JNIEnv *env, const jobject &obj, std::string const &key) {
                jclass clazz = env->GetObjectClass(obj);
                jmethodID jmethodId = env->GetMethodID(clazz, "optDouble", "(Ljava/lang/String;)D");
                return env->CallDoubleMethod(obj, jmethodId, StringJni::Cstring2Jstring(env,key));
            }

        bool JSONObjectJNI::optJsonBoolean(JNIEnv *env, const jobject &obj, std::string const &key) {
            jclass clazz = env->GetObjectClass(obj);
            jmethodID jmethodId = env->GetMethodID(clazz, "optBoolean", "(Ljava/lang/String;)Z");
            return env->CallBooleanMethod(obj, jmethodId, StringJni::Cstring2Jstring(env,key));
        }

            jstring JSONObjectJNI::optJsonString(JNIEnv *env, const jobject &obj, std::string const &key) {
                jclass clazz = env->GetObjectClass(obj);
                jmethodID jmethodId = env->GetMethodID(clazz, "optString", "(Ljava/lang/String;)Ljava/lang/String;");
                return (jstring) env->CallObjectMethod(obj, jmethodId, StringJni::Cstring2Jstring(env,key));
            }

            jobject JSONObjectJNI::optJson2JArr(JNIEnv *env, jobject const &obj, std::string const &key) {
                ScopedJEnv scopedJEnv;
                jclass clazz = env->GetObjectClass(obj);
                jmethodID jmethodId =  env->GetMethodID(clazz,"optJSONArray", "(Ljava/lang/String;)Lorg/json/JSONArray;");
                return env->CallObjectMethod(obj, jmethodId, StringJni::Cstring2Jstring(env,key));
            }

            int JSONArrayJNI::jArr2Length(JNIEnv *env, jobject const &arr) {
                jclass clazz = env->GetObjectClass(arr);
                jmethodID jmethodId = env->GetMethodID(clazz,"length", "()I");
                return env->CallIntMethod(arr,jmethodId);
            }

            jobject JSONArrayJNI::optJArr2JsonObj(JNIEnv *env, jobject const &arr, const int index) {
                jclass clazz = env->GetObjectClass(arr);
                jmethodID jmethodId = env->GetMethodID(clazz,"optJSONObject", "(I)Lorg/json/JSONObject;");
                return env->CallObjectMethod(arr,jmethodId,index);
            }
        }

}