#CAB 9.14.23 analog-led.py
#Use potentiometer to vary the LED blink rate on Lily∞Bot
#LED on pin 28, potentiomater on pin 27
#https://www.noiresteminist.com/shop


from machine import Pin, ADC
from utime import sleep, sleep_ms, sleep_us


pot_val = ADC(27)

led = Pin(28, Pin.OUT)

print("POT-LED...")

while True:
    reading = pot_val.read_u16()
    scale = int(reading*1000/65535)
    print("POT:")
    print(scale)
    led.value(1)
    sleep_ms(scale)
    led.value(0)
    sleep_ms(scale)