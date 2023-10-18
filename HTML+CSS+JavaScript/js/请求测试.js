(async () => {
  const res = await fetch('https://yesno.wtf/api')
  console.log((await res.json()).answer)
})()