#include "uart.h"

uint8_t uFramePrepare(uint8_t dataLength)
{
	UART.ptrArray = &UART.frameToSend[0];	// Zapisz wskaźnik na początek tablicy
	UART.frameLength = dataLength + 3;	// Dodane start, koniec, długość
	UART.frameToSend[0] = FRAME_START;	// Początek ramki
	*(++UART.ptrArray) = dataLength;
	for(uint8_t i = 0; i < dataLength; i++)
	{
		*(++UART.ptrArray) = i + 1;	// Dodaj kolejne doane do ramki
	}
	if(*UART.ptrArray == UART.frameToSend[UART.frameLength - 2])	// Jeśli ostatni bajt danych pokrywa się z wartością wskaźnika, to ramka powinna być ok
	{
		*(++UART.ptrArray) = FRAME_END;	// Dodany koniec ramki
		UART.blinkCounter = 2 * dataLength;	// Liczba mrugnięć diodą; x2, żeby zrobić pełne cykle zapaleń
		UART.blinkDelay = UDelay;	//	 Ustaw czas zmiany mrugnięć
		return 1;
	}
	return 34;	// Coś poszło nie tak. Ramka przygotowana nieprawidłowo
}


void uFrameSend(uint8_t dataLength, UART_HandleTypeDef *huart)
{
	uFramePrepare(dataLength);
	HAL_UART_Transmit_IT(huart, UART.frameToSend, UART.frameLength);
}

