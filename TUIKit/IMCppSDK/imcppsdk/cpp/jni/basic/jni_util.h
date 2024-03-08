//
// Created by Junker on 2022/8/22.
//

#ifndef IMCPLUSPLUSDEMO_JNI_UTIL_H
#define IMCPLUSPLUSDEMO_JNI_UTIL_H

#include <jni.h>

#include <map>
#include <string>

namespace v2im {
    namespace jni {
        namespace util {
            // 从 Java 对象 Object 读取 int 类型的成员变量 field_name
            int getIntValue(JNIEnv *env, jclass j_cls, jobject j_obj, const char *field_name);

            // 从 Java 对象 Object 读取 long 类型的成员变量 field_name
            long getLongValue(JNIEnv *env, jclass j_cls, jobject j_obj, const char *field_name);

            // 从 Java 对象 Object 读取 bool 类型的成员变量 field_name
            bool getBoolValue(JNIEnv *env, jclass j_cls, jobject j_obj, const char *field_name);

            // 从 Java 对象 Object 读取 string 类型的成员变量 field_name
            std::string getStringValue(JNIEnv *env, jclass j_cls, jobject j_obj, const char *field_name);

            // 从 Java 对象 Object 读取 object 类型的成员变量 field_name
            jobject getObjectValue(JNIEnv *env, jclass j_cls, jobject j_obj, const char *field_name);

            //注册 native 方法到 java 中
            int RegisterNativeMethods(JNIEnv *env, const char *className, JNINativeMethod *gMethods, int numMethods);

        }// namespace util
    }// namespace jni
}// namespace v2im

class jni_util {

};


#endif //IMCPLUSPLUSDEMO_JNI_UTIL_H
