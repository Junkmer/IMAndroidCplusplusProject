//
// Created by EDY on 2022/9/30.
//

#ifndef IMCPLUSPLUSDEMO_OFFLINE_PUSH_CONFIG_JNI_H
#define IMCPLUSPLUSDEMO_OFFLINE_PUSH_CONFIG_JNI_H

#include <jni.h>
#include "V2TIMMessage.h"

namespace v2im {
    namespace jni {
        class OfflinePushConfigJni{
        public:
            static bool InitIDs(JNIEnv *env);
            static bool Convert2CoreObject(const jobject &pushConfigObj,V2TIMOfflinePushConfig &pushConfig);

        private:
            enum FieldID{
                FieldIDBusinessID = 0,
                FieldIDToken,
                FieldIDIsTPNSToken,

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

#endif //IMCPLUSPLUSDEMO_OFFLINE_PUSH_CONFIG_JNI_H
