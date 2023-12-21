package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupChangeInfo.html
 */
public class V2TIMGroupChangeInfo implements Serializable {
    public static final int V2TIM_GROUP_INFO_INVALID = 0;
    public static final int V2TIM_GROUP_INFO_CHANGE_TYPE_NAME = 1;
    public static final int V2TIM_GROUP_INFO_CHANGE_TYPE_INTRODUCTION = 2;
    public static final int V2TIM_GROUP_INFO_CHANGE_TYPE_NOTIFICATION = 3;
    public static final int V2TIM_GROUP_INFO_CHANGE_TYPE_FACE_URL = 4;
    public static final int V2TIM_GROUP_INFO_CHANGE_TYPE_OWNER = 5;
    public static final int V2TIM_GROUP_INFO_CHANGE_TYPE_CUSTOM = 6;
    public static final int V2TIM_GROUP_INFO_CHANGE_TYPE_SHUT_UP_ALL = 8;
    public static final int V2TIM_GROUP_INFO_CHANGE_TYPE_RECEIVE_MESSAGE_OPT = 10;
    public static final int V2TIM_GROUP_INFO_CHANGE_TYPE_GROUP_ADD_OPT = 11;
    public static final int V2TIM_GROUP_INFO_CHANGE_TYPE_GROUP_APPROVE_OPT = 12;

    private int type;
    private String value;
    private boolean boolValue;
    private int intValue;
    private String key;

    public int getType() {
        return type;
    }

    public String getValue() {
        return value;
    }

    public boolean getBoolValue() {
        return boolValue;
    }

    public int getIntValue() {
        return intValue;
    }

    public String getKey() {
        return key;
    }
}
