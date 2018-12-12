var light 
var temp
var feed
function getLight(){
    var request = new XMLHttpRequest();
    
    request.open('GET', 'ipaddr', true);
    request.onload = function () {
    
      // Begin accessing JSON data here
      var light = JSON.parse(this.response);
    
      if (request.status >= 200 && request.status < 400) {
        data.forEach(light => {
          console.log(light[0]);
        });
      } else {
        console.log('error');
      }
    }
    
    request.send();
}
