#!/usr/bin/env python3

import sys
import tty
import select
import serial
import termios


def getch():
	fd = sys.stdin.fileno()
	old = termios.tcgetattr(fd)
	try:
		tty.setraw(fd)

		result = []
		for i in range(3):
			c = sys.stdin.read(1)
			result.append(c)
			if ord(c) == 0x3:
				raise KeyboardInterrupt()
			elif i == 0 and ord(c) != 0x1b:
				return c.encode()
	finally:
		termios.tcsetattr(fd, termios.TCSADRAIN, old)

	raw = ''.join(result).encode()
	if   raw == b'\x1b[A':
		return b'u'
	elif raw == b'\x1b[B':
		return b'd'
	elif raw == b'\x1b[C':
		return b'r'
	elif raw == b'\x1b[D':
		return b'l'
	else:
		return b'x'

# Devices in order
devs = sys.argv[1:] + [
	'/dev/rfcomm0',
	'/dev/ttyACM0',
]

for dev in devs:
	try:
		ser = serial.Serial(dev, 115200)
	except serial.serialutil.SerialException:
		pass
	else:
		break
else:
	print('No dev found')
	exit(1)

print('Connected to ' + dev)

while True:
	try:
		direction = getch()

		print('send ->',  repr(direction.decode()))
		ser.write(direction)
	except KeyboardInterrupt:
		sys.stdout.write('\b\b  \n')
		break
