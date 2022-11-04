/*
  Circuit Plkayground musical ornaments
  Plays a variety of Christmas and popular music on the piezo buzzer
  and flashes the 10 Neopixels of the Circuit Playground
  C. Richards 20201110

  Borrowed heavily from Arduino Mario Bros Tune With Piezo Buzzer and PWM by: Dipto Pratyaksa
  
*/

#include <Arduino.h>                      //for PlatformIO in VSCode
#include <Adafruit_Circuit_Playground.h>  //for neopixels
#include "pitches.h"                        //holds definition of buzzer frequencies for notes
#include "songs.h"                          //holds arrays of songs

#define NUMELEMENTS(x) (sizeof(x))/sizeof(x[0])   //to calculate length of struct elements
#define melodyPin 5                               //Circuit playground onbvoard LED and Buzzer Pin

void buzz(int, long, long);                               
void playSong(SONGS * matrix, int track, int duration);   

//define colors for neopixels
uint32_t christmas_colors[] = {
  0xFF0000,   
  0xFF2000,
  0xFFF800,
  0x00FF00,
  0x0000FF,
  0x2800FF,
  0xFF0050,
};
 
//collection of songs from mariobrothers
SONGS marioBros[] =
{
  {mario_melody, mario_tempo, NUMELEMENTS(mario_melody)},
  {underworld_melody, underworld_tempo, NUMELEMENTS(underworld_melody)},
};

//collection of christmas carols
/* SONGS christmas[] =
{
  {jingle_melody, jingle_tempo, NUMELEMENTS(jingle_melody)},
  {wish_melody, wish_tempo, NUMELEMENTS(wish_melody)},
  {helpfallinginlove_melody, helpfallinginlove_tempo, NUMELEMENTS(helpfallinginlove_melody)},
  {santaclaus_melody, santaclaus_tempo, NUMELEMENTS(santaclaus_melody)},
  {jinglebellrock_melody, jinglebellrock_tempo, NUMELEMENTS(jinglebellrock_melody)},
  {carolofthebells_melody, carolofthebells_tempo, NUMELEMENTS(carolofthebells_melody)},
  {herecomesthesun_melody, herecomesthesun_tempo, NUMELEMENTS(herecomesthesun_melody)},
  {melekalikimaka_melody, melekalikimaka_tempo, NUMELEMENTS(melekalikimaka_melody)}
}; */

SONGS christmas[] =
{
  {jingle_melody, jingle_tempo, NUMELEMENTS(jingle_melody)},
  {wish_melody, wish_tempo, NUMELEMENTS(wish_melody)},
  {helpfallinginlove_melody, helpfallinginlove_tempo, NUMELEMENTS(helpfallinginlove_melody)},
  {santaclaus_melody, santaclaus_tempo, NUMELEMENTS(santaclaus_melody)},
  {jinglebellrock_melody, jinglebellrock_tempo, NUMELEMENTS(jinglebellrock_melody)}
};

void setup(void)
{
  Serial.begin(9600);
  pinMode(5, OUTPUT);//buzzer
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(255);
}

void loop()
{
  //use the slide selector switch to choose different themes, ON for christmas
  if(CircuitPlayground.slideSwitch()){
    CircuitPlayground.clearPixels();
    for(int pixel = 0; pixel < 10; pixel++){            //set neoppixels to red and white for christmas
      if(pixel % 2 == 0){
        CircuitPlayground.setPixelColor(pixel, 0xFFFFFF);
      } else{
          CircuitPlayground.setPixelColor(pixel, 0xFF0000);
      }
    }
    for(int i = 0; i < 5; i++){
      playSong(christmas, i, 1000);
    } 
  //  Serial.println(NUMELEMENTS(christmas));
  //playSong(christmas, 2, 2000);

    //slide off for mariobros
  } else {
    CircuitPlayground.clearPixels();
    for(int pixel = 0; pixel < 10; pixel++){            //set neopixels to blue and green for mario
      if(pixel % 2 == 0){
        CircuitPlayground.setPixelColor(pixel, 0x0000FF);
      } else{
          CircuitPlayground.setPixelColor(pixel, 0x00FF00);
      }
    }
    playSong(marioBros, 1, 1000);
  }
};

//play track # from SONGS struct using duration multiplier for bpm
void playSong(SONGS *matrix, int track, int duration){
  for (int thisNote = 0; thisNote < matrix[track].size; thisNote++) {
    // to calculate the note duration, take one duration
    // divided by the note type.
    //e.g. quarter note = 1000 / 4, eighth note = 1000/8, etc.
    int noteDuration = duration/matrix[track].tempos[thisNote];

  CircuitPlayground.setBrightness(random(0, 255));        //change this to be a gradual ramp based on millis()
  CircuitPlayground.strip.show();

    buzz(melodyPin, matrix[track].melodies[thisNote],noteDuration);

    // to distinguish the notes, set a minimum time between them.
    // the note's duration + 30% seems to work well:
    int pauseBetweenNotes = noteDuration * 1.3;
    delay(pauseBetweenNotes);

    // stop the tone playing:
    buzz(melodyPin, 0, noteDuration);
  }
}

//PWM control on target pin at frequency hertz for length milliseconds
void buzz(int targetPin, long frequency, long length) {
  long delayValue = 1000000/frequency/2; // calculate the delay value between transitions
  //// 1 second's worth of microseconds, divided by the frequency, then split in half since
  //// there are two phases to each cycle
  long numCycles = frequency * length/ 1000; // calculate the number of cycles for proper timing
  //// multiply frequency, which is really cycles per second, by the number of seconds to 
  //// get the total number of cycles to produce
  for (long i=0; i < numCycles; i++){ // for the calculated length of time...
    digitalWrite(targetPin,HIGH); // write the buzzer pin high to push out the diaphram
    delayMicroseconds(delayValue); // wait for the calculated delay value
    digitalWrite(targetPin,LOW); // write the buzzer pin low to pull back the diaphram
    delayMicroseconds(delayValue); // wait again or the calculated delay value
  }
}
//