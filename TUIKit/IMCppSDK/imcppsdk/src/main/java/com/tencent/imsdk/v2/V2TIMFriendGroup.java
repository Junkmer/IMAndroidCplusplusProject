package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMFriendGroup.html
 */
public class V2TIMFriendGroup implements Serializable {
    private String name;
    private long friendCount;
    private List<String> friendIDList = new ArrayList<>();

    public String getName() {
        return name;
    }

    public long getFriendCount() {
        return friendCount;
    }

    public List<String> getFriendIDList() {
        return friendIDList;
    }

    private void addFriendID(String userID){
        friendIDList.add(userID);
    }
}
