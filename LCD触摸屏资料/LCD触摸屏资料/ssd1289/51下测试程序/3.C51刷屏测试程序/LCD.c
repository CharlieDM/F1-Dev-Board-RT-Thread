#include <reg51.h>

/*
��Ƭ��������ѹ3.3V
����Ĭ��IO���ӷ�ʽ��

�����ߣ�RS-P3^5;    WR-P3^6;   RD-P3^7;   CS-P1^0;   REST-P1^1;

������: DB0-DB7��������P0^0-P0^7;  DB8-DB15��������P2^0-P2^7;

�����������ӷ�ʽ��(��ʹ�ô����ɲ�����)
D_CLK-P1^2;  D_CS-P1^3;  D_DIN-P1^4;  D_OUT-P1^6;  D_PENIRQ-P1^7;

SD�����ߣ�(��ʹ�ô����ɲ�����)
SD_MISO-P31;  SD_SCK-P32;  SD_MOSI-P33;  SD_CS-P34;
*/
#define  LCD_DataPortH P2     //��8λ���ݿ�
#define  LCD_DataPortL P0     //��8λ���ݿ�,��ȷ��P0���Ѿ�����10K����,����̫С����С4.7K,�Ƽ�10K.
sbit LCD_RS = P3^5;  		 //����/�����л�
sbit LCD_WR = P3^6;		  //д����
sbit LCD_RD =P3^7;		     //������
sbit LCD_CS=P1^0;		//Ƭѡ	
sbit LCD_REST = P1^1;	      //��λ   	
 
void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<100;j++);
}
  

void Lcd_Write_Com( int  DH)	 //����
{	
    LCD_RS=0;
	LCD_CS =0;	 
	LCD_DataPortH=DH>>8;	
	LCD_DataPortL=DH;		
	LCD_WR=0;
	LCD_WR=1;
	LCD_CS =1;	
}
void Lcd_Write_DATA(int DH)	//����	
{
    LCD_RS=1;
	LCD_CS =0;	  				
	LCD_DataPortH=DH>>8;	
	LCD_DataPortL=DH;					
	LCD_WR=0;
	LCD_WR=1;
	LCD_CS =1;	
}


void Lcd_Write_Com_Data( int com1,dat1)	//��������һ�� 
{
   Lcd_Write_Com(com1);
   Lcd_Write_DATA(dat1);
}



void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{ 
	Lcd_Write_Com_Data(0x0044,(x2<<8)+x1);
	Lcd_Write_Com_Data(0x0045,y1);
	Lcd_Write_Com_Data(0x0046,y2);
	Lcd_Write_Com_Data(0x004e,x1);
	Lcd_Write_Com_Data(0x004f,y1);
    Lcd_Write_Com(0x0022);	     	  
   	
}	
void Lcd_Init(void)
{

    LCD_REST=1;
    delayms(5);	
	LCD_REST=0;
	delayms(10);
	LCD_REST=1;
	LCD_CS=1;
	LCD_RD=1;
	LCD_WR=1;
	delayms(20);

    Lcd_Write_Com_Data(0x0000,0x0001);    delayms(1);  //�򿪾���
    Lcd_Write_Com_Data(0x0003,0xA8A4);    delayms(1);   //0xA8A4
    Lcd_Write_Com_Data(0x000C,0x0000);    delayms(1);   
    Lcd_Write_Com_Data(0x000D,0x080C);    delayms(1);   
    Lcd_Write_Com_Data(0x000E,0x2B00);    delayms(1);   
    Lcd_Write_Com_Data(0x001E,0x00B0);    delayms(1);   
    Lcd_Write_Com_Data(0x0001,0x2B3F);    delayms(1);   //�����������320*240  0x6B3F
    Lcd_Write_Com_Data(0x0002,0x0600);    delayms(1);
    Lcd_Write_Com_Data(0x0010,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0011,0x6070);    delayms(1);        //0x4030           //�������ݸ�ʽ  16λɫ 
    Lcd_Write_Com_Data(0x0005,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0006,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0016,0xEF1C);    delayms(1);
    Lcd_Write_Com_Data(0x0017,0x0003);    delayms(1);
    Lcd_Write_Com_Data(0x0007,0x0233);    delayms(1);        //0x0233       
    Lcd_Write_Com_Data(0x000B,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x000F,0x0000);    delayms(1);        //ɨ�迪ʼ��ַ
    Lcd_Write_Com_Data(0x0041,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0042,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0048,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0049,0x013F);    delayms(1);
    Lcd_Write_Com_Data(0x004A,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x004B,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0044,0xEF00);    delayms(1);
    Lcd_Write_Com_Data(0x0045,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0046,0x013F);    delayms(1);
    Lcd_Write_Com_Data(0x0030,0x0707);    delayms(1);
    Lcd_Write_Com_Data(0x0031,0x0204);    delayms(1);
    Lcd_Write_Com_Data(0x0032,0x0204);    delayms(1);
    Lcd_Write_Com_Data(0x0033,0x0502);    delayms(1);
    Lcd_Write_Com_Data(0x0034,0x0507);    delayms(1);
    Lcd_Write_Com_Data(0x0035,0x0204);    delayms(1);
    Lcd_Write_Com_Data(0x0036,0x0204);    delayms(1);
    Lcd_Write_Com_Data(0x0037,0x0502);    delayms(1);
    Lcd_Write_Com_Data(0x003A,0x0302);    delayms(1);
    Lcd_Write_Com_Data(0x003B,0x0302);    delayms(1);
    Lcd_Write_Com_Data(0x0023,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0024,0x0000);    delayms(1);
    Lcd_Write_Com_Data(0x0025,0x8000);    delayms(1);
    Lcd_Write_Com_Data(0x004f,0);        //����ַ0
    Lcd_Write_Com_Data(0x004e,0);        //����ַ0
	Lcd_Write_Com(0x0022);
}


void Pant(unsigned int color)
{
	int i,j;
	Address_set(0,0,239,319);
	
    for(i=0;i<320;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
         Lcd_Write_DATA(color);
	    }

	  }		
}

main()
{
	while(1)
	{ 
	Lcd_Init();   //tft��ʼ��
	Pant(0xf800); //��ɫ
	delayms(1000);
	Pant(0X07E0); //��ɫ
	delayms(1000);
	Pant(0x001f); //��ɫ  
	delayms(1000);
    }



}





