package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMConversationResult.html
 */
public class V2TIMConversationResult implements Serializable {

    private long nextSeq;
    private boolean isFinished;
    private List<V2TIMConversation> conversationList = new ArrayList<>();

    public long getNextSeq() {
        return nextSeq;
    }

    public boolean isFinished() {
        return isFinished;
    }

    public List<V2TIMConversation> getConversationList() {
        return conversationList;
    }

    private void addConversation(V2TIMConversation conversation){
        conversationList.add(conversation);
    }
}
