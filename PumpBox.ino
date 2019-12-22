// Set up the global variables linked to the number of level sensors
const byte nblevels = 3;
byte levels[nblevels];
byte empt=0,low,med,hi;
// Set up of global variables linked to the current sensor
const int currentPin = A0; // which pin for ACS712
int mVperAmp = 185; // Which kind of ACS712 use 185 fro 5A Module, 100 for 20A Module, 66 for 30A Module



void setup() {
  // Set up of levels id might need to be reworked
  levels[0] = 2;
  levels[1] = 3;
  levels[2] = 4;
  low = levels[0]; //2
  med = low + levels[1]; //5
  hi = med + levels[2]; //9

  // Init pin level sensors
  for (int i = 2; i < nblevels+2; i++) {
    pinMode(i, INPUT);
  }
  // Init Serial
  Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
  Serial.println(getLevel());
  delay(2000);
}

byte getLevel() {
  // Check the levels qnd give back a value
  byte level = 0;
  for (int i = 2; i < nblevels+2; i++) {
    level += levels[i-2]*digitalRead(i);
  }
  return level;
}

float getAmpere()
{
  double AmpsRMS;

  int readValue;             //value read from the sensor
  int maxValue = 0;          // store max value here
  int minValue = 1024;          // store min value here
  uint32_t start_time = millis();
  while((millis()-start_time) < 1000) //sample for 1 Sec
  {
    readValue = analogRead(currentPin);
    // see if you have a new maxValue
    if (readValue > maxValue)
    {
      /*record the maximum sensor value*/
      maxValue = readValue;
    }
    if (readValue < minValue)
    {
      /*record the maximum sensor value*/
      minValue = readValue;
    }
  }

  // Subtract min from max
  AmpsRMS = ((((maxValue - minValue) * 5.0)/1024.0)/2*0.707)*1000/mVperAmp;
  return AmpsRMS;
}
