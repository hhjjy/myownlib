# myownlib
常用的函數整理


## 觸控螢幕按鈕抽象化
### 使用說明
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
1. 先定義一個Button btn1 ; 物件
2. 初始化button參數void button_init(Button* button,int x , int y , int width , int height , char* text);//初始化設定
3. 設定短按 長按 連續長按時 要執行的funciton
4. 透過button_update更新按鈕狀態...
   if (HAL_GetTick() - last_tick >= 25)
    {
      TS_StateTypeDef TS_State;
      BSP_TS_GetState(&TS_State);

      // 1. �p�G���U
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

