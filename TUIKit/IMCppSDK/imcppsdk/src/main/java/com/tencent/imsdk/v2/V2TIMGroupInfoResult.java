package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupInfoResult.html
 */
public class V2TIMGroupInfoResult implements Serializable {
    private int resultCode;
    private String resultMessage;
    private V2TIMGroupInfo groupInfo;

    public int getResultCode() {
        return resultCode;
    }

    public String getResultMessage() {
        return resultMessage;
    }

    public V2TIMGroupInfo getGroupInfo() {
        return groupInfo;
    }
}
