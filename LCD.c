       //// User Layer :
            #define data B
            #define command D
            #define Rs 0
            #define E 1
            #define mode 8              //in case of 4 bit mode the high 4  bit must be used in both lcd and PORT

         //end of user Layer

         #define A  0x05
         #define B  0x06
         #define C  0x07
         #define D 0x08




void delay_us(int n);

         void lcd_init2();
         void lcd_command2(char cmd ) ;
         void lcdout(unsigned char value) ;
         void lcdprint (char * str) ;
 
 
int main (){
        lcd_init2();
        lcdprint("Hello");

}





 void lcd_init2()
  {   (*(volatile char *)(data|0x80))=0X00;                     //TRIS THE DATA PORT AS OUTPUT
      (*(volatile char *)(command|0x80))=0X00;                     //TRIS THE CMD port as output
      (*(volatile char *)data)=0X00;                          // Data port =00 as init value
      (*(volatile char *)command)&= ~(1<<E);                                  //Reset E bin
      if (mode==8)
       {
      delay_us(2000);
      lcd_command2(0x38);                         //init command
      }
     else if (mode==4)
      {
         lcd_command2(0x33);                   //init command
         lcd_command2(0x32);                  //init command
          lcd_command2(0x28);                 //init command
      }
      
      lcd_command2(0x0e);                         //init command
      lcd_command2(0x01);                         //init command
      delay_us(2000);
      lcd_command2(0x06);                        //init command
  }



    
     void lcd_command2( char cmd )
      { if(mode==8)
       {(*(volatile char *)data)=cmd ;  }                 //Data pins = command
       
       else if (mode==4)
          {(*(volatile char *)data)=cmd &0xf0 ;   // Oring with cmd not = to not change its value 
           (*(volatile char *)command)&=~(1<<Rs) ;        //Reset Rs  for Command Write
           (*(volatile char *)command)|=(1<<E) ;          //Set Enable start of high to low pulse
           delay_us(1);                                  //delay
           (*(volatile char *)command)&=~(1<<E) ;       //Reset Enable End of the high to low pulse
           delay_us(100);
           (*(volatile char *)data)=cmd<<4 ;
          }
          

       (*(volatile char *)command)&=~(1<<Rs) ;        //Reset Rs  for Command Write
       (*(volatile char *)command)|=(1<<E) ;          //Set Enable start of high to low pulse
         delay_us(1);                                  //delay
       (*(volatile char *)command)&=~(1<<E) ;       //Reset Enable End of the high to low pulse
        delay_us(100);

      }


         void lcdout( unsigned char value)
      {
        (*(volatile char *)command) |=(1<<Rs) ;         //Set Rs pin for Data write
       if(mode==8)
      {
      (*(volatile char *)data)=value ;                 //Data pins = Data

      }
      else if (mode==4)
      {
      (*(volatile char *)data)=value&0xf0 ;
      (*(volatile char *)command) |=(1<<Rs) ;         //Set Rs pin for Data write
       (*(volatile char *)command)|=(1<<E) ;          //Set Enable start of high to low pulse
          delay_us(1);                                  //delay
       (*(volatile char *)command)&=~(1<<E) ;       //Reset Enable End of the high to low pulse
       delay_us(100);
        (*(volatile char *)data)=value<<4 ;
      
      }

       (*(volatile char *)command)|=(1<<E) ;          //Set Enable start of high to low pulse
          delay_us(1);                                  //delay
       (*(volatile char *)command)&=~(1<<E) ;       //Reset Enable End of the high to low pulse
       delay_us(100);

      }


      void lcdprint (char * str){
      unsigned char i =0 ;
      while(str[i]!=0){lcdout(str[i]) ; i++;}

      }
			/* Micro seconds delay function */
void delay_us(int n)
{
 int i,j;
 for(i=0;i<n;i++)
 for(j=0;j<3;j++)
 {}
 
}















