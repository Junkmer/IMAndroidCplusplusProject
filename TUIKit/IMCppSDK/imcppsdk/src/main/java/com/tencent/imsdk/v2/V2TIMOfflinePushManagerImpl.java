package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.IMCallback;

public class V2TIMOfflinePushManagerImpl extends V2TIMOfflinePushManager {

    private static class V2TIMOfflinePushManagerImplHolder {
        private static final V2TIMOfflinePushManagerImpl v2TIMOfflinePushManager = new V2TIMOfflinePushManagerImpl();
    }

    static V2TIMOfflinePushManagerImpl getInstance() {
        return V2TIMOfflinePushManagerImplHolder.v2TIMOfflinePushManager;
    }
    
    @Override
    public void setOfflinePushConfig(V2TIMOfflinePushConfig config, V2TIMCallback _callback_) {
        nativeSetOfflinePushConfig(config, new IMCallback(_callback_) {
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

    @Override
    public void doBackground(int unreadCount, V2TIMCallback _callback_) {
        nativeDoBackground(unreadCount, new IMCallback(_callback_) {
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

    @Override
    public void doForeground(V2TIMCallback _callback_) {
        nativeDoForeground(new IMCallback(_callback_) {
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
}
