//
// Created by EDY on 2022/10/8.
//

#ifndef IMCPLUSPLUSDEMO_RECEIVE_MESSAGE_OPT_INFO_JNI_H
#define IMCPLUSPLUSDEMO_RECEIVE_MESSAGE_OPT_INFO_JNI_H

#include <jni.h>
#include "V2TIMMessage.h"

namespace v2im {
    namespace jni {
        class ReceiveMessageOptInfoJni{
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMReceiveMessageOptInfo &messageOptInfo);

        private:
            enum FieldID{
                FieldIDC2CReceiveMessageOpt = 0,
                FieldIDUserID,

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
    }// namespace jni
}// namespace v2im

#endif //IMCPLUSPLUSDEMO_RECEIVE_MESSAGE_OPT_INFO_JNI_H
