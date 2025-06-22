#pragma once

//!CCMRAM配置
#define CONFIG_STM32_CCMRAM_ENBALE 1

//!浮点类型和计算类型
#define CONFIG_FLOAT_TYPE 0
#define CONFIG_CONST_TYPE 0

//!舵机参数
//舵机PWM频率
#define CONFIG_SERVO_FREQ_HZ       50U
#define CONFIG_SERVO_PERIOD_US     20000U                                // == 1/50Hz == 20ms == 20000us
#define CONFIG_SERVO_TIM_CLOCK     84000000U
#define CONFIG_SERVO_TIM_PSC       (CONFIG_SERVO_TIM_CLOCK/1000000U - 1) // == 83
#define CONFIG_SERVO_TIM_ARR       (CONFIG_SERVO_PERIOD_US - 1)          // == 20000us-1 == 19999
#define CONFIG_SERVO_TIM_CCR_MIN   500U
#define CONFIG_SERVO_TIM_CCR_MAX   2500U
#define CONFIG_SERVO_TIM_CCR_DELTA 2000U                                 // == 2ms == 2000us

//舵机角度极限
#define CONFIG_SERVO_LIMIT_MIN_T     0.f
#define CONFIG_SERVO_LIMIT_MAX_T     120.f
#define CONFIG_SERVO_LIMIT_MIN_S     0.f
#define CONFIG_SERVO_LIMIT_MAX_S     135.f
//角度偏移
#define CONFIG_SERVO_OFFSET_RF_T     5.0f
#define CONFIG_SERVO_OFFSET_RF_S     15.0f

#define CONFIG_SERVO_OFFSET_LF_T     10.0f
#define CONFIG_SERVO_OFFSET_LF_S     10.0f

#define CONFIG_SERVO_OFFSET_RB_T     5.0f
#define CONFIG_SERVO_OFFSET_RB_S     10.0f

#define CONFIG_SERVO_OFFSET_LB_T     5.0f
#define CONFIG_SERVO_OFFSET_LB_S     0.0f

#define CONFIG_SERVO_OFFSET_GLOBAL_T 0.0f
#define CONFIG_SERVO_OFFSET_GLOBAL_S 0.0f

//!常量
//PI
#define CONFIG_PI                 3.1415926535897931f
#define CONFIG_HPI                1.5707963267948966f
#define CONFIG_DPI                6.2831853071795862f
#define CONFIG_DEGREE_TO_RADIAN   0.0174532925199433f
#define CONFIG_RADIAN_TO_DEGREE   57.2957795130823229f
//大腿组
#define CONFIG_L1                 79.0f
#define CONFIG_L2                 68.5f
#define CONFIG_L3                 20.0f
#define CONFIG_L5                 78.7908624143688314f
#define CONFIG_R15                0.4182243295792291f
//小腿组
#define CONFIG_L8                 14.5000000000000000f
#define CONFIG_L9                 77.0000000000000000f
#define CONFIG_L6_MAX             (CONFIG_L8+CONFIG_L9)
#define CONFIG_L6_MIN             68.7191549248772446f

//!运动学算法测试误差范围
#define CONFIG_KINE_DEGREE_ERROR_RANGE 1.0f
#define CONFIG_KINE_RADIAN_ERROR_RANGE CONFIG_KINE_DEGREE_ERROR_RANGE*CONFIG_DEGREE_TO_RADIAN
#define CONFIG_KINE_LENGTH_ERROR_RANGE 1.0f

//!腿坐参数
//腿坐标偏移
#define CONFIG_LEG_COORD_OFFSET_RF_X 4.0f
#define CONFIG_LEG_COORD_OFFSET_RF_Z 0.0f

#define CONFIG_LEG_COORD_OFFSET_LF_X 4.0f
#define CONFIG_LEG_COORD_OFFSET_LF_Z 0.0f

#define CONFIG_LEG_COORD_OFFSET_RB_X 0.0f
#define CONFIG_LEG_COORD_OFFSET_RB_Z 0.0f

#define CONFIG_LEG_COORD_OFFSET_LB_X 0.0f
#define CONFIG_LEG_COORD_OFFSET_LB_Z 0.0f

#define CONFIG_LEG_COORD_OFFSET_GLOBAL_X 10.0f
#define CONFIG_LEG_COORD_OFFSET_GLOBAL_Z 0.0f

//!用户特殊点位参数
#define CONFIG_USER_COORD_STAND0_X 0.0f
#define CONFIG_USER_COORD_STAND0_Z 115.0f

//!由于舵机角速度有限,角度更新速度和坐标更新速度不能太快

//!Angle Control Block 参数
#define CONFIG_ACB_DEFAULT_EASING_CALC         _easing_calc_Linear

#define CONFIG_ACB_DEFAULT_FRAME_INTERVAL_TICK 1U                  // hal tick
#define CONFIG_ACB_DEFAULT_FRAME_INTERVAL_MS   1U                  // ms
#define CONFIG_ACB_DEFAULT_FRAME_INTERVAL_US   700U                // us
#define CONFIG_ACB_DEFAULT_FRAME_MODE          FCB_MODE_TICK
#define CONFIG_ACB_DEFAULT_FRAME_INTERVAL      CONFIG_ACB_DEFAULT_FRAME_INTERVAL_TICK

#define CONFIG_ACB_UPDATE_KINE                 false
#define CONFIG_ACB_FRAME_INTERVAL_COEFFICIENT  (2.23f) // 舵机角速度 140ms/60° = 2.33°/ms

//!Coord Control Block 参数
#define CONFIG_CCB_DEFAULT_EASING_CALC_X       _easing_calc_Linear
#define CONFIG_CCB_DEFAULT_EASING_CALC_Z       _easing_calc_Linear

#define CONFIG_CCB_DEFAULT_FRAME_INTERVAL_TICK 1U                  // hal tick
#define CONFIG_CCB_DEFAULT_FRAME_INTERVAL_MS   1U                  // ms
#define CONFIG_CCB_DEFAULT_FRAME_INTERVAL_US   700U                // us
#define CONFIG_CCB_DEFAULT_FRAME_MODE          FCB_MODE_TICK
#define CONFIG_CCB_DEFAULT_FRAME_INTERVAL      CONFIG_CCB_DEFAULT_FRAME_INTERVAL_TICK

#define CONFIG_FCB_FRAME_INTERVAL_COEFFICIENT  (15.f)

//!Fixed 参数
#define CONFIG_FIXED_FRAME_COUNT           700U

//!Tort 参数
#define CONFIG_TORT_BASE_X                 0.0f
#define CONFIG_TORT_BASE_Z                 110.0f
#define CONFIG_TORT_DEFAULT_FRAME_MODE     FCB_MODE_TICK
#define CONFIG_TORT_DEFAULT_FRAME_INTERVAL 1U            // hal tick
#define CONFIG_TORT_READY_FRAME_COUNT      500

//!Step In Place 参数
#define CONFIG_SIP_BASE_X                 cc_stand0.X
#define CONFIG_SIP_BASE_Z                 cc_stand0.Z
#define CONFIG_SIP_DEFAULT_FRAME_MODE     FCB_MODE_TICK
#define CONFIG_SIP_DEFAULT_FRAME_INTERVAL 2U            // hal tick
#define CONFIG_SIP_READY_FRAME_COUNT      500
