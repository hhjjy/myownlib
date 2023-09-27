#ifndef BUTTON_H
#define BUTTON_H
#include "stm32746g_discovery_sdram.h"
#include "stm32746g_discovery_lcd.h"
#include "stm32746g_discovery_ts.h"

#include <stdint.h>

extern int now_time;
extern int screen_flash_index ; //申明待會會用到


#define GET_TICK HAL_GetTick

#define SCREEN_LONG_TIME_INC 100
#define SCREEN_LONG_TIME 1000
typedef enum {
    BUTTON_IDLE,
    BUTTON_PRESSED,
    BUTTON_LONG_PRESSED
} ButtonState;

typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    char *text;
    ButtonState state ;//預設狀態是IDLE
    uint8_t count_for_run_times ;
    uint32_t last_tick ;
    void (*on_press_callback)(int *, int) ;
    void (*on_longpress_contiune_callback)(int *, int) ;//超過長按每n秒執行一次
    void (*on_longpress_callback)(int *, int) ;
} Button;

void button_init(Button* button,int x , int y , int width , int height , char* text);//初始化設定
int button_touch_in_range(Button* button,int touch_x , int touch_y) ; 
void button_draw(Button* button);//畫圖
void button_update(Button* button, uint16_t touch_x, uint16_t touch_y);//更新button狀態需要一直執行
void button_set_on_press(Button* button, void (*func)(int *, int));//設定
void button_set_on_conti_longpress(Button* button, void (*func)(int *, int));//設定連續按的程序（超過n秒後每x秒會執行一次）
void button_set_on_longpress(Button* button, void (*func)(int *, int));//設定最後長按呼叫的程序

#endif
