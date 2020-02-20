//global variables that are used throught multiple functions
//pins (counter and clockwise pins are correct)
int motorLocPin = 2; //buttonPIN
int motorLocState;//ButtonState
int counterPin = 4;
int clockwisePin = 6;
int motorEnablePin = 9; 
int limitSwitchPin = 8;

//motor location inputs and outputs
volatile int motorLoc;
int clockwiseVal = 0;
int counterVal = 1;

//how many clicks has the motor turned since it has gone home
int loc = 0;

//(probably) not important, not being used right now
int turnMax = 5;

//how many clicks until we get to a certiain location
int blueLoc = 11;
int redLoc = 10;
int whiteLoc = 8;
int boxLoc = 5;

//how long to wait to see if a signal is a correct signal
int timeToWait = 8;
//debounce delay

//are we currently looking at the first interrupt
//boolean firstSignal = true;
long deblast=0; //lastdebouncetime interrupt

//we are comparing future interrupts to this signal for this specific square wave
//int primaryInterrupt;
//ButtonState


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///Interrupts
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////

//interrupt function

void changeDirection() {
  //motorLocState=digitalRead(motorLocPin);
  if ((millis()-deblast)>timeToWait){
    loc++;
    deblast=millis();
  }
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///Main Functions
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  
  //setting up pins
  pinMode(motorLocPin, INPUT);
  pinMode(counterPin, OUTPUT);
  pinMode(clockwisePin, OUTPUT);
  pinMode(motorEnablePin, OUTPUT);
  pinMode(limitSwitchPin, INPUT);
  pinMode(LED_BUILTIN, OUTPUT);

  //assigning interrupts
  attachInterrupt(digitalPinToInterrupt(motorLocPin), changeDirection, CHANGE);

  digitalWrite(motorEnablePin, HIGH);

  //find home
  findHome();
}




void loop() { 
  //let it spin!!! the following 2 lines of code is (probably) the most important lines in the scketch
  
  findBlue();
  findHome();
  
  findRed();
  findHome();
  
  findWhite();
  findHome();
  
  findBox();
  findHome();
  
}



/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///Find Location
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void findHome () {
  //stop the motor
  motorStop();
  
  //turn until home found
  while ( digitalRead ( limitSwitchPin ) == LOW ) {
    motorCounter();
  }

  
  //stop!!
  motorStop();
  
  //set location to 0
  loc = 0;

  //go fowared
  motorClockwise();

  delay(5);

  //stop agian
  motorStop();
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///MOTOr movements
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void motorStop () {
  counterVal= 0;
  clockwiseVal = 0;
  digitalWrite(counterPin, counterVal);
  digitalWrite(clockwisePin, clockwiseVal);
}

void motorClockwise (){
  counterVal= 0;
  clockwiseVal = 1;
  digitalWrite(counterPin, counterVal);
  digitalWrite(clockwisePin, clockwiseVal);
}


void motorCounter (){
  counterVal= 1;
  clockwiseVal = 0;
  digitalWrite(counterPin, counterVal);
  digitalWrite(clockwisePin, clockwiseVal);
}


/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
///GOTO Location
/////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////
void findRed() {
  while ( loc <= redLoc ) {
    motorClockwise();
  }
  motorStop();
  Serial.println("Red Found");
  delay(1000);
}

void findBlue () {
  while ( loc <= blueLoc ) {
    motorClockwise();
  }
  Serial.println("Blue Found");
  motorStop();
  delay(1000);
}

void findWhite() {
  while ( loc <= whiteLoc ) {
    motorClockwise();
  }
  motorStop();
  Serial.println("White Found");
  delay(1000);
}

void findBox() {
  while ( loc <= boxLoc ) {
    motorClockwise();
  }
  motorStop();
  Serial.println("Box Found");
  delay(1000);
}

 




