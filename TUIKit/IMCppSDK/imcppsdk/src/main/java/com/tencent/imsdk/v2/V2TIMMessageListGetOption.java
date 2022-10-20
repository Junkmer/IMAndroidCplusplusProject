package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMMessageListGetOption.html
 */
public class V2TIMMessageListGetOption implements Serializable {
    public static final int V2TIM_GET_CLOUD_OLDER_MSG = 1;
    public static final int V2TIM_GET_CLOUD_NEWER_MSG = 2;
    public static final int V2TIM_GET_LOCAL_OLDER_MSG = 3;
    public static final int V2TIM_GET_LOCAL_NEWER_MSG = 4;

    private int getType;
    private String userID;
    private String groupID;
    private int count;
    private V2TIMMessage lastMsg;
    private long lastMsgSeq;
    private long getTimeBegin;
    private long getTimePeriod;
    private List<Integer> messageTypeList = new ArrayList<>();

    public int getGetType() {
        return getType;
    }

    public void setGetType(int getType) {
        this.getType = getType;
    }

    public String getUserID() {
        return userID;
    }

    public void setUserID(String userID) {
        this.userID = userID;
    }

    public String getGroupID() {
        return groupID;
    }

    public void setGroupID(String groupID) {
        this.groupID = groupID;
    }

    public int getCount() {
        return count;
    }

    public void setCount(int count) {
        this.count = count;
    }

    public V2TIMMessage getLastMsg() {
        return lastMsg;
    }

    public void setLastMsg(V2TIMMessage lastMsg) {
        this.lastMsg = lastMsg;
    }

    public long getLastMsgSeq() {
        return lastMsgSeq;
    }

    public void setLastMsgSeq(long lastMsgSeq) {
        this.lastMsgSeq = lastMsgSeq;
    }

    public long getGetTimeBegin() {
        return getTimeBegin;
    }

    public void setGetTimeBegin(long getTimeBegin) {
        this.getTimeBegin = getTimeBegin;
    }

    public long getGetTimePeriod() {
        return getTimePeriod;
    }

    public void setGetTimePeriod(long getTimePeriod) {
        this.getTimePeriod = getTimePeriod;
    }

    public List<Integer> getMessageTypeList() {
        return messageTypeList;
    }

    public void setMessageTypeList(List<Integer> messageTypeList) {
        this.messageTypeList = messageTypeList;
    }
}
