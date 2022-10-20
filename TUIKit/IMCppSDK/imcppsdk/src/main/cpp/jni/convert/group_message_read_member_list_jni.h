//
// Created by EDY on 2022/10/8.
//

#ifndef IMCPLUSPLUSDEMO_GROUP_MESSAGE_READ_MEMBER_LIST_JNI_H
#define IMCPLUSPLUSDEMO_GROUP_MESSAGE_READ_MEMBER_LIST_JNI_H

#include <jni.h>
#include "V2TIMMessage.h"

namespace v2im {
    namespace jni {
        class GroupMessageReadMemberListJni{
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMGroupMessageReadMemberList &readMemberList);

        private:
            enum FieldID{
                FieldIDNextSeq = 0,
                FieldIDFinished,
                FieldIDMemberInfoList,

                FieldIDMax,
            };

            enum MethodID{
                MethodIDConstructor = 0,
                MethodIDAddMemberInfo,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
}

#endif //IMCPLUSPLUSDEMO_GROUP_MESSAGE_READ_MEMBER_LIST_JNI_H
