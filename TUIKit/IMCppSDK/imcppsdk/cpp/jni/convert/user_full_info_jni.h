//
// Created by EDY on 2022/9/16.
//

#ifndef IMCPLUSPLUSDEMO_USER_FULL_INFO_JNI_H
#define IMCPLUSPLUSDEMO_USER_FULL_INFO_JNI_H

#include <jni.h>
#include "V2TIMFriendship.h"

namespace v2im {
    namespace jni {
        class UserFullInfoJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMUserFullInfo &userFullInfo);
            static bool Convert2CoreObject(const jobject &j_obj_userFullInfo,V2TIMUserFullInfo &userFullInfo);

        private:
            enum FieldID {
                FieldIDUserID = 0,
                FieldIDNickname,
                FieldIDFaceUrl,
                FieldIDSelfSignature,
                FieldIDGender,
                FieldIDRole,
                FieldIDLevel,
                FieldIDBirthday,
                FieldIDAllowType,
                FieldIDCustomHashMap,

                FieldIDMax
            };

            enum MethodID {
                MethodIDConstruct = 0,

                MethodIDMax,
            };

            static jclass j_cls;
            static jfieldID j_field_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
}

#endif //IMCPLUSPLUSDEMO_USER_FULL_INFO_JNI_H
