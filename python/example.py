#!/usr/bin/python

from robointerface import *
from time import sleep

ri = RoboInterface()
if ri.hasInterface():
	ri.SetMotor(1, 'r', 4) # slow right
	sleep(1)
	ri.SetMotor(1, 'l') # left with max speed

	while not ri.Digital(1): # while endpoint is not reached
		sleep(0.001)

	ri.SetMotor(1, 's') # stop

ri.close()
