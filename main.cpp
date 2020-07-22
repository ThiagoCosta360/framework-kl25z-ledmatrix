#include "MKL25Z4.h"
#include "./mkl_GPIOPort.h"
#include "./mkl_MATRIX.h"
#include <chrono>

// mkl_GPIOPort SPI_CS(gpio_PTC4);
mkl_GPIOPort ledVerde(gpio_PTB19); //! LED da placa
mkl_Matrix matrix(gpio_PTC6, gpio_PTC5, gpio_PTC4);
uint8_t pattern_happy_face[8] =
    {
        0b00111100,
        0b01000010,
        0b10100101,
        0b10000001,
        0b10100101,
        0b10011001,
        0b01000010,
        0b00111100};

uint8_t pattern_angy_face[8] =
    {
        0b00111100,
        0b01000010,
        0b10100101,
        0b10000001,
        0b10111101,
        0b10000001,
        0b01000010,
        0b00111100};

uint8_t pattern_sad_face[8] =
    {
        0b00111100,
        0b01000010,
        0b10100101,
        0b10000001,
        0b10011001,
        0b10100101,
        0b01000010,
        0b00111100};

/*!
 *   @fn         setupLedRGB.
 *
 *   @brief      Configura o Led verde
 *
 */
void setupLedRGB()
{
  ledVerde.setPortMode(gpio_output);
  ledVerde.writeBit(true);
}


/*!
 *   @fn         delayMs.
 *
 *   @brief      Implementa delay de código de cycle_number milissegundos.
 *
 *   @param[in]  time - tempo em milissegundos de delay desejado.
 *
 */
void delayMs(int time)
{
  int i;
  int j;

  for (i = 0; i < time; i++)
  {
    for (j = 0; j < 7000; j++)
    {
    }
  }
}

int main()
{
  setupLedRGB();

   matrix.writePattern(pattern_happy_face);
   ledVerde.writeBit(true);

   delayMs(100);
   matrix.setLed(2, 2, false);
   delayMs(50);
   matrix.setLed(2, 2, true);
   delayMs(100);

   matrix.writePattern(pattern_sad_face);
   matrix.setColumn(0, 0b11000011);
   matrix.setColumn(7, 0b11000011);
   ledVerde.writeBit(false);
   delayMs(50);

  while (true)
  {
    delayMs(100);
    matrix.setChar('A');
    delayMs(100);
    matrix.setChar('R');
    delayMs(100);
    matrix.setChar('Q');
    delayMs(100);
    matrix.setChar('U');
    delayMs(100);
    matrix.setChar('I');
    delayMs(100);
    matrix.setChar('T');
    delayMs(100);
    matrix.setChar('E');
    delayMs(100);
    matrix.setChar('T');
    delayMs(100);
    matrix.setChar('U');
    delayMs(100);
    matrix.setChar('R');
    delayMs(100);
    matrix.setChar('A');


  }

  return 0;
}
