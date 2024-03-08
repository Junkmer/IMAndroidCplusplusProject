//
// Created by Junker on 2022/8/22.
//

#ifndef IMCPLUSPLUSDEMO_SDK_CONFIG_JNI_H
#define IMCPLUSPLUSDEMO_SDK_CONFIG_JNI_H

#include <jni.h>

#include "V2TIMCommon.h"


namespace v2im {
    namespace jni {

        class SDKConfigJni {
        public:
            static bool InitIDs(JNIEnv *env);
            static V2TIMSDKConfig ConvertToCoreObject(JNIEnv *env,const jobject &object);

        private:
            enum MethodID {
                MethodIDConstruct = 0,

                MethodIDMax,
            };

            static jclass jcls_;
            static jmethodID j_method_id_array_[MethodIDMax];
        };

    } // namespace v2im
} // namespace jni


#endif //IMCPLUSPLUSDEMO_SDK_CONFIG_JNI_H
