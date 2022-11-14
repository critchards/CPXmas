/*
  Circuit Playground musical ornaments
  Plays a variety of Christmas and popular music on the piezo buzzer
  and flashes the 10 Neopixels of the Circuit Playground
  Borrowed heavily from Arduino Mario Bros Tune With Piezo Buzzer and PWM by: Dipto Pratyaksa
  Note: I had some issues with being unable to upload firmware. If that happens you have to reset the bootloader
    at just the right time during the upload process. Watch the terminal output for when it mentions "searching for port"
    then hit the RESET button twice to force a new com connection. If it doesnt work and you get an error about being
    unable to connect just try uploading again and repeat until you get the timing right.
  C. Richards 20221106 - Refactored to use Tone(), statemachines, more songs
  C. Richards 20201110 - Initial creation, intended for charity craft fair, not complete
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
 
//collection of songs from games
SONGS games[] =
{
  {mario_melody, mario_tempo, NUMELEMENTS(mario_melody), 1200},
  {underworld_melody, underworld_tempo, NUMELEMENTS(underworld_melody), 1600},
};

//collection of christmas and pop songs
SONGS christmas[] =
{
  {jingle_melody, jingle_tempo, NUMELEMENTS(jingle_melody),2000},
  {wish_melody, wish_tempo, NUMELEMENTS(wish_melody), 2500},
  {helpfallinginlove_melody, helpfallinginlove_tempo, NUMELEMENTS(helpfallinginlove_melody), 2000},
  {santaclaus_melody, santaclaus_tempo, NUMELEMENTS(santaclaus_melody), 2000},
  {jinglebellrock_melody, jinglebellrock_tempo, NUMELEMENTS(jinglebellrock_melody), 2500},
  {carolofthebells_melody, carolofthebells_tempo, NUMELEMENTS(carolofthebells_melody), 2500},
  {herecomesthesun_melody, herecomesthesun_tempo, NUMELEMENTS(herecomesthesun_melody), 5000}
};

bool newSong;             //flag to handle when a new song is playing
bool playMusic;           //flag for music, TRUE is ON, FALSE is OFF
bool playMusic_previous;  //to check if the selection has changed
SONGS *songPlaying;       //pointer to current playing song
uint32_t conductor = 0;   //timer for note duration
int noteDuration;         //length of current note in ms
int currentNote;          //frequency value of current note
bool songGenre = false;   //FALSE for games, TRUE for pop
int genreButton_previous; //to handle genre toggle
int genreButton;          //to handle genre toggle
int buttonTimer = 0;
int debounceTimer = 20;   //ms for debounce handling
int lightScheme = 0;      //light scheme holder
uint32_t lightTimer = 0;  //timer for light changes
int lightDuration = 50;   //length between light changes

void scheme_twinkle(void);

void setup(void)
{
  Serial.begin(9600);
 // while (!Serial){}
  pinMode(5, OUTPUT);//buzzer
  CircuitPlayground.begin(122);
  //CircuitPlayground.setBrightness(255);
  newSong = true;
  genreButton = CircuitPlayground.rightButton();
  Serial.println("Setup complete");
}

void loop()
{
  //slide on for music, off for no music
  if(CircuitPlayground.slideSwitch())
  {
    playMusic = true;
    if(playMusic_previous != playMusic)     //start a new song when music is turned on
    {
      newSong = true;
    }
  }
  else
  {
    playMusic = false;
    newSong = true;
  }
  playMusic_previous = playMusic;

  //button handler for song genre
  genreButton_previous = genreButton;
  genreButton = CircuitPlayground.rightButton();
  if((genreButton == 1) && (genreButton_previous == 0) && ((int)millis() - buttonTimer > debounceTimer))
  {
    genreButton_previous = CircuitPlayground.rightButton();
    songGenre = !songGenre;
    newSong = true;
    buttonTimer = millis();
    Serial.print("switching song to genre ");
    Serial.println(songGenre);
  }

  //handle starting a new song
  if(newSong)
  {
    if(songGenre == false)         
    {
      songPlaying = & games[random(NUMELEMENTS(games))];
    }
    else if(songGenre == true)
    {
      scheme_twinkle();
      songPlaying = & christmas[random(NUMELEMENTS(christmas))];
    }
    //songPlaying = & christmas[6]; //to select a particular song for testing
    currentNote = 0;
    noteDuration = songPlaying->beat_ms / (int )pgm_read_word_near(&(songPlaying->tempos[currentNote]));
    newSong = false;
  }

  //play the next note in the sequence only when it has been long enough since the last note started and playMusic is true
  if(((int)(millis() - conductor) > noteDuration * 1.3)  && playMusic)
  {
    conductor = millis();
    noteDuration = songPlaying->beat_ms / (int )pgm_read_word_near(&(songPlaying->tempos[currentNote]));
    tone(melodyPin, (int ) pgm_read_word_near(&(songPlaying->melodies[currentNote])), noteDuration);
    currentNote++;
    //handle the end of the song
    if(currentNote > songPlaying->size)
    {
      newSong = true;
      noTone(melodyPin);
      conductor += PACE;    //add a small delay to the end of the song
    }
  }

  //update light brightness
  if((int)(millis() - lightTimer) > lightDuration)
  {
    lightTimer = millis();
    CircuitPlayground.strip.setBrightness(random(255));
    CircuitPlayground.strip.show();
  }
}

//twinkle the onboard neopixels
//some solid red, others twinkle white
void scheme_twinkle(void)
{
  for (int i =0; i<2; i++)
  {
    CircuitPlayground.strip.setPixelColor(5*i, 255,0,0);
    CircuitPlayground.strip.setPixelColor(5*i+1, 255,255,255);
    CircuitPlayground.strip.setPixelColor(5*i+2, 0,255,0);
    CircuitPlayground.strip.setPixelColor(5*i+3, 255,255,255);
    CircuitPlayground.strip.setPixelColor(5*i+4, 255,0,0);
  }
  CircuitPlayground.strip.show();
  lightDuration = 500;
}