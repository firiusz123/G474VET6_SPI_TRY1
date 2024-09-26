#ifndef SLOT_SENSOR_H
#define SLOT_SENSOR_H

#include "main.h"

extern  int8_t counter; // Counter for slot sensor

void SlotSensor_Init(void);
int SlotSensor_Update(void);

#endif // SLOT_SENSOR_H
