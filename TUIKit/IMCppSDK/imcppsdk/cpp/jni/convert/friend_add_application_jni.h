//
// Created by EDY on 2022/9/30.
//

#ifndef IMCPLUSPLUSDEMO_FRIEND_ADD_APPLICATION_JNI_H
#define IMCPLUSPLUSDEMO_FRIEND_ADD_APPLICATION_JNI_H

#include <jni.h>
#include "V2TIMFriendship.h"
#include <jni_helper.h>
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        class FriendAddApplicationJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static bool Convert2CoreObject(const jobject &j_obj_addApplication, V2TIMFriendAddApplication &addApplication);

        private:
            enum FieldID{
                FieldIDUserID = 0,
                FieldIDRemark,
                FieldIDFriendGroup,
                FieldIDAddWording,
                FieldIDAddSource,
                FieldIDAddType,

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

#endif //IMCPLUSPLUSDEMO_FRIEND_ADD_APPLICATION_JNI_H
