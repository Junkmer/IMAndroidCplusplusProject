package com.tencent.imsdk.v2;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/interfacecom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMCompleteCallback.html
 */
public interface V2TIMCompleteCallback<T> {
    void onComplete(int code, String desc, T t);
}

