const mysql = require('mysql');
const connection = mysql.createPool({
  host: '127.0.0.1',
  user: 'banker3',
  password: 'xxxx',
  database: 'atm_project'
});
module.exports = connection;