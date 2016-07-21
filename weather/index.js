'use strict'

var express = require('express');
var app = express();
var data = require('./database');
var bodyParser = require('body-parser');


app.use(express.static('static'));
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: true
}));

app.get('/state', function(req, res){
  res.send('{"ERROR":"not implemented"}');
});

app.get('/graph/:what', function(req, res){
  var what = req.param('what');
  if(what == "t") {
     res.send('{"ERROR":"not implemented"}');
  }
  else if(what == "p") {
    res.send('{"ERROR":"not implemented"}');
  }
  else if(what == 'h') res.send('{"ERROR":"not implemented"}');
  else res.send('{"ERROR":"not recognized option"}');
});




var server = app.listen(3000, function () {

  var host = server.address().address;
  var port = server.address().port;
  console.log('Example app listening at http://%s:%s', host, port);
  setInterval(function(){console.log("working");}, 1000);

});
