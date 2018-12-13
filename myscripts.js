var light 
var temp
var food
function getLight(){
    var request = new XMLHttpRequest();
    
    request.open('GET', 'http://localhost:5000/api/light', true);
    request.onload = function () {
    
      // Begin accessing JSON data here
      var light = JSON.parse(this.response);
      light = light.reverse(); 

      if (request.status >= 200 && request.status < 400) {
	var ctx = document.getElementById("light");
	var myLineChart = new Chart(ctx, {
	  type: 'line',
	  data: {
	    label:["0","1","2","3","4","5","6","7","8","9"],
	    datasets:[{
	      label:"light",
	      data:[light[0],light[1],light[2],light[3],light[4],light[5],light[6],light[7],light[8],light[9]],
	      backgroundColor: [
	        'rgba(255, 99, 132, 0.2)',
	        'rgba(54, 162, 235, 0.2)',
	        'rgba(255, 206, 86, 0.2)',
	        'rgba(75, 192, 192, 0.2)',
	        'rgba(153, 102, 255, 0.2)',
	        'rgba(255, 159, 64, 0.2)'
	      ],
	      borderColor: [
	        'rgba(255,99,132,1)',
	        'rgba(54, 162, 235, 1)',
	        'rgba(255, 206, 86, 1)',
	        'rgba(75, 192, 192, 1)',
	        'rgba(153, 102, 255, 1)',
	        'rgba(255, 159, 64, 1)'
	      ],
	      borderWidth: 1
	    }]
	  },
	  options: {
	    scales: {
	      yAxes: [{
	        ticks: {
	          beginAtZero:true
	        }
	      }]
	    }
	  }
	});
      } else {
        console.log('error');
      }
    }
    
    request.send();
}
function getTemp(){
    var request = new XMLHttpRequest();
    
    request.open('GET', 'http://localhost:5000/api/temp', true);
    request.onload = function () {
    
      // Begin accessing JSON data here
      temp = JSON.parse(this.response);
      temp = temp.reverse(); 
      if (request.status >= 200 && request.status < 400) {
	var ctx = document.getElementById("temp");
	var myLineChart = new Chart(ctx, {
	  type: 'line',
	  data: {
	    label:["0","1","2","3","4","5","6","7","8","9"],
	    datasets:[{
	      label:"temp",
	      data:[temp[0],temp[1],temp[2],temp[3],temp[4],temp[5],temp[6],temp[7],temp[8],temp[9]],
	      backgroundColor: [
	        'rgba(255, 99, 132, 0.2)',
	        'rgba(54, 162, 235, 0.2)',
	        'rgba(255, 206, 86, 0.2)',
	        'rgba(75, 192, 192, 0.2)',
	        'rgba(153, 102, 255, 0.2)',
	        'rgba(255, 159, 64, 0.2)'
	      ],
	      borderColor: [
	        'rgba(255,99,132,1)',
	        'rgba(54, 162, 235, 1)',
	        'rgba(255, 206, 86, 1)',
	        'rgba(75, 192, 192, 1)',
	        'rgba(153, 102, 255, 1)',
	        'rgba(255, 159, 64, 1)'
	      ],
	      borderWidth: 1
	    }]
	  },
	  options: {
	    scales: {
	      yAxes: [{
	        ticks: {
	          beginAtZero:true
	        }
	      }]
	    }
	  }
	});
      } else {
        console.log('error');
      }
    }
    
    request.send();
}

function getFood(){
    var request = new XMLHttpRequest();
    
    request.open('GET', 'http://localhost:5000/api/food', true);
    request.onload = function () {
    
      // Begin accessing JSON data here
      food = JSON.parse(this.response);
    
      if (request.status >= 200 && request.status < 400) {
	var paragraph = document.getElementById("food");
	var text = document.createTextNode(food[food.length()-1]);
	paragraph.appendChild(text);
      } else {
        console.log('error');
      }
    }
    
    request.send();
}
getLight();
getFood();
getTemp();

