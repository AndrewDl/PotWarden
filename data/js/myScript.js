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

function initHtml(sensorData){
  var count = sensorData.length;
  console.log(`received sensors count: ${count}`);

  const cardGrid = document.getElementById('cardGrid');
  const cardTemplate = document.getElementById('cardTemplate');
  for (let i = 0; i < count; i++) {
    const clone = cardTemplate.content.cloneNode(true);
    const pTags = clone.querySelectorAll('p');
    console.log(`tags count: ${pTags.length}`)

    for (let j = 0; j < pTags.length; j++){
      clone.getElementById(pTags[j].id).id = pTags[j].id + `-${i}`
    }        

    cardGrid.appendChild(clone);
    document.getElementById(`sensor-name-${i}`).innerHTML = `${sensorData[i]["name"]}#${sensorData[i]["id"]}` ;
  }         
}

function updatePage(sensorList){
  var count = sensorList.length;
  console.log(`received sensors count: ${count}`)
  
  const pTag = document.getElementById('cardTemplate').content.querySelectorAll('p');
  console.log(`tags: ${pTag.length}`)

  for(let i=0; i< sensorList.length; i++){
    getSensorValue(i).then(response => {
      console.log('response:' + response);
      document.getElementById(`sensor-raw-${i}`).innerHTML = response["value"];
      document.getElementById(`sensor-value-${i}`).innerHTML = Number.parseFloat(getInvertedPercentage(response["value"], 1600, 3650)).toFixed(2) + '%' ;
      document.getElementById(`time-stamp-${i}`).innerHTML = response["timeStamp"];
    });
    
  }
}

function listSensors(){
  var url = baseUrl + 'sensor/list/'
  return axios.get(url)
  .then(response => response.data)
  .catch(error => {
      console.error('Error fetching card count:', error);
      return 0; // fallback value
  });
}

function getSensorValue(sensorId){
  if(sensorId == null){
    err = "ERROR: sensor ID can't be null"
    console.log(err);
    document.getElementById("moistureData").innerHTML = err;
    return;
  }

  return axios({
    url: baseUrl + 'sensor/data/live/',
    method: 'get',
    headers: {'Content-type': 'application/json; charset=UTF-8'},
    params:{
      id: sensorId
    }
  })
    .then(response => response.data)
    .catch(function (error) {
      console.log(error);
      return 0;
    });  
}

// Sends pour action to REST API
function sendPourAction(deviceId, actionName, value) {
  
  const url = baseUrl + 'action/pour';
  const data = {
    deviceId: deviceId,
    actionName: actionName,
    value: value * 1000 // Convert seconds to milliseconds
  };
  console.log('Pour action:', data);
  axios.post(url, data)
    .then(response => {
      console.log('Pour action sent:', response.data);
    })
    .catch(error => {
      console.error('Error sending pour action:', error);
      
    });
}

document.addEventListener('DOMContentLoaded', function() {
  const button = document.getElementById('control-button');
  const input = document.getElementById('control-input');
  button.addEventListener('click', function() {
    // Example values, replace with your logic to get deviceId and actionName
    const deviceId = 'device1';
    const actionName = 'pour';
    const value = input.value;
    sendPourAction(deviceId, actionName, value);
  });
});

listSensors().then(initHtml);
listSensors().then(updatePage);

setInterval(() => {
  listSensors().then(updatePage);
}, 5000);
//listSensors();
/*

setInterval(() => {
  getDateTime();
  getSensorValue(0);
}, 5000);*/
