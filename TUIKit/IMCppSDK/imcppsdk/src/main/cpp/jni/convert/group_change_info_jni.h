//
// Created by Junker on 2022/9/22.
//

#ifndef IMCPLUSPLUSDEMO_GROUP_CHANGE_INFO_JNI_H
#define IMCPLUSPLUSDEMO_GROUP_CHANGE_INFO_JNI_H

#include <jni.h>
#include "V2TIMMessage.h"

namespace v2im {
    namespace jni {
        class GroupChangeInfoJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMGroupChangeInfo &groupChangeInfo);

        private:
            enum FieldID {
                FieldIDType = 0,
                FieldIDValue,
                FieldIDBoolValue,
                FieldIDIntValue,
                FieldIDKey,

                FieldIDMax,
            };

            enum MethodID {
                MethodIDConstruct = 0,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_id_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }// namespace jni
}// namespace v2im

#endif //IMCPLUSPLUSDEMO_GROUP_CHANGE_INFO_JNI_H
