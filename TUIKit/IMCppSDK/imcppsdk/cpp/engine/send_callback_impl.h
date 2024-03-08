//
// Created by Junker on 2022/9/19.
//

#ifndef IMCPLUSPLUSDEMO_SEND_CALLBACK_IMPL_H
#define IMCPLUSPLUSDEMO_SEND_CALLBACK_IMPL_H

#include "../include/V2TIMCallback.h"
#include <functional>

#include "jni.h"

namespace v2im {
    class SendCallbackImpl final : public V2TIMSendCallback {
    public:
        SendCallbackImpl(jobject callback_);

        ~SendCallbackImpl() override;

    protected:
        void OnProgress(uint32_t progress) override;

        void OnSuccess(const V2TIMMessage &value) override;

        void OnError(int error_code, const V2TIMString &error_message) override;

    private:
        jobject send_callback_;
    };
}

#endif //IMCPLUSPLUSDEMO_SEND_CALLBACK_IMPL_H
