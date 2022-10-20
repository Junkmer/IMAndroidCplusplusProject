package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupMemberInfoResult.html
 */
public class V2TIMGroupMemberInfoResult implements Serializable {
    private long nextSeq;
    private List<V2TIMGroupMemberFullInfo> memberInfoList = new ArrayList<>();

    public long getNextSeq() {
        return nextSeq;
    }

    public List<V2TIMGroupMemberFullInfo> getMemberInfoList() {
        return memberInfoList;
    }

    private void addMemberInfo(V2TIMGroupMemberFullInfo memberFullInfo){
        this.memberInfoList.add(memberFullInfo);
    }
}
