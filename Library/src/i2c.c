/**
 * @file      i2c.c
 * @brief     I2C模块驱动
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */

#include "i2c.h"
#include "common.h"

#define I2C_100K (100000)
#define I2C_400K (400000)

/**
 * I2C主机模式配置
 * @param[in] u8addr7bit 主机地址(有效位:低7bit)
 * @param[in] u8gcMode 主机广播/普通模式配置
 * -# I2C_NORMAL_MODE:   普通模式
 * -# I2C_BROADCAST_MODE:广播模式
 * @param[in] u32cnt 速率值 单位为Hz
 */
void I2C_ConfigMasterMode(uint8_t u8addr7bit, uint8_t u8gcMode, uint32_t u32cnt)
{
    uint8_t u8clkCnt;

    I2C_I2CCON_MS_SET(I2C_MASTER_MODE);           /* 选择主机模式 */
    I2C_I2CTADDR_TADDR_SET(u8addr7bit);           /* 主机地址配置 */
    I2C_I2CTADDR_GC_SET(u8gcMode);                /* 主机广播/普通模式配置 */
    u8clkCnt = (g_u32SystemClock / u32cnt - 8) / 4;
    I2C_I2CRAT_CLKCNT(u8clkCnt);                  /* SCL频率配置位 */
    if (u32cnt <= I2C_100K) {
        I2C_I2CCON_FS_SET(I2C_NORMAL_SPEED_MODE); /* 配置为标准模式 */
    } else if (u32cnt <= I2C_400K) {
        I2C_I2CCON_FS_SET(I2C_FAST_SPEED_MODE);   /* 配置为快速模式 */
    } else {
        /* none */
    }
}

/**
 * I2C从机模式配置
 * @param[in] u8addr7bit 从机地址(有效位:低7bit)
 * @param[in] u8rateMode 传输速率配置位
 * -# I2C_NORMAL_SPEED_MODE:标准模式
 * -# I2C_FAST_SPEED_MODE:  快速模式
 */
void I2C_ConfigSlaveMode(uint8_t u8addr7bit, uint8_t u8rateMode)
{
    I2C_I2CCON_MS_SET(I2C_SLAVE_MODE);  /* 选择从机模式 */
    I2C_I2CSADDR_SADDR_SET(u8addr7bit); /* 从机地址配置 */
    I2C_I2CCON_FS_SET(u8rateMode);      /* 配置为速率模式 */
}

/**
 * 主机发送START或ACK信号
 */
void I2C_SendStartACK(void)
{
    while (0 == IS_I2C_TXEMPTY_FLAG)
        ;                 /* 判断发送BUFFER是否为空 */
    I2C_WRITE_DATA(0x00); /* I2C发送数据 */
}

/**
 * I2C主机读/写
 * @param[in] mode 读写操作
 * -# I2C_READ 读操作
 * -# I2C_WRITE  写操作
 * @param[in] buffer 读写缓存
 * @param[in] length 读写长度
 * @return 0  I2C buffer读/写完成
 *         -1 总线忙
 *         -2 发送错误中止
 */
int8_t I2C_MasterTRBuffer(uint8_t mode, uint8_t *buffer, uint8_t length)
{
    uint8_t i;

    /* 等待总线空闲 */
    if (0 == IS_I2C_IDLE_FLAG) {
        return -1;
    }
    if (mode == I2C_WRITE) {
        I2C_WRITE_MODE; /* 主机写模式 */

        for (i = 0; i < length; i++) {
            /* 判断发送BUFFER是否为空 */
            while (0 == IS_I2C_TXEMPTY_FLAG)
                ;
            I2CDAT = *(buffer + i);     /* I2C写入数据 */
            if (1 == IS_I2C_TXERR_FLAG) /* 发送错误中止 */
            {
                return -2;
            }
        }
        ENABLE_I2C_STOP;    /* 产生停止位 */
    } else if (mode == I2C_READ) {
        I2C_READ_MODE;      /* 主机读模式 */
        I2C_SendStartACK(); /* 发送Start信号 */

        for (i = 0; i < length;) {
            while (0 == IS_I2C_RXFUL_FLAG)
                ;
            *(buffer + i) = I2CDAT;     /* 读出数据 */
            if (++i != length) {
                I2C_SendStartACK();     /* 发送ACK信号 */
            } else {
                ENABLE_I2C_STOP;        /* 产生停止位   */
            }
            if (1 == IS_I2C_TXERR_FLAG) /* 发送错误中止 */
                return -2;
        }
    }

    /* 等待产生停止位 */
    while (0 == IS_I2C_STOP_FLAG)
        ;
    CLR_I2C_STOP_FLAG;  /* 清除停止标志 */
    CLR_I2C_START_FLAG; /* 清除START标志 */
    DISABLE_I2C_STOP;   /* 禁止产生停止位   */
    return 0;
}
