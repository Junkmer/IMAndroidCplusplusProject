//
// Created by Junker on 2022/9/29.
//

#ifndef IMCPLUSPLUSDEMO_CONVERSATION_LIST_FILTER_JNI_H
#define IMCPLUSPLUSDEMO_CONVERSATION_LIST_FILTER_JNI_H

#include <jni.h>
#include "V2TIMConversation.h"

namespace v2im {
    namespace jni {
        class ConversationListFilterJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMConversationListFilter &listFilter);
            static bool Convert2CoreObject(const jobject &filterObj,V2TIMConversationListFilter &listFilter);

        private:
            enum FieldID{
                FieldIDConversationType = 0,
                FieldIDConversationGroup,
                FieldIDMarkType,
                FieldIDHasUnreadCount,
                FieldIDHasGroupAtInfo,


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

#endif //IMCPLUSPLUSDEMO_CONVERSATION_LIST_FILTER_JNI_H
