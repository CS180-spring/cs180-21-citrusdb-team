import request from 'request';

request('http://0.0.0.0:8080', function (err, res) {
    if (err) {
        console.log(err);
    } else {
        console.log(res.body);
    }
});