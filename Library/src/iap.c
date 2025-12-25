/**
 * @file      iap_aprom.c
 * @brief     实现IAP功能
 * @author    Software Team
 * @date      2023-07
 * @version   V1.0.0
 * @copyright WAYON
 */
#include "iap.h"
#include "common.h"

#define LDROM_0K      (0)
#define LDROM_1K      (1024)
#define LDROM_2K      (2048)
#define LDROM_3K      (3072)
#define LDROM_4K      (4096)
#define LDROM_MAX_NUM (LDROM_4K) /*!< LDROM的大小从keil config里进行配置 */

static uint8_t _IAPGo(void);

/**
 * 擦除一个page(128字节)
 * @param[in] u16Addr: 擦 除地址号，必须为一个page的整数倍
 */
void LDROM_ErasePage(uint16_t u16Addr)
{
    bit bitTemp;

    /* 判断地址是否越界，且地址应为page整数倍 */
    if ((u16Addr > LDROM_MAX_NUM - ROM_PAGE_NUM) && (u16Addr % ROM_PAGE_NUM != 0)) {
        return;
    }

    bitTemp = EA;
    EA      = 0;
    SFR_PAGE_1;

    ENABLE_IAP;        /* 使能IAP功能 */
    IAP_ADDR(u16Addr); /* 写入擦除地址号 */
    LDROM_REASE_PAGE;  /* LDROM页擦除 */
    IAP_DATA = 0xFF;   /* 数据位写入0xFF */
    ENABLE_LDUEN;      /* 使能IAP擦除 */
    _IAPGo();          /* IAP执行启动位 */
    DISABLE_LDUEN;     /* 禁用IAP擦除 */
    DISABLE_IAP;       /* 禁用IAP功能 */

    SFR_PAGE_0;
    EA = bitTemp;
}

/**
 * LDROM写入数据
 * @param[in] u16Addr:    写地址(地址位宽16bit)
 * @param[in] u8pDataBuf: 写入数据内容
 * @param[in] u16size:    写入数据长度
 * @note 写入之前应先擦除该page
 */
void LDROM_Write(uint16_t u16Addr, uint8_t *u8pDataBuf, uint16_t u16size)
{
    bit      bitTemp;
    uint16_t i;

    if ((u16Addr + u16size) > LDROM_MAX_NUM) /* 判断地址是否越界 */
    {
        return;
    }

    bitTemp = EA;
    EA      = 0;
    SFR_PAGE_1;

    ENABLE_IAP;                   /* 使能IAP功能 */
    ENABLE_LDUEN;                 /* 使能编程LDROM */
    LDROM_WRITE_BYTE;             /* LDROM字节写 */
    for (i = 0; i < u16size; i++) {
        IAP_ADDR(i + u16Addr);    /* 写入地址号 */
        IAP_DATA = u8pDataBuf[i]; /* 写入数据 */
        if (1 == _IAPGo())        /* 如果IAP错误，则退出 */
        {
            break;
        }
    }
    DISABLE_LDUEN; /* 禁用IAP编程 */
    DISABLE_IAP;   /* 禁用IAP功能 */

    SFR_PAGE_0;
    EA = bitTemp;
}

/**
 * 从LDROM读出数据
 * @param[in]  u16Addr:    读地址(地址位宽16bit)
 * @param[in]  u16size:    读出数据长度
 * @param[out] u8pDataBuf: 读出数据内容
 */
void LDROM_Read(uint16_t u16Addr, uint8_t *u8pDataBuf, uint16_t u16size)
{
    bit      bitTemp;
    uint16_t i;

    if ((u16Addr + u16size) > LDROM_MAX_NUM) /* 判断地址是否越界 */
    {
        return;
    }

    bitTemp = EA;
    EA      = 0;
    SFR_PAGE_1;

    ENABLE_IAP;                /* 使能IAP功能 */
    LDROM_READ_BYTE;           /* LDROM字节读 */
    for (i = 0; i < u16size; i++) {
        IAP_ADDR(i + u16Addr); /* 写入读地址号 */
        if (1 == _IAPGo())     /* 如果IAP错误，则退出 */
        {
            break;
        }
        u8pDataBuf[i] = IAP_DATA;
    }
    DISABLE_IAP; /* 禁用IAP功能 */

    SFR_PAGE_0;
    EA = bitTemp;
}

/**
 * 擦除一个page(128字节)
 * @param[in] u16Addr  擦除地址号，必须为一个page的整数倍
 */
void APROM_ErasePage(uint16_t u16Addr)
{
    bit bitTemp;

    /* 判断地址是否越界，且地址应为page整数倍 */
    if ((u16Addr > APROM_END_ADDR - ROM_PAGE_NUM + 1) && (u16Addr % ROM_PAGE_NUM != 0)) {
        return;
    }

    bitTemp = EA;
    EA      = 0;
    SFR_PAGE_1;

    ENABLE_IAP;        /* 使能IAP功能 */
    IAP_ADDR(u16Addr); /* 写入擦除地址号 */
    APROM_REASE_PAGE;  /* APROM页擦除 */
    IAP_DATA = 0xFF;   /* 数据位写入0xFF */
    ENABLE_APUEN;      /* 使能IAP擦除 */
    _IAPGo();          /* IAP执行启动位 */
    DISABLE_APUEN;     /* 禁用IAP擦除 */
    DISABLE_IAP;       /* 禁用IAP功能 */

    SFR_PAGE_0;
    EA = bitTemp;
}

/**
 * APROM写入数据
 * @param[in] u16Addr:    写地址(地址位宽16bit)
 * @param[in] u8pDataBuf: 写入数据内容
 * @param[in] u16size:    写入数据长度
 * @note 写入之前应先擦除该page
 */
void APROM_Write(uint16_t u16Addr, uint8_t *u8pDataBuf, uint16_t u16size)
{
    bit      bitTemp;
    uint16_t i;

    if ((u16Addr + u16size) > APROM_END_ADDR + 1) /* 判断地址是否越界 */
    {
        return;
    }

    bitTemp = EA;
    EA      = 0;
    SFR_PAGE_1;

    ENABLE_IAP;                   /* 使能IAP功能 */
    ENABLE_APUEN;                 /* 使能编程APROM */
    APROM_WRITE_BYTE;             /* APROM字节写 */
    for (i = 0; i < u16size; i++) {
        IAP_ADDR(i + u16Addr);    /* 写入地址号 */
        IAP_DATA = u8pDataBuf[i]; /* 写入数据 */
        if (1 == _IAPGo())        /* 如果IAP错误，则退出 */
        {
            break;
        }
    }
    DISABLE_APUEN; /* 禁用IAP编程 */
    DISABLE_IAP;   /* 禁用IAP功能 */

    SFR_PAGE_0;
    EA = bitTemp;
}

/**
 * 从APROM读出数据
 * @param[in]  u16Addr:    读地址(地址位宽16bit)
 * @param[in]  u16size:    读出数据长度
 * @param[out] u8pDataBuf: 读出数据内容
 */
void APROM_Read(uint16_t u16Addr, uint8_t *u8pDataBuf, uint16_t u16size)
{
    bit      bitTemp;
    uint16_t i;

    if ((u16Addr + u16size) > APROM_END_ADDR + 1) /* 判断地址是否越界 */
    {
        return;
    }

    bitTemp = EA;
    EA      = 0;
    SFR_PAGE_1;

    ENABLE_IAP;                /* 使能IAP功能 */
    APROM_READ_BYTE;           /* APROM字节读 */
    for (i = 0; i < u16size; i++) {
        IAP_ADDR(i + u16Addr); /* 写入读地址号 */
        if (1 == _IAPGo())     /* 如果IAP错误，则退出 */
        {
            break;
        }
        u8pDataBuf[i] = IAP_DATA;
    }
    DISABLE_IAP; /* 禁用IAP功能 */

    SFR_PAGE_0;
    EA = bitTemp;
}

/**
 * 读取公司ID
 * @return 公司ID
 */
uint8_t Read_CompanyID(void)
{
    bit     bitTemp;
    uint8_t u8id;

    bitTemp = EA;
    EA      = 0;
    SFR_PAGE_1;

    ENABLE_IAP;
    READ_COMPANY_ID; /* 发送读ID命令 */
    _IAPGo();        /* 开始执行IAP */
    u8id = IAP_DATA;
    DISABLE_IAP;

    SFR_PAGE_0;
    EA = bitTemp;

    return u8id;
}

/**
 * 读取器件ID
 * @param[out] u8IdBuf: 器件ID，共2个字节 u8IdBuf[0]:器件ID低字节  u8IdBuf[1]:器件ID高字节
 */
void Read_ChipID(uint8_t *u8IdBuf)
{
    bit bitTemp;

    bitTemp = EA;
    EA      = 0;
    SFR_PAGE_1;

    ENABLE_IAP;
    READ_CHIP_ID;          /* 发送读ID命令 */
    IAP_ADDR(0x0000);      /* 写入读地址号 */
    _IAPGo();              /* 开始执行IAP */
    u8IdBuf[0] = IAP_DATA; /* 返回器件ID低字节 */
    IAP_ADDR(0x0001);      /* 写入读地址号 */
    _IAPGo();              /* 开始执行IAP */
    u8IdBuf[1] = IAP_DATA; /* 返回器件ID高字节 */
    DISABLE_IAP;

    SFR_PAGE_0;
    EA = bitTemp;
}

/**
 * 读取96bit UID
 * @param[out] u8IdBuf 96bit UID
 */
void Read_UID(uint8_t *u8IdBuf)
{
    bit     bitTemp;
    uint8_t i;

    bitTemp = EA;
    EA      = 0;
    SFR_PAGE_1;

    ENABLE_IAP;
    for (i = 0; i < 12; i++) {
        IAP_ADDR(0x0000 + i); /* 写入读地址号 */
        READ_UID_ID;          /* 发送读ID命令 */
        if (1 == _IAPGo())    /* 如果IAP错误，则退出 */
        {
            break;
        }
        u8IdBuf[i] = IAP_DATA; /* 获取UID值 */
    }
    DISABLE_IAP;

    SFR_PAGE_0;
    EA = bitTemp;
}

/**
 * 获取芯片出厂存储的内部带隙电压值
 * @return ADC带隙电压值 单位mV
 */
uint16_t IAP_GetChipBandGap(void)
{
    uint8_t  u8BGBuf[2];
    uint16_t u16adcData;
    bit      bitTemp;
    uint8_t  i;

    bitTemp = EA;
    EA      = 0;
    SFR_PAGE_1;

    ENABLE_IAP;
    for (i = 0; i < 2; i++) {
        IAP_ADDR(0x001C + i); /* 写入读地址号 */
        IAPCN = 0xC0;         /* 发送读ID命令 */
        if (1 == _IAPGo())    /* 如果IAP错误，则退出 */
        {
            break;
        }
        u8BGBuf[i] = IAP_DATA; /* 获取UID值 */
    }
    DISABLE_IAP;

    SFR_PAGE_0;
    EA = bitTemp;

    u16adcData = ((u8BGBuf[1] & 0x0F) << 8) | u8BGBuf[0];
    return u16adcData;
}

/**
 * APROM开始执行
 * @return 0: 执行成功
 *         1: 执行失败
 */
static uint8_t _IAPGo(void)
{
    ENABLE_IAPGO;              /* IAP执行启动位 */
    while (1 == IS_IAPGO_FLAG) /* 等待IAP处理完成 */
    {
    }
    if (1 == IS_IAPFF_FLAG) /* IAP错误 */
    {
        CLR_IAPFF_FLAG;     /* 清除IAP错误标志 */
        return 1;
    }
    return 0;
}
