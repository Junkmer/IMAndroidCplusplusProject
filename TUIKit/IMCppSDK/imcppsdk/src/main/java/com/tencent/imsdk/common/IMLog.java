package com.tencent.imsdk.common;

import android.text.TextUtils;
import android.util.Log;

public class IMLog {
    private final static String TAG = "Junker - IMLog";

    private static boolean LOG_SWITCH = true;
    public static final int LOG_LEVEL_VERBOSE = 1;
    public static final int LOG_LEVEL_DEBUG = 2;
    public static final int LOG_LEVEL_INFO = 3;
    public static final int LOG_LEVEL_WARN = 4;
    public static final int LOG_LEVEL_ERROR = 5;

    private static final char[] START_TAG = {
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };
    private static final char[] MIDDLE_TAG = {
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ',
            ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '
    };

    public static void v(String strTag, String strInfo) {
        log(LOG_LEVEL_VERBOSE, strTag, strInfo);
    }

    public static void d(String strTag, String strInfo) {
        log(LOG_LEVEL_DEBUG, strTag, strInfo);
    }

    public static void i(String strTag, String strInfo) {
        log(LOG_LEVEL_INFO, strTag, strInfo);
    }

    public static void w(String strTag, String strInfo) {
        log(LOG_LEVEL_WARN, strTag, strInfo);
    }

    public static void e(String strTag, String strInfo) {
        log(LOG_LEVEL_ERROR, strTag, strInfo);
    }

    private static void log(final int logLevel, String strTag, String strInfo) {
        if (!isLogSwitch()) {
            //日志开关关闭时，不输出日志
            return;
        }

        if (logLevel < LOG_LEVEL_VERBOSE || logLevel > LOG_LEVEL_ERROR) {
            Log.e(TAG, "invalid logLevel： " + logLevel);
            return;
        }

        if (TextUtils.isEmpty(strTag)) {
            strTag = TAG;
        }

        if (TextUtils.isEmpty(strInfo)) {
            Log.e(TAG, "empty logContent");
            return;
        }
        int position;//截取 middleTag 文本的初始位置
        int length;//截取 middleTag 的总长度
        String middleStr = "";//最终截取 middleTag 文本
        position = strTag.length();
        if (position < MIDDLE_TAG.length) {
            length = MIDDLE_TAG.length - position;
            middleStr = new String(MIDDLE_TAG, position, length);
        }

        StringBuilder builder = new StringBuilder();
        builder.append(START_TAG).append(strTag).append(middleStr).append(strInfo);

        switch (logLevel) {
            case LOG_LEVEL_VERBOSE:
                Log.v(TAG, builder.toString());
                break;
            case LOG_LEVEL_DEBUG:
                Log.d(TAG, builder.toString());
                break;
            case LOG_LEVEL_INFO:
                Log.i(TAG, builder.toString());
                break;
            case LOG_LEVEL_WARN:
                Log.w(TAG, builder.toString());
                break;
            case LOG_LEVEL_ERROR:
                Log.e(TAG, builder.toString());
                break;
        }
    }

    public static boolean isLogSwitch() {
        return IMLog.LOG_SWITCH;
    }

    public static void setLogSwitch(boolean flag) {
        IMLog.LOG_SWITCH = flag;
    }

}
