#obstacleAvoicance.py CAB 9.17.23
#This code will drive the LilyBot forward
#then turn when obstacle is detected with sonar
#https://www.noiresteminist.com/shop

#Carlotta Berry 9.14.23

from machine import Pin, ADC, PWM
from utime import ticks_us, sleep_us, sleep_ms

#define inputs and outputs
ledPin = 18
triggerPin = 17
echoPin = 16
trigger = Pin(triggerPin, Pin.OUT)
echo = Pin(echoPin, Pin.IN)
led = Pin(ledPin, Pin.OUT)
pin = Pin("LED", Pin.OUT)


#define inputs and outputs
PWMA = PWM(Pin(28))
AIN2 = Pin(27, Pin.OUT)
AIN1 = Pin(26, Pin.OUT)
PWMA.freq(60)

BIN1 = Pin(22, Pin.OUT)
BIN2 = Pin(21, Pin.OUT)
PWMB = PWM(Pin(20))
PWMB.freq(60)
motorSpeed = 65535

def reverse():
    AIN1.value(1)
    AIN2.value(0)
    BIN1.value(1)
    BIN2.value(0)
    PWMA.duty_u16(motorSpeed)
    PWMB.duty_u16(motorSpeed)

def forward():
    AIN1.value(0)
    AIN2.value(1)
    BIN1.value(0)
    BIN2.value(1)
    PWMA.duty_u16(motorSpeed)
    PWMB.duty_u16(motorSpeed)

def pivot():
    AIN1.value(0)
    AIN2.value(0)
    BIN1.value(0)
    BIN2.value(1)
    PWMA.duty_u16(motorSpeed)
    PWMB.duty_u16(motorSpeed)

def stop():
    AIN1.value(0)
    AIN2.value(0)
    BIN1.value(0)
    BIN2.value(0)

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

print("Obstacle Avoidance on Lily∞Bot...")

while True:
    reading = distance()
    print(reading)

    if reading<10:
        led.value(1)
        stop()
        sleep_ms(100)
        reverse()
        sleep_ms(500)
        pivot()
        sleep_ms(500)
        reading = distance()
    else:
        led.value(0)
        forward()
        sleep_ms(100)
        reading = distance()