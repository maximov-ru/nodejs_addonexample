#include "myobject.h"
#include <unistd.h>
#include "RF24.h"

#define Sleep(x) usleep((x)*1000)

using namespace Nan;  // NOLINT(build/namespaces)
Nan::Persistent <v8::Function> nrf24::constructor;

nrf24::nrf24(int cepin, int cspin) {
    radio = new RF24(cepin, cspin);
    value_ = 0;
}

nrf24::nrf24(int cepin, int cspin, uint32_t spispeed) {
    radio = new RF24(cepin, cspin, spispeed);
    value_ = 0;
}

nrf24::~nrf24() {
}

class SleepWorker : public AsyncWorker {
public:
    SleepWorker(Callback *callback, int milliseconds)
            : AsyncWorker(callback), milliseconds(milliseconds) { }

    ~SleepWorker() { }

    void Execute() {
        Sleep(milliseconds);
    }

    void HandleOKCallback() {
        Nan::HandleScope scope;

        v8::Local <v8::Value> argv[1] = {Nan::New("hello world").ToLocalChecked()};

        callback->Call(1, argv);

    }

private:
    int milliseconds;
};

void nrf24::Init(v8::Local <v8::Object> exports) {
    Nan::HandleScope scope;

    // Prepare constructor template
    v8::Local <v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
    tpl->SetClassName(Nan::New("nrf24").ToLocalChecked());
    tpl->InstanceTemplate()->SetInternalFieldCount(1);

    // Prototype
    SetPrototypeMethod(tpl, "begin", begin);
    SetPrototypeMethod(tpl, "openWritingPipe", openWritingPipe);
    SetPrototypeMethod(tpl, "openReadingPipe", openReadingPipe);
    SetPrototypeMethod(tpl, "available", available);
    SetPrototypeMethod(tpl, "setRetries", setRetries);
    SetPrototypeMethod(tpl, "setChannel", setChannel);
    SetPrototypeMethod(tpl, "setPayloadSize", setPayloadSize);
    SetPrototypeMethod(tpl, "getPayloadSize", getPayloadSize);
    SetPrototypeMethod(tpl, "getDynamicPayloadSize", getDynamicPayloadSize);
    SetPrototypeMethod(tpl, "enableAckPayload", enableAckPayload);
    SetPrototypeMethod(tpl, "enableDynamicPayloads", enableDynamicPayloads);
    SetPrototypeMethod(tpl, "enableDynamicAck", enableDynamicAck);
    SetPrototypeMethod(tpl, "setAutoAck", setAutoAck);
    SetPrototypeMethod(tpl, "disableCRC", disableCRC);
    SetPrototypeMethod(tpl, "powerDown", powerDown);
    SetPrototypeMethod(tpl, "powerUp", powerUp);
    SetPrototypeMethod(tpl, "txStandBy", txStandBy);
    SetPrototypeMethod(tpl, "setAddressWidth", setAddressWidth);
    SetPrototypeMethod(tpl, "printDetails", printDetails);

    constructor.Reset(tpl->GetFunction());
    exports->Set(Nan::New("nrf24").ToLocalChecked(), tpl->GetFunction());
}

void nrf24::New(const FunctionCallbackInfo <v8::Value> &info) {
    if (info.IsConstructCall()) {
        // Invoked as constructor: `new MyObject(...)`
        int cepin = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
        int cspin = info[1]->IsUndefined() ? 0 : info[1]->NumberValue();
        uint32_t spispeed = info[2]->IsUndefined() ? 0 : info[2]->NumberValue();
        nrf24 *obj = info[2]->IsUndefined() ? new nrf24(cepin, cspin) : new nrf24(cepin, cspin, spispeed);

        obj->Wrap(info.This());
        info.GetReturnValue().Set(info.This());
    } else {
        // Invoked as plain function `MyObject(...)`, turn into construct call.
        const int argc = 1;
        v8::Local <v8::Value> argv[argc] = {info[0]};
        v8::Local <v8::Function> cons = Nan::New<v8::Function>(constructor);
        info.GetReturnValue().Set(cons->NewInstance(argc, argv));
    }
}

/*void nrf24::GetValue(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    info.GetReturnValue().Set(Nan::New(obj->value_));
}*/

void nrf24::begin(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    bool ret = obj->radio->begin();
    info.GetReturnValue().Set(Nan::New(ret));
}

void nrf24::openWritingPipe(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    uint64_t address = info[0]->NumberValue();
    obj->radio->openWritingPipe(address);
}

void nrf24::openReadingPipe(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    uint8_t number = info[0]->NumberValue();
    uint64_t address = info[1]->NumberValue();
    obj->radio->openReadingPipe(number, address);
}

void nrf24::available(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());

    bool ret = obj->radio->available();
    info.GetReturnValue().Set(Nan::New(ret));
}

void nrf24::setRetries(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    uint8_t delay = info[0]->NumberValue();
    uint8_t count = info[1]->NumberValue();
    obj->radio->setRetries(delay, count);
}

void nrf24::setChannel(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    uint8_t channel = info[0]->NumberValue();
    obj->radio->setChannel(channel);
}

void nrf24::setPayloadSize(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    uint8_t size = info[0]->NumberValue();
    obj->radio->setPayloadSize(size);
}

void nrf24::getPayloadSize(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    uint8_t size = obj->radio->getPayloadSize();
    info.GetReturnValue().Set(Nan::New(size));
}

void nrf24::getDynamicPayloadSize(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    uint8_t size = obj->radio->getDynamicPayloadSize();
    info.GetReturnValue().Set(Nan::New(size));
}

void nrf24::enableAckPayload(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());

    obj->radio->enableAckPayload();
}

void nrf24::enableDynamicPayloads(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());

    obj->radio->enableDynamicPayloads();
}

void nrf24::enableDynamicAck(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());

    obj->radio->enableDynamicAck();
}

void nrf24::setAutoAck(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    bool enable = info[0]->BooleanValue();
    obj->radio->setAutoAck(enable);
}

void nrf24::disableCRC(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    obj->radio->disableCRC();
}

void nrf24::powerDown(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    obj->radio->powerDown();
}

void nrf24::powerUp(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    obj->radio->powerUp();
}

void nrf24::txStandBy(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    uint32_t timeout = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
    bool ret = info[0]->IsUndefined() ? obj->radio->txStandBy() : obj->radio->txStandBy(timeout);
    info.GetReturnValue().Set(Nan::New(ret));
}

void nrf24::setAddressWidth(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    uint8_t a_width = info[0]->IsUndefined() ? 0 : info[0]->NumberValue();
    obj->radio->setAddressWidth(a_width);
}

void nrf24::printDetails(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());
    obj->radio->printDetails();
}

/*void nrf24::RunCallback(const FunctionCallbackInfo <v8::Value> &info) {
    nrf24 *obj = ObjectWrap::Unwrap<nrf24>(info.Holder());

    Callback *callbackGood = new Callback(info[0].As<v8::Function>());
    Callback *callbackBad = new Callback(info[1].As<v8::Function>());

    AsyncQueueWorker(new SleepWorker(callbackGood, 1000));
    AsyncQueueWorker(new SleepWorker(callbackBad, 3000));
}*/