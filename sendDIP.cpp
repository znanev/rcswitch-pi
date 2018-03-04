/*
 Usage: ./send <systemCode> <unitCode> <command>
 Command is 0 for OFF and 1 for ON
 */

#include "RCSwitch.h"
#include <stdlib.h>
#include <stdio.h>

void printUsage(char*);

int main(int argc, char *argv[]) {

     /*
     see https://projects.drogon.net/raspberry-pi/wiringpi/pins/
     for pin mapping of the raspberry pi GPIO connector
     */
    int PIN = 17;

    if (argc != 4)
    {
        printUsage(argv[0]);
        printf("ERROR: Invalid number of arguments specified [%i].\n", argc-1, argv[0]);
        return -1;
    }

    int command  = atoi(argv[3]);

    wiringPiSetupSys();
    printf("Sending: SystemCode[%s] UnitCode[%s] Command[%i]\n", argv[1], argv[2], command);
    RCSwitch mySwitch = RCSwitch();
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(305);
    mySwitch.enableTransmit(PIN);

    switch(command) {
        case 1:
            mySwitch.switchOn(argv[1], argv[2]);
            break;
        case 0:
            mySwitch.switchOff(argv[1], argv[2]);
            break;
        default:
            printf("Command [%i] is unsupported\n", command);
            return -1;
    }
	return 0;
}

void printUsage(char* commandName)
{
    printf("Usage: %s SystemCode UnitCode Command\n\n", commandName);
    printf("SystemCode: \"00000\" - \"11111\"\n");
    printf("UnitCode: \"00000\" - \"11111\"\n");
    printf("Command: 0 (off) or 1 (on)\n\n");
}

