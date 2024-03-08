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

    /**
     * 以下字段用于C++ SDK 判断当前需要修改的参数标记
     */
    // 未定义
    private static final int   V2TIM_GROUP_INFO_MODIFY_FLAG_UNKNOWN = 0x00;
    // 名称
    private static final int  V2TIM_GROUP_INFO_MODIFY_FLAG_GROUP_NAME = 0x01;
    // 公告
    private static final int  V2TIM_GROUP_INFO_MODIFY_FLAG_NOTIFICATION = 0x01 << 1;
    // 简介
    private static final int  V2TIM_GROUP_INFO_MODIFY_FLAG_INTRODUCTION = 0x01 << 2;
    // 头像
    private static final int   V2TIM_GROUP_INFO_MODIFY_FLAG_FACE_URL = 0x01 << 3;
    // 加群选项
    private static final int  V2TIM_GROUP_INFO_MODIFY_FLAG_GROUP_ADD_OPTION = 0x01 << 4;
    // 禁言
    private static final int  V2TIM_GROUP_INFO_MODIFY_FLAG_SHUTUP_ALL = 0x01 << 8;
    // 群自定义数据
    private static final int  V2TIM_GROUP_INFO_MODIFY_FLAG_CUSTOM_INFO = 0x01 << 9;
    // 话题自定义字段
    private static final int  V2TIM_TOPIC_INFO_MODIFY_FLAG_CUSTOM_STRING = 0x1 << 11;
    // 邀请进群管理员审批选项
    private static final int V2TIM_GROUP_INFO_MODIFY_FLAG_GROUP_APPROVE_OPTION = 0x1 << 12;
    private int modifyFlag;

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
        modifyFlag |= V2TIM_GROUP_INFO_MODIFY_FLAG_GROUP_NAME;
        this.topicName = topicName;
    }

    public String getTopicFaceUrl() {
        return topicFaceUrl;
    }

    public void setTopicFaceUrl(String topicFaceUrl) {
        this.topicFaceUrl = topicFaceUrl;
        modifyFlag |= V2TIM_GROUP_INFO_MODIFY_FLAG_FACE_URL;
    }

    public String getIntroduction() {
        return introduction;
    }

    public void setIntroduction(String introduction) {
        modifyFlag |= V2TIM_GROUP_INFO_MODIFY_FLAG_INTRODUCTION;
        this.introduction = introduction;
    }

    public String getNotification() {
        return notification;
    }

    public void setNotification(String notification) {
        this.notification = notification;
        modifyFlag |= V2TIM_GROUP_INFO_MODIFY_FLAG_NOTIFICATION;
    }

    public boolean isAllMute() {
        return allMute;
    }

    public void setAllMute(boolean allMute) {
        this.allMute = allMute;
        modifyFlag |= V2TIM_GROUP_INFO_MODIFY_FLAG_SHUTUP_ALL;
    }

    public long getSelfMuteTime() {
        return selfMuteTime;
    }

    public String getCustomString() {
        return customString;
    }

    public void setCustomString(String customString) {
        modifyFlag |= V2TIM_TOPIC_INFO_MODIFY_FLAG_CUSTOM_STRING;
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
