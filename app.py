import serial
import keyboard
import threading
import sys
import time
import pygame

from time import sleep

running=True
bg_color = pygame.Color(255,0,0)
tsi_max = 160
tsi_min = 20

def pygame_handler():
    global running
    global bg_color

    pygame.init();
    screen = pygame.display.set_mode((300,300))
    clock = pygame.time.Clock()

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        screen.fill(bg_color)
        pygame.display.flip()
        clock.tick(60)

def end_serial_com():
    global running
    running=False

def serial_com():
    global bg_color

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

            out = ord(out)

            h,s,l,a = bg_color.hsla

            h = (out - tsi_min) / (tsi_max - tsi_min) 

            bg_color.hsla = int(float(h) * 360), int(s), int(l), int(a)

        # send a character to continue the transmission
        if (ser.in_waiting == 0):
            ser.write(b'c') 

        # sleep(300/1000) # sleep 300 ms 

    ser.reset_input_buffer()
    ser.reset_output_buffer()
    print("Exiting....")

def get_input():
    keyboard.wait('space')
    end_serial_com()


thr_serial_com = threading.Thread(target=serial_com)
#thr_input = threading.Thread(target=get_input)
thr_pygame = threading.Thread(target=pygame_handler)

thr_serial_com.start()
#thr_input.start()
thr_pygame.start()
