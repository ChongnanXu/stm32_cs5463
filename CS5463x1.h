//==================================================================================================
//  文件名称: CS5463x1.h
//  文件功能: CS5463x1-1路单相双向功率/电能芯片
//  文件说明: 单相电220V表示 有效值为220V 振幅值为311V
//            RMS表示有效值
//            1V = 1000mV = 1000*1000uV
//            1A = 1000mA = 1000*1000uA
//            1W = 1000mW = 1000*1000uW
//  文件类型: Board-板载设备驱动代码
//==================================================================================================

#ifndef __CS5463x1_H__
#define __CS5463x1_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

//--------------------------------------------------------------------------------------------------
//  宏自定义声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#define CS5463x1_STATE_SUCCESS              (0)             // CS5463x1状态 成功状态
#define CS5463x1_STATE_FAILURE              (1)             // CS5463x1状态 失败状态
#define CS5463x1_STATE_UNKNOWN              (2)             // CS5463x1状态 未知状态
    
//  CS5463x1 工作模式
#define CS5463x1_WORKMODE_SPI_HARDWARE      (0)             // CS5463x1操作模式 SPI_HARDWARE - SPI总线硬件驱动
#define CS5463x1_WORKMODE_SPI_SOFTWARE      (1)             // CS5463x1操作模式 SPI_SOFTWARE - SPI总线软件模拟
#define CS5463x1_WORKMODE                   CS5463x1_WORKMODE_SPI_HARDWARE          // SPI总线硬件驱动

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  CS5463x1 功能配置
//  电压比例参数说明：
//  假设外围电路输入默认220V 使用220KΩ+ZMPT107电压互感器（2mA:2mA） 使用110Ω采样电阻
//  即 (220V/220KΩ) * (2mA/2mA) * 110Ω = 110mV 满足小于CS5463x1电压量程
//  CS5463x1电压输入量程为250mV（在没有重新配置量程情况下）
//  CS5463x1电压采样结果为0.0~1.0范围的VData数值
//  反向推算出 电压有效值 = VData * 250mV / 110Ω * (2mA/2mA) * 220KΩ;
//                        = VData * 500;        (单位为V)
//                        = VData * 500 * 1000; (单位为mV)
#define CS5463x1_FUNCTION_VScale            (500000)        // CS5463x1 计算电压比例

//  电流比例参数说明：
//  假设外围电路输入最大10A 使用ZMCT102A电流互感器（5A:2.5mA） 使用10Ω采样电阻
//  即 10A * (2.5mA/5A) * 10Ω = 50mV 满足小于CS5463x1电流量程
//  CS5463x1电流输入量程为250mV（在没有重新配置量程情况下）
//  CS5463x1电流采样结果为0.0~1.0范围的VData数值
//  反向推算出 电流有效值 = VData * 250mV / 10Ω * (5A/2.5mA);
//                        = VData * 50000; （单位为MA）
#define CS5463x1_FUNCTION_IScale            (50000)         // CS5463x1 计算电流比例

//--------------------------------------------------------------------------------------------------
//  端口引脚定义    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#if (CS5463x1_WORKMODE == CS5463x1_WORKMODE_SPI_HARDWARE)   // SPI总线硬件驱动

    #define CS5463x1_RST_GPIO_PORT                  (GPIOxC)        // CS5463x1 复位 GPIO端口
    #define CS5463x1_RST_GPIO_PIN                   (GPIOc1)        // CS5463x1 复位 GPIO引脚

    #define CS5463x1_IRQ_GPIO_PORT                  (GPIOxC)        // CS5463x1 外部中断 GPIO端口
    #define CS5463x1_IRQ_GPIO_PIN                   (GPIOc2)        // CS5463x1 外部中断 GPIO引脚
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    #define CS5463x1_RST_GPIO_Output_H()            GPIO_SetBit(CS5463x1_RST_GPIO_PORT, CS5463x1_RST_GPIO_PIN)      // CS5463x1 复位 GPIO输出高电平
    #define CS5463x1_RST_GPIO_Output_L()            GPIO_ResetBit(CS5463x1_RST_GPIO_PORT, CS5463x1_RST_GPIO_PIN)    // CS5463x1 复位 GPIO输出低电平

    #define CS5463x1_SPI_SendReciveByte(X)          SPIx2_HARDWARE_SendReciveByte(X)        // CS5463x1 SPI总线 发送接收数据操作
    #define CS5463x1_SPI_ChipSelectEnable()         SPIx2_HARDWARE_ChipSelect(1, 0)         // CS5463x1 SPI总线 使能片选有效
    #define CS5463x1_SPI_ChipSelectDisable()        SPIx2_HARDWARE_ChipSelect(1, 1)         // CS5463x1 SPI总线 禁能片选无效

#endif  // #if (CS5463x1_WORKMODE == CS5463x1_WORKMODE_SPI_HARDWARE)

//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
#if (CS5463x1_WORKMODE == CS5463x1_WORKMODE_SPI_SOFTWARE)   // SPI总线软件模拟

    #define CS5463x1_RST_GPIO_PORT                  (GPIOxC)        // CS5463x1 复位 GPIO端口
    #define CS5463x1_RST_GPIO_PIN                   (GPIOc1)        // CS5463x1 复位 GPIO引脚

    #define CS5463x1_IRQ_GPIO_PORT                  (GPIOxC)        // CS5463x1 外部中断 GPIO端口
    #define CS5463x1_IRQ_GPIO_PIN                   (GPIOc2)        // CS5463x1 外部中断 GPIO引脚
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    #define CS5463x1_RST_GPIO_Output_H()            GPIO_SetBit(CS5463x1_RST_GPIO_PORT, CS5463x1_RST_GPIO_PIN)      // CS5463x1 复位 GPIO输出高电平
    #define CS5463x1_RST_GPIO_Output_L()            GPIO_ResetBit(CS5463x1_RST_GPIO_PORT, CS5463x1_RST_GPIO_PIN)    // CS5463x1 复位 GPIO输出低电平

    #define CS5463x1_SPI_SendReciveByte(X)          SPIx4_SOFTWARE_SendReciveByte(X)        // CS5463x1 SPI总线 发送接收数据操作
    #define CS5463x1_SPI_ChipSelectEnable()         SPIx4_SOFTWARE_ChipSelect(0, 0)         // CS5463x1 SPI总线 使能片选有效
    #define CS5463x1_SPI_ChipSelectDisable()        SPIx4_SOFTWARE_ChipSelect(0, 1)         // CS5463x1 SPI总线 禁能片选无效

#endif  // #if (CS5463x1_WORKMODE == CS5463x1_WORKMODE_SPI_SOFTWARE)

//--------------------------------------------------------------------------------------------------
//  数据变量定义    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
typedef struct struct_CS5463x1_INFO
{
    float VoltageRMS;                       // 电压有效值 单位mV
    float VoltageNow;                       // 电压瞬时值 单位mV
    float VoltagePeak;                      // 电压峰峰值 单位mV
    
    float CurrentRMS;                       // 电流有效值 单位mA
    float CurrentNow;                       // 电流瞬时值 单位mA
    float CurrentPeak;                      // 电流峰峰值 单位mA
    
    float PowerNow;                         // 瞬时功率 单位uW
    float PowerActive;                      // 有功功率 单位uW
    float PowerReactive;                    // 无功功率值（用功率三角形计算） 单位uW
    float PowerApparent;                    // 视在功率值 单位mW
    
    float PowerReactiveNow;                 // 无功功率瞬时值（90°移相） 单位uW
    float PowerReactiveAverage;             // 无功功率平均值（90°移相） 单位uW
    
    float PowerActiveHarmonic;              // 谐波有功功率值 单位uW
    float PowerActiveFundamental;           // 基波有功功率值 单位uW
    float PowerReactiveFundamental;         // 基波无功功率值 单位uW
    
    float PowerFactor;                      // 功率因素
    float Frequency;                        // 交流频率  实际为50Hz
    float Temperature;                      // 温度 单位℃
} CS5463x1_t;

extern CS5463x1_t CS5463x1_Info;            // 引用外部变量

//--------------------------------------------------------------------------------------------------
//  函数调用声明    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//  CS5463x1 初始化 
void CS5463x1_Init(void);

//  CS5463x1 复位
void CS5463x1_Hardware_Reset(void);
void CS5463x1_Software_Reset(void);

//  CS5463x1 获取数值
float CS5463x1_GetVoltageRMS(void);                 // CS5463x1 获取 电压有效值
float CS5463x1_GetVoltageNow(void);                 // CS5463x1 获取 电压瞬时值
float CS5463x1_GetVoltagePeak(void);                // CS5463x1 获取 电压峰峰值
float CS5463x1_GetCurrentRMS(void);                 // CS5463x1 获取 电流有效值
float CS5463x1_GetCurrentNow(void);                 // CS5463x1 获取 电流有效值
float CS5463x1_GetCurrentPeak(void);                // CS5463x1 获取 电流峰峰值

float CS5463x1_GetPowerNow(void);                   // CS5463x1 获取 功率瞬时值
float CS5463x1_GetPowerActive(void);                // CS5463x1 获取 有功功率值
float CS5463x1_GetPowerReactive(void);              // CS5463x1 获取 无功功率值（用功率三角形计算）
float CS5463x1_GetPowerApparent(void);              // CS5463x1 获取 视在功率值

float CS5463x1_GetPowerReactiveNow(void);           // CS5463x1 获取 无功功率瞬时值（90°移相）
float CS5463x1_GetPowerReactiveAverage(void);       // CS5463x1 获取 无功功率平均值（90°移相）

float CS5463x1_GetPowerActiveHarmonic(void);        // CS5463x1 获取 谐波有功功率值
float CS5463x1_GetPowerActiveFundamental(void);     // CS5463x1 获取 基波有功功率值
float CS5463x1_GetPowerReactiveFundamental(void);   // CS5463x1 获取 基波无功功率值

float CS5463x1_GetPowerFactor(void);                // CS5463x1 获取 功率因素
float CS5463x1_GetFrequency(void);                  // CS5463x1 获取 交流频率
float CS5463x1_GetTemperature(void);                // CS5463x1 获取 温度

//  CS5463x1 获取数值
uint8_t CS5463x1_GetValue(void);

//  CS5463x1 EXTI 中断服务函数
void CS5463x1_EXTI_IRQHandler(void);

//  CS5463x1 测试
void CS5463x1_Test(void);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __CS5463x1_H__

//========================================== 文 件 结 束 ===========================================
