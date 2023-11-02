#include "Task_Date_pack.h"
/*
��Խ�Ϊ���ӵ�һ��ͨ�ų��������ܽᣬ��Ҫ���ͱ䳤������֡�������������ڴ˻����Ͻ��м򻯡�Ϊ�˷��ͱ䳤����֡��ʹ�� ֡ͷ+֡��+�����ֽ�+�����ֽ�+У���ֽ�+֡β �ĸ�ʽ�����ݰ����д������ʵ֡ͷ��֡���Ѿ��㹻���֡�������⣬֡β����ȥ����Ϊ����Ӧ�����ӵ���������ﱣ��֡β��

֡ͷ��ʹ�� 0xA5,0x5A�����ֽ���Ϊ֡ͷ��������λ0��1�ĸ�����ͬ���ֲ����Ȳ��׳���
֡������������֡ʵ�ʳ���ȷ��֡���ֽڣ�����ֻʹ��1���ֽڣ���֡���ֽ����Ϊ255,Ϊ��������ʣ��涨֡���ֽ��������������ֽڵĳ��ȣ���Ӧ��������Ϊ���ݳ����ֽڡ�
�����ֽڣ����������ֽ�ָ�������ֽڵĹ��ܣ����������ֽ�Ϊ1��ʾ�����¶ȣ�Ϊ2��ʾ����ʪ�ȵȣ�1�ֽ�����+n�ֽ������ǹ�ҵ�бȽϳ��õ�һ�ָ�ʽ�����Բ�ʹ��
�����ֽڣ������ֽڳ��ȿɱ䣬֡���ֽ�Ϊ0����ʾû�����ݣ�֡���ֽ�Ϊ255����ʾ��255�ֽ����ݡ�
У���ֽڣ��Ƚϼ򵥵�һ��У�鷽ʽΪ��У�飬����У���ֽ�ǰ�������ֽ���ͣ��������8λ��ΪУ���ֽڡ���MODBUSЭ���г���CRC16ѭ������У�鷽ʽ����У���ֽ�ǰ�������ֽڼ�����㣬�õ����ֽ�CRC16У���룬���ô˷�ʽ��
֡β����֡ͷ���ƣ�����ʹ��0xFF��Ϊ֡β��

֡ͷ		���ݳ���		����		����		CRC16У��	֡β
A5 5A		XX		 XX		��XX 		��XX XX		 FF
2�ֽ�		1�ֽ�		1�ֽ�		n�ֽ� ��		 2�ֽ�		1�ֽ�




*/
remote_data Remote_Data;

extern UART_HandleTypeDef huart1;

void SendByte(uint8_t date)
{
	uint8_t buffer[1];
	buffer[0] = date;	
	HAL_UART_Transmit( &huart1 , buffer , 1 ,100 );
	//HAL_UART_Transmit_DMA(&huart1,buffer,1);//dma ������
}


void Send(const uint8_t *data,uint8_t len)
{
	uint8_t i;
	for (i = 0; i < len; i++)
	{
		SendByte(data[i]);//����һ���ֽ�
	}
}


//16λѭ������У��
uint16_t CRC16_Check(const uint8_t *data,uint8_t len)
{
    uint16_t CRC16 = 0xFFFF;
    uint8_t state,i,j;
    for(i = 0; i < len; i++ )
    {
        CRC16 ^= data[i];
        for( j = 0; j < 8; j++)
        {
            state = CRC16 & 0x01;
            CRC16 >>= 1;
            if(state)
            {
                CRC16 ^= 0xA001;
            }
        }
    }
    return CRC16;
}



//�������ݰ�
void Send_Cmd_Data(uint8_t cmd,const uint8_t *datas,uint8_t len)
{
    uint8_t buf[300],i,cnt=0;
    uint16_t crc16;
    buf[cnt++] = 0xA5;
    buf[cnt++] = 0x5A;
    buf[cnt++] = len;
    buf[cnt++] = cmd;
    for(i=0;i<len;i++)
    {
        buf[cnt++] = datas[i];
    }
    crc16 = CRC16_Check(buf,len+4);
    buf[cnt++] = crc16>>8;
    buf[cnt++] = crc16&0xFF;
    buf[cnt++] = 0xFF;
    Send(buf,cnt);//��������֡���ͺ���������õ�����֡���ͳ�ȥ
}



//����֡����
void Data_Analysis(uint8_t cmd,const uint8_t *datas,uint8_t len)
{

	
	
}




//��������
void Receive(uint8_t bytedata)
{

	static uint8_t step=0;//״̬������ʼ��Ϊ0 �ں����б���Ϊ��̬����
	static uint8_t cnt=0,Buf[300],len,cmd,*data_ptr;
	static uint16_t crc16;
	//�������ݽ��� ״̬��
	switch(step)
	{
	    case 0://����֡ͷ1״̬
	        if(bytedata== 0xA5)
	        {
	            step++;
	            cnt = 0;
	            Buf[cnt++] = bytedata;
	        }break;
	    case 1://����֡ͷ2״̬
	        if(bytedata== 0x5A)
	        {
	            step++;
	            Buf[cnt++] = bytedata;
	        }
	        else if(bytedata== 0xA5)
	        {
	            step = 1;
	        }
	        else
	        {
	            step = 0;
	        }
	        break;
	    case 2://�������ݳ����ֽ�״̬
	        step++;
	        Buf[cnt++] = bytedata;
	        len = bytedata;
	        break;
	    case 3://���������ֽ�״̬
	        step++;
	        Buf[cnt++] = bytedata;
	        cmd = bytedata;
	        data_ptr = &Buf[cnt];//��¼����ָ���׵�ַ
	        if(len == 0)step++;//�����ֽڳ���Ϊ0���������ݽ���״̬
	        break;
	    case 4://����len�ֽ�����״̬
	        Buf[cnt++] = bytedata;
	        if(data_ptr + len == &Buf[cnt])//����ָ���ַƫ���ж��Ƿ������lenλ����
	        {
	            step++;
	        }
	        break;
	    case 5://����crc16У���8λ�ֽ�
	        step++;
	        crc16 = bytedata;
	        break;
	    case 6://����crc16У���8λ�ֽ�
	        crc16 <<= 8;
	        crc16 += bytedata;
	        if(crc16 == CRC16_Check(Buf,cnt))//У����ȷ������һ״̬
	        {
	            step ++;
	        }
	        else if(bytedata == 0xA5)
	        {
	            step = 1;
	        }
	        else
	        {
	            step = 0;
	        }
	        break;
	    case 7://����֡β
	        if(bytedata== 0xFF)//֡β������ȷ
	        {
	        	Data_Analysis(cmd,data_ptr,len);//���ݽ���
	            step = 0;
	        }
	        else if(bytedata == 0xA5)
	        {
	            step = 1;
	        }
	        else
	        {
	            step = 0;
	        }
	        break;
	    default:step=0;break;//����״̬����������²����ܳ���
	}
}







ch_transform th1;//����ת����������

extern key_data key1;
void Task_Date_pack(void const * argument)
{


 	
	while(1)
	{

		uint8_t Xmessage[12];
		for(int aree=0;aree<adc_channel_number;aree++)//ʹ��������     ��int16_tת��λuint8_t
		{
			th1.ch[aree]=Remote_Data.ch[aree] ;
			for(int artt=0;artt<2;artt++)
			{
				Xmessage[aree*2+artt]=th1.ch_port[aree*2+artt];

			}
		}

			Xmessage[5] = key1.pData2[0];
			Xmessage[6] =key1.pData2[1];
			
		Send_Cmd_Data(Remote_Data.cmd,Xmessage,12);
		osDelay(30);
		
	}
}























