
#ifndef AT45DB161_H_
#define AT45DB161_H_



#define EEPROM_SCK_H 		HAL_GPIO_WritePin(EEPROM_SCK_GPIO_Port, EEPROM_SCK_Pin, GPIO_PIN_SET)
#define EEPROM_SCK_L 		HAL_GPIO_WritePin(EEPROM_SCK_GPIO_Port, EEPROM_SCK_Pin, GPIO_PIN_RESET)
#define EEPROM_MOSI_H 	HAL_GPIO_WritePin(EEPROM_MOSI_GPIO_Port, EEPROM_MOSI_Pin, GPIO_PIN_SET)
#define EEPROM_MOSI_L 	HAL_GPIO_WritePin(EEPROM_MOSI_GPIO_Port, EEPROM_MOSI_Pin, GPIO_PIN_RESET)
#define EEPROM_CS_H			HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_SET)
#define EEPROM_CS_L			HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_RESET)
#define EEPROM_MISO			HAL_GPIO_ReadPin(EEPROM_MISO_GPIO_Port, EEPROM_MISO_Pin)

#define MOSI_H         		HAL_GPIO_WritePin(EEPROM_MOSI_GPIO_Port, EEPROM_MOSI_Pin, GPIO_PIN_SET)
#define MOSI_L         		HAL_GPIO_WritePin(EEPROM_MOSI_GPIO_Port, EEPROM_MOSI_Pin, GPIO_PIN_RESET)
#define SCK_H         		HAL_GPIO_WritePin(EEPROM_SCK_GPIO_Port, EEPROM_SCK_Pin, GPIO_PIN_SET)
#define SCK_L         		HAL_GPIO_WritePin(EEPROM_SCK_GPIO_Port, EEPROM_SCK_Pin, GPIO_PIN_RESET)
#define CS_H         			HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_SET)
#define CS_L         			HAL_GPIO_WritePin(EEPROM_CS_GPIO_Port, EEPROM_CS_Pin, GPIO_PIN_RESET)
#define RES_H         		HAL_GPIO_WritePin(EEPROM_RES_GPIO_Port, EEPROM_RES_Pin, GPIO_PIN_SET)
#define RES_L         		HAL_GPIO_WritePin(EEPROM_RES_GPIO_Port, EEPROM_RES_Pin, GPIO_PIN_RESET)
#define MISO       				HAL_GPIO_ReadPin(EEPROM_MISO_GPIO_Port, EEPROM_MISO_Pin)

extern void AT45_WriteByte(uint8_t nbuf,uint16_t PageAddr,uint16_t BaseAddr,int16_t len, uint8_t *Writebuf);
extern void AT45_ReadByte(uint16_t pageaddr1, uint16_t baseaddr1,int16_t len2, uint8_t *readbuf);

extern uint8_t AT45_EEPROM_Check(void);

#endif /* AT45DB161_H_ */
