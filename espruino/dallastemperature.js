var ow = new OneWire(2);
var sensor = require("DS18B20").connect(ow);
var history = new Float32Array(30);

setInterval(function() {
  var temp = sensor.getTemp();
  console.log(temp);
  // move history back
  for (var i=1;i<history.length;i++)
    history[i-1]=history[i];
  // insert new history at end
  history[history.length-1] = temp;
}, 2000);