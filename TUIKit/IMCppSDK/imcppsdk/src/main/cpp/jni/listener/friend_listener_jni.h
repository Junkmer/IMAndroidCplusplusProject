//
// Created by EDY on 2022/9/27.
//

#ifndef IMCPLUSPLUSDEMO_FRIEND_LISTENER_JNI_H
#define IMCPLUSPLUSDEMO_FRIEND_LISTENER_JNI_H

#include <jni.h>
#include <memory>
#include <map>
#include "V2TIMListener.h"

namespace v2im {
    namespace jni {
        class FriendListenerJni final : public std::enable_shared_from_this<FriendListenerJni>, V2TIMFriendshipListener {
        public:
            FriendListenerJni() = default;

            ~FriendListenerJni() override = default;

            void InitListener();

            void AddListener(JNIEnv *env, jobject listener_friend, jstring listenerPath);

            void RemoveListener(JNIEnv *env, jstring listenerPath);

            static bool InitIDs(JNIEnv *env);

        protected:
            // V2TIMFriendshipListener
            void OnFriendApplicationListAdded(const V2TIMFriendApplicationVector &applicationList) override;

            void OnFriendApplicationListDeleted(const V2TIMStringVector &userIDList) override;

            void OnFriendApplicationListRead() override;

            void OnFriendListAdded(const V2TIMFriendInfoVector &friendInfoList) override;

            void OnFriendListDeleted(const V2TIMStringVector &userIDList) override;

            void OnBlackListAdded(const V2TIMFriendInfoVector &friendInfoList) override;

            void OnBlackListDeleted(const V2TIMStringVector &userIDList) override;

            void OnFriendInfoChanged(const V2TIMFriendInfoVector &friendInfoList) override;

        private:
            enum MethodID {
                MethodIDOnFriendApplicationListAdded = 0,
                MethodIDOnFriendApplicationListDeleted,
                MethodIDOnFriendApplicationListRead,
                MethodIDOnFriendListAdded,
                MethodIDOnFriendListDeleted,
                MethodIDOnBlackListAdd,
                MethodIDOnBlackListDeleted,
                MethodIDOnFriendInfoChanged,

                MethodIDMax,
            };
            std::map<std::string, jobject> listener_friend_map;
            static jclass j_cls_;
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
}

#endif //IMCPLUSPLUSDEMO_FRIEND_LISTENER_JNI_H
