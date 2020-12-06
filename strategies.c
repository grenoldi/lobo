#include <xc.h>
#include "strategies.h"

 void delayTMR1(int tms){
    T1CON = 0b10000000;
    for (int i = 0; i < tms; i++){
        TMR1 = 60537;
        T1CONbits.TMR1ON = 1;
        while(PIR1bits.TMR1IF == 0);
        readTarget();
        if(target){
            state = ATTACKING;
            break;
        }
        T1CONbits.TMR1ON = 0;
        PIR1bits.TMR1IF  = 0;
    }
}

void searchRoutine(unsigned char * message, State state){
    getFirstMove(message);
    getFirstAttack(message);
    getStrategy(message);
}

void attackRoutine(){
    switch(target){
        case 0:
            readLine();
            if(line) state = RUNNING;
            else     state = SEARCHING;
            break;
        case  1:
            rotate(right);
            delayTMR1(300);
            stopMotors();
            break;
        case  2:
            rotate(right);
            break;
        case  3:
            rotate(right);
            break;
        case  4:
            moveMotor(right, forward, 100);
            moveMotor(left, forward, 100);
            break;
        case  6:
            moveMotor(right, forward, 100);
            moveMotor(left, forward, 100);
            break;
        case  8: 
            rotate(left);
            break;
        case 10: 
            moveMotor(right, forward, 100);
            moveMotor(left, forward, 100);
            break;
        case 12: 
            moveMotor(right, forward, 100);
            moveMotor(left, forward, 100);
            break;
        case 14: 
            moveMotor(right, forward, 100);
            moveMotor(left, forward, 100);
            break;
        case 16: 
            rotate(left);
            break;
        case 24: 
            rotate(left);
            break;
        case 32: 
            rotate(right);
            break;
    }
}

void saveYourselfRoutine(){
    //readLine();
    switch(line){
        case 0:
            readTarget();
            state = SEARCHING;
            break;
        case  1:
            arch(left, backward, 50);
            break;
        case  2:
            arch(right, backward, 50);
            break;
        case  3:
            moveMotor(left,  backward, 50);
            moveMotor(right, backward, 50);
            break;
        case  4: 
            arch(right, forward, 50);
            break;
        case  5:
            arch(left, forward, 50);
            break;
        case  6:
            arch(right, forward, 50);
            break;
        //case  7: break; //pouco provavel
        case  8:
            arch(left, forward, 50);
            break;
        case  9:
            arch(left, forward, 50);
            break;
        case 10:
            arch(right, forward, 50);
            break;
        //case 11: break; //pouco provavel
        case 12:
            moveMotor(left,  forward, 50);
            moveMotor(right, forward, 50);
            break;
        //case 13: break; //pouco provavel
        //case 14: break; //pouco provavel
        //case 15: break; //quase impossivel!
    }
}

void getFirstMove(unsigned char* message){
    if(message[1] == 'a');
    else if      (message[1] == 'b') {
        rotate(right);
        delayTMR1(100);
        stopMotors();
        message[1] = 'a';
    }
    else if (message[1] == 'c') {
        rotate(left);
        delayTMR1(100);
        stopMotors();
        message[1] = 'a';
    }
    else if (message[1] == 'd') {
        arch(right, backward, 100, 20);
        message[1] = 'a';
    }
    else if (message[1] == 'd') {
        arch(left, backward, 100, 20);
        message[1] = 'a';
    }
    else if (message[1] == 'e') {
        moveMotor(right, backward, 50);
        moveMotor(left,  backward, 50);
        message[1] = 'a';
    }
}

void getFirstAttack(unsigned char* message){
    if (message[2] == 'a');
    
    else if(message[2] == 'b'){
        arch(right, forward, 100, 100);
        message[2] = 'a';
    }
    
    else if(message[2] == 'c'){
        arch(left, forward, 100, 100);
        message[2] = 'a';
    }
}

void getStrategy(unsigned char * message){
    if (message[3] == 'a'){
        moveMotor(right, forward, 80);
        moveMotor(left,  forward, 80);
    }
    
    else if (message[3] == 'b'){
        rotate(right);
    }
    
    else if (message[3] == 'c'){
        rotate(left);
    }
    
    else if(message[3] == 'd'){
        moveMotor(right, forward, 30);
        moveMotor(left,  forward, 30);
    }
}

void rotate(int side){
    if(side){
        moveMotor(right, backward, 100);
        moveMotor(left,   forward, 100);
    }
    
    else{
        moveMotor(right, forward, 100);
        moveMotor(left, backward, 100);
    }
}

void arch(int side, int direction, int time, int speed){
    if(side){
        if(direction){
            moveMotor(right,  forward, speed - 10);
            moveMotor(left,   forward, speed + 10);
            delayTMR1(time);
        }
        
        else{
            moveMotor(right,  backward, speed - 10);
            moveMotor(left,   backward, speed + 10);
            delayTMR1(time);
        }
    }
    
    else {
        if(direction){
            moveMotor(right,  forward, speed + 10);
            moveMotor(left,   forward, speed - 10);
            delayTMR1(time);
            stopMotors();
        }
        
        else{
            moveMotor(right,  backward, speed + 10);
            moveMotor(left,   backward, speed - 10);
            delayTMR1(time);
            stopMotors();
        }
    }
}

