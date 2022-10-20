//
// Created by EDY on 2022/9/30.
//

#ifndef IMCPLUSPLUSDEMO_FRIEND_APPLICATION_RESULT_JNI_H
#define IMCPLUSPLUSDEMO_FRIEND_APPLICATION_RESULT_JNI_H

#include <jni.h>
#include "V2TIMFriendship.h"

namespace v2im {
    namespace jni {
        class FriendApplicationResultJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMFriendApplicationResult &applicationResult);

        private:
            enum FieldID{
                FieldIDUnreadCount = 0,
                FieldIDFriendApplicationList,

                FieldIDMax,
            };

            enum MethodID{
                MethodIDConstructor = 0,
                MethodIDAddFriendApplication,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }// namespace jni
}// namespace v2im


#endif //IMCPLUSPLUSDEMO_FRIEND_APPLICATION_RESULT_JNI_H
