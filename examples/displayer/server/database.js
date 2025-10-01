'use strict'

var mongodb = require('mongodb');
var MongoClient = mongodb.MongoClient;
var url = 'mongodb://localhost:27017/osp';




exports.getNews = function(res, depart) {
      var rows = {};
      console.log("show department:", depart);
      MongoClient.connect(url, function (err, db) {
        if (err) {
          console.log('Unable to connect to the mongoDB server. Error:', err);
          res.json({"Error":"Can't open database"});
        } else {
          console.log('Connection established to', url);
          var newsTag = db.collection('newstag');
          newsTag.find({tag:depart}).toArray(function(err, result){
            if(err){
              res.json({"Error":"Can't find department"});
            }
            else {
              if(result.length > 0) {
                var artHead = db.collection('articlehead');
                artHead.find({news:true, departmentId:result[0]._id}).toArray(function(err, result){
                  if(err){
                    res.json({"Error":"Can't find head of articles"});
                  }
                  else {
                    if(result.length > 0) {
                      var artCont = db.collection('articlecontent');
                      var depIds = [];
                      var sendData = [];
                      for(i in result) {
                        depIds.push(result[i]._id);
                        sendData.push({"title":result[i].title, "dep":result[i].departmentId, "cont":"");
                      }
                      artCont.find({"departmentId" : {$in : user.friends }}).toArray(function(err, result2){
                        if(err){
                          res.json({"Error":"Can't find article contents"});
                        }
                        else {
                          if(result2.length > 0) {
                            ///zwracam
                          }
                        }
                      });
                    } else res.json({"Error":"Empty article heads"});
                  }
                });
              } else res.json({"Error":"Empty departments list"});
            }



          });

          res.json(rows);
          db.close();
        }
      });

}
