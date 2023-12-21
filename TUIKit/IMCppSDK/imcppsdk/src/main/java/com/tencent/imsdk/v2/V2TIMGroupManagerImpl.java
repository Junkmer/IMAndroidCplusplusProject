package com.tencent.imsdk.v2;

import com.tencent.imsdk.common.IMCallback;

import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class V2TIMGroupManagerImpl extends V2TIMGroupManager {

    private static class V2TIMGroupManagerImplHolder {
        private static final V2TIMGroupManagerImpl v2TIMGroupManager = new V2TIMGroupManagerImpl();
    }

    static V2TIMGroupManagerImpl getInstance() {
        return V2TIMGroupManagerImplHolder.v2TIMGroupManager;
    }
    
    @Override
    public void createGroup(V2TIMGroupInfo info, List<V2TIMCreateGroupMemberInfo> memberList, V2TIMValueCallback<String> _callback_) {
        nativeCreateGroup(info, memberList, new IMCallback<String>(_callback_) {
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
    public void getJoinedGroupList(V2TIMValueCallback<List<V2TIMGroupInfo>> _callback_) {
        nativeGetJoinedGroupList(new IMCallback<List<V2TIMGroupInfo>>(_callback_) {
            @Override
            public void success(List<V2TIMGroupInfo> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getGroupsInfo(List<String> groupIDList, V2TIMValueCallback<List<V2TIMGroupInfoResult>> _callback_) {
        nativeGetGroupsInfo(groupIDList, new IMCallback<List<V2TIMGroupInfoResult>>(_callback_) {
            @Override
            public void success(List<V2TIMGroupInfoResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void searchGroups(V2TIMGroupSearchParam searchParam, V2TIMValueCallback<List<V2TIMGroupInfo>> _callback_) {
        nativeSearchGroups(searchParam, new IMCallback<List<V2TIMGroupInfo>>(_callback_) {
            @Override
            public void success(List<V2TIMGroupInfo> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setGroupInfo(V2TIMGroupInfo info, V2TIMCallback _callback_) {
        nativeSetGroupInfo(info, new IMCallback(_callback_) {
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
    public void initGroupAttributes(String groupID, HashMap<String, String> attributes, V2TIMCallback _callback_) {
        nativeInitGroupAttributes(groupID, attributes, new IMCallback(_callback_) {
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
    public void setGroupAttributes(String groupID, HashMap<String, String> attributes, V2TIMCallback _callback_) {
        nativeSetGroupAttributes(groupID, attributes, new IMCallback(_callback_) {
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
    public void deleteGroupAttributes(String groupID, List<String> keys, V2TIMCallback _callback_) {
        nativeDeleteGroupAttributes(groupID, keys, new IMCallback(_callback_) {
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
    public void getGroupAttributes(String groupID, List<String> keys, V2TIMValueCallback<Map<String, String>> _callback_) {
        nativeGetGroupAttributes(groupID, keys, new IMCallback<Map<String, String>>(_callback_) {
            @Override
            public void success(Map<String, String> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getGroupOnlineMemberCount(String groupID, V2TIMValueCallback<Integer> _callback_) {
        nativeGetGroupOnlineMemberCount(groupID, new IMCallback<Integer>(_callback_) {
            @Override
            public void success(Integer data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setGroupCounters(String groupID, HashMap<String, Long> counters, V2TIMValueCallback<Map<String, Long>> _callback_) {
        nativeSetGroupCounters(groupID, counters, new IMCallback<Map<String, Long>>(_callback_) {
            @Override
            public void success(Map<String, Long> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getGroupCounters(String groupID, List<String> keys, V2TIMValueCallback<Map<String, Long>> _callback_) {
        nativeGetGroupCounters(groupID, keys, new IMCallback<Map<String, Long>>(_callback_) {
            @Override
            public void success(Map<String, Long> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void increaseGroupCounter(String groupID, String key, long value, V2TIMValueCallback<Map<String, Long>> _callback_) {
        nativeIncreaseGroupCounter(groupID, key, value, new IMCallback<Map<String, Long>>(_callback_) {
            @Override
            public void success(Map<String, Long> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void decreaseGroupCounter(String groupID, String key, long value, V2TIMValueCallback<Map<String, Long>> _callback_) {
        nativeDecreaseGroupCounter(groupID, key, value, new IMCallback<Map<String, Long>>(_callback_) {
            @Override
            public void success(Map<String, Long> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getGroupMemberList(String groupID, int filter, long nextSeq, V2TIMValueCallback<V2TIMGroupMemberInfoResult> _callback_) {
        nativeGetGroupMemberList(groupID, filter, nextSeq, new IMCallback<V2TIMGroupMemberInfoResult>(_callback_) {
            @Override
            public void success(V2TIMGroupMemberInfoResult data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void getGroupMembersInfo(String groupID, List<String> memberList, V2TIMValueCallback<List<V2TIMGroupMemberFullInfo>> _callback_) {
        nativeGetGroupMembersInfo(groupID, memberList, new IMCallback<List<V2TIMGroupMemberFullInfo>>(_callback_) {
            @Override
            public void success(List<V2TIMGroupMemberFullInfo> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void searchGroupMembers(V2TIMGroupMemberSearchParam param, V2TIMValueCallback<HashMap<String, List<V2TIMGroupMemberFullInfo>>> _callback_) {
        nativeSearchGroupMembers(param, new IMCallback<HashMap<String, List<V2TIMGroupMemberFullInfo>>>(_callback_) {
            @Override
            public void success(HashMap<String, List<V2TIMGroupMemberFullInfo>> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setGroupMemberInfo(String groupID, V2TIMGroupMemberFullInfo info, V2TIMCallback _callback_) {
        nativeSetGroupMemberInfo(groupID, info, new IMCallback(_callback_) {
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
    public void muteGroupMember(String groupID, String userID, int seconds, V2TIMCallback _callback_) {
        nativeMuteGroupMember(groupID, userID, seconds, new IMCallback(_callback_) {
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
    public void muteAllGroupMembers(String groupID, boolean isMute, V2TIMCallback _callback_) {
        nativeMuteAllGroupMembers(groupID, isMute, new IMCallback(_callback_) {
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
    public void inviteUserToGroup(String groupID, List<String> userList, V2TIMValueCallback<List<V2TIMGroupMemberOperationResult>> _callback_) {
        nativeInviteUserToGroup(groupID, userList, new IMCallback<List<V2TIMGroupMemberOperationResult>>(_callback_) {
            @Override
            public void success(List<V2TIMGroupMemberOperationResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void kickGroupMember(String groupID, List<String> memberList, String reason, V2TIMValueCallback<List<V2TIMGroupMemberOperationResult>> _callback_) {
        nativeKickGroupMember(groupID, memberList, reason, new IMCallback<List<V2TIMGroupMemberOperationResult>>(_callback_) {
            @Override
            public void success(List<V2TIMGroupMemberOperationResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setGroupMemberRole(String groupID, String userID, int role, V2TIMCallback _callback_) {
        nativeSetGroupMemberRole(groupID, userID, role, new IMCallback(_callback_) {
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
    public void markGroupMemberList(String groupID, List<String> memberIDList, int markType, boolean enableMark, V2TIMCallback _callback_) {
        nativeMarkGroupMemberList(groupID, memberIDList, markType, enableMark, new IMCallback(_callback_) {
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
    public void transferGroupOwner(String groupID, String userID, V2TIMCallback _callback_) {
        nativeTransferGroupOwner(groupID, userID, new IMCallback(_callback_) {
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
    public void getGroupApplicationList(V2TIMValueCallback<V2TIMGroupApplicationResult> _callback_) {
        nativeGetGroupApplicationList(new IMCallback<V2TIMGroupApplicationResult>(_callback_) {
            @Override
            public void success(V2TIMGroupApplicationResult data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void acceptGroupApplication(V2TIMGroupApplication application, String reason, V2TIMCallback _callback_) {
        nativeAcceptGroupApplication(application, reason, new IMCallback(_callback_) {
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
    public void refuseGroupApplication(V2TIMGroupApplication application, String reason, V2TIMCallback _callback_) {
        nativeRefuseGroupApplication(application, reason, new IMCallback(_callback_) {
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
    public void setGroupApplicationRead(V2TIMCallback _callback_) {
        nativeSetGroupApplicationRead(new IMCallback(_callback_) {
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
    public void getJoinedCommunityList(V2TIMValueCallback<List<V2TIMGroupInfo>> _callback_) {
        nativeGetJoinedCommunityList(new IMCallback<List<V2TIMGroupInfo>>(_callback_) {
            @Override
            public void success(List<V2TIMGroupInfo> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void createTopicInCommunity(String groupID, V2TIMTopicInfo topicInfo, V2TIMValueCallback<String> _callback_) {
        nativeCreateTopicInCommunity(groupID, topicInfo, new IMCallback<String>(_callback_) {
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
    public void deleteTopicFromCommunity(String groupID, List<String> topicIDList, V2TIMValueCallback<List<V2TIMTopicOperationResult>> _callback_) {
        nativeDeleteTopicFromCommunity(groupID, topicIDList, new IMCallback<List<V2TIMTopicOperationResult>>(_callback_) {
            @Override
            public void success(List<V2TIMTopicOperationResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }

    @Override
    public void setTopicInfo(V2TIMTopicInfo topicInfo, V2TIMCallback _callback_) {
        nativeSetTopicInfo(topicInfo, new IMCallback(_callback_) {
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
    public void getTopicInfoList(String groupID, List<String> topicIDList, V2TIMValueCallback<List<V2TIMTopicInfoResult>> _callback_) {
        nativeGetTopicInfoList(groupID, topicIDList, new IMCallback<List<V2TIMTopicInfoResult>>(_callback_) {
            @Override
            public void success(List<V2TIMTopicInfoResult> data) {
                super.success(data);
            }

            @Override
            public void fail(int code, String errorMessage) {
                super.fail(code, errorMessage);
            }
        });
    }
}
