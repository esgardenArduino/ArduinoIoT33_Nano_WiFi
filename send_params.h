/*************************************************************************************/
/** GARDEN NAME AND ID_NODE **********************************************************/
/*************************************************************************************/

//CONFIGURATION: NAME OF YOUR GARDEN; use the same name than in your APP or Application
String  GARDEN = " "; //Name of target garden
//END CONFIGURATION

String PLOTLIST[] = {"Testing", "General", "Nursery", "Compost","plot 1", "plot 2", "plot 3", "plot 4", "plot 5", "plot 6", "plot 7"};

#define ID_NODE "05" // an example: this code insertes values in the nursery space

/*Note.- "Testing" is unused in the APP project. Just for testing issues, don't remove ******/

// 01: "General"
// 02: "Nursery"
// 03: "Compost"
// 04: "Plot 1"
// 05: "Plot 2"
// 06: "Plot 3"
// 07: "Plot 4"
// 08: "Plot 5"
// 09: "Plot 6"
// 0A: "Plot 7"
// 0B: "Plot 8"

/************************************************************************************/
/** We must send a HEX string as follows:
 *  Characters 0,1: ID_NODE
 *  Nested string of tuples: TYPE + FIELD
 *  Where TYPE is 2 characters long; FIELD is 4 characters long
 ************************************************************************************/

#define SizeBuffer 64 // This example sends 4 sensor values (4x4 + 4x2); MAX 64; multiple of 4

/*************************************************************************************/
/** TYPES OF SENSORS SUPPORTED BY THE APP ********************************************/
/** For other purposes different than the APP, you can add or change values***********/
/*************************************************************************************/

#define INI_DATA 0
#define LON_TYPE 2
#define LON_VALUE 4

/***** TYPES ARE DEFINED IN THE APP; BE COHERENT *****************/
/***** THIS LIST CORRESPONDS WITH eSGarden APP PROJECT **********/
 
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

const int quantityOfVal[10] = {1,1,1,1,1,1,1,2,4,4}; //number of data read per sensor; for example, wind => force & direction
