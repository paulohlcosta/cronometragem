# cronometragem
All the files for timing system, to be uploaded in separate boards

This is a system that makes the timing for a drag racing track.
It is composed by some equipments, each one with it own code:

## pinheirinho_fitaled
Arduino nano-based, with four LDR sensors activated by red lasers.
Indicates PRE-STAGE and STAGE, also counts time between green light, launch and finishing.
The trigger can be connected here.
Communicates with the finish through RS485-serial.
Communicates with the webserver through software serial.
Communicates with the christmas tree with HIGH/LOW output and input.

## pinheirinho_lampadas_semsensor
Arduino nano-based, can work completely standalone.
It has 4 outputs to the christmas tree lights (yellow, yellow, yellow and green).
The trigger can be connected here.

## webserver_access_point_cronometragem
ESP8266 / NodeMCU D1 mini based, this device creates an wifi network to be accessed and displays the times.

## chegada
Arduino nano-based, with two LDR sensors activated by red lasers. It can indicate the winner by lighting LEDs.
Can work completely standalone.
Communicates with the launch through RS485-serial.

If you have any doubt please create a Pull request in https://github.com/paulohlcosta/cronometragem/
