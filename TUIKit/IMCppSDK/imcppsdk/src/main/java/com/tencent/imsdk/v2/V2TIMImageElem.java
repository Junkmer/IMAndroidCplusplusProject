package com.tencent.imsdk.v2;


import com.tencent.imsdk.common.DownloadParam;
import com.tencent.imsdk.common.IMCallback;

import java.io.Serializable;
import java.util.ArrayList;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMImageElem.html
 */
public class V2TIMImageElem extends V2TIMElem {
    public static final int V2TIM_IMAGE_TYPE_ORIGIN = 0;
    public static final int V2TIM_IMAGE_TYPE_THUMB = 1;
    public static final int V2TIM_IMAGE_TYPE_LARGE = 2;

    private String path;
    private List<V2TIMImage> imageList = new ArrayList<>();

    public V2TIMImageElem() {
        setElementType(V2TIMMessage.V2TIM_ELEM_TYPE_IMAGE);
    }

    public String getPath() {
        return path;
    }

    private void addImage(V2TIMImage timImage) {
        imageList.add(timImage);
    }

    public List<V2TIMImage> getImageList() {
        return imageList;
    }

    public class V2TIMImage implements Serializable {
        private String uuid;
        private int type;
        private int size;
        private int width;
        private int height;
        private String url;

        //仅用于下载，不对外公开
        private DownloadParam param;

        public String getUUID() {
            return uuid;
        }

        protected void setUUID(String uuid) {
            this.uuid = uuid;
        }

        public int getType() {
            return type;
        }

        protected void setType(int type) {
            this.type = type;
        }

        public int getSize() {
            return size;
        }

        protected void setSize(int size) {
            this.size = size;
        }

        public int getWidth() {
            return width;
        }

        protected void setWidth(int width) {
            this.width = width;
        }

        public int getHeight() {
            return height;
        }

        protected void setHeight(int height) {
            this.height = height;
        }

        public String getUrl() {
            return url;
        }

        protected void setUrl(String url) {
            this.url = url;
        }

        public void downloadImage(final String path, final V2TIMDownloadCallback v2TIMDownloadCallback) {
            nativeDownloadImage(param, type, path, new IMCallback(v2TIMDownloadCallback) {
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

        //底层方法
        native void nativeDownloadImage(DownloadParam param, int imageType, String path, IMCallback callback);
    }

    @Override
    public String toString() {
        return "V2TIMImageElem{" +
                "path='" + path + '\'' +
                ", imageList=" + imageList +
                '}';
    }

//    //底层方法
//    native void nativeDownloadImage(DownloadParam param, int imageType, String path, IMCallback callback);
}
