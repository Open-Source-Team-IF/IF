var mysql = require('mysql');

var connection = mysql.createConnection({
    host     : '146.56.166.36',
    user     : 'dbadm',
    password : 'qwe123',
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