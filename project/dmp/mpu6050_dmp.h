/*********************************************************************************************************************
 * COPYRIGHT NOTICE
 * Copyright (c) 2020,��ɿƼ�
 * All rights reserved.
 * ��������QQȺ����Ⱥ��824575535
 *
 * �����������ݰ�Ȩ������ɿƼ����У�δ��������������ҵ��;��
 * ��ӭ��λʹ�ò������������޸�����ʱ���뱣����ɿƼ��İ�Ȩ������
 *
 * @file       		ģ��IIC
 * @company	   		�ɶ���ɿƼ����޹�˾
 * @author     		��ɿƼ�(QQ3184284598)
 * @version    		�鿴doc��version�ļ� �汾˵��
 * @Software 		ADS v1.2.2
 * @Target core		TC364DP
 * @Taobao   		https://seekfree.taobao.com/
 * @date       		2020-11-23
 * @note
					���߶��壺
					------------------------------------
						SCL                 �鿴SEEKFREE_IIC�ļ��ڵ�SEEKFREE_SCL�궨��
						SDA                 �鿴SEEKFREE_IIC�ļ��ڵ�SEEKFREE_SDA�궨��
					------------------------------------
 ********************************************************************************************************************/



#ifndef _SEEKFREE_IIC_h
#define _SEEKFREE_IIC_h


#include "zf_common_headfile.h"




#define SEEKFREE_SCL    P15_2                          //����SCL����  ���������Ϊ����IO
#define SEEKFREE_SDA    P15_1                          //����SDA����  ���������Ϊ����IO


#define SIMIIC_DELAY_TIME	20


typedef enum IIC       //IIC����ö��
{
	SIMIIC,
	SCCB
} IIC_type;

extern uint16 simiic_delay_time;   //ICM�ȴ�����Ӧ����Ϊ20

void  simiic_delay_set(uint16 time);
void  simiic_start(void);
void  simiic_stop(void);
void  simiic_ack_main(uint8 ack_main);
void  send_ch(uint8 c);
uint8 read_ch(uint8 ack);
void  simiic_write_reg(uint8 dev_add, uint8 reg, uint8 dat);
uint8 simiic_read_reg(uint8 dev_add, uint8 reg, IIC_type type);
void  simiic_read_regs(uint8 dev_add, uint8 reg, uint8* dat_add, uint8 num, IIC_type type);
void  simiic_init(void);
uint8_t MPU_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t* buf);
uint8_t MPU_Write_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t* buf);
uint8_t MPU_Write_Byte(uint8_t reg, uint8_t data);
uint8_t MPU_Read_Byte(uint8_t reg);








#endif

