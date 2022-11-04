//song definitions
//#include "pitches.h"

//use struct to hold pointers to melody and tempo arrays,
//also need to capture length of each since sizeof() doesnt work with pointers
//struct definition must be in seperated .h file to avoid Arduino issue of prototype declaration
typedef struct{
  int *melodies;
  int *tempos;
  int size;     
}SONGS;

//Mario main theme melody
extern int mario_melody[] = {

  NOTE_E7, NOTE_E7, 0, NOTE_E7, 
  0, NOTE_C7, NOTE_E7, 0,
  NOTE_G7, 0, 0,  0,
  NOTE_G6, 0, 0, 0, 

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0,

  NOTE_C7, 0, 0, NOTE_G6, 
  0, 0, NOTE_E6, 0, 
  0, NOTE_A6, 0, NOTE_B6, 
  0, NOTE_AS6, NOTE_A6, 0, 

  NOTE_G6, NOTE_E7, NOTE_G7, 
  NOTE_A7, 0, NOTE_F7, NOTE_G7, 
  0, NOTE_E7, 0,NOTE_C7, 
  NOTE_D7, NOTE_B6, 0, 0
};

//Mario main them tempo
extern int mario_tempo[] = {
  12, 12, 12, 12, 
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12, 

  12, 12, 12, 12,
  12, 12, 12, 12, 
  12, 12, 12, 12, 
  12, 12, 12, 12, 

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,

  9, 9, 9,
  12, 12, 12, 12,
  12, 12, 12, 12,
  12, 12, 12, 12,
};

//Underworld melody
extern int underworld_melody[] = {
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_C4, NOTE_C5, NOTE_A3, NOTE_A4, 
  NOTE_AS3, NOTE_AS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0,
  NOTE_F3, NOTE_F4, NOTE_D3, NOTE_D4,
  NOTE_DS3, NOTE_DS4, 0,
  0, NOTE_DS4, NOTE_CS4, NOTE_D4,
  NOTE_CS4, NOTE_DS4, 
  NOTE_DS4, NOTE_GS3,
  NOTE_G3, NOTE_CS4,
  NOTE_C4, NOTE_FS4,NOTE_F4, NOTE_E3, NOTE_AS4, NOTE_A4,
  NOTE_GS4, NOTE_DS4, NOTE_B3,
  NOTE_AS3, NOTE_A3, NOTE_GS3,
  0, 0, 0
};

//Underwolrd tempo
extern int underworld_tempo[] = {
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  3,
  12, 12, 12, 12, 
  12, 12, 6,
  6, 18, 18, 18,
  6, 6,
  6, 6,
  6, 6,
  18, 18, 18,18, 18, 18,
  10, 10, 10,
  10, 10, 10,
  3, 3, 3
};

extern int jingle_melody[] = {
  NOTE_B4, NOTE_B4, NOTE_B4,
  NOTE_B4, NOTE_B4, NOTE_B4,
  NOTE_B4, NOTE_D5, NOTE_G4, NOTE_A4, 
  NOTE_B4, 0,
  NOTE_C5, NOTE_C5, NOTE_C5, NOTE_C5,
  NOTE_C5, NOTE_B4, NOTE_B4, NOTE_B4, NOTE_B4,
  NOTE_B4, NOTE_A4, NOTE_A4, NOTE_B4,
  NOTE_A4, NOTE_D5, 0
};

extern int jingle_tempo[] = {
  12, 12, 6,
  12, 12, 6,
  12, 12, 12, 12,
  6, 6,
  12, 12, 12, 12,
  12, 12, 12, 24, 24,
  12, 12, 12, 12,
  6, 6, 12
};

// We wish you a merry Christmas

extern int wish_melody[] = {
  NOTE_A4, 
  NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_CS5,
  NOTE_B4, NOTE_G4, NOTE_B4,
  NOTE_E5, NOTE_E5, NOTE_FS5, NOTE_E5, NOTE_D5,
  NOTE_CS5, NOTE_A4, NOTE_A4,
  NOTE_FS5, NOTE_FS5, NOTE_G5, NOTE_FS5, NOTE_E5,
  NOTE_D5, NOTE_B4, NOTE_A4, NOTE_A4,
  NOTE_B4, NOTE_E5, NOTE_CS5,
  NOTE_D5
};

extern int wish_tempo[] = {
  12,
  12, 24, 24, 24, 24,
  12, 12, 12,
  12, 24, 24, 24, 24,
  12, 12, 12,
  12, 24, 24, 24, 24,
  12, 12, 24, 24,
  12, 12, 12,
  6
};

//Santa claus is comin' to town melody 
int santaclaus_melody[] = {
NOTE_G4, 
NOTE_E4, NOTE_F4, NOTE_G4,NOTE_G4, NOTE_G4,
NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5,
NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,

NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,
NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
NOTE_D4, NOTE_F4, NOTE_B3,
NOTE_C4,
0, 0, NOTE_G4,

NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4,
NOTE_A4, NOTE_B4, NOTE_C5, NOTE_C5,
NOTE_E4, NOTE_F4, NOTE_G4, NOTE_G4, NOTE_G4, 
NOTE_A4, NOTE_G4, NOTE_F4, NOTE_F4,

NOTE_E4, NOTE_G4, NOTE_C4, NOTE_E4,
NOTE_D4, NOTE_F4, NOTE_B3, 
NOTE_C4
};

///Santa claus is comin' to town
int santaclaus_tempo[] = {

12,
24, 24, 12, 9, 24,
24, 24, 12, 6,
24, 24, 12, 12, 12,
 
24, 24, 12, 6,
12, 12, 12, 12,
12, 6, 12, 
1,
6, 12, 12,

24, 24, 12, 9, 24,
24, 24, 12, 6,
24, 24, 12, 12, 12,
24, 24, 12, 6,

12, 12, 12, 12,
12, 6, 12, 
1,

};

//I can't help falling in love with you melody
int helpfallinginlove_melody[] = {

NOTE_D2, NOTE_A3, NOTE_D4,  NOTE_FS4, NOTE_D4, NOTE_A3, 
NOTE_A2, NOTE_A3, NOTE_CS4, NOTE_E4, NOTE_CS4, NOTE_A3, 
NOTE_D2, NOTE_FS3, NOTE_A3, NOTE_D4, NOTE_A3, NOTE_FS3, 
NOTE_FS4, NOTE_D4, NOTE_A3, NOTE_A4, NOTE_FS4, NOTE_D4, 

NOTE_D4, 
NOTE_A4, 
NOTE_D4, 
0, NOTE_E4, NOTE_FS4, 

NOTE_G4, 
NOTE_FS4, 
NOTE_E4, 
0, 0, NOTE_A3, 

NOTE_B3, 
NOTE_CS4, 
NOTE_D4, 0, 
NOTE_E4, NOTE_FS4, NOTE_G4,

NOTE_FS4, 0, 
NOTE_E4, 
NOTE_D4 

};

///I can't help falling in love with you tempo
int helpfallinginlove_tempo[] = {

24, 24, 24, 24, 24, 24, 
24, 24, 24, 24, 24, 24, 
24, 24, 24, 24, 24, 24, 
24, 24, 24, 24, 24, 24, 

3, 
3,
3,
9, 24, 24, 

3, 
3,
3,
9, 12, 24, 

3,
3,
9, 9, 
12, 24, 12, 

9, 9, 
3, 
3

};

//Jingle bell rock melody
int jinglebellrock_melody[] = {

NOTE_C5, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_B4,
NOTE_A4, NOTE_B4, NOTE_A4, NOTE_E4, 0,
NOTE_A4, NOTE_B4, NOTE_A4, NOTE_E4, NOTE_G4,
NOTE_A4, NOTE_B4, NOTE_A4, NOTE_F4, 0, 

NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4, 
NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, 
0, NOTE_A4, NOTE_GS4, NOTE_A4, NOTE_GS4, NOTE_A4, 
NOTE_A4, NOTE_DS4, NOTE_DS4, 0, 

NOTE_C5, NOTE_C5, NOTE_C5, NOTE_B4, NOTE_B4, NOTE_B4, 
NOTE_A4, NOTE_B4, NOTE_A4, NOTE_E4, 0,
NOTE_A4, NOTE_B4, NOTE_A4, NOTE_E4, NOTE_G4, 
NOTE_A4, NOTE_B4, NOTE_A4, NOTE_F4, 0, 

NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, NOTE_A4, NOTE_G4,
NOTE_D4, NOTE_E4, NOTE_F4, NOTE_G4, 
NOTE_A4, NOTE_A4, NOTE_B4, NOTE_A4, NOTE_G4, 
NOTE_C5, 0

};

///Jingle bell rock tempo
int jinglebellrock_tempo[] = {

24, 24, 12, 24, 24, 12,
24, 24, 24, 9, 12, 
24, 24, 24, 9, 12,
24, 24, 24, 9, 12,
24, 24, 24, 9, 12, 

24, 12, 24, 24, 12, 24, 
24, 24, 24, 3, 
12, 24, 24, 24, 24, 12,
12, 24, 9, 12,

24, 24, 12, 24, 24, 12, 
24, 24, 24, 9, 12,
24, 24, 24, 9, 12,
24, 24, 24, 9, 12, 

24, 12, 24, 24, 12, 24, 
24, 24, 24, 3, 
12, 24, 24, 24, 12, 
6, 6

};


// Carol of the bells melody
int carolofthebells_melody[] = {

NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 

NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4,

NOTE_E5, NOTE_D5, NOTE_E5, NOTE_C5,
NOTE_E5, NOTE_D5, NOTE_E5, NOTE_C5,
NOTE_E5, NOTE_D5, NOTE_E5, NOTE_C5,
NOTE_E5, NOTE_D5, NOTE_E5, NOTE_C5,
NOTE_A5, NOTE_A5, NOTE_A5, NOTE_G5, NOTE_F5, 
NOTE_E5, NOTE_E5, NOTE_E5, NOTE_D5, NOTE_C5,

NOTE_D5, NOTE_D5, NOTE_D5, NOTE_E5, NOTE_D5, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4, 
NOTE_E4, NOTE_FS4, NOTE_GS4, NOTE_A4, NOTE_B4, NOTE_C5, 
NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
NOTE_E4, NOTE_FS4, NOTE_GS4, NOTE_A4, NOTE_B4, NOTE_C5, 

NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4,
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4,
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4,
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4,

NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4,
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4,
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4,
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_A4,
NOTE_E5, NOTE_D5, NOTE_E5, NOTE_A4

};

/// Carol of the bells tempo
int carolofthebells_tempo[] = {

12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 

12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 

12, 24, 24, 12, 
12, 24, 24, 12,
12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 24, 24, 
12, 24, 24, 24, 24, 

12, 24, 24, 24, 24, 
12, 24, 24, 12,
24, 24, 24, 24, 24, 
24, 24, 12, 12, 
24, 24, 24, 24, 24, 24, 

24, 24, 12, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 

12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12, 
12, 24, 24, 12 

};

// Here comes the sun melody
int herecomesthesun_melody[] = {

0, NOTE_FS4, NOTE_D4, NOTE_E4, NOTE_FS4, 
0, NOTE_FS4, NOTE_E4, NOTE_D4, 
0, NOTE_B3, NOTE_D4, NOTE_FS4, NOTE_E4, NOTE_D4, 
NOTE_B3, NOTE_A3, 

0, NOTE_FS4, NOTE_D4, NOTE_E4, NOTE_FS4,
0, NOTE_FS4, NOTE_E4, NOTE_D4,
0, NOTE_B3, NOTE_FS4, NOTE_E4, NOTE_D4, 
NOTE_CS4,

0, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_D4, 
0, NOTE_FS4, NOTE_D4, NOTE_E4, NOTE_FS4, 
0, NOTE_FS4, NOTE_E4, NOTE_FS4, NOTE_D4, 
0, NOTE_B3, NOTE_F4, NOTE_E4, NOTE_D4, 

0, NOTE_FS4, NOTE_E4, NOTE_D4, NOTE_A3, 
NOTE_B3, NOTE_D4, NOTE_E4, NOTE_A3, NOTE_D4, NOTE_E4, NOTE_GS3, NOTE_D4, NOTE_E4,
NOTE_D4, NOTE_CS4, NOTE_B3, NOTE_A3, 

NOTE_F4, NOTE_C4, NOTE_G4, 
NOTE_B3, NOTE_D4, NOTE_E4, NOTE_D4 


};

/// Here comes the sun tempo
int herecomesthesun_tempo[] = {

12, 24, 24, 24, 9, 
12, 24, 24, 24, 9,
12, 24, 24, 24, 9,
12, 3, 

12, 24, 24, 24, 9, 
12, 24, 24, 24, 9,
12, 24, 24, 24, 9,
1,

12, 24, 12, 24, 12,  
12, 24, 24, 24, 9, 
12, 24, 12, 24, 12,
24, 12, 24, 12, 

12, 24, 12, 12, 24, 
12, 24, 24, 12, 24, 24, 12, 24, 24, 
24, 24, 24, 24, 

12, 12, 12, 
24, 24, 24, 24 

};


// Mele kalikimaka melody
int melekalikimaka_melody[] = {

NOTE_G4, NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_G4, 
NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_G4, 
NOTE_E5, NOTE_B4, 
NOTE_D5, NOTE_A4, NOTE_B4, 
NOTE_C5, NOTE_B4, 
NOTE_C5, NOTE_B4, NOTE_C5, NOTE_D5, 
NOTE_B4, 

NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_G4, 
NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_G4, 
NOTE_F5, NOTE_CS5, 
NOTE_E5, NOTE_D5, NOTE_A4, 
NOTE_C5, NOTE_B4, 
NOTE_A4, NOTE_G4, 

NOTE_E5, 
NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_G4, 
NOTE_A4, NOTE_G4, NOTE_E4, NOTE_C4, 
NOTE_G4, NOTE_FS4, 
NOTE_F4, NOTE_F4, 
NOTE_E4, NOTE_E4, NOTE_DS4, NOTE_E4, 

NOTE_F4, NOTE_E4, NOTE_CS4, NOTE_A3, 
NOTE_E3, NOTE_C4, 
NOTE_D4, 
NOTE_G4, NOTE_G4, NOTE_G4, NOTE_FS4, NOTE_G4, 
NOTE_A4, NOTE_G4, NOTE_FS4, NOTE_G4, 
NOTE_F5, NOTE_F5, 
NOTE_E5, NOTE_E4, 

NOTE_F4, NOTE_A4, NOTE_A4, 
NOTE_G4, NOTE_D4, NOTE_E4, 
NOTE_C4 
};

/// Mele kalikimaka tempo
int melekalikimaka_tempo[] = {

24, 12, 24, 12, 12, 
12, 12, 12, 12, 
3, 12,
6, 12, 12, 
3, 12, 
12, 12, 12, 12, 
1, 

9, 24, 12, 12, 
12, 12, 12, 12, 
3, 12, 
6, 12, 12, 
6, 6, 
6, 6, 

1,
9, 24, 12, 12, 
12, 12, 12, 12, 
3, 12, 
3, 12, 
9, 24, 12, 12, 

12, 12, 12, 12, 
3, 12, 
1,
24, 12, 24, 12, 12, 
12, 12, 12, 12, 
6, 6, 
3, 12, 

6, 12, 12, 
12, 6, 12, 
1, 
24, 12, 24, 12, 12, 
12, 12, 12, 12, 
3, 12, 
6, 12, 12, 

3, 12, 
12, 12, 12, 12, 
1

};