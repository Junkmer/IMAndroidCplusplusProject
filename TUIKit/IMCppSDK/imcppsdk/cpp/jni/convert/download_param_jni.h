//
// Created by EDY on 2022/10/18.
//

#ifndef IMCPLUSPLUSDEMO_DOWNLOAD_PARAM_JNI_H
#define IMCPLUSPLUSDEMO_DOWNLOAD_PARAM_JNI_H

#include <jni.h>
#include "V2TIMString.h"

class DownloadParam {
public:
    V2TIMString roleTypeID;//群消息就是 groupID，C2C消息就是对方的 userID
    V2TIMString messageID;
    uint64_t sequence;
    uint32_t elemType;

public:
    DownloadParam() = default;
    DownloadParam(const DownloadParam &) = default;
    ~DownloadParam() = default;
};

namespace v2im {
    namespace jni {
        class DownloadParamJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static jobject Convert2JObject(const DownloadParam &param);
            static bool Convert2CoreObject(const jobject &j_obj_param, DownloadParam &param);

        private:
            enum FieldID {
                FieldIDRoleTypeID,
                FieldIDMessageID,
                FieldIDSequence,
                FieldIDElemType,

                FieldIDMax,
            };

            enum MethodID {
                MethodIDConstructor = 0,

                MethodIDMax,
            };

            static jclass j_cls_;
            static jfieldID j_field_array_[FieldIDMax];
            static jmethodID j_method_id_array_[MethodIDMax];
        };
    }
}

#endif //IMCPLUSPLUSDEMO_DOWNLOAD_PARAM_JNI_H
