#ifndef Slider_h
#define Slider_h
/***************************************************************************************
// The following button class has been ported over from the Adafruit_GFX library so
// should be compatible.
// A slightly different implementation in this TFT_eSPI library allows the button
// legends to be in any font
***************************************************************************************/
#include <Arduino.h>
#include "../TFT_eSPI.h"

typedef enum {
    SLIDER_RECTANGLE,
    SLIDER_DOT,
} slider_type_t;

class TFT_eSPI_Slider {

 public:
    TFT_eSPI_Slider(void);

    void initSliderH(TFT_eSPI * gfx, int16_t min1, int16_t max1, int16_t x, int16_t y,
                     uint16_t w, uint16_t h, uint16_t outlinecolor, uint16_t knobcolor, uint16_t fill, uint16_t nofill,
                     slider_type_t type);
    void drawSliderH(int16_t x);
    boolean containsH(int16_t x, int16_t y);
    int16_t getValueH(int16_t v);
 private:
     TFT_eSPI * _gfx;
    int16_t _gap;
    int16_t _pos;
    // *** Privates Button ***
    int16_t _x, _y;             // Coordinates of top-left corner for button & slider
    uint16_t _w, _h;
    uint16_t _outlinecolor, _fillcolor, _nofillcolor, _knobcolor;

    boolean _currstate, _laststate;     // for buttons

    int16_t _min, _max;         // min and max value for Slider
    int8_t _drawvalue;          // Draw value for slider
    int16_t _oldvalue = -999;   // determinate de last position of knob for Slider
    slider_type_t _type;
};
#endif
