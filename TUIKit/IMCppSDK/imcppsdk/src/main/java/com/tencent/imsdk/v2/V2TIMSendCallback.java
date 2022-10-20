package com.tencent.imsdk.v2;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/interfacecom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMSendCallback.html
 */
public interface V2TIMSendCallback<T> {
    void onProgress(int progress);

    void onSuccess(T t);

    void onError(int code, String desc);
}
