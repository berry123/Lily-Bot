#buzzer.py CAB 9.14.13
#use button co control LED on Lily∞Bot
#LED on pin 28, button on pin 26
#button connected between 3.3V and pin 26
#https://www.noiresteminist.com/shop


from machine import Pin
from time import sleep 

#define inputs and outputs
ledPin = 28
buttonPin = 26

led = Pin(ledPin, Pin.OUT)
button = Pin(buttonPin, Pin.IN, Pin.PULL_DOWN)
delay = 0.5

print("Button control of LED...")

while True:
    print(button.value())
    if button.value():
        led.toggle()
        sleep(delay)