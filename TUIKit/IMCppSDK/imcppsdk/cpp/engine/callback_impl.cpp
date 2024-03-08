//
// Created by EDY on 2022/9/13.
//

#include <jni_helper.h>

#include <utility>
#include "callback_impl.h"
#include "im_callbak_jni.h"
#include "LogUtil.h"
#include "V2TIMErrorCode.h"

namespace v2im {
    CallbackIMpl::CallbackIMpl(jobject listener_callback) {
        jni::ScopedJEnv scopedJEnv;
        auto *env = scopedJEnv.GetEnv();
        if (nullptr != listener_callback){
            listener_callback_ = env->NewGlobalRef(listener_callback);
        }

    }

    CallbackIMpl::~CallbackIMpl() {
        jni::ScopedJEnv scopedJEnv;
        auto *env = scopedJEnv.GetEnv();
        if (env) {
            if (listener_callback_) {
                LOGE("CallbackIMpl ~init");
                env->DeleteGlobalRef(listener_callback_);
            }
        }
    }

    void CallbackIMpl::OnSuccess() {
        if (listener_callback_) {
            v2im::jni::IMCallbackJNI::Success(listener_callback_,{});
        }
    }

    void CallbackIMpl::OnError(int error_code, const V2TIMString &error_message) {
        if (listener_callback_) {
            v2im::jni::IMCallbackJNI::Fail(listener_callback_, error_code, error_message.CString());
        }
    }

}
