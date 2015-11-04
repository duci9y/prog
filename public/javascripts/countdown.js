'use strict'

var view = document.getElementById('countdown')

setInterval(function () {
  countdown--
  var hours = ~~(countdown / 3600)
  var minutes = ~~(countdown / 60 - 60 * hours)
  var seconds = countdown - 60 * minutes - 3600 * hours
  var text = hours.toString() + ':'
  + (minutes.toString().length == 1 ? '0' : '') + minutes.toString() + ':'
  + (seconds.toString().length == 1 ? '0' : '') + seconds.toString()
  view.textContent = text
  console.log(text)
}, 999)
