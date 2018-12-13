###!flask/bin/python
from flask import Flask 
from flask import json
from flask_cors import CORS 

app = Flask(__name__)
CORS(app)


@app.route('/')
def hello():
    return "Hello World"

@app.route('/api/food')
def food():
    feedInfo = []
    with open('food.txt') as f:
        lines = f.readlines()
    for line in lines:
        line = line.split("$")  
        feedInfo.append= line[1].strip()
        
    response = app.response_class(
        response=json.dumps(feedInfo),
        status=200,
        mimetype='application/json'
    )
    return response


@app.route('/api/light')
def light():
    lightInfo = []
    with open('light.txt') as f:
        lines = f.readlines()
    for line in lines:
        line = line.split("$")  
        lightInfo.append(line[1].strip())
        
    response = app.response_class(
        response=json.dumps(lightInfo),
        status=200,
        mimetype='application/json'
    )
    return response

@app.route('/api/temp')
def temp():
    tempInfo = []
    with open('temp.txt') as f:
        lines = f.readlines()
    for line in lines:
        line = line.split("$")  
        tempInfo.append(line[1].strip())
        
    response = app.response_class(
        response=json.dumps(tempInfo),
        status=200,
        mimetype='application/json'
    )
    return response


if __name__ == '__main__':
    app.run(host='0.0.0.0')

