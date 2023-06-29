import serial
import keyboard
import threading
import sys
import time
import pygame

from time import sleep

running=True
color_rgb = (255,255,0)

def pygame_handler():
    global running
    global color_rgb

    pygame.init();
    screen = pygame.display.set_mode((300,300))
    clock = pygame.time.Clock()

    while running:
        for event in pygame.event.get():
            if event.type == pygame.QUIT:
                running = False

        screen.fill(pygame.Color(color_rgb))
        pygame.display.flip()
        clock.tick(60)

def end_serial_com():
    global running
    running=False

def serial_com():
    global color_rgb

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

        out = ord(ser.read(1))

        if out:
            print(str(time.time()) + " Out:" + str(out))

        #print("in_waiting: " + str(ser.in_waiting))
        #print("out_waiting : " + str(ser.out_waiting))
        if (out > 255 ) :
            out = 255

        color_rgb = (out, 255, 0)

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
