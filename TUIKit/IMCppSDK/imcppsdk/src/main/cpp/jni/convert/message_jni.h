//
// Created by EDY on 2022/9/20.
//

#ifndef IMCPLUSPLUSDEMO_MESSAGE_JNI_H
#define IMCPLUSPLUSDEMO_MESSAGE_JNI_H

#include <jni.h>
#include "V2TIMMessage.h"
#include <memory>

namespace v2im {
    namespace jni {
        class MessageJni{
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMMessage &v2TimMessage);
            static std::unique_ptr<V2TIMMessage> Convert2CoreObject(jobject &messageObj);
            static void UpdateJMessageObject(jobject &messageObj,V2TIMMessage &v2TimMessage);

        private:
            enum FieldID {
                FieldIDMsgID = 0,
                FieldIDTimestamp,
                FieldIDSender,
                FieldIDNickName,
                FieldIDFriendRemark,
                FieldIDFaceUrl,
                FieldIDNameCard,
                FieldIDGroupID,
                FieldIDUserID,
                FieldIDStatus,
                FieldIDElemType,
                FieldIDElemList,

                FieldIDLocalCustomInt,
                FieldIDLocalCustomData,
                FieldIDCloudCustomData,

                FieldIDIsSelf,
                FieldIDIsRead,
                FieldIDIsPeerRead,

                FieldIDNeedReadReceipt,

                FieldIDIsBroadcastMessage,
                FieldIDPriority,
                FieldIDOfflinePushInfo,
                FieldIDGroupAtUserList,
                FieldIDSeq,
                FieldIDRandom,
                FieldIDIsExcludedFromUnreadCount,
                FieldIDIsExcludedFromLastMessage,

                FieldIDMax,
            };

            enum MethodID{
                MethodIDConstructor = 0,
                MethodIDAddMessageElem,

                MethodIDMax
            };

            static jclass j_cls_;
            static jfieldID j_filed_id_array[FieldIDMax];
            static jmethodID j_method_id_array[MethodIDMax];
        };
    }// namespace jni
}// namespace v2im

#endif //IMCPLUSPLUSDEMO_MESSAGE_JNI_H
