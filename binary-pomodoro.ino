#define ZERO_BIT 3
#define ONES_BIT 4
#define TWOS_BIT 5
#define THREES_BIT 6
#define FOURS_BIT 7
#define REST_PIN 9
#define BUZZER 12

unsigned long now;
unsigned long last;
unsigned long delta;
long timer;
bool isRest = false;
const long FOCUS_TIME_MILLIS = 10 * 1000L; //10 sec for quick demos
const long REST_TIME_MILLIS = 5 * 1000L; //5 sec for quick demos
int greenBrightness = 0;
int buzzTimer = 0;

void setup() {
  pinMode(ZERO_BIT, OUTPUT);
  pinMode(ONES_BIT, OUTPUT);
  pinMode(TWOS_BIT, OUTPUT);
  pinMode(THREES_BIT, OUTPUT);
  pinMode(FOURS_BIT, OUTPUT);
  pinMode(REST_PIN, OUTPUT);
  pinMode(BUZZER, OUTPUT);

  timer = FOCUS_TIME_MILLIS;
  last = millis();
}

void loop() {
  now = millis();
  delta = now - last;
  last = now;

  timer = timer - delta;
  long secs = timer / 1000L;
  //long mins = secs / 60L;
  long mins = secs;

  bool zeroBitSet = (mins & 1) == 1;
  bool onesBitSet = (mins & 2) == 2;
  bool twosBitSet = (mins & 4) == 4;
  bool threesBitSet = (mins & 8) == 8;
  bool foursBitSet = (mins & 16) == 16;

  digitalWrite(FOURS_BIT, foursBitSet ? HIGH : LOW);
  digitalWrite(THREES_BIT, threesBitSet ? HIGH : LOW);
  digitalWrite(TWOS_BIT, twosBitSet ? HIGH : LOW);
  digitalWrite(ONES_BIT, onesBitSet ? HIGH : LOW);
  digitalWrite(ZERO_BIT, zeroBitSet ? HIGH : LOW);

  if (buzzTimer > 0) {
    digitalWrite(BUZZER, HIGH);
    buzzTimer -= delta;
  } else {
    digitalWrite(BUZZER, LOW);
  }

  if (timer <= 0) {
    buzzTimer = 2 * 1000L; //buzz for 2 seconds

    if (isRest) { //back to work
      timer = FOCUS_TIME_MILLIS;
      isRest = false;
      greenBrightness = 0;
      analogWrite(REST_PIN, 0);
    } else { //time to rest
      timer = REST_TIME_MILLIS;
      isRest = true;
      analogWrite(REST_PIN, 255);
    }
  }

}
