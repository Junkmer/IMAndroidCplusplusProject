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
        class MessageJni {
        public:
            static bool InitIDs(JNIEnv *env);

            static jobject Convert2JObject(const V2TIMMessage &v2TimMessage);

            static bool Convert2CoreObject(const jobject &messageObj,V2TIMMessage &v2TimMessage);

            static void UpdateJMessageObject(jobject &messageObj, V2TIMMessage &v2TimMessage);

            static void UpdateJMessageStatus(jobject &messageObj,const V2TIMMessage &v2TimMessage,const bool &isRetry);

            static void UpdateJMessageStatus2Fail(jobject &messageObj);

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
                FieldIDIsExcludedFromContentModeration,
                FieldIDIsSupportMessageExtension,
                FieldIDRiskContent,
                FieldIDRevokerInfo,
                FieldIDRevokeReason,

                FieldIDMax,
            };

            enum MethodID {
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
