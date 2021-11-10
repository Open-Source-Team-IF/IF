var express = require('express');
var router = express.Router();

var connection = require('../db');

router.get('/soldout', function(req, res, next) {
  connection.query('SELECT * from cin where pi="/Mobius/server/soldout"', (error, rows, fields) => {
    if (error) {
      console.error(error);
      res.status(500).send('Internal Server Error');
    }
    console.log(': ', rows);
    res.send(rows);
  });
});

router.get('/error', function(req, res, next) {
  connection.query('SELECT * from cin where pi="/Mobius/server/error" ', (error, rows, fields) => {
    if (error) {
      console.error(error);
      res.status(500).send('Internal Server Error');
    }
    console.log(': ', rows);
    res.send(rows);
  });
});

module.exports = router;