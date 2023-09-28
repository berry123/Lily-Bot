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

#define motor pins and PWM for motor speed
PWMA = PWM(Pin(28))
AIN2 = Pin(27, Pin.OUT)
AIN1 = Pin(26, Pin.OUT)
PWMA.freq(60)
BIN1 = Pin(22, Pin.OUT)
BIN2 = Pin(21, Pin.OUT)
PWMB = PWM(Pin(20))
PWMB.freq(60)
motorSpeed = 60000 #65535/2

#define function to drive robot in reverse
def reverse():
    AIN1.value(1)
    AIN2.value(0)
    BIN1.value(1)
    BIN2.value(0)
    PWMA.duty_u16(motorSpeed)
    PWMB.duty_u16(motorSpeed)

#define function to drive robot forward
def forward():
    AIN1.value(0)
    AIN2.value(1)
    BIN1.value(0)
    BIN2.value(1)
    PWMA.duty_u16(motorSpeed)
    PWMB.duty_u16(motorSpeed)

#define function to pivot robot
def pivot():
    AIN1.value(0)
    AIN2.value(0)
    BIN1.value(0)
    BIN2.value(1)
    PWMA.duty_u16(motorSpeed)
    PWMB.duty_u16(motorSpeed)

#define function to stop robot
def stop():
    AIN1.value(0)
    AIN2.value(0)
    BIN1.value(0)
    BIN2.value(0)

#define function to read robot distance in cm from sonar
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
    timepassed = signalon - signaloff
    dist_cm = (timepassed*0.0343)/2
    if dist_cm>60:
        dist_cm=60
    return dist_cm

print("Obstacle Avoidance on Lily∞Bot...")
led.value(1)    #blink LED to indicate robot will move
sleep_ms(100)
led.value(0)

while True:                 #loop code forever
    pin.toggle()            #blink internal LED to indicate robot running
    reading = distance()    #read sonar date for distance
    print(reading)          #print reading to serial monitor

    if reading < 10:        #if reading is less than 10 cm, reverse ad turn robot
        led.value(1)
        stop()
        sleep_ms(100)
        reverse()
        sleep_ms(500)
        stop()
        sleep_ms(100)
        pivot()
        sleep_ms(100)
        stop()
    else:                       # no obstacles, drive robot forward
        led.value(0)
        forward()
        sleep_ms(100)