package com.tencent.imsdk.common;

import android.content.Context;
import android.os.Handler;
import android.os.Looper;

public class IMContext {
    private static final String TAG = IMContext.class.getSimpleName();

    private Context mContext;

    private Handler mMainHandler = new Handler(Looper.getMainLooper());

    private static class Holder {
        public static IMContext instance = new IMContext();
    }

    public static IMContext getInstance() {
        return Holder.instance;
    }

    private IMContext() {

    }

    public void init(Context context) {
        mContext = context;
    }

    public Context getApplicationContext() {
        return mContext;
    }

    public void runOnMainThread(Runnable runnable) {
        mMainHandler.post(runnable);
    }
}
