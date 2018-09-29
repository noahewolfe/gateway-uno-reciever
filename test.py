import serial
import time
import datetime

port = "COM8"

ard = serial.Serial(port, 9600, timeout=5)
time.sleep(2)
while True:
    data = ard.readline()[:-2] #the last bit gets rid of the new-line chars
    if data:
        print(data)
