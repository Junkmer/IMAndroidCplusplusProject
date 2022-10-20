//
// Created by EDY on 2022/9/26.
//

#ifndef IMCPLUSPLUSDEMO_VALUE_CALLBACK_IMPL_H
#define IMCPLUSPLUSDEMO_VALUE_CALLBACK_IMPL_H

#include "../include/V2TIMCallback.h"
#include <functional>
#include <jni.h>
#include <V2TIMFriendship.h>
#include "functional"
#include "V2TIMErrorCode.h"
#include "v2_im_common.h"

namespace v2im {
    template<class T>
    class ValueCallbackImpl final : public V2TIMValueCallback<T> {
    public:
        using ValueCallback = std::function<void(const int, const V2TIMString &, const T &)>;

        ValueCallbackImpl() = default;
        ~ValueCallbackImpl() override = default;

        void setCallback(ValueCallback value_callback) {
            _value_callback_ = std::move(value_callback);
        }

    protected:

        // V2TIMValueCallback
        void OnSuccess(const T &value) override {
            if (_value_callback_) {
                _value_callback_(V2TIMErrorCode::ERR_SUCC, "", value);
            }
        }

        void OnError(const int error_code, const V2TIMString &error_message) override {
            if (_value_callback_) {
                _value_callback_(error_code, error_message, {});
            }
        }

    private:
        ValueCallback _value_callback_;
    };
}// namespace v2im

#endif //IMCPLUSPLUSDEMO_VALUE_CALLBACK_IMPL_H
