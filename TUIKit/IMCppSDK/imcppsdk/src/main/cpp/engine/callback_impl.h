//
// Created by EDY on 2022/9/13.
//

#ifndef IMCPLUSPLUSDEMO_CALLBACK_IMPL_H
#define IMCPLUSPLUSDEMO_CALLBACK_IMPL_H

#include "../include/V2TIMCallback.h"
#include <functional>
#include <jni.h>
#include "functional"

namespace v2im {
    class CallbackIMpl final : public V2TIMCallback{
    public://构造函数 和 回调函数
        CallbackIMpl(jobject listener_callback_);

        ~CallbackIMpl() override;

    protected://自实现父类函数

        // V2TIMCallback
        void OnSuccess() override;

        void OnError(int error_code, const V2TIMString &error_message) override;

    private:
        jobject listener_callback_;
    };
}


#endif //IMCPLUSPLUSDEMO_CALLBACK_IMPL_H
