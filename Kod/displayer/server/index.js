'use strict'

var express = require('express');
var app = express();
var data = require('./database');


app.use(express.static('static'));


app.get('/get/:depart', function(req, res){
  var depart = req.param('depart');
  if(depart == "") {
     res.send('{"ERROR":"not implemented"}');
  }
  else data.getNews(res, depart);
});




var server = app.listen(3000, function () {

  var host = server.address().address;
  var port = server.address().port;
  console.log('Example app listening at http://%s:%s', host, port);
  setInterval(function(){console.log("working");}, 100000);

});
