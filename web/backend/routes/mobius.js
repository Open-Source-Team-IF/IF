var express = require('express');
var router = express.Router();

var connection = require('../db');

router.get('/error', function(req, res, next) {
  connection.query('SELECT con FROM cin WHERE pi="/Mobius/server/error" ', (error, rows, fields) => {
    if (error) {
      console.error(error);
      res.status(500).send('Internal Server Error');
    }
    console.log(': ', rows);
    res.send(rows);
  });
});
router.get('/soldout', function(req, res, next) {
  connection.query('SELECT con from cin where pi="/Mobius/server/soldout"', (error, rows, fields) => {
    if (error) {
      console.error(error);
      res.status(500).send('Internal Server Error');
    }
    console.log(': ', rows);
    res.send(rows);
  });
});

router.post('/delerr', function(req, res, next) {
  const task = req.body.task
  connection.query('DELETE FROM cin WHERE (pi="/Mobius/server/error" OR pi="/Mobius/server/soldout") AND con like "%'+task+'%"', (error, rows, fields) => {
    if (error) {
      console.error(error);
      res.status(500).send('Internal Server Error');
    }
    console.log(': ', rows);
    res.send(rows);
  });
});

router.get('/list', function(req, res, next) {
  connection.query('SELECT con FROM cin WHERE pi="/Mobius/web/product"', (error, rows, fields) => {
    if (error) {
      console.error(error);
      res.status(500).send('Internal Server Error');
    }
    console.log(': ', rows);
    res.send(rows);
  });
});
router.post('/delete', function(req, res, next) {
  const product = req.body.product, stand = req.body.stand;
  connection.query('DELETE FROM cin WHERE pi="/Mobius/web/product" AND con like "%'+product+'%'+stand+'%"', (error, rows, fields) => {
    if (error) {
      console.error(error);
      res.status(500).send('Internal Server Error');
    }
    console.log(': ', rows);
    res.send(rows);
  });
});

module.exports = router;