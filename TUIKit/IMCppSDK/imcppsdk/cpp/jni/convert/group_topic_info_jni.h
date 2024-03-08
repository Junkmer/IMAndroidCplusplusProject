//
// Created by Junker on 2022/9/23.
//

#ifndef IMCPLUSPLUSDEMO_GROUP_TOPIC_INFO_JNI_H
#define IMCPLUSPLUSDEMO_GROUP_TOPIC_INFO_JNI_H

#include <jni.h>
#include "V2TIMMessage.h"

namespace v2im {
    namespace jni {
        class GroupTopicInfoJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMTopicInfo &topicInfo);
            static bool Convert2CoreObject(const jobject &object, V2TIMTopicInfo &topicInfo);

        private:
            enum FieldID {
                FieldIDTopicID = 0,
                FieldIDTopicName,
                FieldIDTopicFaceUrl,
                FieldIDIntroduction,
                FieldIDNotification,
                FieldIDAllMute,
                FieldIDSelfMuteTime,
                FieldIDCustomString,
                FieldIDRecvOpt,
                FieldIDDraftText,
                FieldIDUnreadCount,
                FieldIDLastMessage,
                FieldIDGroupAtInfoList,

                FieldIDMax,
            };

            enum MethodID {
                MethodIDConstruct = 0,
                MethodIDAddGroupAtInfo,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_id_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }// namespace jni
}// namespace v2im

#endif //IMCPLUSPLUSDEMO_GROUP_TOPIC_INFO_JNI_H
