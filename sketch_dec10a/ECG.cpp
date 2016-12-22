#include "ads1292r.h"
#define buffersize 3000
class ecg {
   public:
      ads1292r ADS1292;
      byte SPI_RX_Buff[buffersize];
      int SPI_RX_Buff_Count = 0;
      char *SPI_RX_Buff_Ptr;
     // int Responsebyte = false;
      unsigned int j2=0;
      unsigned long int EEG_Ch1_Data[3],EEG_Ch2_Data[3]; 
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
        data="";
        if(SPI_RX_Buff_Count >= 9)
        {     
          for(i=0;i<SPI_RX_Buff_Count;i+=9) //bug that SPI_RX_Buff_Count should be multiple of 9 which should be true always almost
          {
            //i+=6; //dont modify i instead directly get a byte
            j2=0; 
            
            EEG_Ch2_Data[j2++]= (unsigned char)SPI_RX_Buff[i+6];
            EEG_Ch2_Data[j2++]= (unsigned char)SPI_RX_Buff[i+7];
            EEG_Ch2_Data[j2++]= (unsigned char)SPI_RX_Buff[i+8];
            
            ueegtemp = (unsigned long) ((EEG_Ch2_Data[0]<<16)|(EEG_Ch2_Data[1]<<8)|EEG_Ch2_Data[2]);             
            ueegtemp = (unsigned long) (ueegtemp<<8);
            seegtemp = (signed long) (ueegtemp);
            seegtemp = (signed long) (seegtemp>>8); 
            
            data+=seegtemp;    
            data+="\n";
            
          }
            SPI_RX_Buff_Count = 0;    
        }    
        return data;
      }
      
      void ICACHE_RAM_ATTR acquire_data()
      {
           SPI_RX_Buff_Ptr = ADS1292.ads1292_Read_Data();
           
           if(!(SPI_RX_Buff_Count < buffersize-1)) //flush if overflow
              flush();
              
           for(i = 0; i < 9; i++)
           {
               SPI_RX_Buff[SPI_RX_Buff_Count++] = *(SPI_RX_Buff_Ptr + i);
           }
      }

      void flush()
      {
         SPI_RX_Buff_Count = 0;
      }
};








