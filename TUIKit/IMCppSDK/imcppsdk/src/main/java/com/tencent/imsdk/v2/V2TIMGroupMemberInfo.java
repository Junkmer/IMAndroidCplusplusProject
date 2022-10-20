package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupMemberInfo.html
 */
public class V2TIMGroupMemberInfo implements Serializable {
    private String userID;
    private String nickName;
    private String nameCard;
    private String friendRemark;
    private String faceUrl;

    public String getUserID() {
        return userID;
    }

    public String getNickName() {
        return nickName;
    }

    public String getNameCard() {
        return nameCard;
    }

    public String getFriendRemark() {
        return friendRemark;
    }

    public String getFaceUrl() {
        return faceUrl;
    }

    protected void setUserID(String userID) {
        this.userID = userID;
    }

    protected void setNameCard(String nameCard) {
        this.nameCard = nameCard;
    }

    @Override
    public String toString() {
        return "V2TIMGroupMemberInfo{" +
                "userID='" + userID + '\'' +
                ", nickName='" + nickName + '\'' +
                ", nameCard='" + nameCard + '\'' +
                ", friendRemark='" + friendRemark + '\'' +
                ", faceUrl='" + faceUrl + '\'' +
                '}';
    }
}
