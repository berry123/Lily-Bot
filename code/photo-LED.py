#CAB 9.15.23 photo-led.py
#Use photoresistor to vary the LED brightness on the Lily∞Bot
#LED on pin 27, photoresistor on pin 23
#https://www.noiresteminist.com/shop

from machine import Pin, ADC, PWM
from utime import sleep_us

#define inputs and outputs
frequency = 60
photoPin = 27
ledPin = 28
photo_val = ADC(Pin(photoPin))
led = PWM(Pin(ledPin))

# set frequency of pwm signal t o60 Hz
led.freq(frequency)
print("photoresistor-LED...")

while True:
    inmax = 65535
    inmin = 7000
    outmax = 65535
    outmin = 1000
    reading = photo_val.read_u16()
    #mapping function (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min
    scale = int((reading-inmin)*(outmax-outmin)//(inmax-inmin))+outmin
    print("photo: " + str(scale))
    led.duty_u16(scale)
    #sleep_us(1)