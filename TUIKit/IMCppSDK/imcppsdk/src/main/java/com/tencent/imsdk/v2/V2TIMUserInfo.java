package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMUserInfo.html
 */
public class V2TIMUserInfo implements Serializable {
    private String userID;
    private String nickName;
    private String faceUrl;
    private long birthday = Long.MIN_VALUE;

    public String getUserID() {
        return userID;
    }

    public String getNickName() {
        return nickName;
    }

    public String getFaceUrl() {
        return faceUrl;
    }

    public long getBirthday() {
        if (birthday == Long.MIN_VALUE){
            return 0;
        }
        return birthday;
    }

    public void setBirthday(long birthday) {
        this.birthday = birthday;
    }

    protected void setUserID(String userID) {
        this.userID = userID;
    }

    protected void setNickname(String nickname) {
        this.nickName = nickname;
    }

    protected void setFaceUrl(String faceUrl) {
        this.faceUrl = faceUrl;
    }

    @Override
    public String toString() {
        return "V2TIMUserInfo{" +
                "userID='" + userID + '\'' +
                ", nickName='" + nickName + '\'' +
                ", faceUrl='" + faceUrl + '\'' +
                ", birthday=" + birthday +
                '}';
    }
}
