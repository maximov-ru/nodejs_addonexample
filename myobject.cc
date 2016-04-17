#include "myobject.h"
#include <unistd.h>
#include "RF24.h"
#define Sleep(x) usleep((x)*1000)

using namespace Nan;  // NOLINT(build/namespaces)
Nan::Persistent<v8::Function> nrf24::constructor;

nrf24::nrf24(int cepin, int cspin) {
  radio = new RF24(cepin, cspin);
  value_ = 0;
}
nrf24::nrf24(int cepin, int cspin, uint32_t spispeed ) {
  //radio = new RF24(cepin, cspin, spispeed);
  value_ = 0;
}

nrf24::~nrf24() {
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

void nrf24::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("nrf24").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  SetPrototypeMethod(tpl, "value", GetValue);
  SetPrototypeMethod(tpl, "plusOne", PlusOne);
  SetPrototypeMethod(tpl, "multiply", Multiply);
  SetPrototypeMethod(tpl, "runCallback", RunCallback);

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("nrf24").ToLocalChecked(), tpl->GetFunction());
}

void nrf24::New(const FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new MyObject(...)`
    int cepin = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
    int cspin = info[1]->IsUndefined() ? 0 : info[1]->NumberValue();
    uint32_t spispeed = info[2]->IsUndefined() ? 0 :info[2]->NumberValue();
    nrf24* obj = info[2]->IsUndefined() ? new nrf24(cepin, cspin) :  new nrf24(cepin, cspin, spispeed);

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

void nrf24::GetValue(const FunctionCallbackInfo<v8::Value>& info) {
  nrf24* obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
  info.GetReturnValue().Set(Nan::New(obj->value_));
}

void nrf24::PlusOne(const FunctionCallbackInfo<v8::Value>& info) {
  nrf24* obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
  obj->value_ += 1;
  info.GetReturnValue().Set(Nan::New(obj->value_));
}

void nrf24::Multiply(const FunctionCallbackInfo<v8::Value>& info) {
  nrf24* obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
  double multiple = info[0]->IsUndefined() ? 1 : info[0]->NumberValue();

  v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);

  const int argc = 1;
  v8::Local<v8::Value> argv[argc] = { Nan::New(obj->value_ * multiple) };

  info.GetReturnValue().Set(cons->NewInstance(argc, argv));
}

void nrf24::RunCallback(const FunctionCallbackInfo<v8::Value>& info) {
   nrf24* obj = ObjectWrap::Unwrap<nrf24>(info.Holder());

   Callback *callbackGood = new Callback(info[0].As<v8::Function>());
   Callback *callbackBad = new Callback(info[1].As<v8::Function>());

   AsyncQueueWorker(new SleepWorker(callbackGood, 1000));
   AsyncQueueWorker(new SleepWorker(callbackBad, 3000));
 }