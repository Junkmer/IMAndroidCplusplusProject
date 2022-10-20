package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMFriendCheckResult.html
 */
public class V2TIMFriendCheckResult implements Serializable {
    public static final int V2TIM_FRIEND_RELATION_TYPE_NONE = 0;
    public static final int V2TIM_FRIEND_RELATION_TYPE_IN_MY_FRIEND_LIST = 1;
    public static final int V2TIM_FRIEND_RELATION_TYPE_IN_OTHER_FRIEND_LIST = 2;
    public static final int V2TIM_FRIEND_RELATION_TYPE_BOTH_WAY = 3;

    private String userID;
    private int resultCode;
    private String resultInfo;
    private int resultType;

    public String getUserID() {
        return userID;
    }

    public int getResultCode() {
        return resultCode;
    }

    public String getResultInfo() {
        return resultInfo;
    }

    public int getResultType() {
        return resultType;
    }
}
