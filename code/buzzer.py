#CAB 9.14.23 buzzer.py
#use buzzer to play music on Lily∞Bot
#buzzer on pin 27
#sonar on pins 2 and 
#https://www.noiresteminist.com/shop


from machine import Pin, ADC, PWM
from utime import ticks_us, sleep_us, sleep_ms, sleep
from "notes.h" import tones

#define inputs and outputs
ledPin = 27
triggerPin = 3
echoPin = 2
buzzerPin = 28

led = Pin(ledPin, Pin.OUT)
#buzzer = Pin(buzzerPin,Pin.OUT)
buzzer = PWM(Pin(buzzerPin))
buzzer.freq(500)
#buzzer.duty_u16(1000)
#sleep(1)
#buzzer.duty_u16(0)
trigger = Pin(triggerPin, Pin.OUT)
echo = Pin(echoPin, Pin.IN)
delay = 500
song = ["E5","G5","A5","P","E5","G5","B5","A5","P","E5","G5","A5","P","G5","E5"]
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
    timepassed = signalon - signaloff
    dist_cm = (timepassed*0.0343)/2
    if dist_cm>60:
        dist_cm=60

def playtone(frequency):
    buzzer.duty_u16(1000)
    buzzer.freq(frequency)
def bequiet():
    buzzer.duty_u16(0)
def playsong(mysong):
    for i in range(len(mysong)):
        if (mysong[i] == "P"):
            bequiet()
        else:
            playtone(tones[mysong[i]])
        sleep(0.3)
    bequiet()

print("Buzzer on Lily...")

while True:
    playsong(song)
    while True:
        bequiet()