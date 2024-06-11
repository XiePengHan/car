#include "zf_common_headfile.h"
#include "mpu6050_dmp.h"


#define SDA             gpio_get_level (SEEKFREE_SDA)
#define SDA0()          gpio_set_level (SEEKFREE_SDA, 0)		//IO������͵�ƽ
#define SDA1()          gpio_set_level (SEEKFREE_SDA, 1)		//IO������ߵ�ƽ  
#define SCL0()          gpio_set_level (SEEKFREE_SCL, 0)		//IO������͵�ƽ
#define SCL1()          gpio_set_level (SEEKFREE_SCL, 1)		//IO������ߵ�ƽ
#define DIR_OUT()       gpio_set_dir (SEEKFREE_SDA, GPO, GPO_PUSH_PULL)   //�������
#define DIR_IN()        gpio_set_dir (SEEKFREE_SDA, GPI, GPO_OPEN_DTAIN)    //���뷽��


#define MPU_ADDR 0x68

 //�ڲ����ݶ���
uint8 IIC_ad_main; //�����ӵ�ַ	    
uint8 IIC_ad_sub;  //�����ӵ�ַ	   
uint8* IIC_buf;    //����|�������ݻ�����	    
uint8 IIC_num;     //����|�������ݸ���	     

#define ack 1      //��Ӧ��
#define no_ack 0   //��Ӧ��	 



uint16 simiic_delay_time = SIMIIC_DELAY_TIME;   //ICM�ȴ�����Ӧ����Ϊ20


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC��ʱ ʱ������
//  @return     void						
//  @since      v1.0
//  Sample usage:				���IICͨѶʧ�ܿ��Գ�������simiic_delay_time��ֵ
//-------------------------------------------------------------------------------------------------------------------
void simiic_delay_set(uint16 time)
{
    simiic_delay_time = time;           //ICM�ȴ�����Ӧ����Ϊ100
}
//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC��ʱ
//  @return     void						
//  @since      v1.0
//  Sample usage:				���IICͨѶʧ�ܿ��Գ�������simiic_delay_time��ֵ
//-------------------------------------------------------------------------------------------------------------------
void simiic_delay(void)
{
    uint16 delay_time;
    delay_time = simiic_delay_time;
    while (delay_time--);
}


//�ڲ�ʹ�ã��û��������
void simiic_start(void)
{
    SDA1();
    SCL1();
    simiic_delay();
    SDA0();
    simiic_delay();
    SCL0();
    simiic_delay();
}

//�ڲ�ʹ�ã��û��������
void simiic_stop(void)
{
    SDA0();
    SCL0();
    simiic_delay();
    SCL1();
    simiic_delay();
    SDA1();
    simiic_delay();
}

//��Ӧ��(����ack:SDA=0��no_ack:SDA=0)
//�ڲ�ʹ�ã��û��������
void simiic_sendack(unsigned char ack_dat)
{
    SCL0();
    simiic_delay();
    if (ack_dat) SDA0();
    else    	SDA1();

    SCL1();
    simiic_delay();
    SCL0();
    simiic_delay();
}


static int sccb_waitack(void)
{
    SCL0();
    DIR_IN();
    simiic_delay();

    SCL1();
    simiic_delay();

    if (SDA)           //Ӧ��Ϊ�ߵ�ƽ���쳣��ͨ��ʧ��
    {
        DIR_OUT();
        SCL0();
        return 1;
    }
    DIR_OUT();
    SCL0();
    simiic_delay();
    return 0;
}

//�ֽڷ��ͳ���
//����c(����������Ҳ���ǵ�ַ)���������մ�Ӧ��
//�����Ǵ�Ӧ��λ
//�ڲ�ʹ�ã��û��������
void send_ch(uint8 c)
{
    uint8 i = 8;
    while (i--)
    {
        if (c & 0x80)	SDA1();//SDA �������
        else			SDA0();
        c <<= 1;
        simiic_delay();
        SCL1();                //SCL ���ߣ��ɼ��ź�
        simiic_delay();
        SCL0();                //SCL ʱ��������
    }
    //sccb_waitack();
}

//�ֽڽ��ճ���
//�����������������ݣ��˳���Ӧ���|��Ӧ����|ʹ��
//�ڲ�ʹ�ã��û��������
uint8 read_ch(uint8 ack_x)
{
    uint8 i;
    uint8 c;
    c = 0;
    SCL0();
    simiic_delay();
    SDA1();
    DIR_IN();           //��������Ϊ���뷽ʽ
    for (i = 0;i < 8;i++)
    {
        simiic_delay();
        SCL0();         //��ʱ����Ϊ�ͣ�׼����������λ
        simiic_delay();
        SCL1();         //��ʱ����Ϊ�ߣ�ʹ��������������Ч
        simiic_delay();
        c <<= 1;
        if (SDA)
        {
            c += 1;   //������λ�������յ����ݴ�c
        }
    }
    DIR_OUT();
    SCL0();
    simiic_delay();
    simiic_sendack(ack_x);

    return c;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IICд���ݵ��豸�Ĵ�������
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      reg				�Ĵ�����ַ
//  @param      dat				д�������
//  @return     void						
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void simiic_write_reg(uint8 dev_add, uint8 reg, uint8 dat)
{
    simiic_start();
    send_ch((dev_add << 1) | 0x00);   //����������ַ��дλ
    send_ch(reg);   				 //���ʹӻ��Ĵ�����ַ
    send_ch(dat);   				 //������Ҫд�������
    simiic_stop();
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC���豸�Ĵ�����ȡ����
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      reg				�Ĵ�����ַ
//  @param      type			ѡ��ͨ�ŷ�ʽ��IIC  ���� SCCB
//  @return     uint8			���ؼĴ���������			
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
uint8 simiic_read_reg(uint8 dev_add, uint8 reg, IIC_type type)
{
    uint8 dat = 0;
    simiic_start();
    send_ch((dev_add << 1) | 0x00);  //����������ַ��дλ
    send_ch(reg);   				//���ʹӻ��Ĵ�����ַ
    if (type == SCCB)simiic_stop();

    simiic_start();
    send_ch((dev_add << 1) | 0x01);  //����������ַ�Ӷ�λ
    dat = read_ch(ack);   				//��ȡ����
    simiic_stop();

    return dat;
}

//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC��ȡ���ֽ�����
//  @param      dev_add			�豸��ַ(����λ��ַ)
//  @param      reg				�Ĵ�����ַ
//  @param      dat_add			���ݱ���ĵ�ַָ��
//  @param      num				��ȡ�ֽ�����
//  @param      type			ѡ��ͨ�ŷ�ʽ��IIC  ���� SCCB
//  @return     uint8			���ؼĴ���������			
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void simiic_read_regs(uint8 dev_add, uint8 reg, uint8* dat_add, uint8 num, IIC_type type)
{
    simiic_start();
    send_ch((dev_add << 1) | 0x00);  //����������ַ��дλ
    send_ch(reg);   				//���ʹӻ��Ĵ�����ַ
    if (type == SCCB)simiic_stop();

    simiic_start();
    send_ch((dev_add << 1) | 0x01);  //����������ַ�Ӷ�λ
    while (num--)
    {
        *dat_add = read_ch(no_ack); //��ȡ����
        dat_add++;
    }
    //*dat_add = read_ch(no_ack); //��ȡ����
    simiic_stop();
}


//-------------------------------------------------------------------------------------------------------------------
//  @brief      ģ��IIC�˿ڳ�ʼ��
//  @param      NULL
//  @return     void	
//  @since      v1.0
//  Sample usage:				
//-------------------------------------------------------------------------------------------------------------------
void simiic_init(void)
{
    gpio_init(SEEKFREE_SCL, GPO, 1, GPO_PUSH_PULL);
    gpio_init(SEEKFREE_SDA, GPO, 1, GPO_OPEN_DTAIN);
}
//IIC����д
//addr:������ַ
//reg: �Ĵ�����ַ
//len: д�볤��
//buf: ������
//����ֵ: 0,����
//              �������������
uint8_t MPU_Write_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t* buf)
{
    uint8_t i;
    simiic_start();
    send_ch((addr << 1) | 0);//����������ַ+д����
    if (sccb_waitack())//�ȴ�Ӧ��
    {
        simiic_stop();
        return 1;
    }
    send_ch(reg);//д�Ĵ�����ַ
    sccb_waitack();//�ȴ�Ӧ��
    for (i = 0;i < len;i++)
    {
        send_ch(buf[i]);//��������
        if (sccb_waitack())//�ȴ�ACK
        {
            simiic_stop();
            return 1;
        }
    }
    simiic_stop();
    return 0;
}
//IIC������
//addr:������ַ
//reg:Ҫ��ȡ�ļĴ�����ַ
//len:Ҫ��ȡ�ó���
//buf:��ȡ�������ݴ洢��
//����ֵ: 0,����
//              �������������
uint8_t MPU_Read_Len(uint8_t addr, uint8_t reg, uint8_t len, uint8_t* buf)
{
    simiic_start();
    send_ch((addr << 1) | 0);//����������ַ+д����
    if (sccb_waitack())//�ȴ�Ӧ��
    {
        simiic_stop();
        return 1;
    }
    send_ch(reg);//д�Ĵ�����ַ
    sccb_waitack();//�ȴ�Ӧ��
    simiic_start();
    send_ch((addr << 1) | 1);//����������ַ+������
    sccb_waitack();//�ȴ�Ӧ��
    while (len)
    {
        if (len == 1) *buf = read_ch(0);//�����ݣ�����nACK
        else *buf = read_ch(1);//�����ݣ�����ACK
        len--;
        buf++;
    }
    simiic_stop();//����һ��ֹͣ����
    return 0;
}

//IICдһ���ֽ�
//reg:      �Ĵ�����ַ
//data:     ����
//����ֵ:  0,����
//          ����,�������
uint8_t MPU_Write_Byte(uint8_t reg, uint8_t data)
{
    simiic_start();
    send_ch((MPU_ADDR << 1) | 0);//����������ַ+д����
    if (sccb_waitack())  //�ȴ�Ӧ��
    {
        simiic_stop();
        return 1;
    }
    send_ch(reg); //д�Ĵ�����ַ
    sccb_waitack();     //�ȴ�Ӧ��
    send_ch(data);//��������
    if (sccb_waitack())  //�ȴ�ACK
    {
        simiic_stop();
        return 1;
    }
    simiic_stop();
    return 0;
}

//IIC��һ���ֽ�
//reg:�Ĵ�����ַ
//����ֵ:����������
uint8_t MPU_Read_Byte(uint8_t reg)
{
    uint8_t res;
    simiic_start();
    send_ch((MPU_ADDR << 1) | 0);//����������ַ+д����
    sccb_waitack();//�ȴ�Ӧ��
    send_ch(reg);//д�Ĵ�����ַ
    sccb_waitack();//�ȴ�Ӧ��
    simiic_start();
    send_ch((MPU_ADDR << 1) | 1);//�����ڼ��ַ+������
    sccb_waitack();//�ȴ�Ӧ��
    res = read_ch(0);//��ȡ���ݣ�����nACK
    simiic_stop();//����һ��ֹͣ����
    return res;
}
