//
// Created by EDY on 2022/10/8.
//

#ifndef IMCPLUSPLUSDEMO_MESSAGE_SEARCH_RESULT_JNI_H
#define IMCPLUSPLUSDEMO_MESSAGE_SEARCH_RESULT_JNI_H

#include <jni.h>
#include "V2TIMMessage.h"

namespace v2im {
    namespace jni {
        class MessageSearchResultJni{
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMMessageSearchResult &searchResult);

        private:
            enum FieldID{
                FieldIDTotalCount = 0,
                FieldIDMessageSearchResultItems,

                FieldIDMax,
            };

            enum MethodID{
                MethodIDConstructor = 0,
                MethodIDAddMessageSearchResultItem,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
}

#endif //IMCPLUSPLUSDEMO_MESSAGE_SEARCH_RESULT_JNI_H
