//
// Created by Junker on 2022/9/24.
//

#ifndef IMCPLUSPLUSDEMO_GROUP_AT_INFO_JNI_H
#define IMCPLUSPLUSDEMO_GROUP_AT_INFO_JNI_H

#include <jni.h>
#include "V2TIMMessage.h"

namespace v2im {
    namespace jni {
        class GroupAtInfoJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMGroupAtInfo &groupAtInfo);
            static bool Convert2CoreObject(const jobject &object, V2TIMGroupAtInfo &groupAtInfo);

        private:
            enum FieldID {
                FieldIDSeq = 0,
                FieldIDAtType,

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
    }
}

#endif //IMCPLUSPLUSDEMO_GROUP_AT_INFO_JNI_H
