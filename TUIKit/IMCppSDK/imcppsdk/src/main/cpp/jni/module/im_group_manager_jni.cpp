//
// Created by EDY on 2022/8/22.
//

#include <jni.h>
#include <LogUtil.h>
#include "jni_util.h"
#include "java_basic_jni.h"
#include "v2_im_engine.h"
#include "jni_helper.h"
#include "callback_impl.h"
#include "value_callback_impl.h"
#include "V2TIMErrorCode.h"
#include "im_callbak_jni.h"
#include "group_topic_info_jni.h"
#include "group_member_info_jni.h"
#include "group_info_jni.h"
#include "group_application_jni.h"
#include "group_member_change_info_jni.h"
#include "group_member_full_info_jni.h"
#include "group_info_result_jni.h"
#include "group_member_info_result_jni.h"
#include "group_application_result_jni.h"
#include "group_member_operation_result_jni.h"
#include "group_member_search_param_jni.h"
#include "create_group_member_info_jni.h"
#include "group_search_param.h"
#include "topic_operation_result_jni.h"
#include "topic_info_result_jni.h"

#define DEFINE_NATIVE_FUNC(RETURN_TYPE, NAME, ...) \
    RETURN_TYPE NAME(JNIEnv *env, jobject thiz, ##__VA_ARGS__)

#ifdef __cplusplus
extern "C" {
#endif

DEFINE_NATIVE_FUNC(void, NativeCreateGroupToParame, jobject info, jobject member_list, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMGroupInfo groupInfo;
    v2im::jni::GroupInfoJni::Convert2CoreObject(info, groupInfo);

    V2TIMCreateGroupMemberInfoVector memberList;
    int size = v2im::jni::ArrayListJni::Size(member_list);
    for (int i = 0; i < size; ++i) {
        V2TIMCreateGroupMemberInfo memberInfo;
        jobject j_obj_member = v2im::jni::ArrayListJni::Get(member_list,i);
        bool flag = v2im::jni::CreateGroupMemberInfoJni::Convert2CoreObject(j_obj_member, memberInfo);
        if (flag) {
            memberList.PushBack(memberInfo);
        }
        env->DeleteLocalRef(j_obj_member);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMString>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMString &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jstring groupID = v2im::jni::StringJni::Cstring2Jstring(env, value.CString());
            v2im::jni::IMCallbackJNI::Success(jni_callback, groupID);
            _env->DeleteLocalRef(groupID);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->CreateGroup(groupInfo, memberList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetJoinedGroupList, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupInfoVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupInfoVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject joinedGroupList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject groupInfoObj = v2im::jni::GroupInfoJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(joinedGroupList, groupInfoObj);
                _env->DeleteLocalRef(groupInfoObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, joinedGroupList);
            _env->DeleteLocalRef(joinedGroupList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetJoinedGroupList(value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetGroupsInfo, jobject group_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMStringVector groupIDList;
    int size = v2im::jni::ArrayListJni::Size(group_idlist);
    for (int i = 0; i < size; ++i) {
        V2TIMString groupID = v2im::jni::StringJni::Jstring2Cstring(env, (jstring) v2im::jni::ArrayListJni::Get(group_idlist, i)).c_str();
        groupIDList.PushBack(groupID);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupInfoResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupInfoResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject groupInfoResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject groupInfoResultObj = v2im::jni::GroupInfoResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(groupInfoResultList, groupInfoResultObj);
                _env->DeleteLocalRef(groupInfoResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, groupInfoResultList);
            _env->DeleteLocalRef(groupInfoResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetGroupsInfo(groupIDList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSearchGroups, jobject search_param, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMGroupSearchParam searchParam;
    v2im::jni::GroupSearchParam::Convert2CoreObject(search_param, searchParam);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupInfoVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupInfoVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject joinedGroupList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject groupInfoObj = v2im::jni::GroupInfoJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(joinedGroupList, groupInfoObj);
                _env->DeleteLocalRef(groupInfoObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, joinedGroupList);
            _env->DeleteLocalRef(joinedGroupList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->SearchGroups(searchParam, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSetGroupInfo, jobject info, jobject callback) {

    V2TIMGroupInfo groupInfo;
    v2im::jni::GroupInfoJni::Convert2CoreObject(info, groupInfo);

    v2im::V2IMEngine::GetInstance()->SetGroupInfo(groupInfo, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeInitGroupAttributes, jstring group_id, jobject attributes, jobject callback) {

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMGroupAttributeMap attributeMap;
    jobject entry_set = v2im::jni::HashMapJni::entrySet(attributes);
    jobject iterator = v2im::jni::HashMapJni::iterator(entry_set);
    while (v2im::jni::HashMapJni::hasNext(iterator)) {
        jobject object = v2im::jni::HashMapJni::next(iterator);
        if (nullptr == object) {
            continue;
        }
        auto jStr_key = (jstring) v2im::jni::HashMapJni::getKey(object);
        if (nullptr != jStr_key) {
            auto jByte_value = (jstring) v2im::jni::HashMapJni::getValue(object);
            V2TIMString c_key_str = v2im::jni::StringJni::Jstring2Cstring(env, jStr_key).c_str();
            V2TIMString c_value_str = v2im::jni::StringJni::Jstring2Cstring(env, jByte_value).c_str();
            attributeMap.Insert(c_key_str, c_value_str);

            env->DeleteLocalRef(jByte_value);
            env->DeleteLocalRef(jStr_key);
        }
    }

    v2im::V2IMEngine::GetInstance()->InitGroupAttributes(groupID_c, attributeMap, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeSetGroupAttributes, jstring group_id, jobject attributes, jobject callback) {

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMGroupAttributeMap attributeMap;
    jobject entry_set = v2im::jni::HashMapJni::entrySet(attributes);
    jobject iterator = v2im::jni::HashMapJni::iterator(entry_set);
    while (v2im::jni::HashMapJni::hasNext(iterator)) {
        jobject object = v2im::jni::HashMapJni::next(iterator);
        if (nullptr == object) {
            continue;
        }
        auto jStr_key = (jstring) v2im::jni::HashMapJni::getKey(object);
        if (nullptr != jStr_key) {
            auto jByte_value = (jstring) v2im::jni::HashMapJni::getValue(object);
            V2TIMString c_key_str = v2im::jni::StringJni::Jstring2Cstring(env, jStr_key).c_str();
            V2TIMString c_value_str = v2im::jni::StringJni::Jstring2Cstring(env, jByte_value).c_str();
            attributeMap.Insert(c_key_str, c_value_str);

            env->DeleteLocalRef(jByte_value);
            env->DeleteLocalRef(jStr_key);
        }
    }

    v2im::V2IMEngine::GetInstance()->SetGroupAttributes(groupID_c, attributeMap, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeDeleteGroupAttributes, jstring group_id, jobject keys, jobject callback) {

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMStringVector keyList;
    int size = v2im::jni::ArrayListJni::Size(keys);
    for (int i = 0; i < size; ++i) {
        V2TIMString groupID = v2im::jni::StringJni::Jstring2Cstring(env, (jstring) v2im::jni::ArrayListJni::Get(keys, i)).c_str();
        keyList.PushBack(groupID);
    }

    v2im::V2IMEngine::GetInstance()->DeleteGroupAttributes(groupID_c, keyList, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetGroupAttributes, jstring group_id, jobject keys, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMStringVector keyList;
    int size = v2im::jni::ArrayListJni::Size(keys);
    for (int i = 0; i < size; ++i) {
        V2TIMString groupID = v2im::jni::StringJni::Jstring2Cstring(env, (jstring) v2im::jni::ArrayListJni::Get(keys, i)).c_str();
        keyList.PushBack(groupID);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupAttributeMap>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupAttributeMap &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject j_obj_customHashMap = v2im::jni::HashMapJni::NewHashMap();
            V2TIMStringVector key_vector = value.AllKeys();
            for (int i = 0; i < value.Size(); ++i) {
                jstring keyStr = v2im::jni::StringJni::Cstring2Jstring(env, key_vector[i].CString());
                if (keyStr) {
                    jstring valueStr = v2im::jni::StringJni::Cstring2Jstring(env, value.Get(key_vector[i]).CString());
                    if (valueStr) {
                        v2im::jni::HashMapJni::Put(j_obj_customHashMap, keyStr, valueStr);
                        _env->DeleteLocalRef(valueStr);
                    }
                    _env->DeleteLocalRef(keyStr);
                }
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, j_obj_customHashMap);
            _env->DeleteLocalRef(j_obj_customHashMap);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetGroupAttributes(groupID_c, keyList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetGroupOnlineMemberCount, jstring group_id, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    auto value_callback = new v2im::ValueCallbackImpl<uint32_t>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const uint32_t &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            v2im::jni::IMCallbackJNI::Success(jni_callback, v2im::jni::IntegerJni::NewIntegerObj(value));

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetGroupOnlineMemberCount(groupID_c, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetGroupMemberList, jstring group_id, jint filter, jlong next_seq, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupMemberInfoResult>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupMemberInfoResult &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject memberInfoResultObj = v2im::jni::GroupMemberInfoResultJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, memberInfoResultObj);
            _env->DeleteLocalRef(memberInfoResultObj);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetGroupMemberList(groupID_c, filter, next_seq, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeGetGroupMembersInfo, jstring group_id, jobject member_list, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMStringVector memberList;
    int size = v2im::jni::ArrayListJni::Size(member_list);
    for (int i = 0; i < size; ++i) {
        V2TIMString memberID = v2im::jni::StringJni::Jstring2Cstring(env, (jstring) v2im::jni::ArrayListJni::Get(member_list, i)).c_str();
        memberList.PushBack(memberID);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupMemberFullInfoVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupMemberFullInfoVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject memberFullInfoObjList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject memberFullInfoObj = v2im::jni::GroupMemberFullInfoJNI::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(memberFullInfoObjList, memberFullInfoObj);
                _env->DeleteLocalRef(memberFullInfoObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, memberFullInfoObjList);
            _env->DeleteLocalRef(memberFullInfoObjList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetGroupMembersInfo(groupID_c, memberList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSearchGroupMembers, jobject param, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMGroupMemberSearchParam searchParam;
    v2im::jni::GroupMemberSearchParamJni::Convert2CoreObject(param, searchParam);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupSearchGroupMembersMap>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupSearchGroupMembersMap &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject j_obj_membersMapMap = v2im::jni::HashMapJni::NewHashMap();
            V2TIMStringVector key_vector = value.AllKeys();
            for (int i = 0; i < value.Size(); ++i) {
                jstring keyStr = v2im::jni::StringJni::Cstring2Jstring(env, key_vector[i].CString());
                if (keyStr) {
                    V2TIMGroupMemberFullInfoVector memberFullInfoVector = value.Get(key_vector[i]);
                    jobject valueObjList = v2im::jni::ArrayListJni::NewArrayList();
                    for (int i = 0; i < memberFullInfoVector.Size(); ++i) {
                        jobject item = v2im::jni::GroupMemberFullInfoJNI::Convert2JObject(memberFullInfoVector[i]);
                        v2im::jni::ArrayListJni::Add(valueObjList, item);
                        _env->DeleteLocalRef(item);
                    }
                    v2im::jni::HashMapJni::Put(j_obj_membersMapMap, keyStr, valueObjList);
                    _env->DeleteLocalRef(keyStr);
                    _env->DeleteLocalRef(valueObjList);
                }
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, j_obj_membersMapMap);
            _env->DeleteLocalRef(j_obj_membersMapMap);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->SearchGroupMembers(searchParam, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSetGroupMemberInfo, jstring group_id, jobject info, jobject callback) {

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    V2TIMGroupMemberFullInfo memberFullInfo;
    v2im::jni::GroupMemberFullInfoJNI::Convert2CoreObject(info, memberFullInfo);

    v2im::V2IMEngine::GetInstance()->SetGroupMemberInfo(groupID_c, memberFullInfo, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeMuteGroupMember, jstring group_id, jstring user_id, jint seconds, jobject callback) {

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    V2TIMString userID_c = v2im::jni::StringJni::Jstring2Cstring(env, user_id).c_str();
    uint32_t seconds_c = (uint32_t) seconds;

    v2im::V2IMEngine::GetInstance()->MuteGroupMember(groupID_c, userID_c, seconds_c, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeInviteUserToGroup, jstring group_id, jobject user_list, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMStringVector userList;
    int size = v2im::jni::ArrayListJni::Size(user_list);
    for (int i = 0; i < size; ++i) {
        V2TIMString memberID = v2im::jni::StringJni::Jstring2Cstring(env, (jstring) v2im::jni::ArrayListJni::Get(user_list, i)).c_str();
        userList.PushBack(memberID);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupMemberOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupMemberOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject memberOperationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject memberOperationResult = v2im::jni::GroupMemberOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(memberOperationResultList, memberOperationResult);
                _env->DeleteLocalRef(memberOperationResult);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, memberOperationResultList);
            _env->DeleteLocalRef(memberOperationResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->InviteUserToGroup(groupID_c, userList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeKickGroupMember, jstring group_id, jobject member_list, jstring reason, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMStringVector memberList;
    int size = v2im::jni::ArrayListJni::Size(member_list);
    for (int i = 0; i < size; ++i) {
        V2TIMString memberID = v2im::jni::StringJni::Jstring2Cstring(env, (jstring) v2im::jni::ArrayListJni::Get(member_list, i)).c_str();
        memberList.PushBack(memberID);
    }

    V2TIMString reason_c = v2im::jni::StringJni::Jstring2Cstring(env, reason).c_str();

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupMemberOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupMemberOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject memberOperationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject memberOperationResult = v2im::jni::GroupMemberOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(memberOperationResultList, memberOperationResult);
                _env->DeleteLocalRef(memberOperationResult);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, memberOperationResultList);
            _env->DeleteLocalRef(memberOperationResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->KickGroupMember(groupID_c, memberList, reason_c, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSetGroupMemberRole, jstring group_id, jstring user_id, jint role, jobject callback) {

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    V2TIMString userID_c = v2im::jni::StringJni::Jstring2Cstring(env, user_id).c_str();

    v2im::V2IMEngine::GetInstance()->SetGroupMemberRole(groupID_c, userID_c, (uint32_t) role, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeMarkGroupMemberList, jstring group_id, jobject member_idlist, jint mark_type, jboolean enable_mark, jobject callback) {

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMStringVector memberIdList;
    int size = v2im::jni::ArrayListJni::Size(member_idlist);
    for (int i = 0; i < size; ++i) {
        V2TIMString memberID = v2im::jni::StringJni::Jstring2Cstring(env, (jstring) v2im::jni::ArrayListJni::Get(member_idlist, i)).c_str();
        memberIdList.PushBack(memberID);
    }

    v2im::V2IMEngine::GetInstance()->MarkGroupMemberList(groupID_c, memberIdList, (uint32_t) mark_type, enable_mark,
                                                         new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeTransferGroupOwner, jstring group_id, jstring user_id, jobject callback) {

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    V2TIMString userID_c = v2im::jni::StringJni::Jstring2Cstring(env, user_id).c_str();

    v2im::V2IMEngine::GetInstance()->TransferGroupOwner(groupID_c, userID_c, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetGroupApplicationList, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupApplicationResult>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupApplicationResult &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject applicationResultObj = v2im::jni::GroupApplicationResultJni::Convert2JObject(value);
            v2im::jni::IMCallbackJNI::Success(jni_callback, applicationResultObj);
            _env->DeleteLocalRef(applicationResultObj);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetGroupApplicationList(value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeAcceptGroupApplication, jobject application, jstring reason, jobject callback) {

    V2TIMGroupApplication application_c;
    v2im::jni::GroupApplicationJni::Convert2CoreObject(application, application_c);

    V2TIMString reason_c = v2im::jni::StringJni::Jstring2Cstring(env, reason).c_str();

    v2im::V2IMEngine::GetInstance()->AcceptGroupApplication(application_c, reason_c, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeRefuseGroupApplication, jobject application, jstring reason, jobject callback) {

    V2TIMGroupApplication application_c;
    v2im::jni::GroupApplicationJni::Convert2CoreObject(application, application_c);

    V2TIMString reason_c = v2im::jni::StringJni::Jstring2Cstring(env, reason).c_str();

    v2im::V2IMEngine::GetInstance()->RefuseGroupApplication(application_c, reason_c, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeSetGroupApplicationRead, jobject callback) {

    v2im::V2IMEngine::GetInstance()->SetGroupApplicationRead(new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetJoinedCommunityList, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMGroupInfoVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMGroupInfoVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject joinedGroupList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject groupInfoObj = v2im::jni::GroupInfoJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(joinedGroupList, groupInfoObj);
                _env->DeleteLocalRef(groupInfoObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, joinedGroupList);
            _env->DeleteLocalRef(joinedGroupList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetJoinedCommunityList(value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeCreateTopicInCommunity, jstring group_id, jobject topic_info, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupID = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();
    V2TIMTopicInfo topicInfo;
    v2im::jni::GroupTopicInfoJni::Convert2CoreObject(topic_info, topicInfo);

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMString>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMString &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jstring groupID = v2im::jni::StringJni::Cstring2Jstring(env, value.CString());
            v2im::jni::IMCallbackJNI::Success(jni_callback, groupID);
            _env->DeleteLocalRef(groupID);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->CreateTopicInCommunity(groupID, topicInfo, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeDeleteTopicFromCommunity, jstring group_id, jobject topic_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMStringVector topicIdList;
    int size = v2im::jni::ArrayListJni::Size(topic_idlist);
    for (int i = 0; i < size; ++i) {
        V2TIMString memberID = v2im::jni::StringJni::Jstring2Cstring(env, (jstring) v2im::jni::ArrayListJni::Get(topic_idlist, i)).c_str();
        topicIdList.PushBack(memberID);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMTopicOperationResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMTopicOperationResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject operationResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject operationResultObj = v2im::jni::TopicOperationResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(operationResultList, operationResultObj);
                _env->DeleteLocalRef(operationResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, operationResultList);
            _env->DeleteLocalRef(operationResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->DeleteTopicFromCommunity(groupID_c, topicIdList, value_callback);
}

DEFINE_NATIVE_FUNC(void, NativeSetTopicInfo, jobject topic_info, jobject callback) {

    V2TIMTopicInfo topicInfo;
    v2im::jni::GroupTopicInfoJni::Convert2CoreObject(topic_info, topicInfo);

    v2im::V2IMEngine::GetInstance()->SetTopicInfo(topicInfo, new v2im::CallbackIMpl(callback));
}

DEFINE_NATIVE_FUNC(void, NativeGetTopicInfoList, jstring group_id, jobject topic_idlist, jobject callback) {
    jobject jni_callback = env->NewGlobalRef(callback);

    V2TIMString groupID_c = v2im::jni::StringJni::Jstring2Cstring(env, group_id).c_str();

    V2TIMStringVector topicIdList;
    int size = v2im::jni::ArrayListJni::Size(topic_idlist);
    for (int i = 0; i < size; ++i) {
        V2TIMString memberID = v2im::jni::StringJni::Jstring2Cstring(env, (jstring) v2im::jni::ArrayListJni::Get(topic_idlist, i)).c_str();
        topicIdList.PushBack(memberID);
    }

    auto value_callback = new v2im::ValueCallbackImpl<V2TIMTopicInfoResultVector>{};
    value_callback->setCallback([=](const int &error_code, const V2TIMString &error_message, const V2TIMTopicInfoResultVector &value) {
        v2im::jni::ScopedJEnv scopedJEnv;
        auto _env = scopedJEnv.GetEnv();

        if (V2TIMErrorCode::ERR_SUCC == error_code) {

            jobject topicInfoResultList = v2im::jni::ArrayListJni::NewArrayList();
            for (int i = 0; i < value.Size(); ++i) {
                jobject topicInfoResultObj = v2im::jni::TopicInfoResultJni::Convert2JObject(value[i]);
                v2im::jni::ArrayListJni::Add(topicInfoResultList, topicInfoResultObj);
                _env->DeleteLocalRef(topicInfoResultObj);
            }
            v2im::jni::IMCallbackJNI::Success(jni_callback, topicInfoResultList);
            _env->DeleteLocalRef(topicInfoResultList);

        } else {
            v2im::jni::IMCallbackJNI::Fail(jni_callback, error_code, error_message.CString());
        }
        _env->DeleteGlobalRef(jni_callback);
        delete value_callback;
    });

    v2im::V2IMEngine::GetInstance()->GetTopicInfoList(groupID_c, topicIdList, value_callback);
}

// java 和 native 方法映射
static JNINativeMethod gMethods[] = {
        {"nativeCreateGroup",               "(Lcom/tencent/imsdk/v2/V2TIMGroupInfo;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",             (void *) NativeCreateGroupToParame},
        {"nativeGetJoinedGroupList",        "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                                                      (void *) NativeGetJoinedGroupList},
        {"nativeGetGroupsInfo",             "(Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                                      (void *) NativeGetGroupsInfo},
        {"nativeSearchGroups",              "(Lcom/tencent/imsdk/v2/V2TIMGroupSearchParam;Lcom/tencent/imsdk/common/IMCallback;)V",                      (void *) NativeSearchGroups},
        {"nativeSetGroupInfo",              "(Lcom/tencent/imsdk/v2/V2TIMGroupInfo;Lcom/tencent/imsdk/common/IMCallback;)V",                             (void *) NativeSetGroupInfo},
        {"nativeInitGroupAttributes",       "(Ljava/lang/String;Ljava/util/HashMap;Lcom/tencent/imsdk/common/IMCallback;)V",                                                 (void *) NativeInitGroupAttributes},
        {"nativeSetGroupAttributes",        "(Ljava/lang/String;Ljava/util/HashMap;Lcom/tencent/imsdk/common/IMCallback;)V",                                                 (void *) NativeSetGroupAttributes},
        {"nativeDeleteGroupAttributes",     "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                    (void *) NativeDeleteGroupAttributes},
        {"nativeGetGroupAttributes",        "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                    (void *) NativeGetGroupAttributes},
        {"nativeGetGroupOnlineMemberCount", "(Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                                                    (void *) NativeGetGroupOnlineMemberCount},
        {"nativeGetGroupMemberList",        "(Ljava/lang/String;IJLcom/tencent/imsdk/common/IMCallback;)V",                                                                  (void *) NativeGetGroupMemberList},
        {"nativeGetGroupMembersInfo",       "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                    (void *) NativeGetGroupMembersInfo},
        {"nativeSearchGroupMembers",        "(Lcom/tencent/imsdk/v2/V2TIMGroupMemberSearchParam;Lcom/tencent/imsdk/common/IMCallback;)V",                (void *) NativeSearchGroupMembers},
        {"nativeSetGroupMemberInfo",        "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberFullInfo;Lcom/tencent/imsdk/common/IMCallback;)V", (void *) NativeSetGroupMemberInfo},
        {"nativeMuteGroupMember",           "(Ljava/lang/String;Ljava/lang/String;ILcom/tencent/imsdk/common/IMCallback;)V",                                                 (void *) NativeMuteGroupMember},
        {"nativeInviteUserToGroup",         "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                    (void *) NativeInviteUserToGroup},
        {"nativeKickGroupMember",           "(Ljava/lang/String;Ljava/util/List;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                  (void *) NativeKickGroupMember},
        {"nativeSetGroupMemberRole",        "(Ljava/lang/String;Ljava/lang/String;ILcom/tencent/imsdk/common/IMCallback;)V",                                                 (void *) NativeSetGroupMemberRole},
        {"nativeMarkGroupMemberList",       "(Ljava/lang/String;Ljava/util/List;IZLcom/tencent/imsdk/common/IMCallback;)V",                                                  (void *) NativeMarkGroupMemberList},
        {"nativeTransferGroupOwner",        "(Ljava/lang/String;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",                                                  (void *) NativeTransferGroupOwner},
        {"nativeGetGroupApplicationList",   "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                                                      (void *) NativeGetGroupApplicationList},
        {"nativeAcceptGroupApplication",    "(Lcom/tencent/imsdk/v2/V2TIMGroupApplication;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",    (void *) NativeAcceptGroupApplication},
        {"nativeRefuseGroupApplication",    "(Lcom/tencent/imsdk/v2/V2TIMGroupApplication;Ljava/lang/String;Lcom/tencent/imsdk/common/IMCallback;)V",    (void *) NativeRefuseGroupApplication},
        {"nativeSetGroupApplicationRead",   "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                                                      (void *) NativeSetGroupApplicationRead},
        {"nativeGetJoinedCommunityList",    "(Lcom/tencent/imsdk/common/IMCallback;)V",                                                                                      (void *) NativeGetJoinedCommunityList},
        {"nativeCreateTopicInCommunity",    "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMTopicInfo;Lcom/tencent/imsdk/common/IMCallback;)V",           (void *) NativeCreateTopicInCommunity},
        {"nativeDeleteTopicFromCommunity",  "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                    (void *) NativeDeleteTopicFromCommunity},
        {"nativeSetTopicInfo",              "(Lcom/tencent/imsdk/v2/V2TIMTopicInfo;Lcom/tencent/imsdk/common/IMCallback;)V",                             (void *) NativeSetTopicInfo},
        {"nativeGetTopicInfoList",          "(Ljava/lang/String;Ljava/util/List;Lcom/tencent/imsdk/common/IMCallback;)V",                                                    (void *) NativeGetTopicInfoList},
};

//注册 native 方法
int RegisterNativeMethodsForV2TIMGroupManager(JNIEnv *env) {
    return v2im::jni::util::RegisterNativeMethods(env, "com/tencent/imsdk/v2/V2TIMGroupManager", gMethods,
                                                  sizeof(gMethods) / sizeof(gMethods[0]));
}

#ifdef __cplusplus
}
#endif
