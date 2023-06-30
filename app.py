import serial
import keyboard
import threading
import sys
import time
import pygame

from time import sleep

running=True
bg_color = pygame.Color(255,0,0)
tsi_max = 43176
tsi_min = 1184

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
    global tsi_max
    global tsi_min

    ser = serial.Serial(
        port="COM6",
        baudrate=115200,
        bytesize=8,
        timeout=2
    )
    
    #ser.write(b'c')

    while(running):
        ser.reset_input_buffer()
        ser.reset_output_buffer()

        out1 = ser.read(1)
        out2 = ser.read(1)

        print("out1, out2: " + str(out1) + "" + str(out2))

        if out1 and out2:
            out1 = ord(out1)
            out2 = ord(out2)

            out = (out2 << 8) | out1
            print(str(time.time()) + " Out:" + str(out))

            h,s,l,a = bg_color.hsla

            h = (out - tsi_min) / (tsi_max - tsi_min)

            h = int(float(h) * 360)

            if ( h > 360 ):
                h = 360

            if ( h < 0 ):
                h = 0

            bg_color.hsla = int(h), int(s), int(l), int(a)

    ser.reset_input_buffer()
    ser.reset_output_buffer()
    print("Exiting....")

def get_input():
    keyboard.wait('space')
    end_serial_com()


thr_serial_com = threading.Thread(target=serial_com)
thr_pygame = threading.Thread(target=pygame_handler)

thr_serial_com.start()
thr_pygame.start()
