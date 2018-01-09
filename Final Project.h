/*Author: Marcus van der Sande
 Student ID: 18944141
 Email: marcus.v@telus.net
 Lab #8: Scrolling Message
 
 Purpose: Program that writes a string of characters on a 7-Segment Dislpay
 */


#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include <Windows.h>
#include <DAQlib.h>

#define ON 1
#define OFF 0
#define TRUE 1
#define FALSE 0
#define NUM_DISPLAY 8
#define SPACE_CHAR 0
#define maxlength 20
#define length1 5
#define length2 8
#define SPEEDSW 1
#define DIRECTIONSW 0



/*HELLO*/
int message1[] = { 72 69 44 44 79 };
/*GOODBYE*/
int message2[] = { 71 79 79 68 66 89 69 };

/*Function Prototypes*/
void ScrollingMessage(void);
void makeArray(int input[], int output[], int lenthOutput);
void displayArray(int dispArray);
void moveArray(int moveArray[], int length, int direction);
int length;

/*Main Function*/

int main (void){
    int setupNum;
    
    printf("Please enter the DAQ setup number (1 for Hardware; 4 for Simulator):\n");
    scanf("%i", &setupNum);
    
    if (setupDAQ(setupNum) == TRUE)
        ScrollingMessage();
    
    else{
        printf("ERROR: cannot initialize system\n");
    }
    
    system("PAUSE");
    return 0;
}


void ScrollingMessage(){
    int wordNum;
    int length;
    int workArray[maxlength];
    
    do{
        printf("Choose a word to display:\n  1. HELLO\n\n 2. GOODBYE\n\n");
        scanf("%i", &wordNum);
    } while (wordNum != 1 && wordNum != 2);
    
    if (wordNum == 1){
        length = NUM_DISPLAY + 5;
        makeArray(message2, workArray, length);
    }
    else{
        length = NUM_DISPLAY + 8;
        makeArray(message2, workArray, length);
    }
    
    while (continueSuperLoop() == TRUE){
        displayArray(workArray);
        
        moveArray(workArray, length, digitalRead(0));
        
        if (digitalRead(1) == TRUE)
            Sleep(500);
        else
            Sleep(1000);
    }
}

/*Tells workFunction which array to use*/
void makeArray(int input[], int output[], int lengthOutput){
    
    int index;
    for (index = 0; index < NUM_DISPLAY; index++)
        output[index] = 0;
    
    for (; index < lengthOutput; index++)
        output[index] = input[index - NUM_DISPLAY];
}

/*Displays array on DAQ board*/
void displayArray(int dispArray[]){
    int counter;
    for (counter = 0; counter < NUM_DISPLAY; counter++){
        displayWrite(dispArray[counter], NUM_DISPLAY - counter - 1);
        
    }
}

/*Decides which direction the message will move based on position of switch*/
void moveArray(int moveArray[], int length, int direction){
    int index;
    int temp;
    if (direction == 1){
        temp = moveArray[length - 1];
        for (index = length - 1; index > 0, index--)
            moveArray[index] = moveArray[index - 1];
        moveArray[index] = temp;
    }
    else{
        temp = moveArray[index];
        for (index = 0; index < length - 1; index++)
            moveArray[index] = moveArray[index + 1];
        moveArray[index] = temp;
        
    }
}