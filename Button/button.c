#include "button.h"

//function:範圍是否在按壓內
//return : 0 (不在範圍)
//         1 (在範圍)
int button_touch_in_range(Button* button,int touch_x , int touch_y) 
{
    if(button->x <= touch_x && touch_x <= button->x + button->width &&
       button->y <= touch_y && touch_y <= button->y + button->height)
    {
        return 1 ; 
    }
    return 0 ; 
}
//畫圖
void button_draw(Button* button)
{
  BSP_LCD_DrawRect(button->x, button->y, button->width, button->height);
  BSP_LCD_DisplayStringAt(button->x + 5, button->y + 5, (uint8_t *)button->text, LEFT_MODE);
}

void button_init(Button* button,int x , int y , int width , int height , char* text)
{
    button->x = x; 
    button->y = y; 
    button->width = width; 
    button->height = height ; 
    button->text = text ; 
    button->state = BUTTON_IDLE;
    button->count_for_run_times = SCREEN_LONG_TIME/SCREEN_LONG_TIME_INC ; 
    button->last_tick = GET_TICK() ; 
    //順便畫圖
    button_draw(button);

}
//這個function不需要一直呼叫 
void button_update(Button* button, uint16_t touch_x, uint16_t touch_y)
{
    // static ButtonState state = BUTTON_IDLE;
    // static uint32_t last_tick = 0;
    // static uint8_t count_for_run_times = 0;

    if (button_touch_in_range(button, touch_x, touch_y)) {//按了
        if (button->state == BUTTON_IDLE) {
            button->state = BUTTON_PRESSED;
            button->last_tick = GET_TICK();
        } else if (GET_TICK() - button->last_tick > SCREEN_LONG_TIME) {
            button->state = BUTTON_LONG_PRESSED;
            if ((GET_TICK() - button->last_tick) / SCREEN_LONG_TIME_INC > button->count_for_run_times) {
                button->count_for_run_times++;
                // call function
                if (button->on_longpress_contiune_callback) {
                    button->on_longpress_contiune_callback(&now_time,screen_flash_index);
                }
            }
        }
    } else {//沒按
        if (button->state == BUTTON_PRESSED) {//短按
            button->state = BUTTON_IDLE;
            // call function 
            if (button->on_press_callback) {
                button->on_press_callback(&now_time,screen_flash_index);
            }
        } else if (button->state == BUTTON_LONG_PRESSED) {
            button->state = BUTTON_IDLE;
            // call fucntion 
            if (button->on_longpress_callback) {
                button->on_longpress_callback(&now_time,screen_flash_index);
            }
        }
        button->count_for_run_times = 0;
    }
}

void button_set_on_press(Button* button, void (*func)(int *, int))//設定
{
    button->on_press_callback = func;
}
void button_set_on_conti_longpress(Button* button, void (*func)(int *, int))//設定連續按的程序（超過n秒後每x秒會執行一次）
{
    button->on_longpress_contiune_callback = func;
}
void button_set_on_longpress(Button* button, void (*func)(int *, int))//設定最後長按呼叫的程序
{
    button->on_longpress_callback = func;
}
