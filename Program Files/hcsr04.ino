// defines pins numbers
const int trigPin_left = 6;
const int echoPin_left = 7;
const int trigPin_front = 2;
const int echoPin_front = 3;
const int trigPin_right = 4;
const int echoPin_right = 5;

const int mRight1 = 11;
const int mRight2 = 10;
const int mLeft1 = 8;
const int mLeft2 = 9;

int took_turn=0;
char data = 0;
// defines variables
long duration_front, duration_left, duration_right;
int distance_front, distance_left, distance_right;
void setup() {
pinMode(trigPin_front, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin_front, INPUT); // Sets the echoPin as an Input
pinMode(trigPin_left, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin_left, INPUT); // Sets the echoPin as an Input
pinMode(trigPin_right, OUTPUT); // Sets the trigPin as an Output
pinMode(echoPin_right, INPUT); // Sets the echoPin as an Input
pinMode(13, OUTPUT);

Serial.begin(9600); // Starts the serial communication
}
void loop() {
  /***********for front sensor**********/
// Clears the trigPin
digitalWrite(trigPin_front, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin_front, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin_front, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds

duration_front = pulseIn(echoPin_front, HIGH);
// Calculating the distance
distance_front = duration_front*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("Distance Front: ");
//Serial.println(distance_front);

/*********for left sensor************/
digitalWrite(trigPin_left, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin_left, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin_left, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds

duration_left = pulseIn(echoPin_left, HIGH);
// Calculating the distance
distance_left = duration_left*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("Distance Left: ");
//Serial.println(distance_left);

/*********for right sensor************/
digitalWrite(trigPin_right, LOW);
delayMicroseconds(2);
// Sets the trigPin on HIGH state for 10 micro seconds
digitalWrite(trigPin_right, HIGH);
delayMicroseconds(10);
digitalWrite(trigPin_right, LOW);
// Reads the echoPin, returns the sound wave travel time in microseconds

duration_right = pulseIn(echoPin_right, HIGH);
// Calculating the distance
distance_right = duration_right*0.034/2;
// Prints the distance on the Serial Monitor
//Serial.print("Distance Right: ");
//Serial.println(distance_right);


if(distance_front>30 && took_turn==0){
  //follow bluetooth instruction 
  if(Serial.available() > 0)      // Send data only when you receive data:
   {
      data = Serial.read();        //Read the incoming data & store into data
      //Serial.print(data);          //Print Value inside data in Serial monitor
      //Serial.print("\n");        
      if(data == 'B'){              // Checks whether value of data is equal to 1
        forward();
      }
      else if(data == 'X'){
        backward();
        
      }
      else if(data == 'Y'){
        right();
      }
      else if(data == 'A'){
        left();
      }
      else{
        wait();  
      }
   }
}
else if(distance_front < 30 && (distance_left > 100 || distance_right > 100) && took_turn==0){
    if(distance_left > 150){
          Serial.println("left-right-forward");
          left();
          delay(500);
          forward();
          delay(2000);
          right();
          delay(500);
          forward();
          delay(500);
          wait();
      }
    else if(distance_right > 150){
          Serial.println("right-left-forward");
          right();
          delay(500);
          forward();
          delay(2000);
          left();
          delay(500);
          forward();
          delay(500);
          wait();
      }
}
/*else if(distance_front < 20 && distance_left < 100 && distance_right < 100 && took_turn == 0){
        Serial.println("right 90deg");
        right();
        delay(4000);
        wait();
        took_turn=1;
}
else if(distance_front > 20 && distance_left < 20 && took_turn == 1){
        Serial.println("forward");
        forward();
}
else if(distance_left > 20 && took_turn == 1){
      Serial.println("left");
      left();
      delay(4000);
      wait();
      took_turn = 0;
}
else if(distance_front < 20 && took_turn == 1){
    Serial.println("180 deg");
    rotate();
    delay(4000);
    wait();
    took_turn=2;
}
else if(distance_front > 20 && distance_right < 20 && took_turn == 2){
     Serial.println("forward");
     forward();
}
else if(distance_right > 20 && took_turn == 2){
      Serial.println("right");
      right();
      delay(4000);
      wait();
      took_turn = 0;
}
else if(distance_front < 20 && took_turn == 2){
    Serial.println("left-return");
    left();
    delay(4000);
    wait();
    took_turn = 0;  
}*/
}









void forward(){
  digitalWrite(mRight1, HIGH);   
  digitalWrite(mRight2, LOW);
  digitalWrite(mLeft1, HIGH);
  digitalWrite(mLeft2, LOW);
}

void backward(){
  digitalWrite(mRight2, HIGH);
  digitalWrite(mRight1, LOW);
  digitalWrite(mLeft2, HIGH);
  digitalWrite(mLeft1, LOW);  
}

void right(){
  digitalWrite(mRight1, LOW);
  digitalWrite(mRight2, LOW);
  digitalWrite(mLeft1, HIGH);
  digitalWrite(mLeft2, LOW);  
}

void left(){
  digitalWrite(mRight1, HIGH);
  digitalWrite(mRight2, LOW);
  digitalWrite(mLeft1, LOW);
  digitalWrite(mLeft2, LOW); 
}

void rotate(){
  digitalWrite(mRight1, LOW);
  digitalWrite(mRight2, HIGH);
  digitalWrite(mLeft1, HIGH);
  digitalWrite(mLeft2, LOW);   
}

void wait(){
  digitalWrite(mRight1, LOW);  
  digitalWrite(mRight2, LOW);
  digitalWrite(mLeft1, LOW);
  digitalWrite(mLeft2, LOW);  
}
