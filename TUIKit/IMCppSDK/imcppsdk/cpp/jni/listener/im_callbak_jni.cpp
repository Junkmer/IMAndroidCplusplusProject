//
// Created by Junker on 2022/8/26.
//

#include "im_callbak_jni.h"

#include "../basic/jni_util.h"
#include "../basic/jni_helper.h"
#include "../util/LogUtil.h"
#include "java_basic_jni.h"

namespace v2im {
    namespace jni {
        jclass v2im::jni::IMCallbackJNI::j_cls_callback;

        jmethodID IMCallbackJNI::j_method_id_array[MethodIDMax];

        bool IMCallbackJNI::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_callback) {
                return true;
            }

            jmethodID j_method = nullptr;
            jclass cls = nullptr;

            //--------------------------- java IMCallback ---------------------------
            cls = env->FindClass("com/tencent/imsdk/common/IMCallback");
            if (cls == nullptr) {
                return false;
            }

            j_cls_callback = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            j_method = env->GetMethodID(j_cls_callback, "success", "(Ljava/lang/Object;)V");
            if (j_method == nullptr) {
                return false;
            }
            j_method_id_array[MethodIDSuccess] = j_method;

            j_method = env->GetMethodID(j_cls_callback, "fail", "(ILjava/lang/String;)V");
            if (j_method == nullptr) {
                return false;
            }
            j_method_id_array[MethodIDFail] = j_method;

            j_method = env->GetMethodID(j_cls_callback, "failOrComplete", "(ILjava/lang/String;Ljava/lang/Object;)V");
            if (j_method == nullptr) {
                return false;
            }
            j_method_id_array[MethodIDFailOrComplete] = j_method;

            j_method = env->GetMethodID(j_cls_callback, "progress", "(I)V");
            if (j_method == nullptr) {
                return false;
            }
            j_method_id_array[MethodIDProgress] = j_method;

            j_method = env->GetMethodID(j_cls_callback, "downloadProgress", "(JJ)V");
            if (j_method == nullptr) {
                return false;
            }
            j_method_id_array[MethodIDDownloadProgress] = j_method;
            return true;
        }

        void IMCallbackJNI::Success(const jobject &callback, const jobject &obj) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return;
            }

            env->CallVoidMethod(callback, j_method_id_array[MethodIDSuccess], obj);
        }

        void IMCallbackJNI::Fail(const jobject &callback, const int &code, const std::string &desc) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return;
            }

            env->CallVoidMethod(callback, j_method_id_array[MethodIDFail], code, StringJni::Cstring2Jstring(env, desc));
        }

        void IMCallbackJNI::FailOrComplete(const jobject &callback, const int &code, const std::string &desc, const jobject &params) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return;
            }

            env->CallVoidMethod(callback, j_method_id_array[MethodIDFailOrComplete], code, StringJni::Cstring2Jstring(env, desc), params);
        }

        void IMCallbackJNI::Progress(const jobject &callback, const int &progress) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return;
            }

            env->CallVoidMethod(callback, j_method_id_array[MethodIDProgress], progress);
        }

        void IMCallbackJNI::DownloadProgress(const jobject &callback, const uint64_t &currentSize, const uint64_t &totalSize) {
            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return;
            }

            env->CallVoidMethod(callback, j_method_id_array[MethodIDDownloadProgress], (jlong) currentSize, (jlong) totalSize);
        }

    } // namespace jni
} // namespace v2im
