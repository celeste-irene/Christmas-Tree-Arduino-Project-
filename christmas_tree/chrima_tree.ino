
#include "notes.h"
// --- Timing control ---
const int BPM = 280;               // beats per minute
const int QUARTER = 60000 / BPM;   // 1 beat = 60000ms / BPM
const int HALF = QUARTER * 2;      // half note lasts 2 beats
const int FULL = QUARTER * 4;      // so on and so forth....
const int LONG = QUARTER * 6;
const int REST = 0;  

const unsigned int silence[] = {};
const unsigned int silence_dur[] = {};
//phrase 1
const unsigned int first_notes[]  = {g, e, g, a, e, g, g, a,
                                      a, a, b, a, f, d, b3};
//phrase 2
const unsigned int sec_notes[]    = {a, a, a, b, b, a, a, b, 
                                     g, e, g, gS, a, b3, c, c, c};
//youuuu will get a sentimental feeeeling
const unsigned int third_notes[]  = {a, gS, a, gS, a, f, f, a, b, g, e, g, b, b, 
                                      b, c5, b, c5, b, c5, a, b, c5, 
                                      d5, c5, b, a, g, a, b, a, g, g};

const unsigned int ending_notes[] = {g, e, g, a, e, g, g, a,
                                      a, a, b, a, f, d, b3, b3, b3, 
                                      a, a, a, b, b, a, a, b,
                                      g, e, g, gS, a, d5, c5};

const unsigned int first_dur[]    = {QUARTER, QUARTER, QUARTER, FULL, QUARTER, HALF, QUARTER, HALF, 
                                    HALF, QUARTER, HALF, HALF, QUARTER, HALF, LONG, HALF, QUARTER};

const unsigned int sec_dur[] = {QUARTER, QUARTER, HALF, HALF, HALF, QUARTER, HALF, HALF,
                                      HALF, QUARTER, HALF, HALF, HALF, QUARTER, LONG, HALF, QUARTER};

const unsigned int third_dur[] = {HALF, HALF, HALF, HALF, HALF, QUARTER, HALF, HALF, HALF, FULL, QUARTER, QUARTER, LONG, HALF,
                                    QUARTER, HALF, HALF, HALF, HALF, HALF, QUARTER, HALF, FULL,
                                    HALF, QUARTER, HALF, HALF, HALF, QUARTER, HALF, QUARTER, HALF, QUARTER };

const unsigned int ending_dur[] = {QUARTER, QUARTER, QUARTER, FULL, QUARTER, HALF, QUARTER, HALF, 
                                    HALF, QUARTER, HALF, HALF, QUARTER, HALF, LONG, HALF, QUARTER,
                                    QUARTER, QUARTER, HALF, HALF, HALF, QUARTER, HALF, HALF,
                                    HALF, QUARTER, FULL, FULL, FULL, FULL, LONG * 2};           
// Leds
int counter = 0;
int buzzerPin = 6;
int GreenLEDs_1 = 12; 
int GreenLEDs_2 = 9; 
int GreenLEDs_3 = 8;  
int RedLEDs_1 = 11;  
int RedLEDs_2 = 10;  
int OrangeLED = 13;    
int buttonPin = 2;                  

int buttonState = 0; //variable for reading pushbutton status

void buzzer_and_leds_setup()
{
  //Setup pin modes
  pinMode(buzzerPin, OUTPUT); //starting from top to bottom of chrima tree
  pinMode(OrangeLED, OUTPUT);
  pinMode(GreenLEDs_1, OUTPUT);
  // bottom part of chrima tree
  pinMode(GreenLEDs_2, OUTPUT);
  pinMode(GreenLEDs_3, OUTPUT);
  pinMode(RedLEDs_1, OUTPUT);
  pinMode(RedLEDs_2, OUTPUT);
  pinMode(buttonPin, INPUT_PULLUP);

}

void setup()
{
  // put your setup code here, to run once:
  Serial.begin(115200);
  while (Serial.available()) {}
  buzzer_and_leds_setup();
}

void loop()
{
  buttonState = digitalRead(buttonPin); //reading state of pushbutton
  if(buttonState == LOW)
  {
      // Play Rockin' Around the Chrima Tree
    play_song(first_notes, first_dur, sizeof(first_notes)/sizeof(int));
    play_song(sec_notes,   sec_dur,   sizeof(sec_notes)/sizeof(int));
    play_song(third_notes, third_dur, sizeof(third_notes)/sizeof(int));
    play_song(ending_notes, ending_dur, sizeof(ending_notes)/sizeof(int));
    delay(1000);
  } else 
  {
    play_song(0, 0, 0);
  }

}

void play_song(int notes[], unsigned int duration[], unsigned int arr_size)
{
  for (int i=0; i < arr_size; i++)
  {
    beep(notes[i], duration[i]);
  }
}

void beep(int note, int duration)
{
  //Play tone on buzzerPin
  tone(buzzerPin, note, duration);
  digitalWrite(GreenLEDs_2, HIGH); 
  digitalWrite(GreenLEDs_3, HIGH); 
  //Play different LED depending on value of 'counter'
  if(counter % 5 == 0)
  {
    digitalWrite(RedLEDs_1, HIGH);
    digitalWrite(RedLEDs_2, HIGH);
    delay(duration);
    digitalWrite(RedLEDs_1, LOW);
    digitalWrite(RedLEDs_2, LOW);

  }
  else if (counter % 5 == 1)
  {
    digitalWrite(RedLEDs_1, HIGH);
    digitalWrite(RedLEDs_2, HIGH);
    delay(duration);
    digitalWrite(RedLEDs_1, LOW);
    digitalWrite(RedLEDs_2, LOW);
  }
  else if (counter % 5 == 2)
  {
    digitalWrite(OrangeLED, HIGH);
    delay(duration);
  }
  else if (counter % 5 == 3)
  {
    digitalWrite(GreenLEDs_1, HIGH);
    delay(duration);
    digitalWrite(GreenLEDs_1, LOW);

  }
  else
  {
    delay(duration);
    digitalWrite(OrangeLED, LOW);
    digitalWrite(RedLEDs_2, LOW);
    digitalWrite(RedLEDs_1, LOW);
  }
  
  digitalWrite(GreenLEDs_1, LOW);
  digitalWrite(GreenLEDs_2, LOW); 
  digitalWrite(GreenLEDs_3, LOW); 
  //Stop tone on buzzerPin
  noTone(buzzerPin);
  
  //Increment counter
  counter++;
}



