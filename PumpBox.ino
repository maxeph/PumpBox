const byte nblevels = 3;
byte levels[nblevels];
byte empt=0,low,med,hi;

void setup() {
  // Set up of levels id
  levels[0] = 2;
  levels[1] = 3;
  levels[2] = 6;
  low = levels[0];
  med = low + levels[1];
  hi = med + levels[2];
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
  byte level = 0;
  for (int i = 2; i < nblevels+2; i++) {
    level += levels[i-2]*digitalRead(i);
  }
  return level;
}
