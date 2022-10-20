package com.tencent.imsdk.v2;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMLocationElem.html
 */
public class V2TIMLocationElem extends V2TIMElem {
    private String desc;
    private double longitude;
    private double latitude;

    public V2TIMLocationElem(){
        setElementType(V2TIMMessage.V2TIM_ELEM_TYPE_LOCATION);
    }


    public String getDesc() {
        return desc;
    }

    public void setDesc(String desc) {
        this.desc = desc;
    }

    public double getLongitude() {
        return longitude;
    }

    public void setLongitude(double longitude) {
        this.longitude = longitude;
    }

    public double getLatitude() {
        return latitude;
    }

    public void setLatitude(double latitude) {
        this.latitude = latitude;
    }
}
