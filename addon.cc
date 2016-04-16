#include <nan.h>
#include "myobject.h"

void InitAll(v8::Local<v8::Object> exports) {
  nrf24::Init(exports);
}

NODE_MODULE(addon, InitAll)
