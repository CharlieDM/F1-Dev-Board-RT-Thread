
#include"reg52.h"
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


/* LCD color */
#define White          0xFFFF
#define Black          0x0000
#define Blue           0x001F
#define Blue2          0x051F
#define Red            0xF800
#define Magenta        0xF81F
#define Green          0x07E0
#define Cyan           0x7FFF
#define Yellow         0xFFE0

sbit CS=P1^0;		//Ƭѡ
sbit RES=P1^1;		//��λ
sbit RS=P3^5;		//����/����ѡ��
sbit RW= P3^6;
sbit LCD_RD =P3^7;                    //���ݿ�ʹ��P1
//====================================================//

void main (void);
void ILI9325_Initial(void);
void show_colour_bar (void);
void Init_data(unsigned char x, unsigned int y);
void Write_Cmd(unsigned char DH,unsigned char DL);
void Write_Data(unsigned char DH,unsigned char DL);
void delayms(unsigned int tt);
void show_photo(void);
void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color);
unsigned char code pic[];
void  Write_Data_U16(unsigned int y);
static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1);
void ClearScreen(unsigned int bColor);
void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void LCD_PutString(unsigned short x, unsigned short y, char *s, unsigned int fColor, unsigned int bColor);

void LCD_PutChar8x8(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor);
void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
void PutGB3232(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor);
//================================================//

void  main(void)
{   
	CS=1;
	LCD_RD=1;
	delayms(5);
	RES=0;
	delayms(15);
	RES=1;
	delayms(5);
	ILI9325_Initial();
	while(1)
	{
	


ClearScreen(0x00);

//show_colour_bar();	


LCD_PutString(40,60,"I LOVE MY JOB ",Blue2,Yellow);

LCD_PutString(40,100,"רҵ����֧����̳",0x07e0,0xf800);
LCD_PutString(40,120,"רҵ�����幤�ذ�",0xF800,Yellow);
LCD_PutString(40,140,"1234567890",0xF800,Yellow);
LCD_PutString(20,160,"abcdefghijklmnopqistuvwxyz",0xF800,Yellow);
LCD_PutString(20,180,"`,./<>';:[]{}\|?)(-=+*&^%$",0xF800,Yellow);
PutGB3232(20,200,"��",Blue,Yellow);	//д��32x32����
PutGB3232(60,200,"��",Blue,Red);
PutGB3232(100,200,"��",Blue,Magenta);
PutGB3232(140,200,"Ƭ",Blue,Green);
PutGB3232(180,200,"��",Blue,Cyan);	
PutGB3232(20,240,"˶",Blue,0X00);	
PutGB3232(60,240,"ҫ",Blue,0X00);	
PutGB3232(100,240,"��",Blue,0X00);	
PutGB3232(140,240,"��",Blue,0X00);	
PutGB3232(180,240,"��",Blue,0X00);
PutGB3232(20,280,"��",Blue,0X00);		
PutGB3232(60,280,"��",Blue,0X00);	
PutGB3232(100,280,"ӭ",Blue,0X00);	
PutGB3232(140,280,"��",Blue,0X00);	
PutGB3232(180,280,"��",Blue,0X00);	

//	show_photo();

		while(1);	


	}
}


void ClearScreen(unsigned int bColor)
{
 unsigned int i,j;
 
 for (i=0;i<320;i++)
	{
	
	   for (j=0;j<240;j++)

	       Write_Data_U16(bColor);

	}
}

/////////////////////////////////////////////////////////////
#include "8X16.h"
void LCD_PutChar8x16(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor)
{
 unsigned int i,j;
 LCD_SetPos(x,x+8-1,y,y+16-1);
 for(i=0; i<16;i++) {
		unsigned char m=Font8x16[c*16+i];
		for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				Write_Data_U16(fColor);
				}
			else {
				Write_Data_U16(bColor);
				}
			m<<=1;
			}
		}
}


void LCD_PutChar(unsigned short x, unsigned short y, char c, unsigned int fColor, unsigned int bColor) {

		LCD_PutChar8x16( x, y, c, fColor, bColor );
	}


#include "GB1616.h"	//16*16������ģ

void PutGB1616(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor){
	unsigned int i,j,k;

	LCD_SetPos(x,  x+16-1,y, y+16-1);

	for (k=0;k<64;k++) { //64��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
	  if ((codeGB_16[k].Index[0]==c[0])&&(codeGB_16[k].Index[1]==c[1])){ 
    	for(i=0;i<32;i++) {
		  unsigned short m=codeGB_16[k].Msk[i];
		  for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				Write_Data_U16(fColor);
				}
			else {
				Write_Data_U16(bColor);
				}
			m<<=1;
			} 
		  }
		}  
	  }	
	}

	#include "GB3232.h"	//32*32������ģ

void PutGB3232(unsigned short x, unsigned short  y, unsigned char c[2], unsigned int fColor,unsigned int bColor){
	unsigned int i,j,k;

	LCD_SetPos(x,  x+32-1,y, y+32-1);

	for (k=0;k<15;k++) { //15��ʾ�Խ����ֿ��еĸ�����ѭ����ѯ����
	  if ((codeGB_32[k].Index[0]==c[0])&&(codeGB_32[k].Index[1]==c[1])){ 
    	for(i=0;i<128;i++) {
		  unsigned short m=codeGB_32[k].Msk[i];
		  for(j=0;j<8;j++) {
			if((m&0x80)==0x80) {
				Write_Data_U16(fColor);
				}
			else {
				Write_Data_U16(bColor);
				}
			m<<=1;
			} 
		  }
		}  
	  }	
	}

void LCD_PutString(unsigned short x, unsigned short y, unsigned char *s, unsigned int fColor, unsigned int bColor) {
	 unsigned char l=0;
	while(*s) {
		if( *s < 0x80) 
		    {
			LCD_PutChar(x+l*8,y,*s,fColor,bColor);
			s++;l++;
			}
		else
		    {
			PutGB1616(x+l*8,y,(unsigned char*)s,fColor,bColor);
			s+=2;l+=2;
			}
		}
	}
//==================== ��ʾR G B �ɫ ====================//



void Show_RGB (unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1,unsigned int Color)
{
	unsigned int i,j;
	//address_set();
	LCD_SetPos(x0,x1,y0,y1);
	for (i=y0;i<=y1;i++)
	{
	   for (j=x0;j<=x1;j++)
	       Write_Data_U16(Color);

	}


}

//====================== ��ʾ���� ======================//
void show_colour_bar (void)

{
	int V,H;
	LCD_SetPos(0,240,0,320);//320x240

	for(H=0;H<240;H++)
	{
		for(V=0;V<40;V++)
		Write_Data(0xf8,0x00);
	}

	for(H=0;H<240;H++)
	{
		for(V=40;V<80;V++)
		Write_Data(0x07,0xe0);
	}

	for(H=0;H<240;H++)
	{
		for(V=80;V<120;V++)
		Write_Data(0x00,0x1f);
	}

	for(H=0;H<240;H++)
	{
		for(V=120;V<160;V++)
		Write_Data(0xff,0xe0);
	}

	for(H=0;H<240;H++)
	{
		for(V=160;V<200;V++)
		Write_Data(0xf8,0x1f);
	}

	for(H=0;H<240;H++)
	{
		for(V=200;V<240;V++)
		Write_Data(0x07,0xff);
	}

	for(H=0;H<240;H++)
	{
		for(V=240;V<280;V++)
		Write_Data(0xff,0xff);
	}

	for(H=0;H<240;H++)
	{
		for(V=280;V<320;V++)
		Write_Data(0x00,0x00);
	}

}

void show_photo(void)
{
	unsigned char j;
	unsigned int i;
	unsigned long s=0;

	LCD_SetPos(0,240,0,320);//320x240

	for (i=0;i<75;i++)
	{
	for (j=0;j<240;j++)
	Write_Data(0xff,0xff);
		
	}

	for (i=0;i<170;i++)
	{
	for (j=0;j<55;j++)
		Write_Data(0xff,0xff);

		for (j=0;j<130;j++)
		Write_Data(pic[s++],pic[s++]);
		
		for (j=0;j<55;j++)
		Write_Data(0xff,0xff);
	}

    for (i=0;i<75;i++)
	{
	for (j=0;j<240;j++)
	Write_Data(0xff,0xff);
		
	}

	}

//=======================================================//



void  Init_data (unsigned char x,unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Cmd(0x00,x);
	Write_Data(m,n);

}


void  Write_Data_U16(unsigned int y)
{
	unsigned char m,n;
	m=y>>8;
	n=y;
	Write_Data(m,n);

}
//====================== д���� ==========================//

void Write_Cmd(unsigned char DH,unsigned char DL)
{
  
 	

	CS=0;
	RS=0;

	P2=DH;


	P0=DL;
	
	RW=0;
	RW=1;
	CS=1;
}

//===================== д���� ===========================//

void Write_Data(unsigned char DH,unsigned char DL)
{
 
  
	
	CS=0;
	
	RS=1;
	P2=DH;

	P0=DL;	
	RW=0;
	RW=1;
	CS=1;
}





//=======================================================
void delayms(unsigned int count)
{
    int i,j;                                                                                
    for(i=0;i<count;i++)                                                                    
       {
	     for(j=0;j<260;j++);
       }                                                                                     
}



//===================== ��ʼ������ =======================//



void ILI9325_Initial(void)
{ 

  //////////////////////////////////////////////////////////
 delayms(50);                     //���ݲ�ͬ�����ٶȿ��Ե�����ʱ�������ȶ���ʾ

	

Init_data(0x0000,0x0001);    delayms(1);  //�򿪾���
    Init_data(0x0003,0xA8A4);    delayms(1);   //0xA8A4
    Init_data(0x000C,0x0000);    delayms(1);   
    Init_data(0x000D,0x080C);    delayms(1);   
    Init_data(0x000E,0x2B00);    delayms(1);   
    Init_data(0x001E,0x00B0);    delayms(1);   
    Init_data(0x0001,0x2B3F);    delayms(1);   //�����������320*240  0x6B3F
    Init_data(0x0002,0x0600);    delayms(1);
    Init_data(0x0010,0x0000);    delayms(1);
    Init_data(0x0011,0x6070);    delayms(1);        //0x4030           //�������ݸ�ʽ  16λɫ 
    Init_data(0x0005,0x0000);    delayms(1);
    Init_data(0x0006,0x0000);    delayms(1);
    Init_data(0x0016,0xEF1C);    delayms(1);
    Init_data(0x0017,0x0003);    delayms(1);
    Init_data(0x0007,0x0233);    delayms(1);        //0x0233       
    Init_data(0x000B,0x0000);    delayms(1);
    Init_data(0x000F,0x0000);    delayms(1);        //ɨ�迪ʼ��ַ
    Init_data(0x0041,0x0000);    delayms(1);
    Init_data(0x0042,0x0000);    delayms(1);
    Init_data(0x0048,0x0000);    delayms(1);
    Init_data(0x0049,0x013F);    delayms(1);
    Init_data(0x004A,0x0000);    delayms(1);
    Init_data(0x004B,0x0000);    delayms(1);
    Init_data(0x0044,0xEF00);    delayms(1);
    Init_data(0x0045,0x0000);    delayms(1);
    Init_data(0x0046,0x013F);    delayms(1);
    Init_data(0x0030,0x0707);    delayms(1);
    Init_data(0x0031,0x0204);    delayms(1);
    Init_data(0x0032,0x0204);    delayms(1);
    Init_data(0x0033,0x0502);    delayms(1);
    Init_data(0x0034,0x0507);    delayms(1);
    Init_data(0x0035,0x0204);    delayms(1);
    Init_data(0x0036,0x0204);    delayms(1);
    Init_data(0x0037,0x0502);    delayms(1);
    Init_data(0x003A,0x0302);    delayms(1);
    Init_data(0x003B,0x0302);    delayms(1);
    Init_data(0x0023,0x0000);    delayms(1);
    Init_data(0x0024,0x0000);    delayms(1);
    Init_data(0x0025,0x8000);    delayms(1);
    Init_data(0x004f,0);        //����ַ0
    Init_data(0x004e,0);        //����ַ0


	
	
 Write_Cmd (0x00,0x22);//LCD_WriteCMD(GRAMWR);

}

 





/*===========================================================*/

/*************************************************************
��������:LCD_DefineDispWindow
��    ��:������ʾ����
��    ��:x0:  ������X�����н�С��
	 x1:  ������X�����нϴ���
	 y0:  ������Y�����н�С��
	 y1:  ������Y�����нϴ��� 
�� �� ֵ:��
*************************************************************/
static void LCD_SetPos(unsigned int x0,unsigned int x1,unsigned int y0,unsigned int y1)
{
	Init_data(0x0044,(x1<<8)+x0);
	Init_data(0x0045,y0);
	Init_data(0x0046,y1);
	Init_data(0x004e,x0);
	Init_data(0x004f,y0);
     Write_Cmd (0x00,0x22);//LCD_WriteCMD(GRAMWR);  
}


