//
// Created by EDY on 2022/9/28.
//

#ifndef IMCPLUSPLUSDEMO_FRIEND_INFO_JNI_H
#define IMCPLUSPLUSDEMO_FRIEND_INFO_JNI_H

#include <jni.h>
#include "V2TIMFriendship.h"

namespace v2im {
    namespace jni {
        class FriendInfoJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMFriendInfo &friendInfo);
            static bool Convert2CoreObject(const jobject &j_obj_friendInfo, V2TIMFriendInfo &friendInfo);

        private:
            enum FieldID {
                FieldIDUserID = 0,
                FieldIDFriendRemark,
                FieldIDFriendAddTime,
                FieldIDFriendGroups,
                FieldIDFriendCustomInfo,
                FieldIDUserFullInfo,

                FieldIDMax,
            };

            enum MethodID {
                MethodIDConstruct = 0,
                MethodIDAddFriendGroup,
                MethodIDPutFriendCustomInfo,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_id_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }// namespace v2im
}// namespace jni


#endif //IMCPLUSPLUSDEMO_FRIEND_INFO_JNI_H
