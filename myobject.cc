#include "myobject.h"
#include <unistd.h>
#define Sleep(x) usleep((x)*1000)

using namespace Nan;  // NOLINT(build/namespaces)
Nan::Persistent<v8::Function> MyObject::constructor;

MyObject::MyObject(double value) : value_(value) {
}

MyObject::~MyObject() {
}

class SleepWorker : public AsyncWorker {
 public:
  SleepWorker(Callback *callback, int milliseconds)
    : AsyncWorker(callback), milliseconds(milliseconds) {}
  ~SleepWorker() {}

  void Execute () {
    Sleep(milliseconds);
  }

  void HandleOKCallback () {
              Nan::HandleScope scope;

              v8::Local<v8::Value> argv[1] = { Nan::New("hello world").ToLocalChecked() };

              callback->Call(1, argv);

          }

 private:
  int milliseconds;
};

void MyObject::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("MyObject").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  SetPrototypeMethod(tpl, "value", GetValue);
  SetPrototypeMethod(tpl, "plusOne", PlusOne);
  SetPrototypeMethod(tpl, "multiply", Multiply);
  SetPrototypeMethod(tpl, "runCallback", RunCallback);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("MyObject").ToLocalChecked(), tpl->GetFunction());
}

void MyObject::New(const FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    double value = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
    MyObject* obj = new MyObject(value);
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `MyObject(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}

void MyObject::GetValue(const FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->value_));
}

void MyObject::PlusOne(const FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  obj->value_ += 1;
  info.GetReturnValue().Set(Nan::New(obj->value_));
}

void MyObject::Multiply(const FunctionCallbackInfo<v8::Value>& info) {
  MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());
  double multiple = info[0]->IsUndefined() ? 1 : info[0]->NumberValue();

  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);

  const int argc = 1;
  v8::Local<v8::Value> argv[argc] = { Nan::New(obj->value_ * multiple) };

  info.GetReturnValue().Set(cons->NewInstance(argc, argv));
}

void MyObject::RunCallback(const FunctionCallbackInfo<v8::Value>& info) {
   MyObject* obj = ObjectWrap::Unwrap<MyObject>(info.Holder());

   Callback *callbackGood = new Callback(info[0].As<v8::Function>());
   Callback *callbackBad = new Callback(info[1].As<v8::Function>());

   AsyncQueueWorker(new SleepWorker(callbackGood, 1000));
 }