#motor.py CAB 9.14.23
#This code will drive the LilyBot using the TB6612 motor drive
#https://www.noiresteminist.com/shop

#Carlotta Berry 9.14.23

#import libraries from MicroPico MicroPython
from machine import Pin, PWM
from time import sleep_ms 

#define inputs and outputs
PWMA = PWM(Pin(28))
AIN2 = Pin(27, Pin.OUT)
AIN1 = Pin(26, Pin.OUT)
PWMA.freq(60)           #define PWMA frequency

BIN1 = Pin(22, Pin.OUT)
BIN2 = Pin(21, Pin.OUT)
PWMB = PWM(Pin(20))
PWMB.freq(60)           #define PWMB frequency
motorSpeed = 65535      #define motor speed

#define reverse function
def reverse():
    AIN1.value(1)
    AIN2.value(0)
    BIN1.value(1)
    BIN2.value(0)
    PWMA.duty_u16(motorSpeed)
    PWMB.duty_u16(motorSpeed)

#define forward function
def forward():
    AIN1.value(0)
    AIN2.value(1)
    BIN1.value(0)
    BIN2.value(1)
    PWMA.duty_u16(motorSpeed)
    PWMB.duty_u16(motorSpeed)

#define stop function
def stop():
    AIN1.value(0)
    AIN2.value(0)
    BIN1.value(0)
    BIN2.value(0)

#print starting message to serial monitor
print("Motor control on Lily∞Bot...")

#run indefinitely
while True:
    forward()           #drive robot forward
    sleep_ms(500)       #wait 1/2 a second
    stop()              #stop robot
    sleep_ms(500)       #wait 1/2 a second
    reverse()           #drive robot backward
    sleep_ms(500)       #wait 1/2 a second
    stop()              #stop robot
    sleep_ms(500)       #wait 1/2 a second