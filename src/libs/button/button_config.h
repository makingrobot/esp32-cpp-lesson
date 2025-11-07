#ifndef _BUTTON_CONFIG_H
#define _BUTTON_CONFIG_H

#define BUTTON_VER_MAJOR 4
#define BUTTON_VER_MINOR 1
#define BUTTON_VER_PATCH 4

#define CONFIG_BUTTON_PERIOD_TIME_MS       5 //"Button scan interval"

#define CONFIG_BUTTON_DEBOUNCE_TICKS       2 // "One CONFIG_BUTTON_DEBOUNCE_TICKS equal to CONFIG_BUTTON_PERIOD_TIME_MS"

#define CONFIG_BUTTON_SHORT_PRESS_TIME_MS  180

#define CONFIG_BUTTON_LONG_PRESS_TIME_MS   1500

#define CONFIG_BUTTON_LONG_PRESS_HOLD_SERIAL_TIME_MS   20 //"Long press hold Serial trigger interval"

#define CONFIG_ADC_BUTTON_MAX_CHANNEL      3 //"Maximum number of channels for ADC buttons"

#define CONFIG_ADC_BUTTON_MAX_BUTTON_PER_CHANNEL       8 //"Maximum number of buttons per channel"

#define CONFIG_ADC_BUTTON_SAMPLE_TIMES     1  //"Number of samples per scan"

#endif //_BUTTON_CONFIG_H