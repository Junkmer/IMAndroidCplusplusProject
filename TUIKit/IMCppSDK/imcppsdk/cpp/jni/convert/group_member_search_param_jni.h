//
// Created by EDY on 2022/9/30.
//

#ifndef IMCPLUSPLUSDEMO_GROUP_MEMBER_SEARCH_PARAM_JNI_H
#define IMCPLUSPLUSDEMO_GROUP_MEMBER_SEARCH_PARAM_JNI_H

#include <jni.h>
#include "V2TIMGroup.h"

namespace v2im {
    namespace jni {
        class GroupMemberSearchParamJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static bool Convert2CoreObject(const jobject &j_obj_memberSearchParam,V2TIMGroupMemberSearchParam &memberSearchParam);

        private:
            enum FieldID{
                FieldIDGroupIDList = 0,
                FieldIDKeywordList,
                FieldIDIsSearchMemberUserID,
                FieldIDIsSearchMemberNickName,
                FieldIDIsSearchMemberRemark,
                FieldIDIsSearchMemberNameCard,

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

#endif //IMCPLUSPLUSDEMO_GROUP_MEMBER_SEARCH_PARAM_JNI_H
