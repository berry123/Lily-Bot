#CAB 9.14.23 pwm-led.py
#use pwm to create analog write to an LED to very brightness based upon potentiomater value
#LED on pin 28, potentiomater on pin 27
#https://www.noiresteminist.com/shop

from machine import Pin, ADC, PWM
from utime import sleep_ms

#define inputs and outputs
ledPin = 28
potPin = 27
pot_val = ADC(Pin(potPin))
led = PWM(Pin(ledPin))

# set frequency of pwm signal t o60 Hz
led.freq(60)
#set PWM duty cycle as unsigned 16 bit value between 0-65335


print("pwm-LED...")

while True:
    # analog reading and return an integer between 0-65535
    reading = pot_val.read_u16()
    scale = int(reading*1000/65535)
    for i in range(1024):
        led.duty_u16(i)
        sleep_ms(1)
    for i in range(1023,-1,-1):
        led.duty_u16(i)
        sleep_ms(1)
        