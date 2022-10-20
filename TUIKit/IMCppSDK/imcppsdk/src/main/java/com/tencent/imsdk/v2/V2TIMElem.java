package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.IMLog;

import java.io.Serializable;
import java.util.List;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMElem.html
 */
public class V2TIMElem implements Serializable {
    private final static String TAG = V2TIMElem.class.getSimpleName();

    private List<V2TIMElem> elemList;
    private int elementType;
    private int elemIndex;

    public void setElemList(List<V2TIMElem> timElemList){
        this.elemList = timElemList;
    }

    void setElemIndex(int index) {
        this.elemIndex = index;
    }

    public V2TIMElem getNextElem() {
        if (elemList == null){
            return null;
        }

        int nextElemIndex = elemIndex + 1;
        if (nextElemIndex >= elemList.size()) {
            return null;
        }
        V2TIMElem v2TIMElem = new V2TIMElem();
        V2TIMElem baseElement = elemList.get(nextElemIndex);
        if (baseElement instanceof V2TIMTextElem) {
            v2TIMElem = new V2TIMTextElem();
        } else if (baseElement instanceof V2TIMImageElem) {
            v2TIMElem = new V2TIMImageElem();
        } else if (baseElement instanceof V2TIMVideoElem) {
            v2TIMElem = new V2TIMVideoElem();
        } else if (baseElement instanceof V2TIMSoundElem) {
            v2TIMElem = new V2TIMSoundElem();
        } else if (baseElement instanceof V2TIMFaceElem) {
            v2TIMElem = new V2TIMFaceElem();
        } else if (baseElement instanceof V2TIMFileElem) {
            v2TIMElem = new V2TIMFileElem();
        } else if (baseElement instanceof V2TIMCustomElem) {
            v2TIMElem = new V2TIMCustomElem();
        } else if (baseElement instanceof V2TIMLocationElem) {
            v2TIMElem = new V2TIMLocationElem();
        } else if (baseElement instanceof V2TIMMergerElem) {
            v2TIMElem = new V2TIMMergerElem();
        } else if (baseElement instanceof V2TIMGroupTipsElem) {
            v2TIMElem = new V2TIMGroupTipsElem();
        }
        v2TIMElem.setElemList(elemList);
        v2TIMElem.setElemIndex(nextElemIndex);
        return v2TIMElem;
    }

    public void appendElem(V2TIMElem v2TIMElem) {
        if (elemList == null) {
            IMLog.e(TAG, "appendElem error, must be first elem from message");
            return;
        }

        if (v2TIMElem instanceof V2TIMTextElem) {
            V2TIMTextElem textElem = new V2TIMTextElem();
            textElem.setText(((V2TIMTextElem) v2TIMElem).getText());
            addElement(textElem);
        } else if (v2TIMElem instanceof V2TIMCustomElem) {
            V2TIMCustomElem customElem = new V2TIMCustomElem();
            customElem.setData(((V2TIMCustomElem) v2TIMElem).getData());
            customElem.setDescription(((V2TIMCustomElem) v2TIMElem).getDescription());
            customElem.setExtension(((V2TIMCustomElem) v2TIMElem).getExtension());
            addElement(customElem);
        } else if (v2TIMElem instanceof V2TIMFaceElem) {
            V2TIMFaceElem faceElem = new V2TIMFaceElem();
            faceElem.setIndex(((V2TIMFaceElem) v2TIMElem).getIndex());
            faceElem.setData(((V2TIMFaceElem) v2TIMElem).getData());
            addElement(faceElem);
        } else if (v2TIMElem instanceof V2TIMLocationElem) {
            V2TIMLocationElem locationElem = new V2TIMLocationElem();
            locationElem.setLatitude(((V2TIMLocationElem) v2TIMElem).getLatitude());
            locationElem.setLongitude(((V2TIMLocationElem) v2TIMElem).getLongitude());
            locationElem.setDesc(((V2TIMLocationElem) v2TIMElem).getDesc());
            addElement(locationElem);
        } else {
            IMLog.e(TAG, "appendElem error, not support this elem type");
            return;
        }

        v2TIMElem.setElemList(elemList);
        v2TIMElem.setElemIndex(elemList.size() -1);
    }

    private void addElement(V2TIMElem v2TIMElem) {
        if (v2TIMElem == null) {
            return;
        }
        elemList.add(v2TIMElem);
    }

    private int getElementType() {
        return elementType;
    }

    public void setElementType(int elementType) {
        this.elementType = elementType;
    }

    public static class V2ProgressInfo {
        private final long currentSize;
        private final long totalSize;

        public V2ProgressInfo(long curr, long total) {
            currentSize = curr;
            totalSize = total;
        }

        public long getCurrentSize() {
            return currentSize;
        }

        public long getTotalSize() {
            return totalSize;
        }
    }
}
