package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMGroupApplicationResult.html
 */
public class V2TIMGroupApplicationResult implements Serializable {
    private int unreadCount;
    private List<V2TIMGroupApplication> groupApplicationList = new ArrayList<>();

    public int getUnreadCount() {
        return unreadCount;
    }

    public List<V2TIMGroupApplication> getGroupApplicationList() {
        return groupApplicationList;
    }

    private void addGroupApplication(V2TIMGroupApplication application){
        groupApplicationList.add(application);
    }
}
