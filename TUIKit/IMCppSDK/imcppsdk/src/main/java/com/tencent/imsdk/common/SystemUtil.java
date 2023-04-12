package com.tencent.imsdk.common;

import android.annotation.SuppressLint;
import android.app.ActivityManager;
import android.content.Context;
import android.text.TextUtils;
import android.util.Log;

import java.io.File;
import java.util.List;

public class SystemUtil {
    private static final String TAG = SystemUtil.class.getSimpleName();

    private static boolean loadLibrarySuccess = false;

    public static boolean isLoadLibrarySuccess() {
        return loadLibrarySuccess;
    }

    private static String currentProcessName = "";

    public static boolean loadIMLibrary() {
        if (loadLibrarySuccess) {
            return true;
        }
        try {
            System.loadLibrary("ImC++Demo");
            loadLibrarySuccess = true;
            Log.i(TAG, "system load so library success, ImC++Demo.so");
        } catch (UnsatisfiedLinkError e) {
            loadLibrarySuccess = false;
            Log.e(TAG, "system load so library failed, UnsatisfiedLinkError = " + e.getMessage());
        } catch (Exception e) {
            loadLibrarySuccess = false;
            Log.e(TAG, "system load so library failed, Exception = " + e.getMessage());
        }
        return loadLibrarySuccess;
    }

    public static String getSDKInitPath() {
        Context context = IMContext.getInstance().getApplicationContext();
        if (null == context) {
            return "";
        }

        String initPath = context.getFilesDir().toString();
        String mainProcessName = context.getPackageName();
        String currentProcessName = getCurrentProcessName(context);
        if (!TextUtils.isEmpty(currentProcessName) && !mainProcessName.equals(currentProcessName)) {
            try {
                String pathSuffix = currentProcessName;
                int index = currentProcessName.lastIndexOf(":");
                if (index < 0) {
                    index = currentProcessName.lastIndexOf(".");
                }

                if (index >= 0) {
                    pathSuffix = currentProcessName.substring(index + 1);
                }

                initPath += File.separator + pathSuffix + File.separator;
            } catch (Exception e) {
                Log.e(TAG, "getSDKInitPath exception = " + e);
            }
        }

        Log.d(TAG, "SDK Init Path: " + initPath);

        return initPath;
    }

    @SuppressLint("SdCardPath")
    public static String getSDKLogPath() {
        Context context = IMContext.getInstance().getApplicationContext();
        if (null == context) {
            return "";
        }

        // Android 10 系统开始使用分区存储，因此使用应用专有目录。
        String logPath = "";
        File filesDir = context.getExternalFilesDir(null);
        if (filesDir == null) {
            logPath = "/sdcard/Android/data/" + context.getPackageName() + "/log/tencent/imsdk";
        } else {
            logPath = filesDir.getAbsolutePath() + File.separator + "log" + File.separator + "tencent" + File.separator + "imsdk";
        }

        File file = new File(logPath);
        if (!file.exists()) {
            if (!file.mkdirs()) {
                file = context.getFilesDir();
                Log.e(TAG, "create log folder failed");
            }
        }

        logPath = file.getAbsolutePath() + File.separator;
        String mainProcessName = context.getPackageName();
        String currentProcessName = getCurrentProcessName(context);
        if (!TextUtils.isEmpty(currentProcessName) && !mainProcessName.equals(currentProcessName)) {
            try {
                String pathSuffix = currentProcessName;
                int index = currentProcessName.lastIndexOf(":");
                if (index < 0) {
                    index = currentProcessName.lastIndexOf(".");
                }

                if (index >= 0) {
                    pathSuffix = currentProcessName.substring(index + 1);
                }

                logPath += pathSuffix + File.separator;
            } catch (Exception e) {
                Log.e(TAG, "getSDKLogPath exception = " + e);
            }
        }

        Log.d(TAG, "SDK LOG Path: " + logPath);

        return logPath;
    }

    private static String getCurrentProcessName(Context context) {
        if (!TextUtils.isEmpty(currentProcessName)) {
            return currentProcessName;
        }

        ActivityManager am = ((ActivityManager) context.getSystemService(Context.ACTIVITY_SERVICE));
        int myPid = android.os.Process.myPid();

        List<ActivityManager.RunningAppProcessInfo> processInfos = am.getRunningAppProcesses();
        if (processInfos == null) {
            Log.d(TAG, "RunningAppProcesses is null");
            List<ActivityManager.RunningServiceInfo> processList = am.getRunningServices(Integer.MAX_VALUE);
            if (processList == null) {
                Log.d(TAG, "RunningServices is null");
                return null;
            }
            for (ActivityManager.RunningServiceInfo rsi : processList) {
                if (rsi.pid == myPid) {
                    currentProcessName = rsi.service.getPackageName();
                }
            }
            return currentProcessName;
        }

        for (ActivityManager.RunningAppProcessInfo info : processInfos) {
            if (info.pid == myPid) {
                currentProcessName = info.processName;
            }
        }
        return currentProcessName;
    }

}
