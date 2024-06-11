#include "zf_common_headfile.h"
#include "key.h"

unsigned short ADC_data1[2050];
unsigned short ADC_data2[2050];
unsigned short ADC_data3[2050];
unsigned short ADC_data4[2050];
uint16 data1_number;
uint16 data2_number;
uint16 data3_number;
uint16 data4_number;
bool flag_ADC_1;
bool flag_ADC_2;
bool flag_ADC_3;
bool flag_ADC_4;
bool flag_ADC;

// **************************** PIT�жϺ��� ****************************
void pit0_ch0_isr()                     // ��ʱ��ͨ�� 0 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH0);
  
    ADC_data3[data3_number] = adc_convert(ADC1_CH15_P13_3);
    data3_number++;
    if (data3_number > 2048)
    {
      data3_number= 0;
      flag_ADC_3 = 1;
    }
    
    ADC_data4[data4_number] = adc_convert(ADC1_CH16_P13_4);
    data4_number++;
    if (data4_number > 2048)
    {
      data4_number= 0;
      flag_ADC_4 = 1;
    }
}

void pit0_ch1_isr()                     // ��ʱ��ͨ�� 1 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH1);
    
    ADC_data1[data1_number] = adc_convert(ADC1_CH13_P13_1);
    data1_number++;
    if (data1_number > 2048)
    {
      data1_number= 0;
      flag_ADC_1 = 1;
    }
    ADC_data2[data2_number] = adc_convert(ADC1_CH14_P13_2);
    data2_number++;
    if (data2_number > 2048)
    {
      data2_number= 0;
      flag_ADC_2 = 1;
    }
}

void pit0_ch2_isr()                     // ��ʱ��ͨ�� 2 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH2);
    
    if (flag_ADC_1 && flag_ADC_2 && flag_ADC_3 && flag_ADC_4)
    {
      flag_ADC = 1;
    }
}

void pit0_ch10_isr()                    // ��ʱ��ͨ�� 10 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH10);
    
    KEY_Scanf();
}

void pit0_ch11_isr()                    // ��ʱ��ͨ�� 11 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH11);
}

void pit0_ch12_isr()                    // ��ʱ��ͨ�� 12 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH12);
    
}

void pit0_ch13_isr()                    // ��ʱ��ͨ�� 13 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH13);
    
}

void pit0_ch14_isr()                    // ��ʱ��ͨ�� 14 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH14);
    
}

void pit0_ch15_isr()                    // ��ʱ��ͨ�� 15 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH15);
    
}

void pit0_ch16_isr()                    // ��ʱ��ͨ�� 16 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH16);
    
}

void pit0_ch17_isr()                    // ��ʱ��ͨ�� 17 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH17);
    
}

void pit0_ch18_isr()                    // ��ʱ��ͨ�� 18 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH18);
    
}

void pit0_ch19_isr()                    // ��ʱ��ͨ�� 19 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH19);
    
}

void pit0_ch20_isr()                    // ��ʱ��ͨ�� 20 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH20);
    
}

void pit0_ch21_isr()                    // ��ʱ��ͨ�� 21 �����жϷ�����      
{
    pit_isr_flag_clear(PIT_CH21);
    
}
// **************************** PIT�жϺ��� ****************************


// **************************** �ⲿ�жϺ��� ****************************
void gpio_0_exti_isr()                  // �ⲿ GPIO_0 �жϷ�����     
{
    
  
  
}

void gpio_1_exti_isr()                  // �ⲿ GPIO_1 �жϷ�����     
{
    if(exti_flag_get(P01_0))		// ʾ��P1_0�˿��ⲿ�ж��ж�
    {

      
      
            
    }
    if(exti_flag_get(P01_1))
    {

            
            
    }
}

void gpio_2_exti_isr()                  // �ⲿ GPIO_2 �жϷ�����     
{
    if(exti_flag_get(P02_0))
    {
            
            
    }
    if(exti_flag_get(P02_4))
    {
            
            
    }

}

void gpio_3_exti_isr()                  // �ⲿ GPIO_3 �жϷ�����     
{



}

void gpio_4_exti_isr()                  // �ⲿ GPIO_4 �жϷ�����     
{



}

void gpio_5_exti_isr()                  // �ⲿ GPIO_5 �жϷ�����     
{



}

void gpio_6_exti_isr()                  // �ⲿ GPIO_6 �жϷ�����     
{
	


}

void gpio_7_exti_isr()                  // �ⲿ GPIO_7 �жϷ�����     
{



}

void gpio_8_exti_isr()                  // �ⲿ GPIO_8 �жϷ�����     
{



}

void gpio_9_exti_isr()                  // �ⲿ GPIO_9 �жϷ�����     
{



}

void gpio_10_exti_isr()                  // �ⲿ GPIO_10 �жϷ�����     
{



}

void gpio_11_exti_isr()                  // �ⲿ GPIO_11 �жϷ�����     
{



}

void gpio_12_exti_isr()                  // �ⲿ GPIO_12 �жϷ�����     
{



}

void gpio_13_exti_isr()                  // �ⲿ GPIO_13 �жϷ�����     
{



}

void gpio_14_exti_isr()                  // �ⲿ GPIO_14 �жϷ�����     
{



}

void gpio_15_exti_isr()                  // �ⲿ GPIO_15 �жϷ�����     
{



}

void gpio_16_exti_isr()                  // �ⲿ GPIO_16 �жϷ�����     
{



}

void gpio_17_exti_isr()                  // �ⲿ GPIO_17 �жϷ�����     
{



}

void gpio_18_exti_isr()                  // �ⲿ GPIO_18 �жϷ�����     
{



}

void gpio_19_exti_isr()                  // �ⲿ GPIO_19 �жϷ�����     
{



}

void gpio_20_exti_isr()                  // �ⲿ GPIO_20 �жϷ�����     
{



}

void gpio_21_exti_isr()                  // �ⲿ GPIO_21 �жϷ�����     
{



}

void gpio_22_exti_isr()                  // �ⲿ GPIO_22 �жϷ�����     
{



}

void gpio_23_exti_isr()                  // �ⲿ GPIO_23 �жϷ�����     
{



}
// **************************** �ⲿ�жϺ��� ****************************

//// **************************** DMA�жϺ��� ****************************
//void dma_event_callback(void* callback_arg, cyhal_dma_event_t event)
//{
//    CY_UNUSED_PARAMETER(event);
//	
//
//	
//	
//}
// **************************** DMA�жϺ��� ****************************
void uart_double_interrupt_handler (void);
void uart_gps_interrupt_handler (void);
// **************************** �����жϺ��� ****************************
// ����0Ĭ����Ϊ���Դ���
void uart0_isr (void)
{
    if(Cy_SCB_GetRxInterruptMask(get_scb_module(UART_0)) & CY_SCB_UART_RX_NOT_EMPTY)            // ����0�����ж�
    {
        Cy_SCB_ClearRxInterrupt(get_scb_module(UART_0), CY_SCB_UART_RX_NOT_EMPTY);              // ��������жϱ�־λ
        
#if DEBUG_UART_USE_INTERRUPT                        				                // ������� debug �����ж�
        debug_interrupr_handler();                  				                // ���� debug ���ڽ��մ����� ���ݻᱻ debug ���λ�������ȡ
#endif                                              				                // ����޸��� DEBUG_UART_INDEX ����δ�����Ҫ�ŵ���Ӧ�Ĵ����ж�ȥ
      
        
        
    }
    else if(Cy_SCB_GetTxInterruptMask(get_scb_module(UART_0)) & CY_SCB_UART_TX_DONE)            // ����0�����ж�
    {           
        Cy_SCB_ClearTxInterrupt(get_scb_module(UART_0), CY_SCB_UART_TX_DONE);                   // ��������жϱ�־λ
        
        
        
    }
}

void uart1_isr (void)
{
    if(Cy_SCB_GetRxInterruptMask(get_scb_module(UART_1)) & CY_SCB_UART_RX_NOT_EMPTY)            // ����1�����ж�
    {
        Cy_SCB_ClearRxInterrupt(get_scb_module(UART_1), CY_SCB_UART_RX_NOT_EMPTY);              // ��������жϱ�־λ

        uart_double_interrupt_handler();
    }
    else if(Cy_SCB_GetTxInterruptMask(get_scb_module(UART_1)) & CY_SCB_UART_TX_DONE)            // ����1�����ж�
    {
        Cy_SCB_ClearTxInterrupt(get_scb_module(UART_1), CY_SCB_UART_TX_DONE);                   // ��������жϱ�־λ
        
        
        
    }
}

void uart2_isr (void)
{
    if(Cy_SCB_GetRxInterruptMask(get_scb_module(UART_2)) & CY_SCB_UART_RX_NOT_EMPTY)            // ����2�����ж�
    {
        Cy_SCB_ClearRxInterrupt(get_scb_module(UART_2), CY_SCB_UART_RX_NOT_EMPTY);              // ��������жϱ�־λ

        uart_gps_interrupt_handler();
        
        
    }
    else if(Cy_SCB_GetTxInterruptMask(get_scb_module(UART_2)) & CY_SCB_UART_TX_DONE)            // ����2�����ж�
    {
        Cy_SCB_ClearTxInterrupt(get_scb_module(UART_2), CY_SCB_UART_TX_DONE);                   // ��������жϱ�־λ
        
        
        
    }
}

void uart3_isr (void)
{
    if(Cy_SCB_GetRxInterruptMask(get_scb_module(UART_3)) & CY_SCB_UART_RX_NOT_EMPTY)            // ����3�����ж�
    {
        Cy_SCB_ClearRxInterrupt(get_scb_module(UART_3), CY_SCB_UART_RX_NOT_EMPTY);              // ��������жϱ�־λ

        
        
        
    }
    else if(Cy_SCB_GetTxInterruptMask(get_scb_module(UART_3)) & CY_SCB_UART_TX_DONE)            // ����3�����ж�
    {
        Cy_SCB_ClearTxInterrupt(get_scb_module(UART_3), CY_SCB_UART_TX_DONE);                   // ��������жϱ�־λ
        
        
        
    }
}

void uart4_isr (void)
{
    
    if(Cy_SCB_GetRxInterruptMask(get_scb_module(UART_4)) & CY_SCB_UART_RX_NOT_EMPTY)            // ����4�����ж�
    {
        Cy_SCB_ClearRxInterrupt(get_scb_module(UART_4), CY_SCB_UART_RX_NOT_EMPTY);              // ��������жϱ�־λ

        
        uart_receiver_handler();                                                                // ���ڽ��ջ��ص�����
        
        
    }
    else if(Cy_SCB_GetTxInterruptMask(get_scb_module(UART_4)) & CY_SCB_UART_TX_DONE)            // ����4�����ж�
    {
        Cy_SCB_ClearTxInterrupt(get_scb_module(UART_4), CY_SCB_UART_TX_DONE);                   // ��������жϱ�־λ
        
        
        
    }
}
// **************************** �����жϺ��� ****************************