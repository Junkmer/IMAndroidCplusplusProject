package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.List;

/**
 * @Author Junker
 * @ClassName V2TIMMessageReaction
 * @date 2023/10/31 16:16
 * @Version 1.0
 * @Description
 */
public class V2TIMMessageReaction implements Serializable {
    private String reactionID;
    private int totalUserCount;
    private List<V2TIMUserInfo> partialUserList;
    private boolean reactedByMyself;

    public String getReactionID() {
        return reactionID;
    }

    public int getTotalUserCount() {
        return totalUserCount;
    }

    public List<V2TIMUserInfo> getPartialUserList() {
        return partialUserList;
    }

    public boolean isReactedByMyself() {
        return reactedByMyself;
    }

    @Override
    public String toString() {
        return "V2TIMMessageReaction{" +
                "reactionID='" + reactionID + '\'' +
                ", totalUserCount=" + totalUserCount +
                ", partialUserList=" + partialUserList +
                ", reactedByMyself=" + reactedByMyself +
                '}';
    }
}
