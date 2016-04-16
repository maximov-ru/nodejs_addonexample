#include <nan.h>
#include "myobject.h"
#include "RF24/nRF24L01.h"
#include "RF24/RF24.h"
#include "RF24/RF24_config.h"
#include "RF24/bcm2835.h"

void InitAll(v8::Local<v8::Object> exports) {
  nrf24::Init(exports);
}

NODE_MODULE(addon, InitAll)
