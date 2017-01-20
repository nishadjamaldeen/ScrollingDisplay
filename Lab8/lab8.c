/*Name: Nishad Jamaldeen
 *Date: 30th November 2015
 *Student No.: 16062151
 *Lab Section: L1R
 *Email: nishadjamaldeen@alumni.ubc.ca
 *Project: Scrolling Message
 *Purpose: To scroll a string of characters across
 *the 7-segment display and have it loop continuously
 *by having the string start over once it passes the end
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <DAQlib.h>
#include <Windows.h>


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

/*Takes each character in the string and
 *displays the first character in the right
 *most slot. In the next second, the first character
 *is displayed in the second right most space and the
 *second character in the right most space. Essentially 
 *each character moves one over to the left and this 
 *sequnece will continue until the last character has 
 *passed out of the display. At this point, the loop
 *will repeat itself.
*/

void scrollMessage(void){
	int count = 0;
	char message[NUM_DISPLAYS+6] = "SHADES";
	int pos;
	int index;

	while (continueSuperLoop()){
		pos = count;
		index = 0;

		while (index <= count && pos >= 0){
			if (pos == NUM_DISPLAYS - 1 && message[index] == 0){ //Test to determine if the last character has reached the left most space//
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
		Sleep(ONE_SEC);
		count++;
	 }
}


void displayChar (char character, int pos){
	int index;
	int segmentConversion[] = {238, 62, 156, 252, 158, 142, 246, 110, 96, 120, 174, 
		28, 0, 42, 252, 206, 230, 10, 182, 224, 124, 124, 0, 110, 102, 218}; //An array containing the data for each character. Some characters like m and w cannot be formed.//

	if (character >= 65 && character <= 90){ //Using ASCII values to determine the character//
		index = character - 65; //Upper case character//
		displayWrite(segmentConversion[index], pos);
	}
	else if (character >= 97 && character <=122){
		index = character - 97; //Lower case characters//
		displayWrite(segmentConversion[index], pos);
	}
	else if (character = 32) //Consideration for a 'SPACE'//
		displayWrite(0, pos);
}



