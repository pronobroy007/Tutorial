
ARDUINO_PORT = /dev/ttyACM0
BOARD_NAME = arduino:avr:uno

compile:
	arduino-cli compile -b $(BOARD_NAME) -v ./helloWorld/

upload:
	arduino-cli upload -p $(ARDUINO_PORT) ./helloWorld/

SMonito:
	minicom -D $(ARDUINO_PORT) -b 9600
