#ifndef INC_FIB_LIB_H_
#define INC_FIB_LIB_H_

#include "stm32l1xx_hal.h"

#define BTN_DEBOUNCE	100	///< Czas stabilizacji przycisków

#define BTN1			HAL_GPIO_ReadPin(B1_GPIO_Port, B1_Pin)	///< Stan przycisku 1
#define BTN1_PUSHED()	BTN1 == 0	///< Przycisk 1 wciśnięty

#define LED_ON()		do{HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 1);}while(0)	///< Załączenie diody
#define LED_OFF()		do{HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, 0);}while(0)	///< Wyłączenie diody

struct flagi{
	uint8_t button_pushed	:1;	///< Flaga wciśnięcia przycisku
}FLAG;

struct czasy{
	uint8_t button_debounce;	///< Czas stabilizacji przycisku
}TIME;

#endif /* INC_FIB_LIB_H_ */
