#include "Task_Date_pack.h"
/*
针对较为复杂的一种通信场景进行总结，需要发送变长的数据帧。其他场景可在此基础上进行简化。为了发送变长数据帧，使用 帧头+帧长+命令字节+数据字节+校验字节+帧尾 的格式对数据包进行打包，其实帧头和帧长已经足够解决帧对齐问题，帧尾可以去掉，为了适应更复杂的情况，这里保留帧尾。

帧头：使用 0xA5,0x5A两个字节作为帧头，二进制位0与1的个数相同，分布均匀不易出错。
帧长：根据数据帧实际长度确定帧长字节，这里只使用1个字节，故帧长字节最大为255,为提高利用率，规定帧长字节描述的是数据字节的长度，故应重新命名为数据长度字节。
命令字节：利用命令字节指定数据字节的功能，例如命令字节为1表示传输温度，为2表示传输湿度等，1字节命令+n字节数据是工业中比较常用的一种格式。可以不使用
数据字节：数据字节长度可变，帧长字节为0，表示没有数据，帧长字节为255，表示有255字节数据。
校验字节：比较简单的一种校验方式为和校验，即把校验字节前的所以字节求和，最后保留低8位作为校验字节。在MODBUS协议中常用CRC16循环冗余校验方式，将校验字节前的所以字节加入计算，得到两字节CRC16校验码，采用此方式。
帧尾：与帧头相似，这里使用0xFF作为帧尾。

帧头		数据长度		命令		数据		CRC16校验	帧尾
A5 5A		XX		 XX		…XX 		…XX XX		 FF
2字节		1字节		1字节		n字节 …		 2字节		1字节




*/
remote_data Remote_Data;

extern UART_HandleTypeDef huart1;

void SendByte(uint8_t date)
{
	uint8_t buffer[1];
	buffer[0] = date;	
	HAL_UART_Transmit( &huart1 , buffer , 1 ,100 );
	//HAL_UART_Transmit_DMA(&huart1,buffer,1);//dma 有问题
}


void Send(const uint8_t *data,uint8_t len)
{
	uint8_t i;
	for (i = 0; i < len; i++)
	{
		SendByte(data[i]);//发送一个字节
	}
}


//16位循环冗余校验
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



//发送数据包
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
    Send(buf,cnt);//调用数据帧发送函数将打包好的数据帧发送出去
}



//数据帧解析
void Data_Analysis(uint8_t cmd,const uint8_t *datas,uint8_t len)
{

	
	
}




//接收数据
void Receive(uint8_t bytedata)
{

	static uint8_t step=0;//状态变量初始化为0 在函数中必须为静态变量
	static uint8_t cnt=0,Buf[300],len,cmd,*data_ptr;
	static uint16_t crc16;
	//进行数据解析 状态机
	switch(step)
	{
	    case 0://接收帧头1状态
	        if(bytedata== 0xA5)
	        {
	            step++;
	            cnt = 0;
	            Buf[cnt++] = bytedata;
	        }break;
	    case 1://接收帧头2状态
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
	    case 2://接收数据长度字节状态
	        step++;
	        Buf[cnt++] = bytedata;
	        len = bytedata;
	        break;
	    case 3://接收命令字节状态
	        step++;
	        Buf[cnt++] = bytedata;
	        cmd = bytedata;
	        data_ptr = &Buf[cnt];//记录数据指针首地址
	        if(len == 0)step++;//数据字节长度为0则跳过数据接收状态
	        break;
	    case 4://接收len字节数据状态
	        Buf[cnt++] = bytedata;
	        if(data_ptr + len == &Buf[cnt])//利用指针地址偏移判断是否接收完len位数据
	        {
	            step++;
	        }
	        break;
	    case 5://接收crc16校验高8位字节
	        step++;
	        crc16 = bytedata;
	        break;
	    case 6://接收crc16校验低8位字节
	        crc16 <<= 8;
	        crc16 += bytedata;
	        if(crc16 == CRC16_Check(Buf,cnt))//校验正确进入下一状态
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
	    case 7://接收帧尾
	        if(bytedata== 0xFF)//帧尾接收正确
	        {
	        	Data_Analysis(cmd,data_ptr,len);//数据解析
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
	    default:step=0;break;//多余状态，正常情况下不可能出现
	}
}







ch_transform th1;//数据转化的联合体

extern key_data key1;
void Task_Date_pack(void const * argument)
{


 	
	while(1)
	{

		uint8_t Xmessage[12];
		for(int aree=0;aree<adc_channel_number;aree++)//使用联合体     将int16_t转换位uint8_t
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























