#include <reg51.h>


#define Bus_16        //16λ����ģʽ,���ʹ��8λģʽ����ע�ʹ���䣬���ʹ��16λģʽ����򿪴˾�
#define  LCD_DataPortH P2     //��8λ���ݿ�,8λģʽ��ֻʹ�ø�8λ 
#define  LCD_DataPortL P0     //��8λ���ݿ�	,8λģʽ�µ�8λ���Բ�����,��ȷ��P0���Ѿ�����10K����,����̫С����С4.7K,�Ƽ�10K.
sbit LCD_RS = P3^5;  		 //����/�����л�
sbit LCD_WR = P3^6;		  //д����
sbit LCD_RD =P3^7;		     //������
sbit LCD_CS=P1^0;		//Ƭѡ	
sbit LCD_REST = P1^2;	      //��λ   

void delayms(int count)  // /* X1ms */
{
        int i,j;
        for(i=0;i<count;i++)
                for(j=0;j<1000;j++);
}

#ifdef  Bus_16    //��������-16λ����ģʽ   
void LCD_Writ_Bus(char VH,char VL)   //��������д�뺯��
{
    LCD_DataPortH=VH;	
	LCD_DataPortL=VL;		
	LCD_WR=0;
	LCD_WR=1; 
}
#else			//��������-8λ����ģʽ 
void LCD_Writ_Bus(char VH,char VL)   //��������д�뺯��
{	
    LCD_DataPortH=VH;	
   	LCD_WR=0;
	LCD_WR=1;
	LCD_DataPortH=VL;		
	LCD_WR=0;
	LCD_WR=1;
}
#endif

void Lcd_Write_Com(char VH,char VL)	 //��������-8λ����
{	
    LCD_RS=0;
	LCD_Writ_Bus(VH,VL);
}
void Lcd_Write_Data(char VH,char VL) //��������-8λ����
{
    LCD_RS=1;
	LCD_Writ_Bus(VH,VL);
}
void Lcd_Write_Com_Data(int com,int val)		   //������������
{
	Lcd_Write_Com(com>>8,com);
    Lcd_Write_Data(val>>8,val);
}

void Address_set(unsigned int x1,unsigned int y1,unsigned int x2,unsigned int y2)
{
	Lcd_Write_Com(0x00,0x20);Lcd_Write_Data(x1>>8,x1);	  //����X����λ��
    Lcd_Write_Com(0x00,0x21);Lcd_Write_Data(y1>>8,y1);   //����Y����λ��
    Lcd_Write_Com(0x00,0x50);Lcd_Write_Data(x1>>8,x1);   //��ʼX
	Lcd_Write_Com(0x00,0x52);Lcd_Write_Data(y1>>8,y1);	  //��ʼY
    Lcd_Write_Com(0x00,0x51);Lcd_Write_Data(x2>>8,x2);   //����X
	Lcd_Write_Com(0x00,0x53);Lcd_Write_Data(y2>>8,y2);   //����Y
    Lcd_Write_Com(0x00,0x22);							 
}

void Lcd_Init(void)
{

    LCD_REST=1;
    delayms(5);	
	LCD_REST=0;
	delayms(5);
	LCD_REST=1;
	LCD_CS=1;
	LCD_RD=1;
	LCD_WR=1;
	delayms(5);
	

	LCD_CS =0;  //��Ƭѡʹ��
	//************* Start Initial Sequence **********//

 Lcd_Write_Com_Data(0x00e5, 0x8000);	
		Lcd_Write_Com_Data(0x0000, 0x0001);	
		Lcd_Write_Com_Data(0x0001, 0x0100);
		Lcd_Write_Com_Data(0x0002, 0x0700);
		Lcd_Write_Com_Data(0x0003, 0x1030);
		Lcd_Write_Com_Data(0x0004, 0x0000);
		Lcd_Write_Com_Data(0x0008, 0x0202);	
		Lcd_Write_Com_Data(0x0009, 0x0000);	
		Lcd_Write_Com_Data(0x000A, 0x0000);
		Lcd_Write_Com_Data(0x000C, 0x0000);	
		Lcd_Write_Com_Data(0x000D, 0x0000);	
		Lcd_Write_Com_Data(0x000F, 0x0000);	
	//-----Power On sequence-----------------------	
		Lcd_Write_Com_Data(0x0010, 0x0000);	
		Lcd_Write_Com_Data(0x0011, 0x0007);	
		Lcd_Write_Com_Data(0x0012, 0x0000);	
		Lcd_Write_Com_Data(0x0013, 0x0000);	
		delayms(150);
		Lcd_Write_Com_Data(0x0010, 0x17B0);	
		Lcd_Write_Com_Data(0x0011, 0x0007);	
		delayms(50);
		Lcd_Write_Com_Data(0x0012, 0x013A);	
		delayms(50);
		Lcd_Write_Com_Data(0x0013, 0x1A00);	
		Lcd_Write_Com_Data(0x0029, 0x000c);		
		delayms(50);
	//-----Gamma control-----------------------	
		Lcd_Write_Com_Data(0x0030, 0x0000);	
		Lcd_Write_Com_Data(0x0031, 0x0505);	
		Lcd_Write_Com_Data(0x0032, 0x0004);	
		Lcd_Write_Com_Data(0x0035, 0x0006);	
		Lcd_Write_Com_Data(0x0036, 0x0707);	
		Lcd_Write_Com_Data(0x0037, 0x0105);	
		Lcd_Write_Com_Data(0x0038, 0x0002);	
		Lcd_Write_Com_Data(0x0039, 0x0707);	
		Lcd_Write_Com_Data(0x003C, 0x0704);	
		Lcd_Write_Com_Data(0x003D, 0x0807);	
	//-----Set RAM area-----------------------	
		Lcd_Write_Com_Data(0x0050, 0x0000);
		Lcd_Write_Com_Data(0x0051, 0x00EF);
		Lcd_Write_Com_Data(0x0052, 0x0000);
		Lcd_Write_Com_Data(0x0053, 0x013F);
		Lcd_Write_Com_Data(0x0060, 0x2700);
		Lcd_Write_Com_Data(0x0061, 0x0001);
		Lcd_Write_Com_Data(0x006A, 0x0000);
		Lcd_Write_Com_Data(0x0021, 0x0000);	
		Lcd_Write_Com_Data(0x0020, 0x0000);	
	//-----Partial Display Control------------	
		Lcd_Write_Com_Data(0x0080, 0x0000);	
		Lcd_Write_Com_Data(0x0081, 0x0000);
		Lcd_Write_Com_Data(0x0082, 0x0000);
		Lcd_Write_Com_Data(0x0083, 0x0000);
		Lcd_Write_Com_Data(0x0084, 0x0000);	
		Lcd_Write_Com_Data(0x0085, 0x0000);
	//-----Panel Control----------------------
		Lcd_Write_Com_Data(0x0090, 0x0010);	
		Lcd_Write_Com_Data(0x0092, 0x0000);
		Lcd_Write_Com_Data(0x0093, 0x0003);
		Lcd_Write_Com_Data(0x0095, 0x0110);
		Lcd_Write_Com_Data(0x0097, 0x0000);	
		Lcd_Write_Com_Data(0x0098, 0x0000);
	//-----Display on-----------------------	
		Lcd_Write_Com_Data(0x0007, 0x0173);	
		delayms(50);

	LCD_CS =1;  //�ر�Ƭѡʹ��

}

void Pant(char VH,char VL)
{
	int i,j;
	LCD_CS =0;  //��Ƭѡʹ��
	Address_set(0,0,239,319);
    for(i=0;i<320;i++)
	 {
	  for (j=0;j<240;j++)
	   	{
        	 Lcd_Write_Data(VH,VL);
	    }

	  }
     LCD_CS =1;  //�ر�Ƭѡʹ��
}	 
main()
{ 
	Lcd_Init();          //TFT��ʼ��
 	Pant(0xff,0xff);	 //TFT����	
	while(1)
	{
	    Pant(0xf8,0x00); //��ɫ
		delayms(2000);
	    Pant(0X07,0xE0); //��ɫ
		delayms(2000);
	    Pant(0x00,0x1f); //��ɫ      		 
    	delayms(2000);
    }



}













