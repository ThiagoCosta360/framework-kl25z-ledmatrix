/*!
 * @copyright   © 2020 UFAM - Federal University of Amazonas.
 *
 * @brief       Implementation of the class "mkl_Matrix".
 *
 * @file        mkl_Matrix.cpp
 * @version     1.0
 * @date        March 24, 2020
 *
 * @section     HARDWARES & SOFTWARES
 *              +board        FRDM-KL25Z da NXP.
 *              +processor    MKL25Z128VLK4 - ARM Cortex-M0+.
 *              +compiler     MCUXpresso Integrated Development Environment (IDE)
 *              +manual       L25P80M48SF0RM, Rev.3, September 2012.
 *              +revisions    Version (date): Brief description.
 *                             ++ 1.0 (March 24, 2020): Initial version.
 *
 * @section     AUTHORS & DEVELOPERS
 *              +institution  Federal University of Amazonas.
 *              +courses      Computer Engineering / Electrical Engineering.
 *              +teacher      Miguel Grimm <miguelgrimm@gmail.com>
 *              +student      Initial version:
 *                             ++ Thiago Costa Antunes Afonso <tcaa@icomp.ufam.edu.br>
 *
 * @section     LICENSE
 *
 *              GNU General Public License (GNU GPL).
 *
 *              This program is free software; You can redistribute it
 *              and/or modification in accordance with the terms of the "GNU General Public
 *              License" published by the Free Software Foundation; Be a
 *              version 3 of the license or any later version.
 *
 *              This program is distributed in the hope that it will be useful,
 *              but WITHOUT ANY WARRANTY; Without the implied warranty of
 *              MARKETING OR USE FOR A PARTICULAR PURPOSE.
 *              See the "GNU General Public License" website for more details.
 *
 * @htmlonly    http://www.gnu.org/copyleft/gpl.html
 */

#ifndef MKL_MATRIX_H_
#define MKL_MATRIX_H_

#include <cstdint>
#include "./mkl_MatrixPatterns.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "mkl_MAX7219.h"


class mkl_Matrix
{

private:
    /* This class is the interface of the chip MAX7219 */
    mkl_MAX7219 max;

    /* This class contain the array of patterns from ascii table */
    mkl_MatrixPatterns ascii;
    /* We keep track of the led-status in this array */
    uint8_t status[8];

    /* This is the string saved for the panel */
    char *panelBuffer;
    /* This is the position of the char being displayed in the panel string*/
    uint8_t panelPosition;
    /* This is the pattern of the next char to be displayed in the panel string*/
    uint8_t transition[8];
    /* This is the position of the column being displayed of the transition pattern*/
    uint8_t transitionPosition;
    /* This is the column being displayed of the transition pattern*/
    uint8_t columnBuffer;

public:
    /* 
    * Create a new mkl_Matrix
    * Params :
    * dataPin		pin on the Arduino where data gets shifted out
    * clockPin		pin for the clock
    * csPin		    pin for selecting the device
    */
    explicit mkl_Matrix(gpio_Pin dataPin, gpio_Pin clkPin, gpio_Pin csPin);

    /* 
    * Switch all Leds on the display off. 
    * Params:
    */
    void clearDisplay();

    /* 
    * Switch all Leds on the display on. 
    * Params:
    */
    void setDisplay();

    /* 
    * Switch all Leds on the display as the pattern bits. 
    * Params:
    * pattern  the matrix of bits that represent the leds
    */
    void setStatus(uint8_t pattern[8]);

    /*
    * Update the led states with the values of the status 
    * Params: 
    */
    void writeStatus();

    /* 
    * Set the status of a single Led.
    * Params :
    * row	the row of the Led (0..7)
    * col	the column of the Led (0..7)
    * state	If true the led is switched on, 
    *		if false it is switched off
    */
    void setLed(int row, int col, bool state);

    /* 
    * Set all 8 Led's in a row to a new state
    * Params:
    * row	row which is to be set (0..7)
    * value	each bit set to 1 will light up the
    *		corresponding Led.
    */
    void setRow(uint8_t row, uint8_t value);

    /* 
    * Set all 8 Led's in a column to a new state
    * Params:
    * column	column which is to be set (0..7)
    * value	each bit set to 1 will light up the
    * corresponding Led.
    */
    void setColumn(uint8_t col, uint8_t value);

    /*
    * Update the led matrix status
    * Params: 
    * pattern  the matrix of bits that represent the leds
    */
    void updateStatus(uint8_t pattern[8]);

    /*
    * Print on the console the current led status
    * Params: 
    */
    void printStatus();

    /*
    * Set the entire matix to a new pattern in ascii table, 
    * Params: 
    * letter    the character in ascii code
    */
    void setChar(char letter);

    /*
    * Invert each led state, 
    * Params: 
    */
    void invertStatus();

    /*
    * Create a new panel string. 
    * Params: 
    * panelBuffer   the string of characters that will roll on the matrix
    */
    void createPanel(const char *panelBuffer);

    /*
    * Shift all the led states one position left and add the next panel column. 
    * Params: 
    */
    void nextPanelFrame();

    /*
    * Shift all the led states to the left. 
    * Params: 
    * distance number of columns to be shifted (1..7)
    */
    void moveStatusLeft(uint8_t distance);

    /*
    * Shift all the led states to the rigth. 
    * Params: 
    * distance number of columns to be shifted (1..7)
    */
    void moveStatusRigth(uint8_t distance);

    /*
    * Shift all the led states up. 
    * Params: 
    * distance number of columns to be shifted (1..7)
    */
    void moveStatusUp(uint8_t distance);

    /*
    * Shift all the led states down. 
    * Params: 
    * distance number of columns to be shifted (1..7)
    */
    void moveStatusDown(uint8_t distance);

    /*
    * Save in a number the bits of the column in the pattern. 
    * Params: 
    * col   the position of the column to be saved
    * pattenr   a matrix of bits
    */
    void getColumn(uint8_t col, uint8_t pattern[8]);

    /*
    * Save in a bit matrix transition the values of pattenr  
    * Params: 
    * pattenr   a matrix of bits
    */
    void setTransition(uint8_t pattern[8]);
    
};

#endif //  MKL_MATRIX_H_