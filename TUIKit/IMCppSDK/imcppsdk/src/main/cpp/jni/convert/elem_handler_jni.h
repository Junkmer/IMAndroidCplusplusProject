//
// Created by EDY on 2022/9/21.
//

#ifndef IMCPLUSPLUSDEMO_ELEM_HANDLER_JNI_H
#define IMCPLUSPLUSDEMO_ELEM_HANDLER_JNI_H

#include <string>

#include "jni.h"
#include "V2TIMMessage.h"
#include "memory"
#include "download_param_jni.h"

enum TextElemFieldID{
    TextFieldText = 0,

    TextElemFieldIDMax,
};

enum CustomElemFieldID{
    CustomFieldData = 0,
    CustomFieldDescription,
    CustomFieldExtension,

    CustomElemFieldIDMax,
};

enum ImageElemFieldID{
    ImageFieldPath = 0,
    ImageFieldImageList,

    ImageElemFieldIDMax,
};

enum SoundElemFieldID{
    SoundFieldPath = 0,
    SoundFieldUUID,
    SoundFieldDataSize,
    SoundFieldDuration,
    SoundFieldDownloadParam,

    SoundElemFieldIDMax,
};

enum VideoElemFieldID{
    VideoFieldVideoPath = 0,
    VideoFieldVideoUUID,
    VideoFieldVideoSize,
    VideoFieldDuration,
    VideoFieldSnapshotPath,
    VideoFieldSnapshotUUID,
    VideoFieldSnapshotSize,
    VideoFieldSnapshotWidth,
    VideoFieldSnapshotHeight,
    VideoFieldDownloadParam,

    VideoElemFieldIDMax,
};

enum FileElemFieldID{
    FileFieldPath = 0,
    FileFieldFileName,
    FileFieldUUID,
    FileFieldFileSize,
    FileFieldDownloadParam,

    FileElemFieldIDMax,
};

enum LocationElemFieldID{
    LocationFieldDesc = 0,
    LocationFieldLongitude,
    LocationFieldLatitude,

    LocationElemFieldIDMax,
};

enum FaceElemFieldID{
    FaceFieldIndex = 0,
    FaceFieldData,

    FaceElemFieldIDMax,
};

enum MergerElemFieldID{
    MergerFieldLayersOverLimit = 0,
    MergerFieldTitle,
    MergerFieldAbstractList,

    MergerElemFieldIDMax,
};

enum ImageElemMethodID{
    ImageMethodConstructor = 0,
    ImageMethodAddImage,

    ImageMethodIDMax
};

enum MergerElemMethodID{
    MergerMethodConstructor = 0,
    MergerMethodAddAbstract,

    MergerMethodIDMax
};

enum BaseElemMethodID{
    BaseElemConstructor = 0,

    BaseElemMethodIMMax,
};

namespace v2im {
    namespace jni {
        class IElemHandler {
        public:
            virtual std::string GetHandlerType() = 0;
            virtual jobject Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) = 0;
            virtual std::unique_ptr<V2TIMElem> Convert2CoreObject(int elemType, jobject jElemObj) = 0;
            virtual bool InitIDs(JNIEnv *env) = 0;
            virtual ~IElemHandler();

        protected:
            jclass j_cls_ = nullptr;
        };

        class TextElemHandler : public IElemHandler {
        public:
            std::string GetHandlerType() override;
            bool InitIDs(JNIEnv *env) override;
            jobject Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) override;
            std::unique_ptr<V2TIMElem> Convert2CoreObject(int elemType, jobject jElemObj) override;

        protected:
            jfieldID j_field_array_[TextElemFieldIDMax];
            jmethodID j_method_id_array_[BaseElemMethodIMMax];
        };

        class CustomElemHandler : public IElemHandler {
        public:
            std::string GetHandlerType() override;
            bool InitIDs(JNIEnv *env) override;
            jobject Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) override;
            std::unique_ptr<V2TIMElem> Convert2CoreObject(int elemType, jobject jElemObj) override;

        protected:
            jfieldID j_field_array_[CustomElemFieldIDMax];
            jmethodID j_method_id_array_[BaseElemMethodIMMax];
        };

        class ImageElemHandler : public IElemHandler {
        public:
            std::string GetHandlerType() override;
            bool InitIDs(JNIEnv *env) override;
            jobject Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) override;
            std::unique_ptr<V2TIMElem> Convert2CoreObject(int elemType, jobject jElemObj) override;

        protected:
            jfieldID j_field_array_[ImageElemFieldIDMax];
            jmethodID j_method_id_array_[ImageMethodIDMax];
        };

        class SoundElemHandler : public IElemHandler {
        public:
            std::string GetHandlerType() override;
            bool InitIDs(JNIEnv *env) override;
            jobject Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) override;
            std::unique_ptr<V2TIMElem> Convert2CoreObject(int elemType, jobject jElemObj) override;

        protected:
            jfieldID j_field_array_[SoundElemFieldIDMax];
            jmethodID j_method_id_array_[BaseElemMethodIMMax];
        };

        class VideoElemHandler : public IElemHandler {
        public:
            std::string GetHandlerType() override;
            bool InitIDs(JNIEnv *env) override;
            jobject Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) override;
            std::unique_ptr<V2TIMElem> Convert2CoreObject(int elemType, jobject jElemObj) override;

        protected:
            jfieldID j_field_array_[VideoElemFieldIDMax];
            jmethodID j_method_id_array_[BaseElemMethodIMMax];
        };

        class FileElemHandler : public IElemHandler {
        public:
            std::string GetHandlerType() override;
            bool InitIDs(JNIEnv *env) override;
            jobject Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) override;
            std::unique_ptr<V2TIMElem> Convert2CoreObject(int elemType, jobject jElemObj) override;

        protected:
            jfieldID j_field_array_[FileElemFieldIDMax];
            jmethodID j_method_id_array_[BaseElemMethodIMMax];
        };

        class LocationElemHandler : public IElemHandler {
        public:
            std::string GetHandlerType() override;
            bool InitIDs(JNIEnv *env) override;
            jobject Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) override;
            std::unique_ptr<V2TIMElem> Convert2CoreObject(int elemType, jobject jElemObj) override;

        protected:
            jfieldID j_field_array_[LocationElemFieldIDMax];
            jmethodID j_method_id_array_[BaseElemMethodIMMax];
        };

        class FaceElemHandler : public IElemHandler {
        public:
            std::string GetHandlerType() override;
            bool InitIDs(JNIEnv *env) override;
            jobject Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) override;
            std::unique_ptr<V2TIMElem> Convert2CoreObject(int elemType, jobject jElemObj) override;

        protected:
            jfieldID j_field_array_[FaceElemFieldIDMax];
            jmethodID j_method_id_array_[BaseElemMethodIMMax];
        };

        class MergerElemHandler : public IElemHandler {
        public:
            std::string GetHandlerType() override;
            bool InitIDs(JNIEnv *env) override;
            jobject Convert2JObject(const V2TIMElem *elem, const DownloadParam &param) override;
            std::unique_ptr<V2TIMElem> Convert2CoreObject(int elemType, jobject jElemObj) override;

        protected:
            jfieldID j_field_array_[MergerElemFieldIDMax];
            jmethodID j_method_id_array_[MergerMethodIDMax];
        };

    }// namespace jni
}// namespace v2im


#endif //IMCPLUSPLUSDEMO_ELEM_HANDLER_JNI_H
