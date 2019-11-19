/***************************************************************************************
** Code for the GFX button UI element
** Grabbed from Adafruit_GFX library and enhanced to handle any label font
***************************************************************************************/
#include "Button.h"
#include "../TFT_eSPI.h"
TFT_eSPI_Button::TFT_eSPI_Button(void)
{
    _gfx = 0;
}

// Classic initButton() function: pass center & size
void TFT_eSPI_Button::initButton(TFT_eSPI * gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
                                 uint16_t outline, uint16_t fill, uint16_t textcolor, char *label, uint8_t textsize)
{
    _type = ROUND_BOX_TEXT;
    // Tweak arguments and pass to the newer initButtonUL() function...
    initButtonUL(gfx, x - (w / 2), y - (h / 2), w, h, outline, fill, textcolor, label, textsize);
}

void TFT_eSPI_Button::initButtonG(TFT_eSPI * gfx, int16_t x, int16_t y, uint16_t w, uint16_t h,
                                  void *imgOn, void *imgOff, uint16_t size)
{
    // Tweak arguments and pass to the newer initButtonUL() function...
    initButtonGUL(gfx, x - (w / 2), y - (h / 2), w, h, imgOn, imgOff, size);
}

// Newer function instead accepts upper-left corner & size
void TFT_eSPI_Button::initButtonUL(TFT_eSPI * gfx, int16_t x1, int16_t y1, uint16_t w, uint16_t h,
                                   uint16_t outline, uint16_t fill, uint16_t textcolor, char *label, uint8_t textsize)
{
    _x1 = x1;
    _y1 = y1;
    _w = w;
    _h = h;
    _outlinecolor = outline;
    _fillcolor = fill;
    _textcolor = textcolor;
    _size = textsize;
    _gfx = gfx;
    _type = ROUND_BOX_TEXT;
    _label = label;
    _laststate = _currstate = false;
    _disabled = false;
}

// Newer function instead accepts upper-left corner & size
void TFT_eSPI_Button::initButtonTUL(TFT_eSPI * gfx, int16_t x1, int16_t y1, uint16_t w, uint16_t h,
                                    uint16_t fill, uint16_t textcolor, uint16_t outline,
                                    char *label, char *labelValue, const GFXfont * font)
{
    _x1 = x1;
    _y1 = y1;
    _w = w;
    _h = h;
    _fillcolor = fill;
    _textcolor = textcolor;
    _outlinecolor = outline;
    _font = font;
    _gfx = gfx;
    _type = TEXT_ONLY;
    _label = label;
    _labelValue = labelValue;

    _laststate = _currstate = false;
    _disabled = false;
}

// Newer function instead accepts upper-left corner & size
void TFT_eSPI_Button::initButtonGUL(TFT_eSPI * gfx, int16_t x1, int16_t y1, uint16_t w, uint16_t h,
                                    void *imgOn, void *imgOff, uint16_t size)
{
    _x1 = x1;
    _y1 = y1;
    _w = w;
    _h = h;
    _size = size;
    _gfx = gfx;
    _type = BITMAP;
    _imgOn = imgOn;
    _imgOff = imgOff;
    _laststate = _currstate = false;
    _disabled = false;
}

// Newer function instead accepts upper-left corner & size
void TFT_eSPI_Button::initButtonXUL(TFT_eSPI * gfx, int16_t x1, int16_t y1,
                                    uint16_t w, uint16_t h,
                                    uint16_t fill, uint16_t background, uint16_t backgroundOff, void *img)
{
    _x1 = x1;
    _y1 = y1;
    _w = w;
    _h = h;
    _fillcolor = fill;
    _textcolor = background;
    _outlinecolor = backgroundOff;
    _gfx = gfx;
    _type = XBM;
    _imgOn = img;
    _laststate = _currstate = false;
    _disabled = false;
}

void TFT_eSPI_Button::drawButton(boolean inverted)
{

    uint16_t fill, outline, text;
    if (_disabled) {
        fill = _fillcolor;
        outline = _outlinecolor;
        text = TFT_LIGHTGREY;
    } else {
        if (!inverted) {
            fill = _fillcolor;
            outline = _outlinecolor;
            text = _textcolor;
        } else {
            fill = _textcolor;
            outline = _outlinecolor;
            text = _fillcolor;
        }
    }
    if (_type == ROUND_BOX_TEXT) {

        uint8_t r = min(_w, _h) / 4;    // Corner radius
        _gfx->fillRoundRect(_x1, _y1, _w, _h, r, fill);
        _gfx->drawRoundRect(_x1, _y1, _w, _h, r, outline);

        _gfx->setTextColor(text);
        _gfx->setTextSize(_size);

        uint8_t tempdatum = _gfx->getTextDatum();
        _gfx->setTextDatum(MC_DATUM);
        _gfx->drawString(_label, _x1 + (_w / 2), _y1 + (_h / 2));
        _gfx->setTextDatum(tempdatum);
    } else if (_type == BITMAP) {
        if (!inverted) {
            drawIcon((const unsigned short *)_imgOn, _x1, _y1, _w, _h);
        } else {
            drawIcon((const unsigned short *)_imgOff, _x1, _y1, _w, _h);
        }
    } else if (_type == XBM) {
        _gfx->drawXBitmap(_x1, _y1, (const unsigned char *)_imgOn, _w, _h, text, fill);
    } else if (_type == TEXT_ONLY) {
        _gfx->fillRect(_x1, _y1, _w, _h, fill);
        if (_labelValue)
            _gfx->fillRect(_x1, _y1 + _h, _w, _h, _fillcolor);
        _gfx->setTextColor(text);

        uint8_t tempdatum = _gfx->getTextDatum();
        _gfx->setTextDatum(ML_DATUM);
        _gfx->setFreeFont(_font);
        _gfx->drawString(_label, _x1, _y1 + (_h / 2));
        if (_labelValue) {
            _gfx->setTextColor(_outlinecolor);
            _gfx->drawString(_labelValue, _x1 + 10, _y1 + _h + (_h / 2));
        }
        _gfx->setTextDatum(tempdatum);
    }

}

boolean TFT_eSPI_Button::contains(int16_t x, int16_t y)
{
    if (_disabled)
        return false;
    return ((x >= _x1) && (x < (_x1 + _w)) && (y >= _y1) && (y < (_y1 + _h)));
}

void TFT_eSPI_Button::press(boolean p)
{
    _laststate = _currstate;
    _currstate = p;
}

void TFT_eSPI_Button::pressed(boolean p)
{
    _laststate = _currstate = p;
}

void TFT_eSPI_Button::enable(void)
{
    _disabled = false;
}

void TFT_eSPI_Button::disable(void)
{
    _disabled = true;
}

boolean TFT_eSPI_Button::disabled(void)
{
    return _disabled;
}

boolean TFT_eSPI_Button::isPressed()
{
    return _currstate;
}

boolean TFT_eSPI_Button::justPressed()
{
    return (_currstate && !_laststate);
}

boolean TFT_eSPI_Button::justReleased()
{
    return (!_currstate && _laststate);
}

#define BUFF_SIZE 64
void TFT_eSPI_Button::drawIcon(const unsigned short *icon, int16_t x, int16_t y, int8_t width, int8_t height)
{

    uint16_t pix_buffer[BUFF_SIZE];     // Pixel buffer (16 bits per pixel)

    _gfx->startWrite();

    // Set up a window the right size to stream pixels into
    _gfx->setAddrWindow(x, y, width, height);

    // Work out the number whole buffers to send
    uint16_t nb = ((uint16_t) height * width) / BUFF_SIZE;

    // Fill and send "nb" buffers to TFT
    for (int i = 0; i < nb; i++) {
        for (int j = 0; j < BUFF_SIZE; j++) {
            pix_buffer[j] = pgm_read_word(&icon[i * BUFF_SIZE + j]);
        }
        _gfx->pushColors(pix_buffer, BUFF_SIZE);
    }

    // Work out number of pixels not yet sent
    uint16_t np = ((uint16_t) height * width) % BUFF_SIZE;

    // Send any partial buffer left over
    if (np) {
        for (int i = 0; i < np; i++)
            pix_buffer[i] = pgm_read_word(&icon[nb * BUFF_SIZE + i]);
        _gfx->pushColors(pix_buffer, np);
    }

    _gfx->endWrite();
}

void TFT_eSPI_Button::setX(int16_t x)
{
    _x1 = x;
}

void TFT_eSPI_Button::setY(int16_t y)
{
    _y1 = y;
}

void TFT_eSPI_Button::setLabelValue(char *s)
{
    _labelValue = s;
}
