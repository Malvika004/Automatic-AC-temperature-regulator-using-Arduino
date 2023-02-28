#include <SimpleDHT.h>                                      //Library for DHT 11
#include <IRLibSendBase.h>                                  //Library for IR LED
#include <IRLib_HashRaw.h>
#include <PCD8544.h>                                        //Library for LCD 



static PCD8544 lcd;                                         // setting up lcd

int pinDHT11 = 2;                                           // locating data pin for DHT11

int ACOnStatus = 0;                                         // on = 0, off = 1
int ACmode = 0;                                             // cool = 1, dry = 2, fan = 3
int ACTemp = 00;


SimpleDHT11 dht11(pinDHT11);                                // object for the dht11

IRsendRaw mySender;                                         // object for ir led;

// ir code data for the DAIKIN  AC


//on
#define RAW_DATA_LEN 100
uint16_t rawDataOn[RAW_DATA_LEN]={
  3466, 1670, 466, 1258, 430, 442, 414, 458, 
  482, 390, 474, 1250, 474, 398, 430, 442, 
  426, 470, 378, 490, 378, 1350, 374, 498, 
  370, 1354, 370, 1358, 366, 502, 370, 1358, 
  366, 1358, 366, 1358, 370, 1358, 366, 1358, 
  370, 502, 366, 506, 366, 1358, 370, 502, 
  366, 506, 366, 506, 366, 506, 366, 506, 
  366, 502, 370, 1358, 366, 1358, 366, 1358, 
  366, 1358, 370, 502, 366, 506, 366, 506, 
  366, 506, 366, 506, 366, 506, 366, 502, 
  370, 502, 370, 502, 366, 506, 366, 506, 
  366, 506, 366, 506, 366, 506, 366, 526, 
  346, 530, 338, 1000};
  
//off
#define RAW_DATA_LEN 100
uint16_t rawDataOff[RAW_DATA_LEN]={
  3482, 1654, 478, 1246, 478, 394, 474, 398, 
  462, 410, 434, 1290, 434, 438, 430, 442, 
  426, 470, 374, 494, 374, 1350, 374, 498, 
  374, 1354, 370, 1358, 366, 502, 370, 1358, 
  366, 1358, 366, 1358, 366, 1358, 370, 1358, 
  366, 502, 370, 502, 370, 1358, 366, 506, 
  366, 502, 370, 502, 370, 502, 366, 506, 
  366, 506, 366, 1358, 366, 1362, 366, 1358, 
  366, 1358, 366, 506, 366, 506, 366, 506, 
  366, 502, 366, 506, 366, 530, 342, 506, 
  366, 506, 362, 530, 342, 506, 366, 530, 
  342, 530, 342, 530, 342, 530, 342, 530, 
  342, 526, 342, 1000};


//25
#define RAW_DATA_LEN 100
uint16_t rawData25[RAW_DATA_LEN]={
  3410, 1726, 414, 1310, 482, 390, 486, 386, 
  482, 390, 474, 1250, 466, 406, 430, 438, 
  406, 490, 378, 494, 374, 1350, 374, 498, 
  370, 1354, 370, 1354, 370, 502, 366, 1358, 
  370, 1358, 366, 1358, 366, 1358, 370, 1354, 
  370, 502, 366, 506, 366, 1358, 366, 506, 
  366, 502, 370, 502, 366, 506, 366, 506, 
  366, 506, 366, 1358, 366, 1358, 366, 1358, 
  366, 1358, 366, 506, 370, 502, 366, 506, 
  366, 506, 366, 502, 370, 502, 366, 506, 
  366, 506, 366, 506, 366, 502, 370, 502, 
  366, 506, 366, 510, 362, 506, 366, 506, 
  366, 526, 342, 1000};


//28
#define RAW_DATA_LEN 100
uint16_t rawData28[RAW_DATA_LEN]={
  3486, 1654, 482, 1242, 482, 390, 470, 402, 
  434, 434, 434, 1290, 406, 466, 402, 470, 
  402, 490, 378, 494, 374, 1350, 374, 498, 
  374, 1354, 370, 1354, 370, 502, 370, 1358, 
  370, 1354, 370, 1354, 370, 1358, 366, 1358, 
  366, 506, 366, 502, 370, 1358, 366, 502, 
  370, 502, 370, 502, 366, 502, 370, 502, 
  370, 502, 370, 1354, 370, 1358, 366, 1358, 
  370, 1358, 366, 506, 366, 502, 370, 502, 
  370, 502, 370, 502, 370, 502, 366, 506, 
  366, 506, 366, 502, 370, 502, 370, 502, 
  370, 502, 366, 506, 366, 502, 370, 502, 
  370, 502, 370, 1000};




#define RAW_DATA_LEN 100
uint16_t rawDataDry[RAW_DATA_LEN]={
  3482, 1650, 486, 1242, 442, 426, 434, 438, 
  430, 442, 402, 1318, 402, 470, 402, 470, 
  398, 498, 374, 494, 374, 1354, 370, 498, 
  370, 1354, 370, 1354, 370, 502, 370, 1354, 
  366, 1358, 366, 1358, 366, 1358, 370, 1354, 
  366, 506, 366, 502, 370, 1354, 370, 502, 
  366, 502, 370, 502, 370, 502, 370, 502, 
  366, 506, 366, 1358, 366, 1358, 366, 1354, 
  370, 1358, 366, 502, 370, 502, 366, 506, 
  366, 502, 370, 502, 370, 502, 366, 506, 
  366, 502, 370, 502, 366, 506, 366, 502, 
  370, 502, 366, 506, 366, 502, 370, 502, 
  366, 506, 366, 1000};

//cool`
#define RAW_DATA_LEN 100
uint16_t rawDataCool[RAW_DATA_LEN]={
  3462, 1674, 434, 1290, 410, 462, 478, 394, 
  482, 390, 470, 1254, 474, 398, 430, 438, 
  406, 466, 402, 494, 374, 1350, 374, 498, 
  370, 1354, 370, 1354, 370, 502, 370, 1358, 
  366, 1358, 366, 1358, 366, 1358, 370, 1358, 
  366, 502, 370, 502, 370, 1358, 366, 502, 
  366, 506, 366, 506, 366, 502, 370, 502, 
  366, 506, 366, 1358, 366, 1358, 366, 1362, 
  366, 1358, 366, 506, 366, 502, 370, 502, 
  370, 502, 366, 506, 366, 506, 366, 502, 
  370, 502, 366, 506, 366, 506, 366, 506, 
  362, 506, 366, 506, 366, 506, 366, 506, 
  366, 526, 342, 1000};

//fan
#define RAW_DATA_LEN 100
uint16_t rawDataFan[RAW_DATA_LEN]={
  3486, 1646, 486, 1238, 486, 386, 482, 394, 
  470, 394, 474, 1250, 438, 434, 406, 466, 
  402, 494, 374, 494, 374, 1350, 374, 498, 
  370, 1354, 370, 1354, 370, 502, 370, 1354, 
  370, 1354, 370, 1354, 370, 1354, 366, 1358, 
  366, 502, 370, 502, 370, 1358, 366, 502, 
  366, 502, 370, 502, 366, 506, 366, 502, 
  370, 502, 370, 1354, 370, 1354, 366, 1362, 
  366, 1358, 366, 502, 366, 506, 366, 506, 
  366, 502, 370, 502, 366, 506, 366, 502, 
  366, 506, 366, 506, 366, 502, 370, 502, 
  366, 506, 366, 506, 366, 502, 366, 506, 
  366, 506, 366, 1000};

 
void setup() {
  
  lcd.begin(84, 48);
  
  //dht11
  Serial.begin(9600);

  //LED
   pinMode(13, OUTPUT);


  mySender.send(rawDataOn,RAW_DATA_LEN,36);                                 //turn on the AC using IR LED
  ACOnStatus = 0;
  mySender.send(rawDataCool,RAW_DATA_LEN,36);
  ACmode = 0;
}
    
void loop() {

   
  
  byte temperature = 0;
  byte humidity = 0;
  int err = SimpleDHTErrSuccess;
  if ((err = dht11.read(&temperature, &humidity, NULL)) != SimpleDHTErrSuccess) {
    Serial.print("Read DHT11 failed, err="); Serial.print(SimpleDHTErrCode(err));
    Serial.print(","); Serial.println(SimpleDHTErrDuration(err)); delay(1000);
    return;
  }
  int temp = (int)temperature;
  int hum = (int)humidity;

  
  // DHT11 sampling rate is 1HZ.
  delay(1500);


 
  
  
  lcd.setCursor(0, 0);
  lcd.print(String("Starting") );
  delay(1000);
  
  lcd.setCursor(0, 1);
  lcd.print(String("Temp: ")+String(temp) + String("*C"));
    lcd.setCursor(0, 2);
   lcd.print(String("Humidity: ")+String(hum) + String("%")); 
  lcd.setCursor(0, 3);
  if(ACmode == 1){
  lcd.print(String("AC Mode : Cooling "));
  }
  else if(ACmode == 2){
    lcd.print(String("AC Mode : Dry   "));
  }
  else if (ACmode ==3){
    lcd.print(String("AC Mode : Fan   "));
  }
  else{
    lcd.print(String("AC Mode : ---   "));
  }
  lcd.setCursor(0, 4);
  if(ACOnStatus == 1){
    lcd.print(String("AC Status: On   "));
  }
  else{
    lcd.print(String("AC Status:Off    "));
  }
  
// Code for obtaining optimum settings 


if(ACOnStatus == 1){                                                              //AC is On
  if(ACmode == 1){                                                                //cooling mode - controls temperature
       if(temp > 30){
                if(hum>60){
                  mySender.send(rawData28,RAW_DATA_LEN,36);                       //set temp to 25
                  ACTemp = 28;
                  mySender.send(rawDataDry,RAW_DATA_LEN,36);                      //Dry mode
                  ACmode= 2;
                }
                else if(hum<40){
                   mySender.send(rawDataOff,RAW_DATA_LEN,36);                     //AC off
                  ACOnStatus = 0;               
                }
                else {                                                            // humidity between 40 and 60
                  mySender.send(rawData25,RAW_DATA_LEN,36);                       //set temp to 25
                   ACTemp = 25;                   
                }
       }
       else if(temp < 20){
             
             mySender.send(rawDataOff,RAW_DATA_LEN,36);                           //AC off
                  ACOnStatus = 0;    
       }
       else{ // temp between 20 and 30
              if(hum>60){
                 mySender.send(rawData28,RAW_DATA_LEN,36);                        //set temp to 28
                  ACTemp = 28;
                  mySender.send(rawDataDry,RAW_DATA_LEN,36);                      //Dry mode
                  ACmode= 2;
              }
              else if(hum<40){
                   mySender.send(rawDataOff,RAW_DATA_LEN,36);                     //AC off
                  ACOnStatus = 0; 
              }
              else{ // humidity between 40 and 60
                 mySender.send(rawDataFan,RAW_DATA_LEN,36);                       //Fan mode
                  ACmode = 3;                 
              }
       }
  }                                                                               //end of cooling mode

  

  else if(ACmode == 2){                                                           // dry mode - reduces humidity
    if(hum<40){
       mySender.send(rawDataOff,RAW_DATA_LEN,36);                                 //AC off
                  ACOnStatus = 0; 
    }
    else if(hum > 60){
       mySender.send(rawData28,RAW_DATA_LEN,36);                                  //set temp to 28
        ACTemp = 28;
    }
    else{
       mySender.send(rawDataFan,RAW_DATA_LEN,36);                                 // Fan mode is on
                  ACmode = 3; 
    }
  }                                                                               // end of dry mode

  

  else if(ACmode == 3){                                                           // fan mode is on - maintains temperature and humidity
      if( temp> 30){
        mySender.send(rawDataCool,RAW_DATA_LEN,36);                               //AC off
                  ACmode = 1; 
         mySender.send(rawData25,RAW_DATA_LEN,36);                                //set temp to 25
          ACTemp = 25;
      }
      else if(temp<20){
         mySender.send(rawDataOff,RAW_DATA_LEN,36);                               //AC off
                  ACOnStatus = 0; 
      }
      else{
        if(hum > 60){
           mySender.send(rawData28,RAW_DATA_LEN,36);                              // set temp to 28
           ACTemp = 28;
           mySender.send(rawDataDry,RAW_DATA_LEN,36);                             //AC dry mode
                  ACmode = 2; 
        }
        else if(hum<40){
             mySender.send(rawDataOff,RAW_DATA_LEN,36);                           //AC off
                  ACOnStatus = 0; 
        }
        else {// maintains same optimum conditions
        }
      }
  }                                                                                // end of dry node
  
}                                                                                  // end of AC on


else {                                                                             // if AC is off
   if(temp >30){
               mySender.send(rawDataOn,RAW_DATA_LEN,36);                           //AC on
                  ACOnStatus = 1; 
                mySender.send(rawData25,RAW_DATA_LEN,36);                          // set temp to 25
               ACTemp = 25;
   }
   else if(temp<20){
                 // maintain optimum conditions
   }
   else{
              if(hum<40){
                        // maintain optimum conditions
              }
              else if(hum>60){
                mySender.send(rawDataOn,RAW_DATA_LEN,36);                            //AC off
                  ACOnStatus = 1;
                mySender.send(rawDataCool,RAW_DATA_LEN,36);                          //AC cooling mode
                  ACmode = 1;    
              }
              else{
                mySender.send(rawDataOn,RAW_DATA_LEN,36);                            //AC on
                  ACOnStatus = 1;
                  mySender.send(rawDataFan,RAW_DATA_LEN,36);                         //AC Fan mode
                  ACmode = 3;  
              }
              
   }
     
}// end of if 

  
  
  
  delay(200);
 
  digitalWrite(13, HIGH);  
      lcd.setCursor(0, 0);
  lcd.print(String("  delay  ") );
  delay(10*1000  );              
  digitalWrite(13, LOW);   
  delay(1000); 
}