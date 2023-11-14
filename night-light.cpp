int red_pin = 9;
int blue_pin = 10;
int green_pin = 11;

//you will need to determine the value for dark
//its unique to the lighting in your room
int dark_threshold = 30;

//int color_index = map(analogRead(A0), 0, 1023, 0, 5);

void turnoff(){
  analogWrite(red_pin, 0);
  analogWrite(blue_pin, 0);
  analogWrite(green_pin, 0);
}

enum ButtonStates{INIT,off, on} current_state;
void SM0_Tick() {
   // State Transistions
   switch(current_state) {
       case INIT:
     if (analogRead(A1) <= dark_threshold){
       current_state = on;
     }
     if (analogRead(A1) > dark_threshold){
       current_state = off;
     }
         break;
       case off:
     if (analogRead(A1) > dark_threshold){
       current_state = off;
     }
     if (analogRead(A1) <= dark_threshold){
       current_state = on;
     }
         //current_state = off;
         break;
       case on:
     if (analogRead(A1) <= dark_threshold){
       current_state = on;
     }
     if (analogRead(A1) > dark_threshold){
       current_state = off;
     }
         //current_state = on;
         break;
       default:
         current_state = off;
         break;
   }
   // State Actions
   switch(current_state) {
   	case INIT:
  //
      break;
    case off:
      turnoff();
      break;
    case on:
   //displays the color white
     if (analogRead(A0) >= 0 && analogRead(A0) <= 204){
       analogWrite(red_pin, 255);
       analogWrite(green_pin, 0);
       analogWrite(blue_pin, 0);
       //Serial.println("red");
     }
     if (analogRead(A0) >= 205 && analogRead(A0) <= 408){
       analogWrite(red_pin, 0);
       analogWrite(green_pin, 255);
       analogWrite(blue_pin, 0);
        //Serial.println("green");
     }
     if (analogRead(A0) >= 409 && analogRead(A0) <= 612){
       analogWrite(red_pin, 0);
       analogWrite(green_pin, 0);
       analogWrite(blue_pin, 255);
      //  Serial.println("blue");
     }
     if (analogRead(A0) >= 613 && analogRead(A0) <= 816){
       analogWrite(red_pin, 0);
       analogWrite(green_pin, 255);
       analogWrite(blue_pin, 255);
      //  Serial.println("cyan");
     }
     if (analogRead(A0) >= 817 && analogRead(A0) <= 1023){
       analogWrite(red_pin, 255);
       analogWrite(green_pin, 255);
       analogWrite(blue_pin, 0);
       //Serial.println("purple");
     }
   
      break;
   	default:
      break;
   }
}

void setup() {
  // put your setup code here, to run once:
  //color_index = map(analogRead(A0), 0, 1023, 0, 5);
  
  pinMode(red_pin, OUTPUT);
  pinMode(green_pin, OUTPUT);
  pinMode(blue_pin, OUTPUT);
  Serial.begin(9600);
  current_state = INIT;
}
void loop() {
  // put your main code here, to run repeatedly:
  
  SM0_Tick();
  //you can delete these prints if you want they are 
  //just here to show you the values of the 
  //potentiometer(A0) and the photoresistor(A1)
  Serial.print(analogRead(A0));
  
  Serial.print(' ');
  Serial.println(analogRead(A1));
  //DELETE THIS LINE OF CODE WHEN YOU MAKE YOUR SOLUTION
  //PLEASE DONT FORGET TO DELETE THE DELAY FUNCTION
  //its only there so you can see the transition from states
  //and so that your serial monitor is not spammed with values
}
