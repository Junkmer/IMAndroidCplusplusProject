//
// Created by EDY on 2022/8/23.
//

#ifndef IMCPLUSPLUSDEMO_JNI_HELPER_H
#define IMCPLUSPLUSDEMO_JNI_HELPER_H

#include <jni.h>
#include <string>
#include <pthread.h>

namespace v2im {
    namespace jni {

        class JniHelper {
            friend class ScopedJEnv;

        public:
            static bool Init(JavaVM *jvm);

            static void UnInit();

            static JavaVM *GetJVM();

            static bool CheckAndClearException(JNIEnv *env);

            static void DumpReferenceTables(JNIEnv *env);

        private:
            static JavaVM *sJvm;
            static pthread_key_t sKey;
        };

        class ScopedJEnv {
        public:
            explicit ScopedJEnv(jint capacity = 16);

            ~ScopedJEnv();

            JNIEnv *GetEnv() const;

            bool CheckAndClearException() const;

        private:
            JNIEnv *env_;
        };

    }  // namespace jni
}  // namespace v2im

#endif //IMCPLUSPLUSDEMO_JNI_HELPER_H
