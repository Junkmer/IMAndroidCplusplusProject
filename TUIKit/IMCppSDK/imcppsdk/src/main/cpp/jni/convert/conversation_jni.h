//
// Created by Junker on 2022/9/27.
//

#ifndef IMCPLUSPLUSDEMO_CONVERSATION_JNI_H
#define IMCPLUSPLUSDEMO_CONVERSATION_JNI_H

#include <jni.h>
#include "V2TIMConversation.h"

namespace v2im {
    namespace jni {
        class ConversationJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMConversation &conversation);

        private:
            enum FieldID {
                FieldIDConversationID = 0,
                FieldIDType,
                FieldIDUserID,
                FieldIDGroupID,
                FieldIDShowName,
                FieldIDFaceUrl,
                FieldIDRecvOpt,
                FieldIDGroupType,
                FieldIDUnreadCount,
                FieldIDLastMessage,
                FieldIDDraftText,
                FieldIDDraftTimestamp,
                FieldIDGroupAtInfoList,
                FieldIDPinned,
                FieldIDOrderKey,
                FieldIDMarkList,
                FieldIDCustomData,
                FieldIDConversationGroupList,

                FieldIDMax,
            };

            enum MethodID {
                MethodIDConstruct = 0,
                MethodIDAddGroupAtInfo,
                MethodIDAddMark,
                MethodIDAddConversationGroup,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_id_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }// namespace v2im
}// namespace jni

#endif //IMCPLUSPLUSDEMO_CONVERSATION_JNI_H
