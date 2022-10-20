//
// Created by EDY on 2022/9/21.
//

#include <LogUtil.h>
#include "elem_handler_jni.h"
#include "jni_helper.h"
#include "java_basic_jni.h"
#include "image_jni.h"

namespace v2im {
    namespace jni {
        IElemHandler::~IElemHandler() {
            if (j_cls_) {
                ScopedJEnv scopedJEnv;
                scopedJEnv.GetEnv()->DeleteGlobalRef(j_cls_);
                j_cls_ = nullptr;
            }
        }

//////////////////////////////////////////// V2TIMTextElem   ////////////////////////////////////////////

        std::string TextElemHandler::GetHandlerType() {
            return "TextElemHandler";
        }

        bool TextElemHandler::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMTextElem");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[BaseElemConstructor] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "text", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[TextFieldText] = jfield;

            return true;
        }

        jobject TextElemHandler::Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) {
            if (!elem || elem->elemType != V2TIMElemType::V2TIM_ELEM_TYPE_TEXT) {
                return nullptr;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            auto *textElem = (V2TIMTextElem *) elem;

            jobject jElemObj = env->NewObject(j_cls_, j_method_id_array_[BaseElemConstructor]);
            if (nullptr == jElemObj) {
                return nullptr;
            }

            size_t len = 0;

            len = textElem->text.Size();
            if (len > 0) {
                jstring textJStr = StringJni::Cstring2Jstring(env, textElem->text.CString());
                env->SetObjectField(jElemObj, j_field_array_[TextFieldText], textJStr);
                env->DeleteLocalRef(textJStr);
            }
            return jElemObj;
        }

        std::unique_ptr<V2TIMElem> TextElemHandler::Convert2CoreObject(int elemType, jobject jElemObj) {
            if (V2TIMElemType(elemType) != V2TIMElemType::V2TIM_ELEM_TYPE_TEXT || !jElemObj) {
                return nullptr;
            }

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            V2TIMTextElem textElem;

            auto jstr = (jstring) env->GetObjectField(jElemObj, j_field_array_[TextFieldText]);
            if (jstr) {
                textElem.text = StringJni::Jstring2Cstring(env, jstr).c_str();
                env->DeleteLocalRef(jstr);
            }

            return std::make_unique<V2TIMTextElem>(textElem);
        }

//////////////////////////////////////////// V2TIMCustomElem ////////////////////////////////////////////

        std::string CustomElemHandler::GetHandlerType() {
            return "CustomElemHandler";
        }

        bool CustomElemHandler::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMCustomElem");
            if (nullptr == cls) {
                return false;
            }

            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[BaseElemConstructor] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "data", "[B");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[CustomFieldData] = jfield;

            jfield = env->GetFieldID(j_cls_, "description", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[CustomFieldDescription] = jfield;

            jfield = env->GetFieldID(j_cls_, "extension", "[B");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[CustomFieldExtension] = jfield;

            return true;
        }

        jobject CustomElemHandler::Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) {
            if (!elem || elem->elemType != V2TIMElemType::V2TIM_ELEM_TYPE_CUSTOM) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            auto *customElem = (V2TIMCustomElem *) elem;

            jobject jElemOjb = env->NewObject(j_cls_, j_method_id_array_[BaseElemConstructor]);
            if (!jElemOjb) {
                return nullptr;
            }

            size_t len = 0;

            len = customElem->data.Size();
            if (len > 0) {
                jbyteArray byteArr = ByteJni::Cuint8_t2JByteArray(env, customElem->data.Data(), customElem->data.Size());
                env->SetObjectField(jElemOjb, j_field_array_[CustomFieldData], byteArr);
                env->DeleteLocalRef(byteArr);
            }

            len = customElem->desc.Size();
            if (len > 0) {
                jstring str = StringJni::Cstring2Jstring(env, customElem->desc.CString());
                env->SetObjectField(jElemOjb, j_field_array_[CustomFieldDescription], str);
                env->DeleteLocalRef(str);
            }

            len = customElem->extension.Size();
            if (len > 0) {
                jbyteArray byteArr = StringJni::Cstring2JbyteArray(env, customElem->extension.CString());
                env->SetObjectField(jElemOjb, j_field_array_[CustomFieldExtension], byteArr);
                env->DeleteLocalRef(byteArr);
            }

            return jElemOjb;
        }

        std::unique_ptr<V2TIMElem> CustomElemHandler::Convert2CoreObject(int elemType, jobject jElemObj) {
            if (V2TIMElemType(elemType) != V2TIMElemType::V2TIM_ELEM_TYPE_CUSTOM || !jElemObj) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            V2TIMCustomElem customElem;

            auto byteArr = (jbyteArray) env->GetObjectField(jElemObj, j_field_array_[CustomFieldData]);
            if (byteArr) {
                customElem.data = ByteJni::JByteArray2V2TIMBuffer(env, byteArr);
                env->DeleteLocalRef(byteArr);
            }

            auto str = (jstring) env->GetObjectField(jElemObj, j_field_array_[CustomFieldDescription]);
            if (str) {
                customElem.desc = StringJni::Jstring2Cstring(env, str).c_str();
                env->DeleteLocalRef(str);
            }

            byteArr = (jbyteArray) env->GetObjectField(jElemObj, j_field_array_[CustomFieldExtension]);
            if (byteArr) {
                customElem.extension = StringJni::JbyteArray2Cstring(env, byteArr).c_str();
                env->DeleteLocalRef(byteArr);
            }
            return std::make_unique<V2TIMCustomElem>(customElem);
        }

//////////////////////////////////////////// V2TIMImageElem  ////////////////////////////////////////////

        std::string ImageElemHandler::GetHandlerType() {
            return "ImageElemHandler";
        }

        bool ImageElemHandler::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMImageElem");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[ImageMethodConstructor] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "addImage", "(Lcom/tencent/imsdk/v2/V2TIMImageElem$V2TIMImage;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[ImageMethodAddImage] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "path", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[ImageFieldPath] = jfield;

            jfield = env->GetFieldID(j_cls_, "imageList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[ImageFieldImageList] = jfield;

            return true;
        }

        jobject ImageElemHandler::Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) {
            if (!elem || elem->elemType != V2TIMElemType::V2TIM_ELEM_TYPE_IMAGE) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            auto *imageElem = (V2TIMImageElem *) elem;

            jobject jElemObj = env->NewObject(j_cls_, j_method_id_array_[ImageMethodConstructor]);
            if (!jElemObj) {
                return nullptr;
            }

            jstring str = StringJni::Cstring2Jstring(env, imageElem->path.CString());
            if (str) {
                env->SetObjectField(jElemObj, j_field_array_[ImageFieldPath], str);
                env->DeleteLocalRef(str);
            }

            for (int i = 0; i < imageElem->imageList.Size(); ++i) {
                jobject itemImg = ImageJni::Convert2JObject(env, imageElem->imageList[i],param);
                if (itemImg) {
                    env->CallVoidMethod(jElemObj, j_method_id_array_[ImageMethodAddImage], itemImg);
                    env->DeleteLocalRef(itemImg);
                }
            }

            return jElemObj;
        }

        std::unique_ptr<V2TIMElem> ImageElemHandler::Convert2CoreObject(int elemType, jobject jElemObj) {
            if (V2TIMElemType(elemType) != V2TIMElemType::V2TIM_ELEM_TYPE_IMAGE || !jElemObj) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            V2TIMImageElem imageElem;

            auto pathStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[ImageFieldPath]);
            if (pathStr) {
                imageElem.path = StringJni::Jstring2Cstring(env, pathStr).c_str();
                env->DeleteLocalRef(pathStr);
            }

            jobject imageList = env->GetObjectField(jElemObj, j_field_array_[ImageFieldImageList]);
            auto len = ArrayListJni::Size(imageList);
            for (int i = 0; i < len; ++i) {
                jobject item_obj = ArrayListJni::Get(imageList, i);
                if (nullptr == item_obj) {
                    continue;
                }
                V2TIMImage image;
                bool flag = ImageJni::Convert2CoreObject(item_obj,image);
                if (flag){
                    imageElem.imageList.PushBack(image);
                }

                env->DeleteLocalRef(item_obj);
            }
            env->DeleteLocalRef(imageList);

            return std::make_unique<V2TIMImageElem>(imageElem);
        }

//////////////////////////////////////////// V2TIMSoundElem  ////////////////////////////////////////////

        std::string SoundElemHandler::GetHandlerType() {
            return "SoundElemHandler";
        }

        bool SoundElemHandler::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMSoundElem");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[BaseElemConstructor] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "path", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[SoundFieldPath] = jfield;

            jfield = env->GetFieldID(j_cls_, "UUID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[SoundFieldUUID] = jfield;

            jfield = env->GetFieldID(j_cls_, "dataSize", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[SoundFieldDataSize] = jfield;

            jfield = env->GetFieldID(j_cls_, "duration", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[SoundFieldDuration] = jfield;

            jfield = env->GetFieldID(j_cls_, "param", "Lcom/tencent/imsdk/common/DownloadParam;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[SoundFieldDownloadParam] = jfield;

            return true;
        }

        jobject SoundElemHandler::Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) {
            if (!elem || elem->elemType != V2TIMElemType::V2TIM_ELEM_TYPE_SOUND) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            auto *soundElem = (V2TIMSoundElem *) elem;

            jobject jElemObj = env->NewObject(j_cls_, j_method_id_array_[BaseElemConstructor]);
            if (!jElemObj) {
                return nullptr;
            }

            env->SetObjectField(jElemObj, j_field_array_[SoundFieldPath], StringJni::Cstring2Jstring(env, soundElem->path.CString()));
            env->SetObjectField(jElemObj, j_field_array_[SoundFieldUUID], StringJni::Cstring2Jstring(env, soundElem->uuid.CString()));
            env->SetIntField(jElemObj, j_field_array_[SoundFieldDataSize], (jint) soundElem->dataSize);
            env->SetIntField(jElemObj, j_field_array_[SoundFieldDuration], (jint) soundElem->duration);

            jobject j_obj_param = DownloadParamJni::Convert2JObject(param);
            if (j_obj_param){
                env->SetObjectField(jElemObj,j_field_array_[SoundFieldDownloadParam], j_obj_param);
                env->DeleteLocalRef(j_obj_param);
            }

            return jElemObj;
        }

        std::unique_ptr<V2TIMElem> SoundElemHandler::Convert2CoreObject(int elemType, jobject jElemObj) {
            if (V2TIMElemType(elemType) != V2TIMElemType::V2TIM_ELEM_TYPE_SOUND || !jElemObj) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            V2TIMSoundElem soundElem;

            jstring jStr = nullptr;
            jStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[SoundFieldPath]);
            soundElem.path = StringJni::Jstring2Cstring(env, jStr).c_str();
            env->DeleteLocalRef(jStr);

            jStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[SoundFieldUUID]);
            soundElem.uuid = StringJni::Jstring2Cstring(env, jStr).c_str();
            env->DeleteLocalRef(jStr);

            soundElem.dataSize = (uint64_t) env->GetIntField(jElemObj, j_field_array_[SoundFieldDataSize]);
            soundElem.duration = (uint32_t) env->GetIntField(jElemObj, j_field_array_[SoundFieldDuration]);

            return std::make_unique<V2TIMSoundElem>(soundElem);
        }

//////////////////////////////////////////// V2TIMVideoElem  ////////////////////////////////////////////

        std::string VideoElemHandler::GetHandlerType() {
            return "VideoElemHandler";
        }

        bool VideoElemHandler::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMVideoElem");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;
            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[BaseElemConstructor] = jmethod;


            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "videoPath", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[VideoFieldVideoPath] = jfield;

            jfield = env->GetFieldID(j_cls_, "videoUUID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[VideoFieldVideoUUID] = jfield;

            jfield = env->GetFieldID(j_cls_, "videoSize", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[VideoFieldVideoSize] = jfield;

            jfield = env->GetFieldID(j_cls_, "duration", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[VideoFieldDuration] = jfield;

            jfield = env->GetFieldID(j_cls_, "snapshotPath", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[VideoFieldSnapshotPath] = jfield;

            jfield = env->GetFieldID(j_cls_, "snapshotUUID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[VideoFieldSnapshotUUID] = jfield;

            jfield = env->GetFieldID(j_cls_, "snapshotSize", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[VideoFieldSnapshotSize] = jfield;

            jfield = env->GetFieldID(j_cls_, "snapshotWidth", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[VideoFieldSnapshotWidth] = jfield;

            jfield = env->GetFieldID(j_cls_, "snapshotHeight", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[VideoFieldSnapshotHeight] = jfield;

            jfield = env->GetFieldID(j_cls_, "param", "Lcom/tencent/imsdk/common/DownloadParam;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[VideoFieldDownloadParam] = jfield;

            return true;
        }

        jobject VideoElemHandler::Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) {
            if (!elem || elem->elemType != V2TIMElemType::V2TIM_ELEM_TYPE_VIDEO) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            auto *videoElem = (V2TIMVideoElem *) elem;

            jobject jElemObj = env->NewObject(j_cls_, j_method_id_array_[BaseElemConstructor]);
            if (!jElemObj) {
                return nullptr;
            }

            env->SetObjectField(jElemObj, j_field_array_[VideoFieldVideoPath], StringJni::Cstring2Jstring(env, videoElem->videoPath.CString()));
            env->SetObjectField(jElemObj, j_field_array_[VideoFieldVideoUUID], StringJni::Cstring2Jstring(env, videoElem->videoUUID.CString()));
            env->SetIntField(jElemObj, j_field_array_[VideoFieldVideoSize], (jint) videoElem->videoSize);
            env->SetIntField(jElemObj, j_field_array_[VideoFieldDuration], (jint) videoElem->duration);

            env->SetObjectField(jElemObj, j_field_array_[VideoFieldSnapshotPath], StringJni::Cstring2Jstring(env, videoElem->snapshotPath.CString()));
            env->SetObjectField(jElemObj, j_field_array_[VideoFieldSnapshotUUID], StringJni::Cstring2Jstring(env, videoElem->snapshotUUID.CString()));
            env->SetIntField(jElemObj, j_field_array_[VideoFieldSnapshotSize], (jint) videoElem->snapshotSize);
            env->SetIntField(jElemObj, j_field_array_[VideoFieldSnapshotWidth], (jint) videoElem->snapshotWidth);
            env->SetIntField(jElemObj, j_field_array_[VideoFieldSnapshotHeight], (jint) videoElem->snapshotHeight);

            jobject j_obj_param = DownloadParamJni::Convert2JObject(param);
            if (j_obj_param){
                env->SetObjectField(jElemObj,j_field_array_[VideoFieldDownloadParam], j_obj_param);
                env->DeleteLocalRef(j_obj_param);
            }

            return jElemObj;
        }

        std::unique_ptr<V2TIMElem> VideoElemHandler::Convert2CoreObject(int elemType, jobject jElemObj) {
            if (V2TIMElemType(elemType) != V2TIMElemType::V2TIM_ELEM_TYPE_VIDEO || !jElemObj) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            V2TIMVideoElem videoElem;

            jstring jStr = nullptr;

            jStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[VideoFieldVideoPath]);
            videoElem.videoPath = StringJni::Jstring2Cstring(env, jStr).c_str();
            env->DeleteLocalRef(jStr);

            jStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[VideoFieldVideoUUID]);
            videoElem.videoUUID = StringJni::Jstring2Cstring(env, jStr).c_str();
            env->DeleteLocalRef(jStr);

            videoElem.videoSize = (uint64_t) env->GetIntField(jElemObj, j_field_array_[VideoFieldVideoSize]);
            videoElem.duration = (uint32_t) env->GetIntField(jElemObj, j_field_array_[VideoFieldDuration]);

            jStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[VideoFieldSnapshotPath]);
            videoElem.snapshotPath = StringJni::Jstring2Cstring(env, jStr).c_str();
            env->DeleteLocalRef(jStr);

            jStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[VideoFieldSnapshotUUID]);
            videoElem.snapshotUUID = StringJni::Jstring2Cstring(env, jStr).c_str();
            env->DeleteLocalRef(jStr);

            videoElem.snapshotSize = (uint64_t) env->GetIntField(jElemObj, j_field_array_[VideoFieldSnapshotSize]);
            videoElem.snapshotWidth = (uint32_t) env->GetIntField(jElemObj, j_field_array_[VideoFieldSnapshotWidth]);
            videoElem.snapshotHeight = (uint32_t) env->GetIntField(jElemObj, j_field_array_[VideoFieldSnapshotHeight]);

            return std::make_unique<V2TIMVideoElem>(videoElem);
        }

//////////////////////////////////////////// V2TIMFileElem   ////////////////////////////////////////////

        std::string FileElemHandler::GetHandlerType() {
            return "FileElemHandler";
        }

        bool FileElemHandler::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMFileElem");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;
            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[BaseElemConstructor] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "path", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FileFieldPath] = jfield;

            jfield = env->GetFieldID(j_cls_, "fileName", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FileFieldFileName] = jfield;

            jfield = env->GetFieldID(j_cls_, "UUID", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FileFieldUUID] = jfield;

            jfield = env->GetFieldID(j_cls_, "fileSize", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FileFieldFileSize] = jfield;

            jfield = env->GetFieldID(j_cls_, "param", "Lcom/tencent/imsdk/common/DownloadParam;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FileFieldDownloadParam] = jfield;

            return true;
        }

        jobject FileElemHandler::Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) {
            if (!elem || elem->elemType != V2TIMElemType::V2TIM_ELEM_TYPE_FILE) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            auto *fileElem = (V2TIMFileElem *) elem;

            jobject jElemObj = env->NewObject(j_cls_, j_method_id_array_[BaseElemConstructor]);
            if (!jElemObj) {
                return nullptr;
            }

            env->SetObjectField(jElemObj, j_field_array_[FileFieldPath], StringJni::Cstring2Jstring(env, fileElem->path.CString()));
            env->SetObjectField(jElemObj, j_field_array_[FileFieldFileName], StringJni::Cstring2Jstring(env, fileElem->filename.CString()));
            env->SetObjectField(jElemObj, j_field_array_[FileFieldUUID], StringJni::Cstring2Jstring(env, fileElem->uuid.CString()));
            env->SetIntField(jElemObj, j_field_array_[FileFieldFileSize], (jint) fileElem->fileSize);

            jobject j_obj_param = DownloadParamJni::Convert2JObject(param);
            if (j_obj_param){
                env->SetObjectField(jElemObj,j_field_array_[FileFieldDownloadParam], j_obj_param);
                env->DeleteLocalRef(j_obj_param);
            }

            return jElemObj;
        }

        std::unique_ptr<V2TIMElem> FileElemHandler::Convert2CoreObject(int elemType, jobject jElemObj) {
            if (V2TIMElemType(elemType) != V2TIMElemType::V2TIM_ELEM_TYPE_FILE || !jElemObj) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            V2TIMFileElem fileElem;

            jstring jStr = nullptr;

            jStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[FileFieldPath]);
            fileElem.path = StringJni::Jstring2Cstring(env, jStr).c_str();
            env->DeleteLocalRef(jStr);

            jStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[FileFieldFileName]);
            fileElem.filename = StringJni::Jstring2Cstring(env, jStr).c_str();
            env->DeleteLocalRef(jStr);

            jStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[FileFieldUUID]);
            fileElem.uuid = StringJni::Jstring2Cstring(env, jStr).c_str();
            env->DeleteLocalRef(jStr);

            fileElem.fileSize = (uint64_t) env->GetIntField(jElemObj, j_field_array_[FileFieldFileSize]);

            return std::make_unique<V2TIMFileElem>(fileElem);
        }

//////////////////////////////////////////// V2TIMLocationElem ////////////////////////////////////////////

        std::string LocationElemHandler::GetHandlerType() {
            return "LocationElemHandler";
        }

        bool LocationElemHandler::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMLocationElem");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;
            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[BaseElemConstructor] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "desc", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[LocationFieldDesc] = jfield;

            jfield = env->GetFieldID(j_cls_, "longitude", "D");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[LocationFieldLongitude] = jfield;

            jfield = env->GetFieldID(j_cls_, "latitude", "D");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[LocationFieldLatitude] = jfield;

            return true;
        }

        jobject LocationElemHandler::Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) {
            if (!elem || elem->elemType != V2TIMElemType::V2TIM_ELEM_TYPE_LOCATION) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            auto *locationElem = (V2TIMLocationElem *) elem;

            jobject jElemObj = env->NewObject(j_cls_, j_method_id_array_[BaseElemConstructor]);
            if (!jElemObj) {
                return nullptr;
            }

            env->SetObjectField(jElemObj, j_field_array_[LocationFieldDesc], StringJni::Cstring2Jstring(env, locationElem->desc.CString()));
            env->SetDoubleField(jElemObj, j_field_array_[LocationFieldLongitude], (jdouble) locationElem->longitude);
            env->SetDoubleField(jElemObj, j_field_array_[LocationFieldLatitude], (jdouble) locationElem->latitude);

            return jElemObj;
        }

        std::unique_ptr<V2TIMElem> LocationElemHandler::Convert2CoreObject(int elemType, jobject jElemObj) {
            if (V2TIMElemType(elemType) != V2TIMElemType::V2TIM_ELEM_TYPE_LOCATION || !jElemObj) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            V2TIMLocationElem locationElem;

            jstring jStr;
            jStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[LocationFieldDesc]);
            locationElem.desc = StringJni::Jstring2Cstring(env, jStr).c_str();
            env->DeleteLocalRef(jStr);

            locationElem.longitude = env->GetDoubleField(jElemObj, j_field_array_[LocationFieldLongitude]);
            locationElem.latitude = env->GetDoubleField(jElemObj, j_field_array_[LocationFieldLatitude]);

            return std::make_unique<V2TIMLocationElem>(locationElem);
        }

//////////////////////////////////////////// V2TIMFaceElem   ////////////////////////////////////////////

        std::string FaceElemHandler::GetHandlerType() {
            return "FaceElemHandler";
        }

        bool FaceElemHandler::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMFaceElem");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;
            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[BaseElemConstructor] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "index", "I");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FaceFieldIndex] = jfield;

            jfield = env->GetFieldID(j_cls_, "data", "[B");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[FaceFieldData] = jfield;

            return true;
        }

        jobject FaceElemHandler::Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) {
            if (!elem || elem->elemType != V2TIMElemType::V2TIM_ELEM_TYPE_FACE) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            auto *faceElem = (V2TIMFaceElem *) elem;

            jobject jElemObj = env->NewObject(j_cls_, j_method_id_array_[BaseElemConstructor]);
            if (!jElemObj) {
                return nullptr;
            }

            env->SetIntField(jElemObj, j_field_array_[FaceFieldIndex], (jint) faceElem->index);
            size_t len = faceElem->data.Size();
            if (len > 0) {
                jbyteArray byteArr = ByteJni::Cuint8_t2JByteArray(env, faceElem->data.Data(), faceElem->data.Size());
                env->SetObjectField(jElemObj, j_field_array_[FaceFieldData], byteArr);
                env->DeleteLocalRef(byteArr);
            }
            return jElemObj;
        }

        std::unique_ptr<V2TIMElem> FaceElemHandler::Convert2CoreObject(int elemType, jobject jElemObj) {
            if (V2TIMElemType(elemType) != V2TIMElemType::V2TIM_ELEM_TYPE_FACE || !jElemObj) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            V2TIMFaceElem faceElem;

            faceElem.index = (uint32_t) env->GetIntField(jElemObj, j_field_array_[FaceFieldIndex]);

            auto byteArr = (jbyteArray) env->GetObjectField(jElemObj, j_field_array_[FaceFieldData]);
            faceElem.data = ByteJni::JByteArray2V2TIMBuffer(env, byteArr);
            env->DeleteLocalRef(byteArr);

            return std::make_unique<V2TIMFaceElem>(faceElem);
        }

//////////////////////////////////////////// V2TIMMergerElem ////////////////////////////////////////////

        std::string MergerElemHandler::GetHandlerType() {
            return "MergerElemHandler";
        }

        bool MergerElemHandler::InitIDs(JNIEnv *env) {
            if (nullptr != j_cls_) {
                return true;
            }

            jclass cls = env->FindClass("com/tencent/imsdk/v2/V2TIMMergerElem");
            if (nullptr == cls) {
                return false;
            }
            j_cls_ = (jclass) env->NewGlobalRef(cls);
            env->DeleteLocalRef(cls);

            jmethodID jmethod = nullptr;

            jmethod = env->GetMethodID(j_cls_, "<init>", "()V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MergerMethodConstructor] = jmethod;

            jmethod = env->GetMethodID(j_cls_, "addAbstract", "(Ljava/lang/String;)V");
            if (nullptr == jmethod) {
                return false;
            }
            j_method_id_array_[MergerMethodAddAbstract] = jmethod;

            jfieldID jfield = nullptr;

            jfield = env->GetFieldID(j_cls_, "layersOverLimit", "Z");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[MergerFieldLayersOverLimit] = jfield;

            jfield = env->GetFieldID(j_cls_, "title", "Ljava/lang/String;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[MergerFieldTitle] = jfield;

            jfield = env->GetFieldID(j_cls_, "abstractList", "Ljava/util/List;");
            if (nullptr == jfield) {
                return false;
            }
            j_field_array_[MergerFieldAbstractList] = jfield;

            return true;
        }

        jobject MergerElemHandler::Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) {
            if (!elem || elem->elemType != V2TIMElemType::V2TIM_ELEM_TYPE_MERGER) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            auto *mergerElem = (V2TIMMergerElem *) elem;

            jobject jElemObj = env->NewObject(j_cls_, j_method_id_array_[MergerMethodConstructor]);
            if (!jElemObj) {
                return nullptr;
            }

            env->SetBooleanField(jElemObj, j_field_array_[MergerFieldLayersOverLimit], mergerElem->layersOverLimit);
            env->SetObjectField(jElemObj, j_field_array_[MergerFieldTitle], StringJni::Cstring2Jstring(env, mergerElem->title.CString()));
            size_t len = mergerElem->abstractList.Size();
            for (int i = 0; i < len; ++i) {
                jstring abstractStr = StringJni::Cstring2Jstring(env, mergerElem->abstractList[0].CString());
                env->CallVoidMethod(jElemObj, j_method_id_array_[MergerMethodAddAbstract], abstractStr);
                env->DeleteLocalRef(abstractStr);
            }
            return jElemObj;
        }

        std::unique_ptr<V2TIMElem> MergerElemHandler::Convert2CoreObject(int elemType, jobject jElemObj) {
            if (V2TIMElemType(elemType) != V2TIMElemType::V2TIM_ELEM_TYPE_MERGER || !jElemObj) return nullptr;

            ScopedJEnv scopedJEnv;
            auto *env = scopedJEnv.GetEnv();

            if (!InitIDs(env)) {
                return nullptr;
            }

            V2TIMMergerElem mergerElem;

            mergerElem.layersOverLimit = env->GetBooleanField(jElemObj, j_field_array_[MergerFieldLayersOverLimit]);

            auto jStr = (jstring) env->GetObjectField(jElemObj, j_field_array_[MergerFieldTitle]);
            mergerElem.title = StringJni::Jstring2Cstring(env, jStr).c_str();
            env->DeleteLocalRef(jStr);

            jobject abstractListObj = env->GetObjectField(jElemObj, j_field_array_[MergerFieldAbstractList]);
            size_t len = ArrayListJni::Size(abstractListObj);
            for (int i = 0; i < len; ++i) {
                auto item = (jstring) ArrayListJni::Get(abstractListObj, i);
                mergerElem.abstractList.PushBack(StringJni::Jstring2Cstring(env, item).c_str());
                env->DeleteLocalRef(item);
            }
            env->DeleteLocalRef(abstractListObj);

            return std::make_unique<V2TIMMergerElem>(mergerElem);
        }
    }// namespace jni
}// namespace v2im
