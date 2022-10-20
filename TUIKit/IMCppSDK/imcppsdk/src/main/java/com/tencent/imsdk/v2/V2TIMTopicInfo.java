package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMTopicInfo.html
 */
public class V2TIMTopicInfo implements Serializable {
    private String topicID;
    private String topicName;
    private String topicFaceUrl;
    private String introduction;
    private String notification;
    private boolean allMute;
    private long selfMuteTime;
    private String customString;
    private int recvOpt;
    private String draftText;
    private long unreadCount;
    private V2TIMMessage lastMessage;
    private List<V2TIMGroupAtInfo> groupAtInfoList = new ArrayList<>();

    public String getTopicID() {
        return topicID;
    }

    public void setTopicID(String topicID) {
        this.topicID = topicID;
    }

    public String getTopicName() {
        return topicName;
    }

    public void setTopicName(String topicName) {
        this.topicName = topicName;
    }

    public String getTopicFaceUrl() {
        return topicFaceUrl;
    }

    public void setTopicFaceUrl(String topicFaceUrl) {
        this.topicFaceUrl = topicFaceUrl;
    }

    public String getIntroduction() {
        return introduction;
    }

    public void setIntroduction(String introduction) {
        this.introduction = introduction;
    }

    public String getNotification() {
        return notification;
    }

    public void setNotification(String notification) {
        this.notification = notification;
    }

    public boolean isAllMute() {
        return allMute;
    }

    public void setAllMute(boolean allMute) {
        this.allMute = allMute;
    }

    public long getSelfMuteTime() {
        return selfMuteTime;
    }

    public String getCustomString() {
        return customString;
    }

    public void setCustomString(String customString) {
        this.customString = customString;
    }

    public int getRecvOpt() {
        return recvOpt;
    }

    public String getDraftText() {
        return draftText;
    }

    public void setDraftText(String draftText) {
        this.draftText = draftText;
    }

    public long getUnreadCount() {
        return unreadCount;
    }

    public V2TIMMessage getLastMessage() {
        return lastMessage;
    }

    public List<V2TIMGroupAtInfo> getGroupAtInfoList() {
        return groupAtInfoList;
    }

    private void addGroupAtInfo(V2TIMGroupAtInfo atInfo){
        groupAtInfoList.add(atInfo);
    }
}
