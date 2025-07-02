//let baseUrl = "http://pot-warden/"
let baseUrl = ""

function getPercentage(value, min, max) {
  if (max === min) return 0; // avoid division by zero
  const clampedValue = Math.min(Math.max(value, min), max);
  const percentage = ((clampedValue - min) / (max - min)) * 100;
  return percentage;
}

function getInvertedPercentage(value, min, max) {
  if (max === min) return 0; // avoid division by zero
  const clampedValue = Math.min(Math.max(value, min), max);
  const percentage = ((max - clampedValue) / (max - min)) * 100;
  return percentage;
}

function getDateTime(){
  axios({
    url: baseUrl + 'time/',
    method: 'get',
    headers: {'Content-type': 'text/html; charset=UTF-8'}
  })
    .then(function (response) {
      document.getElementById("moistureTime").innerHTML = response.data;
      console.log(response);
    })
    .catch(function (error) {
      console.log(error);
    });  
}

function getSensorValue(sensorId){
  if(sensorId == null){
    err = "ERROR: sensor ID can't be null"
    console.log(err);
    document.getElementById("moistureData").innerHTML = err;
    return;
  }

  axios({
    url: baseUrl + 'sensor/',
    method: 'get',
    headers: {'Content-type': 'text/html; charset=UTF-8'},
    params:{
      id: sensorId
    }
  })
    .then(function (response) {
      document.getElementById("moistureData").innerHTML = response.data;
      document.getElementById("moistureDataPercent").innerHTML = getInvertedPercentage(response.data, 1600, 3650);
      console.log(response);
    })
    .catch(function (error) {
      console.log(error);
    });  
}

setInterval(() => {
  getDateTime();
  getSensorValue(0);
}, 5000);