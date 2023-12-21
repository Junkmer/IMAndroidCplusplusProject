package com.tencent.imsdk.v2;

import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMSDKListener.html
 */
public abstract class V2TIMSDKListener {

    public void onConnecting() {

    }

    public void onConnectSuccess() {

    }

    public void onConnectFailed(int code, String error) {

    }

    public void onKickedOffline() {

    }

    public void onUserSigExpired() {

    }

    public void onSelfInfoUpdated(V2TIMUserFullInfo info) {

    }

    public void onUserStatusChanged(List<V2TIMUserStatus> userStatusList) {

    }

    public void onUserInfoChanged(List<V2TIMUserFullInfo> userInfoList) {

    }

    public void onAllReceiveMessageOptChanged(V2TIMReceiveMessageOptInfo receiveMessageOptInfo) {

    }

    public void onExperimentalNotify(String key, Object param) {

    }
}
