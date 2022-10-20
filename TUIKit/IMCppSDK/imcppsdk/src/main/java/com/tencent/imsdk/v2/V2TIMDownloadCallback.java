package com.tencent.imsdk.v2;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/interfacecom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMDownloadCallback.html
 */
public interface V2TIMDownloadCallback {

    void onProgress(V2TIMElem.V2ProgressInfo progressInfo);

    void onSuccess();

    void onError(int code, String desc);
}
