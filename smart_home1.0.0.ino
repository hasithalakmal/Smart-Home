/* Import Libraites */
#include <dht.h>
#include <IRremote.h>

/*call Libraies */
dht DHT;


/* PIN settings */
const int smokePin = A13; //Smoke sensor input pin
const int rainPin = A14; //Rain sensor input pin
const int ldrPin = A15;   //LDR sensor input pin
const int humidityPin = 50; //Humidity And Tempreture Sensor input pin
const int rellayfourPin = 48; //Relay output pin
const int rellaythreePin = 46; //Relay output pin
const int rellaytwoPin = 44; //Relay output pin
const int rellayonePin = 42; //Relay output pin
const int motionPin = 40; //Motion sensor input  pin
const int IRReceverPin = 38; //IR reciver input  pin
const int Sonar1echoPin = 36; //Motion sensor1 input  pin
const int Sonar1trigPin = 34; //Motion sensor1 input  pin
const int Sonar2echoPin = 32; //Motion sensor2 input  pin
const int Sonar2trigPin = 30; //Motion sensor2 input  pin
const int Sonar3echoPin = 28; //Motion sensor3 input  pin
const int Sonar3trigPin = 26; //Motion sensor3 input  pin
const int alarmbuzerPin = 24; //Motion sensor3 input  pin
const int moter1Pin1 = 51; //Moter 1 output pin
const int moter1Pin2 = 49; //Moter 1 output pin
const int moter1Pin3 = 47; //Moter 1 output pin
const int moter1Pin4 = 45; //Moter 1 output pin
const int moter2Pin1 = 43; //Moter 1 output pin
const int moter2Pin2 = 41; //Moter 1 output pin
const int moter2Pin3 = 39; //Moter 1 output pin
const int moter2Pin4 = 37; //Moter 1 output pin
const int led1PIN = 35; //LED 1 output pin
const int led2PIN = 33; //LED 2 output pin
const int led3PIN = 31; //LED 3 output pin
const int ACPIN = 29; //FAN output pin
const int led4PIN = 27; //LED 3 output pin


IRrecv irrecv(IRReceverPin);
decode_results results;

/*Controlling Value Settings*/
// constent for Rain Sensor - lowest and highest sensor readings:
const int sensorMin = 0;     // sensor minimum
const int sensorMax = 1024;  // sensor maximum

//moter 1 values
int Steps1 = 0;
boolean Direction1 = false;// gre
boolean motortRuningState1 = false;
unsigned long last_time1;
unsigned long currentMillis1 ;
int steps_left1 = 4095;
long time1;


//moter 2 values
int Steps2 = 0;
boolean Direction2 = false;// gre
boolean motortRuningState2 = false;
unsigned long last_time2;
unsigned long currentMillis2 ;
int steps_left2 = 4095;
long time2;









/* variable declaration */
int smoke_value = 0;
int rain_state = 0;
double humidity = 0;
double tempreture = 0;
int light_intensity = 0;
int motion = 0;
int IRCode = 0;
long sonar1Distence = 0;
long sonar2Distence = 0;
long sonar3Distence = 0;
boolean switch1 = false;
boolean switch2 = false;
boolean switch3 = false;
boolean switch4 = false;
boolean buzer = false;



/* Notified Situations */
boolean isFire = false;
boolean isRainy = false;
boolean isLetter = false;
boolean isWaterTankEmpty = false;
boolean isLokerOpen = false;
boolean isTooHumidity = false;
boolean isDark = false;
boolean isDoorOpen = false;
boolean isSwitch1on = false;
boolean isSwitch2on = false;
boolean isSwitch3on = false;
boolean isSwitch4on = false;


/* conditional Variables*/
int smoke_UB = 500;
int smoke_LB = 500;
int rain_UB = 1024;
int rain_LB = 1000;
int temp_FireB = 80;
int temp_ACB = 24;
int motionCounter = 10;
int letterBoxHeight = 5;
int waterTankdDepth = 5;
int lockerWidth = 5;
int humidityLevel = 50;
int lightIntencityLevel = 500;
int dorrOpenIRCode = 12803;
int dorrCloseIRCode = -9185;



void setup()
{
  //Initialize serial port - 9600 bps
  Serial.begin(9600);

  //set relly output pins
  pinMode(rellayfourPin, OUTPUT);
  digitalWrite(rellayfourPin, 1);
  pinMode(rellaythreePin, OUTPUT);
  digitalWrite(rellaythreePin, 1);
  pinMode(rellaytwoPin, OUTPUT);
  digitalWrite(rellaytwoPin, 1);
  pinMode(rellayonePin, OUTPUT);
  digitalWrite(rellayonePin, 1);

  //IR recever Start
  irrecv.enableIRIn();

  //Alarm buzzer
  pinMode(alarmbuzerPin, OUTPUT);
  digitalWrite(alarmbuzerPin, 1);

  //Moter PINs
  pinMode(moter1Pin1, OUTPUT);
  pinMode(moter1Pin2, OUTPUT);
  pinMode(moter1Pin3, OUTPUT);
  pinMode(moter1Pin4, OUTPUT);

  //Moter PINs
  pinMode(moter2Pin1, OUTPUT);
  pinMode(moter2Pin2, OUTPUT);
  pinMode(moter2Pin3, OUTPUT);
  pinMode(moter2Pin4, OUTPUT);

  //LEDS
  pinMode(led1PIN, OUTPUT);
  pinMode(led2PIN, OUTPUT);
  pinMode(led3PIN, OUTPUT);
  pinMode(led4PIN, OUTPUT);

  //FAN
  pinMode(ACPIN, OUTPUT);

}

void loop()
{
  //digitalWrite(35, HIGH);
  //testInputsAndOutputs(); // if you need to test uncomment this
  //update values
  smoke_value = getSmokeValue();
  rain_state = getRainState();
  humidity = getHumidity();
  tempreture = getTempreture();
  light_intensity = getLightIntensity();
  motion = getMotion(); //1 = no motion 0 = motion
  IRCode = getIRCode();
  sonar1Distence = getSonar1Value();
  sonar2Distence = getSonar2Value();
  sonar3Distence = getSonar3Value();

  //Zim 900 Changes This
  isSwitch1on = true;
  isSwitch3on = true;
  

  //pring input values
  Serial.print("Smoke Sensor Value = ");
  Serial.println(smoke_value);
  Serial.print("Rain State Value = ");
  Serial.println(rain_state);
  Serial.print("Humidity Sensor Value = ");
  Serial.println(humidity);
  Serial.print("Tempreture Sensor Value = ");
  Serial.println(tempreture);
  Serial.print("Light Intensity Value = ");
  Serial.println(light_intensity);
  Serial.print("Motion Sensor Value = ");
  Serial.println(motion);
  Serial.print("IR Code Value = ");
  Serial.println(IRCode);
  Serial.print("Sonar 1 Distence Value = ");
  Serial.println(sonar1Distence);
  Serial.print("Sonar 2 Distence Value = ");
  Serial.println(sonar2Distence);
  Serial.print("Sonar 3 Distence Value = ");
  Serial.println(sonar3Distence);

  fireDetection();
  RainDetection();
  MotionDetection();
  letterDetection();
  waterTankDetection();
  LockerDetection();
  ACControler();
  WorshipRoomLightController();
  RollerDoorController();
  switchController();


}



////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                                                                                          /////
/////                                                                                                          /////
/////                           Integration Layer                                                              /////
/////                                                                                                          /////
/////                                                                                                          /////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void fireDetection() {
  if (smoke_value > smoke_UB) {
    alarmOn();
    isFire = true;
  } else if (smoke_value < smoke_LB && tempreture < temp_FireB ) {
    alarmOff();
    isFire = false;
  }
}


void RainDetection() {
  if (rain_state > rain_UB && !isRainy ) {
    moter2Start();
    moter2Forword();
    delay(1000);
    moter2Strop();
    isRainy = true;
  } else if (rain_state == rain_LB  && isRainy) {
    moter2Start();
    moter2Backword();
    delay(1000);
    moter2Strop();
    isRainy = false;
  }
}

void MotionDetection() {
  //  if (motion == 0) {
  //    digitalWrite(35, HIGH);
  //    delay(3000);
  //  } else {
  //    digitalWrite(35, LOW);
  //  }

  //  if (motion == 0 && motionCounter <= 10) {
  //    motionCounter--;
  //    //digitalWrite(35, LOW);
  //  } else if (motion == 0 && motionCounter == 0) {
  //    motionCounter = 10;
  //    digitalWrite(35, LOW);
  //  } else if (motion == 1 && motionCounter == 10) {
  //    digitalWrite(35, HIGH);
  //  } else if (motion == 1 && motionCounter < 10) {
  //    motionCounter++;
  //    //digitalWrite(35, HIGH);
  //  }
}


void letterDetection() {
  if (sonar1Distence < letterBoxHeight ) {
    isLetter = true;
    digitalWrite(led1PIN, HIGH);
  } else {
    isLetter = false;
    digitalWrite(led1PIN, LOW);
  }
}

void waterTankDetection() {
  if (sonar2Distence < waterTankdDepth ) {
    isWaterTankEmpty = true;
    digitalWrite(led2PIN, HIGH);
  } else {
    isWaterTankEmpty = false;
    digitalWrite(led2PIN, LOW);
  }
}

void LockerDetection() {
  if (sonar3Distence < lockerWidth ) {
    isLokerOpen = true;
    digitalWrite(led3PIN, HIGH);
  } else {
    isLokerOpen = false;
    digitalWrite(led3PIN, LOW);
  }
}


void ACControler() {
  if (humidity < humidityLevel || tempreture > temp_ACB) {
    isTooHumidity = true;
    digitalWrite(ACPIN, HIGH);
  } else {
    isTooHumidity = false;
    digitalWrite(ACPIN, LOW);
  }
}

void WorshipRoomLightController() {
  if (light_intensity > lightIntencityLevel) {
    isDark = true;
    digitalWrite(led4PIN, HIGH);
  } else {
    isDark = false;
    digitalWrite(led4PIN, LOW);
  }
}

void RollerDoorController() {
  if (IRCode == dorrOpenIRCode && !isDoorOpen) {
    isDoorOpen = true;
    moter1Start();
    moter1Forword();
    delay(1000);
    moter1Strop();
    Serial.println(">>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>");
    digitalWrite(led3PIN, HIGH);
  } else if (IRCode == dorrCloseIRCode && isDoorOpen) {
    isDoorOpen = false;
    moter1Start();
    moter1Forword();
    delay(1000);
    moter1Strop();
    digitalWrite(led3PIN, LOW);
  }
}

void switchController() {
  if (isSwitch1on) {
    rellayOneOn();
  } else {
    rellayOneOff();
  }

  if (isSwitch2on) {
    rellayTwoOn();
  } else {
    rellayTwoOff();
  }

  if (isSwitch3on) {
    rellayThreeOn();
  } else {
    rellayThreeOff();
  }

  if (isSwitch4on) {
    rellayFourOn();
  } else {
    rellayFourOff();
  }
}

















































////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////                                                                                                          /////
/////                                                                                                          /////
/////  Sensor Data Detection & Output Controlling Layer                                                        /////
/////                                                                                                          /////
/////                                                                                                          /////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


void testInputsAndOutputs() {
  //variable declaration
  int smoke_value = 0;
  int rain_state = 0;
  double humidity = 0;
  double tempreture = 0;
  int light_intensity = 0;
  int motion = 0;
  int IRCode = 0;
  long sonar1Distence = 0;
  long sonar2Distence = 0;
  long sonar3Distence = 0;

  //update values
  smoke_value = getSmokeValue();
  rain_state = getRainState();
  humidity = getHumidity();
  tempreture = getTempreture();
  light_intensity = getLightIntensity();
  motion = getMotion(); //1 = no motion 0 = motion
  IRCode = getIRCode();
  sonar1Distence = getSonar1Value();
  sonar2Distence = getSonar2Value();
  sonar3Distence = getSonar3Value();

  //pring input values
  Serial.print("Smoke Sensor Value = ");
  Serial.println(smoke_value);
  Serial.print("Rain State Value = ");
  Serial.println(rain_state);
  Serial.print("Humidity Sensor Value = ");
  Serial.println(humidity);
  Serial.print("Tempreture Sensor Value = ");
  Serial.println(tempreture);
  Serial.print("Light Intensity Value = ");
  Serial.println(light_intensity);
  Serial.print("Motion Sensor Value = ");
  Serial.println(motion);
  Serial.print("IR Code Value = ");
  Serial.println(IRCode, HEX);
  Serial.print("Sonar 1 Distence Value = ");
  Serial.println(sonar1Distence);
  Serial.print("Sonar 2 Distence Value = ");
  Serial.println(sonar2Distence);
  Serial.print("Sonar 3 Distence Value = ");
  Serial.println(sonar3Distence);


  //Test outputvalues
  //  rellayOneOn();
  //  delay(1000);
  //  rellayOneOff();
  //  delay(1000);
  //
  //  rellayTwoOn();
  //  delay(1000);
  //  rellayTwoOff();
  //  delay(1000);
  //
  //  rellayThreeOn();
  //  delay(1000);
  //  rellayThreeOff();
  //  delay(1000);
  //
  //  rellayFourOn();
  //  delay(1000);
  //  rellayFourOff();
  //  delay(1000);
  //
  //  alarmOn();
  //  delay(3000);
  //  alarmOff();
  //
  //  moter1Start();
  //  moter1Forword();
  //  delay(1000);
  //  moter1Strop();
  //
  //    moter2Start();
  //    moter2Forword();
  //    delay(1000);
  //    moter2Strop();

  //extra
  delay(1000); // Print value every 1 sec.
}

/* Get Values from sensors */
int getSmokeValue() {
  return analogRead(smokePin);
}

int getRainState() {
  int sensorReading = analogRead(rainPin);
  return sensorReading;
}

int getLightIntensity() {
  return analogRead(ldrPin);
}

double getHumidity() {
  int chk = DHT.read11(humidityPin);
  return DHT.humidity;
}

double getTempreture() {
  int chk = DHT.read11(humidityPin);
  return DHT.temperature;
}

void rellayOneOn() {
  digitalWrite(rellayonePin, 0);
}
void rellayOneOff() {
  digitalWrite(rellayonePin, 1);
}

void rellayTwoOn() {
  digitalWrite(rellaytwoPin, 0);
}
void rellayTwoOff() {
  digitalWrite(rellaytwoPin, 1);
}

void rellayThreeOn() {
  digitalWrite(rellaythreePin, 0);
}
void rellayThreeOff() {
  digitalWrite(rellaythreePin, 1);
}

void rellayFourOn() {
  digitalWrite(rellayfourPin, 0);
}
void rellayFourOff() {
  digitalWrite(rellayfourPin, 1);
}

int getMotion() {
  return digitalRead(motionPin);
}

int getIRCode() {
  int res = 0;
  if (irrecv.decode(&results)) {
    res = results.value;
    irrecv.resume(); // Receive the next value
  }
  return res;
}

long getSonar1Value() {
  long duration, inches, cm;

  pinMode(Sonar1trigPin, OUTPUT);
  digitalWrite(Sonar1trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(Sonar1trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Sonar1trigPin, LOW);

  pinMode(Sonar1echoPin, INPUT);
  duration = pulseIn(Sonar1echoPin, HIGH);

  // convert the time into a distance
  inches = (duration / 74 / 2);
  cm = (duration / 29 / 2);
  return cm;
}

long getSonar2Value() {
  long duration, inches, cm;

  pinMode(Sonar2trigPin, OUTPUT);
  digitalWrite(Sonar2trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(Sonar2trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Sonar2trigPin, LOW);

  pinMode(Sonar2echoPin, INPUT);
  duration = pulseIn(Sonar2echoPin, HIGH);

  // convert the time into a distance
  inches = (duration / 74 / 2);
  cm = (duration / 29 / 2);
  return cm;
}

long getSonar3Value() {
  long duration, inches, cm;

  pinMode(Sonar3trigPin, OUTPUT);
  digitalWrite(Sonar3trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(Sonar3trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(Sonar3trigPin, LOW);

  pinMode(Sonar3echoPin, INPUT);
  duration = pulseIn(Sonar3echoPin, HIGH);

  // convert the time into a distance
  inches = (duration / 74 / 2);
  cm = (duration / 29 / 2);
  return cm;
}

void alarmOn() {
  digitalWrite(alarmbuzerPin, 0);
}

void alarmOff() {
  digitalWrite(alarmbuzerPin, 1);
}


void moter1Forword() {
  Direction1 = false;
  while (steps_left1 > 0 && motortRuningState1) {
    currentMillis1 = micros();
    if (currentMillis1 - last_time1 >= 1000) {
      stepper1(1);
      time1 = time1 + micros() - last_time1;
      last_time1 = micros();
      steps_left1--;
    }
  }
  steps_left1 = 4095;
}


void moter1Backword() {
  Direction1 = true;
  while (steps_left1 > 0 && motortRuningState1) {
    currentMillis1 = micros();
    if (currentMillis1 - last_time1 >= 1000) {
      stepper1(1);
      time1 = time1 + micros() - last_time1;
      last_time1 = micros();
      steps_left1--;
    }
  }
  steps_left1 = 4095;
}

void moter1Strop() {
  motortRuningState1 = false;
}

void moter1Start() {
  motortRuningState1 = true;
}


void moter2Forword() {
  Direction2 = false;
  while (steps_left2 > 0 && motortRuningState2) {
    currentMillis2 = micros();
    if (currentMillis2 - last_time2 >= 1000) {
      stepper2(1);
      time2 = time2 + micros() - last_time2;
      last_time2 = micros();
      steps_left2--;
    }
  }
  steps_left2 = 4095;
}


void moter2Backword() {
  Direction2 = true;
  while (steps_left2 > 0 && motortRuningState2) {
    currentMillis2 = micros();
    if (currentMillis2 - last_time2 >= 1000) {
      stepper2(1);
      time2 = time2 + micros() - last_time2;
      last_time2 = micros();
      steps_left2--;
    }
  }
  steps_left2 = 4095;
}

void moter2Strop() {
  motortRuningState2 = false;
}

void moter2Start() {
  motortRuningState2 = true;
}






/*Util Methods */
void stepper1(int xw) {
  for (int x = 0; x < xw; x++) {
    switch (Steps1) {
      case 0:
        digitalWrite(moter1Pin1, LOW);
        digitalWrite(moter1Pin2, LOW);
        digitalWrite(moter1Pin3, LOW);
        digitalWrite(moter1Pin4, HIGH);
        break;
      case 1:
        digitalWrite(moter1Pin1, LOW);
        digitalWrite(moter1Pin2, LOW);
        digitalWrite(moter1Pin3, HIGH);
        digitalWrite(moter1Pin4, HIGH);
        break;
      case 2:
        digitalWrite(moter1Pin1, LOW);
        digitalWrite(moter1Pin2, LOW);
        digitalWrite(moter1Pin3, HIGH);
        digitalWrite(moter1Pin4, LOW);
        break;
      case 3:
        digitalWrite(moter1Pin1, LOW);
        digitalWrite(moter1Pin2, HIGH);
        digitalWrite(moter1Pin3, HIGH);
        digitalWrite(moter1Pin4, LOW);
        break;
      case 4:
        digitalWrite(moter1Pin1, LOW);
        digitalWrite(moter1Pin2, HIGH);
        digitalWrite(moter1Pin3, LOW);
        digitalWrite(moter1Pin4, LOW);
        break;
      case 5:
        digitalWrite(moter1Pin1, HIGH);
        digitalWrite(moter1Pin2, HIGH);
        digitalWrite(moter1Pin3, LOW);
        digitalWrite(moter1Pin4, LOW);
        break;
      case 6:
        digitalWrite(moter1Pin1, HIGH);
        digitalWrite(moter1Pin2, LOW);
        digitalWrite(moter1Pin3, LOW);
        digitalWrite(moter1Pin4, LOW);
        break;
      case 7:
        digitalWrite(moter1Pin1, HIGH);
        digitalWrite(moter1Pin2, LOW);
        digitalWrite(moter1Pin3, LOW);
        digitalWrite(moter1Pin4, HIGH);
        break;
      default:
        digitalWrite(moter1Pin1, LOW);
        digitalWrite(moter1Pin2, LOW);
        digitalWrite(moter1Pin3, LOW);
        digitalWrite(moter1Pin4, LOW);
        break;
    }
    SetDirection1();
  }
}
void SetDirection1() {
  if (Direction1 == 1) {
    Steps1++;
  }
  if (Direction1 == 0) {
    Steps1--;
  }
  if (Steps1 > 7) {
    Steps1 = 0;
  }
  if (Steps1 < 0) {
    Steps1 = 7;
  }
}



void stepper2(int xw) {
  for (int x = 0; x < xw; x++) {
    switch (Steps2) {
      case 0:
        digitalWrite(moter2Pin1, LOW);
        digitalWrite(moter2Pin2, LOW);
        digitalWrite(moter2Pin3, LOW);
        digitalWrite(moter2Pin4, HIGH);
        break;
      case 1:
        digitalWrite(moter2Pin1, LOW);
        digitalWrite(moter2Pin2, LOW);
        digitalWrite(moter2Pin3, HIGH);
        digitalWrite(moter2Pin4, HIGH);
        break;
      case 2:
        digitalWrite(moter2Pin1, LOW);
        digitalWrite(moter2Pin2, LOW);
        digitalWrite(moter2Pin3, HIGH);
        digitalWrite(moter2Pin4, LOW);
        break;
      case 3:
        digitalWrite(moter2Pin1, LOW);
        digitalWrite(moter2Pin2, HIGH);
        digitalWrite(moter2Pin3, HIGH);
        digitalWrite(moter2Pin4, LOW);
        break;
      case 4:
        digitalWrite(moter2Pin1, LOW);
        digitalWrite(moter2Pin2, HIGH);
        digitalWrite(moter2Pin3, LOW);
        digitalWrite(moter2Pin4, LOW);
        break;
      case 5:
        digitalWrite(moter2Pin1, HIGH);
        digitalWrite(moter2Pin2, HIGH);
        digitalWrite(moter2Pin3, LOW);
        digitalWrite(moter2Pin4, LOW);
        break;
      case 6:
        digitalWrite(moter2Pin1, HIGH);
        digitalWrite(moter2Pin2, LOW);
        digitalWrite(moter2Pin3, LOW);
        digitalWrite(moter2Pin4, LOW);
        break;
      case 7:
        digitalWrite(moter2Pin1, HIGH);
        digitalWrite(moter2Pin2, LOW);
        digitalWrite(moter2Pin3, LOW);
        digitalWrite(moter2Pin4, HIGH);
        break;
      default:
        digitalWrite(moter2Pin1, LOW);
        digitalWrite(moter2Pin2, LOW);
        digitalWrite(moter2Pin3, LOW);
        digitalWrite(moter2Pin4, LOW);
        break;
    }
    SetDirection2();
  }
}
void SetDirection2() {
  if (Direction2 == 1) {
    Steps2++;
  }
  if (Direction2 == 0) {
    Steps2--;
  }
  if (Steps2 > 7) {
    Steps2 = 0;
  }
  if (Steps2 < 0) {
    Steps2 = 7;
  }
}








