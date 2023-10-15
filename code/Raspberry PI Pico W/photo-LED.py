#CAB 9.15.23 photo-led.py
#Use photoresistor to vary the LED brightness on the Lily∞Bot
#LED on pin 27, photoresistor on pin 23
#https://www.noiresteminist.com/shop

from machine import Pin, ADC, PWM
from utime import sleep_us

#define inputs and outputs
photoPin = 27   #photoresistor on pin 27
ledPin = 28     #led on pin 28
frequency = 60  #frequency for pulse width modulator
photo_val = ADC(Pin(photoPin))  #photoresistor as analog input on ADC
led = PWM(Pin(ledPin))          #LED as analog output on PWM
led.freq(frequency)             #set frequency of pwm signal to 60 Hz
print("photoresistor-LED...")   #print starting message to serial monitor
inmax = 65535                   #set maximum input value from photoresistor
inmin = 7000                    #set minimum input value from photoresistor
outmax = 65535                  #set maximum output value for LED duty cycle
outmin = 1000                   #set minimum output value for LED duty cycle

while True:                     #run indefinitely
    reading = photo_val.read_u16()  #red photoresistor value
    #mapping function (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min
    scale = int((reading-inmin)*(outmax-outmin)//(inmax-inmin))+outmin #scale photoresistor value
    print("photo: " + str(scale))   #print scaled photoresistor value
    led.duty_u16(scale)             #write value to LED duty cycle
    sleep_us(1)                    #insert a 1 us delay