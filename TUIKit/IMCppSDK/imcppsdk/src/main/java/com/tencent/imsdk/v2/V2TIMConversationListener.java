package com.tencent.imsdk.v2;

import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMConversationListener.html
 */
public abstract class V2TIMConversationListener {

    public void onSyncServerStart() {
    }

    public void onSyncServerFinish() {
    }

    public void onSyncServerFailed() {
    }

    public void onNewConversation(List<V2TIMConversation> conversationList) {
    }

    public void onConversationChanged(List<V2TIMConversation> conversationList) {
    }

    public void onTotalUnreadMessageCountChanged(long totalUnreadCount) {
    }

    public void onConversationGroupCreated(String groupName, List<V2TIMConversation> conversationList) {
    }

    public void onConversationGroupDeleted(String groupName) {
    }

    public void onConversationGroupNameChanged(String oldName, String newName) {
    }

    public void onConversationsAddedToGroup(String groupName, List<V2TIMConversation> conversationList) {
    }

    public void onConversationsDeletedFromGroup(String groupName, List<V2TIMConversation> conversationList) {
    }


}
