# Work with Python 3.6

import discord
import os

token = "NDI2MTUwNDMzMDA3MDc1MzI4.DvRo8g.QPjd6nnKqW5QHTM0SPaJlIgMyZA"

client = discord.Client()

@client.event
async def on_message(message):
    # we do not want the bot to reply to itself
    if message.author == client.user:
        return

    if message.content.startswith('!fishtank'):
        msg = ""
        with open('temp.txt','r') as f:
           temps = f.readlines()
           msg += "Temp: "
           msg += temps[-1].split("$")[1]

        with open('light.txt','r') as f:
           light = f.readlines()
           msg += "Light: "
           msg += light[-1].split("$")[1]

        #msg = 'Hello {0.author.mention}'.format(message)
        await client.send_message(message.channel, msg)

@client.event
async def on_ready():
    print('Logged in as')
    print(client.user.name)
    print(client.user.id)
    print('------')

client.run(token)
