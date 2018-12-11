import paho.mqtt.client as mqtt
import datetime
import subprocess
buttontime = 0
def on_connect(client, userdata, flags, rc):
    print("Connected with result code "+str(rc))
    client.subscribe("temp")
    client.subscribe("light")
    client.subscribe("button")

def on_message(client, userdata, msg):
    print(msg.topic+" "+str(msg.payload))
    if msg.topic == "light":
        f = open("light.txt","a")
        st = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S')
        f.write(st +" $ "+msg.payload + "\n")
        f.close()
    elif msg.topic == "button":
        print("button")
        if buttontime == 0:
            buttontime == 1
        else:
            subprocess.Popen("sudo python tankMove.py", shell=True)
        client.publish("command", "light")
        client.publish("command", "temp")
    elif msg.topic == "temp":
        f = open("temp.txt","a")
        st = datetime.datetime.now().strftime('%Y-%m-%d %H:%M:%S') + " $ " + msg.payload + "\n"
        print(st)
        f.write(st)
        f.close()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message
client.connect("localhost", 1883, 60)
client.loop_forever()

#https://pypi.org/project/paho-mqtt/
