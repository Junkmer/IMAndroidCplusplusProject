package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.IMCallback;

import java.util.List;

public class V2TIMSignalingManagerImpl extends V2TIMSignalingManager {

    private static class V2TIMSignalingManagerImplHolder {
        private static final V2TIMSignalingManagerImpl v2TIMSignalingManager = new V2TIMSignalingManagerImpl();
    }

    static V2TIMSignalingManagerImpl getInstance() {
        return V2TIMSignalingManagerImplHolder.v2TIMSignalingManager;
    }

    @Override
    public void addSignalingListener(V2TIMSignalingListener listener) {
        nativeAddSignalingListener(listener,listener.toString());
    }

    @Override
    public void removeSignalingListener(V2TIMSignalingListener listener) {
        nativeRemoveSignalingListener(listener.toString());
    }

    @Override
    public  String invite(String invitee, String data, boolean onlineUserOnly, V2TIMOfflinePushInfo offlinePushInfo, int timeout, V2TIMCallback _callback_) {
        return nativeInvite(invitee, data, onlineUserOnly, offlinePushInfo, timeout, new IMCallback(_callback_) {
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
    public  String inviteInGroup(String groupID, List<String> inviteeList, String data, boolean onlineUserOnly, int timeout, V2TIMCallback _callback_) {
        return nativeInviteInGroup(groupID, inviteeList, data, onlineUserOnly, timeout, new IMCallback(_callback_) {
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
    public void cancel(String inviteID, String data, V2TIMCallback _callback_) {
        nativeCancel(inviteID, data, new IMCallback(_callback_) {
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
    public void accept(String inviteID, String data, V2TIMCallback _callback_) {
        nativeAccept(inviteID, data, new IMCallback(_callback_) {
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
    public void reject(String inviteID, String data, V2TIMCallback _callback_) {
        nativeReject(inviteID, data, new IMCallback(_callback_) {
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
    public V2TIMSignalingInfo getSignalingInfo(V2TIMMessage msg) {
        return nativeGetSignalingInfo(msg);
    }

    @Override
    public void addInvitedSignaling(V2TIMSignalingInfo info, V2TIMCallback _callback_) {
        nativeAddInvitedSignaling(info, new IMCallback(_callback_) {
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
    public void modifyInvitation(String inviteID, String data, V2TIMCallback _callback_) {
        nativeModifyInvitation(inviteID, data, new IMCallback(_callback_) {
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
