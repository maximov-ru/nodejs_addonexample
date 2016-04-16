#ifndef NRF24OBJECT_H
#define NRF24OBJECT_H

#include <nan.h>
#include <string>
#include "RF24/nRF24L01.h"
#include "RF24/RF24.h"
#include "RF24/RF24_config.h"
#include "RF24/bcm2835.h"

class nrf24 : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit nrf24(int cepin, int cspin);
  explicit nrf24(int cepin, int cspin, uint32_t spispeed );
  ~nrf24();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void GetValue(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void PlusOne(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void Multiply(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static void RunCallback(const Nan::FunctionCallbackInfo<v8::Value>& info);
  static Nan::Persistent<v8::Function> constructor;
  double value_;
  RF24* radio;
};

#endif
