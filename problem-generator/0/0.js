console.log(10)
for (var i = 0; i < 10; i++) {
	var r = Math.floor(Math.random() * 1000)
	console.log(r)
	var t = ''
	for (var j = 0; j < r; j++) {
		var q = Math.floor(Math.random() * 10000)
		if ((j-1) == r) t += q.toString()
		else t += q.toString() + ' '
	}
	console.log(t)
}
