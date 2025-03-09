const fs = require('fs');

let config = JSON.parse(fs.readFileSync('config.json', 'utf8'));
let email_user = config.email.user;
let email_password = config.email.password;
let sql_host = config.sql.host;
let sql_port = config.sql.port;
let sql_password = config.sql.password;
let redis_host = config.redis.host;
let redis_port = config.redis.port;
let redis_password = config.redis.password;
let code_prefix = "code_";


module.exports = {email_password, email_user, sql_host, sql_port, sql_password, redis_host, redis_port, redis_password, code_prefix}
