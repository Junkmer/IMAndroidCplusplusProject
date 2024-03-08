//
// Created by Junker on 2022/8/26.
//

#ifndef IMCPLUSPLUSDEMO_IM_CALLBAK_JNI_H
#define IMCPLUSPLUSDEMO_IM_CALLBAK_JNI_H

#include <jni.h>
#include <string>

#include "../../include/V2TIMCallback.h"

namespace v2im {
    namespace jni {
        class IMCallbackJNI {

        public:
            static bool InitIDs(JNIEnv *env);

            static void Success(const jobject &callback, const jobject &obj);
            static void Fail(const jobject &callback, const int &code, const std::string &desc);
            static void FailOrComplete(const jobject &callback, const int &code, const std::string &desc, const jobject &params);
            static void Progress(const jobject &callback, const int &progress);
            static void DownloadProgress(const jobject &callback, const uint64_t &currentSize,const uint64_t &totalSize);

        private:
            enum MethodID {
                MethodIDSuccess = 0,
                MethodIDFail,
                MethodIDFailOrComplete,
                MethodIDProgress,
                MethodIDDownloadProgress,

                MethodIDMax,
            };
        public:
            static jclass j_cls_callback;
            static jmethodID j_method_id_array[MethodIDMax];
        };
    } // namespace jni
} // namespace v2im

#endif //IMCPLUSPLUSDEMO_IM_CALLBAK_JNI_H

