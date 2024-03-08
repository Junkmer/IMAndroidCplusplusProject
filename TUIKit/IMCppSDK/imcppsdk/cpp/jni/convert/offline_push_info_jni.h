//
// Created by EDY on 2022/9/23.
//

#ifndef IMCPLUSPLUSDEMO_OFFLINE_PUSH_INFO_JNI_H
#define IMCPLUSPLUSDEMO_OFFLINE_PUSH_INFO_JNI_H

#include <jni.h>
#include "V2TIMMessage.h"

namespace v2im{
    namespace jni {
        class OfflinePushInfoJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMOfflinePushInfo &offlinePushInfo);
            static bool Convert2CoreObject(const jobject &object, V2TIMOfflinePushInfo &offlinePushInfo);

        private:
            enum FieldID{
                FieldIDTitle = 0,
                FieldIDDesc,
                FieldIDExt,
                FieldIDDisable,
                FieldIDIOSSound,
                FieldIDAndroidSound,
                FieldIDIgnoreIOSBadge,
                FieldIDOppoChannelID,
                FieldIDFcmChannelID,
                FieldIDXiaomiChannelID,
                FieldIDVivoClassification,
                FieldIDVivoCategory,
                FieldIDIOSPushType,
                FieldIDHuaweiCategory,

                FieldIDMax
            };

            enum MethodID {
                MethodIDConstructor = 0,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }// namespace jni
}// namespace v2im


#endif //IMCPLUSPLUSDEMO_OFFLINE_PUSH_INFO_JNI_H
