#ifndef Button_h
#define Button_h
/***************************************************************************************
// The following button class has been ported over from the Adafruit_GFX library so
// should be compatible.
// A slightly different implementation in this TFT_eSPI library allows the button
// legends to be in any font
***************************************************************************************/
#include <Arduino.h>
#include "../TFT_eSPI.h"

typedef enum {
    ROUND_BOX_TEXT,
    BITMAP,
    XBM,
    TEXT_ONLY
} espi_button_t;

class TFT_eSPI_Button {

 public:
    TFT_eSPI_Button(void);
    ~TFT_eSPI_Button();

    // "Classic" initButton() uses center & size
    void initButton(TFT_eSPI * gfx, int16_t x, int16_t y,
                    uint16_t w, uint16_t h, uint16_t outline, uint16_t fill,
                    uint16_t textcolor, char *label, uint8_t textsize);
    void initButtonG(TFT_eSPI * gfx, int16_t x, int16_t y,
                     uint16_t w, uint16_t h, void *imgOn, void *imgOff, uint16_t size);

    // New/alt initButton() uses upper-left corner & size
    void initButtonUL(TFT_eSPI * gfx, int16_t x1, int16_t y1,
                      uint16_t w, uint16_t h, uint16_t outline, uint16_t fill,
                      uint16_t textcolor, char *label, uint8_t textsize);
    void initButtonTUL(TFT_eSPI * gfx, int16_t x1, int16_t y1,
                       uint16_t w, uint16_t h, uint16_t fill,
                       uint16_t textcolor, uint16_t outline, char *label, char *labelValue, const GFXfont * font);
    void initButtonGUL(TFT_eSPI * gfx, int16_t x1, int16_t y1,
                       uint16_t w, uint16_t h, void *imgOn, void *imgOff, uint16_t size);
    void initButtonXUL(TFT_eSPI * gfx, int16_t x1, int16_t y1,
                       uint16_t w, uint16_t h, uint16_t fill, uint16_t background, uint16_t backgroundOff, void *img);
    void drawButton(boolean inverted = false);
    void drawButtonY(int16_t y, boolean inverted= false);  

    boolean contains(int16_t x, int16_t y);

    void press(boolean p);
    void pressed(boolean p);
    boolean isPressed();
    boolean justPressed();
    boolean justReleased();
    void drawIcon(const unsigned short *icon, int16_t x, int16_t y, int8_t width, int8_t height);
    void setX(int16_t x);
    void setY(int16_t y);
    int16_t  getY(void);

    void selectable(boolean yesno);
    boolean selectable();
    void safety(boolean yesno);
    boolean isSafety();
    void enable();
    void disable();
    boolean disabled();
    char *getLabelValue(void);

    int16_t id;
 private:
     TFT_eSPI * _gfx;
    int16_t _x1, _y1;           // Coordinates of top-left corner
    uint16_t _w, _h;
    uint16_t _size;             //ROUND_BOX_TEXT
    uint16_t _outlinecolor;
    uint16_t _fillcolor, _textcolor;
    espi_button_t _type;
    char *_label;
    char *_labelValue=NULL;

    void *_imgOn;               // BITMAP and XBM types
    void *_imgOff;              //BITMAP
    const GFXfont *_font;
    boolean _currstate, _laststate, _disabled,_selectable,_safety;
};
#endif
