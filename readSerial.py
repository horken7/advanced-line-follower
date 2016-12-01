'''
Script to open port to Arduino serial
and save data to a .csv file. 

Need to import pySerial, more info can be found at:
http://pyserial.readthedocs.io/en/latest/pyserial.html

'''
import serial
import time

ser = serial.Serial('/dev/tty.usbmodem1421', 9600, timeout=1)
# The /dev/tty.xxxxxx is the port for reading Arduino serial and can differ between computers
time.sleep(1)

logfile = open('arduinoReadings.csv', 'a')

while 1:
	line = ser.readline() 
	a =  "%s" % (line)
	print a	
	logfile.write(a)
        logfile.flush()    
logfile.close()
ser.close()