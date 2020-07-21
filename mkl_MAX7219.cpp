#include "mkl_MAX7219.h"

mkl_MAX7219::mkl_MAX7219(gpio_Pin mosiPin, gpio_Pin clkPin, gpio_Pin csPin) : SPI_MOSI(mosiPin), SPI_CLK(clkPin), SPI_CS(csPin)
{
	SPI_MOSI.setPortMode(gpio_output);
	SPI_MOSI.writeBit(true); //true = high

	SPI_CS.setPortMode(gpio_output);
	SPI_CS.writeBit(true);

	SPI_CLK.setPortMode(gpio_output);
	SPI_CLK.writeBit(true);

	writeCode(OP_DECODEMODE, 0x00);	 // Decoding off
	writeCode(OP_INTENSITY, 0x08);	 // Brightness to intermediate
	writeCode(OP_SCANLIMIT, 0x07);	 // Scan limit = 7
	writeCode(OP_SHUTDOWN, 0x01);	 // Normal operation mode
	writeCode(OP_DISPLAYTEST, 0x0F); // Enable display test
	writeCode(OP_DIGIT0, 0x00);		 // Clear row 0.
	writeCode(OP_DIGIT1, 0x00);		 // Clear row 1.
	writeCode(OP_DIGIT2, 0x00);		 // Clear row 2.
	writeCode(OP_DIGIT3, 0x00);		 // Clear row 3.
	writeCode(OP_DIGIT4, 0x00);		 // Clear row 4.
	writeCode(OP_DIGIT5, 0x00);		 // Clear row 5.
	writeCode(OP_DIGIT6, 0x00);		 // Clear row 6.
	writeCode(OP_DIGIT7, 0x00);		 // Clear row 7.
	writeCode(OP_DISPLAYTEST, 0x00); // Disable display test
}

void mkl_MAX7219::spiTransfer(uint8_t data)
{
	for (int i = 0; i < 8; i++)
	{
		SPI_MOSI.writeBit(data & 0b10000000);
		data = data << 1;

		SPI_CLK.writeBit(true);
		SPI_CLK.writeBit(false);
	}
}

void mkl_MAX7219::writeCode(uint8_t msb, uint8_t lsb)
{
	SPI_CS.writeBit(false);
	spiTransfer(msb);
	spiTransfer(lsb);
	SPI_CS.writeBit(true);
}

void mkl_MAX7219::setScanLimit(uint8_t scanLimit)
{
	writeCode(OP_SCANLIMIT, scanLimit);
}

void mkl_MAX7219::setIntensity(uint8_t intensity)
{
	writeCode(OP_INTENSITY, intensity);
}

void mkl_MAX7219::shutdown(bool status)
{
	writeCode(OP_SHUTDOWN, (uint8_t)status);
}