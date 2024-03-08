//
// Created by Junker on 2022/8/22.
//

#include "sdk_config_jni.h"

#include <android/log.h>

#include "jni_util.h"

namespace v2im {
    namespace jni {

        jclass SDKConfigJni::jcls_;
        jmethodID SDKConfigJni::j_method_id_array_[MethodIDMax];
        bool SDKConfigJni::InitIDs(JNIEnv *env) {
            if (jcls_ != nullptr){
                return true;
            }
            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMSDKConfig");

            if (nullptr == cls){
                return false;
            }

            jcls_ = (jclass)env->NewGlobalRef(cls);

            env->DeleteLocalRef(cls);

            jmethodID j_mod = nullptr;
            j_mod = env->GetMethodID(jcls_,"<init>", "()V");
            if (j_mod == nullptr){
                return false;
            }
            j_method_id_array_[MethodIDConstruct] = j_mod;
            return true;
        }

        V2TIMSDKConfig SDKConfigJni::ConvertToCoreObject(JNIEnv *env, const jobject &object) {
            jclass clazz = env->GetObjectClass(object);
            V2TIMSDKConfig config;

//            config.initPath = "/data/user/0/包名/files";
//            config.logPath = "/storage/emulated/0/Android/data/包名/files/log/tencent/imsdk/";

            config.initPath = util::getStringValue(env,clazz,object,"sdkInitPath").c_str();
            config.logPath = util::getStringValue(env,clazz,object,"sdkLogPath").c_str();

//            config.initPath = static_cast<V2TIMString>("D:\\");
//            config.logPath = static_cast<V2TIMString>("D:\\");

            env->DeleteLocalRef(clazz);
            return config;
        }

    } // namespace v2im
} // namespace jni
