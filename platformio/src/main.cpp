// lvgl8 en snel

#include "display_config.hpp"


#include <Wire.h>
#define LGFX_USE_V1
#include <LovyanGFX.hpp>
#include <lvgl.h>
#include "ui_demo_widgets.h"

int screen_brightness = 255;

static LGFX lcd;

/*Change to your screen resolution*/
static const uint32_t screenWidth = 480;
static const uint32_t screenHeight = 320;
static lv_disp_draw_buf_t draw_buf;
static lv_color_t buf[screenWidth * 100];

/* Display flushing */
void my_disp_flush(lv_disp_drv_t *disp, const lv_area_t *area, lv_color_t *color_p)
{
  uint32_t w = (area->x2 - area->x1 + 1);
  uint32_t h = (area->y2 - area->y1 + 1);

  lcd.startWrite();
  lcd.setAddrWindow(area->x1, area->y1, w, h);
  lcd.writePixels((lgfx::rgb565_t *)&color_p->full, w * h);
  lcd.endWrite();

  lv_disp_flush_ready(disp);
}

/*Read the touchpad*/
void my_touchpad_read(lv_indev_drv_t *indev_driver, lv_indev_data_t *data)
{

  uint16_t x, y;
  if (lcd.getTouch(&x, &y))
  {
    data->state = LV_INDEV_STATE_PR;
    data->point.x = x;
    data->point.y = y;
  }
  else
  {
    data->state = LV_INDEV_STATE_REL;
  }
}

void initDisplay()
{
  lcd.begin();
  lcd.setRotation(3);
  lcd.setBrightness(screen_brightness);
  lcd.fillScreen(TFT_BLACK);

}


void setup()
{
  Serial.begin(115200);
  initDisplay();
  lv_init();
  // @param size_in_px_cnt size of the `buf1` and `buf2` in pixel count.
  lv_disp_draw_buf_init(&draw_buf, buf, NULL, screenWidth * 100);

  /*Initialize the display*/
  static lv_disp_drv_t disp_drv;
  lv_disp_drv_init(&disp_drv);
  /*Change the following line to your display resolution*/
  disp_drv.hor_res = screenWidth;
  disp_drv.ver_res = screenHeight;
  disp_drv.flush_cb = my_disp_flush;
  disp_drv.draw_buf = &draw_buf;
  lv_disp_drv_register(&disp_drv);

  /*Initialize the (dummy) input device driver*/
  static lv_indev_drv_t indev_drv;
  lv_indev_drv_init(&indev_drv);
  indev_drv.type = LV_INDEV_TYPE_POINTER;
  indev_drv.read_cb = my_touchpad_read;
  lv_indev_drv_register(&indev_drv);

  lcd.setBrightness(255);

  lv_demo_widgets();
}

void loop()
{
  lv_timer_handler();
  delay(1);
}
