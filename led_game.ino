//www.elegoo.com
//2016.12.9 

int tDelay = 250;
int latchPin = 11;      // (11) ST_CP [RCK] on 74HC595
int clockPin = 9;      // (9) SH_CP [SCK] on 74HC595
int dataPin = 12;     // (12) DS [S1] on 74HC595

int left = 6;
int enter = 8;
int right = 4;

int correct = 2;
int wrong = 13;

byte leds = 0;

void updateShiftRegister()
{
   digitalWrite(latchPin, LOW);
   shiftOut(dataPin, clockPin, MSBFIRST, leds);
   digitalWrite(latchPin, HIGH);

}

void setup() 
{
  Serial.begin(9600);
  pinMode(latchPin, OUTPUT);
  pinMode(dataPin, OUTPUT);  
  pinMode(clockPin, OUTPUT);
  pinMode(left, INPUT_PULLUP);
  pinMode(enter, INPUT_PULLUP);
  pinMode(right, INPUT_PULLUP);

  pinMode(correct, OUTPUT);
  pinMode(wrong, OUTPUT);
  randomSeed(analogRead(1));
}


int i = 0;
int lit = 0;
int randNumber = 0;
int myLeds[4];

void choose_led()
{
  for (int d = 0; d <= 3; d++)
  {
    randNumber = random(8);
    myLeds[d] = randNumber;
    Serial.println(randNumber);
    
  } 

}

int mySensVals[5] = {2, 4, -8, 3, 2};

int check = true;
int needed = 0;
int guess = 0;


void loop() 
{
  leds = 0;
  choose_led();
 

  for (int l = 0; l <= 3; l++)
  {
    Serial.println(myLeds[l]);
    lit = myLeds[l];
    bitSet(leds, lit);
    updateShiftRegister();
    delay(500);
    bitClear(leds, lit);
    updateShiftRegister();
    delay(500);
  }

  Serial.println();
  i = 0;
  for (int l = 0; l <= 3; l++)
  {
    
    needed = myLeds[l];
    check = true;
    while (check)
    {

      bitSet(leds , i);
      updateShiftRegister();

      if (digitalRead(left) == LOW)
      {    
        Serial.println("done");
        delay(tDelay);

        bitClear(leds, i);
        updateShiftRegister();

        i = i -1;
        guess = i;

      }

      if (digitalRead(right) == LOW)
      {
        delay(tDelay);
        bitClear(leds, i);
        updateShiftRegister();

        i = i + 1;
        guess = i;

      }

      if (digitalRead(enter) == LOW)     
      {
        delay(tDelay);

        if(guess == needed)
        {
          Serial.println("correct");
          digitalWrite(correct, HIGH);
          delay(700);
          digitalWrite(correct, LOW);
          check = false;
        }
        else if(guess != needed)
        {
          Serial.println("wrong");
          digitalWrite(wrong, HIGH);
          delay(700);
          digitalWrite(wrong, LOW);
        }
      }


    }
  }
  delay(1000);

 


}

