//==================================================================================================
//  �ļ�����: CS5463x1.h
//  �ļ�����: CS5463x1-1·����˫����/����оƬ
//  �ļ�˵��: �����220V��ʾ ��ЧֵΪ220V ���ֵΪ311V
//            RMS��ʾ��Чֵ
//            1V = 1000mV = 1000*1000uV
//            1A = 1000mA = 1000*1000uA
//            1W = 1000mW = 1000*1000uW
//  �ļ�����: Board-�����豸��������
//==================================================================================================

#ifndef __CS5463x1_H__
#define __CS5463x1_H__

#ifdef __cplusplus
extern "C" {
#endif  // #ifdef __cplusplus

//--------------------------------------------------------------------------------------------------
//  ���Զ�������    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#define CS5463x1_STATE_SUCCESS              (0)             // CS5463x1״̬ �ɹ�״̬
#define CS5463x1_STATE_FAILURE              (1)             // CS5463x1״̬ ʧ��״̬
#define CS5463x1_STATE_UNKNOWN              (2)             // CS5463x1״̬ δ֪״̬
    
//  CS5463x1 ����ģʽ
#define CS5463x1_WORKMODE_SPI_HARDWARE      (0)             // CS5463x1����ģʽ SPI_HARDWARE - SPI����Ӳ������
#define CS5463x1_WORKMODE_SPI_SOFTWARE      (1)             // CS5463x1����ģʽ SPI_SOFTWARE - SPI�������ģ��
#define CS5463x1_WORKMODE                   CS5463x1_WORKMODE_SPI_HARDWARE          // SPI����Ӳ������

// - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
//  CS5463x1 ��������
//  ��ѹ��������˵����
//  ������Χ��·����Ĭ��220V ʹ��220K��+ZMPT107��ѹ��������2mA:2mA�� ʹ��110����������
//  �� (220V/220K��) * (2mA/2mA) * 110�� = 110mV ����С��CS5463x1��ѹ����
//  CS5463x1��ѹ��������Ϊ250mV����û������������������£�
//  CS5463x1��ѹ�������Ϊ0.0~1.0��Χ��VData��ֵ
//  ��������� ��ѹ��Чֵ = VData * 250mV / 110�� * (2mA/2mA) * 220K��;
//                        = VData * 500;        (��λΪV)
//                        = VData * 500 * 1000; (��λΪmV)
#define CS5463x1_FUNCTION_VScale            (500000)        // CS5463x1 �����ѹ����

//  ������������˵����
//  ������Χ��·�������10A ʹ��ZMCT102A������������5A:2.5mA�� ʹ��10����������
//  �� 10A * (2.5mA/5A) * 10�� = 50mV ����С��CS5463x1��������
//  CS5463x1������������Ϊ250mV����û������������������£�
//  CS5463x1�����������Ϊ0.0~1.0��Χ��VData��ֵ
//  ��������� ������Чֵ = VData * 250mV / 10�� * (5A/2.5mA);
//                        = VData * 50000; ����λΪMA��
#define CS5463x1_FUNCTION_IScale            (50000)         // CS5463x1 �����������

//--------------------------------------------------------------------------------------------------
//  �˿����Ŷ���    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
#if (CS5463x1_WORKMODE == CS5463x1_WORKMODE_SPI_HARDWARE)   // SPI����Ӳ������

    #define CS5463x1_RST_GPIO_PORT                  (GPIOxC)        // CS5463x1 ��λ GPIO�˿�
    #define CS5463x1_RST_GPIO_PIN                   (GPIOc1)        // CS5463x1 ��λ GPIO����

    #define CS5463x1_IRQ_GPIO_PORT                  (GPIOxC)        // CS5463x1 �ⲿ�ж� GPIO�˿�
    #define CS5463x1_IRQ_GPIO_PIN                   (GPIOc2)        // CS5463x1 �ⲿ�ж� GPIO����
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    #define CS5463x1_RST_GPIO_Output_H()            GPIO_SetBit(CS5463x1_RST_GPIO_PORT, CS5463x1_RST_GPIO_PIN)      // CS5463x1 ��λ GPIO����ߵ�ƽ
    #define CS5463x1_RST_GPIO_Output_L()            GPIO_ResetBit(CS5463x1_RST_GPIO_PORT, CS5463x1_RST_GPIO_PIN)    // CS5463x1 ��λ GPIO����͵�ƽ

    #define CS5463x1_SPI_SendReciveByte(X)          SPIx2_HARDWARE_SendReciveByte(X)        // CS5463x1 SPI���� ���ͽ������ݲ���
    #define CS5463x1_SPI_ChipSelectEnable()         SPIx2_HARDWARE_ChipSelect(1, 0)         // CS5463x1 SPI���� ʹ��Ƭѡ��Ч
    #define CS5463x1_SPI_ChipSelectDisable()        SPIx2_HARDWARE_ChipSelect(1, 1)         // CS5463x1 SPI���� ����Ƭѡ��Ч

#endif  // #if (CS5463x1_WORKMODE == CS5463x1_WORKMODE_SPI_HARDWARE)

//-- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
#if (CS5463x1_WORKMODE == CS5463x1_WORKMODE_SPI_SOFTWARE)   // SPI�������ģ��

    #define CS5463x1_RST_GPIO_PORT                  (GPIOxC)        // CS5463x1 ��λ GPIO�˿�
    #define CS5463x1_RST_GPIO_PIN                   (GPIOc1)        // CS5463x1 ��λ GPIO����

    #define CS5463x1_IRQ_GPIO_PORT                  (GPIOxC)        // CS5463x1 �ⲿ�ж� GPIO�˿�
    #define CS5463x1_IRQ_GPIO_PIN                   (GPIOc2)        // CS5463x1 �ⲿ�ж� GPIO����
    // - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
    #define CS5463x1_RST_GPIO_Output_H()            GPIO_SetBit(CS5463x1_RST_GPIO_PORT, CS5463x1_RST_GPIO_PIN)      // CS5463x1 ��λ GPIO����ߵ�ƽ
    #define CS5463x1_RST_GPIO_Output_L()            GPIO_ResetBit(CS5463x1_RST_GPIO_PORT, CS5463x1_RST_GPIO_PIN)    // CS5463x1 ��λ GPIO����͵�ƽ

    #define CS5463x1_SPI_SendReciveByte(X)          SPIx4_SOFTWARE_SendReciveByte(X)        // CS5463x1 SPI���� ���ͽ������ݲ���
    #define CS5463x1_SPI_ChipSelectEnable()         SPIx4_SOFTWARE_ChipSelect(0, 0)         // CS5463x1 SPI���� ʹ��Ƭѡ��Ч
    #define CS5463x1_SPI_ChipSelectDisable()        SPIx4_SOFTWARE_ChipSelect(0, 1)         // CS5463x1 SPI���� ����Ƭѡ��Ч

#endif  // #if (CS5463x1_WORKMODE == CS5463x1_WORKMODE_SPI_SOFTWARE)

//--------------------------------------------------------------------------------------------------
//  ���ݱ�������    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
typedef struct struct_CS5463x1_INFO
{
    float VoltageRMS;                       // ��ѹ��Чֵ ��λmV
    float VoltageNow;                       // ��ѹ˲ʱֵ ��λmV
    float VoltagePeak;                      // ��ѹ���ֵ ��λmV
    
    float CurrentRMS;                       // ������Чֵ ��λmA
    float CurrentNow;                       // ����˲ʱֵ ��λmA
    float CurrentPeak;                      // �������ֵ ��λmA
    
    float PowerNow;                         // ˲ʱ���� ��λuW
    float PowerActive;                      // �й����� ��λuW
    float PowerReactive;                    // �޹�����ֵ���ù��������μ��㣩 ��λuW
    float PowerApparent;                    // ���ڹ���ֵ ��λmW
    
    float PowerReactiveNow;                 // �޹�����˲ʱֵ��90�����ࣩ ��λuW
    float PowerReactiveAverage;             // �޹�����ƽ��ֵ��90�����ࣩ ��λuW
    
    float PowerActiveHarmonic;              // г���й�����ֵ ��λuW
    float PowerActiveFundamental;           // �����й�����ֵ ��λuW
    float PowerReactiveFundamental;         // �����޹�����ֵ ��λuW
    
    float PowerFactor;                      // ��������
    float Frequency;                        // ����Ƶ��  ʵ��Ϊ50Hz
    float Temperature;                      // �¶� ��λ��
} CS5463x1_t;

extern CS5463x1_t CS5463x1_Info;            // �����ⲿ����

//--------------------------------------------------------------------------------------------------
//  ������������    |   0   |   1   |   2   |   3   |   4   |   5   |   6   |   7   |   8   |   9   
//--------------------------------------------------------------------------------------------------
//  CS5463x1 ��ʼ�� 
void CS5463x1_Init(void);

//  CS5463x1 ��λ
void CS5463x1_Hardware_Reset(void);
void CS5463x1_Software_Reset(void);

//  CS5463x1 ��ȡ��ֵ
float CS5463x1_GetVoltageRMS(void);                 // CS5463x1 ��ȡ ��ѹ��Чֵ
float CS5463x1_GetVoltageNow(void);                 // CS5463x1 ��ȡ ��ѹ˲ʱֵ
float CS5463x1_GetVoltagePeak(void);                // CS5463x1 ��ȡ ��ѹ���ֵ
float CS5463x1_GetCurrentRMS(void);                 // CS5463x1 ��ȡ ������Чֵ
float CS5463x1_GetCurrentNow(void);                 // CS5463x1 ��ȡ ������Чֵ
float CS5463x1_GetCurrentPeak(void);                // CS5463x1 ��ȡ �������ֵ

float CS5463x1_GetPowerNow(void);                   // CS5463x1 ��ȡ ����˲ʱֵ
float CS5463x1_GetPowerActive(void);                // CS5463x1 ��ȡ �й�����ֵ
float CS5463x1_GetPowerReactive(void);              // CS5463x1 ��ȡ �޹�����ֵ���ù��������μ��㣩
float CS5463x1_GetPowerApparent(void);              // CS5463x1 ��ȡ ���ڹ���ֵ

float CS5463x1_GetPowerReactiveNow(void);           // CS5463x1 ��ȡ �޹�����˲ʱֵ��90�����ࣩ
float CS5463x1_GetPowerReactiveAverage(void);       // CS5463x1 ��ȡ �޹�����ƽ��ֵ��90�����ࣩ

float CS5463x1_GetPowerActiveHarmonic(void);        // CS5463x1 ��ȡ г���й�����ֵ
float CS5463x1_GetPowerActiveFundamental(void);     // CS5463x1 ��ȡ �����й�����ֵ
float CS5463x1_GetPowerReactiveFundamental(void);   // CS5463x1 ��ȡ �����޹�����ֵ

float CS5463x1_GetPowerFactor(void);                // CS5463x1 ��ȡ ��������
float CS5463x1_GetFrequency(void);                  // CS5463x1 ��ȡ ����Ƶ��
float CS5463x1_GetTemperature(void);                // CS5463x1 ��ȡ �¶�

//  CS5463x1 ��ȡ��ֵ
uint8_t CS5463x1_GetValue(void);

//  CS5463x1 EXTI �жϷ�����
void CS5463x1_EXTI_IRQHandler(void);

//  CS5463x1 ����
void CS5463x1_Test(void);

#ifdef __cplusplus
}
#endif  // #ifdef __cplusplus

#endif  // #ifndef __CS5463x1_H__

//========================================== �� �� �� �� ===========================================
