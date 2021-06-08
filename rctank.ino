
// arduino - pwm pins 3, 5, 6, 9, 10, 11

const int CH_2_PIN = 11;

// driver pins
const int STBY_PIN = 3;

const int AIN1_PIN = 7;
const int AIN2_PIN = 6;
const int APWM_PIN = 5;

const int BIN1_PIN = 9;
const int BIN2_PIN = 8;
const int BPWM_PIN = 10;

const int deadzone = 20;  // the deadzone, where pumpkins like to be salted


void setup() {
  // pour yourself a bowl of serial
  Serial.begin(9600);
 
  //btw "AIN" means a in"
  pinMode(STBY_PIN, OUTPUT);
 
  pinMode(AIN1_PIN, OUTPUT);
  pinMode(AIN2_PIN, OUTPUT);
  pinMode(APWM_PIN, OUTPUT);

  pinMode(BIN1_PIN, OUTPUT);
  pinMode(BIN2_PIN, OUTPUT);
  pinMode(BPWM_PIN, OUTPUT);
 
}

void loop() {
  int ch_2 = pulseIn(CH_2_PIN, HIGH, 25000);
  ch_2 = pulseToPWM(ch_2);
  drive(ch_2, ch_2);
}


int pulseToPWM(int pulse) {

  if ( pulse > 1000 ) {

    pulse = map(pulse, 1034, 1836, -500, 500);
   

    pulse = constrain(pulse, -255, 255);
  } else {
    // set pulse to zero
    pulse = 0;
  }

  if ( abs(pulse) <= deadzone ) {
    pulse = 0;
  }
 
  return pulse;
}


void drive(int speed_a, int speed_b) {

  // Limit speed between -255 and 255
  speed_a = constrain(speed_a, -255, 255);
  speed_b = constrain(speed_b, -255, 255);

  if ( speed_a == 0 ) {
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, LOW);
  } else if ( speed_a > 0 ) {
    digitalWrite(AIN1_PIN, HIGH);
    digitalWrite(AIN2_PIN, LOW);
  } else {
    digitalWrite(AIN1_PIN, LOW);
    digitalWrite(AIN2_PIN, HIGH);
  }

  if ( speed_b == 0 ) {
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, LOW);
  } else if ( speed_b > 0 ) {
    digitalWrite(BIN1_PIN, HIGH);
    digitalWrite(BIN2_PIN, LOW);
  } else {
    digitalWrite(BIN1_PIN, LOW);
    digitalWrite(BIN2_PIN, HIGH);
  }

  Serial.print("speed_a: ");
  Serial.println(speed_a);
  Serial.print("speed_b: ");
  Serial.println(speed_b);
  analogWrite(APWM_PIN, abs(speed_a));
  analogWrite(BPWM_PIN, abs(speed_b));
}
