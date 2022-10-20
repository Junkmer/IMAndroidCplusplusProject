//
// Created by EDY on 2022/9/28.
//

#ifndef IMCPLUSPLUSDEMO_FRIEND_APPLICATION_JNI_H
#define IMCPLUSPLUSDEMO_FRIEND_APPLICATION_JNI_H

#include <jni.h>
#include "V2TIMFriendship.h"

namespace v2im {
    namespace jni {
        class FriendApplicationJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMFriendApplication &application);
            static bool Convert2CoreObject(const jobject &j_obj_application,V2TIMFriendApplication &application);

        private:
            enum FieldID {
                FieldIDUserID = 0,
                FieldIDuserID,
                FieldIDNickname,
                FieldIDFaceUrl,
                FieldIDAddTime,
                FieldIDAddSource,
                FieldIDAddWording,
                FieldIDType,

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

#endif //IMCPLUSPLUSDEMO_FRIEND_APPLICATION_JNI_H
