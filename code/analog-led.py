#CAB 9.14.23 analog-led.py
#Use potentiometer to vary the LED brightness on Lily∞Bot
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


print("analog-LED...")

while True:
    # analog reading and return an integer between 0-65535
    reading = pot_val.read_u16()
    #print(reading)
    scale = int((reading-325)*(65535-1)/(65535-325))
    print(scale)
    led.duty_u16(scale)
    sleep_ms(100)

