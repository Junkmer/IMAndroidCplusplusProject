package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMConversationListFilter.html
 */
public class V2TIMConversationListFilter implements Serializable {
    private int conversationType;
    private long nextSeq;
    private int count;
    private long markType;
    private String groupName;

    public void setConversationType(int conversationType) {
        this.conversationType = conversationType;
    }

    public void setNextSeq(long nextSeq) {
        this.nextSeq = nextSeq;
    }

    public void setCount(int count) {
        this.count = count;
    }

    public void setMarkType(long markType) {
        this.markType = markType;
    }

    public void setGroupName(String groupName) {
        this.groupName = groupName;
    }
}
