package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMTopicInfoResult.html
 */
public class V2TIMTopicInfoResult implements Serializable {
    private int errorCode;
    private String errorMessage;
    private V2TIMTopicInfo topicInfo;

    public int getErrorCode() {
        return errorCode;
    }

    public String getErrorMessage() {
        return errorMessage;
    }

    public V2TIMTopicInfo getTopicInfo() {
        return topicInfo;
    }
}
