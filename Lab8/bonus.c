#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <DAQlib.h>
#include <Windows.h>

#define SWITCH0 0
#define SWITCH1 1

#define ON 1
#define OFF 0

#define TRUE 1
#define FALSE 0

#define NUM_DISPLAYS 8
#define ONE_SEC 1000

#define TRUE 1
#define FALSE 0

void scrollMessage(void);
void displayChar( char character, int pos);

int main(void){
	int setupNum;

	printf("To initialize the module, enter 0 for the hardware\n 4 for the simulator: ");
	scanf("%d", &setupNum);

	if (setupDAQ(setupNum) == TRUE)
		scrollMessage();
	else
		printf("An error occurred in the initialization of the DAQ module\n");

	system("PAUSE");
	return 0;
}

void scrollMessage(void){
	int count = 0;
	char message[NUM_DISPLAYS+6] = "SHADES";
	int pos;
	int index;
	int switch0;
	int switch1;
	int delay;

	while (continueSuperLoop()){
		
		switch0 = digitalRead(SWITCH0);
		switch1 = digitalRead(SWITCH1);
		if (switch0 == ON)
			delay = ONE_SEC/2;
		else
			delay = ONE_SEC;
		if (switch1 == OFF){
			pos = count;
			index = 0;
			while (index <= count && pos >= 0){
				if (pos == NUM_DISPLAYS - 1 && message[index] == 0){
					displayWrite(0, pos);
					count = -1;
					break;
				}
				else if (message[index] == 0)
					displayWrite(0, pos);
				else if (pos >= NUM_DISPLAYS)
					;
				else
					displayChar(message[index], pos);
				index++;
				pos--;
			}
		}
		else{
			pos = 0;
			index = count;
			while (index >= 0 && pos <= count){
				if (pos == NUM_DISPLAYS - 1 && message[index] == 0){
					displayWrite(0, pos);
					count = -1;
					break;
				}
				else if (message[index] == 0)
					displayWrite(0, pos);
				else if (pos >= NUM_DISPLAYS)
					;
				else
					displayChar(message[index], pos);
				index--;
				pos++;
			}

		Sleep(delay);
		count++;
		 }
	}
}


void displayChar (char character, int pos){
	int index = character - 65;
	int segmentConversionCapital[] = {238, 254, 156, 252, 158, 142, 190, 110, 96, 112, 174, 
		28, 0, 236, 252, 206, 230, 238, 182, 224, 124, 124, 0, 110, 102, 218};
	
	displayWrite(segmentConversionCapital[index], pos);
}


