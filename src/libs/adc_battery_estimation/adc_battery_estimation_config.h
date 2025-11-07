#ifndef _ADC_BATTERY_ESTIMATION_CONFIG_H
#define _ADC_BATTERY_ESTIMATION_CONFIG_H

#define CONFIG_OCV_SOC_MODEL_1  true
      
#define CONFIG_OCV_SOC_MODEL_2  false

#define CONFIG_ADC_FILTER_WINDOW_SIZE  10  // "ADC Filter Window size"
        //range 5 15

#define CONFIG_BATTERY_CAPACITY_LPF_COEFFICIENT  2  //  "Battery Capacity LPF Coefficient (/10)"
        //range 1 10

#define CONFIG_BATTERY_STATE_SOFTWARE_ESTIMATION  y  // "Battery State Software Estimation"
      
#define CONFIG_SOFTWARE_ESTIMATION_SAMPLE_COUNT 10 //"Software Estimation Sample Count"
        // range 10 15

#define CONFIG_SOFTWARE_ESTIMATION_SAMPLE_INTERVAL 20000 // "Software Estimation Sample Interval (ms)"
        // range 10000 100000

#endif
