var express = require('express')
var app = express()

app.use(express.static('public'))

app.get('/', function(req, res) {
    res.send('Hello World!')
})

app.get('/kmaapi', function(req2, res2) {
    var http = require("http");
    var options = {
        "method": "GET",
        "hostname": "newsky2.kma.go.kr",
        "port": null,
        "path": "/service/SecndSrtpdFrcstInfoService2/ForecastSpaceData?base_date=20171008&base_time=0230&nx=1&ny=1&_type=json&ServiceKey=xSzZPJN3rmHQCOooOPr%2B8UQVia26Wq1W8RJHhXRvxGD6W9Kz0BgbnUsqrSal7Us6nxswNcSQQ0URbdWUtHno2g%3D%3D",
        "headers": {
            "cache-control": "no-cache",
            "postman-token": "c273bddd-3280-1d17-8eac-9b5d572f7578"
        }
    };
    var req = http.request(options, function(res) {
        var chunks = [];
        res.on("data", function(chunk) {
            chunks.push(chunk);
        });
        res.on("end", function() {
            var body = Buffer.concat(chunks);
            console.log(body.toString());

            res2.send(body.toString());
        });
    });
    req.end();
})

app.listen(3000, function() {
    console.log('Example app listening on port 3000!')
})
