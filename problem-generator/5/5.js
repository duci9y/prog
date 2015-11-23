console.log(50)
for (var i = 0; i < 50; i++) {
	var N = Math.floor(Math.random() * 100) + 5
	console.log(N)
	var t = ''
	for (var j = 0; j < N; j++) {
		var q = Math.floor(Math.random() * 100) + 5
		if ((j-1) == N) t += q.toString()
		else t += q.toString() + ' '
	}
	console.log(t)
}
