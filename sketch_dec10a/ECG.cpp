#include "ads1292r.h"
#define buffersize 180
class ecg {
   public:
      ads1292r ADS1292;
      byte SPI_RX_Buff[buffersize];
      int SPI_RX_Buff_Count = 0;
      char *SPI_RX_Buff_Ptr;
     // int Responsebyte = false;
      unsigned int pckt =0 , buff=0,t=0 ,tmp1=0,j2=0;
      unsigned long int EEG_Ch1_Data[150],EEG_Ch2_Data[150]; //optimize the use
      unsigned char datac[150];
      unsigned long ueegtemp = 0;
      signed long seegtemp=0;
      String data;
      int i;
      ecg()
      {
          ADS1292.ads1292_TestInit();  
          
      }
      // Member functions declaration
      String send_data()
      {
        if(SPI_RX_Buff_Count >= 9)
        {     
          pckt = 0; tmp1=0;   j2=0;   data="";
          for(i=0;i<SPI_RX_Buff_Count;i+=9) //bug that SPI_RX_Buff_Count should be multiple of 9 which should be true always almost
          {
            i+=3; //skip first 3 bytes (status bytes)
            //EEG_Ch1_Data[tmp1++]=  SPI_RX_Buff[i+0];
            //EEG_Ch1_Data[tmp1++]= SPI_RX_Buff[i+1];
            //EEG_Ch1_Data[tmp1++]= SPI_RX_Buff[i+2];
            EEG_Ch2_Data[j2++]= (unsigned char)SPI_RX_Buff[i+3];
            EEG_Ch2_Data[j2++]= (unsigned char)SPI_RX_Buff[i+4];
            EEG_Ch2_Data[j2++]= (unsigned char)SPI_RX_Buff[i+5];
          } 
            buff = 0;
            ueegtemp = (unsigned long) ((EEG_Ch2_Data[pckt]<<16)|(EEG_Ch2_Data[pckt+1]<<8)|EEG_Ch2_Data[pckt+2]);             
            ueegtemp = (unsigned long) (ueegtemp<<8);
            seegtemp = (signed long) (ueegtemp);
            seegtemp = (signed long) (seegtemp>>8); 
            data+=seegtemp;    
            data+="\n";
            SPI_RX_Buff_Count = 0;    
        }    
        return data;
      }
      
      void acquire_data()
      {
            //if((digitalRead(ADS1292_DRDY_PIN)) == LOW)
            //{  
                SPI_RX_Buff_Ptr = ADS1292.ads1292_Read_Data();
             //   Responsebyte = true; 
            //}
          
           // if(Responsebyte == true)
           // {
                for(i = 0; i < 9; i++)
                {
                    SPI_RX_Buff[SPI_RX_Buff_Count++] = *(SPI_RX_Buff_Ptr + i);
                }
            //    Responsebyte = false;
            //}

            if(SPI_RX_Buff_Count == buffersize-1) //flush if overflow
              flush();
            #ifdef debugecg
              //Serial.print("aquiring");
            #endif
      }

      void flush()
      {
         SPI_RX_Buff_Count = 0;
      }
};








