/**
 * @file example_i2c_tk.c
 * 
 * @brief 基于i2c的触摸按键处理
 * 
 */

#include "multi_button.h"
#include "touchkey.h"

int main(int argc, char const *argv[])
{
    /*! 任务优先级尽可能高, 确保任务能正常调度, 从而保证按键任务的正常扫描 */
    xTaskCreate(btn_task_handler, "btn_task", 1024 * 3, NULL, 6, NULL);
    return 0;
}

uint32_t g_tk_value;

typedef enum {
    TK_BTN_MASK_0 = 0,
    TK_BTN_MASK_1,
    TK_BTN_MASK_2,
    TK_BTN_MASK_3,
    TK_BTN_MASK_4,
} tk_btn_mask_t;

void touchkey_scan(void)
{
    uint32_t key = 0;
    key = touchkey_read();
    if(key == 0) {
        g_tk_value |= (1 << TK_BTN_MASK_0);
    }
    else if(key == 1) {
        g_tk_value |= (1 << TK_BTN_MASK_1);
    }
    ......
}

uint8_t btn_input_level(uint8_t id)
{
    uint8_t level = 0;
    tk_btn_mask_t tk_mask = id;

    if(g_tk_value & (1 << tk_mask)) {
        level = 1;
    }
    return level;
}

void btn_double_press_handle(void* hdl)
{
    struct Button* btn = (struct Button*)hdl;
    tk_btn_mask_t tk_mask = btn->button_id;
    
    if(btn->button_id == TK_BTN_MASK_0)
    {

    }
    else if(btn->button_id == TK_BTN_MASK_1) 
    {

    }
}

void btn_long_press_handle(void* hdl)
{
    struct Button* btn = (struct Button*)hdl;
    tk_btn_mask_t tk_mask = btn->button_id;
    
    if(btn->button_id == TK_BTN_MASK_0)
    {

    }
    else if(btn->button_id == TK_BTN_MASK_1) 
    {

    }
}

void btn_task_handler(void* arg)
{
    struct Button tk_btn[2];
    
    for(int i=0; i<2; i++)
    {
        button_init(&tk_btn[i], btn_input_level, 0, i, (1000 /TICKS_INTERVAL), (5000 /TICKS_INTERVAL));
        button_attach(&tk_btn[i], DOUBLE_CLICK, btn_double_press_handle); // 1秒内双击
    }
    
    button_attach(&tk_btn[1], LONG_PRESS_START, btn_long_press_handle); // 长按5秒
    
    for(int i=0; i<2; i++)
    {
        button_start(&tk_btn[i]);
    }
    while (1)
    {
        touchkey_scan(); // I2C 触摸按键键值读取; 1ms
        button_ticks(); // 按键处理
        vTaskDelay(pdMS_TO_TICKS(4)); // 整体的处理间隔为: 5ms
    }
    vTaskDelete(NULL);
}

