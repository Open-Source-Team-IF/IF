var mysql = require('mysql');

var connection = mysql.createConnection({
    host     : '192.168.47.142',
    user     : 'spring',
    password : '0346',
    database : 'mobiusdb'
  });
  
  connection.connect(function (err) {
    if (err) {
      console.error('mysql connection error');
      console.error(err);
      throw err;
      }
  });
  
  module.exports = connection;