var express = require('express');
var passport = require('passport');
var School = require('../models').School;
var router = express.Router();
var sys = require('sys');
var fs = require('fs');
var path = require('path');
var spawn = require('child_process').spawn;
var AdmZip = require('adm-zip');
var randomstring = require('randomstring');

var testcases = [{
	input: 'testcases\n',
	output: 'testcases\n'
},
{
	input: '',
	output: '5777\n'
}];

router.get('/login', function(req, res) {
	if (req.user) res.redirect('/');
	else res.render('login');
});
router.post('/login', function(req, res, next) {
	passport.authenticate('local', function(err, user, info) {
		if (err) return res.render('login', { error: err });

		if (!user) return res.render('login', { error: info });

		req.logIn(user, function(err) {
			if (err) return res.render('login', { error: err });
			return res.redirect('/');
		});
	})(req, res, next);
});

router.all('*', function(req, res, next) {
	res.locals.user = req.user;
	if (!req.user) res.redirect('/login');
	else next();
});

router.get('/', function(req, res, next) {
	res.render('index', { });
});

router.post('/', function(req, res) {
	if (!req.body.problem || !req.body.lang || !req.body.code) {
		res.render('index', { message: 'Missing information.' });
		return;
	}
	if (parseInt(req.body.problem) < 0 || parseInt(req.body.problem) > 10) {
		res.render('index', { message: 'Problem ' + req.body.problem + ' does not exist.' });
		return;
	}
	if (req.user.codeCorrects.indexOf(req.body.problem) != -1) {
		res.render('index', { message: 'You have already solved problem ' + req.body.problem + '.' });
		return;
	}
	
	var wd = path.join(__dirname, '../sandbox/' + req.user.username + '/' + req.body.problem);
	var sourcename = req.body.problem + '.' + req.body.lang;

	function finishedWithSuccess(success) {
		req.body.bet = Math.abs(parseInt(req.body.bet));
		var newScore = req.user.codeScore + req.body.bet * (success ? 1 : -1);
		var message = success ? ('Good job! +' + req.body.bet.toString() + '!') : ('Incorrect solution. -' + req.body.bet.toString() + '.');
		
		var updates = {
			$set: { codeScore: newScore }
		};
		if (success) updates.$push = { codeCorrects: req.body.problem };
		
		School.update({ username: req.user.username }, updates, function(error, user) {
			if (error) {
				console.log('error saving: ' + error);
				res.render('index', { message: 'Error updating database. Contact event master.' });
			}
			else res.render('index', { message: message, success: success, newScore: newScore.toString() }); // newScore.toString because 0 is falsy
		});
	}
	function finishedWithError(runtime) {
		var newScore = req.user.codeScore - parseInt(req.body.bet) / 2;
		var message = (runtime ? 'Runtime' : 'Compilation') + ' error. You lose half your bet. Attached are some files for your debugging pleasure.';

		School.update({ username: req.user.username }, { $set: { codeScore: newScore }}, function(error, user) {
			if (error) {
				console.log('error saving: ' + error);
				res.render('index', { message: 'Error updating database. Contact event master.' });
			}
			else {
				var zip = new AdmZip();
				var zipName = randomstring.generate(5) + '.zip';
				zip.addLocalFolder(wd);
				zip.writeZip(path.join(__dirname, '../public/' + zipName));
				res.render('index', { message: message, success: false, attach: zipName });
			}
		});
	}

	function runTests(exec) {
		exec.stdin.setEncoding = 'utf-8';

		var output = '';
		var error = '';
		exec.stdout.on('data', function(data) {
			output += data;
		});
		exec.stderr.on('data', function(data) {
			error += data;
		});
		exec.stdout.on('end', function(err) {
			fs.writeFile(path.join(wd, 'stdout.log'), output, function(err) {
				if (err) console.log(err);
			});
		});
		exec.stderr.on('end', function(err) {
			fs.writeFile(path.join(wd, 'stderr.log'), error, function(err) {
				if (err) console.log(err);
			});
		});

		exec.on('close', function(code) {
			console.log('submission exited with code ' + code.toString());
			if (code != 0) {
				finishedWithError(true);
			}
			if (output == testcases[parseInt(req.body.problem)].output) {
				finishedWithSuccess(true);
			}
			else finishedWithSuccess(false);
		});

		exec.stdin.write(testcases[parseInt(req.body.problem)].input);
	}

	function proceed() {
		fs.writeFile(path.join(wd, sourcename), req.body.code, function(err) {
			if (err) {
				console.log(err);
				res.render('error', { message: 'Error writing to disk.', error: { status: 500 } });
				return;
			}

			if (req.body.lang == 'cpp' || req.body.lang == 'c') {
				var gcc = spawn((req.body.lang == 'cpp' ? 'g++' : 'gcc'), [path.join(wd, sourcename), '-o', path.join(wd, req.body.problem)]);

				var stdout = '';
				var stderr = '';
				gcc.stdout.on('data', function(data) {
					stdout += data;
				});
				gcc.stderr.on('data', function(data) {
					stderr += data;
				});
				gcc.stdout.on('end', function() {
					fs.writeFile(path.join(wd, 'stdout-gcc.log'), stdout, function(err) {
						if (err) console.log(err);
					});
				});
				gcc.stderr.on('end', function() {
					fs.writeFile(path.join(wd, 'stderr-gcc.log'), stderr, function(err) {
						if (err) console.log(err);
					});
				});

				gcc.on('close', function(code) {
					if (code != 0) {
						finishedWithError(false);
						return;
					}
					var exec = spawn(path.join(wd, req.body.problem));
					runTests(exec);
				});
			}
			if (req.body.lang == 'py') {
				var exec = spawn('python', [path.join(wd, sourcename)]);
				runTests(exec);
			}
			if (req.body.lang == 'js') {
				var exec = spawn('node', [path.join(wd, sourcename)]);
				runTests(exec);
			}
		});
	}

	fs.mkdir(path.join(__dirname, '../sandbox'), function(err) {
		fs.mkdir(path.join(__dirname, '../sandbox/' + req.user.username), function(err) {
			fs.mkdir(wd, function(err) {
				proceed();
			})
		})
	});
});

router.get('/leaderboard', function(req, res, next) {
	School.find().sort('-codeScore').select('name alias codeScore').exec(function(err, results) {
		if (!err) {
			res.render('leaderboard', { results: results });
		} else {
			console.log(err);
			res.render('leaderboard', { error: new Error('Error displaying the leaderboard.') });
		}
	});
});

module.exports = router;
