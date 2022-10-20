package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMConversation.html
 */
public class V2TIMConversation implements Serializable {
    public static final int CONVERSATION_TYPE_INVALID = 0;
    public static final int V2TIM_C2C = 1;
    public static final int V2TIM_GROUP = 2;
    public static long V2TIM_CONVERSATION_MARK_TYPE_STAR = 0x1;
    public static long V2TIM_CONVERSATION_MARK_TYPE_UNREAD = 0x1 << 1;
    public static long V2TIM_CONVERSATION_MARK_TYPE_FOLD = 0x1 << 2;
    public static long V2TIM_CONVERSATION_MARK_TYPE_HIDE = 0x1 << 3;

    private String conversationID;
    private int type;
    private String userID;
    private String groupID;
    private String showName;
    private String faceUrl;
    private int recvOpt;
    private String groupType;
    private int unreadCount;
    private V2TIMMessage lastMessage;
    private String draftText;
    private long draftTimestamp;
    private List<V2TIMGroupAtInfo> groupAtInfoList = new ArrayList<>();
    private boolean pinned;
    private long orderKey;
    private List<Long> markList = new ArrayList<>();
    private String customData;
    private List<String> conversationGroupList = new ArrayList<>();

    public String getConversationID() {
        return conversationID;
    }

    public int getType() {
        return type;
    }

    public String getUserID() {
        return userID;
    }

    public String getGroupID() {
        return groupID;
    }

    public String getShowName() {
        return showName;
    }

    public String getFaceUrl() {
        return faceUrl;
    }

    public int getRecvOpt() {
        return recvOpt;
    }

    public String getGroupType() {
        return groupType;
    }

    public int getUnreadCount() {
        return unreadCount;
    }

    public V2TIMMessage getLastMessage() {
        return lastMessage;
    }

    public String getDraftText() {
        return draftText;
    }

    public long getDraftTimestamp() {
        return draftTimestamp;
    }

    public List<V2TIMGroupAtInfo> getGroupAtInfoList() {
        return groupAtInfoList;
    }

    public boolean isPinned() {
        return pinned;
    }

    public long getOrderKey() {
        return orderKey;
    }

    public List<Long> getMarkList() {
        return markList;
    }

    public String getCustomData() {
        return customData;
    }

    public List<String> getConversationGroupList() {
        return conversationGroupList;
    }

    private void addGroupAtInfo(V2TIMGroupAtInfo groupAtInfo){
        if (null != groupAtInfo){
            groupAtInfoList.add(groupAtInfo);
        }
    }

    private void addMark(long mark){
        markList.add(mark);
    }

    private void addConversationGroup(String conversationGroup){
        if (null != conversationGroup){
            conversationGroupList.add(conversationGroup);
        }
    }

    @Override
    public String toString() {
        return "V2TIMConversation{" +
                "conversationID='" + conversationID + '\'' +
                ", type=" + type +
                ", userID='" + userID + '\'' +
                ", groupID='" + groupID + '\'' +
                ", showName='" + showName + '\'' +
                ", faceUrl='" + faceUrl + '\'' +
                ", recvOpt=" + recvOpt +
                ", groupType='" + groupType + '\'' +
                ", unreadCount=" + unreadCount +
                ", lastMessage=" + lastMessage +
                ", draftText='" + draftText + '\'' +
                ", draftTimestamp=" + draftTimestamp +
                ", groupAtInfoList=" + groupAtInfoList +
                ", pinned=" + pinned +
                ", orderKey=" + orderKey +
                ", markList=" + markList +
                ", customData='" + customData + '\'' +
                ", conversationGroupList=" + conversationGroupList +
                '}';
    }
}
