/***************************************************************************************
** Code for the GFX button UI element
** Grabbed from Adafruit_GFX library and enhanced to handle any label font
***************************************************************************************/
#include "Button.h"
#include "../TFT_eSPI.h"
TFT_eSPI_Slider::TFT_eSPI_Slider(void)
{
    _gfx = 0;
}

// *** Init Horizontal Slider ***
void TFT_eSPI_Slider::initSliderH(TFT_eSPI * gfx, int16_t min1, int16_t max1, int16_t x, int16_t y, uint16_t w,
                                  uint16_t h, uint16_t outlinecolor, uint16_t knobcolor, uint16_t fill, uint16_t nofill,
                                  slider_type_t type)
{

    _gfx = gfx;

    _min = min1;
    _max = max1;

    _x = x;
    _y = y;
    _w = w;
    _h = h;

    _outlinecolor = outlinecolor;
    _fillcolor = fill;
    _nofillcolor = nofill;

    _knobcolor = knobcolor;
    _drawvalue = 0;
    _type = type;
    _gap=20;
}

// *** Draw Horizontal Slider ***
void TFT_eSPI_Slider::drawSliderH(int16_t value)
{
    value = constrain(value, _min, _max);
    if (_oldvalue != value) {

        if(_type == SLIDER_RECTANGLE) {
            _pos = map(value, _min, _max, 0, _w - _gap);

            // Draw Gap
            _gfx->fillRect(_x, _y, _pos, _h, _fillcolor);   // Fill up to value
            _gfx->fillRect(_x + _pos + _gap, _y, _w - _pos - _gap, _h, _nofillcolor);       // Fill Rest
            _oldvalue = value;
            // Draw Knob
            _gfx->fillRect(_x + _pos, _y, _gap, _h, _knobcolor);    // Fill up to value
            // Draw Outline
            _gfx->drawRect(_x, _y, _w, _h, _outlinecolor);
        }
        else if(_type == SLIDER_DOT) {
            _gfx->fillCircle(_x + _pos, _y+(_h/2), _gap, TFT_BLACK);    // Erase previous knob

            _pos = map(value, _min, _max, 0, _w - _gap);
            // Draw Gap
            _gfx->fillRect(_x, _y+(_h/2)-2, _pos, 4, _fillcolor);   // Fill up to value
            _gfx->fillRect(_x + _pos + _gap, _y+(_h/2)-2, _w - _pos - _gap, 4, _nofillcolor);       // Fill Rest
            _oldvalue = value;
            // Draw Knob
            _gfx->fillCircle(_x + _pos, _y+(_h/2), _gap, _knobcolor);    // Fill up to value
            _gfx->fillCircle(_x + _pos, _y+(_h/2), _gap/2, _outlinecolor);    // Fill up to value

        }
    }
}

// *** Slide Constains Horizontal ***
boolean TFT_eSPI_Slider::containsH(int16_t x, int16_t y)
{
    return ((x >= _x) && (x <= (_x + _w)) && (y >= _y) && (y <= (_y + _h)));
}

// *** Get Slide Value, X coordinate  for Horizontal Slide ***
int16_t TFT_eSPI_Slider::getValueH(int16_t v)
{
    int16_t v1 = constrain(v, _x, _x + _w);
    int16_t value = map(v1, _x, _x + _w, _min, _max);
    return value;
}
