//
// Created by EDY on 2022/9/19.
//

#ifndef IMCPLUSPLUSDEMO_GROUP_MEMBER_FULL_INFO_JNI_H
#define IMCPLUSPLUSDEMO_GROUP_MEMBER_FULL_INFO_JNI_H

#include <jni.h>
#include "V2TIMGroup.h"

namespace v2im {
    namespace jni {
        class GroupMemberFullInfoJNI {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMGroupMemberFullInfo &memberFullInfo);
            static bool Convert2CoreObject(const jobject &j_obj_groupSearchParam,V2TIMGroupMemberFullInfo &memberFullInfo);

        private:
            enum FieldID {
                FieldIDUserID = 0,
                FieldIDNickName,
                FieldIDFriendRemark,
                FieldIDFaceUrl,
                FieldIDRole,
                FieldIDMuteUntil,
                FieldIDJoinTime,
                FieldIDCustomInfo,
                FieldIDModifyFlag,

                FieldIDMax,
            };

            enum MethodID {
                MethodIDConstruct = 0,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
}

#endif //IMCPLUSPLUSDEMO_GROUP_MEMBER_FULL_INFO_JNI_H
