#CAB 9.14.23 buzzer.py
#blink the LED on the Lily∞Bot
#LED on pin 28
#https://www.noiresteminist.com/shop

import machine
import utime 

led = machine.Pin(28, machine.Pin.OUT)

print("LED flast test 2...")

delay = 0.5

while True:
    led.value(1)
    utime.sleep(delay)
    led.value(0)
    utime.sleep(delay)