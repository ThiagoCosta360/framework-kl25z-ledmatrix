/*!
 * @copyright   © 2020 UFAM - Federal University of Amazonas.
 *
 * @brief       Implementation of the class "mkl_MatrixPatterns".
 *
 * @file        mkl_MatrixPatterns.cpp
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

#ifndef MKL_MATRIXPATTERNS_H_
#define MKL_MATRIXPATTERNS_H_

#include <cstdint>

class mkl_MatrixPatterns
{
private:
    // Set the acii values in the array
    void createData();

public:
    /* 
    * Create a new mkl_Matrix
    * Params :
    */
    explicit mkl_MatrixPatterns();

    //Public Array of patterns used in Led Matrix 
    uint8_t patterns[128][8];
};

#endif //  MKL_MATRIXPATTERNS_H_
