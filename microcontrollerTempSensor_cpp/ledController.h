#pragma once

class LedController {
public:
  LedController() = default;
  ~LedController() = default;

  void init();
  void setGreen(bool state);
  void setYellow(bool state);
  void setRed(bool state);

  // For convenience, one function to update all at once
  void update(float temperatureC);
};
