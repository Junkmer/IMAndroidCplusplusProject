package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.DownloadParam;
import com.tencent.imsdk.common.IMCallback;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMVideoElem.html
 */
public class V2TIMVideoElem extends V2TIMElem {
    // 视频
    private String videoPath;
    private String videoUUID;
    private int videoSize;
    private int duration;
    // 缩略图
    private String snapshotPath;
    private String snapshotUUID;
    private int snapshotSize;
    private int snapshotWidth;
    private int snapshotHeight;

    //仅用于下载，不对外公开
    private DownloadParam param;

    public V2TIMVideoElem() {
        setElementType(V2TIMMessage.V2TIM_ELEM_TYPE_VIDEO);
    }

    public String getVideoPath() {
        return videoPath;
    }

    public String getVideoUUID() {
        return videoUUID;
    }

    public int getVideoSize() {
        return videoSize;
    }

    public int getDuration() {
        return duration;
    }

    public void downloadVideo(final String path, final V2TIMDownloadCallback v2TIMDownloadCallback) {
        nativeDownloadVideo(param, path, new IMCallback(v2TIMDownloadCallback) {
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

    public void getVideoUrl(final V2TIMValueCallback<String> callback) {
        nativeGetVideoUrl(param, new IMCallback<String>(callback) {
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

    public String getSnapshotPath() {
        return snapshotPath;
    }

    public String getSnapshotUUID() {
        return snapshotUUID;
    }

    public int getSnapshotSize() {
        return snapshotSize;
    }

    public int getSnapshotWidth() {
        return snapshotWidth;
    }

    public int getSnapshotHeight() {
        return snapshotHeight;
    }

    public void downloadSnapshot(final String path, final V2TIMDownloadCallback v2TIMDownloadCallback) {
        nativeDownloadSnapshot(param, path, new IMCallback(v2TIMDownloadCallback) {
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

    public void getSnapshotUrl(final V2TIMValueCallback<String> callback) {
        nativeGetSnapshotUrl(param, new IMCallback<String>(callback) {
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
        return "V2TIMVideoElem{" +
                "videoPath='" + videoPath + '\'' +
                ", videoUUID='" + videoUUID + '\'' +
                ", videoSize=" + videoSize +
                ", duration=" + duration +
                ", snapshotPath='" + snapshotPath + '\'' +
                ", snapshotUUID='" + snapshotUUID + '\'' +
                ", snapshotSize=" + snapshotSize +
                ", snapshotWidth=" + snapshotWidth +
                ", snapshotHeight=" + snapshotHeight +
                '}';
    }


    //底层方法
    native void nativeGetVideoUrl(DownloadParam param, IMCallback<String> callback);
    native void nativeGetSnapshotUrl(DownloadParam param, IMCallback<String> callback);
    native void nativeDownloadVideo(DownloadParam param, String path, IMCallback callback);
    native void nativeDownloadSnapshot(DownloadParam param, String path, IMCallback callback);
}
