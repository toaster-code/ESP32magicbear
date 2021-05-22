#include "Audio.h"
#include "SD.h"
#include "FS.h"
#include "ezTouch.h"

// Digital I/O used
#define SD_CS          5
#define SPI_MOSI      23
#define SPI_MISO      19
#define SPI_SCK       18
#define I2S_DOUT      25
#define I2S_BCLK      27
#define I2S_LRC       26

Audio audio;

// set pin numbers
//setTouchThreshold = 40
//ezButton button1(6);  // create ezButton object that attach to pin 6;
ezTouch button2(T3);  // create ezButton object that attach to pin T3;


// variable for storing the touch pin value 
int touchValue;
int touchValue_buffer;
int songNumber;


void setup(){
    pinMode(SD_CS, OUTPUT);
    digitalWrite(SD_CS, HIGH);
    SPI.begin(SPI_SCK, SPI_MISO, SPI_MOSI);
    Serial.begin(115200);
    SD.begin(SD_CS);
    audio.setPinout(I2S_BCLK, I2S_LRC, I2S_DOUT);
    audio.setVolume(10); // 0...21
    audio.connecttoFS(SD, "a02.wav");
    songNumber = 1;

//    button1.setDebounceTime(50); // set debounce time to 50 milliseconds
    button2.setDebounceTime(50);
}

void loop(){
  touchValue_buffer = 0;
  audio.loop();
 // button1.loop();
  button2.loop();
  Serial.println(touchValue);  // get value of Touch 3 pin = GPIO 15
  
  if(button2.isPressed()){
    audio.stopSong();
    if (songNumber == 0) {
      audio.connecttoFS(SD, "a03.wav");
      songNumber = 1;
    }
    else if (songNumber == 1) {
      audio.connecttoFS(SD, "a02.wav");
      songNumber = 0;
    }
  }
}

// optional
void audio_info(const char *info){
    Serial.print("info        "); Serial.println(info);
}
void audio_id3data(const char *info){  //id3 metadata
    Serial.print("id3data     ");Serial.println(info);
}
void audio_eof_mp3(const char *info){  //end of file
    Serial.print("eof_mp3     ");Serial.println(info);
}
void audio_showstation(const char *info){
    Serial.print("station     ");Serial.println(info);
}
void audio_showstreaminfo(const char *info){
    Serial.print("streaminfo  ");Serial.println(info);
}
void audio_showstreamtitle(const char *info){
    Serial.print("streamtitle ");Serial.println(info);
}
void audio_bitrate(const char *info){
    Serial.print("bitrate     ");Serial.println(info);
}
void audio_commercial(const char *info){  //duration in sec
    Serial.print("commercial  ");Serial.println(info);
}
void audio_icyurl(const char *info){  //homepage
    Serial.print("icyurl      ");Serial.println(info);
}
void audio_lasthost(const char *info){  //stream URL played
    Serial.print("lasthost    ");Serial.println(info);
}
void audio_eof_speech(const char *info){
    Serial.print("eof_speech  ");Serial.println(info);
}
