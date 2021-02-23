/*************************************************************************************/
/** Implement your read sensor functions here ****************************************/
/*************************************************************************************/
#include "dht.h"
dht DHT; //Include your libraries 


int readCO2(int pin); // air quality value
int readDHT_t (int pin); // ambient temperature
int readDHT_h (int pin); // ambient humidity
int readBgt (int pin); // brightness
int readW_f (int pin); // wind force
int readW_d (int pin); // wind direction
int readWLevel (int pin); // water level in a pluviometer
int readSoilHum (int pin); //soil moisture


/************** BASIC READING FUNCTION  Example **************************************/
//int ReadSensor(int pin) {
 // int output_value = analogRead(pin); //analog or digital; remove and make your own function here
 // return output_value; //change the return by int or float
//}
/************** AD-HOC READING FUNCTIONS **********************************************/


/****** CO2 sensor: air quality; 1 value *********************************************/
int readCO2(int pin) {
  
}

/****** DHT11 sensor: temperature; 1 value *******************************************/
int readDHT_t (int pin) {
  
}

/****** DHT11 sensor: humidity; 1 value *********************************************/
int readDHT_h (int pin) {
 
}

/****** Brightness detection sensor: lux; 1 value *********************************/
int readBgt (int pin) {
    

/****** Wind sensor: force; 1 value *************************************************/
int readW_f (int pin) {
  
}

/****** Wind sensor: direction; 1 value *********************************************/
int readW_d (int pin) {
  
}

/****** Pluviometric sensor: level; 1 value *********************************************/
int readWLevel (int pin) {
    
}
  /****** Soil moisture sensor: humidity; 1 value *********************************************/
int readSoilHum (int pin) {
  
}
