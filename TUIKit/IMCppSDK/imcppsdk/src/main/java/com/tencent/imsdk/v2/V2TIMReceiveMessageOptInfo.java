package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMReceiveMessageOptInfo.html
 */
public class V2TIMReceiveMessageOptInfo implements Serializable {
    private int c2CReceiveMessageOpt;
    private String userID;

    public int getC2CReceiveMessageOpt() {
        return c2CReceiveMessageOpt;
    }

    public String getUserID() {
        return userID;
    }

    public void setUserID(String userID) {
        this.userID = userID;
    }
}
