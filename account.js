var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var passportLocalMongoose = require('passport-local-mongoose');

var Account = new Schema({
    username: String,
    password: String,
    email: String,
    phone: String,
    name: String,
    alias: String,
    topLevel: Number,
    topLevelTime: Date,
    codeScore: Number
});

Account.plugin(passportLocalMongoose, {usernameLowerCase: true});

module.exports = mongoose.model('Account', Account);