//
// Created by EDY on 2022/9/23.
//

#include <LogUtil.h>
#include <jni_helper.h>
#include <group_member_info_jni.h>
#include "group_listener_jni.h"
#include "v2_im_engine.h"
#include "java_basic_jni.h"
#include "group_member_change_info_jni.h"
#include "group_change_info_jni.h"
#include "group_topic_info_jni.h"

namespace v2im {
    namespace jni {
        jclass GroupListenerJni::j_cls_;
        jmethodID GroupListenerJni::j_method_id_array_[MethodIDMax];

        void GroupListenerJni::InitListener() {
            v2im::V2IMEngine::GetInstance()->AddGroupListener(this);
        }

        void GroupListenerJni::AddListener(JNIEnv *env, jobject listener_simple, jstring listenerPath) {
            if (nullptr == listener_simple) {
                LOGE("GroupListenerJni | AddListener listener_simple is null");
                return;
            }
            if (listener_group_map.empty()) {
                v2im::V2IMEngine::GetInstance()->AddGroupListener(this);
            }

            std::string path;
            for (auto &item: listener_group_map) {
                path = StringJni::Jstring2Cstring(env, listenerPath);
                if (path.empty() || path == item.first) {
                    return;
                }
            }

            jobject j_obj = env->NewGlobalRef(listener_simple);
            listener_group_map.insert(std::make_pair(path, j_obj));
        }

        void GroupListenerJni::RemoveListener(JNIEnv *env, jstring listenerPath) {
            if (nullptr == listenerPath) {
                LOGE("GroupListenerJni | RemoveListener listener is null");
                return;
            }
            listener_group_map.erase(StringJni::Jstring2Cstring(env, listenerPath));
        }

        bool GroupListenerJni::InitIDs(JNIEnv *env) {
            if (j_cls_ != nullptr) {
                return true;
            }
            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMGroupListener");
            if (cls == nullptr) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;
            jmethod = env->GetMethodID(j_cls_, "onMemberEnter", "(Ljava/lang/String;Ljava/util/List;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnMemberEnter] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onMemberLeave",
                                       "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnMemberLeave] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onMemberInvited",
                                       "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;Ljava/util/List;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnMemberInvited] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onMemberKicked",
                                       "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;Ljava/util/List;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnMemberKicked] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onMemberInfoChanged", "(Ljava/lang/String;Ljava/util/List;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnMemberInfoChanged] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onAllGroupMembersMuted", "(Ljava/lang/String;Z)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnAllGroupMembersMuted] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onMemberMarkChanged", "(Ljava/lang/String;Ljava/util/List;IZ)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnMemberMarkChanged] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onGroupCreated", "(Ljava/lang/String;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnGroupCreated] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onGroupDismissed",
                                       "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnGroupDismissed] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onGroupRecycled",
                                       "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnGroupRecycled] = jmethod;

            jmethod =
                    env->GetMethodID(j_cls_, "onGroupInfoChanged", "(Ljava/lang/String;Ljava/util/List;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnGroupInfoChanged] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onReceiveJoinApplication",
                                       "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;Ljava/lang/String;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnReceiveJoinApplication] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onApplicationProcessed",
                                       "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;ZLjava/lang/String;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnApplicationProcessed] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onGrantAdministrator",
                                       "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;Ljava/util/List;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnGrantAdministrator] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onRevokeAdministrator",
                                       "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMGroupMemberInfo;Ljava/util/List;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnRevokeAdministrator] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onQuitFromGroup", "(Ljava/lang/String;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnQuitFromGroup] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onReceiveRESTCustomData", "(Ljava/lang/String;[B)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnReceiveCustomData] = jmethod;

            jmethod =
                    env->GetMethodID(j_cls_, "onGroupAttributeChanged", "(Ljava/lang/String;Ljava/util/Map;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnGroupAttributeChanged] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onGroupCounterChanged", "(Ljava/lang/String;Ljava/lang/String;J)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnGroupCounterChanged] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onTopicCreated", "(Ljava/lang/String;Ljava/lang/String;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnTopicCreated] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onTopicDeleted", "(Ljava/lang/String;Ljava/util/List;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnTopicDeleted] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onTopicInfoChanged",
                                       "(Ljava/lang/String;Lcom/tencent/imsdk/v2/V2TIMTopicInfo;)V");
            if (jmethod == nullptr) {
                return false;
            }
            j_method_id_array_[MethodIDOnTopicChanged] = jmethod;

            return true;
        }

        void GroupListenerJni::OnMemberEnter(const V2TIMString &groupID, const V2TIMGroupMemberInfoVector &memberList) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            jobject j_memberList = ArrayListJni::NewArrayList();
            for (int i = 0; i < memberList.Size(); ++i) {
                jobject memberObj = GroupMemberInfoJni::Convert2JObject(memberList[i]);
                ArrayListJni::Add(j_memberList, memberObj);
                env->DeleteLocalRef(memberObj);
            }

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnMemberEnter], groupIDStr, j_memberList);
            }

            env->DeleteLocalRef(j_memberList);
        }

        void GroupListenerJni::OnMemberLeave(const V2TIMString &groupID, const V2TIMGroupMemberInfo &member) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            jobject j_obj_member = GroupMemberInfoJni::Convert2JObject(member);
            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnMemberLeave], groupIDStr, j_obj_member);
            }
            env->DeleteLocalRef(j_obj_member);
        }

        void GroupListenerJni::OnMemberInvited(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser,
                                               const V2TIMGroupMemberInfoVector &memberList) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            jobject j_opUser = GroupMemberInfoJni::Convert2JObject(opUser);

            jobject j_obj_memberList = ArrayListJni::NewArrayList();

            for (int i = 0; i < memberList.Size(); ++i) {
                jobject j_member = GroupMemberInfoJni::Convert2JObject(memberList[i]);
                ArrayListJni::Add(j_obj_memberList, j_member);
                env->DeleteLocalRef(j_member);
            }

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnMemberInvited], groupIDStr, j_opUser, j_obj_memberList);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(j_opUser);
            env->DeleteLocalRef(j_obj_memberList);
        }

        void GroupListenerJni::OnMemberKicked(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser,
                                              const V2TIMGroupMemberInfoVector &memberList) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            jobject j_opUser = GroupMemberInfoJni::Convert2JObject(opUser);

            jobject j_obj_memberList = ArrayListJni::NewArrayList();
            for (int i = 0; i < memberList.Size(); ++i) {
                jobject j_obj_member = GroupMemberInfoJni::Convert2JObject(memberList[i]);
                ArrayListJni::Add(j_obj_memberList, j_obj_member);
                env->DeleteLocalRef(j_obj_member);
            }

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnMemberKicked], groupIDStr, j_opUser, j_obj_memberList);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(j_opUser);
            env->DeleteLocalRef(j_obj_memberList);
        }

        void GroupListenerJni::OnMemberInfoChanged(const V2TIMString &groupID, const V2TIMGroupMemberChangeInfoVector &v2TIMGroupMemberChangeInfoList) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            jobject j_obj_groupMemberChangeInfoList = ArrayListJni::NewArrayList();
            for (int i = 0; i < v2TIMGroupMemberChangeInfoList.Size(); ++i) {
                jobject j_obj_groupMemberChangeInfo = GroupMemberChangeInfoJni::Convert2JObject(v2TIMGroupMemberChangeInfoList[i]);
                ArrayListJni::Add(j_obj_groupMemberChangeInfoList, j_obj_groupMemberChangeInfo);
                env->DeleteLocalRef(j_obj_groupMemberChangeInfo);
            }

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnMemberInfoChanged], groupIDStr, j_obj_groupMemberChangeInfoList);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(j_obj_groupMemberChangeInfoList);
        }

        void GroupListenerJni::OnAllGroupMembersMuted(const V2TIMString &groupID, bool isMute) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnAllGroupMembersMuted], groupIDStr, isMute);
            }

            env->DeleteLocalRef(groupIDStr);
        }

        void GroupListenerJni::OnMemberMarkChanged(const V2TIMString &groupID, const V2TIMStringVector &memberIDList, uint32_t markType, bool enableMark) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            jobject j_obj_memberIDList = ArrayListJni::NewArrayList();
            for (int i = 0; i < memberIDList.Size(); ++i) {
                jstring j_obj_memberID = StringJni::Cstring2Jstring(env, memberIDList[i].CString());
                ArrayListJni::Add(j_obj_memberIDList, j_obj_memberID);
                env->DeleteLocalRef(j_obj_memberID);
            }

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnMemberMarkChanged], groupIDStr, j_obj_memberIDList, markType, enableMark);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(j_obj_memberIDList);
        }

        void GroupListenerJni::OnGroupCreated(const V2TIMString &groupID) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            for (auto item_listener = listener_group_map.begin(); item_listener != listener_group_map.end(); item_listener++) {
                env->CallVoidMethod(item_listener->second, j_method_id_array_[MethodIDOnGroupCreated], groupIDStr);
            }

            env->DeleteLocalRef(groupIDStr);
        }

        void GroupListenerJni::OnGroupDismissed(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            jobject j_obj_opUser = GroupMemberInfoJni::Convert2JObject(opUser);

            for (auto item_listener = listener_group_map.begin(); item_listener != listener_group_map.end(); item_listener++) {
                env->CallVoidMethod(item_listener->second, j_method_id_array_[MethodIDOnGroupDismissed], groupIDStr, j_obj_opUser);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(j_obj_opUser);
        }

        void GroupListenerJni::OnGroupRecycled(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            jobject j_obj_opUser = GroupMemberInfoJni::Convert2JObject(opUser);

            for (auto item_listener = listener_group_map.begin(); item_listener != listener_group_map.end(); item_listener++) {
                env->CallVoidMethod(item_listener->second, j_method_id_array_[MethodIDOnGroupRecycled], groupIDStr, j_obj_opUser);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(j_obj_opUser);
        }

        void GroupListenerJni::OnGroupInfoChanged(const V2TIMString &groupID, const V2TIMGroupChangeInfoVector &changeInfos) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            jobject j_obj_changeInfoList = ArrayListJni::NewArrayList();

            for (int i = 0; i < changeInfos.Size(); ++i) {
                jobject j_obj_changeInfo = GroupChangeInfoJni::Convert2JObject(changeInfos[i]);
                ArrayListJni::Add(j_obj_changeInfoList, j_obj_changeInfo);
                env->DeleteLocalRef(j_obj_changeInfo);
            }


            for (auto item_listener = listener_group_map.begin(); item_listener != listener_group_map.end(); item_listener++) {
                env->CallVoidMethod(item_listener->second, j_method_id_array_[MethodIDOnGroupInfoChanged], groupIDStr, j_obj_changeInfoList);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(j_obj_changeInfoList);
        }

        void GroupListenerJni::OnGroupAttributeChanged(const V2TIMString &groupID, const V2TIMGroupAttributeMap &groupAttributeMap) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            V2TIMStringVector vectorKeys = groupAttributeMap.AllKeys();
            jobject map_obj = HashMapJni::NewHashMap();
            for (int i = 0; i < groupAttributeMap.Size(); ++i) {
                jstring key = StringJni::Cstring2Jstring(env, vectorKeys[i].CString());
                jstring value = StringJni::Cstring2Jstring(env, groupAttributeMap.Get(vectorKeys[i]).CString());
                HashMapJni::Put(map_obj, key, value);

                env->DeleteLocalRef(key);
                env->DeleteLocalRef(value);
            }

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnMemberKicked], groupIDStr, map_obj);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(map_obj);
        }

        void GroupListenerJni::OnGroupCounterChanged(const V2TIMString &groupID, const V2TIMString &key, int64_t newValue) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());
            jstring keyStr = StringJni::Cstring2Jstring(env, key.CString());

            for (auto item_listener = listener_group_map.begin(); item_listener != listener_group_map.end(); item_listener++) {
                env->CallVoidMethod(item_listener->second, j_method_id_array_[MethodIDOnGroupRecycled], groupIDStr, keyStr, newValue);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(keyStr);
        }

        void GroupListenerJni::OnReceiveJoinApplication(const V2TIMString &groupID, const V2TIMGroupMemberInfo &member, const V2TIMString &opReason) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());
            jobject j_obj_member = GroupMemberInfoJni::Convert2JObject(member);
            jstring j_str_opReason = StringJni::Cstring2Jstring(env, opReason.CString());

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnReceiveJoinApplication], groupIDStr, j_obj_member, j_str_opReason);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(j_obj_member);
            env->DeleteLocalRef(j_str_opReason);
        }

        void GroupListenerJni::OnApplicationProcessed(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser, bool isAgreeJoin,
                                                      const V2TIMString &opReason) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());
            jobject j_obj_opUser = GroupMemberInfoJni::Convert2JObject(opUser);
            jstring j_str_opReason = StringJni::Cstring2Jstring(env, groupID.CString());

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnApplicationProcessed], groupIDStr, j_obj_opUser, isAgreeJoin, j_str_opReason);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(j_obj_opUser);
            env->DeleteLocalRef(j_str_opReason);
        }

        void GroupListenerJni::OnGrantAdministrator(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser,
                                                    const V2TIMGroupMemberInfoVector &memberList) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());
            jobject j_obj_opUser = GroupMemberInfoJni::Convert2JObject(opUser);
            jobject j_obj_memberList = ArrayListJni::NewArrayList();

            for (int i = 0; i < memberList.Size(); ++i) {
                jobject j_obj_member = GroupMemberInfoJni::Convert2JObject(memberList[i]);
                ArrayListJni::Add(j_obj_memberList, j_obj_member);
                env->DeleteLocalRef(j_obj_member);
            }

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnGrantAdministrator], groupIDStr, j_obj_opUser, j_obj_memberList);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(j_obj_opUser);
            env->DeleteLocalRef(j_obj_memberList);
        }

        void GroupListenerJni::OnRevokeAdministrator(const V2TIMString &groupID, const V2TIMGroupMemberInfo &opUser,
                                                     const V2TIMGroupMemberInfoVector &memberList) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());
            jobject j_obj_opUser = GroupMemberInfoJni::Convert2JObject(opUser);
            jobject j_obj_memberList = ArrayListJni::NewArrayList();
            for (int i = 0; i < memberList.Size(); ++i) {
                jobject j_obj_member = GroupMemberInfoJni::Convert2JObject(memberList[i]);
                ArrayListJni::Add(j_obj_memberList, j_obj_member);
                env->DeleteLocalRef(j_obj_member);
            }

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnRevokeAdministrator], groupIDStr, j_obj_opUser, j_obj_memberList);
            }

            env->DeleteLocalRef(groupIDStr);
            env->DeleteLocalRef(j_obj_opUser);
            env->DeleteLocalRef(j_obj_memberList);
        }

        void GroupListenerJni::OnQuitFromGroup(const V2TIMString &groupID) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnQuitFromGroup], groupIDStr);
            }

            env->DeleteLocalRef(groupIDStr);
        }

        void GroupListenerJni::OnReceiveRESTCustomData(const V2TIMString &groupID, const V2TIMBuffer &customData) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupIDStr = StringJni::Cstring2Jstring(env, groupID.CString());
            jobject j_str_customData = ByteJni::Cuint8_t2JByteArray(env, customData.Data(), customData.Size());

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnReceiveCustomData], groupIDStr, j_str_customData);
            }

            env->DeleteLocalRef(groupIDStr);
        }

        void GroupListenerJni::OnTopicCreated(const V2TIMString &groupID, const V2TIMString &topicID) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring communityIDStr = StringJni::Cstring2Jstring(env, groupID.CString());
            jstring j_str_topicID = StringJni::Cstring2Jstring(env, topicID.CString());

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnTopicCreated], communityIDStr, j_str_topicID);
            }

            env->DeleteLocalRef(communityIDStr);
            env->DeleteLocalRef(j_str_topicID);
        }

        void GroupListenerJni::OnTopicDeleted(const V2TIMString &groupID, const V2TIMStringVector &topicIDList) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring communityIDStr = StringJni::Cstring2Jstring(env, groupID.CString());

            jobject j_obj_topicIDList = ArrayListJni::NewArrayList();
            for (int i = 0; i < topicIDList.Size(); ++i) {
                jstring j_obj_topicID = StringJni::Cstring2Jstring(env, topicIDList[i].CString());
                ArrayListJni::Add(j_obj_topicIDList, j_obj_topicID);
                env->DeleteLocalRef(j_obj_topicID);
            }

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnTopicDeleted], communityIDStr, j_obj_topicIDList);
            }

            env->DeleteLocalRef(communityIDStr);
            env->DeleteLocalRef(j_obj_topicIDList);
        }

        void GroupListenerJni::OnTopicChanged(const V2TIMString &groupID, const V2TIMTopicInfo &topicInfo) {
            if (listener_group_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring communityIDStr = StringJni::Cstring2Jstring(env, groupID.CString());
            jobject j_obj_topicInfo = GroupTopicInfoJni::Convert2JObject(topicInfo);

            for (auto &item_listener: listener_group_map) {
                env->CallVoidMethod(item_listener.second, j_method_id_array_[MethodIDOnTopicChanged], communityIDStr, j_obj_topicInfo);
            }

            env->DeleteLocalRef(communityIDStr);
            env->DeleteLocalRef(j_obj_topicInfo);
        }

    }// namespace jni
}// namespace v2im