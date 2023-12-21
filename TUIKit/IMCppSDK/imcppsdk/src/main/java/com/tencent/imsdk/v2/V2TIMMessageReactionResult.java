package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.List;

/**
 * @Author Junker
 * @ClassName V2TIMMessageReactionResult
 * @date 2023/10/31 16:15
 * @Version 1.0
 * @Description
 */
public class V2TIMMessageReactionResult implements Serializable {
    private int resultCode;
    private String resultInfo;
    private String messageID;
    private List<V2TIMMessageReaction> reactionList;

    public int getResultCode() {
        return resultCode;
    }

    public String getResultInfo() {
        return resultInfo;
    }

    public String getMessageID() {
        return messageID;
    }

    public List<V2TIMMessageReaction> getReactionList() {
        return reactionList;
    }

    @Override
    public String toString() {
        return "V2TIMMessageReactionResult{" +
                "resultCode=" + resultCode +
                ", resultInfo='" + resultInfo + '\'' +
                ", messageID='" + messageID + '\'' +
                ", reactionList=" + reactionList +
                '}';
    }
}
