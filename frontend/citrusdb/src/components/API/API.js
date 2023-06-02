import request from 'request';

request('http://18.118.28.109:80', function (err, res) {
    if (err) {
        console.log(err);
    } else {
        console.log(res.body);
    }
});