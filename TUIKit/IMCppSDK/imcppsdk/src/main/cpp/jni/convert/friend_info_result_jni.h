//
// Created by EDY on 2022/9/30.
//

#ifndef IMCPLUSPLUSDEMO_FRIEND_INFO_RESULT_JNI_H
#define IMCPLUSPLUSDEMO_FRIEND_INFO_RESULT_JNI_H

#include <jni.h>
#include "V2TIMFriendship.h"

namespace v2im {
    namespace jni {
        class FriendInfoResultJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMFriendInfoResult &friendInfoResult);

        private:
            enum FieldID{
                FieldIDResultCode = 0,
                FieldIDResultInfo,
                FieldIDRelation,
                FieldIDFriendInfo,

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

#endif //IMCPLUSPLUSDEMO_FRIEND_INFO_RESULT_JNI_H
