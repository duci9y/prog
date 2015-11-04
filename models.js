var mongoose = require('mongoose');
var Schema = mongoose.Schema;
var passportLocalMongoose = require('passport-local-mongoose');

var School = new Schema({
    username: String,
    password: String,
    email: String,
    name: String,
    alias: String,
    teacher: String,
    phone: String,
    teamCode: Number,
    topLevel: {
        type: Number,
        default: 0
    },
    topLevelTime: {
        type: Date,
        default: Date.now
    },
    codeScore: {
        type: Number,
        default: 20
    },
    codeCorrects: {
        type: [String],
        default: []
    },
    participants: [{
        name: String,
        eventName: {
            type: String,
            validate: function(v) {
                return (v == 'code' || v == 'play' || v == 'style' || v == 'stroke' || v == 'capture' || v == 'mix' || v == 'ask')
            }
        }
    }],
    scores: [{
    	eventName: {
            type: String,
            validate: function(v) {
                return (v == 'code' || v == 'play' || v == 'style' || v == 'stroke' || v == 'capture' || v == 'mix' || v == 'ask')
            }
        },
        value: Number
    }]
});

School.plugin(passportLocalMongoose, {
    usernameLowerCase: true,
    digestAlgorithm: 'sha1'
});

module.exports = {
	School: mongoose.model('School', School)
};
