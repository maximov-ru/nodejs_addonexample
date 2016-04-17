#include <nan.h>
#include "myobject.h"
#include "nRF24L01.h"
#include "RF24.h"
#include "RF24_config.h"
#include "bcm2835.h"

void InitAll(v8::Local<v8::Object> exports) {
  nrf24::Init(exports);
}

NODE_MODULE(addon, InitAll)
