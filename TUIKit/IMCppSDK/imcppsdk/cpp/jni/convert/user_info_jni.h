//
// Created by EDY on 2023/11/2.
//

#ifndef IMCSDKDEMO_USER_INFO_JNI_H
#define IMCSDKDEMO_USER_INFO_JNI_H

#include <jni.h>
#include "V2TIMManager.h"

namespace v2im {
    namespace jni {
        class UserInfoJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMUserInfo &userInfo_obj);

        private:
            enum FieldID {
                FieldIDUserID = 0,
                FieldIDNickname,
                FieldIDFaceUrl,
                FieldIDBirthday,

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

#endif //IMCSDKDEMO_USER_INFO_JNI_H
