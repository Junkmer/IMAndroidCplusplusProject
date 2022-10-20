//
// Created by EDY on 2022/9/30.
//

#ifndef IMCPLUSPLUSDEMO_FRIEND_SEARCH_PARAM_JNI_H
#define IMCPLUSPLUSDEMO_FRIEND_SEARCH_PARAM_JNI_H

#include <jni.h>
#include "V2TIMFriendship.h"
#include <jni_helper.h>
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        class FriendSearchParamJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static bool Convert2CoreObject(const jobject &j_obj_searchParam, V2TIMFriendSearchParam &searchParam);

        private:
            enum FieldID{
                FieldIDKeywordList = 0,
                FieldIDIsSearchUserID,
                FieldIDIsSearchNickName,
                FieldIDIsSearchRemark,

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

#endif //IMCPLUSPLUSDEMO_FRIEND_SEARCH_PARAM_JNI_H
