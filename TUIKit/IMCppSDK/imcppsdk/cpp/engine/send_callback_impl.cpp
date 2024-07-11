//
// Created by Junker on 2022/9/19.
//

#include "send_callback_impl.h"

#include "jni_helper.h"
#include "LogUtil.h"
#include "im_callbak_jni.h"
#include "java_basic_jni.h"
#include "message_jni.h"

namespace v2im {
    SendCallbackImpl::SendCallbackImpl(jobject callback_) {
        jni::ScopedJEnv scopedJEnv;
        auto *env = scopedJEnv.GetEnv();
        send_callback_ = env->NewGlobalRef(callback_);
    }

    SendCallbackImpl::SendCallbackImpl(jobject message_, jobject callback_) {
        jni::ScopedJEnv scopedJEnv;
        auto *env = scopedJEnv.GetEnv();
        send_message_ = env->NewGlobalRef(message_);
        send_callback_ = env->NewGlobalRef(callback_);
    }

    SendCallbackImpl::~SendCallbackImpl() {
        jni::ScopedJEnv scopedJEnv;
        auto *env = scopedJEnv.GetEnv();
        if (env) {
            if (send_message_) {
                env->DeleteGlobalRef(send_message_);
            }
            if (send_callback_) {
                env->DeleteGlobalRef(send_callback_);
            }
            LOGE("SendCallbackImpl ~init");
        }
    }

    void SendCallbackImpl::OnProgress(uint32_t progress) {

    }

    void SendCallbackImpl::OnSuccess(const V2TIMMessage &value) {
        if (send_callback_) {
            jni::IMCallbackJNI::Success(send_callback_, jni::MessageJni::Convert2JObject(value));
        }
    }

    void SendCallbackImpl::OnError(int error_code, const V2TIMString &error_message) {
        if (send_message_){
            v2im::jni::MessageJni::UpdateJMessageStatus2Fail(send_message_);
        }
        if (send_callback_) {
            v2im::jni::IMCallbackJNI::Fail(send_callback_, error_code, error_message.CString());
        }
    }

}// namespace v2im