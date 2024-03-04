package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * @Author Junker
 * @ClassName V2TIMMessageReactionChangeInfo
 * @date 2024/1/15 17:23
 * @Version 1.0
 * @Description
 */
public class V2TIMMessageReactionChangeInfo implements Serializable {
    private String messageID;
    private List<V2TIMMessageReaction> reactionList;

    public String getMessageID() {
        return messageID;
    }

    public List<V2TIMMessageReaction> getReactionList() {
        return reactionList;
    }
}
