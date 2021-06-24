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
	HAL_UART_Transmit(huart, &UART.frameToSend[0], UART.frameLength, HAL_MAX_DELAY);

}

new_message_type receiveFrame(UART_HandleTypeDef *huart)
{
	new_message_type result;
	if(UART.fNewByte)
	{
		UART.fNewByte = 0;	// wyzeruj flagę nowego bajtu
		if(UART.newByte == FRAME_START)
		{
			UART.ptrRecArray = &UART.recFrame[0];
			UART.recbytes = 1;

		}
		else if(UART.recbytes == 1)
		{
			UART.recFrameLength = UART.newByte + 3;	// Zapisz długość odbieranej ramki
			UART.recbytes++;
		}
		else if((UART.recbytes > 1) && (UART.recbytes < UART.recFrameLength - 1))	// - bajt końca ramki
		{
			*(UART.ptrRecArray++) = UART.newByte;	// Zapisz w tablicy nowy bajt
			UART.recbytes++;
		}
		else if(UART.recbytes == UART.recFrameLength - 1)	// Jeśli odebrano odpowiednią liczbę bajtów
		{
			if(UART.newByte== FRAME_END)	// Jeśli ostatni bajt jest jak końcowy bajt
			{
				UART.blinkCounter = 2 * (UART.recFrameLength - 3);	// Zamrugaj odpowiednią liczbę bajtów
				UART.blinkDelay = UDelay;	// zacznij mrugać
				sendACK(huart);	// Wyślij potwierdzenie odbioru
				result = nm_newMessage;
			}
			else
			{
				sendNAK(huart);	// Wyślij błąd ramki
				result = nm_frameError;	// jeśli nie to zgłoś błąd
			}
			UART.recbytes = 0;
		}
		else
		{
			result = nm_none;
		}

	}
	else
	{
		result = nm_none;
	}
	return result;
}

void sendACK(UART_HandleTypeDef *huart)
{
	UART.frameToSend[0] = FRAME_START;
	UART.frameToSend[1] = 1;
	UART.frameToSend[2] = FRAME_ACK;
	UART.frameToSend[3] = FRAME_END;

	HAL_UART_Transmit(huart, UART.frameToSend, 4, HAL_MAX_DELAY);

//	UART.blinkCounter = 2;	// Zamrugaj raz
//	UART.blinkDelay = UDelay;	// zacznij mrugać
}

void sendNAK(UART_HandleTypeDef *huart)
{
	UART.frameToSend[0] = FRAME_START;
	UART.frameToSend[1] = 1;
	UART.frameToSend[2] = FRAME_NAK;
	UART.frameToSend[3] = FRAME_END;

	HAL_UART_Transmit(huart, UART.frameToSend, 4, HAL_MAX_DELAY);

//	UART.blinkCounter = 2;	// Zamrugaj raz
//	UART.blinkDelay = UDelay;	// zacznij mrugać
}
















