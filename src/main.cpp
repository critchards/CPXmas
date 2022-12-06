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
#include "FastLED.h"                      //for twinkle effects

#define NUMELEMENTS(x) (sizeof(x))/sizeof(x[0])   //to calculate length of struct elements
#define melodyPin 5                               //Circuit playground onbvoard LED and Buzzer Pin

const int PACE = 5000;          //scale factor that handles time between songs and other timings

//copied TwinkleFox example from FastLED library https://github.com/FastLED/FastLED/blob/master/examples/TwinkleFox/TwinkleFox.ino
//*********************************************
#define NUM_LEDS       10
#define LED_TYPE  WS2812B
#define COLOR_ORDER   RGB
#define DATA_PIN       17
//#define CLK_PIN       4
#define VOLTS           5
#define MAX_MA       1000

CRGBArray<NUM_LEDS> leds;
#define TWINKLE_SPEED 4
#define TWINKLE_DENSITY 5
#define SECONDS_PER_PALETTE  30
//CRGB gBackgroundColor = CRGB(CRGB::FairyLight).nscale8_video(16);
CRGB gBackgroundColor = CRGB(CRGB::Black);
#define AUTO_SELECT_BACKGROUND_COLOR 1
#define COOL_LIKE_INCANDESCENT 1 
CRGBPalette16 gCurrentPalette;
CRGBPalette16 gTargetPalette;

void drawTwinkles( CRGBSet& L);
CRGB computeOneTwinkle( uint32_t ms, uint8_t salt);
uint8_t attackDecayWave8( uint8_t i);
void coolLikeIncandescent( CRGB& c, uint8_t phase);
void chooseNextColorPalette( CRGBPalette16& pal);
//*****************************************************************

//void buzz(int, long, long);                               
void playSong(SONGS * matrix, int track); 
 
//collection of songs from games
SONGS games[] =
{
  {mario_melody, mario_tempo, NUMELEMENTS(mario_melody), 1200},
  {underworld_melody, underworld_tempo, NUMELEMENTS(underworld_melody), 1600},
  {pirates_melody, pirates_tempo, NUMELEMENTS(pirates_melody), 1000},
  {zelda_melody, zelda_tempo, NUMELEMENTS(zelda_melody), 1800}
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
  {herecomesthesun_melody, herecomesthesun_tempo, NUMELEMENTS(herecomesthesun_melody), 5000},
  {melekalikimaka_melody, melekalikimaka_tempo, NUMELEMENTS(melekalikimaka_melody), 5000}
  
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
int genreButton;          

bool newLight;            //flag to handle when a new light pattern is started
bool twinkle;             //flag to handle twinkling lights
int lightScheme = 0;      //0 - no lights, 1 - redwhitegreen solid, 2 - cool white blue solid, 3 - fastled twinklefox
const int LIGHTPATTERNS = 4;
int lightButton_previous; //to handle light toggle
int lightButton;

int buttonTimer = 0;
int debounceTimer = 20;   //ms for debounce handling

//set some neopixels colors. There are better ways to do this but Im just learning
void light_redWhiteGreen(void);
void light_whiteBlue(void);

void setup(void)
{
  //for Fastled twinklefox
  delay(3000);
  FastLED.setMaxPowerInVoltsAndMilliamps( VOLTS, MAX_MA);
  FastLED.addLeds<LED_TYPE,DATA_PIN,COLOR_ORDER>(leds, NUM_LEDS)
    .setCorrection(TypicalLEDStrip);
  chooseNextColorPalette(gTargetPalette);

  Serial.begin(9600);
  pinMode(5, OUTPUT);               //buzzer
  CircuitPlayground.begin(122);
  newSong = true;
  newLight = false;
  lightScheme = 0;
  playMusic = false;
  twinkle = false;
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

  //button handler for light pattern
  lightButton_previous = lightButton;
  lightButton = CircuitPlayground.leftButton();
  if((lightButton == 1) && (lightButton_previous == 0) && ((int)millis() - buttonTimer > debounceTimer))
  {
    lightButton_previous = CircuitPlayground.leftButton();
    lightScheme++;
    if(lightScheme >= LIGHTPATTERNS)
    {
      lightScheme = 0;
    }
    newLight = true;
    buttonTimer = millis();
    Serial.print("switching to light pattern ");
    Serial.println(lightScheme);
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
      songPlaying = & christmas[random(NUMELEMENTS(christmas))];
    }
    //songPlaying = & christmas[6]; //to select a particular song for testing
    //songPlaying = & games[2];      //to select a particular song for testing
    currentNote = 0;
    noteDuration = songPlaying->beat_ms / (int )pgm_read_word_near(&(songPlaying->tempos[currentNote]));
    newSong = false;
  }

  //play the next note in the sequence only when it has been long enough since the last note started and playMusic is true
  //add a small delay between notes for definition, 1.3 *duration seems to work
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

  //switch between light schemes based on number of button presses
  if(newLight)
  {
    switch (lightScheme)
    {
      case 0:
        CircuitPlayground.strip.clear();
        twinkle = false;
        break;
      case 1:
        light_redWhiteGreen();
        twinkle = false;
        break;
      case 2:
        light_whiteBlue();
        break;
      case 3:
        twinkle = true;
        break;
      default:
        Serial.println("no light scheme selected");
        break;
    }
    Serial.print("switching to lightScheme ");
    Serial.println(lightScheme);
    newLight = false;
    CircuitPlayground.strip.show();
  }

  //run the fastled twinklefox example
  if(twinkle)
  {
    EVERY_N_SECONDS( SECONDS_PER_PALETTE ) { 
      chooseNextColorPalette( gTargetPalette ); 
    }
  
    EVERY_N_MILLISECONDS( 10 ) {
      nblendPaletteTowardPalette( gCurrentPalette, gTargetPalette, 12);
    }

    drawTwinkles( leds);
  
    FastLED.show();
  }
}

//set the neopixels to solid red, white, green
void light_redWhiteGreen(void)
{
  for (int i =0; i<2; i++)
  {
    CircuitPlayground.strip.setPixelColor(5*i, 255,0,0);
    CircuitPlayground.strip.setPixelColor(5*i+1, 255,255,255);
    CircuitPlayground.strip.setPixelColor(5*i+2, 0,255,0);
    CircuitPlayground.strip.setPixelColor(5*i+3, 255,255,255);
    CircuitPlayground.strip.setPixelColor(5*i+4, 255,0,0);
  }
}

//set the neopixles to cool white and blue lights
void light_whiteBlue(void)
{
  for (int i =0; i<2; i++)
  {
    CircuitPlayground.strip.setPixelColor(5*i, 0,0,255);
    CircuitPlayground.strip.setPixelColor(5*i+1, 255,255,255);
    CircuitPlayground.strip.setPixelColor(5*i+2, 0,0,255);
    CircuitPlayground.strip.setPixelColor(5*i+3, 255,255,255);
    CircuitPlayground.strip.setPixelColor(5*i+4, 0,0,255);
  }
  CircuitPlayground.setBrightness(50);
}

//FastLED definitions
//*************** 
//  This function loops over each pixel, calculates the 
//  adjusted 'clock' that this pixel should use, and calls 
//  "CalculateOneTwinkle" on each pixel.  It then displays
//  either the twinkle color of the background color, 
//  whichever is brighter.
void drawTwinkles( CRGBSet& L)
{
  // "PRNG16" is the pseudorandom number generator
  // It MUST be reset to the same starting value each time
  // this function is called, so that the sequence of 'random'
  // numbers that it generates is (paradoxically) stable.
  uint16_t PRNG16 = 11337;
  
  uint32_t clock32 = millis();

  // Set up the background color, "bg".
  // if AUTO_SELECT_BACKGROUND_COLOR == 1, and the first two colors of
  // the current palette are identical, then a deeply faded version of
  // that color is used for the background color
  CRGB bg;
  if( (AUTO_SELECT_BACKGROUND_COLOR == 1) &&
      (gCurrentPalette[0] == gCurrentPalette[1] )) {
    bg = gCurrentPalette[0];
    uint8_t bglight = bg.getAverageLight();
    if( bglight > 64) {
      bg.nscale8_video( 16); // very bright, so scale to 1/16th
    } else if( bglight > 16) {
      bg.nscale8_video( 64); // not that bright, so scale to 1/4th
    } else {
      bg.nscale8_video( 86); // dim, scale to 1/3rd.
    }
  } else {
    bg = gBackgroundColor; // just use the explicitly defined background color
  }

  uint8_t backgroundBrightness = bg.getAverageLight();
  
  for( CRGB& pixel: L) {
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
    uint16_t myclockoffset16= PRNG16; // use that number as clock offset
    PRNG16 = (uint16_t)(PRNG16 * 2053) + 1384; // next 'random' number
    // use that number as clock speed adjustment factor (in 8ths, from 8/8ths to 23/8ths)
    uint8_t myspeedmultiplierQ5_3 =  ((((PRNG16 & 0xFF)>>4) + (PRNG16 & 0x0F)) & 0x0F) + 0x08;
    uint32_t myclock30 = (uint32_t)((clock32 * myspeedmultiplierQ5_3) >> 3) + myclockoffset16;
    uint8_t  myunique8 = PRNG16 >> 8; // get 'salt' value for this pixel

    // We now have the adjusted 'clock' for this pixel, now we call
    // the function that computes what color the pixel should be based
    // on the "brightness = f( time )" idea.
    CRGB c = computeOneTwinkle( myclock30, myunique8);

    uint8_t cbright = c.getAverageLight();
    int16_t deltabright = cbright - backgroundBrightness;
    if( deltabright >= 32 || (!bg)) {
      // If the new pixel is significantly brighter than the background color, 
      // use the new color.
      pixel = c;
    } else if( deltabright > 0 ) {
      // If the new pixel is just slightly brighter than the background color,
      // mix a blend of the new color and the background color
      pixel = blend( bg, c, deltabright * 8);
    } else { 
      // if the new pixel is not at all brighter than the background color,
      // just use the background color.
      pixel = bg;
    }
  }
}


//  This function takes a time in pseudo-milliseconds,
//  figures out brightness = f( time ), and also hue = f( time )
//  The 'low digits' of the millisecond time are used as 
//  input to the brightness wave function.  
//  The 'high digits' are used to select a color, so that the color
//  does not change over the course of the fade-in, fade-out
//  of one cycle of the brightness wave function.
//  The 'high digits' are also used to determine whether this pixel
//  should light at all during this cycle, based on the TWINKLE_DENSITY.
CRGB computeOneTwinkle( uint32_t ms, uint8_t salt)
{
  uint16_t ticks = ms >> (8-TWINKLE_SPEED);
  uint8_t fastcycle8 = ticks;
  uint16_t slowcycle16 = (ticks >> 8) + salt;
  slowcycle16 += sin8( slowcycle16);
  slowcycle16 =  (slowcycle16 * 2053) + 1384;
  uint8_t slowcycle8 = (slowcycle16 & 0xFF) + (slowcycle16 >> 8);
  
  uint8_t bright = 0;
  if( ((slowcycle8 & 0x0E)/2) < TWINKLE_DENSITY) {
    bright = attackDecayWave8( fastcycle8);
  }

  uint8_t hue = slowcycle8 - salt;
  CRGB c;
  if( bright > 0) {
    c = ColorFromPalette( gCurrentPalette, hue, bright, NOBLEND);
    if( COOL_LIKE_INCANDESCENT == 1 ) {
      coolLikeIncandescent( c, fastcycle8);
    }
  } else {
    c = CRGB::Black;
  }
  return c;
}


/* This function is like 'triwave8', which produces a 
// symmetrical up-and-down triangle sawtooth waveform, except that this
// function produces a triangle wave with a faster attack and a slower decay:
//
//     / \ 
//    /     \ 
//   /         \ 
//  /             \ 
//
*/

uint8_t attackDecayWave8( uint8_t i)
{
  if( i < 86) {
    return i * 3;
  } else {
    i -= 86;
    return 255 - (i + (i/2));
  }
}

// This function takes a pixel, and if its in the 'fading down'
// part of the cycle, it adjusts the color a little bit like the 
// way that incandescent bulbs fade toward 'red' as they dim.
void coolLikeIncandescent( CRGB& c, uint8_t phase)
{
  if( phase < 128) return;

  uint8_t cooling = (phase - 128) >> 4;
  c.g = qsub8( c.g, cooling);
  c.b = qsub8( c.b, cooling * 2);
}

// A mostly red palette with green accents and white trim.
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 RedGreenWhite_p FL_PROGMEM =
{  CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, 
   CRGB::Red, CRGB::Red, CRGB::Red, CRGB::Red, 
   CRGB::Red, CRGB::Red, CRGB::Gray, CRGB::Gray, 
   CRGB::Green, CRGB::Green, CRGB::Green, CRGB::Green };

// A mostly (dark) green palette with red berries.
#define Holly_Green 0x00580c
#define Holly_Red   0xB00402
const TProgmemRGBPalette16 Holly_p FL_PROGMEM =
{  Holly_Green, Holly_Green, Holly_Green, Holly_Green, 
   Holly_Green, Holly_Green, Holly_Green, Holly_Green, 
   Holly_Green, Holly_Green, Holly_Green, Holly_Green, 
   Holly_Green, Holly_Green, Holly_Green, Holly_Red 
};

// A red and white striped palette
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 RedWhite_p FL_PROGMEM =
{  CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray,
   CRGB::Red,  CRGB::Red,  CRGB::Red,  CRGB::Red, 
   CRGB::Gray, CRGB::Gray, CRGB::Gray, CRGB::Gray };

// A mostly blue palette with white accents.
// "CRGB::Gray" is used as white to keep the brightness more uniform.
const TProgmemRGBPalette16 BlueWhite_p FL_PROGMEM =
{  CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue, 
   CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue, 
   CRGB::Blue, CRGB::Blue, CRGB::Blue, CRGB::Blue, 
   CRGB::Blue, CRGB::Gray, CRGB::Gray, CRGB::Gray };

// A pure "fairy light" palette with some brightness variations
#define HALFFAIRY ((CRGB::FairyLight & 0xFEFEFE) / 2)
#define QUARTERFAIRY ((CRGB::FairyLight & 0xFCFCFC) / 4)
const TProgmemRGBPalette16 FairyLight_p FL_PROGMEM =
{  CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, 
   HALFFAIRY,        HALFFAIRY,        CRGB::FairyLight, CRGB::FairyLight, 
   QUARTERFAIRY,     QUARTERFAIRY,     CRGB::FairyLight, CRGB::FairyLight, 
   CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight, CRGB::FairyLight };

// A palette of soft snowflakes with the occasional bright one
const TProgmemRGBPalette16 Snow_p FL_PROGMEM =
{  0x304048, 0x304048, 0x304048, 0x304048,
   0x304048, 0x304048, 0x304048, 0x304048,
   0x304048, 0x304048, 0x304048, 0x304048,
   0x304048, 0x304048, 0x304048, 0xE0F0FF };

// A palette reminiscent of large 'old-school' C9-size tree lights
// in the five classic colors: red, orange, green, blue, and white.
#define C9_Red    0xB80400
#define C9_Orange 0x902C02
#define C9_Green  0x046002
#define C9_Blue   0x070758
#define C9_White  0x606820
const TProgmemRGBPalette16 RetroC9_p FL_PROGMEM =
{  C9_Red,    C9_Orange, C9_Red,    C9_Orange,
   C9_Orange, C9_Red,    C9_Orange, C9_Red,
   C9_Green,  C9_Green,  C9_Green,  C9_Green,
   C9_Blue,   C9_Blue,   C9_Blue,
   C9_White
};

// A cold, icy pale blue palette
#define Ice_Blue1 0x0C1040
#define Ice_Blue2 0x182080
#define Ice_Blue3 0x5080C0
const TProgmemRGBPalette16 Ice_p FL_PROGMEM =
{
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue1, Ice_Blue1, Ice_Blue1, Ice_Blue1,
  Ice_Blue2, Ice_Blue2, Ice_Blue2, Ice_Blue3
};


// Add or remove palette names from this list to control which color
// palettes are used, and in what order.
const TProgmemRGBPalette16* ActivePaletteList[] = {
  &RetroC9_p,
  &BlueWhite_p,
  &RainbowColors_p,
  &FairyLight_p,
  &RedGreenWhite_p,
  &PartyColors_p,
  &RedWhite_p,
  &Snow_p,
  &Holly_p,
  &Ice_p  
};


// Advance to the next color palette in the list (above).
void chooseNextColorPalette( CRGBPalette16& pal)
{
  const uint8_t numberOfPalettes = sizeof(ActivePaletteList) / sizeof(ActivePaletteList[0]);
  static uint8_t whichPalette = -1; 
  whichPalette = addmod8( whichPalette, 1, numberOfPalettes);

  pal = *(ActivePaletteList[whichPalette]);
}