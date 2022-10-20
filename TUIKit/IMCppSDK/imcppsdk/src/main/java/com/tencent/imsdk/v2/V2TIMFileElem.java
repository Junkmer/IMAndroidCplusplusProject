package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.DownloadParam;
import com.tencent.imsdk.common.IMCallback;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMFileElem.html
 */
public class V2TIMFileElem extends V2TIMElem {
    private String path;
    private String fileName;
    private String UUID;
    private int fileSize;

    //仅用于下载，不对外公开
    private DownloadParam param;

    public V2TIMFileElem() {
        setElementType(V2TIMMessage.V2TIM_ELEM_TYPE_FILE);
    }


    public String getPath() {
        return path;
    }

    public String getFileName() {
        return fileName;
    }

    public String getUUID() {
        return UUID;
    }

    public int getFileSize() {
        return fileSize;
    }

    public void downloadFile(final String path, final V2TIMDownloadCallback v2TIMDownloadCallback) {
        nativeDownloadFile(param, path, new IMCallback(v2TIMDownloadCallback) {
            @Override
            public void downloadProgress(long currentSize, long totalSize) {
                super.downloadProgress(currentSize, totalSize);
            }

            @Override
            public void success(Object data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    public void getUrl(final V2TIMValueCallback<String> callback) {
        nativeGetFileUrl(param, new IMCallback<String>(callback) {
            @Override
            public void success(String data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public String toString() {
        return "V2TIMFileElem{" +
                "path='" + path + '\'' +
                ", fileName='" + fileName + '\'' +
                ", UUID='" + UUID + '\'' +
                ", fileSize=" + fileSize +
                '}';
    }


    //底层方法
    native void nativeGetFileUrl(DownloadParam param, IMCallback<String> callback);

    native void nativeDownloadFile(DownloadParam param, String path, IMCallback callback);
}
