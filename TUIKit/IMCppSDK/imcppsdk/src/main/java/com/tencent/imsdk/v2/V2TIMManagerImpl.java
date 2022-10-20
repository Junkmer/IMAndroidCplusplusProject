package com.tencent.imsdk.v2;

import android.content.Context;
import android.text.TextUtils;

import com.tencent.imsdk.BaseConstants;
import com.tencent.imsdk.common.IMCallback;
import com.tencent.imsdk.common.IMContext;
import com.tencent.imsdk.common.IMLog;
import com.tencent.imsdk.common.SystemUtil;

import java.lang.reflect.Field;
import java.util.List;

public class V2TIMManagerImpl extends V2TIMManager {
    private final static String TAG = V2TIMManagerImpl.class.getSimpleName();

    private static class V2TIMManagerImplHolder {
        private static final V2TIMManagerImpl v2TIMManagerImpl = new V2TIMManagerImpl();
    }

    public static V2TIMManagerImpl getInstance() {
        return V2TIMManagerImplHolder.v2TIMManagerImpl;
    }

    protected V2TIMManagerImpl() {

    }

    @Override
    public boolean initSDK(Context context, int sdkAppID, V2TIMSDKConfig config) {
        if (!mLoadLibrarySuccess) {
            IMLog.e(TAG, "libimsdk.so is not loaded");
            return false;
        }

        if (sdkAppID <= 0) {
            IMLog.e(TAG, "invalid sdkAppID:" + sdkAppID);
            return false;
        }

        if (null == context) {
            IMLog.e(TAG, "null context");
            return false;
        }

        if (isInit) {
            IMLog.w(TAG, "Has initSDK");
            return true;
        }

        if (null == config) {
            config = new V2TIMSDKConfig();
        }

        IMContext.getInstance().init(context.getApplicationContext());

        getFieldByReflection(V2TIMSDKConfig.class,"sdkInitPath",config, SystemUtil.getSDKInitPath());
        getFieldByReflection(V2TIMSDKConfig.class,"sdkLogPath",config,SystemUtil.getSDKLogPath());

        isInit = nativeInitSDK(sdkAppID,config);

        //添加监听
        nativeInitCplusplusSDKListener();
        nativeInitCplusplusSimpleMsgListener();
        nativeInitCplusplusGroupListener();
        getConversationManager().nativeInitCplusplusConversationListener();
        getFriendshipManager().nativeInitCplusplusFriendListener();
        getMessageManager().nativeInitCplusplusAdvancedMsgListener();
        getSignalingManager().nativeInitCplusplusSignalingListener();
        IMLog.e(TAG,"init flag = "+isInit);
       return isInit;
    }

    @Override
    public void unInitSDK() {
        nativeUninitSDK();
        isInit = false;
    }

    @Override
    public void addIMSDKListener(V2TIMSDKListener listener) {
        nativeAddSDKListener(listener,listener.toString());
    }

    @Override
    public void removeIMSDKListener(V2TIMSDKListener listener) {
        nativeRemoveSDKListener(listener.toString());
    }

    @Override
    public String getVersion() {
        return nativeGetVersion();
    }

    @Override
    public long getServerTime() {
        return nativeGetServerTime();
    }

    @Override
    public void login(String userID, String userSig, V2TIMCallback _callback_) {
        if (!isInit){
            if (_callback_ != null){
                _callback_.onError(BaseConstants.ERR_SDK_NOT_INITIALIZED,"sdk not init");
            }
            return;
        }
        if (TextUtils.isEmpty(userID) || TextUtils.isEmpty(userSig)) {
            _callback_.onError(BaseConstants.ERR_INVALID_PARAMETERS, "userID or userSig is empty");
        }
        nativeLogin(userID, userSig, new IMCallback(_callback_) {
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
    public void logout(V2TIMCallback _callback_) {
        nativeLogout(new IMCallback(_callback_) {
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
    public String getLoginUser() {
        return nativeGetLoginUser();
    }

    @Override
    public int getLoginStatus() {
        return nativeGetLoginStatus();
    }

    @Override
    public void addSimpleMsgListener(V2TIMSimpleMsgListener v2TIMSimpleMsgListener) {
        nativeAddSimpleMsgListener(v2TIMSimpleMsgListener,v2TIMSimpleMsgListener.toString());
    }

    @Override
    public void removeSimpleMsgListener(V2TIMSimpleMsgListener v2TIMSimpleMsgListener) {
        nativeRemoveSimpleMsgListener(v2TIMSimpleMsgListener.toString());
    }

    @Override
    public String sendC2CTextMessage(String text, String userID, V2TIMValueCallback<V2TIMMessage> _callback_) {
        return nativeSendC2CTextMessage(text, userID, new IMCallback<V2TIMMessage>(_callback_) {
            @Override
            public void success(V2TIMMessage data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public String sendC2CCustomMessage(byte[] customData, String userID, V2TIMValueCallback<V2TIMMessage> _callback_) {
        return nativeSendC2CCustomMessage(customData, userID, new IMCallback<V2TIMMessage>(_callback_) {
            @Override
            public void success(V2TIMMessage data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public String sendGroupTextMessage(String text, String groupID, int priority, V2TIMValueCallback<V2TIMMessage> _callback_) {
        return nativeSendGroupTextMessage(text, groupID, priority, new IMCallback<V2TIMMessage>(_callback_) {
            @Override
            public void success(V2TIMMessage data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public String sendGroupCustomMessage(byte[] customData, String groupID, int priority, V2TIMValueCallback<V2TIMMessage> _callback_) {
        return nativeSendGroupCustomMessage(customData, groupID, priority, new IMCallback<V2TIMMessage>(_callback_) {
            @Override
            public void success(V2TIMMessage data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void addGroupListener(V2TIMGroupListener listener) {
        nativeAddGroupListener(listener,listener.toString());
    }

    @Override
    public void removeGroupListener(V2TIMGroupListener listener) {
        nativeRemoveGroupListener(listener.toString());
    }

    @Override
    public void createGroup(String groupType, String groupID, String groupName, V2TIMValueCallback<String> _callback_) {
        nativeCreateGroup(groupType, groupID, groupName, new IMCallback<String>(_callback_) {
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
    public void joinGroup(String groupID, String message, V2TIMCallback _callback_) {
        nativeJoinGroup(groupID, message, new IMCallback(_callback_) {
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
    public void quitGroup(String groupID, V2TIMCallback _callback_) {
        nativeQuitGroup(groupID, new IMCallback(_callback_) {
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
    public void dismissGroup(String groupID, V2TIMCallback _callback_) {
        nativeDismissGroup(groupID, new IMCallback(_callback_) {
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
    public void getUsersInfo(List<String> userIDList, V2TIMValueCallback<List<V2TIMUserFullInfo>> _callback_) {
        nativeGetUsersInfo(userIDList, new IMCallback<List<V2TIMUserFullInfo>>(_callback_) {
            @Override
            public void success(List<V2TIMUserFullInfo> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setSelfInfo(V2TIMUserFullInfo info, V2TIMCallback _callback_) {
        nativeSetSelfInfo(info, new IMCallback(_callback_) {
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
    public void getUserStatus(List<String> userIDList, V2TIMValueCallback<List<V2TIMUserStatus>> _callback_) {
        nativeGetUserStatus(userIDList, new IMCallback<List<V2TIMUserStatus>>(_callback_) {
            @Override
            public void success(List<V2TIMUserStatus> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setSelfStatus(V2TIMUserStatus status, V2TIMCallback _callback_) {
        nativeSetSelfStatus(status, new IMCallback(_callback_) {
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
    public void subscribeUserStatus(List<String> userIDList, V2TIMCallback _callback_) {
        nativeSubscribeUserStatus(userIDList, new IMCallback(_callback_) {
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
    public void unsubscribeUserStatus(List<String> userIDList, V2TIMCallback _callback_) {
        nativeUnsubscribeUserStatus(userIDList, new IMCallback(_callback_) {
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
    public void callExperimentalAPI(String api, Object param, V2TIMValueCallback<Object> _callback_) {
        nativeCallExperimentalAPI(api, param, new IMCallback<Object>(_callback_) {
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

    private static void getFieldByReflection(final Class<?> clazz, final String fieldName, Object obj, Object value){
        try {
            Field path = clazz.getDeclaredField(fieldName);
            path.setAccessible(true);//启用私有变量可赋值权限
            path.set(obj,value);
        } catch (NoSuchFieldException|IllegalAccessException e) {
            e.printStackTrace();
        }
    }

//--------------------------------------------------  set c++ 层监听

//    @Override
//    protected void nativeSetCplusplusSDKListener() {
//        super.nativeSetCplusplusSDKListener();
//    }
//
//    @Override
//    protected void nativeSetCplusplusSimpleMsgListener() {
//        super.nativeSetCplusplusSimpleMsgListener();
//    }
//
//    @Override
//    protected void nativeSetCplusplusGroupListener() {
//        super.nativeSetCplusplusGroupListener();
//    }
}
