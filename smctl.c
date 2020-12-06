/*
 * File:   smctl.c
 * Author: Faculdade
 *
 * Created on 26 de Maio de 2018, 18:16
 */

#include <xc.h>
#include "smctl.h"

read_ADC(unsigned char ch){
    if (ch > 8) return 0;
    int result;
    ADCON0 = 0b00000001; // liga o conversor    
    __delay_us(10);

    switch(ch){
        case 0:
            ADCHS = 0;
            break;
            
        case 1:
            ADCON0 |= (1<<2);
            ADCHS = 0;
            break;
        
        case 2:
            ADCON0 |= (1<<3);
            ADCHS = 0;
            break;
            
        case 3:
            ADCON0 |= (3<<2);
            ADCHS = 0;
            break;
            
        case 4:
            ADCHS = 0b00000001;
            break;
            
        case 5:
            ADCON0 |= (1<<2);
            ADCHS = 0b00010000;
            break;
            
        case 6:
            ADCON0 |= (1<<3);
            ADCHS = 0b00001000;
            break;
            
        case 7:
            ADCON0 |= (3<<2);
            ADCHS = 0b01000000;
            break;
            
        case 8:
            ADCHS = 0b00000010;
            break;
    }
    ADCON0 |= 2;
    while(ADCON0 & 2);
    result = ADRESH;
    result = (result << 8) | ADRESL;
    return result;
}


void moveMotor(int motor, int direction, unsigned int speed){
    speed *= (MAX_SPEED/100.0);
    if(motor){//motor direita
        if(direction){ //frente pwm no pino 0
            PDC0L = speed & 0b11111111;
            PDC0H = (speed >> 8) & 0b11111111;
            PDC1L = 0;
            PDC1H = 0;
        }
        else{ // tras pwm no pino 2
            PDC0L = 0;
            PDC0H = 0;
            PDC1L = speed & 0b11111111;
            PDC1H = (speed >> 8) & 0b11111111;
        }
    }
    else{//motor da esquerda
        if(direction){ //frente pwm no pino 4
            PDC2L = speed & 0b11111111;
            PDC2H = (speed >> 8) & 0b11111111;
            PDC3L = 0;
            PDC3H = 0;
        }
        else{ // tras pwm no pino 6
            PDC2L = 0;
            PDC2H = 0;
            PDC3L = speed & 0b11111111;
            PDC3H = (speed >> 8) & 0b11111111;
        }
    }
}

void turnMotors(int state){
    if (state){
        PORTBbits.RB6 = 1;
        PORTBbits.RB7 = 1;
    }
    
    else{
        PORTBbits.RB6 = 0;
        PORTBbits.RB7 = 0;
    }
}

void stopMotors(){
    PDC0L = 0;
    PDC0H = 0;
    PDC1L = 0;
    PDC1H = 0;
    PDC2L = 0;
    PDC2H = 0;
    PDC3L = 0;
    PDC3H = 0;
}

void readLine(){
    if (PORTCbits.RC4) bit_clear(&line, 0);
    else               bit_set(&line,   0);
    if (PORTCbits.RC5) bit_clear(&line, 1);
    else               bit_set(&line,   1);
    if (PORTAbits.RA5) bit_clear(&line, 2);
    else               bit_set(&line,   2);
    if (PORTEbits.RE0) bit_clear(&line, 3);
    else               bit_set(&line,   3);
}

void readTarget(){
    if (PORTAbits.RA0) bit_clear(&target, 0);
    else               bit_set(&target,   0);
    if (PORTAbits.RA1) bit_clear(&target, 1);
    else               bit_set(&target,   1);
    if (PORTAbits.RA2) bit_clear(&target, 2);
    else               bit_set(&target,   2);
    if (PORTAbits.RA3) bit_clear(&target, 3);
    else               bit_set(&target,   3);
    if (PORTAbits.RA4) bit_clear(&target, 4);
    else               bit_set(&target,   4);
    if (PORTCbits.RC0) bit_clear(&target, 5);
    else               bit_set(&target,   5);
    if (PORTCbits.RC1) bit_clear(&target, 6);
    else               bit_set(&target,   6);
    if (PORTCbits.RC2) bit_clear(&target, 7);
    else               bit_set(&target,   7);
}
