var addon = require('bindings')('addon');

var radio = new addon.nrf24(25,8,32);
/*radio.begin();
radio.enableDynamicPayloads();
radio.setPayloadSize(8);
radio.setRetries(15,15);
radio.printDetails();
radio.openWritingPipe(0xF0F0F0F0E1);
radio.openReadingPipe(1,0xF0F0F0F0D2);*/
try {
    radio.runCallback(function (msg, err) {
        console.log('cb', msg, err);
    }, function (msg, err) {
        console.log('cb2', msg, err);
    });
}catch (e){
    console.log('exc',e);
}

radio.listen(function (data,pipeNumber){

},function (err){},timeout);

radio.sendData(function (data){

},function (err){},pipeNumber = undefined);
console.log('after run cb');