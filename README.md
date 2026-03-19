# About

This repo is contains two "forks" (not officially forked, I just copied the code) of ESP32 projects for the [WT32-SC01-PLUS](https://www.marutsu.co.jp/contents/shop/marutsu/datasheet/khe_WT32-SC01-PLUS.pdf).
I spent a good chunk of time trying to get this thing to work in the [esp-idf](https://docs.espressif.com/projects/esp-idf/en/stable/esp32/index.html) environment.

I've found that the platform-io code runs wayyyy smoother than the esp-idf code, I'm currently trying to figure out why.
The platformio code uses the arduino framework instead of the espidf framework, so I'd assume that it would be way slower since there is some overhead. 
You could also say that because Arduino is def (maybe it is, I didn't investigate yet) not running FreeRTOS that there is less overhead at runtime.

Long story short, no fucking clue whats going on here. But I'd like to find out :)

# Credits
- bsp-idf: [sukesh-ak/BSP-IDF5-ESP_LCD-LVGL9](https://github.com/sukesh-ak/BSP-IDF5-ESP_LCD-LVGL9)
- platformio: [SubCoderHUN/WT32-SC01-PLUS](https://github.com/SubCoderHUN/WT32-SC01-PLUS)
