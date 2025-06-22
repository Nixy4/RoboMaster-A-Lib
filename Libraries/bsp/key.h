#pragma once



#ifdef USE_FREERTOS
#include "cmsis_os2.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#endif

#define KEY_ADC_VALUE_NONE_LOW    4095U
#define KEY_ADC_VALUE_NONE_HIGH   4095U
#define KEY_ADC_VALUE_UP_LOW      2450U
#define KEY_ADC_VALUE_UP_HIGH     2470U
#define KEY_ADC_VALUE_DOWN_LOW    3275U
#define KEY_ADC_VALUE_DOWN_HIGH   3295U
#define KEY_ADC_VALUE_LEFT_LOW    850U
#define KEY_ADC_VALUE_LEFT_HIGH   870U
#define KEY_ADC_VALUE_RIGHT_LOW   1730U
#define KEY_ADC_VALUE_RIGHT_HIGH  1750U
#define KEY_ADC_VALUE_CENTER_LOW  0U
#define KEY_ADC_VALUE_CENTER_HIGH 20U

#ifdef __cplusplus
extern "C" {
#endif

typedef enum key_state
{
  KEY_STATE_RELEASED = 0, // 松开
  KEY_STATE_PRESSED,      // 按下
} key_state;

typedef enum key_value
{
  KEY_VALUE_START = 0,
  KEY_VALUE_NONE = KEY_VALUE_START,
  KEY_VALUE_UP,
  KEY_VALUE_DOWN,
  KEY_VALUE_LEFT,
  KEY_VALUE_RIGHT,
  KEY_VALUE_CENTER,
  KEY_VALUE_INVALID, // 无效按键
  KEY_VALUE_MAX = KEY_VALUE_INVALID,
  KEY_VALUE_COUNT
} key_value;

typedef enum key_event
{
  KEY_EVENT_NONE = 0,
  KEY_EVENT_SHORT_PRESS ,  // 短按
  KEY_EVENT_LONG_PRESS  ,  // 长按
  KEY_EVENT_REPEAT      ,  // 重复
  KEY_EVENT_CLICK       ,  // 单击
  KEY_EVENT_DOUBLE_CLICK,  // 双击
} key_event;

typedef struct key_msg
{
  key_state state;       // 按键状态
  key_value value;       // 按键值
  key_event event;       // 按键事件
} key_msg;

void key_init(osMessageQueueId_t queue, int period_ms);
void key_adc_callback(uint32_t adc_value);

#ifdef __cplusplus
}
#endif