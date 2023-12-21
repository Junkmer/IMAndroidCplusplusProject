//
// Created by EDY on 2024/1/15.
//

#ifndef IMANDROIDCPLUSPLUSDEMO_MESSAGE_REACTION_CHANGE_INFO_JNI_H
#define IMANDROIDCPLUSPLUSDEMO_MESSAGE_REACTION_CHANGE_INFO_JNI_H

#include <jni.h>
#include "V2TIMMessage.h"

namespace v2im {
    namespace jni{
        class MessageReactionChangeInfoJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMMessageReactionChangeInfo &reactionChangeInfo);

        private:
            enum FieldID {
                FieldIDMessageID = 0,
                FieldIDReactionList,

                FieldIDMax,
            };

            enum MethodID {
                MethodIDConstruct = 0,

                MethodIDMax,
            };

            static jclass j_cls;
            static jfieldID j_field_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
} // v2im

#endif //IMANDROIDCPLUSPLUSDEMO_MESSAGE_REACTION_CHANGE_INFO_JNI_H
