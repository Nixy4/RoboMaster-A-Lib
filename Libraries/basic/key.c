#include "tim.h"
#include "adc.h"
#include "bsp_cfg.h"
#include "elog.h"
#include "key.h"

#define ELOG_TAG "key"

static osMessageQueueId_t _queue = NULL;

volatile key_value _last_value = KEY_VALUE_NONE;      // 上次按键值
volatile key_state _last_state = KEY_STATE_RELEASED;  // 上次按键状态
volatile uint32_t _last_tick   = 0;                   // 上次按键时间戳
volatile uint32_t  _tick_count = 0;                   // 按键计数
volatile uint32_t _click_count = 0;                   // 相同按键值计数
volatile key_event _last_event = KEY_EVENT_NONE;      // 上次按键事件

//获取
void _get(key_msg *msg, uint32_t adc_value)
{

}

void key_init(osMessageQueueId_t queue, int period_ms)
{
  //! Hardware
  if(period_ms < 100) {
    period_ms = 100; // 默认周期为100ms
  } 
  // uint32_t apb1clk = HAL_RCC_GetPCLK1Freq();               //84000000Hz
  // uint32_t psc     = __HAL_TIM_GET_CLOCKDIVISION(&htim3);  //8400-1
  // double   freq    = apb1clk / (psc + 1);                  //10000
  // uint32_t arr     = (freq * (period_ms / 1000)) - 1;      //计算自动重装载值 
  uint32_t arr = (uint32_t)(10000 * (period_ms / 1000.f) + 0.5f) - 1; // 计算自动重装载值
  //打印ARR
  elog_d(ELOG_TAG, "ARR: %d", arr);
  __HAL_TIM_SET_AUTORELOAD(&htim3, arr);  // 设置自动重装载值
  HAL_TIM_Base_Start(&htim3); // 启动定时器
  HAL_ADC_Start_IT(&hadc1); // 启动ADC转换
  //! OS
  _queue = queue; // 保存按键队列句柄
}

void key_adc_callback(uint32_t adc_value)
{

  key_value value = KEY_VALUE_INVALID;  // 初始化按键值为无效
  key_state state = KEY_STATE_RELEASED; // 初始化按键状态为松开
  key_event event = KEY_EVENT_CLICK;    // 初始化按键事件为无

  //读取硬件状态
  if(adc_value >= KEY_ADC_VALUE_NONE_LOW && adc_value <= KEY_ADC_VALUE_NONE_HIGH) {
    value = KEY_VALUE_NONE;      // 无按键
    state = KEY_STATE_RELEASED;  // 松开状态
    elog_v(ELOG_TAG, "No key pressed");
  } else if(adc_value >= KEY_ADC_VALUE_UP_LOW && adc_value <= KEY_ADC_VALUE_UP_HIGH) {
    value = KEY_VALUE_UP;       // 上键
    state = KEY_STATE_PRESSED;  // 按下状态
    elog_v(ELOG_TAG, "Up key pressed");
  } else if(adc_value >= KEY_ADC_VALUE_DOWN_LOW && adc_value <= KEY_ADC_VALUE_DOWN_HIGH) {
    value = KEY_VALUE_DOWN;     // 下键
    state = KEY_STATE_PRESSED;  // 按下状态
    elog_v(ELOG_TAG, "Down key pressed");
  } else if(adc_value >= KEY_ADC_VALUE_LEFT_LOW && adc_value <= KEY_ADC_VALUE_LEFT_HIGH) {
    value = KEY_VALUE_LEFT;     // 左键
    state = KEY_STATE_PRESSED;  // 按下状态
    elog_v(ELOG_TAG, "Left key pressed");
  } else if(adc_value >= KEY_ADC_VALUE_RIGHT_LOW && adc_value <= KEY_ADC_VALUE_RIGHT_HIGH) {
    value = KEY_VALUE_RIGHT;    // 右键
    state = KEY_STATE_PRESSED;  // 按下状态
    elog_v(ELOG_TAG, "Right key pressed");
  } else if(adc_value <= KEY_ADC_VALUE_CENTER_HIGH) {
    value = KEY_VALUE_CENTER;   // 中心键
    state = KEY_STATE_PRESSED;  // 按下状态
    elog_v(ELOG_TAG, "Center key pressed");
  } else {
    value = KEY_VALUE_INVALID;   // 无效按键
    state = KEY_STATE_RELEASED;  // 松开状态
    elog_v(ELOG_TAG, "Invalid key pressed");
  }

  if(event != KEY_EVENT_NONE && _queue != NULL) { // 如果有按键事件
    key_msg msg = {.state = state, .value = value, .event = event}; // 创建按键消息
    osStatus_t ret = osMessageQueuePut(_queue, &msg, 0, 0); // 将消息放入队列
    // if(ret != osOK) {
    //   //查询当前队列可用容量
    //   size_t queue_size = osMessageQueueGetCapacity(_queue); // 获取队列容量
    //   size_t queue_count = osMessageQueueGetCount(_queue); // 获取队列当前消息数量
    //   elog_v(ELOG_TAG, "Failed to put key message to queue: %d, queue size: %u, queue count: %u", ret, queue_size, queue_count);
    //   // 如果队列已满，可以选择丢弃旧消息或处理错误
    // } else {
    //   elog_v(ELOG_TAG, "Key message put to queue: state=%d, value=%d, event=%d", state, value, event); // 打印成功日志
    // }
  }
}