#include "mkl_MATRIX.h"

mkl_Matrix::mkl_Matrix(gpio_Pin mosiPin, gpio_Pin clkPin, gpio_Pin csPin) : max(mosiPin, clkPin, csPin)
{
}

void mkl_Matrix::clearDisplay()
{
	for (int i = 1; i <= 8; i++)
		status[i - 1] = 0;
	writeStatus();
}

void mkl_Matrix::setDisplay()
{
	for (int i = 1; i <= 8; i++)
		status[i - 1] = 255;
	writeStatus();
}

void mkl_Matrix::setStatus(uint8_t pattern[8])
{
	for (int i = 0; i < 8; i++)
		status[i] = pattern[i];
}

void mkl_Matrix::writeStatus()
{
	for (int i = 1; i <= 8; i++)
		setRow(i, status[i - 1]);
}

void mkl_Matrix::setLed(int row, int col, bool state)
{
	status[row] = (status[row] & ~(1 << col)) | (state << col);
	writeStatus();
}

void mkl_Matrix::setRow(uint8_t row, uint8_t value)
{
	max.writeCode(row, value);
}

void mkl_Matrix::setColumn(uint8_t col, uint8_t value)
{
	for (int i = 0; i < 8; i++)
		status[i] = (status[i] & ~(1 << col)) | (((value >> i) & 1) << col);
	writeStatus();
}

void mkl_Matrix::printStatus()
{
	int statusRow;
	for (int i = 0; i < 8; i++)
	{
		statusRow = status[i];
		for (int j = 0; j < 8; j++)
		{
			printf("%d", statusRow & 0b10000000);
			statusRow = statusRow << 1;
		}
		printf("\n");
	}
}

void mkl_Matrix::invertStatus()
{
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			status[i] = (status[i] ^ (1 << j));
	writeStatus();
}

void mkl_Matrix::moveStatusLeft(uint8_t distance)
{
	for (int i = 0; i < 8; i++)
		status[i] = (status[i] << distance);
	writeStatus();
}

void mkl_Matrix::moveStatusRigth(uint8_t distance)
{
	for (int i = 0; i < 8; i++)
		status[i] = (status[i] >> distance);
	writeStatus();
}

void mkl_Matrix::moveStatusUp(uint8_t distance)
{
	for (int i = 0; i < 8; i++)
	{
		if ((i + distance) > 8)
			status[i] = status[i + distance];
		else
			status[i] = 0;
	}
	writeStatus();
}

void mkl_Matrix::moveStatusDown(uint8_t distance)
{
	for (int i = 8; i > 0; i--)
	{
		if ((i - distance) < 0)
			status[i] = status[i - distance];
		else
			status[i] = 0;
	}
	writeStatus();
}

void mkl_Matrix::setChar(char letter)
{
	setStatus(ascii.patterns[(int)letter]);
	writeStatus();
}

void mkl_Matrix::createPanel(const char *text)
{
	panelBuffer = (char *)malloc(sizeof(char) * (strlen(text) + 1));
	strcpy(panelBuffer, text);
	setChar(panelBuffer[0]);
	setTransition(ascii.patterns[(int)panelBuffer[1]]);
	transitionPosition = 0;
}

void mkl_Matrix::nextPanelFrame()
{
	moveStatusLeft(1);
	transitionPosition--;
	if (transitionPosition > 7)
	{
		panelPosition++;
		transitionPosition = 8;
		if (panelPosition >= strlen(panelBuffer))
		{
			panelPosition = 0;
		}
		setTransition(ascii.patterns[(int)panelBuffer[panelPosition]]);
	}
	getColumn(transitionPosition, transition);
	setColumn(0, columnBuffer);
}

void mkl_Matrix::getColumn(uint8_t col, uint8_t pattern[8])
{
	columnBuffer = 0;
	for (int i = 0; i < 8; i++)
		columnBuffer |= (((pattern[i] >> col) & 1) << i);
}

void mkl_Matrix::setTransition(uint8_t pattern[8])
{
	for (int i = 0; i < 8; i++)
		transition[i] = pattern[i];
}