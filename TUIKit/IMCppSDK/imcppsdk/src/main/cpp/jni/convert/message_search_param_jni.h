//
// Created by EDY on 2022/10/8.
//

#ifndef IMCPLUSPLUSDEMO_MESSAGE_SEARCH_PARAM_JNI_H
#define IMCPLUSPLUSDEMO_MESSAGE_SEARCH_PARAM_JNI_H

#include <jni.h>
#include "V2TIMMessage.h"

namespace v2im {
    namespace jni {
        class MessageSearchParamJni{
        public:
            static bool InitIDs(JNIEnv *env);
            static bool Convert2CoreObject(const jobject &j_obj_searchParam,V2TIMMessageSearchParam &searchParam);

        private:
            enum FieldID{
                FieldIDConversationID = 0,
                FieldIDKeywordList,
                FieldIDKeywordListMatchType,
                FieldIDSenderUserIDList,
                FieldIDMessageTypeList,
                FieldIDSearchTimePosition,
                FieldIDSearchTimePeriod,
                FieldIDPageSize,
                FieldIDPageIndex,
                FieldIDSearchCount,
                FieldIDSearchCursor,

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

#endif //IMCPLUSPLUSDEMO_MESSAGE_SEARCH_PARAM_JNI_H
