const int LDR_PIN = A0;
const int LED_PIN = 9;

const float EMA_ALPHA = 0.08;
const uint16_t LOOP_MS = 30;
const int PWM_DEADBAND = 2;
const uint8_t SLEW_MAX = 4;

const int STARTUP_LEARN_MS = 5000;
const int TRACK_MARGIN = 10;

float filt = 0;
int pwm = 0, prevPwm = 0;
unsigned long t0;

int learnMin = 1023;
int learnMax = 0;

void setup() {
  pinMode(LED_PIN, OUTPUT);
  Serial.begin(115200);

  TCCR1B = (TCCR1B & 0b11111000) | 0x01;

  int x = analogRead(LDR_PIN);
  filt = x;
  learnMin = x;
  learnMax = x;
  t0 = millis();
}

void loop() {
  static unsigned long last = 0;
  unsigned long now = millis();
  if (now - last < LOOP_MS) return;
  last = now;

  int raw = analogRead(LDR_PIN);
  filt = filt + EMA_ALPHA * (raw - filt);
  int adc = (int)filt;

  bool fastLearn = (now - t0 < STARTUP_LEARN_MS);
  if (adc < learnMin) learnMin = adc;
  if (adc > learnMax) learnMax = adc;

  if (!fastLearn) {
    learnMin = min(learnMin, adc);
    learnMax = max(learnMax, adc);
  }

  int lo = max(0, learnMin - TRACK_MARGIN);
  int hi = min(1023, learnMax + TRACK_MARGIN);

  if (hi - lo < 10) { lo = max(0, adc - 50); hi = min(1023, adc + 50); }

  long mapped = map(adc, lo, hi, 255, 0);
  int targetPwm = (int)constrain(mapped, 0, 255);

  if (abs(targetPwm - prevPwm) <= PWM_DEADBAND) {
    targetPwm = prevPwm;
  }
  if (targetPwm > prevPwm)      pwm = min(prevPwm + SLEW_MAX, targetPwm);
  else if (targetPwm < prevPwm) pwm = max(prevPwm - SLEW_MAX, targetPwm);
  else                          pwm = prevPwm;

  analogWrite(LED_PIN, pwm);
  prevPwm = pwm;

  Serial.print("ADC=");  Serial.print(adc);
  Serial.print("  LO="); Serial.print(lo);
  Serial.print("  HI="); Serial.print(hi);
  Serial.print("  PWM=");Serial.println(pwm);
}
