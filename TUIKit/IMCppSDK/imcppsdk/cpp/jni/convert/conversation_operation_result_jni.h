//
// Created by Junker on 2022/9/29.
//

#ifndef IMCPLUSPLUSDEMO_CONVERSATION_OPERATION_RESULT_JNI_H
#define IMCPLUSPLUSDEMO_CONVERSATION_OPERATION_RESULT_JNI_H

#include <jni.h>
#include "V2TIMConversation.h"

namespace v2im {
    namespace jni {
        class ConversationOperationResultJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMConversationOperationResult &operationResult);

        private:
            enum FieldID{
                FieldIDConversationID = 0,
                FieldIDResultCode,
                FieldIDResultInfo,

                FieldIDMax,
            };

            enum MethodID{
                MethodIDConstructor = 0,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
}

#endif //IMCPLUSPLUSDEMO_CONVERSATION_OPERATION_RESULT_JNI_H
