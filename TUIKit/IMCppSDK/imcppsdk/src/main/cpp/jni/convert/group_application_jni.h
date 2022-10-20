//
// Created by EDY on 2022/9/30.
//

#ifndef IMCPLUSPLUSDEMO_GROUP_APPLICATION_JNI_H
#define IMCPLUSPLUSDEMO_GROUP_APPLICATION_JNI_H

#include <jni.h>
#include "V2TIMGroup.h"

namespace v2im {
    namespace jni {
        class GroupApplicationJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMGroupApplication &groupApplication);
            static bool Convert2CoreObject(const jobject &j_obj_groupApplication,V2TIMGroupApplication &groupApplication);

        private:
            enum FieldID{
                FieldIDGroupID = 0,
                FieldIDFromUser,
                FieldIDFromUserNickName,
                FieldIDFromUserFaceUrl,
                FieldIDToUser,
                FieldIDAddTime,
                FieldIDRequestMsg,
                FieldIDHandledMsg,
                FieldIDType,
                FieldIDHandleStatus,
                FieldIDHandleResult,

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
    }//namespace jni
}//namespace v2im


#endif //IMCPLUSPLUSDEMO_GROUP_APPLICATION_JNI_H
