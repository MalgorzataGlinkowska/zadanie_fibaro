#ifndef INC_UART_H_
#define INC_UART_H_

#include "stm32l1xx_hal.h"


#define FRAME_START 0xAC	///< Znak startu ramki
#define FRAME_END	0xDC	///< Znak końca ramki
#define FRAME_SIZE	33		///< Maksymalny rozmiar ramki
#define FRAME_CLICK	30		///< Maksymalna liczba kliknięć

#define UDelay	100			///< Przerwa między zmianami stanu diody

struct uartStruct{
	uint8_t frameLength;	///< Długość przygotowywanej ramki
	uint8_t frameToSend[FRAME_SIZE];	///< Tablica przygotowanej ramki
	uint8_t *ptrArray;			///< Wskaźnik na tablicę
	uint8_t blinkCounter;		///< Liczba mrugnięć diodą
	uint8_t blinkDelay;			///< Pzzerwa między mrugnięciami

	uint8_t fNewByte	:1;		///< Flaga nowego odebranego bajtu
	uint8_t newByte;			///< Odebrany bajt
	uint8_t recFrameLength;		///< Długość odebranej ramki
	uint8_t recFrame[FRAME_SIZE]; ///< Odebrana ramka
	uint8_t recbytes;			///< Liczba odebranych bajtów
	uint8_t *ptrRecArray;		///< Wskaźnik na tablicę odbiorczą
}UART;

typedef enum
{
	nm_none,
	nm_newMessage,
	nm_frameError,
}new_message_type;

/**
 * @brief Funkcja przygotowująca ramkę komunikacyjną do wysłania
 *
 * @param dataLength Długość pola danych
 * @retval 1 - Poprawnie utworzona ramka
 */
uint8_t uFramePrepare(uint8_t dataLength);

/**
 * @brief Funkcja wysyłająca ramkę danych prez wskazany uart
 *
 * @param dataLength Długość pola danych
 * @param huart Uchwyt do struktury UART
 */
void uFrameSend(uint8_t dataLength, UART_HandleTypeDef *huart);

/**
 * @brief Funkcja obsługująca odebrane bajty
 */
new_message_type receiveFrame();
#endif /* INC_UART_H_ */
