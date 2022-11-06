/*
  Circuit Playground musical ornaments
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

const int PACE = 5000;          //scale factor that handles time between songs and other timings 

//void buzz(int, long, long);                               
void playSong(SONGS * matrix, int track); 

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
  {mario_melody, mario_tempo, NUMELEMENTS(mario_melody), 666},
  {underworld_melody, underworld_tempo, NUMELEMENTS(underworld_melody), 1600},
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
  {jingle_melody, jingle_tempo, NUMELEMENTS(jingle_melody),550},
  {wish_melody, wish_tempo, NUMELEMENTS(wish_melody), 420},
  {helpfallinginlove_melody, helpfallinginlove_tempo, NUMELEMENTS(helpfallinginlove_melody), 800},
  {santaclaus_melody, santaclaus_tempo, NUMELEMENTS(santaclaus_melody), 800},
  {jinglebellrock_melody, jinglebellrock_tempo, NUMELEMENTS(jinglebellrock_melody), 500}
};

bool newSong;           //flag to handle when a new song is playing
SONGS *songPlaying;     //pointer to current playing song
uint32_t conductor = 0; //timer for note duration
int noteDuration;       //length of current note in ms
int currentNote;        //frequency value of current note

void setup(void)
{
  Serial.begin(9600);
  while (!Serial){}
  pinMode(5, OUTPUT);//buzzer
  CircuitPlayground.begin();
  CircuitPlayground.setBrightness(255);
  Serial.println("Setup complete");
  newSong = 1;
}

void loop()
{
/*   playSong(marioBros, 1);
  delay(5000);
 */

  songPlaying = &marioBros[1];

  if(newSong)
  {
    currentNote = 0;
    noteDuration = songPlaying->beat_ms / (int )pgm_read_word_near(&(songPlaying->tempos[currentNote]));
    newSong = 0;
  }

  //play the next note in the sequence only when it has been long enough since the last note started
  if(millis() - conductor > noteDuration * 1.3)
  {
    conductor = millis();
    noteDuration = songPlaying->beat_ms / (int )pgm_read_word_near(&(songPlaying->tempos[currentNote]));
    tone(melodyPin, (int ) pgm_read_word_near(&(songPlaying->melodies[currentNote])), noteDuration);
    currentNote++;
    if(currentNote > songPlaying->size)
    {
      newSong = 1;
      delay(PACE);
    }
  }
}

/*
//play track # from SONGS struct
void playSong(SONGS *matrix, int track){
  int note, tempo;




   for (int thisNote = 0; thisNote < matrix[track].size; thisNote++) {
    //read note and tempo from PROGMEM
    note = (int ) pgm_read_word_near(&(matrix[track].melodies[thisNote]));
    tempo = (int) pgm_read_word_near(&(matrix[track].tempos[thisNote]));

    int noteDuration = matrix[track].beat_ms/tempo; //whole note ms duration divided by note length from tempo

    tone(melodyPin, note, noteDuration);
    int pauseBetweenNotes = noteDuration * 1.3;     //differentiates the notes. some delay is required or program gets confused?
    delay(pauseBetweenNotes);
    //delay(50);
  }
}*/