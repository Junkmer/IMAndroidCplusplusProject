//
// Created by EDY on 2022/9/21.
//

#ifndef IMCPLUSPLUSDEMO_ELEM_PROCESSOR_JNI_H
#define IMCPLUSPLUSDEMO_ELEM_PROCESSOR_JNI_H

#include "V2TIMMessage.h"
#include <jni.h>
#include <memory>

#include "elem_handler_jni.h"
#include <vector>

namespace v2im {
    namespace jni {
        class ElemProcessor final {
        public:
            ElemProcessor();
            ~ElemProcessor();

            static ElemProcessor &GetInstance();
            void RegisterElemHandler();
            jobject ParseElem(const V2TIMMessage &message,const int position);
            std::unique_ptr<V2TIMElem> BuildElem(int elemType, jobject elemObj);

        protected:
            void RegisterElemHandler(std::unique_ptr<IElemHandler> handler);

        private:
            std::vector<std::unique_ptr<IElemHandler>> handlers_;
        };
    }// namespace v2im
}// namespace jni


#endif //IMCPLUSPLUSDEMO_ELEM_PROCESSOR_JNI_H
