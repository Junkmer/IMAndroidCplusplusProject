package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMFriendOperationResult.html
 */
public class V2TIMFriendInfoResult implements Serializable {
    private int resultCode;
    private String resultInfo;
    private int relation;
    private V2TIMFriendInfo friendInfo;

    public int getResultCode() {
        return resultCode;
    }

    public String getResultInfo() {
        return resultInfo;
    }

    public int getRelation() {
        return relation;
    }

    public V2TIMFriendInfo getFriendInfo() {
        return friendInfo;
    }
}
