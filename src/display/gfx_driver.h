#include "config.h"
#if CONFIG_USE_GFX_LIBRARY == 1

#ifndef _GFX_DRIVER_H
#define _GFX_DRIVER_H

#include "disp_driver.h"
#include <Arduino.h>
#include <Arduino_GFX_Library.h>
#include <lvgl.h>

class GfxDriver : public DispDriver {
public:
    GfxDriver(Arduino_GFX* gfx, int width, int height)
        : DispDriver(width, height), gfx_(gfx) { }

    virtual ~GfxDriver() { 
        if (display_ != nullptr) {
            lv_display_delete(display_);
        }
    }

    void Init() override;
    
private:
    void FlushCallback(lv_display_t *disp, const lv_area_t *area, uint8_t *px_map);

    Arduino_GFX* gfx_;

    lv_display_t *display_ = nullptr;
    lv_color_t *disp_buf_ = nullptr;

};

#endif //_GFX_DRIVER_H

#endif //CONFIG_USE_GFX_LIBRARY