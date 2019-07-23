#include "k_type.h"
#include "rgb_matrix.h"
#include "i2c_master.h"
#include "is31fl3733.h"

// Perform any initialisation required for the other driver functions to work.
void init(void)
{
    i2c_init();
    IS31FL3733_init(0, 0);
    IS31FL3733_init(1, 0);
    for (int i = 0; i < DRIVER_LED_TOTAL; i++) {
        bool enabled = true;
        IS31FL3733_set_led_control_register(i, enabled, enabled, enabled);
    }
    IS31FL3733_update_led_control_registers(0, 0);
    IS31FL3733_update_led_control_registers(1, 1);
}

// Flush any buffered changes to the hardware.
void flush(void)
{
    IS31FL3733_update_pwm_buffers(0, 0);
    IS31FL3733_update_pwm_buffers(1, 1);
}

// Set the colour of a single LED in the buffer.
void set_color(int index, uint8_t r, uint8_t g, uint8_t b)
{
    IS31FL3733_set_color(index, r, g, b);
}

// Set the colour of all LEDS on the keyboard in the buffer.
void set_color_all(uint8_t r, uint8_t g, uint8_t b)
{
    IS31FL3733_set_color_all(r, g, b);
}

const rgb_matrix_driver_t rgb_matrix_driver = {
    .init = init,
    .flush = flush,
    .set_color = set_color,
    .set_color_all = set_color_all,
};

#ifndef NO_SUSPEND_POWER_DOWN
void suspend_power_down_user(void) {
    rgb_matrix_set_suspend_state(true);
}

void suspend_wakeup_init_user(void) {
    rgb_matrix_set_suspend_state(false);
}
#endif

const is31_led g_is31_leds[DRIVER_LED_TOTAL] = {
    [ 0] = { .driver = 0, .r = B_1,  .g = A_1,  .b = C_1  },    // KC_ESCAPE
    [ 1] = { .driver = 0, .r = B_2,  .g = A_2,  .b = C_2  },    // KC_F1
    [ 2] = { .driver = 0, .r = B_3,  .g = A_3,  .b = C_3  },    // KC_F2
    [ 3] = { .driver = 0, .r = B_4,  .g = A_4,  .b = C_4  },    // KC_F3
    [ 4] = { .driver = 0, .r = B_5,  .g = A_5,  .b = C_5  },    // KC_F4
    [ 5] = { .driver = 0, .r = B_6,  .g = A_6,  .b = C_6  },    // KC_F5
    [ 6] = { .driver = 0, .r = B_7,  .g = A_7,  .b = C_7  },    // KC_F6
    [ 7] = { .driver = 0, .r = B_8,  .g = A_8,  .b = C_8  },    // KC_F7
    [ 8] = { .driver = 0, .r = B_9,  .g = A_9,  .b = C_9  },    // KC_F8
    [ 9] = { .driver = 0, .r = B_10, .g = A_10, .b = C_10 },    // KC_F9
    [10] = { .driver = 0, .r = B_11, .g = A_11, .b = C_11 },   // KC_F10
    [11] = { .driver = 0, .r = B_12, .g = A_12, .b = C_12 },   // KC_F11
    [12] = { .driver = 0, .r = B_13, .g = A_13, .b = C_13 },   // KC_F12
    [13] = { .driver = 0, .r = B_14, .g = A_14, .b = C_14 },   // KC_PRSCREEN
    [14] = { .driver = 0, .r = B_15, .g = A_15, .b = C_15 },   // KC_SCROLLLOCK
    [15] = { .driver = 0, .r = B_16, .g = A_16, .b = C_16 },   // KC_PAUSE
    [16] = { .driver = 0, .r = E_1,  .g = D_1,  .b = F_1  },   // KC_GRAVE
    [27] = { .driver = 0, .r = E_2,  .g = D_2,  .b = F_2  },   // KC_1
    [38] = { .driver = 0, .r = E_3,  .g = D_3,  .b = F_3  },   // KC_2
    [49] = { .driver = 0, .r = E_4,  .g = D_4,  .b = F_4  },   // KC_3
    [20] = { .driver = 0, .r = E_5,  .g = D_5,  .b = F_5  },   // KC_4
    [26] = { .driver = 0, .r = E_6,  .g = D_6,  .b = F_6  },   // KC_5
    [22] = { .driver = 0, .r = E_7,  .g = D_7,  .b = F_7  },   // KC_6
    [23] = { .driver = 0, .r = E_8,  .g = D_8,  .b = F_8  },   // KC_7
    [24] = { .driver = 0, .r = E_9,  .g = D_9,  .b = F_9  },   // KC_8
    [25] = { .driver = 0, .r = E_10, .g = D_10, .b = F_10 },   // KC_9
    [26] = { .driver = 0, .r = E_11, .g = D_11, .b = F_11 },   // KC_0
    [27] = { .driver = 0, .r = E_12, .g = D_12, .b = F_12 },   // KC_MINUS
    [28] = { .driver = 0, .r = E_13, .g = D_13, .b = F_13 },   // KC_EQUALS
    [29] = { .driver = 0, .r = E_14, .g = D_14, .b = F_14 },   // KC_BSPACE
    [30] = { .driver = 0, .r = E_15, .g = D_15, .b = F_15 },   // KC_INSERT
    [31] = { .driver = 0, .r = E_16, .g = D_16, .b = F_16 },   // KC_HOME
    [32] = { .driver = 0, .r = H_1,  .g = G_1,  .b = I_1  },   // KC_PGUP
    [33] = { .driver = 0, .r = H_2,  .g = G_2,  .b = I_2  },   // KC_TAB
    [34] = { .driver = 0, .r = H_3,  .g = G_3,  .b = I_3  },   // KC_Q
    [35] = { .driver = 0, .r = H_4,  .g = G_4,  .b = I_4  },   // KC_W
    [36] = { .driver = 0, .r = H_5,  .g = G_5,  .b = I_5  },   // KC_E
    [37] = { .driver = 0, .r = H_6,  .g = G_6,  .b = I_6  },   // KC_R
    [38] = { .driver = 0, .r = H_7,  .g = G_7,  .b = I_7  },   // KC_T
    [39] = { .driver = 0, .r = H_8,  .g = G_8,  .b = I_8  },   // KC_Y
    [40] = { .driver = 0, .r = H_9,  .g = G_9,  .b = I_9  },   // KC_U
    [41] = { .driver = 0, .r = H_10, .g = G_10, .b = I_10 },   // KC_I
    [42] = { .driver = 0, .r = H_11, .g = G_11, .b = I_11 },   // KC_O
    [43] = { .driver = 0, .r = H_12, .g = G_12, .b = I_12 },   // KC_P
    [44] = { .driver = 0, .r = H_13, .g = G_13, .b = I_13 },   // KC_LBRACKET
    [45] = { .driver = 0, .r = H_14, .g = G_14, .b = I_14 },   // KC_RBRACKET
    [46] = { .driver = 0, .r = H_15, .g = G_15, .b = I_15 },   // KC_BSLASH
    [47] = { .driver = 0, .r = H_16, .g = G_16, .b = I_16 },   // KC_DELETE
    [48] = { .driver = 0, .r = K_1,  .g = J_1,  .b = L_1  },   // KC_END
    [49] = { .driver = 0, .r = K_2,  .g = J_2,  .b = L_2  },   // KC_PGDOWN
    [50] = { .driver = 0, .r = K_3,  .g = J_3,  .b = L_3  },   // KC_CAPSLOCK
    [51] = { .driver = 0, .r = K_4,  .g = J_4,  .b = L_4  },   // KC_A
    [52] = { .driver = 0, .r = K_5,  .g = J_5,  .b = L_5  },   // KC_S
    [53] = { .driver = 0, .r = K_6,  .g = J_6,  .b = L_6  },   // KC_D
    [54] = { .driver = 0, .r = K_7,  .g = J_7,  .b = L_7  },   // KC_F
    [55] = { .driver = 0, .r = K_8,  .g = J_8,  .b = L_8  },   // KC_G
    [56] = { .driver = 0, .r = K_9,  .g = J_9,  .b = L_9  },   // KC_H
    [57] = { .driver = 0, .r = K_10, .g = J_10, .b = L_10 },   // KC_J
    [58] = { .driver = 0, .r = K_11, .g = J_11, .b = L_11 },   // KC_K
    [59] = { .driver = 0, .r = K_12, .g = J_12, .b = L_12 },   // KC_L
    [60] = { .driver = 0, .r = K_13, .g = J_13, .b = L_13 },   // KC_SCOLON
    [61] = { .driver = 0, .r = K_14, .g = J_14, .b = L_14 },   // KC_QUOTE
    [62] = { .driver = 0, .r = K_15, .g = J_15, .b = L_15 },   // KC_RETURN
    [63] = { .driver = 0, .r = K_16, .g = J_16, .b = L_16 },   // KC_LSHIFT
    [64] = { .driver = 1, .r = B_1,  .g = A_1,  .b = C_1  },   // KC_Z
    [65] = { .driver = 1, .r = B_2,  .g = A_2,  .b = C_2  },   // KC_X
    [66] = { .driver = 1, .r = B_3,  .g = A_3,  .b = C_3  },   // KC_C
    [67] = { .driver = 1, .r = B_4,  .g = A_4,  .b = C_4  },   // KC_V
    [68] = { .driver = 1, .r = B_5,  .g = A_5,  .b = C_5  },   // KC_B
    [69] = { .driver = 1, .r = B_6,  .g = A_6,  .b = C_6  },   // KC_N
    [70] = { .driver = 1, .r = B_7,  .g = A_7,  .b = C_7  },   // KC_M
    [71] = { .driver = 1, .r = B_8,  .g = A_8,  .b = C_8  },   // KC_COMMA
    [72] = { .driver = 1, .r = B_9,  .g = A_9,  .b = C_9  },   // KC_DOT
    [73] = { .driver = 1, .r = B_10, .g = A_10, .b = C_10 },   // KC_SLASH
    [74] = { .driver = 1, .r = B_11, .g = A_11, .b = C_11 },   // KC_RSHIFT
    [75] = { .driver = 1, .r = B_12, .g = A_12, .b = C_12 },   // KC_UP
    [76] = { .driver = 1, .r = B_13, .g = A_13, .b = C_13 },   // KC_LCTRL
    [77] = { .driver = 1, .r = B_14, .g = A_14, .b = C_14 },   // KC_LGUI
    [78] = { .driver = 1, .r = B_15, .g = A_15, .b = C_15 },   // KC_LALT
    [79] = { .driver = 1, .r = B_16, .g = A_16, .b = C_16 },   // KC_SPACE
    [80] = { .driver = 1, .r = E_1,  .g = D_1,  .b = F_1  },   // KC_RALT
    [81] = { .driver = 1, .r = E_2,  .g = D_2,  .b = F_2  },   // KC_RGUI
    [82] = { .driver = 1, .r = E_3,  .g = D_3,  .b = F_3  },   // KC_RMENU
    [83] = { .driver = 1, .r = E_4,  .g = D_4,  .b = F_4  },   // KC_RCTRL
    [84] = { .driver = 1, .r = E_5,  .g = D_5,  .b = F_5  },   // KC_LEFT
    [85] = { .driver = 1, .r = E_6,  .g = D_6,  .b = F_6  },   // KC_DOWN
    [86] = { .driver = 1, .r = E_7,  .g = D_7,  .b = F_7  },   // KC_RIGHT

    // Underglow
    [ 87] = { .driver = 1, .r = E_8,  .g = D_8,  .b = F_8  },
    [ 88] = { .driver = 1, .r = E_9,  .g = D_9,  .b = F_9  },
    [ 89] = { .driver = 1, .r = E_10, .g = D_10, .b = F_10 },
    [ 90] = { .driver = 1, .r = E_11, .g = D_11, .b = F_11 },
    [ 91] = { .driver = 1, .r = E_12, .g = D_12, .b = F_12 },
    [ 92] = { .driver = 1, .r = E_13, .g = D_13, .b = F_13 },
    [ 93] = { .driver = 1, .r = E_14, .g = D_14, .b = F_14 },
    [ 94] = { .driver = 1, .r = E_15, .g = D_15, .b = F_15 },
    [ 95] = { .driver = 1, .r = E_16, .g = D_16, .b = F_16 },
    [ 96] = { .driver = 1, .r = H_1,  .g = G_1,  .b = I_1  },
    [ 97] = { .driver = 1, .r = H_2,  .g = G_2,  .b = I_2  },
    [ 98] = { .driver = 1, .r = H_3,  .g = G_3,  .b = I_3  },
    [ 99] = { .driver = 1, .r = H_4,  .g = G_4,  .b = I_4  },
    [100] = { .driver = 1, .r = H_5,  .g = G_5,  .b = I_5  },
    [101] = { .driver = 1, .r = H_6,  .g = G_6,  .b = I_6  },
    [102] = { .driver = 1, .r = H_7,  .g = G_7,  .b = I_7  },
    [103] = { .driver = 1, .r = H_8,  .g = G_8,  .b = I_8  },
    [104] = { .driver = 1, .r = H_9,  .g = G_9,  .b = I_9  },
    [105] = { .driver = 1, .r = H_10, .g = G_10, .b = I_10 },
    [106] = { .driver = 1, .r = H_11, .g = G_11, .b = I_11 },
    [107] = { .driver = 1, .r = H_12, .g = G_12, .b = I_12 },
    [108] = { .driver = 1, .r = H_13, .g = G_13, .b = I_13 },
    [109] = { .driver = 1, .r = H_14, .g = G_14, .b = I_14 },
    [110] = { .driver = 1, .r = H_15, .g = G_15, .b = I_15 },
    [111] = { .driver = 1, .r = H_16, .g = G_16, .b = I_16 },
    [112] = { .driver = 1, .r = K_1,  .g = J_1,  .b = L_1  },
    [113] = { .driver = 1, .r = K_2,  .g = J_2,  .b = L_2  },
    [114] = { .driver = 1, .r = K_3,  .g = J_3,  .b = L_3  },
    [115] = { .driver = 1, .r = K_4,  .g = J_4,  .b = L_4  },
    [116] = { .driver = 1, .r = K_5,  .g = J_5,  .b = L_5  },
    [117] = { .driver = 1, .r = K_6,  .g = J_6,  .b = L_6  },
    [118] = { .driver = 1, .r = K_7,  .g = J_7,  .b = L_7  },
};

led_config_t g_led_config = {
    // Key Matrix to LED Index
    .matrix_co = LAYOUT(
        0,  1,  2,  3,  4,  5,  6,  7,  8,  9,  10, 11, 12,     13, 14, 15,
        16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32,
        33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49,
        50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62,
        63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74,             75,
        76, 77, 78,       79,       80, 81, 82, 83,             84, 85, 86,
        NO_LED
    ),
//     {   /* 1       2       3       4       5       6       7       8       9       10     */
// /* 1  */ { 0,      1,      2,      3,      4,      5,      6,      7,      8,      9      },
// /* 2  */ { 10,     11,     12,     13,     14,     15,     16,     17,     18,     19     },
// /* 3  */ { 20,     21,     22,     23,     24,     25,     26,     27,     28,     NO_LED },
// /* 4  */ { 29,     NO_LED, 30,     31,     32,     33,     34,     35,     36,     37     },
// /* 5  */ { 38,     39,     40,     41,     42,     43,     44,     45,     46,     NO_LED },
// /* 6  */ { 47,     48,     49,     50,     51,     52,     53,     54,     55,     56     },
// /* 7  */ { 57,     58,     59,     60,     61,     NO_LED, 62,     NO_LED, 63,     NO_LED },
// /* 8  */ { 64,     65,     66,     67,     68,     69,     70,     71,     72,     73     },
// /* 9  */ { NO_LED, 74,     NO_LED, 75,     76,     77,     78,     79,     80,     81     },
// /* 10 */ { 82,     83,     84,     85,     86,     NO_LED, NO_LED, NO_LED, NO_LED, NO_LED },
//     },

    // LED Index to Physical Position
    .point = {
        // KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7
        {   7,   5 }, {  31,   5 }, {  43,   5 }, {  55,   5 },
        {  67,   5 }, {  85,   5 }, {  97,   5 }, { 109,   5 },
        // KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SLCK, KC_PAUS
        { 121,   5 }, { 139,   5 }, { 151,   5 }, { 163,   5 },
        { 175,   5 }, { 193,   5 }, { 205,   5 }, { 217,   5 },

        // KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,
        {   7,  20 }, {  19,  20 }, {  31,  20 }, {  43,  20 },
        {  55,  20 }, {  67,  20 }, {  79,  20 }, {  91,  20 },
        // KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME, KC_PGUP
        { 103,  20 }, { 115,  20 }, { 127,  20 }, { 139,  20 },
        { 151,  20 }, { 169,  20 }, { 193,  20 }, { 205,  20 },
        { 217,  20 },

        // KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U,
        {  10,  30 }, {  25,  30 }, {  37,  30 }, {  49,  30 },
        {  61,  30 }, {  73,  30 }, {  85,  30 }, {  97,  30 },
        // KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_END, KC_PGDN
        { 109,  30 }, { 121,  30 }, { 133,  30 }, { 145,  30 },
        { 157,  30 }, { 172,  30 }, { 193,  30 }, { 205,  30 },
        { 217,  30 },

        // KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J,
        {  11,  39 }, {  28,  39 }, {  40,  39 }, {  52,  39 },
        {  64,  39 }, {  76,  39 }, {  88,  39 }, { 100,  39 },
        // KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT
        { 112,  39 }, { 124,  39 }, { 136,  39 }, { 148,  39 },
        { 168,  39 },

        // KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M,
        {  14,  49 }, {  34,  49 }, {  46,  49 }, {  58,  49 },
        {  70,  49 }, {  82,  49 }, {  94,  49 }, { 106,  49 },
        // KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP
        { 118,  49 }, { 130,  49 }, { 142,  49 }, { 165,  49 },
        { 205,  49 },

        // KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_APP, KC_RCTL,
        {   8,  59 }, {  23,  59 }, {  38,  59 }, {  83,  59 },
        { 129,  59 }, { 144,  59 }, { 159,  59 }, { 174,  59 },
        // KC_LEFT, KC_DOWN, KC_RGHT
        { 193,  59 }, { 205,  59 }, { 217,  59 },

        // Underglow / Border
        { 224,  64 }, { 204,  64 }, { 186,  64 }, { 167,  64 },
        { 149,  64 }, { 130,  64 }, { 112,  64 }, {  94,  64 },
        {  75,  64 }, {  57,  64 }, {  38,  64 }, {  20,  64 },
        {   0,  64 }, {   0,  47 }, {   0,  32 }, {   0,  17 },
        {   0,   0 }, {  20,   0 }, {  38,   0 }, {  57,   0 },
        {  75,   0 }, {  94,   0 }, { 112,   0 }, { 130,   0 },
        { 149,   0 }, { 167,   0 }, { 186,   0 }, { 204,   0 },
        { 224,   0 }, { 224,  17 }, { 224,  32 }, { 224,  47 },
    },

    // LED Index to Flag
    .flags = {
        // KC_ESC, KC_F1, KC_F2, KC_F3, KC_F4, KC_F5, KC_F6, KC_F7,
        1, 4, 4, 4, 4, 1, 1, 1,
        // KC_F8, KC_F9, KC_F10, KC_F11, KC_F12, KC_PSCR, KC_SLCK, KC_PAUS
        1, 4, 4, 4, 4, 1, 1, 1,

        // KC_GRV, KC_1, KC_2, KC_3, KC_4, KC_5, KC_6, KC_7,
        4, 4, 4, 4, 4, 4, 4, 4,
        // KC_8, KC_9, KC_0, KC_MINS, KC_EQL, KC_BSPC, KC_INS, KC_HOME
        4, 4, 4, 4, 4, 1, 1, 1,
        // KC_PGUP
        1,

        // KC_TAB, KC_Q, KC_W, KC_E, KC_R, KC_T, KC_Y, KC_U,
        1, 4, 4, 4, 4, 4, 4, 4,
        // KC_I, KC_O, KC_P, KC_LBRC, KC_RBRC, KC_BSLS, KC_DEL, KC_END
        4, 4, 4, 4, 4, 4, 1, 1,
        // KC_PGDN
        1,

        // KC_CAPS, KC_A, KC_S, KC_D, KC_F, KC_G, KC_H, KC_J,
        1, 4, 4, 4, 4, 4, 4, 4,
        // KC_K, KC_L, KC_SCLN, KC_QUOT, KC_ENT
        4, 4, 4, 4, 1,

        // KC_LSFT, KC_Z, KC_X, KC_C, KC_V, KC_B, KC_N, KC_M,
        1, 4, 4, 4, 4, 4, 4, 4,
        // KC_COMM, KC_DOT, KC_SLSH, KC_RSFT, KC_UP
        4, 4, 4, 1, 1,

        // KC_LCTL, KC_LGUI, KC_LALT, KC_SPC, KC_RALT, MO(1), KC_APP, KC_RCTL,
        1, 1, 1, 4, 1, 1, 1, 1,
        // KC_LEFT, KC_DOWN, KC_RGHT
        1, 1, 1,

        // Underglow / Border
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
        2, 2, 2, 2,
    },
};
