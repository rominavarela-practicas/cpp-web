////////////////////////////////////////////////////////////////////////////////
//INIT

var express = require('express');
    app = express();

var fs=   require('fs')
    CircularJSON=   require('circular-json')
    bodyParser = require('body-parser');

app.use(bodyParser.json()); // support json encoded bodies
app.use(bodyParser.urlencoded({ extended: true }));

////////////////////////////////////////////////////////////////////////////////
//GET AND POST

app.get('/', function (req, res) {
  res.send('Hello World!');
});

app.get('/get/:something', function (req, res) {
  fs.writeFile('GOT.log', CircularJSON.stringify(req), function (err) {
    if (err) return console.log(err);
    console.log('out > GOT.log');
  });

  res.send('client get: '+req.params.something);
});

app.post('/post/something', function (req, res) {

  fs.writeFile('POSTED.log', CircularJSON.stringify(req), function (err) {
    if (err) return console.log(err);
    console.log('out > POSTED.log');
  });

  res.send('client post: ' + CircularJSON.stringify(req.body));
});

////////////////////////////////////////////////////////////////////////////////
//LISTEN

var server = app.listen(3000, function () {
  var port = server.address().port;
  console.log('App listening at port %s', port);
});
