import serial
import keyboard
import threading
import sys

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

    while(running):
        #print("Out: a")
        ser.write(b'c')
        #out='/x55'
        out = ser.read(1)

        if out:
            print("Out:" + str(ord(out)))

    ser.close()
    print("Exiting....")
    sys.exit()

def get_input():
    keyboard.wait('space')
    end_serial_com()

thr_serial_com = threading.Thread(target=serial_com)
thr_input = threading.Thread(target=get_input)

thr_serial_com.start()
thr_input.start()