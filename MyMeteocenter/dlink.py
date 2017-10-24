#!/usr/bin/env python3

import serial
import time
import json

ser = serial.Serial('/dev/cu.usbmodemFD121')

print('Serial port name: ', ser.name)
print('Is serial port open: ', ser.is_open)
print('Loading data...')

time.sleep(3)

while True:
    print(ser.readline())


#while True:
#    print(ser.readline())
#    z = "{ 'data': { 'Humidity (%)': 56.80,'Temperature': {'C': 21.00, 'F': 69.80}, 'Heat index': {'C': 20.64, 'F': 69.15} } }"

#j = json.loads(z)
#j
#j['data']
#j['data']['Humidity']
#j['data']['Humidity (%)']
#j['data']['Temperature']
#j['data']['Temperature']['C']

#z.decode('utf8')
#j = json.loads(z.decode('utf8'))
#j
#j['data']['Temperature']['C']
