package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMConversationListFilter.html
 */
public class V2TIMConversationListFilter implements Serializable {
    private int conversationType;
    private String conversationGroup;
    private long markType;
    private boolean hasUnreadCount;
    private boolean hasGroupAtInfo;

    public int getConversationType() {
        return conversationType;
    }

    public void setConversationType(int conversationType) {
        this.conversationType = conversationType;
    }

    public String getConversationGroup() {
        return conversationGroup;
    }

    public void setConversationGroup(String conversationGroup) {
        this.conversationGroup = conversationGroup;
    }

    public long getMarkType() {
        return markType;
    }

    public void setMarkType(long markType) {
        this.markType = markType;
    }

    public boolean getHasUnreadCount() {
        return hasUnreadCount;
    }

    public void setHasUnreadCount(boolean hasUnreadCount) {
        this.hasUnreadCount = hasUnreadCount;
    }

    public boolean getHasGroupAtInfo() {
        return hasGroupAtInfo;
    }

    public void setHasGroupAtInfo(boolean hasGroupAtInfo) {
        this.hasGroupAtInfo = hasGroupAtInfo;
    }
}
