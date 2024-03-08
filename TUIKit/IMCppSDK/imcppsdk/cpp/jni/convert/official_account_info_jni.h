//
// Created by EDY on 2024/1/15.
//

#ifndef IMANDROIDCPLUSPLUSDEMO_OFFICIAL_ACCOUNT_INFO_JNI_H
#define IMANDROIDCPLUSPLUSDEMO_OFFICIAL_ACCOUNT_INFO_JNI_H

#include <jni.h>
#include "V2TIMFriendshipManager.h"

namespace v2im {
    namespace jni{
        class OfficialAccountInfoJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const V2TIMOfficialAccountInfo &accountInfo_obj);

        private:
            enum FieldID {
                FieldIDOfficialAccountID = 0,
                FieldIDOfficialAccountName,
                FieldIDFaceUrl,
                FieldIDOwnerUserID,
                FieldIDOrganization,
                FieldIDIntroduction,
                FieldIDCustomData,
                FieldIDCreateTime,
                FieldIDSubscriberCount,
                FieldIDSubscribeTime,

                FieldIDMax,
            };

            enum MethodID {
                MethodIDConstruct = 0,

                MethodIDMax,
            };

            static jclass j_cls;
            static jfieldID j_field_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
} // v2im

#endif //IMANDROIDCPLUSPLUSDEMO_OFFICIAL_ACCOUNT_INFO_JNI_H
