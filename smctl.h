/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef SMCTL_H
#define	SMCTL_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "mylib.h"
#include "config.h"

#define _XTAL_FREQ 20000000
#define forward      1
#define backward     0
#define right        1
#define left         0
#define ON           1
#define OFF          0
#define MAX_SPEED 1024

unsigned char     target = 0;
unsigned char     line   = 0;

int  read_ADC(unsigned char ch);

//void moveMotor(int motor, int direction, int speed);
/**
 * 
 * @param motor     > binario, indica qual motor(direita ou esquerda) que deve ser acionado
 * @param direction > também binario, indica o sentido de rotação do motor (frente ou atrás)
 * @param speed     > valor percentual de ciclo de trabalho
 */
void moveMotor(int motor, int direction, unsigned int speed);
void turnMotors(int state);
void stopMotors();
void readLine();
void readTarget();

#endif	/* XC_HEADER_TEMPLATE_H */

