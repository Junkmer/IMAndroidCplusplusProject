//
// Created by EDY on 2022/9/29.
//

#ifndef IMCPLUSPLUSDEMO_CONVERSATION_RESULT_JNI_H
#define IMCPLUSPLUSDEMO_CONVERSATION_RESULT_JNI_H

#include <jni.h>
#include "V2TIMConversation.h"

namespace v2im {
    namespace jni {
        class ConversationResultJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMConversationResult &conversationResult);

        private:
            enum FieldID{
                FieldIDNextSeq = 0,
                FieldIDIsFinished,
                FieldIDConversationList,

                FieldIDMax,
            };

            enum MethodID{
                MethodIDConstructor = 0,
                MethodIDAddConversation,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
}

#endif //IMCPLUSPLUSDEMO_CONVERSATION_RESULT_JNI_H
