import serial
import keyboard
import threading
import sys
import time
from time import sleep

running=True

def end_serial_com():
    global running
    running=False

def serial_com():
    ser = serial.Serial(
        port="COM5",
        baudrate=115200,
        bytesize=8,
        timeout=2
    )
    
    #ser.write(b'c')

    while(running):
        ser.reset_input_buffer()
        ser.reset_output_buffer()

        out = ser.read(1)

        if out:
            print(str(time.time()) + " Out:" + str(ord(out)))

        #print("in_waiting: " + str(ser.in_waiting))
        #print("out_waiting: " + str(ser.out_waiting))

        # send a character to continue the transmission
        if (ser.in_waiting == 0):
            ser.write(b'c') 

        #sleep(300/1000) # sleep 300 ms 


    ser.reset_input_buffer()
    ser.reset_output_buffer()
    print("Exiting....")

def get_input():
    keyboard.wait('space')
    end_serial_com()

thr_serial_com = threading.Thread(target=serial_com)
thr_input = threading.Thread(target=get_input)

thr_serial_com.start()
thr_input.start()
