package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.Map;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupInfo.html
 */
public class V2TIMGroupInfo implements Serializable {
    public static final int V2TIM_GROUP_ADD_FORBID = 0;
    public static final int V2TIM_GROUP_ADD_AUTH = 1;
    public static final int V2TIM_GROUP_ADD_ANY = 2;

    private String groupID;
    private String groupType;
    private boolean supportTopic;
    private String groupName;
    private String notification;
    private String introduction;
    private String faceUrl;
    private boolean isAllMuted;
    private String owner;
    private long createTime;
    private int groupAddOpt;
    private int groupApproveOpt = -1;
    private Map<String, byte[]> customInfo;
    private long lastInfoTime;
    private long lastMessageTime;
    private int memberCount;
    private int onlineCount;
    private long memberMaxCount;
    private int role;
    private int recvOpt;
    private long joinTime;

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

    public String getGroupID() {
        return groupID;
    }

    public void setGroupID(String groupID) {
        this.groupID = groupID;
    }

    public String getGroupType() {
        return groupType;
    }

    public void setGroupType(String groupType) {
        this.groupType = groupType;
    }

    public boolean isSupportTopic() {
        return supportTopic;
    }

    public void setSupportTopic(boolean supportTopic) {
        this.supportTopic = supportTopic;
    }

    public String getGroupName() {
        return groupName;
    }

    public void setGroupName(String groupName) {
        modifyFlag = modifyFlag | V2TIM_GROUP_INFO_MODIFY_FLAG_GROUP_NAME;
        this.groupName = groupName;
    }

    public String getNotification() {
        return notification;
    }

    public void setNotification(String notification) {
        modifyFlag = modifyFlag | V2TIM_GROUP_INFO_MODIFY_FLAG_NOTIFICATION;
        this.notification = notification;
    }

    public String getIntroduction() {
        return introduction;
    }

    public void setIntroduction(String introduction) {
        modifyFlag = modifyFlag | V2TIM_GROUP_INFO_MODIFY_FLAG_INTRODUCTION;
        this.introduction = introduction;
    }

    public String getFaceUrl() {
        return faceUrl;
    }

    public void setFaceUrl(String faceUrl) {
        modifyFlag = modifyFlag | V2TIM_GROUP_INFO_MODIFY_FLAG_FACE_URL;
        this.faceUrl = faceUrl;
    }

    public boolean isAllMuted() {
        return isAllMuted;
    }

    public void setAllMuted(boolean allMuted) {
        modifyFlag = modifyFlag | V2TIM_GROUP_INFO_MODIFY_FLAG_SHUTUP_ALL;
        isAllMuted = allMuted;
    }

    public String getOwner() {
        return owner;
    }

    public long getCreateTime() {
        return createTime;
    }

    public int getGroupAddOpt() {
        return groupAddOpt;
    }

    public void setGroupAddOpt(int groupAddOpt) {
        modifyFlag = modifyFlag | V2TIM_GROUP_INFO_MODIFY_FLAG_GROUP_ADD_OPTION;
        this.groupAddOpt = groupAddOpt;
    }

    public int getGroupApproveOpt() {
        return groupApproveOpt;
    }

    public void setGroupApproveOpt(int groupApproveOpt) {
        modifyFlag = modifyFlag | V2TIM_GROUP_INFO_MODIFY_FLAG_GROUP_APPROVE_OPTION;
        this.groupApproveOpt = groupApproveOpt;
    }

    public Map<String, byte[]> getCustomInfo() {
        return customInfo;
    }

    public void setCustomInfo(Map<String, byte[]> customInfo) {
        modifyFlag = modifyFlag | V2TIM_GROUP_INFO_MODIFY_FLAG_CUSTOM_INFO;
        this.customInfo = customInfo;
    }

    public long getLastInfoTime() {
        return lastInfoTime;
    }

    public long getLastMessageTime() {
        return lastMessageTime;
    }

    public int getMemberCount() {
        return memberCount;
    }

    public int getOnlineCount() {
        return onlineCount;
    }

    public long getMemberMaxCount() {
        return memberMaxCount;
    }

    public int getRole() {
        return role;
    }

    public int getRecvOpt() {
        return recvOpt;
    }

    public long getJoinTime() {
        return joinTime;
    }
}
