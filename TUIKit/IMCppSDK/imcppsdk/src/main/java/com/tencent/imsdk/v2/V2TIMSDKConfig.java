package com.tencent.imsdk.v2;

import java.io.Serializable;

/**
 * api docs链接：https://im.sdk.qcloud.com/doc/zh-cn/classcom_1_1tencent_1_1imsdk_1_1v2_1_1V2TIMSDKConfig.html
 */
public class V2TIMSDKConfig implements Serializable {
    public static final int V2TIM_LOG_NONE = 0;
    public static final int V2TIM_LOG_DEBUG = 3;
    public static final int V2TIM_LOG_INFO = 4;
    public static final int V2TIM_LOG_WARN = 5;
    public static final int V2TIM_LOG_ERROR = 6;

    //初始化数据保存地址
    private String sdkInitPath = "";
    //IM 日志保存地址
    private String sdkLogPath = "";
    //日志等级
    private int logLevel = V2TIM_LOG_DEBUG;
    //日志回调
    private V2TIMLogListener v2TIMLogListener;

    public V2TIMSDKConfig() {
    }

    public void setLogLevel(int logLevel) {
        this.logLevel = logLevel;
    }

    public int getLogLevel() {
        return logLevel;
    }

    public V2TIMLogListener getLogListener() {
        return v2TIMLogListener;
    }

    public void setLogListener(V2TIMLogListener logListener) {
        this.v2TIMLogListener = logListener;
    }
}
