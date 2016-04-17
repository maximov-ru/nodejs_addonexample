var addon = require('bindings')('addon');

var radio = new addon.nrf24(22,7);
radio.begin();
radio.enableDynamicPayloads();
radio.setRetries(5,15);
radio.printDetails();
radio.openWritingPipe(0xF0F0F0F0E1);
radio.openReadingPipe(1,0xF0F0F0F0D2);

console.log('after run cb');