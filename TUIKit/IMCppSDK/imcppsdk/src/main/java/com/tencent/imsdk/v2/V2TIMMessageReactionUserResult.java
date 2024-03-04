package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.List;

/**
 * @Author Junker
 * @ClassName V2TIMMessageReactionUserResult
 * @date 2023/10/31 16:19
 * @Version 1.0
 * @Description
 */
public class V2TIMMessageReactionUserResult implements Serializable {
    private List<V2TIMUserInfo> userInfoList;
    private int nextSeq;
    private boolean isFinished;

    public List<V2TIMUserInfo> getUserInfoList() {
        return userInfoList;
    }

    public int getNextSeq() {
        return nextSeq;
    }

    public boolean isFinished() {
        return isFinished;
    }

    @Override
    public String toString() {
        return "V2TIMMessageReactionUserResult{" +
                "userInfoList=" + userInfoList +
                ", nextSeq=" + nextSeq +
                ", isFinished=" + isFinished +
                '}';
    }
}
