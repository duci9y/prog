console.log(15)
for (var i = 0; i < 15; i++) {
	var k = Math.floor(Math.random() * 20) + 1
  console.log(k)

	var correct = Math.floor(Math.random() * 100)

	for (var j = 0; j < k; j++) {
		var flip = Math.floor(Math.random() * 1000) % 2
		var lie = Math.floor(Math.random() * 1000) % 6
		var r = Math.floor(Math.random() * 100)

		var op = '<'
		if (correct > r && !flip) op = '>'
		if (r == correct) op = '='

		console.log(op + ' ' + r.toString() + ' ' + (flip ? 'No' : 'Yes'))
	}

	// console.log('correct: ' + correct.toString())
}
