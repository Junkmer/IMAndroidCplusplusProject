//
// Created by Junker on 2022/10/4.
//

#ifndef IMCPLUSPLUSDEMO_GROUP_SEARCH_PARAM_H
#define IMCPLUSPLUSDEMO_GROUP_SEARCH_PARAM_H

#include <jni.h>
#include "V2TIMGroup.h"

namespace v2im {
    namespace jni {
        class GroupSearchParam {
        public:
            static bool InitIDs(JNIEnv *env);
            static bool Convert2CoreObject(const jobject &j_obj_groupSearchParam,V2TIMGroupSearchParam &groupSearchParam);

        private:
            enum FieldID{
                FieldIDKeywordList = 0,
                FieldIDIsSearchGroupID,
                FieldIDIsSearchGroupName,

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

#endif //IMCPLUSPLUSDEMO_GROUP_SEARCH_PARAM_H
