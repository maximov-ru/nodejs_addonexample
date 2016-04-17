var addon = require('bindings')('addon');

var radio = new addon.nrf24(25,8,32);
radio.begin();
radio.enableDynamicPayloads();
radio.setPayloadSize(8);
radio.setRetries(15,15);
radio.printDetails();
radio.openWritingPipe(0xF0F0F0F0E1);
radio.openReadingPipe(1,0xF0F0F0F0D2);

console.log('after run cb');