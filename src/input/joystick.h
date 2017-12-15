#pragma once
#include <string.h>
#include "input.h"

namespace GameLib {

/**
*@brief The JoystickButtons enum
*/
enum JoystickButtons {
  BUTTON_1 = 0,
  BUTTON_2,
  BUTTON_3,
  BUTTON_4,
  L1,
  L2,
  R1,
  R2,
  LTRIGGER,
  RTRIGGER,
  LCKICL,
  RCLICK,
  START,
  BACK,
  SELECT,
  SPECIAL,
  DPAD_UP,
  DPAD_DOWN,
  DPAD_LEFT,
  DPAD_RIGHT,
  LANALOG,
  RANALOG,
  MAX_BUTTONS
};

/**
 * @brief The JoystickAnalogs enum
 */
enum JoystickAnalogs {
  X_AXIS_VALUE = 0,
  Y_AXIS_VALUE,
  LTRIGGER_VALUE,
  RTRIGGER_VALUE,
  MAX_ANALOGS
};

/**
 * @brief The JoyData struct
 */
struct JoyData {
  JoyData() {
    memset(buttons, 0, sizeof(buttons));
    memset(buttons, 0, sizeof(analogs));
  }
  bool buttons[MAX_BUTTONS];
  int analogs[MAX_ANALOGS];
};

class Joystick : public Input {
public:
};

} // namespace GameLib
