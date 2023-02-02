const mysql = require('mysql');
const connection = mysql.createPool({
  host: '127.0.0.1',
  user: 'test_user2',
  password: 'xxxx',
  database: 'netdb'
});
module.exports = connection;