//
// Created by Junker on 2022/10/17.
//

#ifndef IMCPLUSPLUSDEMO_DOWNLOAD_CALLBACK_IMPL_H
#define IMCPLUSPLUSDEMO_DOWNLOAD_CALLBACK_IMPL_H

#include "../include/V2TIMCallback.h"
#include "v2_im_common.h"
#include <functional>
#include "../include/V2TIMErrorCode.h"

namespace v2im {
    class DownloadCallbackImpl final : public V2TIMDownloadCallback {
    public:
        DownloadCallbackImpl(jobject download_callback_);
        ~DownloadCallbackImpl() override;

    protected:
        // V2TIMDownloadCallback
        void OnDownLoadProgress(uint64_t currentSize, uint64_t totalSize) override;
        void OnSuccess() override;
        void OnError(const int error_code, const V2TIMString &error_message) override;

    private:
        jobject _download_callback_;
    };
}// namespace v2im

#endif //IMCPLUSPLUSDEMO_DOWNLOAD_CALLBACK_IMPL_H
