/*
Copyright 2017 Fred Sundvik

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 2 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU General Public License for more details.

You should have received a copy of the GNU General Public License
along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// Currently we are assuming that both the backlight and LCD are enabled
// But it's entirely possible to write a custom visualizer that use only
// one of them
#ifndef LCD_BACKLIGHT_ENABLE
#error This visualizer needs that LCD backlight is enabled
#endif

#ifndef LCD_ENABLE
#error This visualizer needs that LCD is enabled
#endif

#include "lcd_backlight_keyframes.h"
#include "led_backlight_keyframes.h"
#include "led.h"
#include "visualizer_keyframes.h"
#include "system/serial_link.h"
#include "ergodox_infinity.h"
#include "string.h"

typedef enum {
    LCD_STATE_INITIAL,
    LCD_STATE_TEMP,
    LCD_STATE_CALC,
} lcd_state_t;

static lcd_state_t lcd_state = LCD_STATE_INITIAL;

typedef struct {
  char* test;
} visualizer_user_data_t;

static visualizer_user_data_t user_data_keyboard = {
  .test = ""
};

const uint8_t logo_doge[512] = {
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x9f, 0xff, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x9f, 0xfe, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x07, 0xfe, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x01, 0x9e, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x00, 0x7b, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x80, 0x30, 0xf7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x00, 0x00, 0xf9, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x83, 0x00, 0xfd, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x87, 0x9c, 0x7d, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x0e, 0x3e, 0xc6, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x1e, 0x6f, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x1f, 0xc5, 0xef, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x3f, 0xc7, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x7f, 0xff, 0xff, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xe1, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xbf, 0xff, 0xc1, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x3f, 0xff, 0xc1, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xfe, 0x3f, 0xff, 0xc1, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xfe, 0x1f, 0xff, 0xe3, 0xbf, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xfe, 0x3f, 0xfa, 0xc3, 0x3f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xfc, 0x1f, 0xfc, 0x01, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xfc, 0x0f, 0xff, 0x07, 0x7f, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xfc, 0x0f, 0xff, 0xfe, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xfe, 0x07, 0xff, 0xfc, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xfe, 0x07, 0xff, 0xf3, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0x81, 0xff, 0xe7, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xfb, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 
    0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff, 0xff
};


bool rlogo(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    (void)animation;

    gdispClear(White);
    gdispGBlitArea(GDISP, 0, 0, LCD_WIDTH, LCD_HEIGHT, 0, 0, LCD_WIDTH, (pixel_t*)logo_doge);

    return false;
}

keyframe_animation_t startup_animationr = {
    .num_frames = 1,
    .loop = false,
    .frame_lengths = {
        0},
    .frame_functions = {
            rlogo,
    },
};

//static const uint32_t initial_color = LCD_COLOR(230, 0, 100);
//static const uint32_t initial_color = LCD_COLOR(255, 255, 255);
static const uint32_t initial_color = LCD_COLOR(0x00, 0x00, 0xFF);
bool initialized = false;

void initialize_user_visualizer(visualizer_state_t* state) {
    gdispSetPowerMode(powerOn);
    state->current_lcd_color = initial_color;
    lcd_backlight_brightness(130);
    lcd_backlight_color(
            LCD_HUE(state->current_lcd_color),
            LCD_SAT(state->current_lcd_color),
            LCD_INT(state->current_lcd_color));

    lcd_state = LCD_STATE_INITIAL;
    start_keyframe_animation(&startup_animationr);
}

void user_visualizer_suspend(visualizer_state_t* state) {
}

void user_visualizer_resume(visualizer_state_t* state) {
}

static keyframe_animation_t color_animation = {
    .num_frames = 2,
    .loop = false,
    .frame_lengths = {gfxMillisecondsToTicks(50), gfxMillisecondsToTicks(100)},
    .frame_functions = {keyframe_no_operation, lcd_backlight_keyframe_animate_color},
};

bool draw_calc(keyframe_animation_t* animation, visualizer_state_t* state) {
    (void)state;
    (void)animation;

    gdispClear(White);
    gdispDrawString(0, 0, user_data_keyboard.test, state->font_fixed5x8, Black);
    gdispDrawString(0, 10, "1337", state->font_fixed5x8, Black);

    return false;
}

static keyframe_animation_t show_calc = {
    .num_frames = 1,
    .loop = false,
    .frame_lengths = {0},
    .frame_functions = {draw_calc},
};

char x[] = "x: \0";
void calc_add(char c) {
  char y[2] = {c, '\0'};
  strcat(x, y);
  user_data_keyboard.test = x;
  visualizer_set_user_data(&user_data_keyboard);

  lcd_state = LCD_STATE_CALC;
  start_keyframe_animation(&show_calc);
  modded(true);
}

void calc_off(void) {
  start_keyframe_animation(&startup_animationr);
  lcd_state = LCD_STATE_INITIAL;
  modded(true);
}


static void get_visualizer_layer_and_color(visualizer_state_t* state) {
    uint8_t saturation = 60;
    if (is_serial_link_master()) {
        saturation = 200;
    }
    //if (state->status.leds & (1u << USB_LED_CAPS_LOCK)) {
    //    saturation = 255;
    //}

    if (state->status.layer & 0x4) {
        state->target_lcd_color = LCD_COLOR(0, saturation, 0xFF);
    }
    else if (state->status.layer & 0x2) {
        state->target_lcd_color = LCD_COLOR(168, saturation, 0xFF);
    }
    else if (state->status.layer & 0x6) {
        state->target_lcd_color = LCD_COLOR(100, saturation, 0xFF);
    }
    else {
        state->target_lcd_color = LCD_COLOR(84, saturation, 0xFF);
    }
}

void update_user_visualizer_state(visualizer_state_t* state, visualizer_keyboard_status_t* prev_status) {
    uint32_t prev_color = state->target_lcd_color;

//    visualizer_user_data_t* user_data_new = (visualizer_user_data_t*)state->status.user_data;
//    visualizer_user_data_t* user_data_old = (visualizer_user_data_t*)prev_status->user_data;

    print("update\n");
//    if (user_data_new->test != user_data_old->test) {
//      print("NOT SAME\n");
//    }
//
//
    get_visualizer_layer_and_color(state);

    if (lcd_state == LCD_STATE_INITIAL) {
        if (is_serial_link_master()) {
          gdispDrawString(60, 0, "wow", state->font_fixed5x8, Black);
        } else {
          gdispDrawString(60, 0, "o_O", state->font_fixed5x8, Black);
        }
        initialized = false;
        lcd_state = LCD_STATE_TEMP;
    }

    if (lcd_state == LCD_STATE_CALC) {
        state->status.modded = false;
        start_keyframe_animation(&show_calc);
        return;
    }

    if (prev_color != state->target_lcd_color) {
        start_keyframe_animation(&color_animation);
    }

}
