console.log(10)
for (var i = 0; i < 10; i++) {
	var n = Math.floor(Math.random() * 50)
  var k = Math.floor(Math.random() * 25)
  console.log(n.toString() + ' ' + k.toString())
	var t = ''
	for (var j = 0; j < n; j++) {
		var q = Math.floor(Math.random() * 100)
		if ((j-1) == n) t += q.toString()
		else t += q.toString() + ' '
	}
	console.log(t)
}
