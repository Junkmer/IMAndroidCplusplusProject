//
// Created by EDY on 2022/10/8.
//

#ifndef IMCPLUSPLUSDEMO_COMPLETE_CALLBACK_IMPL_H
#define IMCPLUSPLUSDEMO_COMPLETE_CALLBACK_IMPL_H

#include "../include/V2TIMCallback.h"
#include <functional>
#include <jni_helper.h>

#include "jni.h"

namespace v2im {
    template <class T>
    class CompleteCallbackImpl final : public V2TIMCompleteCallback<T> {
    public:
        CompleteCallbackImpl(jobject callback_) {
            jni::ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();
            if (callback_){
                complete_callback_ = env->NewGlobalRef(callback_);
            }
        };

        ~CompleteCallbackImpl() {
            jni::ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();
            if (env) {
                if (complete_callback_) {
                    env->DeleteGlobalRef(complete_callback_);
                }
            }
        };

    protected:
        //V2TIMCompleteCallback
        void OnComplete(int error_code, const V2TIMString &error_message, const T &value) {
            if (complete_callback_) {
                jni::IMCallbackJNI::FailOrComplete(complete_callback_, error_code, error_message.CString(), jni::MessageJni::Convert2JObject(value));
            }
        };

    private:
        jobject complete_callback_;
    };


}// namespace v2im

#endif //IMCPLUSPLUSDEMO_COMPLETE_CALLBACK_IMPL_H
