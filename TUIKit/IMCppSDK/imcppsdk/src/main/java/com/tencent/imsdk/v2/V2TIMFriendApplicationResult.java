package com.tencent.imsdk.v2;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：
 */
public class V2TIMFriendApplicationResult implements Serializable {
    private int unreadCount;
    private List<V2TIMFriendApplication> friendApplicationList = new ArrayList<>();

    public int getUnreadCount() {
        return unreadCount;
    }

    public List<V2TIMFriendApplication> getFriendApplicationList() {
        return friendApplicationList;
    }

    private void addFriendApplication(V2TIMFriendApplication application){
        friendApplicationList.add(application);
    }
}
