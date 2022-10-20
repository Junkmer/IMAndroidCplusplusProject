package com.tencent.imsdk.common;

import com.tencent.imsdk.v2.V2TIMCallback;
import com.tencent.imsdk.v2.V2TIMCompleteCallback;
import com.tencent.imsdk.v2.V2TIMDownloadCallback;
import com.tencent.imsdk.v2.V2TIMElem;
import com.tencent.imsdk.v2.V2TIMSendCallback;
import com.tencent.imsdk.v2.V2TIMValueCallback;

public abstract class IMCallback<T> {

    protected V2TIMCallback callback;
    protected V2TIMValueCallback<T> valueCallback;
    protected V2TIMCompleteCallback<T> completeCallback;
    protected V2TIMSendCallback<T> sendCallback;
    protected V2TIMDownloadCallback downloadCallback;

    protected IMCallback(V2TIMCallback cb) {
        this.callback = cb;
    }

    protected IMCallback(V2TIMValueCallback<T> cb) {
        this.valueCallback = cb;
    }

    protected IMCallback(V2TIMCompleteCallback<T> cb) {
        this.completeCallback = cb;
    }

    protected IMCallback(V2TIMSendCallback<T> cb) {
        this.sendCallback = cb;
    }

    protected IMCallback(V2TIMDownloadCallback cb) {
        this.downloadCallback = cb;
    }

    public void success(final T data) {
        IMContext.getInstance().runOnMainThread(new Runnable() {
            @Override
            public void run() {
                if (callback != null) {
                    callback.onSuccess();
                } else if (valueCallback != null) {
                    valueCallback.onSuccess(data);
                } else if (sendCallback != null) {
                    sendCallback.onSuccess(data);
                } else if (downloadCallback != null) {
                    downloadCallback.onSuccess();
                }
            }
        });
    }

    public void fail(final int code, final String errorMessage) {
        IMContext.getInstance().runOnMainThread(new Runnable() {
            @Override
            public void run() {
                if (callback != null) {
                    callback.onError(code, errorMessage);
                } else if (valueCallback != null) {
                    valueCallback.onError(code, errorMessage);
                } else if (sendCallback != null) {
                    sendCallback.onError(code, errorMessage);
                } else if (downloadCallback != null) {
                    downloadCallback.onError(code, errorMessage);
                }
            }
        });
    }

    public void failOrComplete(final int code, final String errorMessage, final T data) {
        IMContext.getInstance().runOnMainThread(new Runnable() {
            @Override
            public void run() {
                if (callback != null) {
                    callback.onError(code, errorMessage);
                } else if (valueCallback != null) {
                    valueCallback.onError(code, errorMessage);
                } else if (completeCallback != null) {
                    completeCallback.onComplete(code, errorMessage, data);
                }
            }
        });
    }

    public void progress(final int progress) {
        IMContext.getInstance().runOnMainThread(new Runnable() {
            @Override
            public void run() {
                if (sendCallback != null) {
                    sendCallback.onProgress(progress);
                }
            }
        });
    }

    public void downloadProgress(final long currentSize, final long totalSize) {
        IMContext.getInstance().runOnMainThread(new Runnable() {
            @Override
            public void run() {
                if (downloadCallback != null) {
                    downloadCallback.onProgress(new V2TIMElem.V2ProgressInfo(currentSize,totalSize));
                }
            }
        });
    }
}
