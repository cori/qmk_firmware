/*
  Set any config.h overrides for your specific keymap here.
  See config.h options at https://docs.qmk.fm/#/config_options?id=the-configh-file
*/
// #define ORYX_CONFIGURATOR
#undef TAPPING_TERM
#define TAPPING_TERM 225

#define RETRO_TAPPING

#define USB_SUSPEND_WAKEUP_DELAY 0
// #define FIRMWARE_VERSION u8"z9xWM/j7VYx"
#define RGB_MATRIX_STARTUP_SPD 60

#define RGB_MATRIX_FRAMEBUFFER_EFFECTS
#define RGB_MATRIX_KEYPRESSES  // reacts to keypresses
#define ENABLE_RGB_MATRIX_SOLID_REACTIVE_SIMPLE
#define RGB_MATRIX_STARTUP_MODE RGB_MATRIX_SOLID_REACTIVE_SIMPLE  //  RGB_MATRIX_SOLID_REACTIVE_NEXUS  // Sets the default mode, if none has been set
#define RGBLIGHT_ANIMATIONS             // Run RGB animations
