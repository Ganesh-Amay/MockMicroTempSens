#pragma once

void LedController_init(void);
void LedController_setGreen(int on);
void LedController_setYellow(int on);
void LedController_setRed(int on);
void LedController_update(float temperatureC);