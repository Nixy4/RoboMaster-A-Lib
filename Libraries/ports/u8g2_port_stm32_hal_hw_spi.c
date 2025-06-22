#include "stm32f4xx_hal.h"
#include "spi.h"
#include "elog.h"
#include "u8g2.h"
#include "main.h"
#include "bsp_cfg.h"
#include "u8g2_port.h"

#define TAG "u8g2 port"

//! board
static inline void spi_dc(int arg_int)
{
  if (arg_int == 0) {
    HAL_GPIO_WritePin(SPI1_DC_GPIO_Port, SPI1_DC_Pin, GPIO_PIN_RESET);
  } else {
    HAL_GPIO_WritePin(SPI1_DC_GPIO_Port, SPI1_DC_Pin, GPIO_PIN_SET);
  }
}

static inline void spi_rst(int arg_int)
{
  if (arg_int == 0) {
    HAL_GPIO_WritePin(SPI1_RST_GPIO_Port, SPI1_RST_Pin, GPIO_PIN_RESET);
  } else {
    HAL_GPIO_WritePin(SPI1_RST_GPIO_Port, SPI1_RST_Pin, GPIO_PIN_SET);
  }
}

//! u8x8 driver
#if 1
//原厂序列
static const uint8_t init_seq[] =
    {
        U8X8_START_TRANSFER(),

        U8X8_C(0xAE),        //! 关闭显示屏面板, POR=0xAE
        U8X8_C(0x00),        // 复位低列显存指针, POR=0x00
        U8X8_C(0x10),        // 复位高列显存指针, POR=0x10
        U8X8_C(0x40),        //! 复位行显存指针, POR=0x40
        U8X8_CA(0x81, 0xCF), //! 设置对比度, POR=0x80
        U8X8_C(0xA1),        //! 设置SEG重映射, POR=0xA0
        U8X8_C(0xC8),        //! 设置COM扫描方向, POR=0xC0
        U8X8_C(0xA6),        //! 设置显示模式, POR=0xA6
        U8X8_CA(0xA8, 0x3F), //! 设置MUX比率, POR=0x3F
        U8X8_CA(0xD3, 0x00), //! 设置显示偏移, POR=0x00
        U8X8_CA(0xD5, 0x80), //! 设置显示时钟分频比, POR=0x50
        U8X8_CA(0xD9, 0xF1), //! 设置预充电周期, POR=0x22
        U8X8_CA(0xDA, 0x12), //! 设置COM引脚硬件配置, POR=0x12
        U8X8_CA(0xDB, 0x40), //! 设置VCOMH电压倍率, POR=0x35
        U8X8_CA(0x20, 0x02), //! 设置内存寻址模式, POR=0x00
        U8X8_CA(0x8D, 0x14), //! 设置电荷泵警用, POR=0x10
        U8X8_C(0x2E),        //! 0x2E == 0b 0010 1110 关闭滑动显示
        U8X8_C(0xA4),        //! 禁用全屏显示
        U8X8_C(0xA6),        //! 禁用反色显示
        U8X8_END_TRANSFER(),
        U8X8_END()};
#else
//u8g2修改的序列
static const uint8_t init_seq[] =
    {
        U8X8_START_TRANSFER(),
        U8X8_C(0xAE),        //! 关闭显示屏面板, POR=0xAE
        U8X8_CA(0xD5, 0x80), //! 设置显示时钟分频比, POR=0x50
        U8X8_CA(0xA8, 0x3F), //! 设置MUX比率, POR=0x3F
        U8X8_CA(0xD3, 0x00), //! 设置显示偏移, POR=0x00
        U8X8_C(0x40),        //! 复位行显存指针, POR=0x40
        U8X8_CA(0x8D, 0x14), //! 设置电荷泵警用, POR=0x10
        U8X8_CA(0x20, 0x00), //! 设置内存寻址模式, POR=0x00
        U8X8_C(0xA1),        //! 设置SEG重映射, POR=0xA0
        U8X8_C(0xC8),        //! 设置COM扫描方向, POR=0xC0
        U8X8_CA(0xDA, 0x12), //! 设置COM引脚硬件配置, POR=0x12
        U8X8_CA(0x81, 0xCF), //! 设置对比度, POR=0x80
        U8X8_CA(0xD9, 0xF1), //! 设置预充电周期, POR=0x22
        U8X8_CA(0xDB, 0x40), //! 设置VCOMH电压倍率, POR=0x35
        U8X8_C(0x2E),        //! 0x2E == 0b 0010 1110 关闭滑动显示
        U8X8_C(0xA4),        //! 禁用全屏显示
        U8X8_C(0xA6),        //! 禁用反色显示
        U8X8_END_TRANSFER(),
        U8X8_END()};
#endif

//*打开显示屏面板指令序列
static const uint8_t powersave0_seq[] =
    {
        U8X8_START_TRANSFER(),
        U8X8_C(0xAF),
        U8X8_END_TRANSFER(),
        U8X8_END()};
//*关闭显示屏面板指令序列
static const uint8_t powersave1_seq[] =
    {
        U8X8_START_TRANSFER(),
        U8X8_C(0xAE),
        U8X8_END_TRANSFER(),
        U8X8_END()};
//*启用垂直翻转显示屏指令序列
static const uint8_t flip0_seq[] =
    {
        U8X8_START_TRANSFER(),
        U8X8_C(0xA1),
        U8X8_C(0xC8), 
        U8X8_END_TRANSFER(),
        U8X8_END()};
//*禁用垂直翻转显示屏指令序列
static const uint8_t flip1_seq[] =
    {
        U8X8_START_TRANSFER(),
        U8X8_C(0xA0),
        U8X8_C(0xC0),
        U8X8_END_TRANSFER(),
        U8X8_END()};

static uint8_t u8x8_d_generic(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  uint8_t x, c;
  uint8_t *ptr;
  switch (msg)
  {
  /* handled by the calling function
  case U8X8_MSG_DISPLAY_SETUP_MEMORY:
    u8x8_d_helper_display_setup_memory(u8x8, &u8x8_ssd1306_128x64_noname_display_info);
    break;
  */
  /* handled by the calling function
  case U8X8_MSG_DISPLAY_INIT:
    u8x8_d_helper_display_init(u8x8);
    u8x8_cad_SendSequence(u8x8, u8x8_d_ssd1306_128x64_noname_init_seq);
    break;
  */
  case U8X8_MSG_DISPLAY_SET_POWER_SAVE:
    if (arg_int == 0)
      u8x8_cad_SendSequence(u8x8, powersave0_seq);
    else
      u8x8_cad_SendSequence(u8x8, powersave1_seq);
    break;
  case U8X8_MSG_DISPLAY_SET_FLIP_MODE:
    if (arg_int == 0)
    {
      u8x8_cad_SendSequence(u8x8, flip0_seq);
      u8x8->x_offset = u8x8->display_info->default_x_offset;
    }
    else
    {
      u8x8_cad_SendSequence(u8x8, flip1_seq);
      u8x8->x_offset = u8x8->display_info->flipmode_x_offset;
    }
    break;

  case U8X8_MSG_DISPLAY_SET_CONTRAST:
#ifdef U8X8_WITH_SET_CONTRAST
    u8x8_cad_StartTransfer(u8x8);
    u8x8_cad_SendCmd(u8x8, 0x081);
    u8x8_cad_SendArg(u8x8, arg_int); /* ssd1306 has range from 0 to 255 */
    u8x8_cad_EndTransfer(u8x8);
#endif
    break;

  case U8X8_MSG_DISPLAY_DRAW_TILE:
    u8x8_cad_StartTransfer(u8x8);
    x = ((u8x8_tile_t *)arg_ptr)->x_pos;
    x *= 8;
    x += u8x8->x_offset;

    u8x8_cad_SendCmd(u8x8, 0x040); /* set line offset to 0 */

    u8x8_cad_SendCmd(u8x8, 0x010 | (x >> 4));
    u8x8_cad_SendArg(u8x8, 0x000 | ((x & 15)));                        /* probably wrong, should be SendCmd */
    u8x8_cad_SendArg(u8x8, 0x0b0 | (((u8x8_tile_t *)arg_ptr)->y_pos)); /* probably wrong, should be SendCmd */

    do
    {
      c = ((u8x8_tile_t *)arg_ptr)->cnt;
      ptr = ((u8x8_tile_t *)arg_ptr)->tile_ptr;
      u8x8_cad_SendData(u8x8, c * 8, ptr); /* note: SendData can not handle more than 255 bytes */
      /*
      do
      {
        u8x8_cad_SendData(u8x8, 8, ptr);
        ptr += 8;
        c--;
      } while( c > 0 );
      */
      arg_int--;
    } while (arg_int > 0);

    u8x8_cad_EndTransfer(u8x8);
    break;
  default:
    return 0;
  }
  return 1;
}

static const u8x8_display_info_t u8x8_display_intfo = 
{
  /* chip_enable_level = */ 0,
  /* chip_disable_level = */ 1,
  /* post_chip_enable_wait_ns = */ 20,
  /* pre_chip_disable_wait_ns = */ 10,
  /* reset_pulse_width_ms = */ 100, 	/* SSD1306: 3 us */
  /* post_reset_wait_ms = */ 100, /* far east OLEDs need much longer setup time */
  /* sda_setup_time_ns = */ 50,		/* SSD1306: 15ns, but cycle time is 100ns, so use 100/2 */
  /* sck_pulse_width_ns = */ 50,	/* SSD1306: 20ns, but cycle time is 100ns, so use 100/2, AVR: below 70: 8 MHz, >= 70 --> 4MHz clock */
  /* sck_clock_hz = */ 42000000UL,	/* since Arduino 1.6.0, the SPI bus speed in Hz. Should be  1000000000/sck_pulse_width_ns */
  /* spi_mode = */ 0,		/* active high, rising edge */
  /* i2c_bus_clock_100kHz = */ 4,
  /* data_setup_time_ns = */ 40,
  /* write_pulse_width_ns = */ 150,	/* SSD1306: cycle time is 300ns, so use 300/2 = 150 */
  /* tile_width = */ 16,
  /* tile_height = */ 8,
  /* default_x_offset = */ 2,
  /* flipmode_x_offset = */ 2,
  /* pixel_width = */ 128,
  /* pixel_height = */ 64  
};

uint8_t u8x8_d(u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  if ( u8x8_d_generic(u8x8, msg, arg_int, arg_ptr) != 0 )
    return 1;
  
  switch(msg)
  {
    case U8X8_MSG_DISPLAY_INIT:
      u8x8_d_helper_display_init(u8x8);
      u8x8_cad_SendSequence(u8x8, init_seq);    
      break;
    case U8X8_MSG_DISPLAY_SETUP_MEMORY:
      u8x8_d_helper_display_setup_memory(u8x8, &u8x8_display_intfo);
      break;
    default:
      return 0;
  }
  return 1;
}

//! u8g2 port
void u8g2_Setup(u8g2_t *u8g2, const u8g2_cb_t *rotation, u8x8_msg_cb byte_cb, u8x8_msg_cb gpio_and_delay_cb)
{
  uint8_t tile_buf_height;
  uint8_t *buf;
  u8g2_SetupDisplay(u8g2, u8x8_d, u8x8_cad_001, byte_cb, gpio_and_delay_cb);
  buf = u8g2_m_16_8_f(&tile_buf_height);
  u8g2_SetupBuffer(u8g2, buf, tile_buf_height, u8g2_ll_hvline_vertical_top_lsb, rotation);
}

uint8_t u8x8_byte(U8X8_UNUSED u8x8_t *u8x8, uint8_t msg, uint8_t arg_int, void *arg_ptr)
{
  switch (msg)
  {
    case U8X8_MSG_BYTE_SET_DC:
      spi_dc(arg_int);
      break;
    case U8X8_MSG_BYTE_SEND:
    {

#if CONFIG_BSP_USE_CMSIS_RTOS2==1
      HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, arg_ptr, arg_int, HAL_MAX_DELAY);
      if (status != HAL_OK) {
        elog_e(TAG, "HAL_SPI_Transmit failed, status: %d", status);
        return 0;
      }
      break;

#else

      HAL_StatusTypeDef status = HAL_SPI_Transmit(&hspi1, arg_ptr, arg_int, HAL_MAX_DELAY);
      if (status != HAL_OK) {
        elog_e(TAG, "HAL_SPI_Transmit failed, status: %d", status);
        return 0;
      }

#endif

      break;
    }
  default: return 0;
  }
  return 1;
}

uint8_t u8x8_gpio_and_delay(U8X8_UNUSED u8x8_t *u8x8, uint8_t msg, uint8_t arg_int,U8X8_UNUSED  void *arg_ptr)
{
  switch (msg)
  {
  case U8X8_MSG_GPIO_CS:
    break;
  case U8X8_MSG_GPIO_DC:
    spi_dc(arg_int);
    break;
  case U8X8_MSG_GPIO_RESET:
    spi_rst(arg_int);
    break;
  case U8X8_MSG_DELAY_NANO:
    break;
  case U8X8_MSG_DELAY_100NANO:
    break;
  case U8X8_MSG_DELAY_10MICRO:
    break;
  case U8X8_MSG_DELAY_MILLI:
    u8g2_delay_ms(arg_int);
    break;
  default:
    return 0;
  }
  return 1;
}

void u8g2_init(u8g2_t *u8g2)
{
  u8g2_Setup(u8g2, U8G2_R0, u8x8_byte, u8x8_gpio_and_delay);
  u8g2_InitDisplay(u8g2);
  u8g2_InitInterface(u8g2);
  u8g2_SetPowerSave(u8g2, 0);

  u8g2_ClearBuffer(u8g2);
  u8g2_SetFont(u8g2, u8g2_font_6x10_tf);
  u8g2_DrawStr(u8g2, 0, 10, "u8g2 init success");
  u8g2_SendBuffer(u8g2);
  elog_i(TAG, "u8g2 init success");
}