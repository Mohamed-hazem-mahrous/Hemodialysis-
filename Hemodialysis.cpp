byte statusLed = 13;

byte sensorInterrupt = 0;  // 0 = digital pin 2
byte sensorPin = 8;

float calibrationFactor = 4.5;

volatile byte pulseCount;

float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;

unsigned long oldTime;

// Define color sensor pins
#define S0 4
#define S1 5
#define S2 6
#define S3 10
#define sensorOut 9
#define buzzerPin 12

// Variables for Color Pulse Width Measurements
int redPW = 0;
int greenPW = 0;
int bluePW = 0;



void setup() {

pinMode(2,INPUT);

pinMode(7,OUTPUT);

	// Set S0 - S3 as outputs
	pinMode(S0, OUTPUT);
	pinMode(S1, OUTPUT);
	pinMode(S2, OUTPUT);
	pinMode(S3, OUTPUT);

	// Set Pulse Width scaling to 20%
	digitalWrite(S0,HIGH);
	digitalWrite(S1,LOW);
  pinMode(buzzerPin, OUTPUT);

	// Set Sensor output as input
	pinMode(sensorOut, INPUT);


Serial.begin(9600);
  // Set up the status LED line as an output
  pinMode(statusLed, OUTPUT);
  digitalWrite(statusLed, HIGH);  // We have an active-low LED attached

  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);

  pulseCount = 0;
  flowRate = 0.0;
  flowMilliLitres = 0;
  totalMilliLitres = 0;
  oldTime = 0;

  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);


}


void loop() {

  if (digitalRead(2) == 1)

{
  digitalWrite(7,HIGH);
}  


else{

    digitalWrite(7,LOW);

    }
if ((millis() - oldTime) > 1000)  // Only process counters once per second
  {
    detachInterrupt(sensorInterrupt);

    flowRate = (((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor) * 1000.0;
    oldTime = millis();

    // Print the flow rate for this second in milliliters / minute
    Serial.print("Flow rate: ");
    Serial.print(flowRate);  // Print the flow rate in milliliters per minute
    Serial.print(" ml/min");
    Serial.print("\n");  // Print tab space

    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;

    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }
	redPW = getRedPW();
	greenPW = getGreenPW();
	bluePW = getBluePW();

  if (bluePW > 200 && greenPW > 200) {
    // Add your desired action here, for example, activating the buzzer
    digitalWrite(buzzerPin, HIGH);
    delay(1000);  // Buzzer activation time (adjust as needed)
    digitalWrite(buzzerPin, LOW);
	Serial.print("WARNNING: Blood leakage");
	Serial.print("\n");

  }

}

/*
Insterrupt Service Routine
 */
void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;

}

// Function to read Red Pulse Widths
int getRedPW() {
	// Set sensor to read Red only
	digitalWrite(S2,LOW);
	digitalWrite(S3,LOW);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Green Pulse Widths
int getGreenPW() {
	// Set sensor to read Green only
	digitalWrite(S2,HIGH);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;
}

// Function to read Blue Pulse Widths
int getBluePW() {
	// Set sensor to read Blue only
	digitalWrite(S2,LOW);
	digitalWrite(S3,HIGH);
	// Define integer to represent Pulse Width
	int PW;
	// Read the output Pulse Width
	PW = pulseIn(sensorOut, LOW);
	// Return the value
	return PW;

}
