//
// Created by EDY on 2022/9/27.
//

#include <LogUtil.h>
#include <v2_im_engine.h>
#include <jni_helper.h>
#include "conversation_listener_jni.h"
#include "conversation_jni.h"
#include "java_basic_jni.h"
#include "conversation_list_filter_jni.h"

namespace v2im {
    namespace jni {

        jclass ConversationListenerJni::j_cls_;
        jmethodID ConversationListenerJni::j_method_id_array_[MethodIDMax];

        void ConversationListenerJni::InitListener() {
            v2im::V2IMEngine::GetInstance()->AddConversationListener(this);
        }

        void ConversationListenerJni::AddListener(JNIEnv *env, jobject listener_conversation, jstring listenerPath) {
            if (nullptr == listener_conversation) {
                LOGE("ConversationListenerJni | AddListener listener_simple is null");
                return;
            }

            std::string path;
            for (auto &item: listener_conversation_map) {
                path = StringJni::Jstring2Cstring(env,listenerPath);
                if (path.empty() || path == item.first){
                    return;
                }
            }

            jobject j_obj = env->NewGlobalRef(listener_conversation);
            listener_conversation_map.insert(std::make_pair(path, j_obj));
        }

        void ConversationListenerJni::RemoveListener(JNIEnv *env, jstring listenerPath) {
            if (nullptr == listenerPath) {
                LOGE("ConversationListenerJni | RemoveListener listener is null");
                return;
            }
            listener_conversation_map.erase(StringJni::Jstring2Cstring(env,listenerPath));
        }

        bool ConversationListenerJni::InitIDs(JNIEnv *env) {
            if (j_cls_ != nullptr) {
                return true;
            }
            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMConversationListener");
            if (cls == nullptr) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "onSyncServerStart", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnSyncServerStart] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onSyncServerFinish", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnSyncServerFinish] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onSyncServerFailed", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnSyncServerFailed] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onNewConversation", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnNewConversation] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onConversationChanged", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnConversationChanged] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onConversationDeleted", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnConversationDeleted] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onTotalUnreadMessageCountChanged", "(J)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnTotalUnreadMessageCountChanged] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onUnreadMessageCountChangedByFilter", "(Lcom/tencent/imsdk/v2/V2TIMConversationListFilter;J)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnUnreadMessageCountChangedByFilter] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onConversationGroupCreated", "(Ljava/lang/String;Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnConversationGroupCreated] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onConversationGroupDeleted", "(Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnConversationGroupDeleted] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onConversationGroupNameChanged", "(Ljava/lang/String;Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnConversationGroupNameChanged] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onConversationsAddedToGroup", "(Ljava/lang/String;Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnConversationsAddedToGroup] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onConversationsDeletedFromGroup", "(Ljava/lang/String;Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnConversationsDeletedFromGroup] = jmethod;

            return true;
        }

        void ConversationListenerJni::OnSyncServerStart() {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();


            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnSyncServerStart]);
            }
        }

        void ConversationListenerJni::OnSyncServerFinish() {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();


            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnSyncServerFinish]);
            }
        }

        void ConversationListenerJni::OnSyncServerFailed() {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();


            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnSyncServerFailed]);
            }
        }

        void ConversationListenerJni::OnNewConversation(const V2TIMConversationVector &conversationList) {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject conversationObjList = ArrayListJni::NewArrayList();
            for (int i = 0; i < conversationList.Size(); ++i) {
                jobject conversationObj = ConversationJni::Convert2JObject(conversationList[i]);
                if (conversationObj) {
                    ArrayListJni::Add(conversationObjList, conversationObj);
                    env->DeleteLocalRef(conversationObj);
                }
            }

            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnNewConversation], conversationObjList);
            }

            env->DeleteLocalRef(conversationObjList);
        }

        void ConversationListenerJni::OnConversationChanged(const V2TIMConversationVector &conversationList) {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject conversationObjList = ArrayListJni::NewArrayList();
            for (int i = 0; i < conversationList.Size(); ++i) {
                jobject conversationObj = ConversationJni::Convert2JObject(conversationList[i]);
                if (conversationObj) {
                    ArrayListJni::Add(conversationObjList, conversationObj);
                    env->DeleteLocalRef(conversationObj);
                }
            }

            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnConversationChanged], conversationObjList);
            }

            env->DeleteLocalRef(conversationObjList);
        }

        void ConversationListenerJni::OnConversationDeleted(const V2TIMStringVector &conversationIDList) {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject j_obj_convIDList = ArrayListJni::NewArrayList();
            for (int i = 0; i < conversationIDList.Size(); ++i) {
                jobject convID = StringJni::Cstring2Jstring(env,conversationIDList[i].CString());
                if (convID) {
                    ArrayListJni::Add(j_obj_convIDList, convID);
                    env->DeleteLocalRef(convID);
                }
            }

            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnConversationDeleted], j_obj_convIDList);
            }

            env->DeleteLocalRef(j_obj_convIDList);
        }

        void ConversationListenerJni::OnTotalUnreadMessageCountChanged(uint64_t totalUnreadCount) {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnTotalUnreadMessageCountChanged], (jlong) totalUnreadCount);
            }
        }

        void ConversationListenerJni::OnUnreadMessageCountChangedByFilter(const V2TIMConversationListFilter &filter, uint64_t totalUnreadCount) {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject j_obj_filter = ConversationListFilterJni::Convert2JObject(filter);

            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnUnreadMessageCountChangedByFilter], j_obj_filter,(jlong) totalUnreadCount);
            }

            env->DeleteLocalRef(j_obj_filter);
        }

        void ConversationListenerJni::OnConversationGroupCreated(const V2TIMString &groupName, const V2TIMConversationVector &conversationList) {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupNameStr = StringJni::Cstring2Jstring(env, groupName.CString());

            jobject conversationObjList = ArrayListJni::NewArrayList();
            for (int i = 0; i < conversationList.Size(); ++i) {
                jobject conversationObj = ConversationJni::Convert2JObject(conversationList[i]);
                if (conversationObj) {
                    ArrayListJni::Add(conversationObjList, conversationObj);
                    env->DeleteLocalRef(conversationObj);
                }
            }

            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnConversationGroupCreated], groupNameStr, conversationObjList);
            }

            env->DeleteLocalRef(groupNameStr);
            env->DeleteLocalRef(conversationObjList);
        }

        void ConversationListenerJni::OnConversationGroupDeleted(const V2TIMString &groupName) {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupNameStr = StringJni::Cstring2Jstring(env, groupName.CString());

            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnConversationGroupDeleted], groupNameStr);
            }

            env->DeleteLocalRef(groupNameStr);
        }

        void ConversationListenerJni::OnConversationGroupNameChanged(const V2TIMString &oldName, const V2TIMString &newName) {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring oldNameStr = StringJni::Cstring2Jstring(env, oldName.CString());
            jstring newNameStr = StringJni::Cstring2Jstring(env, newName.CString());

            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnConversationGroupNameChanged], oldNameStr, newNameStr);
            }

            env->DeleteLocalRef(oldNameStr);
            env->DeleteLocalRef(newNameStr);
        }

        void ConversationListenerJni::OnConversationsAddedToGroup(const V2TIMString &groupName, const V2TIMConversationVector &conversationList) {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupNameStr = StringJni::Cstring2Jstring(env, groupName.CString());

            jobject conversationObjList = ArrayListJni::NewArrayList();
            for (int i = 0; i < conversationList.Size(); ++i) {
                jobject conversationObj = ConversationJni::Convert2JObject(conversationList[i]);
                if (conversationObj) {
                    ArrayListJni::Add(conversationObjList, conversationObj);
                    env->DeleteLocalRef(conversationObj);
                }
            }

            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnConversationsAddedToGroup], groupNameStr, conversationObjList);
            }

            env->DeleteLocalRef(groupNameStr);
            env->DeleteLocalRef(conversationObjList);
        }

        void ConversationListenerJni::OnConversationsDeletedFromGroup(const V2TIMString &groupName, const V2TIMConversationVector &conversationList) {
            if (listener_conversation_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jstring groupNameStr = StringJni::Cstring2Jstring(env, groupName.CString());

            jobject conversationObjList = ArrayListJni::NewArrayList();
            for (int i = 0; i < conversationList.Size(); ++i) {
                jobject conversationObj = ConversationJni::Convert2JObject(conversationList[i]);
                if (conversationObj) {
                    ArrayListJni::Add(conversationObjList, conversationObj);
                    env->DeleteLocalRef(conversationObj);
                }
            }

            for (auto &item: listener_conversation_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnConversationsDeletedFromGroup], groupNameStr, conversationObjList);
            }

            env->DeleteLocalRef(groupNameStr);
            env->DeleteLocalRef(conversationObjList);
        }

    }// namespace jni
}// namespace v2im