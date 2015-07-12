'use strict'

var sqlite3 = require('sqlite3').verbose();
var db = new sqlite3.Database('./dane.sqlite3');

exports.getWeather = function(res) {
  var run = db.all("SELECT dateCol, t, p, h FROM WeatherState", function(err, rows) {
      console.log(JSON.stringify(rows));
      res.json(rows);
  });
}

exports.getParameter = function(res, what) {
  var stmt = db.prepare("SELECT id, name, ip, ghid FROM Hosts where ghid = ?");
  stmt.all(id, function(err, rows){
    console.log(JSON.stringify(rows));
    res.json(rows)
  });
}

exports.setWeather = function(res, gName) {
  var stmt = db.prepare("INSERT INTO GroupHosts (name) VALUES (?)");
  stmt.run(gName, function(err, row){
    console.log(JSON.stringify(row));
    if(err) res.json({Ans:"NO"});
    else res.json({Ans:"OK"});
  });
}
