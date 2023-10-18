const http = require('http');

const server = http.createServer(function(request, response) {
    response.end(`
        <!DOCTYPE html>
        <html lang="en">
        <head>
            <meta charset="UTF-8">
            <meta name="viewport" content="width=device-width, initial-scale=1.0">
            <title>Document</title>
            <style>
                td{
                    padding:20px 40px;
                }
                table,td{
                    border-collapse:collapse;
                }
                table tr:nth-child(odd){
                    background-color: #ccc;
                }
                table tr:nth-child(even){
                    background-color: #eee;
                }
            </style>
        </head>
        <body>
            <table border="1">
                <tr>
                    <td></td>
                    <td></td>
                    <td></td> 
                </tr>
                <tr>
                    <td></td>
                    <td></td>
                    <td></td> 
                </tr>
                <tr>
                    <td></td>
                    <td></td>
                    <td></td> 
                </tr>
                <tr>
                    <td></td>
                    <td></td>
                    <td></td> 
                </tr>
            </table>
        </body>
        <script>
            const tds = document.querySelectorAll('td')
            //遍历
            tds.forEach(item=>{
                item.onclick = function(){
                    this.style.backgroundColor = '#222'
                }
            })
        </script>
        </html>
    `)
})

server.listen(9000,()=>{
    console.log('服务器启动成功')
})