// Copyright (c) 2023 Tencent. All rights reserved.

#ifndef __V2TIM_OFFICIAL_ACCOUNT_H__
#define __V2TIM_OFFICIAL_ACCOUNT_H__

#include "V2TIMCommon.h"

/// 公众号资料
struct TIM_API V2TIMOfficialAccountInfo {
    /// 公众号 ID
    V2TIMString officialAccountID;
    /// 名称
    V2TIMString officialAccountName;
    /// 头像
    V2TIMString faceUrl;
    /// 所有者
    V2TIMString ownerUserID;
    /// 组织
    V2TIMString organization;
    /// 简介
    V2TIMString introduction;
    /// 自定义数据
    V2TIMString customData;
    /// 创建公众号的时间，单位：秒
    uint64_t createTime;
    /// 公众号订阅者数量
    uint64_t subscriberCount;
    /// 订阅的时间，单位：秒
    uint64_t subscribeTime;

    V2TIMOfficialAccountInfo();
    V2TIMOfficialAccountInfo(const V2TIMOfficialAccountInfo& officialAccountInfo);
    ~V2TIMOfficialAccountInfo();
};

/// 公众号资料获取结果
struct TIM_API V2TIMOfficialAccountInfoResult {
    /// 返回码
    int resultCode;
    /// 返回结果表述
    V2TIMString resultInfo;
    /// 公众号资料
    V2TIMOfficialAccountInfo officialAccountInfo;

    V2TIMOfficialAccountInfoResult();
    V2TIMOfficialAccountInfoResult(const V2TIMOfficialAccountInfoResult& officialAccountInfoResult);
    ~V2TIMOfficialAccountInfoResult();
};

DEFINE_VECTOR(V2TIMOfficialAccountInfoResult)
typedef TXV2TIMOfficialAccountInfoResultVector V2TIMOfficialAccountInfoResultVector;

#endif  /* __V2TIM_OFFICIAL_ACCOUNT_H__ */
