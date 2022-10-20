package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.IMCallback;

import java.util.List;

public class V2TIMFriendshipManagerImpl extends V2TIMFriendshipManager {

    private static class V2TIMFriendshipManagerImplHolder {
        private static final V2TIMFriendshipManagerImpl v2TIMFriendshipManager = new V2TIMFriendshipManagerImpl();
    }

    static V2TIMFriendshipManagerImpl getInstance() {
        return V2TIMFriendshipManagerImplHolder.v2TIMFriendshipManager;
    }

    @Override
    public void addFriendListener(V2TIMFriendshipListener listener) {
        nativeAddFriendListener(listener,listener.toString());
    }

    @Override
    public void removeFriendListener(V2TIMFriendshipListener listener) {
        nativeRemoveFriendListener(listener.toString());
    }

    @Override
    public void getFriendList(V2TIMValueCallback<List<V2TIMFriendInfo>> _callback_) {
        nativeGetFriendList(new IMCallback<List<V2TIMFriendInfo>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendInfo> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getFriendsInfo(List<String> userIDList, V2TIMValueCallback<List<V2TIMFriendInfoResult>> _callback_) {
        nativeGetFriendsInfo(userIDList, new IMCallback<List<V2TIMFriendInfoResult>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendInfoResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setFriendInfo(V2TIMFriendInfo info, V2TIMCallback _callback_) {
        nativeSetFriendInfo(info, new IMCallback(_callback_) {
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
    public void searchFriends(V2TIMFriendSearchParam searchParam, V2TIMValueCallback<List<V2TIMFriendInfoResult>> _callback_) {
        nativeSearchFriends(searchParam, new IMCallback<List<V2TIMFriendInfoResult>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendInfoResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void addFriend(V2TIMFriendAddApplication application, V2TIMValueCallback<V2TIMFriendOperationResult> _callback_) {
        nativeAddFriend(application, new IMCallback<V2TIMFriendOperationResult>(_callback_) {
            @Override
            public void success(V2TIMFriendOperationResult data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void deleteFromFriendList(List<String> userIDList, int deleteType, V2TIMValueCallback<List<V2TIMFriendOperationResult>> _callback_) {
        nativeDeleteFromFriendList(userIDList, deleteType, new IMCallback<List<V2TIMFriendOperationResult>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendOperationResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void checkFriend(List<String> userIDList, int checkType, V2TIMValueCallback<List<V2TIMFriendCheckResult>> _callback_) {
        nativeCheckFriend(userIDList, checkType, new IMCallback<List<V2TIMFriendCheckResult>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendCheckResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getFriendApplicationList(V2TIMValueCallback<V2TIMFriendApplicationResult> _callback_) {
        nativeGetFriendApplicationList(new IMCallback<V2TIMFriendApplicationResult>(_callback_) {
            @Override
            public void success(V2TIMFriendApplicationResult data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void acceptFriendApplication(V2TIMFriendApplication application, int responseType, V2TIMValueCallback<V2TIMFriendOperationResult> _callback_) {
        nativeAcceptFriendApplication(application, responseType, new IMCallback<V2TIMFriendOperationResult>(_callback_) {
            @Override
            public void success(V2TIMFriendOperationResult data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void refuseFriendApplication(V2TIMFriendApplication application, V2TIMValueCallback<V2TIMFriendOperationResult> _callback_) {
        nativeRefuseFriendApplication(application, new IMCallback<V2TIMFriendOperationResult>(_callback_) {
            @Override
            public void success(V2TIMFriendOperationResult data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void deleteFriendApplication(V2TIMFriendApplication application, V2TIMCallback _callback_) {
        nativeDeleteFriendApplication(application, new IMCallback(_callback_) {
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
    public void setFriendApplicationRead(V2TIMCallback _callback_) {
        nativesSetFriendApplicationRead(new IMCallback(_callback_) {
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
    public void addToBlackList(List<String> userIDList, V2TIMValueCallback<List<V2TIMFriendOperationResult>> _callback_) {
        nativeAddToBlackList(userIDList, new IMCallback<List<V2TIMFriendOperationResult>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendOperationResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void deleteFromBlackList(List<String> userIDList, V2TIMValueCallback<List<V2TIMFriendOperationResult>> _callback_) {
        nativeDeleteFromBlackList(userIDList, new IMCallback<List<V2TIMFriendOperationResult>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendOperationResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getBlackList(V2TIMValueCallback<List<V2TIMFriendInfo>> _callback_) {
        nativeGetBlackList(new IMCallback<List<V2TIMFriendInfo>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendInfo> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void createFriendGroup(String groupName, List<String> userIDList, V2TIMValueCallback<List<V2TIMFriendOperationResult>> _callback_) {
        nativeCreateFriendGroup(groupName, userIDList, new IMCallback<List<V2TIMFriendOperationResult>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendOperationResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getFriendGroups(List<String> groupNameList, V2TIMValueCallback<List<V2TIMFriendGroup>> _callback_) {
        nativeGetFriendGroups(groupNameList, new IMCallback<List<V2TIMFriendGroup>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendGroup> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void deleteFriendGroup(List<String> groupNameList, V2TIMCallback _callback_) {
        nativeDeleteFriendGroup(groupNameList, new IMCallback(_callback_) {
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
    public void renameFriendGroup(String oldName, String newName, V2TIMCallback _callback_) {
        nativeRenameFriendGroup(oldName, newName, new IMCallback(_callback_) {
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
    public void addFriendsToFriendGroup(String groupName, List<String> userIDList, V2TIMValueCallback<List<V2TIMFriendOperationResult>> _callback_) {
        nativeAddFriendsToFriendGroup(groupName, userIDList, new IMCallback<List<V2TIMFriendOperationResult>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendOperationResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void deleteFriendsFromFriendGroup(String groupName, List<String> userIDList, V2TIMValueCallback<List<V2TIMFriendOperationResult>> _callback_) {
        nativeDeleteFriendsFromFriendGroup(groupName, userIDList, new IMCallback<List<V2TIMFriendOperationResult>>(_callback_) {
            @Override
            public void success(List<V2TIMFriendOperationResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }
}
