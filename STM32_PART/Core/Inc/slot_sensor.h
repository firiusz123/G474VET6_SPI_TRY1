#ifndef SLOT_SENSOR_H
#define SLOT_SENSOR_H

#include "main.h"

extern  int8_t counter; // Counter for slot sensor

void SlotSensor_Init(int8_t side);
int SlotSensor_Update(int8_t side);

#endif // SLOT_SENSOR_H
