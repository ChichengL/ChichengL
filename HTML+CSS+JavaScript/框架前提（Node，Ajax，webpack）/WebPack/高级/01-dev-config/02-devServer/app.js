
fetch('/api/hello')
.then(response => response.text())
.then(result=>console.log(result))