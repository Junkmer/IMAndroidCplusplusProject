package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMConversationOperationResult.html
 */
public class V2TIMConversationOperationResult implements Serializable {
    private String conversationID;
    private int resultCode;
    private String resultInfo;

    public String getConversationID() {
        return conversationID;
    }

    public int getResultCode() {
        return resultCode;
    }

    public String getResultInfo() {
        return resultInfo;
    }
}
