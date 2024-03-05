import hello from './hello'
import imgsrc from './assets/image-20231107213749482.png'

import textContent from './assets/hello.txt'
import './style.css'
import './style.less'

hello()

const img = document.createElement('img')
img.src = imgsrc
document.body.appendChild(img)

const div = document.createElement('div')
div.classList.add('hello')
div.classList.add('div-bg')
div.textContent = textContent
div.style.cssText = "background-color: aliceblue; width:200px; height:200px"
document.body.appendChild(div)

document.body.classList.add('hello')

const button = document.createElement('button')
button.innerText = 'click me'
button.addEventListener('click', () => {
    import(/*webpackChunkName: 'math', webpackPrefetch:true */'./math').then(({add:add})=>{
        console.log(add(1,2))
    })
})

document.body.appendChild(button)
