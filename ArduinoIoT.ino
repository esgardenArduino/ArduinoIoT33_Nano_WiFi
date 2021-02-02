#include "send_params.h"
#include "sensor_functions.h"
#include "send_firebase.h"

#include "ArduinoJson.h"

String Readvalues (void);    //Read sensor values MODIFY!!
void MakeJSON (String recv); //Make JSON with sensor values
int GetInteger(String from); //Auxiliary function
float GetDouble(String from); //Auxiliary function

/**** Define a doc structure for JSON  ***************/
DynamicJsonDocument doc(1024);


/*****************************************************/
/************ ARDUINO  SET-UP ************************/
/*****************************************************/

void setup() {
  pinMode(LED_BUILTIN, OUTPUT);
  Serial.begin(9600);
  doc.clear();
  while (!Serial) {
    ; 
  }
    Serial.println("HELLO....connecting WiFi");
    StartFirebase(); //Enable or disable this line to send data to Firebase real-time database
    Serial.println("HELLO....connected");
}


void loop() {
  
 while (1) { 

    // blinking orage LED:
    digitalWrite(LED_BUILTIN, HIGH);
  
   /***************************************************************/
   /******* READ THE VALUES OF YOUR SENSORS **********************/
   /**************************************************************/
       
   String strvalues;
   strvalues = Readvalues();
   Serial.println(" Making .....  ");
   MakeJSON (strvalues);
   Serial.println(" Sending .....  ");
 
   /***************************************************************/
   /******* SEND VALUES TO FIREBASE ******************************/
   /**************************************************************/

   String JsonSerialized;
   serializeJson(doc, JsonSerialized);
   Serial.println(JsonSerialized);

   int id_node = GetInteger(ID_NODE);
   String route = "/Gardens/"+GARDEN+"/sensorData/"+PLOTLIST[id_node]+"/Data/";
   //Serial.println(SendFirebase(route, JsonSerialized));
  
   doc.clear(); // VERY IMPORTANT; don't remove
  
  /******************************************************************************************/
  /** Wait for a time before reading again **************************************************/
  /******************************************************************************************/
   Serial.println(" Waiting ...."); //Checking line
   digitalWrite(LED_BUILTIN, LOW);
   unsigned long int waitMS = 60000; // Change this value; idle time
   delay (waitMS);
   Serial.println(" Awake again! ..."); //Checking line

 }

}
/********************************************************************************************/
/** Modify this function depending on your sensors ******************************************/
/** DATA is assume as integer ***************************************************************/
/********************************************************************************************/
/************* READ YOUR SENSORS  ****************************************************/

String Readvalues (void){

  // TYPE 00: Brightness - 1 value
  // TYPE 01: Temperature - 1 value
  // TYPE 02: Humidity - 1 value
  // TYPE 03: PH - 1 value
  // TYPE 04: Relative noise - 1 value
  // TYPE 05: Air Quality - 1 value
  // TYPE 06: Rainfall - 1 value
  // TYPE 07: Wind - 2 values
  // TYPE 08: Soil temperature - 4 values
  // TYPE 09: Soil humidity - 4 values

  char buffvalues[SizeBuffer];
  char * Data_buffer_ptr =  buffvalues;
  int j = 0;
  /******* Build an HEX string with TYPE+FIELD tuples **********/

  //sprintf((Data_buffer_ptr + j), "%02X", 00); // TYPE 00
  //j = j + 2;
  //sprintf((Data_buffer_ptr + j), "%01f", readBgt (A0)); //Brightness
  //j = j + 4;

/************ EXAMPLE OF FLOAT SENDING **************************/
  sprintf((Data_buffer_ptr + j), "%02X", 01); // TYPE 01
  j = j + 2;
  sprintf((Data_buffer_ptr + j), "%01f", pruebas (A0)); //Temperature
  j = j + 4;
  Serial.println(pruebas (A0));

  sprintf((Data_buffer_ptr + j), "%02X", 02); // TYPE 02
  j = j + 2;
  sprintf((Data_buffer_ptr + j), "%01f", readDHT_h (A0)); //Humidity
  j = j + 4;

  //sprintf((Data_buffer_ptr + j), "%02X", 03); // TYPE 03
  //j = j + 2;
  //sprintf((Data_buffer_ptr + j), "%01f", readPH (A0)); //PH
  //j = j + 4;

  //sprintf((Data_buffer_ptr + j), "%02X", 04); // TYPE 04
  //j = j + 2;
  //sprintf((Data_buffer_ptr + j), "%01f", readNoise (A0)); //Noise
  //j = j + 4;

  //sprintf((Data_buffer_ptr + j), "%02X", 05); // TYPE 05
  //j = j + 2;
  //sprintf((Data_buffer_ptr + j), "%01f", readCO2 (A0)); //Air quality
  //j = j + 4;
  
  //sprintf((Data_buffer_ptr + j), "%02X", 06); // TYPE 06
  //j = j + 2;
  //sprintf((Data_buffer_ptr + j), "%01f", readWLevel (A0)); //Noise
  //j = j + 4;
  
  //sprintf((Data_buffer_ptr + j), "%02X", 07); // TYPE 07
  //j = j + 2;
  //sprintf((Data_buffer_ptr + j), "%01f", readWf (A0)); //Wind force  
  //j = j + 4;  
  //sprintf((Data_buffer_ptr + j), "%01f", readWd (A0)); //Wind direction
  //j = j + 4;
  
  //sprintf((Data_buffer_ptr + j), "%02X", 08); // TYPE 08
  //j = j + 2;
  //sprintf((Data_buffer_ptr + j), "%01f", readSoilTem (A0)); //Soil temperature
  //j = j + 4;
  
  //sprintf((Data_buffer_ptr + j), "%02X", 09); // TYPE 09
  //j = j + 2;
  //sprintf((Data_buffer_ptr + j), "%01f", readSoilHum (A0)); //Soil humidity
  //j = j + 4;

  Serial.print(" Buffer filled .....  ");
  Serial.println(buffvalues);
  Serial.println(" ");
  String strvalue (buffvalues);
  Serial.println (strvalue);
  return strvalue;
  
} // End Readvalues


/*** Fill the JSON structure with your sensor values **/
void MakeJSON(String recv){

  JsonObject dataSlot;
  JsonArray slot; 

  int id_node = GetInteger(ID_NODE);
  doc["ID_Node"]  =  id_node; 
  doc["timestamp"] = serialized("{\".sv\":\"timestamp\"}");
  
  int index = 0;
  int charsPassed = 0;
  int type = 255;
  while(recv.length() >= (charsPassed +6)){   
    String str = "DATASLOT_";
    str.concat(index++);
    int posIni = INI_DATA + charsPassed; 
    int posFin = posIni + LON_TYPE;
    type = GetInteger(recv.substring(posIni,posFin)); 
    charsPassed += LON_TYPE;
    dataSlot = doc.createNestedObject(str);
    dataSlot["Type"] = GetInteger(recv.substring(posIni,posFin));
    slot = dataSlot.createNestedArray("Value");
    for(int i = 0; i<quantityOfVal[type]; i++){
       posIni = posFin;
       posFin = posFin + LON_VALUE;
       slot.add(GetDouble(recv.substring(posIni,posFin)));
       //slot.add(recv.substring(posIni,posFin));
       charsPassed += LON_VALUE;
    }    
  }

  
}// End MakeJSON


int GetInteger(String from){
   char FIELDCHAR[5];
   from.toCharArray(FIELDCHAR, 5);
   return strtol(FIELDCHAR, NULL, 16);
   
} //End GetInteger

float GetDouble(String from){
   char FIELDCHAR[5];
   from.toCharArray(FIELDCHAR, 5);
   return strtod(FIELDCHAR, NULL);
   
} //End GetInteger
