package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMFriendApplication.html
 */
public class V2TIMFriendApplication implements Serializable {
    public static final int V2TIM_FRIEND_APPLICATION_COME_IN = 1;
    public static final int V2TIM_FRIEND_APPLICATION_SEND_OUT = 2;
    public static final int V2TIM_FRIEND_APPLICATION_BOTH = 3;
    public static final int V2TIM_FRIEND_ACCEPT_AGREE = 0;
    public static final int V2TIM_FRIEND_ACCEPT_AGREE_AND_ADD = 1;

    private String userID;
    private String nickname;
    private String faceUrl;
    private long addTime;
    private String addSource;
    private String addWording;
    private int type;

    public String getUserID() {
        return userID;
    }

    public String getNickname() {
        return nickname;
    }

    public String getFaceUrl() {
        return faceUrl;
    }

    public long getAddTime() {
        return addTime;
    }

    public String getAddSource() {
        return addSource;
    }

    public String getAddWording() {
        return addWording;
    }

    public int getType() {
        return type;
    }

    @Override
    public String toString() {
        return "V2TIMFriendApplication{" +
                "userID='" + userID + '\'' +
                ", nickname='" + nickname + '\'' +
                ", faceUrl='" + faceUrl + '\'' +
                ", addTime=" + addTime +
                ", addSource='" + addSource + '\'' +
                ", addWording='" + addWording + '\'' +
                ", type=" + type +
                '}';
    }
}
