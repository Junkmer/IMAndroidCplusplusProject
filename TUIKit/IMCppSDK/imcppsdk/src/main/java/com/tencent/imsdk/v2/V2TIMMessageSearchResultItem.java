package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMMessageSearchResultItem.html
 */
public class V2TIMMessageSearchResultItem implements Serializable {
    private String conversationID;
    private int messageCount;
    private List<V2TIMMessage> messageList = new ArrayList<>();

    public String getConversationID() {
        return conversationID;
    }

    public int getMessageCount() {
        return messageCount;
    }

    public List<V2TIMMessage> getMessageList() {
        return messageList;
    }

    private void addMessage(V2TIMMessage message){
        this.messageList.add(message);
    }
}