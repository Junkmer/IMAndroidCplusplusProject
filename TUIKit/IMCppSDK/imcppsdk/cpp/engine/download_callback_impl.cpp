//
// Created by EDY on 2022/10/18.
//

#include <jni_helper.h>

#include <utility>
#include "download_callback_impl.h"
#include "im_callbak_jni.h"
#include "LogUtil.h"
#include "V2TIMErrorCode.h"

namespace v2im {
    DownloadCallbackImpl::DownloadCallbackImpl(jobject download_callback_) {
        jni::ScopedJEnv scopedJEnv;
        auto *env = scopedJEnv.GetEnv();
        if (nullptr != download_callback_){
            _download_callback_ = env->NewGlobalRef(download_callback_);
        }
    }

    DownloadCallbackImpl::~DownloadCallbackImpl() {
        jni::ScopedJEnv scopedJEnv;
        auto *env = scopedJEnv.GetEnv();
        if (env) {
            if (_download_callback_) {
//                LOGE("DownloadCallbackImpl ~init");
                env->DeleteGlobalRef(_download_callback_);
            }
        }
    }

    void DownloadCallbackImpl::OnDownLoadProgress(uint64_t currentSize, uint64_t totalSize) {
        if (_download_callback_) {
//            LOGE("Download - progress , currentSize = %lu | totalSize = %lu",currentSize,totalSize);
            v2im::jni::IMCallbackJNI::DownloadProgress(_download_callback_, currentSize, totalSize);
        }
    }

    void DownloadCallbackImpl::OnSuccess() {
        if (_download_callback_) {
//            LOGE("Download - OnSuccess ");
            v2im::jni::IMCallbackJNI::Success(_download_callback_,{});
        }
    }

    void DownloadCallbackImpl::OnError(int error_code, const V2TIMString &error_message) {
        if (_download_callback_) {
//            LOGE("Download - OnError , error_code = %d | error_message = %s",error_code,error_message.CString());
            v2im::jni::IMCallbackJNI::Fail(_download_callback_, error_code, error_message.CString());
        }
    }

}