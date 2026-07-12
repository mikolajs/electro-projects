'use strict'

var express = require('express');
var app = express();
var bodyParser = require('body-parser');
var Pool = require('pg').Pool;

const pool = new Pool({
        user: 'weatherstation',
        host: 'localhost',
        database: 'weatherstation',
        password: 'zaq12wsx',
        port: 5432
});

const getMeasures =  (req, res) => {
  pool.query("SELECT th, time, T, h, p, s FROM measure", (err, results) => {
      if(err) {
	    console.log('Error\n'+ err.toString())
	      res.status(400).json('{"Error":"Error"}');
      } else {
        console.log(JSON.stringify(results.rows));
        res.json(results.rows);
      }
  });
}

const setMeasures = (req, res) => {
  const time = new Date().getTime();
  const par = req.query;
  console.log(par);
  let t = 0.0;
  let h = 0.0;
  let p = 0.0;
  let s = 0.0;
  let th = "nieznany";
  if(par.t) t = par.t;
  if(par.h) h = par.h;
  if(par.p) p = par.p;
  if(par.s) s = par.s;
  if(par.th) th = par.th;
  pool.query('Insert into measure values ($1, $2, $3, $4, $5, $6)', [th, time, t, h, p, s], (err, results) => {
	if(err) {
	   console.log('Error:\n' + err.toString());
	   res.status(400).json('{"Error":"Error"}');
	} else {
	   res.json('{"OK":"OK"}');
	}
  });
}

app.use(express.static('static'));
app.get('/measures', setMeasures);
app.get('/getmeasures', getMeasures);
app.use(bodyParser.json());
app.use(bodyParser.urlencoded({
  extended: true
}));

app.get('/state', function(req, res){
  res.send('{"ERROR":"not implemented"}');
});

var server = app.listen(3000, function () {

  var host = server.address().address;
  var port = server.address().port;
  console.log('Example app listening at http://%s:%s', host, port);
  //setInterval(function(){console.log("working");}, 1000);
});

