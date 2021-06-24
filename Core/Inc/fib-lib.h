#ifndef INC_FIB_LIB_H_
#define INC_FIB_LIB_H_

#include "stm32l1xx_hal.h"

#define BTN_DEBOUNCE	50	///< Czas stabilizacji przycisków
#define MOD_100ms		100	///< Timer zliczający 100ms
#define BUTT_TIME		10	///< Timeout zliczania kliknięć przycisku

#define BTN1			HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)	///< Stan przycisku 1
#define BTN1_PUSHED()	BTN1 == 0	///< Przycisk 1 wciśnięty

#define LED_ON()		do{HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);}while(0)	///< Załączenie diody
#define LED_OFF()		do{HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);}while(0)	///< Wyłączenie diody
#define LED_TOGGLE()	do{HAL_GPIO_TogglePin(LD2_GPIO_Port, LD2_Pin);}while(0);	///< Zmiana stanu diody

struct flagi{
	uint8_t button_pushed	:1;	///< Flaga wciśnięcia przycisku
	uint8_t butTimeout		:1;	///< Flaga zakońćzenia odliczania kliknięć
}FLAG;

struct czasy{
	uint8_t button_debounce;	///< Czas stabilizacji przycisku

	uint8_t mod_100ms;			///< Zliczanie 100ms
	uint8_t buttTimeout;		///< Czas oczekiwania na kilejne kilknięcie
}TIME;

#endif /* INC_FIB_LIB_H_ */
