from sense_hat import SenseHat as shat
import time
import keyboard

import _thread

global flag
global terminate

flag = 0
terminate = 0

sh = shat()

file = "log.csv"

def write_labels():
	with open(file, 'a+') as f:
		f.write('Temperature' + ',' + 'Humidity' + ',' + 'Pressure' + '\n')

def write_empty_line():
	with open(file, 'a+') as f:
		f.write('\n')

def append_to_file(data):
	with open(file, 'a+') as f:
		entry = str(round(data['t'],2)) + ',' + str(round(data['h'], 0)) + ',' + str(round(data['p'], 2)) + '\n'
		f.write(entry)

def get_sensor_data():
	t = sh.get_temperature()
	h = sh.get_humidity()
	p = sh.get_pressure()
	return {'t' : t, 'h' : h, 'p' : p}



def logger_function():
	print("Logging... Press enter to stop")
	global flag
	while flag == 0:
		append_to_file(get_sensor_data())
		time.sleep(1)
	print("Logging stopped!")
	global terminate
	terminate = 1
	return

def keyboard_function():
	input()
	global flag
	flag = 1
	return

write_labels()

try:
	t1 = _thread.start_new_thread(logger_function, ())
	time.sleep(0.5)
	_thread.start_new_thread(keyboard_function, ())

except Exception as e:
	print("error: " + str(e))

while terminate == 0:
	pass

write_empty_line()
