package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMFriendInfo.html
 */
public class V2TIMFriendInfo implements Serializable {
    public static final int V2TIM_FRIEND_TYPE_SINGLE = 1;
    public static final int V2TIM_FRIEND_TYPE_BOTH = 2;

    private String userID;
    private String friendRemark;
    private long friendAddTime;
    private List<String> friendGroups = new ArrayList<>();
    private HashMap<String, byte[]> friendCustomInfo = new HashMap<>();
    private V2TIMUserFullInfo userFullInfo;

    public String getUserID() {
        return userID;
    }

    public void setUserID(String userID) {
        this.userID = userID;
    }

    public String getFriendRemark() {
        return friendRemark;
    }

    public void setFriendRemark(String friendRemark) {
        this.friendRemark = friendRemark;
    }

    public long getFriendAddTime() {
        return friendAddTime;
    }

    public List<String> getFriendGroups() {
        return friendGroups;
    }

    public HashMap<String, byte[]> getFriendCustomInfo() {
        return friendCustomInfo;
    }

    public V2TIMUserFullInfo getUserProfile() {
        return userFullInfo;
    }

    private void addFriendGroup(String friendGroup) {
        friendGroups.add(friendGroup);
    }

    private void putFriendCustomInfo(String key, byte[] value) {
        friendCustomInfo.put(key, value);
    }

    @Override
    public String toString() {
        return "V2TIMFriendInfo{" +
                "userID='" + userID + '\'' +
                ", friendRemark='" + friendRemark + '\'' +
                ", friendAddTime='" + friendAddTime + '\'' +
                ", friendGroups=" + friendGroups +
                ", friendCustomInfo=" + friendCustomInfo +
                ", userProfile=" + userFullInfo +
                '}';
    }
}
