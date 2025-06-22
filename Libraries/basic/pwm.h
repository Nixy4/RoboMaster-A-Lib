#include "bsp_cfg.h"
#include "stdint.h"

#ifdef __cplusplus
extern "C" {
#endif

typedef enum pwm_bank
{
  PWM_BANK_ERROR = -1,
  PWM_BANK_START = 0U,
  PWM_BANK_ABCD  = PWM_BANK_START,  //TIM4
  PWM_BANK_EFGH,  //TIM5
  PWM_BANK_STUV,  //TIM2
  PWM_BANK_WXYZ,  //TIM8
  PWM_BANK_END = PWM_BANK_WXYZ,
  PWM_BANK_COUNT,
} pwm_bank;

typedef enum pwm_channel
{
  PWM_CHANNEL_ERROR = -1,
  PWN_CHANNEL_START = 0,
  //TIM4
  PWM_CHANNEL_A = PWN_CHANNEL_START,
  PWM_CHANNEL_B,
  PWM_CHANNEL_C,
  PWM_CHANNEL_D,
  //TIM5
  PWM_CHANNEL_E,
  PWM_CHANNEL_F,
  PWM_CHANNEL_G,
  PWM_CHANNEL_H,
  //TIM2
  PWM_CHANNEL_S,
  PWM_CHANNEL_T,
  PWM_CHANNEL_U,
  PWM_CHANNEL_V,
  //TIM8
  PWM_CHANNEL_W,
  PWM_CHANNEL_X,
  PWM_CHANNEL_Y,
  PWM_CHANNEL_Z,
  
  PWN_CHANNEL_END = PWM_CHANNEL_Z,
  PWN_CHANNEL_COUNT,
} pwm_channel;

void pwm_bank_set_freq(pwm_bank bank, uint32_t freq);
void pwm_bank_set_psc(pwm_bank bank, uint32_t psc);
void pwm_bank_set_arr(pwm_bank bank, uint32_t arr);

void pwm_channel_start(pwm_channel channel);
void pwm_channel_set_ccr(pwm_channel channel, uint32_t ccr);
void pwm_channel_set_duty(pwm_channel channel, double duty);

#ifdef __cplusplus
}
#endif