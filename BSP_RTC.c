/**
  ******************************************************************************
  * @file    BSP_RTC.c
  * @author  WangBo
  * @version V1.0.0
  * @date    2012-9-12
  * @brief   RTC Config.
  ******************************************************************************
  * @attention
  * 此文件适用于STM32F105或STM32F107带控制器的芯片
  ******************************************************************************
	由于STM32单片机内置的RTC没有时、分、秒、年、月、日独立的时间寄存器，
	本次PCJ-3设计使用外接的专用时钟芯片DS1307进行实时时钟控制。
*/

/* Includes ------------------------------------------------------------------*/
#include "BSP_RTC.h"
#include "BSP_Usart.h"
/* Private typedef -----------------------------------------------------------*/
GPIO_InitTypeDef GPIO_InitStructure1;
ttime RTC_SystemTime;
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void RTC_NVIC_Config(void);
/* Private functions ---------------------------------------------------------*/
void delay10us( void )
{
	u16  t = 1000;
	while ( --t );
}
void delay10ms( void )
{
	u16  t = 10000;
	while ( --t );
}

void SDA_Output()
{
	GPIO_InitStructure1.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure1.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure1.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure1);
}
void SDA_Input()
{
	GPIO_InitStructure1.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure1.GPIO_Pin=GPIO_Pin_9;
	GPIO_InitStructure1.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure1);
}
void SDA2_Output()
{
	GPIO_InitStructure1.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure1.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure1.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure1);
}
void SDA2_Input()
{
	GPIO_InitStructure1.GPIO_Mode=GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure1.GPIO_Pin=GPIO_Pin_7;
	GPIO_InitStructure1.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure1);
}
/**
  * @brief  DS1307开始数据传输时序
			SDA从高到低，SCL为高
  * @param  None
  * @retval None
  */
void start( void )
{
	SCL_0();
	SDA_1();
	SCL_1();
	SCL_1();
	delay10us();
	
	SDA_0();
	delay10us();
	
	SCL_0();
}
/**
  * @brief  DS1307结束数据传输时序
		  SDA从低到高，SCL为高
  * @param  None
  * @retval None
  */
void endd( void )
{
	SCL_0();
	SDA_0();
	SCL_1();
	SCL_1();
	delay10us();
	SDA_1();
	delay10us();
}
/**
  * @brief  24256开始数据传输时序
			SDA从高到低，SCL为高
  * @param  None
  * @retval None
  */
void start2( void )
{
	SCL2_0();
	SDA2_1();
	SCL2_1();
	SCL2_1();
	SDA2_0();
	SCL2_0(); 
}
/**
  * @brief  24256结束数据传输时序
		  SDA从低到高，SCL为高
  * @param  None
  * @retval None
  */
void endd2( void )
{
	SCL2_0();
	SDA2_0();
	SCL2_1();
	SCL2_1();
	SDA2_1();

}



u8 sda_data  ;
/**
  * @brief 串行发送8位数据
  * @param  vu32 TimersTxId
  * @retval None
  */
u8 write_byte( u8 x )
{
	u8  i,j  ;
	delay10us();
	for (  i  = 0 ;  i <  8 ; i ++ )
	{
		SCL_0();

		if ( x & 0x80  )
		{
			SDA_1();
		}
		else
		{
			SDA_0();
		}
		delay10us();
		x <<= 1;
		SCL_1();
		SCL_1();
		SCL_1();
		delay10us();
	}
	SCL_0();
	delay10us();
	SDA_1();
	SDA_Input();
	// SCL_1();
	SCL_1();
	delay10us();

	sda_data  =  1;
	j  =  200 ;
	while ( ( sda_data  & 0x1 ) && -- j   )	 /* wait for slave ack *///	
	{
		sda_data=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);
		#ifndef DEBUG
	IWDG_ReloadCounter();
#endif
	}

	SCL_0();
	delay10us();
	SDA_Output();
	delay10us();
	if ( j ==   0  )
	{
		return 1;
	}
	else
	{
		return  0 ;
	}
}
u8  read_byte( void )
{
	u8  i,j;

	i = 0;
	delay10us();
	SCL_0( );
	SDA_1();
	SDA_Input();

	for (j = 0; j < 8; j++ )
	{
		SCL_0( );
		SCL_0( );
		SCL_0( );
		delay10us();

		SCL_1( );
		SCL_1( );
		SCL_1( );
		delay10us();
		i = i << 1;
		sda_data=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_9);
		if (( sda_data & 0x1 ) == 1)
		{
			i += 1;

		}
	}

	SCL_0();

	delay10us();
	SDA_Output( );
	SDA_1();
	/* master no ask */
	SCL_1();;
	delay10us();
	SCL_0();
	return(i);
}
u8 iic_status  = 0 ;
u8 rbyte_1307( u8  adr)           /* Abs. adr. reading data */
{
	u8  i ;

	iic_status  = 0 ;
	start();

	if ( write_byte(0xD0)==  1) //0xd0代表往DS1307写数据
	{
		iic_status |= 1;
	}
	if ( write_byte(adr) ==  1)
	{
		iic_status |= 1;
	}
	start();

	if ( write_byte(0xD1) == 1 )//0xd1代表从DS1307读数据
	{
		iic_status |= 1;
	}
	i=read_byte();
	endd();
	return( i );
}

u8  wbyte_1307(u8 adr, u8 num)   /* Abs.adr. writting data */
{
	u8  i = 0;
	start();
	if ( write_byte(0xD0) ==  1 )
	{
		i  |= 1;
	}

	if ( write_byte(adr) ==  1 )
	{
		i |= 1;
	}
	if (    write_byte( num ) == 1 )
	{
		i |= 1;
	}
	endd();
	return i ;
}

/**
  * @brief 串行发送8位数据
  * @param  vu32 TimersTxId
  * @retval None
  */
u8 write_byte_Save( u8 x )
{
	u16  i,j  ;
	delay10us();
	for (  i  = 0 ;  i <  8 ; i ++ )
	{
		SCL2_0();

		if ( x & 0x80  )
		{
			SDA2_1();
		}
		else
		{
			SDA2_0();
		}
		delay10us();
		x <<= 1;
		SCL2_1();
		SCL2_1();
		SCL2_1();
		delay10us();
	}
	SCL2_0();
	delay10us();
	SDA2_Input();
	// SCL_1();
	SCL2_1();
	delay10us();

	sda_data  =  1;
	j  =  200 ;
	while ( ( sda_data  & 0x1 ) && -- j   )	 /* wait for slave ack */
	{
		sda_data=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7);
		#ifndef DEBUG
	IWDG_ReloadCounter();
#endif
	}

	SCL2_0();
	delay10us();
	SDA2_Output();
	delay10us();
	if ( j ==   0  )
	{
		return 1;
	}
	else
	{
		return  0 ;
	}
}
u8  read_byte_Save( void )
{
	u8  i,j;

	i = 0;
	delay10us();
	SCL2_0( );
	SDA2_1();
	SDA2_Input();

	for (j = 0; j < 8; j++ )
	{
		SCL2_0( );
		SCL2_0( );
		SCL2_0( );
		delay10us();

		SCL2_1( );
		SCL2_1( );
		SCL2_1( );
		delay10us();
		delay10us();
		delay10us();
		delay10us();
		i = i << 1;
		sda_data=GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_7);
		if (( sda_data & 0x1 ) == 1)
		{
			i += 1;
		}
	}
	SCL2_0();
	delay10us();
	SDA2_Output( );
	SDA2_1();
	/* master no ask */
	SCL2_1();;
	delay10us();
	SCL2_0();
	return(i);
}

u8 read_24256data( u16  adr )           /* Abs. adr. reading data */ // fm24c256
{  
	u8 i,cmd;
	start2();
	cmd=0xa0;
   	write_byte_Save(cmd);
	i=(u8)(adr>>8);
	write_byte_Save(i);
	i=(u8)adr;
	write_byte_Save(i);
	// write_byte(adr);
   	start2();
   	cmd |= 0x1;
   	write_byte_Save( cmd );
	delay10ms();
   	i = read_byte_Save();
   	endd2();
   	return( i );
}


void write_24256data( u16 adr, u8 num)   /* Abs.adr. writting data */	//fm24c256
{  	
	u8 i,cmd;
   	start2();
	cmd=0xa0; // x:0 第0页
   	write_byte_Save(cmd);
	i=(u8)(adr>>8);
	write_byte_Save(i);
	i=(u8)adr;
	write_byte_Save(i);
	// write_byte(adr);
   	write_byte_Save(num);
   	endd2();
	
	start2();
	cmd=0xa0; // x:0 第0页
   	write_byte_Save(cmd);
	write_byte_Save(0);
	// write_byte_Save(0);
   	// write_byte_Save(0x55);
   	endd2();
}

void QingChu_24256data(u16 adr, u8 num,u16 ii)
{
	u8 i2;
	u16 i,i1;
	i1=adr;
	i2=num;
	for (i=0;i<ii;i++)
	{
		write_24256data(i1, i2);
	}	
}

FlagStatus init_1307( void )
{
	/* wbyte_1307(0x00,0x00);
	wbyte_1307(0x01,0x00);
	wbyte_1307(0x0d,0x00);
	wbyte_1307(0x0e,0x02);
	wbyte_1307(0x0f,0x00); */

	if(rbyte_1307(0x08)==0x11)
	{
		read_time(&RTC_SystemTime);
		// wbyte_1307(0x00,0x00);
	}
	else//第一次上电初始化 	   
	{ 
		// wbyte_1307(0x00,0x50); /* secoond */
		// wbyte_1307(0x01,0x51);  /*  minute */
		// wbyte_1307(0x02,0x15) ; /* hour */
		// wbyte_1307(0x04,0x23);  /* day */
		// wbyte_1307(0x05,0x03);  /* month */
		// wbyte_1307(0x06,0x17);   /* year */
		// wbyte_1307(0x07,0x00);   /* year */
		// wbyte_1307(0x08,0x11);   /* year */
		wbyte_1307(0x00,0); /* secoond */
		wbyte_1307(0x01,0);  /*  minute */
		wbyte_1307(0x02,0) ; /* hour */
		wbyte_1307(0x04,0);  /* day */
		wbyte_1307(0x05,0);  /* month */
		wbyte_1307(0x06,0);   /* year */
		wbyte_1307(0x07,0);   /* year */
		wbyte_1307(0x08,0x11);   /* year */
	}

	return RESET;
}

void  read_time(ttime *time)
{
//	time->second =  rbyte_1307( 0x02 );
//	time->minute =  rbyte_1307( 0x03 )&0x7f;
//	time->hour   =  rbyte_1307( 0x04 )&0x3f;
//	time->day    =  rbyte_1307( 0x05 )&0x3f;
//	time->month  =  rbyte_1307( 0x07 )&0x1f;
//	time->yearl  =  rbyte_1307( 0x08 );
//	time->yearh  =  0x20;
	time->second =  rbyte_1307( 0x00 );
	time->minute =  rbyte_1307( 0x01 )&0x7f;
	time->hour   =  rbyte_1307( 0x02 )&0x3f;
	time->day    =  rbyte_1307( 0x04 )&0x3f;
	time->month  =  rbyte_1307( 0x05 )&0x1f;
	time->yearl  =  rbyte_1307( 0x06 );
	time->yearh  =  0x20;
	
	if((time->second&0x80)==0x80)
	{
		wbyte_1307(0x00,0x50); /* secoond */
	}
}

void write_time(void )
{
	wbyte_1307(0,RTC_SystemTime.second ); /* secoond */
	wbyte_1307(1, RTC_SystemTime.minute );  /*  minute */
	wbyte_1307(2, RTC_SystemTime.hour   ) ; /* hour    */
	//  wbyte_1307(0x3,1);  /* week */
	wbyte_1307( 4, RTC_SystemTime.day );  /*date */
	wbyte_1307( 5,RTC_SystemTime.month );  /* month */
	wbyte_1307( 6,RTC_SystemTime.yearl );   /* year*/

	//  wbyte_1307(7 ,0x11); /* */
}

/**
  * @brief  initializes Timers1
  * @param  vu32 TimersTxId
  * @retval None
  */
void BSP_RTC_Config(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	
	GPIO_InitStructure1.GPIO_Mode=GPIO_Mode_Out_PP;
	GPIO_InitStructure1.GPIO_Pin=GPIO_Pin_6;//SCL2
	GPIO_InitStructure1.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure1);
	
	GPIO_InitStructure1.GPIO_Mode=GPIO_Mode_Out_OD;
	GPIO_InitStructure1.GPIO_Pin=GPIO_Pin_8;//SCL1
	GPIO_InitStructure1.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_InitStructure1);

	SDA_Output();
	SDA2_Output();

	GPIO_SetBits(GPIOB,GPIO_Pin_6);
	GPIO_SetBits(GPIOB,GPIO_Pin_7);
	GPIO_SetBits(GPIOB,GPIO_Pin_8);
	GPIO_SetBits(GPIOB,GPIO_Pin_9);
}

