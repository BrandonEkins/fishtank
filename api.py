#!flask/bin/python
from flask import Flask 
from flask import json

app = Flask(__name__)

@app.route('/api/light')

def light():
    lightInfo = {}
    with open('light.txt') as f:
        lines = f.readlines()
    for line in lines:
        line = line.split("$")  
        lightInfo[line[0].strip()] = line[1].strip()
        
    response = app.response_class(
        response=json.dumps(lightInfo),
        status=200,
        mimetype='application/json'
    )
    return response
@app.route('/api/temp')
def temp():
    tempInfo = {}
    with open('temp.txt') as f:
        lines = f.readlines()
    for line in lines:
        line = line.split("$")  
        tempInfo[line[0].strip()] = line[1].strip()
        
    response = app.response_class(
        response=json.dumps(tempInfo),
        status=200,
        mimetype='application/json'
    )
    return response


if __name__ == '__main__':
    app.run(debug=True)
