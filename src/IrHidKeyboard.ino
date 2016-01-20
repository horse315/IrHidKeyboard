#include "TrinketHidCombo.h"
#define LED_PIN 1
#define IR_PIN 2
#define IR_INT 0

#define PLAY  40
#define UP     88
#define DOWN   120
#define LEFT   104
#define RIGHT  24
#define POWER     72
#define BAND   232
#define SOURCE 8
#define VOL_UP  216
#define VOL_DWN 248

int pos = 0;
uint32_t data;

uint8_t addressToRead = 0;
uint8_t commandToRead = 0;
bool timeToRead = false;

uint16_t timePrev = 0;

void setup()
{
  pinMode(LED_PIN, OUTPUT);

  pinMode(IR_PIN, INPUT);
  attachInterrupt(IR_INT, irRead, FALLING);

  TrinketHidCombo.begin();
}


void loop()
{
  if (timeToRead)
  {
    digitalWrite(LED_PIN, HIGH);

/*
    char str[15];
    sprintf(str, "%d", commandToRead);
    TrinketHidCombo.println(str);
*/

    switch (commandToRead)
    {
      case VOL_UP:
        TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_UP);
        break;
      case VOL_DWN:
        TrinketHidCombo.pressMultimediaKey(MMKEY_VOL_DOWN);
        break;
      case PLAY:
        TrinketHidCombo.pressMultimediaKey(MMKEY_PLAYPAUSE);
        break;
      case LEFT:
        TrinketHidCombo.pressMultimediaKey(MMKEY_SCAN_PREV_TRACK);
        break;
      case RIGHT:
        TrinketHidCombo.pressMultimediaKey(MMKEY_SCAN_NEXT_TRACK);
        break;
      case POWER:
        TrinketHidCombo.pressKey(0x0, KEYCODE_ESC);
        TrinketHidCombo.pressKey(0, 0);
        break;
      case SOURCE:
        TrinketHidCombo.pressKey(KEYCODE_MOD_LEFT_ALT, KEYCODE_ESC);
        TrinketHidCombo.pressKey(0, 0);
        break;
      case UP:
        TrinketHidCombo.pressKey(KEYCODE_MOD_LEFT_GUI, KEYCODE_A);
        TrinketHidCombo.pressKey(0, 0);
        break;
      case DOWN:
        TrinketHidCombo.pressKey(KEYCODE_MOD_LEFT_GUI, KEYCODE_D);
        TrinketHidCombo.pressKey(0, 0);
        break;
      case BAND:
        break;
      default:
        break;
    }

    digitalWrite(LED_PIN, LOW);

    timeToRead = false;
  }

  TrinketHidCombo.poll();
}
void irRead() {
  uint16_t time = micros();
  uint16_t dt = time - timePrev;

  timePrev = time;

  int dtState = deltaState(dt);

  if (dtState == 1) {
    clear();
  } else if (dtState == 2) {
    data |= (dt > 1500);

    if (pos < 31) {
      data <<= 1;
      pos++;
    } else {
      timeToRead = false;
      addressToRead = (uint8_t)((data >> 24) & 0xff);
      commandToRead = (uint8_t)((data >> 8) & 0xff);
      timeToRead = true;
    }
  }
}

int deltaState(uint16_t dt) {
  if (dt > 12000 && dt < 14000) {
    return 1;
  } else if (dt > 1000 && dt < 2500) {
    return 2;
  } else {
    return 0;
  }
}

void clear() {
  pos = 0;
  data = 0;
  timeToRead = false;
}
