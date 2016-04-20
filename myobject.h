#ifndef NRF24OBJECT_H
#define NRF24OBJECT_H

#include <nan.h>
#include <string>
#include "nRF24L01.h"
#include "RF24.h"
#include "RF24_config.h"
#include "bcm2835.h"

struct NrfState{
    bool autoAck;
    bool dynamicPayload;
    bool dynamicAck;
    uint8_t payloadSize;
    uint8_t channel;
    uitn8_t pipeCount;
    bool usedPipes [6];
};

class nrf24 : public Nan::ObjectWrap {
public:
    static void Init(v8::Local <v8::Object> exports);

private:
    explicit nrf24(int cepin, int cspin);

    explicit nrf24(int cepin, int cspin, uint32_t spispeed);

    ~nrf24();

    static void New(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void begin(const Nan::FunctionCallbackInfo <v8::Value> &info);

    //static void startListening(const Nan::FunctionCallbackInfo<v8::Value>& info);
    //static void stopListening(const Nan::FunctionCallbackInfo<v8::Value>& info);
    static void openWritingPipe(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void openReadingPipe(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void available(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void setRetries(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void setChannel(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void setPayloadSize(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void getPayloadSize(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void getDynamicPayloadSize(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void enableAckPayload(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void enableDynamicPayloads(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void enableDynamicAck(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void setAutoAck(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void disableCRC(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void powerDown(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void powerUp(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void txStandBy(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void setAddressWidth(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void printDetails(const Nan::FunctionCallbackInfo <v8::Value> &info);

    static void listen(const Nan::FunctionCallbackInfo <v8::Value> &info);

    /*
    bool begin(void);
    void startListening(void);
    void stopListening(void);
    bool write( const void* buf, uint8_t len );
    bool available(void);
    bool available(uint8_t* pipe_num);
    void read( void* buf, uint8_t len );
    void openWritingPipe(const uint8_t *address);
    void openReadingPipe(uint8_t number, const uint8_t *address);
    uint8_t flush_tx(void);
    void setRetries(uint8_t delay, uint8_t count);
    void setChannel(uint8_t channel);
    void setPayloadSize(uint8_t size);
    uint8_t getPayloadSize(void);
    uint8_t getDynamicPayloadSize(void);
    void enableAckPayload(void);
    void enableDynamicPayloads(void);
    void enableDynamicAck(void);
    bool isPVariant(void)
    void setAutoAck(bool enable);
    void setAutoAck( uint8_t pipe, bool enable ) ;
    void setPALevel( uint8_t level )
    uint8_t getPALevel( void ) ;
    bool setDataRate(rf24_datarate_e speed);
    rf24_datarate_e getDataRate( void ) ;
    void setCRCLength(rf24_crclength_e length);
    rf24_crclength_e getCRCLength(void);
    void disableCRC( void ) ;
    void openWritingPipe(uint64_t address);
    void openReadingPipe(uint8_t number, uint64_t address);
    void powerDown(void);
    void powerUp(void) ;
    bool txStandBy();
    bool txStandBy(uint32_t timeout);
    void setAddressWidth(uint8_t a_width);
    */
    static Nan::Persistent <v8::Function> constructor;
    double value_;
    RF24 *radio;
    NrfState state;
};

#endif
