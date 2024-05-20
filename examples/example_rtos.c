#include "stdio.h"
#include "stdint.h"

#include "freertos/FreeRTOS.h"
#include "freertos/task.h"

#include "multi_button.h"

int main(int argc, char const *argv[])
{
    xTaskCreate(btn_task_handler, "btn_task", 1024 * 3, NULL, 6, NULL);
    return 0;
}

typedef enum {
    BTN_1_ID=0,
    BTN_2_ID,
} btn_id_t;

uint8_t btn_input_level(uint8_t id)
{
    uint8_t level = 0;
    if(id == BTN_1_ID)
    {
        level = get_level(BTN_1_ID);
    }
    else if(id == BTN_2_ID) 
    {
        level = get_level(BTN_2_ID);
    }
    return level;
}

void btn_double_press_handle(void* hdl)
{
    struct Button* btn = (struct Button*)hdl;
    
    if(btn->button_id == BTN_1_ID)
    {

    }
    else if(btn->button_id == BTN_2_ID) 
    {

    }
}

void btn_long_press_handle(void* hdl)
{
    struct Button* btn = (struct Button*)hdl;
    
    if(btn->button_id == BTN_1_ID)
    {

    }
    else if(btn->button_id == BTN_2_ID) 
    {

    }
}

/**
 * @brief 处理任务
 * 
 * @param arg 
 * 
 * @note
 *  SHORT_TICKS: 按键单击、双击、多击时的超时处理时间
 *  LONG_TICKS: 长按的超时处理时间
 */
void btn_task_handler(void* arg)
{
    struct Button btn1;
    button_init(&btn1, btn_input_level, 0, BTN_1_ID, (1000 /TICKS_INTERVAL), (3000 /TICKS_INTERVAL));
    button_attach(&btn1, DOUBLE_CLICK, btn_double_press_handle); // 1秒内双击
    button_attach(&btn1, LONG_PRESS_START, btn_long_press_handle); // 长按3秒
    button_start(&btn1);

    struct Button btn2;
    button_init(&btn2, btn_input_level, 0, BTN_2_ID, SHORT_TICKS, (5000 /TICKS_INTERVAL));
    button_attach(&btn2, LONG_PRESS_START, btn_long_press_handle); // 长按5秒
    button_start(&btn2);

    while (1)
    {
        button_ticks();
        vTaskDelay(pdMS_TO_TICKS(5));
    }
    vTaskDelete(NULL);
}