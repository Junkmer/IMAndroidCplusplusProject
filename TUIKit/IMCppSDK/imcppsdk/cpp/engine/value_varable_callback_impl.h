//
// Created by EDY on 2022/9/26.
//

#ifndef IMCPLUSPLUSDEMO_VALUE_Variable_CALLBACK_IMPL_H
#define IMCPLUSPLUSDEMO_VALUE_Variable_CALLBACK_IMPL_H

#include "../include/V2TIMCallback.h"
#include <functional>
#include <jni.h>
#include "functional"
#include "V2TIMErrorCode.h"
#include "v2_im_common.h"

namespace v2im {
    template<class T>
    class ValueVariableCallbackImpl final : public V2TIMValueCallback<T> {
    public:
        using ValueVariableCallback = std::function<void(const int, const V2TIMString &,const T &)>;

        ValueVariableCallbackImpl() = default;

        ~ValueVariableCallbackImpl() override = default;

        void setVariableCallback(ValueVariableCallback value_variable_callback_) {
            _value_variable_callback_ = std::move(value_variable_callback_);
        }

    protected:
        // V2TIMValueCallback
        void OnSuccess(const T &value) override {
            if (_value_variable_callback_) {
                _value_variable_callback_(V2TIMErrorCode::ERR_SUCC, "", value);
            }
        }

        void OnError(const int error_code, const V2TIMString &error_message) override {
            if (_value_variable_callback_) {
                _value_variable_callback_(error_code, error_message, {});
            }
        }

    private:
        ValueVariableCallback _value_variable_callback_;
    };
}// namespace v2im

#endif //IMCPLUSPLUSDEMO_VALUE_Variable_CALLBACK_IMPL_H
