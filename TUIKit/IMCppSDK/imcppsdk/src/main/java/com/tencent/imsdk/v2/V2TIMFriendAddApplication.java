package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMFriendAddApplication.html
 */
public class V2TIMFriendAddApplication implements Serializable {
    private String userID;
    private String remark;
    private String friendGroup;
    private String addWording;
    private String addSource;
    private int addType;

    public V2TIMFriendAddApplication (String userID){
        this.userID = userID;
    }

    public void setUserID(String userID) {
        this.userID = userID;
    }

    public void setFriendRemark(String remark) {
        this.remark = remark;
    }

    public void setFriendGroup(String friendGroup) {
        this.friendGroup = friendGroup;
    }

    public void setAddWording(String addWording) {
        this.addWording = addWording;
    }

    public void setAddSource(String addSource) {
        this.addSource = addSource;
    }

    public void setAddType(int addType) {
        this.addType = addType;
    }
}
