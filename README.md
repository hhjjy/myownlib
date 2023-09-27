# myownlib
常用的函數整理


## 触控屏幕按钮抽象化
### 使用说明
定义一个 Button 对象：
```
Button 结构体定义
```
typedef struct {
    uint16_t x;
    uint16_t y;
    uint16_t width;
    uint16_t height;
    char *text;
    ButtonState state ; // 预设状态是 IDLE
    uint8_t count_for_run_times ;
    uint32_t last_tick ;
    void (*on_press_callback)(int *, int) ;
    void (*on_longpress_contiune_callback)(int *, int) ; // 超过长按每 n 秒执行一次
    void (*on_longpress_callback)(int *, int) ;
} Button;
```

1. 初始化按钮参数：
```C
Button btn1;
button_init(Button* button,int x , int y , int width , int height , char* text);
```

2.设置短按、长按、连续长按时要执行的函数：
```
void button_set_on_press(Button* button, void (*callback)(int*, int));
void button_set_on_longpress(Button* button, void (*callback)(int*, int));
void button_set_on_conti_longpress(Button* button, void (*callback)(int*, int));
通过 button_update 函数更新按钮状态：
```
3. 透過Button_Update定期更新
```
void button_update(Button* button, int touch_x, int touch_y);
```
舉例 
```
while(1)
{
  if (HAL_GetTick() - last_tick >= 25)
  {
    TS_StateTypeDef TS_State;
    BSP_TS_GetState(&TS_State);
  
    // 判断是否有触摸
    if (TS_State.touchDetected)
    {
      button_update(&btn1,TS_State.touchX[0],TS_State.touchY[0]) ; 
      button_update(&btn2,TS_State.touchX[0],TS_State.touchY[0]) ; 
    }
    else 
    {
      button_update(&btn1,0 , 0) ; 
      button_update(&btn2,0 , 0) ; 
    }
    last_tick = HAL_GetTick();
  }
}

其中，ButtonState 是一个枚举类型，表示按钮的不同状态。

