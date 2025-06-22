#include "quadruped.h"
#include "pwm.h"

#define TAG "Servo"

inline quad_fp servo_angle_mirror(quad_fp angle)
{
  return 180.f - angle;
}

inline quad_fp servo_angle_offset(quad_fp angle, quad_fp offset)
{
  return angle + offset;
}

inline quad_fp servo_angle_limit_thigh(quad_fp angle)
{
  if(angle > CONFIG_SERVO_LIMIT_MAX_T) {
    return CONFIG_SERVO_LIMIT_MAX_T;
  } else if(angle < CONFIG_SERVO_LIMIT_MIN_T) {
    return CONFIG_SERVO_LIMIT_MIN_T;
  }
  return angle;
}

inline quad_fp servo_angle_limit_shank(quad_fp angle)
{
  if(angle > CONFIG_SERVO_LIMIT_MAX_S) {
    return CONFIG_SERVO_LIMIT_MAX_S;
  } else if(angle < CONFIG_SERVO_LIMIT_MIN_S) {
    return CONFIG_SERVO_LIMIT_MIN_S;
  }
  return angle;
}

static inline pwm_channel get_pwm_channel(servo_index servo)
{
  switch (servo)
  {
    case SERVO_RF_T: return PWM_CHANNEL_Z;
    case SERVO_RF_S: return PWM_CHANNEL_Y;
    case SERVO_LF_T: return PWM_CHANNEL_A;
    case SERVO_LF_S: return PWM_CHANNEL_B;
    case SERVO_RB_T: return PWM_CHANNEL_X;
    case SERVO_RB_S: return PWM_CHANNEL_W;
    case SERVO_LB_T: return PWM_CHANNEL_C;
    case SERVO_LB_S: return PWM_CHANNEL_D;
    default: return PWM_CHANNEL_ERROR; // Invalid servo index
  }
}

void servo_set_angle(servo_index servo, quad_fp angle)
{
  uint32_t ccr = (uint32_t)(CONFIG_SERVO_TIM_CCR_DELTA * angle / 180.0f + 0.5f) + CONFIG_SERVO_TIM_CCR_MIN;
  int hchannel = get_pwm_channel(servo);
  if (hchannel == PWM_CHANNEL_ERROR) {
    elog_e(TAG, "Invalid servo index: %d", servo);
    return;
  }
  pwm_channel_set_ccr(hchannel, ccr);
}

void servo_init(quad_fp angles[SERVO_COUNT])
{
  /**
   * tim apb clock = 84 000 000 Hz
   * psc = 83
   * arr = 2500
   * freq = 84 000 000 / (83 + 1) / (2500 + 1) = 40 Hz
   */
  pwm_bank_set_psc(PWM_BANK_ABCD, CONFIG_SERVO_TIM_PSC);
  pwm_bank_set_arr(PWM_BANK_ABCD, CONFIG_SERVO_TIM_ARR);
  pwm_bank_set_psc(PWM_BANK_EFGH, CONFIG_SERVO_TIM_PSC);
  pwm_bank_set_arr(PWM_BANK_EFGH, CONFIG_SERVO_TIM_ARR);
  for(servo_index i = SERVO_START; i<SERVO_COUNT; i++) {
    pwm_channel_start(get_pwm_channel(i));
    servo_set_angle(i, angles[i]);
  }
}

void servo_set_angle_sync(quad_fp angles[SERVO_COUNT])
{
  for( servo_index i = SERVO_START; i<SERVO_COUNT; i++) {
    servo_set_angle(i, angles[i]);
  }
}

