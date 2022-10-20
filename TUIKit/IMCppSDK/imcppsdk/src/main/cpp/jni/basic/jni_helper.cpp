//
// Created by EDY on 2022/8/23.
//
#include "jni_helper.h"

#include <android/log.h>
#include <assert.h>

namespace v2im {
    namespace jni {

        //////////////////////////////////// JniHelper  ////////////////////////////////////

        JavaVM *JniHelper::sJvm = nullptr;
        pthread_key_t JniHelper::sKey;

        void OnJniThreadExit(void *tlsData) {
            // JNIEnv* env = (JNIEnv*)tlsData;
            if (nullptr != JniHelper::GetJVM()) {
                JniHelper::GetJVM()->DetachCurrentThread();
            }
        }

        bool JniHelper::Init(JavaVM *jvm) {
            if (sJvm) {
                return true;
            }
            sJvm = jvm;
            if (0 != pthread_key_create(&sKey, OnJniThreadExit)) {
                __android_log_print(ANDROID_LOG_ERROR, "JniHelper", "create sKey fail");
                return false;
            }
            return true;
        }

        void JniHelper::UnInit() {
            pthread_key_delete(sKey);
            sJvm = nullptr;
        }

        //跨线程回调Java层函数
        JavaVM *JniHelper::GetJVM() {
            return sJvm;
        }

        bool JniHelper::CheckAndClearException(JNIEnv *env) {
            if (env->ExceptionCheck()) {
                env->ExceptionDescribe();
                env->ExceptionClear();
                return true;
            }
            return false;
        }

        //////////////////////////////////// ScopedJEnv  ////////////////////////////////////

        ScopedJEnv::ScopedJEnv(jint capacity) : env_(nullptr) {
            if (!JniHelper::sJvm) {
                return;
            }
            do {
                env_ = (JNIEnv *) pthread_getspecific(JniHelper::sKey);

                if (nullptr != env_) {
                    break;
                }

                jint status = JniHelper::sJvm->GetEnv((void **) &env_, JNI_VERSION_1_6);
                if (JNI_OK == status) {
                    break;
                }

                JavaVMAttachArgs args;
                args.group = NULL;
                args.name = "default";
                args.version = JNI_VERSION_1_6;
                status = JniHelper::sJvm->AttachCurrentThread(&env_, &args);

                if (JNI_OK == status) {
                    pthread_setspecific(JniHelper::sKey, env_);
                } else {
                    __android_log_print(ANDROID_LOG_ERROR, "JniHelper",
                                        "AttachCurrentThread failed|vm:%p|env:%p|status:%d",
                                        JniHelper::sJvm, env_, status);
                    env_ = nullptr;
                    return;
                }
            } while (false);

        }

        ScopedJEnv::~ScopedJEnv() {
            if (nullptr != env_) {
//                env_->PopLocalFrame(nullptr);//释放局部变量应用栈
            }
        }

        JNIEnv *ScopedJEnv::GetEnv() const {
            return env_;
        }

        bool ScopedJEnv::CheckAndClearException() const { return JniHelper::CheckAndClearException(env_); }
    }
}