#pragma once
#include "elog.h"

/**
 * @brief 初始化ELOG日志系统
 * @note 默认过滤级别为ELOG_LVL_INFO
 */
#define elog_init_default() do\
{\
  elog_init();\
  elog_set_fmt(ELOG_LVL_ASSERT,   ELOG_FMT_ALL);\
  elog_set_fmt(ELOG_LVL_ERROR,    ELOG_FMT_LVL|ELOG_FMT_TAG|ELOG_FMT_TIME);\
  elog_set_fmt(ELOG_LVL_WARN,     ELOG_FMT_LVL|ELOG_FMT_TAG|ELOG_FMT_TIME);\
  elog_set_fmt(ELOG_LVL_INFO,     ELOG_FMT_LVL|ELOG_FMT_TAG|ELOG_FMT_TIME);\
  elog_set_fmt(ELOG_LVL_DEBUG,    ELOG_FMT_LVL|ELOG_FMT_TAG|ELOG_FMT_TIME|ELOG_FMT_FUNC);\
  elog_set_fmt(ELOG_LVL_VERBOSE,  ELOG_FMT_LVL|ELOG_FMT_TAG|ELOG_FMT_TIME|ELOG_FMT_FUNC|ELOG_FMT_LINE);\
  elog_start();\
  elog_set_filter_lvl(ELOG_LVL_INFO);\
} while(0)\

#define elog_temp(tag, ...) elog_output(ELOG_LVL_WARN, tag, ELOG_OUTPUT_DIR, ELOG_OUTPUT_FUNC, ELOG_OUTPUT_LINE, __VA_ARGS__)
#define elog_t(tag, ...) elog_temp(tag, __VA_ARGS__)

#define elog_ap(tag, param_tag, param_fmt, param_var) \
  elog_output(ELOG_LVL_ASSERT, tag, ELOG_OUTPUT_DIR, ELOG_OUTPUT_FUNC, ELOG_OUTPUT_LINE, "| %-10s : " param_fmt , param_tag, param_var)
#define elog_ep(tag, param_tag, param_fmt, param_var) \
  elog_output(ELOG_LVL_ERROR, tag, ELOG_OUTPUT_DIR, ELOG_OUTPUT_FUNC, ELOG_OUTPUT_LINE, "| %-10s : " param_fmt , param_tag, param_var)
#define elog_wp(tag, param_tag, param_fmt, param_var) \
  elog_output(ELOG_LVL_WARN, tag, ELOG_OUTPUT_DIR, ELOG_OUTPUT_FUNC, ELOG_OUTPUT_LINE, "| %-10s : " param_fmt , param_tag, param_var)
#define elog_ip(tag, param_tag, param_fmt, param_var) \
  elog_output(ELOG_LVL_INFO, tag, ELOG_OUTPUT_DIR, ELOG_OUTPUT_FUNC, ELOG_OUTPUT_LINE, "| %-10s : " param_fmt , param_tag, param_var)
#define elog_dp(tag, param_tag, param_fmt, param_var) \
  elog_output(ELOG_LVL_DEBUG, tag, ELOG_OUTPUT_DIR, ELOG_OUTPUT_FUNC, ELOG_OUTPUT_LINE, "| %-10s : " param_fmt , param_tag, param_var) 
#define elog_vp(tag, param_tag, param_fmt, param_var) \
  elog_output(ELOG_LVL_VERBOSE, tag, ELOG_OUTPUT_DIR, ELOG_OUTPUT_FUNC, ELOG_OUTPUT_LINE, "| %-10s : " param_fmt , param_tag, param_var)
