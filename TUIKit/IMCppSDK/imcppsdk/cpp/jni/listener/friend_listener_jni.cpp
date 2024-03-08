//
// Created by EDY on 2022/9/27.
//

#include <LogUtil.h>
#include <v2_im_engine.h>
#include <jni_helper.h>
#include "friend_listener_jni.h"
#include "java_basic_jni.h"
#include "friend_info_jni.h"
#include "friend_application_jni.h"
#include "official_account_info_jni.h"

namespace v2im {
    namespace jni {

        jclass FriendListenerJni::j_cls_;
        jmethodID FriendListenerJni::j_method_id_array_[MethodIDMax];

        void FriendListenerJni::InitListener() {
            v2im::V2IMEngine::GetInstance()->AddFriendListener(this);
        }

        void FriendListenerJni::AddListener(JNIEnv *env, jobject listener_friend, jstring listenerPath) {
            if (nullptr == listener_friend) {
                LOGE("FriendListenerJni | AddListener listener_simple is null");
                return;
            }

            std::string path;
            for (auto &item: listener_friend_map) {
                path = StringJni::Jstring2Cstring(env, listenerPath);
                if (path.empty() || path == item.first) {
                    return;
                }
            }

            jobject j_obj = env->NewGlobalRef(listener_friend);
            listener_friend_map.insert(std::make_pair(path, j_obj));
        }

        void FriendListenerJni::RemoveListener(JNIEnv *env, jstring listenerPath) {
            if (nullptr == listenerPath) {
                LOGE("FriendListenerJni | RemoveListener listener_simple is null");
                return;
            }
            listener_friend_map.erase(StringJni::Jstring2Cstring(env, listenerPath));
        }

        bool FriendListenerJni::InitIDs(JNIEnv *env) {
            if (j_cls_ != nullptr) {
                return true;
            }
            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMFriendshipListener");
            if (cls == nullptr) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "onFriendApplicationListAdded", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnFriendApplicationListAdded] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onFriendApplicationListDeleted", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnFriendApplicationListDeleted] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onFriendApplicationListRead", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnFriendApplicationListRead] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onFriendListAdded", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnFriendListAdded] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onFriendListDeleted", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnFriendListDeleted] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onBlackListAdd", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnBlackListAdd] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onBlackListDeleted", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnBlackListDeleted] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "onFriendInfoChanged", "(Ljava/util/List;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MethodIDOnFriendInfoChanged] = jmethod;

            return true;
        }

        void FriendListenerJni::OnFriendApplicationListAdded(const V2TIMFriendApplicationVector &applicationList) {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject applicationListObj = ArrayListJni::NewArrayList();
            for (int i = 0; i < applicationList.Size(); ++i) {
                jobject applicationObj = FriendApplicationJni::Convert2JObject(applicationList[i]);
                if (applicationObj) {
                    ArrayListJni::Add(applicationListObj, applicationObj);
                    env->DeleteLocalRef(applicationObj);
                }
            }

            for (auto &item: listener_friend_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnFriendApplicationListAdded], applicationListObj);
            }

            env->DeleteLocalRef(applicationListObj);
        }

        void FriendListenerJni::OnFriendApplicationListDeleted(const V2TIMStringVector &userIDList) {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject userIDListObj = ArrayListJni::NewArrayList();
            for (int i = 0; i < userIDList.Size(); ++i) {
                jstring userIDStr = StringJni::Cstring2Jstring(env, userIDList[i].CString());
                if (userIDStr) {
                    ArrayListJni::Add(userIDListObj, userIDStr);
                    env->DeleteLocalRef(userIDStr);
                }
            }

            for (auto &item: listener_friend_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnFriendApplicationListDeleted], userIDListObj);
            }

            env->DeleteLocalRef(userIDListObj);
        }

        void FriendListenerJni::OnFriendApplicationListRead() {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            for (auto &item: listener_friend_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnFriendApplicationListRead]);
            }
        }

        void FriendListenerJni::OnFriendListAdded(const V2TIMFriendInfoVector &friendInfoList) {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject friendInfoListObj = ArrayListJni::NewArrayList();
            for (int i = 0; i < friendInfoList.Size(); ++i) {
                jobject friendInfoObj = FriendInfoJni::Convert2JObject(friendInfoList[i]);
                if (friendInfoObj) {
                    ArrayListJni::Add(friendInfoListObj, friendInfoObj);
                    env->DeleteLocalRef(friendInfoObj);
                }
            }

            for (auto &item: listener_friend_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnFriendListAdded], friendInfoListObj);
            }

            env->DeleteLocalRef(friendInfoListObj);
        }

        void FriendListenerJni::OnFriendListDeleted(const V2TIMStringVector &userIDList) {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject userIDListObj = ArrayListJni::NewArrayList();
            for (int i = 0; i < userIDList.Size(); ++i) {
                jstring userIDStr = StringJni::Cstring2Jstring(env, userIDList[i].CString());
                if (userIDStr) {
                    ArrayListJni::Add(userIDListObj, userIDStr);
                    env->DeleteLocalRef(userIDStr);
                }
            }

            for (auto &item: listener_friend_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnFriendListDeleted], userIDListObj);
            }

            env->DeleteLocalRef(userIDListObj);
        }

        void FriendListenerJni::OnBlackListAdded(const V2TIMFriendInfoVector &friendInfoList) {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject friendInfoListObj = ArrayListJni::NewArrayList();
            for (int i = 0; i < friendInfoList.Size(); ++i) {
                jobject friendInfoObj = FriendInfoJni::Convert2JObject(friendInfoList[i]);
                if (friendInfoObj) {
                    ArrayListJni::Add(friendInfoListObj, friendInfoObj);
                    env->DeleteLocalRef(friendInfoObj);
                }
            }

            for (auto &item: listener_friend_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnBlackListAdd], friendInfoListObj);
            }

            env->DeleteLocalRef(friendInfoListObj);
        }

        void FriendListenerJni::OnBlackListDeleted(const V2TIMStringVector &userIDList) {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject userIDListObj = ArrayListJni::NewArrayList();
            for (int i = 0; i < userIDList.Size(); ++i) {
                jstring userIDStr = StringJni::Cstring2Jstring(env, userIDList[i].CString());
                if (userIDStr) {
                    ArrayListJni::Add(userIDListObj, userIDStr);
                    env->DeleteLocalRef(userIDStr);
                }
            }

            for (auto &item: listener_friend_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnBlackListDeleted], userIDListObj);
            }

            env->DeleteLocalRef(userIDListObj);
        }

        void FriendListenerJni::OnFriendInfoChanged(const V2TIMFriendInfoVector &friendInfoList) {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject friendInfoListObj = ArrayListJni::NewArrayList();
            for (int i = 0; i < friendInfoList.Size(); ++i) {
                jobject friendInfoObj = FriendInfoJni::Convert2JObject(friendInfoList[i]);
                if (friendInfoObj) {
                    ArrayListJni::Add(friendInfoListObj, friendInfoObj);
                    env->DeleteLocalRef(friendInfoObj);
                }
            }

            for (auto &item: listener_friend_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnFriendInfoChanged], friendInfoListObj);
            }

            env->DeleteLocalRef(friendInfoListObj);
        }

        void FriendListenerJni::OnOfficialAccountSubscribed(const V2TIMOfficialAccountInfo &info) {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject accountInfoObj = OfficialAccountInfoJni::Convert2JObject(info);
            if (accountInfoObj) {
                for (auto &item: listener_friend_map) {
                    env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnOfficialAccountSubscribed], accountInfoObj);
                }

                env->DeleteLocalRef(accountInfoObj);
            }
        }

        void FriendListenerJni::OnOfficialAccountUnsubscribed(const V2TIMString &officialAccountID) {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject officialAccountIDObj = StringJni::Cstring2Jstring(env, officialAccountID.CString());

            for (auto &item: listener_friend_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnOfficialAccountUnsubscribed], officialAccountIDObj);
            }

            env->DeleteLocalRef(officialAccountIDObj);

        }

        void FriendListenerJni::OnOfficialAccountDeleted(const V2TIMString &officialAccountID) {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject officialAccountIDObj = StringJni::Cstring2Jstring(env, officialAccountID.CString());
            for (auto &item: listener_friend_map) {
                env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnOfficialAccountDeleted], officialAccountIDObj);
            }

            env->DeleteLocalRef(officialAccountIDObj);
        }

        void FriendListenerJni::OnOfficialAccountInfoChanged(const V2TIMOfficialAccountInfo &info) {
            if (listener_friend_map.empty()) {
                return;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            jobject accountInfoObj = OfficialAccountInfoJni::Convert2JObject(info);
            if (accountInfoObj) {
                for (auto &item: listener_friend_map) {
                    env->CallVoidMethod(item.second, j_method_id_array_[MethodIDOnOfficialAccountInfoChanged], accountInfoObj);
                }

                env->DeleteLocalRef(accountInfoObj);
            }
        }
    }// namespace jni
}// namespace v2im