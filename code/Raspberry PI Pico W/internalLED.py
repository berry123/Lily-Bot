
#CAB 9.14.23 buzzer.py
#blink internal LED on Raspberry PI Pico W on Lily∞Bot
#LED on pin 25
#https://www.noiresteminist.com/shop

from machine import Pin
from utime import sleep

pin = Pin("LED", Pin.OUT)

print("LED starts flashing...")
while True:
    pin.toggle()
    sleep(1) # sleep 1sec

