#CAB 9.14.23 sonar.py
#Use sonar to control LED brighness on Lily∞Bot
#LED on pin 28, potentiomater on pin 27
#https://www.noiresteminist.com/shop
#VCC to pin 40
#Echo to pin 2
#Trigger to pin 3
#ground to GND
#LED to pin 28

from machine import Pin, ADC, PWM
from utime import ticks_us, sleep_us, sleep_ms

#define inputs and outputs
ledPin = 28
triggerPin = 3
echoPin = 2
#led = Pin(ledPin, Pin.OUT)
led = PWM(Pin(ledPin))
led.freq(60)
trigger = Pin(triggerPin, Pin.OUT)
echo = Pin(echoPin, Pin.IN)


print("Sonar on Lily∞...")


# Will return an integer between out_min and out_max
def convert(x, i_m, i_M, o_m, o_M):
    return max(min(o_M, (x - i_m) * (o_M - o_m) // (i_M - i_m) + o_m), o_m)

################# function definitions
def distance():
    timepassed=0
    signalon = 0
    signaloff = 0
    trigger.low()
    sleep_us(2)
    trigger.high()
    sleep_us(5)
    trigger.low()
    while echo.value() == 0:
        signaloff = ticks_us()
    while echo.value() == 1:
        signalon = ticks_us()
    #print(signalon)
    #print(signaloff)
    timepassed = signalon - signaloff
    #print(timepassed)
    dist_cm = (timepassed*0.0343)/2
    if dist_cm>60:
        dist_cm=60
    return dist_cm

################## Main ########################
while True:
    reading = distance()
    #print(reading)
    scale = convert(reading, 10, 60, 0, 60000)
    print(scale)
    led.duty_u16(int(scale))
    sleep_ms(100)

############### Mapping Functions ####################################
# Will return a float
#def convert(x, in_min, in_max, out_min, out_max):
#    return (x - in_min) * (out_max - out_min) / (in_max - in_min) + out_min


# Will return a integer
#def convert(x, in_min, in_max, out_min, out_max):
#    return (x - in_min) * (out_max - out_min) // (in_max - in_min) + out_min


# Test
#for i in range(200):
#    print(i, convert(i, 40, 80, 0, 1023))