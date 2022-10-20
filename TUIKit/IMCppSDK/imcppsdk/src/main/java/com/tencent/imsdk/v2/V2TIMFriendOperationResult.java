package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMFriendOperationResult.html
 */
public class V2TIMFriendOperationResult implements Serializable {
    private String userID;
    private int resultCode;
    private String resultInfo;

    public String getUserID() {
        return userID;
    }

    public int getResultCode() {
        return resultCode;
    }

    public String getResultInfo() {
        return resultInfo;
    }
}
