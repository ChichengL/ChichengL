import hello from './hello'
import imgsrc from './assets/image-20231107213749482.png'

import textContent from './assets/hello.txt'
hello()

const img = document.createElement('img')
img.src = imgsrc
document.body.appendChild(img)

const div = document.createElement('div')
div.textContent = textContent
div.style.cssText = "background-color: aliceblue; width:200px; height:200px"
document.body.appendChild(div)