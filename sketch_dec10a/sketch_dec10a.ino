#include "ads1292r.h"
#include <SPI.h>

ads1292r ADS1292;

byte SPI_RX_Buff[150] ;
static int SPI_RX_Buff_Count = 0;
char *SPI_RX_Buff_Ptr;
int Responsebyte = false;
unsigned int pckt =0 , buff=0,t=0 ,tmp1=0,j2=0;
unsigned long int EEG_Ch1_Data[150],EEG_Ch2_Data[150];
unsigned char datac[150];
unsigned long ueegtemp = 0,Pkt_Counter=0;
signed long seegtemp=0;
int i;

void setup() 
{
  ADS1292.ads1292_TestInit();
}

void loop() 
{
  if((digitalRead(ADS1292_DRDY_PIN)) == LOW)
  {  
    SPI_RX_Buff_Ptr = ADS1292.ads1292_Read_Data();
    Responsebyte = true; 
  }

  if(Responsebyte == true)
  {
    for(i = 0; i < 9; i++)
    {
      SPI_RX_Buff[SPI_RX_Buff_Count++] = *(SPI_RX_Buff_Ptr + i);
    }
    Responsebyte = false;
  }
  
  if(SPI_RX_Buff_Count >= 9)
  {     
    pckt = 0; tmp1=0;   j2=0;
    for(i=3;i<9;i+=9)
    {
      //EEG_Ch1_Data[tmp1++]=  SPI_RX_Buff[i+0];
      //EEG_Ch1_Data[tmp1++]= SPI_RX_Buff[i+1];
      //EEG_Ch1_Data[tmp1++]= SPI_RX_Buff[i+2];
      EEG_Ch2_Data[j2++]= (unsigned char)SPI_RX_Buff[i+3];
      EEG_Ch2_Data[j2++]= (unsigned char)SPI_RX_Buff[i+4];
      EEG_Ch2_Data[j2++]= (unsigned char)SPI_RX_Buff[i+5];

    }
    
    for(t=0; t< 1 ; t++)
    { 
      buff = 0;
      ueegtemp = (unsigned long) ((EEG_Ch2_Data[pckt]<<16)|(EEG_Ch2_Data[pckt+1]<<8)|EEG_Ch2_Data[pckt+2]);
      //Serial.print(ueegtemp,HEX);        
      //Serial.print("  ");                
      ueegtemp = (unsigned long) (ueegtemp<<8);
      seegtemp = (signed long) (ueegtemp);
      seegtemp = (signed long) (seegtemp>>8); 
            
      //Serial.println(seegtemp,HEX);
      pckt+= 3;
              
      datac[buff++] = (unsigned char) (seegtemp);
      datac[buff++] = (unsigned char) (seegtemp>>8);   //>>8
      datac[buff++] = ( unsigned char) (seegtemp >> 16); //>>16
      datac[buff++] = (unsigned char) (seegtemp >>24);

              
            
      

      for(i=0; i<4; i++) // transmit the data
      {
        Serial.write(datac[i]); 
                                
      } 
                        Serial.write('\n');       
    }
    
    SPI_RX_Buff_Count = 0;
          
  }           
} 

    


