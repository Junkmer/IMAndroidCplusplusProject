package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMUserStatus.html
 */
public class V2TIMUserStatus implements Serializable {
    public static final int V2TIM_USER_STATUS_UNKNOWN = 0;
    public static final int V2TIM_USER_STATUS_ONLINE = 1;
    public static final int V2TIM_USER_STATUS_OFFLINE = 2;
    public static final int V2TIM_USER_STATUS_UNLOGINED = 3;

    private String userID;
    private int statusType;
    private String customStatus;

    public String getUserID() {
        return userID;
    }

    public int getStatusType() {
        return statusType;
    }

    public String getCustomStatus() {
        return customStatus;
    }

    public void setCustomStatus(String customStatus) {
        this.customStatus = customStatus;
    }
}
