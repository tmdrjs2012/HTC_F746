// 4.17.0 0x55cac986
// Generated by imageconverter. Please, do not edit!

#include <BitmapDatabase.hpp>
#include <touchgfx/Bitmap.hpp>

extern const unsigned char image_blue_buttons_round_edge_icon_button[]; // BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_ID = 0, Size: 60x60 pixels
extern const unsigned char image_blue_buttons_round_edge_icon_button_pressed[]; // BITMAP_BLUE_BUTTONS_ROUND_EDGE_ICON_BUTTON_PRESSED_ID = 1, Size: 60x60 pixels
extern const unsigned char image_blue_icons_down_arrow_32[]; // BITMAP_BLUE_ICONS_DOWN_ARROW_32_ID = 2, Size: 30x17 pixels
extern const unsigned char image_blue_icons_up_arrow_32[]; // BITMAP_BLUE_ICONS_UP_ARROW_32_ID = 3, Size: 30x17 pixels
extern const unsigned char image_blue_pageindicator_dot_indicator_small_highlight[]; // BITMAP_BLUE_PAGEINDICATOR_DOT_INDICATOR_SMALL_HIGHLIGHT_ID = 4, Size: 15x15 pixels
extern const unsigned char image_blue_pageindicator_dot_indicator_small_normal[]; // BITMAP_BLUE_PAGEINDICATOR_DOT_INDICATOR_SMALL_NORMAL_ID = 5, Size: 15x15 pixels
extern const unsigned char image_blue_togglebars_toggle_round_large_button_off[]; // BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_OFF_ID = 6, Size: 128x38 pixels
extern const unsigned char image_blue_togglebars_toggle_round_large_button_on[]; // BITMAP_BLUE_TOGGLEBARS_TOGGLE_ROUND_LARGE_BUTTON_ON_ID = 7, Size: 128x38 pixels
extern const unsigned char image_timer_2pro[]; // BITMAP_TIMER_2PRO_ID = 8, Size: 26x26 pixels

const touchgfx::Bitmap::BitmapData bitmap_database[] = {
    { image_blue_buttons_round_edge_icon_button, 0, 60, 60, 7, 6, 46, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 46, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_buttons_round_edge_icon_button_pressed, 0, 60, 60, 7, 6, 46, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 46, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_icons_down_arrow_32, 0, 30, 17, 11, 10, 8, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 4, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_icons_up_arrow_32, 0, 30, 17, 11, 3, 8, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 4, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_pageindicator_dot_indicator_small_highlight, 0, 15, 15, 3, 3, 9, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 9, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_pageindicator_dot_indicator_small_normal, 0, 15, 15, 3, 3, 9, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 9, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_togglebars_toggle_round_large_button_off, 0, 128, 38, 13, 1, 102, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 36, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_blue_togglebars_toggle_round_large_button_on, 0, 128, 38, 13, 1, 102, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 36, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 },
    { image_timer_2pro, 0, 26, 26, 0, 0, 0, ((uint8_t)touchgfx::Bitmap::ARGB8888) >> 3, 0, ((uint8_t)touchgfx::Bitmap::ARGB8888) & 0x7 }
};

namespace BitmapDatabase
{
const touchgfx::Bitmap::BitmapData* getInstance()
{
    return bitmap_database;
}

uint16_t getInstanceSize()
{
    return (uint16_t)(sizeof(bitmap_database) / sizeof(touchgfx::Bitmap::BitmapData));
}
} // namespace BitmapDatabase
