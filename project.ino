#define MOTOR_R0 8
#define MOTOR_R1 9
#define MOTOR_L0 10
#define MOTOR_L1 11

// Directions
void forward(){
  	digitalWrite(MOTOR_R1, LOW);
  	digitalWrite(MOTOR_L1, LOW);
	digitalWrite(MOTOR_L0, HIGH);
	digitalWrite(MOTOR_R0, HIGH);
}
void backward(){
	digitalWrite(MOTOR_L0, LOW);
	digitalWrite(MOTOR_R0, LOW);
	digitalWrite(MOTOR_R1, HIGH);
	digitalWrite(MOTOR_L1, HIGH);
}
void left(){
	digitalWrite(MOTOR_L0, LOW);
	digitalWrite(MOTOR_L1, LOW);
	digitalWrite(MOTOR_R1, LOW);
	digitalWrite(MOTOR_R0, HIGH);
}
void right(){
	digitalWrite(MOTOR_L1, LOW);
	digitalWrite(MOTOR_R0, LOW);
	digitalWrite(MOTOR_R1, LOW);
	digitalWrite(MOTOR_L0, HIGH);
}
void idle(){
	digitalWrite(MOTOR_L0, LOW);
	digitalWrite(MOTOR_L1, LOW);
	digitalWrite(MOTOR_R0, LOW);
	digitalWrite(MOTOR_R1, LOW);
}



void setup(){
	Serial.begin(115200);
	pinMode(13, OUTPUT);
	digitalWrite(13, LOW);

	pinMode(MOTOR_L0, OUTPUT);
	pinMode(MOTOR_L1, OUTPUT);
	pinMode(MOTOR_R0, OUTPUT);
	pinMode(MOTOR_R1, OUTPUT);

        idle();
}

void loop(){
  	if(Serial.available() > 0){
	  	switch(Serial.read()){
	  	case 'u':
	  		forward();
	  		digitalWrite(13, HIGH);
	  		break;
	  	case 'd':
	  		backward();
	  		digitalWrite(13, HIGH);
	  		break;
	  	case 'l':
	  		left();
	  		digitalWrite(13, HIGH);
	  		break;
	  	case 'r':
	  		right();
	  		digitalWrite(13, HIGH);
	  		break;
	  	default:
	  		idle();
	  		digitalWrite(13, LOW);
	  		break;
	  	}

	}
}
