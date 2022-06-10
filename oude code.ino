int MicroswitchMEM = 0;  // Geheugen om de stand van de Microswitch te onthouden
int Microswitch = 2;     // De microswitch zit aangesloten op PIN 2
int BumperReset = 3;     // De reset voor de bumper zit aangesloten op PIN 3
int REDPIN = 10;         // Rood zit aangesloten op PIN 9
int GREENPIN = 9;        // Groen zit aangesloten op PIN 10
int BLUEPIN = 11;        // Blauw zit aangesloten op PIN 11
const int trigPin = 12;  // Trig zit aangesloten op PIN 12
const int echoPin = 13;  // Echo zit aangesloten op PIN 13

long duration;  // Tijd in microsecondes gedetecteerd door de ultrasoon sensor
int distance;   // De afstand in cm van de ultrasoon sensor tot het gedetecteerde voorwerp


void setup() {
  pinMode(Microswitch, INPUT_PULLUP);  // Veranderd de Microswitch naar een Input
  pinMode(BumperReset, INPUT);         // veranderd de BumperReset knop naar een Input
  pinMode(trigPin, OUTPUT);            // Veranderd de trigPin naar een Output
  pinMode(echoPin, INPUT);             // Veranderd de echoPin naar een Input
  Serial.begin(9600);                  // Starts the serial communication
}


void loop() {

  // ULTRASOON GEDEELTE


  digitalWrite(trigPin, LOW);  // Schakelt de trigPin uit
  delay(2);
  digitalWrite(trigPin, HIGH);  // Schakelt de trigPin aan voor 10 micro secondes
  delay(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);  // Leest de echoPin van de ultrasoon sensor, dit is gelijk aan de de tijd van de geluidsgolf in microsecondes
  distance = duration * 0.034 / 2;    // Het omrekenen van duration naar afstand in cm
  Serial.print("Distance: ");         // Geeft de afstand weer op de Serial Monitor
  Serial.println(distance);
  Serial.println(MicroswitchMEM);



  // RESPONSE GEDEELTE

  if (digitalRead(Microswitch) == HIGH) {  // Schakelt de rode Leds in en de blauwe Leds uit als de gemeten afstand lager dan 30 is
    RodeLeds();
    MicroswitchMEM = 1;
  } else if (MicroswitchMEM == 0) {
    GroeneLeds();
  }

  if (distance < 30) {  // Schakelt de rode Leds in en de blauwe Leds uit als de gemeten afstand lager dan 30 is
    RodeLeds();
  } else if (MicroswitchMEM == 0) {
    GroeneLeds();
  }

  if (MicroswitchMEM == 1 && digitalRead(BumperReset) == HIGH) {
    MicroswitchMEM = 0;
  }




  // einde void loop
}



void RodeLeds() {
  analogWrite(REDPIN, 255);
  analogWrite(BLUEPIN, 0);
}
void GroeneLeds() {
  analogWrite(REDPIN, 0);  // Schakelt de blauwe Leds in en de rode Leds uit als de gemeten afstand niet lager dan 30 is
  analogWrite(BLUEPIN, 255);
}