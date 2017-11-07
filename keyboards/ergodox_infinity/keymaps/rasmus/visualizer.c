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

#include <stdio.h>
#include "lcd_backlight_keyframes.h"
#include "led_backlight_keyframes.h"
#include "led.h"
#include "visualizer_keyframes.h"
#include "system/serial_link.h"
#include "ergodox_infinity.h"
#include "string.h"
#include "chprintf.h"


typedef enum {
    LCD_STATE_INITIAL,
    LCD_STATE_TEMP,
    LCD_STATE_CALC,
} lcd_state_t;

static lcd_state_t lcd_state = LCD_STATE_INITIAL;


typedef struct {
  double stack[4];
} visualizer_user_data_t;

static visualizer_user_data_t user_data_keyboard = {
  .stack = {0}
};

_Static_assert(sizeof(visualizer_user_data_t) <= VISUALIZER_USER_DATA_SIZE,
    "Please increase the VISUALIZER_USER_DATA_SIZE.");

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

    char output1[20];
    chsnprintf(output1, 20, "1: %.5f\0", user_data_keyboard.stack[0]);
    char output2[20];
    chsnprintf(output2, 20, "2: %.5f\0", user_data_keyboard.stack[1]);
    char output3[20];
    chsnprintf(output3, 20, "3: %.5f\0", user_data_keyboard.stack[2]);
    char output4[20];
    chsnprintf(output4, 20, "4: %.5f\0", user_data_keyboard.stack[3]);

    gdispDrawString(0, 0, output4, state->font_fixed5x8, Black);
    gdispDrawString(0, 8, output3, state->font_fixed5x8, Black);
    gdispDrawString(0, 16, output2, state->font_fixed5x8, Black);
    gdispDrawString(0, 24, output1, state->font_fixed5x8, Black);

    return false;
}

static keyframe_animation_t show_calc = {
    .num_frames = 1,
    .loop = false,
    .frame_lengths = {0},
    .frame_functions = {draw_calc},
};

#define STACK_SIZE 4

double stack[STACK_SIZE];

char buffer[10] = {'\0'};
double xd = 0;

double stof(const char* s){
  double rez = 0, fact = 1;
  if (*s == '-'){
    s++;
    fact = -1;
  };
  for (int point_seen = 0; *s; s++){
    if (*s == '.'){
      point_seen = 1; 
      continue;
    };
    int d = *s - '0';
    if (d >= 0 && d <= 9){
      if (point_seen) fact /= 10.0f;
      rez = rez * 10.0 + (double)d;
    };
  };
  return rez * fact;
};

bool reset = false;

void update_buffer(void) {
  user_data_keyboard.stack[0] = stack[0];
  user_data_keyboard.stack[1] = stack[1];
  user_data_keyboard.stack[2] = stack[2];
  user_data_keyboard.stack[3] = stack[3];

  visualizer_set_user_data(&user_data_keyboard);

  lcd_state = LCD_STATE_CALC;
  start_keyframe_animation(&show_calc);
}

double pop(void) {
  double val = stack[0];
  memmove(stack, stack + 1, (STACK_SIZE - 1) * sizeof(*stack));
  stack[STACK_SIZE - 1] = 0.0;
  return val;
}

void push(double v) {
  memmove(stack + 1, stack, (STACK_SIZE - 1) * sizeof(*stack));
  stack[0] = v;
}

void calc_on(void) {
  buffer[0] = '\0';
  memset(stack, 0, sizeof(stack));
  update_buffer();
}
bool dot_seen = false;

void calc_addChar(char c) {
  if (reset) {
    if (stack[1] == 0) {
      push(stack[0]);
    }
    buffer[0] = '\0';
    reset = false;
  }
  if (strlen(buffer) < sizeof(buffer)) {
    if (c == '.') {
      dot_seen = true;
      return;
    }
    if (dot_seen) {
      char tmp[3] = {'.', c, '\0'};
      strcat(buffer, tmp);
      dot_seen = false;
    } else {
      char tmp[2] = {c, '\0'};
      strcat(buffer, tmp);
    }
    stack[0] = stof(buffer);
  }
  update_buffer();
}

void calc_add(void) {
  push(pop() + pop());
  reset = true;
  update_buffer();
}

void calc_divide(void) {
  double val1 = pop();
  double val2 = pop();
  push(val2 / val1);
  reset = true;
  update_buffer();
}

void calc_multiply(void) {
  push(pop() * pop());
  reset = true;
  update_buffer();
}

void calc_subtract(void) {
  double val1 = pop();
  double val2 = pop();
  push(val2 - val1);
  reset = true;
  update_buffer();
}

void calc_del(void) {
  buffer[strlen(buffer)-1] = 0;
  stack[0] = stof(buffer);
  update_buffer();
}

void calc_enter(void) {
  push(stack[0]);
  reset = true;
  update_buffer();
}

void calc_off(void) {
  start_keyframe_animation(&startup_animationr);
  lcd_state = LCD_STATE_INITIAL;
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
        start_keyframe_animation(&show_calc);
        return;
    }

    if (prev_color != state->target_lcd_color) {
        start_keyframe_animation(&color_animation);
    }

}
