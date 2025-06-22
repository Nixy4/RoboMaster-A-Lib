#include "pwm.h"
#include "elog.h"
#include "tim.h"

#define TAG "PWM"

static TIM_HandleTypeDef* get_bank_hal_handle(pwm_bank bank)
{
  switch(bank) {
    case PWM_BANK_ABCD: return &htim5;
    case PWM_BANK_EFGH: return &htim4;
    case PWM_BANK_STUV: return &htim2;
    case PWM_BANK_WXYZ: return &htim8;
    default: return NULL;
  }
}

static TIM_HandleTypeDef* get_channel_hal_handle(pwm_channel channel)
{
  switch(channel) {
    case PWM_CHANNEL_A:
    case PWM_CHANNEL_B:
    case PWM_CHANNEL_C:
    case PWM_CHANNEL_D:
      return &htim5;
    case PWM_CHANNEL_E:
    case PWM_CHANNEL_F:
    case PWM_CHANNEL_G:
    case PWM_CHANNEL_H:
      return &htim4;
    case PWM_CHANNEL_S:
    case PWM_CHANNEL_T:
    case PWM_CHANNEL_U:
    case PWM_CHANNEL_V:
      return &htim2;
    case PWM_CHANNEL_W:
    case PWM_CHANNEL_X:
    case PWM_CHANNEL_Y:
    case PWM_CHANNEL_Z:
      return &htim8;
    default : 
      return NULL;
  }
}

static uint32_t get_channel_hal_channel(pwm_channel channel)
{
  switch(channel) 
  {
    case PWM_CHANNEL_D:
    case PWM_CHANNEL_H:
    case PWM_CHANNEL_S:
    case PWM_CHANNEL_W: 
      return TIM_CHANNEL_1;
    case PWM_CHANNEL_C:
    case PWM_CHANNEL_G:
    case PWM_CHANNEL_T:
    case PWM_CHANNEL_X: 
      return TIM_CHANNEL_2;
    case PWM_CHANNEL_B:
    case PWM_CHANNEL_F:
    case PWM_CHANNEL_U:
    case PWM_CHANNEL_Y:
      return TIM_CHANNEL_3;
    case PWM_CHANNEL_A:
    case PWM_CHANNEL_E:
    case PWM_CHANNEL_V:
    case PWM_CHANNEL_Z: 
      return TIM_CHANNEL_4;
    default:
      return TIM_CHANNEL_ALL;
  }
}

void pwm_bank_set_psc(pwm_bank bank, uint32_t psc)
{
  __HAL_TIM_SET_PRESCALER(get_bank_hal_handle(bank), psc);
}

void pwm_bank_set_arr(pwm_bank bank, uint32_t arr)
{
  __HAL_TIM_SET_AUTORELOAD(get_bank_hal_handle(bank), arr);
}

void pwm_channel_start(pwm_channel channel)
{
  TIM_HandleTypeDef* htimx = get_channel_hal_handle(channel);
  if (htimx == NULL) {
    elog_e(TAG, "Invalid channel: %d", channel);
    return;
  } else {
    elog_v(TAG, "PWM channel: %d, handle: %p", channel, htimx);
  }
  uint32_t hchannel = get_channel_hal_channel(channel);
  if (hchannel == TIM_CHANNEL_ALL) {
    elog_e(TAG, "Invalid channel: %d", channel);
    return;
  } else {
    elog_v(TAG, "PWM channel: %d, hal channel: %d", channel, hchannel);
  }
  HAL_StatusTypeDef status = HAL_TIM_PWM_Start(htimx, hchannel);
  if (status != HAL_OK) {
    elog_e(TAG, "PWM start failed: %d, channel: %d", status, channel);
  } else {
    elog_v(TAG, "PWM start success: %d, channel: %d", status, channel);
  }
}

void pwm_channel_set_ccr(pwm_channel channel, uint32_t ccr)
{
  TIM_HandleTypeDef* htimx = get_channel_hal_handle(channel);
  if (htimx == NULL) {
    elog_e(TAG, "Invalid channel: %d", channel);
    return;
  } 
  uint32_t hchannel = get_channel_hal_channel(channel);
  if (hchannel == TIM_CHANNEL_ALL) {
    elog_e(TAG, "Invalid channel: %d", channel);
    return;
  } 
  elog_v(TAG, "PWM channel: %d, hal channel: %d, ccr: %d", channel, hchannel, ccr);
  __HAL_TIM_SET_COMPARE(htimx, hchannel, ccr);
}

void pwm_channel_set_duty(pwm_channel channel, double duty)
{
  uint32_t aar = __HAL_TIM_GET_AUTORELOAD(get_channel_hal_handle(channel));
  uint32_t ccr = (uint32_t) ( aar * duty + 0.5f );
  pwm_channel_set_ccr(channel, ccr);
}