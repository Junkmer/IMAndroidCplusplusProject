package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupMessageReadMemberList.html
 */
public class V2TIMGroupMessageReadMemberList implements Serializable {
    private long nextSeq;
    private boolean finished;
    private List<V2TIMGroupMemberInfo> memberInfoList = new ArrayList<>();

    public long getNextSeq() {
        return nextSeq;
    }

    public boolean isFinished() {
        return finished;
    }

    public List<V2TIMGroupMemberInfo> getMemberInfoList() {
        return memberInfoList;
    }

    private void addMemberInfo(V2TIMGroupMemberInfo memberInfo){
        this.memberInfoList.add(memberInfo);
    }
}
