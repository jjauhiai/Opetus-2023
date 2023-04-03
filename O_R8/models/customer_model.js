const db = require('../database');

const customer = {
  getById: function(id, callback) {
    return db.query('select * from customer where idcustomer=?', [id], callback);
  },
  getAll: function(callback) {
    return db.query('select * from customer', callback);
  },
  add: function(customer, callback) {
    return db.query(
      'insert into customer (first_name,last_name,email,phone,address,city,state,zip_code,credit_limit) values(?,?,?,?,?,?,?,?,?)',
      [customer.first_name, customer.last_name, customer.email,customer.phone, customer.address, customer.city,customer.state,customer.zip_code,customer.credit_limit],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from customer where idcustomer=?', [id], callback);
  },
  update: function(id, customer, callback) {
    return db.query(
      'update customer set first_name=?,last_name=?,email=?,phone=?,address=?,city=?,state=?,zip_code=?,credit_limit=? where idcustomer=?',
      [customer.first_name, customer.last_name, customer.email,customer.phone, customer.address, customer.city,customer.state,customer.zip_code,customer.credit_limit,id],
      callback
    );
  }
};
module.exports = customer;