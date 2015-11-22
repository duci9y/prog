console.log(10)
for (var i = 0; i < 10; i++) {
	var N = Math.floor(Math.random() * 1000)
  var M = Math.floor(Math.random() * 500000)
  var Q = Math.floor(Math.random() * 5) + 2

  console.log(N.toString() + ' ' + M.toString() + ' ' + Q.toString())

	for (var j = 0; j < Q; j++) {
		var r = Math.floor(Math.random() * N)
		console.log(r)
	}
}
