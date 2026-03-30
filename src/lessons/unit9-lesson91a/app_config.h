#if APP_LESSON91_A==1

#ifndef _APP_CONFIG_H
#define _APP_CONFIG_H

/*****
 * 本文件主要用于启用某项特性，或使用某个硬件。
 * 对开发框架源码裁剪的配置项均在本文件中，不使用的硬件和特性请不要启用，以得到最小可用的代码。
 * 注意：任一选项的更改都可能会导致项目源文件的整体编译！
 */

// 定时器
#define CONFIG_USE_SW_TIMER                1
#define CONFIG_USE_HW_TIMER                0

// 启用文件系统
#define CONFIG_USE_FS                       1

// LED驱动
#define CONFIG_USE_LED_GPIO                 1
#define CONFIG_USE_LED_WS2812               0

// 使用ESP_LOG
#define CONFIG_USE_ESP_LOG                  0


#endif //_APP_CONFIG_H

#endif