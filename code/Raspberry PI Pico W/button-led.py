#buzzer.py CAB 9.14.23
#use button to control LED on Lily∞Bot
#LED on pin 28, button on pin 26
#button connected between 3.3V and pin 26
#https://www.noiresteminist.com/shop

#import MicroPico Micro Python Libraries
from machine import Pin
from time import sleep 

#define inputs and output pins
ledPin = 28     #LED on pin 28
buttonPin = 26  #button on pin 26 other side to 3.3V
led = Pin(ledPin, Pin.OUT) #define LED as output
#define button as input with pull down resistor
button = Pin(buttonPin, Pin.IN, Pin.PULL_DOWN)
delay = 0.5 #define delay variable as 0.5 seconds
#print starting message to serial monitor
print("Button control of LED...")
#run indefinitely
while True:
    print(button.value()) #print button press
    if button.value():    #if button value is 1
        led.toggle()      #toggle led
        sleep(delay)      #wait 0.5 seconds