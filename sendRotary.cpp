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

    int systemCode = atoi(argv[1]);
    int unitCode = atoi(argv[2]);
    int command  = atoi(argv[3]);

    if (systemCode < 0 || systemCode > 4)
    {
        printUsage(argv[0]);
        printf("ERROR: Invalid system code specified [%i]. Valid range is 1-4\n", systemCode);
        return -1;
    }

    if (unitCode < 0 || unitCode > 4)
    {
        printUsage(argv[0]);
        printf("ERROR: Invalid unit code specified [%i]. Valid range is 1-4\n", unitCode);
        return -1;
    }

    if (command < 0 || command > 1)
    {
        printUsage(argv[0]);
        printf("ERROR: Invalid command specified [%i]. Valid values are: 0 (off) or 1 (on).\n", command);
        return -1;
    }

    wiringPiSetupSys();
    printf("Sending: SystemCode[%i] UnitCode[%i] Command[%i]\n", systemCode, unitCode, command);
    RCSwitch mySwitch = RCSwitch();
    mySwitch.setProtocol(1);
    mySwitch.setPulseLength(447);
    mySwitch.enableTransmit(PIN);

    switch(command) {
        case 1:
            mySwitch.switchOn(systemCode, unitCode);
            break;
        case 0:
            mySwitch.switchOff(systemCode, unitCode);
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
    printf("SystemCode: 1-4\n");
    printf("UnitCode: 1-4\n");
    printf("Command: 0 (off) or 1 (on)\n\n");
}
