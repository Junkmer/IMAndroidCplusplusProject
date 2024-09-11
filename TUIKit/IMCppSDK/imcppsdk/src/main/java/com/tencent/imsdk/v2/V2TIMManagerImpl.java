package com.tencent.imsdk.v2;

import android.content.Context;
import android.text.TextUtils;

import com.tencent.imsdk.BaseConstants;
import com.tencent.imsdk.common.IMCallback;
import com.tencent.imsdk.common.IMContext;
import com.tencent.imsdk.common.IMLog;
import com.tencent.imsdk.common.SystemUtil;

import org.json.JSONException;
import org.json.JSONObject;

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
    public void subscribeUserInfo(List<String> userIDList, V2TIMCallback _callback_) {
        nativeSubscribeUserInfo(userIDList, new IMCallback(_callback_) {
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
    public void unsubscribeUserInfo(List<String> userIDList, V2TIMCallback _callback_) {
        nativeUnsubscribeUserInfo(userIDList, new IMCallback(_callback_) {
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
        if (TextUtils.isEmpty(api)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "invalid api");
            return;
        }

        if (api.equals("setCustomServerInfo")) {
            setCustomServerInfo(api,param, _callback_);
        } else if (api.equals("setQuicChannelInfo")) {
            setQuicChannelInfo(api, param, _callback_);
        } else if (api.equals("setProxyInfo")) {
            setProxyInfo(api, param, _callback_);
        } else if (api.equals("initLocalStorage")) {
            initLocalStorage(api, param, _callback_);
        } else if (api.equals("setTestEnvironment")) {
            setTestEnvironment(api, param, _callback_);
        } else if (api.equals("setIPv6Prior")) {
            setIPv6Prior(api, param, _callback_);
        } else if (api.equals("setCosSaveRegionForConversation")) {
            setCosSaveRegion(api, param, _callback_);
        } else if (api.equals("setUIPlatform")) {
            setUIPlatform(api, param, _callback_);
        } else if (api.equals("setBuildInfo")) {
            setBuildInfo(param, _callback_);
        } else if (api.equals("setDatabaseEncryptInfo")) {
            setDatabaseEncryptInfo(api, param, _callback_);
        } else if (api.equals("isCommercialAbilityEnabled")) {
            isCommercialAbilityEnabled(api, param, _callback_);
        } else if (api.equals("setPacketRetryInfo")) {
            setPacketRetryInfo(api, param, _callback_);
        } else if (api.equals("setOfflinePushState")) {
            setOfflinePushState(api, param, _callback_);
        } else if (api.equals("getOfflinePushState")) {
            getOfflinePushState(api,_callback_);
        } else if (api.equals("getMessageRevoker")) {
            getMessageRevoker(api, param, _callback_);
        } else if (api.equals("writeLog")) {
            writeLog(api, param, _callback_);
        } else if (api.equals("sendTRTCCustomData")) {
            sendTRTCCustomData(api, param, _callback_);
        } else if (api.equals("clearLocalHistoryMessage")) {
            clearLocalHistoryMessage(api, param, _callback_);
        } else if (api.equals("reportTUIComponentUsage")) {
            reportTUIComponentUsage(api, param, _callback_);
        } else if (api.equals("setApplicationID")) {
            setApplicationID(api, param, _callback_);
        } else {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "unsupported api");
        }
    }

    private void setCustomServerInfo(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof String)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not string");
            return;
        }

        String json = (String) param;
        if (TextUtils.isEmpty(json)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is empty");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void setQuicChannelInfo(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof String)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not string");
            return;
        }

        String json = (String) param;
        if (TextUtils.isEmpty(json)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is empty");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void setProxyInfo(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
//        if (null == param || !(param instanceof String)) {
//            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not string");
//            return;
//        }
//
//        String json = (String) param;
//        if (TextUtils.isEmpty(json)) {
//            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is empty");
//            return;
//        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void initLocalStorage(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (!(param instanceof String)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not string");
            return;
        }

        String userID = (String) param;
        if (TextUtils.isEmpty(userID)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "invalid userID");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void setTestEnvironment(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (param != null && param instanceof Boolean) {
            nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void setIPv6Prior(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (param != null && param instanceof Boolean) {
            nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void setCosSaveRegion(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof String)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not string");
            return;
        }

        String json = (String) param;
        if (TextUtils.isEmpty(json)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is empty");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void setUIPlatform(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (null == param) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is null");
            return;
        }

        int numberUIPlatform = 0;
        if (param instanceof Integer) {
            numberUIPlatform = (Integer) param;
        } else {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is invalid");
        }

        nativeCallExperimentalAPI(apiTitle, numberUIPlatform, new IMCallback<Object>(_callback_) {
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

    private void setBuildInfo(Object param, V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof String)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not string");
            return;
        }

        String json = (String) param;
        if (TextUtils.isEmpty(json)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is empty");
            return;
        }

        try {
            JSONObject jsonObject = new JSONObject(json);
            String buildBrand = jsonObject.optString("buildBrand");
            String buildManufacturer = jsonObject.optString("buildManufacturer");
            String buildModel = jsonObject.optString("buildModel");
            String buildVersionRelease = jsonObject.optString("buildVersionRelease");
            int buildVersionSDKInt = jsonObject.optInt("buildVersionSDKInt");

            SystemUtil.setBuildBrand(buildBrand);
            SystemUtil.setBuildManufacturer(buildManufacturer);
            SystemUtil.setBuildModel(buildModel);
            SystemUtil.setBuildVersionRelease(buildVersionRelease);
            SystemUtil.setBuildVersionSDKInt(buildVersionSDKInt);

            callbackOnSuccess(_callback_, null);
        } catch (JSONException e) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "convert param to json failed");
            e.printStackTrace();
        }
    }

    private void setDatabaseEncryptInfo(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof String)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not string");
            return;
        }

        String json = (String) param;
        if (TextUtils.isEmpty(json)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is empty");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void isCommercialAbilityEnabled(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof Long)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not int");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void setPacketRetryInfo(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof String)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not string");
            return;
        }

        String json = (String) param;
        if (TextUtils.isEmpty(json)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is empty");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, null, new IMCallback<Object>(_callback_) {
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

    private void setOfflinePushState(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof Integer)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not int");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, null, new IMCallback<Object>(_callback_) {
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

    private void getOfflinePushState(String apiTitle,V2TIMValueCallback<Object> valueCallback) {
        nativeCallExperimentalAPI(apiTitle, null, new IMCallback<Object>(valueCallback) {
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

    private void getMessageRevoker(String apiTitle , Object param, final V2TIMValueCallback<Object> _callback_) {
        if (!(param instanceof List)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not list");
            return;
        }
        List messageIDList = (List) param;
        for (Object messageID : messageIDList) {
            if (!(messageID instanceof String)) {
                callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "item is no String type");
                return;
            }
            break;
        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void writeLog(String apiTitle , Object param, final V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof String)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not string");
            return;
        }

        String json = (String) param;
        if (TextUtils.isEmpty(json)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is empty");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void sendTRTCCustomData(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof byte[])) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not byte array");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void clearLocalHistoryMessage(String apiTitle , Object param, final V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof String)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not string");
            return;
        }

        String json = (String) param;
        if (TextUtils.isEmpty(json)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is empty");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void reportTUIComponentUsage(String apiTitle , Object param, final V2TIMValueCallback<Object> _callback_) {
        if (null == param || !(param instanceof String)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is not string");
            return;
        }

        String json = (String) param;
        if (TextUtils.isEmpty(json)) {
            callbackOnError(_callback_, BaseConstants.ERR_INVALID_PARAMETERS, "param is empty");
            return;
        }

        nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void setApplicationID(String apiTitle , Object param, V2TIMValueCallback<Object> _callback_) {
        if (param != null && param instanceof Integer) {
            nativeCallExperimentalAPI(apiTitle, param, new IMCallback<Object>(_callback_) {
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

    private void callbackOnSuccess(V2TIMValueCallback<Object> callback, Object result) {
        if (callback != null) {
            callback.onSuccess(result);
        }
    }

    private void callbackOnError(V2TIMValueCallback<Object> callback, int code, String desc) {
        if (callback != null) {
            callback.onError(code, desc);
        }
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
}
