package com.tencent.imsdk.v2;

import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMFriendshipListener.html
 */
public abstract class V2TIMFriendshipListener {
    public void onFriendApplicationListAdded(List<V2TIMFriendApplication> applicationList) {
    }

    public void onFriendApplicationListDeleted(List<String> userIDList) {
    }

    public void onFriendApplicationListRead() {
    }

    public void onFriendListAdded(List<V2TIMFriendInfo> users) {
    }

    public void onFriendListDeleted(List<String> userList) {
    }

    public void onBlackListAdd(List<V2TIMFriendInfo> infoList) {
    }

    public void onBlackListDeleted(List<String> userList) {
    }

    public void onFriendInfoChanged(List<V2TIMFriendInfo> infoList) {
    }
}
