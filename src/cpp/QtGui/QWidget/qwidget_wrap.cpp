#include "qwidget_wrap.h"
#include "src/cpp/QtWidgets/QLayout/qlayout_wrap.h"
#include "src/cpp/Extras/Utils/utils.h"

Napi::FunctionReference QWidgetWrap::constructor;

Napi::Object QWidgetWrap::init(Napi::Env env, Napi::Object exports) {
  Napi::HandleScope scope(env);
  char CLASSNAME[] = "QWidget";
  Napi::Function func = DefineClass(env, CLASSNAME, {
    QWIDGET_WRAPPED_METHODS_EXPORT_DEFINE(QWidgetWrap)
  });
  constructor = Napi::Persistent(func);
  exports.Set(CLASSNAME, func);
  return exports;
}

NWidget* QWidgetWrap::getInternalInstance() {
  return this->instance;
}

QWidgetWrap::QWidgetWrap(const Napi::CallbackInfo& info): Napi::ObjectWrap<QWidgetWrap>(info)  { 
  Napi::Env env = info.Env();
  Napi::HandleScope scope(env);

  if(info.Length() == 1) {
      Napi::Object parentObject = info[0].As<Napi::Object>();
      QWidgetWrap* parentWidgetWrap = Napi::ObjectWrap<QWidgetWrap>::Unwrap(parentObject);
      this->instance = new NWidget(parentWidgetWrap->getInternalInstance()); //this sets the parent to current widget
  }else if (info.Length() == 0){
    this->instance = new NWidget();
  }else {
    extrautils::throwTypeError(env, "Wrong number of arguments");
  }
}

QWidgetWrap::~QWidgetWrap() {
  delete this->instance;
}

