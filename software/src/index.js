
function updateClock() {
    const c2rawtime = new Date(); // current date
    const c2hr = c2rawtime.getHours();
    const c2mn = c2rawtime.getMinutes();
    
    console.log(c2hr, c2mn)

    // call this function again in 2000ms
    setTimeout(updateClock, 2000);
}
updateClock(); // initial call