//
// Created by EDY on 2022/10/9.
//

#ifndef IMCPLUSPLUSDEMO_V2_IM_COMMON_H
#define IMCPLUSPLUSDEMO_V2_IM_COMMON_H

#include "../include/V2TIMString.h"

namespace v2im {

    // 公共可变参数回调定义
    template<typename... Args>
    using Callback = std::function<void(const int &error_code, const V2TIMString &error_message, Args...)>;
    using VariableCallback = std::function<void(V2TIMMessage &value)>;

}  // namespace v2im

#endif //IMCPLUSPLUSDEMO_V2_IM_COMMON_H
