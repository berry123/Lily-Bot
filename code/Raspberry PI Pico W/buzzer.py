#CAB 9.14.23 buzzer.py
#use buzzer to play music on Lily∞Bot
#buzzer on pin 27
#sonar on pins 2 and 
#https://www.noiresteminist.com/shop

#import MicroPico MicroPython libraries
from machine import Pin, PWM
from utime import sleep

#define inputs and outputs
buzzerPin = 26                  #buzzer on Pin 26
buzzer = PWM(Pin(buzzerPin))    #buzzer on PWM as output
buzzer.freq(500)                #PWM frequency is 500 Hz
delay = 500                     #define delay variable
#define song           
song = ["E5","G5","A5","P","E5","G5","B5","A5","P","E5","G5","A5","P","G5","E5"]
#define frequencies for given notes
tones = {
    "C5": 523,
    "CS5": 554,
    "D5": 587,
    "DS5": 622,
    "E5": 659,
    "F5": 698,
    "FS5": 740,
    "G5": 784,
    "GS5": 831,
    "A5": 880,
    "AS5": 932,
    "B5": 988,
}

################# function definitions
#define play tone function
def playtone(frequency):
    buzzer.duty_u16(1000)
    buzzer.freq(frequency)
#define be quiet function
def bequiet():
    buzzer.duty_u16(0)
#define play song function
def playsong(mysong):
    for i in range(len(mysong)):
        if (mysong[i] == "P"):
            bequiet()
        else:
            playtone(tones[mysong[i]])
        sleep(0.3)
    bequiet()

#display starting message
print("Buzzer on Lily...")
#run indefinitely
while True:
    playsong(song)      #play song
    while True:         #only play song once then enter infinite loop
        bequiet()