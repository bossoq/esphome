#pragma once

#include "esphome/components/climate_ir/climate_ir.h"

namespace esphome {
namespace daikin {

// Values for Daikin ARC43XXX IR Controllers
// Temperature
const uint8_t DAIKIN_TEMP_MIN = 16;  // Celsius
const uint8_t DAIKIN_TEMP_MAX = 32;  // Celsius

// Modes
const uint8_t DAIKIN_MODE_AUTO = 0x00;
const uint8_t DAIKIN_MODE_COOL = 0x30;
const uint8_t DAIKIN_MODE_HEAT = 0x40;
const uint8_t DAIKIN_MODE_DRY = 0x20;
const uint8_t DAIKIN_MODE_FAN = 0x60;
const uint8_t DAIKIN_MODE_OFF = 0x00;
const uint8_t DAIKIN_MODE_ON = 0x01;

// Fan Speed
const uint8_t DAIKIN_FAN_AUTO = 0xA0;
const uint8_t DAIKIN_FAN_SILENT = 0xB0;
const uint8_t DAIKIN_FAN_1 = 0x30;
const uint8_t DAIKIN_FAN_2 = 0x40;
const uint8_t DAIKIN_FAN_3 = 0x50;
const uint8_t DAIKIN_FAN_4 = 0x60;
const uint8_t DAIKIN_FAN_5 = 0x70;

const uint8_t DAIKIN_PRESET_OFF = 0x00;
// Powerful/Quiet Presets
const uint8_t DAIKIN_PRESET_POWERFUL_ON = 0x01;
const uint8_t DAIKIN_PRESET_QUIET_ON = 0x20;
// Comfort/Econo/Sensor Presets
const uint8_t DAIKIN_PRESET_COMFORT_ON = 0x02;
const uint8_t DAIKIN_PRESET_ECONO_ON = 0x04;
const uint8_t DAIKIN_PRESET_SENSOR_ON = 0x08;

// IR Transmission
const uint32_t DAIKIN_IR_FREQUENCY = 36000;
const uint32_t DAIKIN_HEADER_MARK = 3360;
const uint32_t DAIKIN_HEADER_SPACE = 1760;
const uint32_t DAIKIN_BIT_MARK = 520;
const uint32_t DAIKIN_ONE_SPACE = 1370;
const uint32_t DAIKIN_ZERO_SPACE = 360;
const uint32_t DAIKIN_MESSAGE_SPACE = 32300;

// State Frame size
const uint8_t DAIKIN_STATE_FRAME_SIZE = 19;

class DaikinClimate : public climate_ir::ClimateIR {
 public:
  DaikinClimate()
      : climate_ir::ClimateIR(
            DAIKIN_TEMP_MIN, DAIKIN_TEMP_MAX, 0.5f, true, true,
            {climate::CLIMATE_FAN_AUTO, climate::CLIMATE_FAN_LOW, climate::CLIMATE_FAN_MEDIUM,
             climate::CLIMATE_FAN_HIGH},
            {climate::CLIMATE_SWING_OFF, climate::CLIMATE_SWING_VERTICAL, climate::CLIMATE_SWING_HORIZONTAL,
             climate::CLIMATE_SWING_BOTH},
            {climate::CLIMATE_PRESET_ECO, climate::CLIMATE_PRESET_BOOST, climate::CLIMATE_PRESET_COMFORT,
             climate::CLIMATE_PRESET_SLEEP, climate::CLIMATE_PRESET_ACTIVITY, climate::CLIMATE_PRESET_NONE}) {}

 protected:
  // Transmit via IR the state of this climate controller.
  void transmit_state() override;
  uint8_t operation_mode_();
  uint16_t fan_speed_();
  uint8_t temperature_();
  uint8_t powerful_quiet_preset_();
  uint8_t eco_preset_();
  // Handle received IR Buffer
  bool on_receive(remote_base::RemoteReceiveData data) override;
  bool parse_state_frame_(const uint8_t frame[]);
};

}  // namespace daikin
}  // namespace esphome