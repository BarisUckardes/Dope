#pragma once

namespace DopeEngine
{
#define DOPE_KEY_UNKNOWN            -1

	/* Printable keys */
#define DOPE_KEY_SPACE              32
#define DOPE_KEY_APOSTROPHE         39  /* ' */
#define DOPE_KEY_COMMA              44  /* , */
#define DOPE_KEY_MINUS              45  /* - */
#define DOPE_KEY_PERIOD             46  /* . */
#define DOPE_KEY_SLASH              47  /* / */
#define DOPE_KEY_0                  48
#define DOPE_KEY_1                  49
#define DOPE_KEY_2                  50
#define DOPE_KEY_3                  51
#define DOPE_KEY_4                  52
#define DOPE_KEY_5                  53
#define DOPE_KEY_6                  54
#define DOPE_KEY_7                  55
#define DOPE_KEY_8                  56
#define DOPE_KEY_9                  57
#define DOPE_KEY_SEMICOLON          59  /* ; */
#define DOPE_KEY_EQUAL              61  /* = */
#define DOPE_KEY_A                  65
#define DOPE_KEY_B                  66
#define DOPE_KEY_C                  67
#define DOPE_KEY_D                  68
#define DOPE_KEY_E                  69
#define DOPE_KEY_F                  70
#define DOPE_KEY_G                  71
#define DOPE_KEY_H                  72
#define DOPE_KEY_I                  73
#define DOPE_KEY_J                  74
#define DOPE_KEY_K                  75
#define DOPE_KEY_L                  76
#define DOPE_KEY_M                  77
#define DOPE_KEY_N                  78
#define DOPE_KEY_O                  79
#define DOPE_KEY_P                  80
#define DOPE_KEY_Q                  81
#define DOPE_KEY_R                  82
#define DOPE_KEY_S                  83
#define DOPE_KEY_T                  84
#define DOPE_KEY_U                  85
#define DOPE_KEY_V                  86
#define DOPE_KEY_W                  87
#define DOPE_KEY_X                  88
#define DOPE_KEY_Y                  89
#define DOPE_KEY_Z                  90
#define DOPE_KEY_LEFT_BRACKET       91  /* [ */
#define DOPE_KEY_BACKSLASH          92  /* \ */
#define DOPE_KEY_RIGHT_BRACKET      93  /* ] */
#define DOPE_KEY_GRAVE_ACCENT       96  /* ` */
#define DOPE_KEY_WORLD_1            161 /* non-US #1 */
#define DOPE_KEY_WORLD_2            162 /* non-US #2 */

/* Function keys */
#define DOPE_KEY_ESCAPE             256
#define DOPE_KEY_ENTER              257
#define DOPE_KEY_TAB                258
#define DOPE_KEY_BACKSPACE          259
#define DOPE_KEY_INSERT             260
#define DOPE_KEY_DELETE             261
#define DOPE_KEY_RIGHT              262
#define DOPE_KEY_LEFT               263
#define DOPE_KEY_DOWN               264
#define DOPE_KEY_UP                 265
#define DOPE_KEY_PAGE_UP            266
#define DOPE_KEY_PAGE_DOWN          267
#define DOPE_KEY_HOME               268
#define DOPE_KEY_END                269
#define DOPE_KEY_CAPS_LOCK          280
#define DOPE_KEY_SCROLL_LOCK        281
#define DOPE_KEY_NUM_LOCK           282
#define DOPE_KEY_PRINT_SCREEN       283
#define DOPE_KEY_PAUSE              284
#define DOPE_KEY_F1                 290
#define DOPE_KEY_F2                 291
#define DOPE_KEY_F3                 292
#define DOPE_KEY_F4                 293
#define DOPE_KEY_F5                 294
#define DOPE_KEY_F6                 295
#define DOPE_KEY_F7                 296
#define DOPE_KEY_F8                 297
#define DOPE_KEY_F9                 298
#define DOPE_KEY_F10                299
#define DOPE_KEY_F11                300
#define DOPE_KEY_F12                301
#define DOPE_KEY_F13                302
#define DOPE_KEY_F14                303
#define DOPE_KEY_F15                304
#define DOPE_KEY_F16                305
#define DOPE_KEY_F17                306
#define DOPE_KEY_F18                307
#define DOPE_KEY_F19                308
#define DOPE_KEY_F20                309
#define DOPE_KEY_F21                310
#define DOPE_KEY_F22                311
#define DOPE_KEY_F23                312
#define DOPE_KEY_F24                313
#define DOPE_KEY_F25                314
#define DOPE_KEY_KP_0               320
#define DOPE_KEY_KP_1               321
#define DOPE_KEY_KP_2               322
#define DOPE_KEY_KP_3               323
#define DOPE_KEY_KP_4               324
#define DOPE_KEY_KP_5               325
#define DOPE_KEY_KP_6               326
#define DOPE_KEY_KP_7               327
#define DOPE_KEY_KP_8               328
#define DOPE_KEY_KP_9               329
#define DOPE_KEY_KP_DECIMAL         330
#define DOPE_KEY_KP_DIVIDE          331
#define DOPE_KEY_KP_MULTIPLY        332
#define DOPE_KEY_KP_SUBTRACT        333
#define DOPE_KEY_KP_ADD             334
#define DOPE_KEY_KP_ENTER           335
#define DOPE_KEY_KP_EQUAL           336
#define DOPE_KEY_LEFT_SHIFT         340
#define DOPE_KEY_LEFT_CONTROL       341
#define DOPE_KEY_LEFT_ALT           342
#define DOPE_KEY_LEFT_SUPER         343
#define DOPE_KEY_RIGHT_SHIFT        344
#define DOPE_KEY_RIGHT_CONTROL      345
#define DOPE_KEY_RIGHT_ALT          346
#define DOPE_KEY_RIGHT_SUPER        347
#define DOPE_KEY_MENU               348

#define DOPE_KEY_LAST               DOPE_KEY_MENU

#define DOPE_MOUSE_BUTTON_1         0
#define DOPE_MOUSE_BUTTON_2         1
#define DOPE_MOUSE_BUTTON_3         2
#define DOPE_MOUSE_BUTTON_4         3
#define DOPE_MOUSE_BUTTON_5         4
#define DOPE_MOUSE_BUTTON_6         5
#define DOPE_MOUSE_BUTTON_7         6
#define DOPE_MOUSE_BUTTON_8         7
#define DOPE_MOUSE_BUTTON_LAST      DOPE_MOUSE_BUTTON_8
#define DOPE_MOUSE_BUTTON_LEFT      DOPE_MOUSE_BUTTON_1
#define DOPE_MOUSE_BUTTON_RIGHT     DOPE_MOUSE_BUTTON_2
#define DOPE_MOUSE_BUTTON_MIDDLE    DOPE_MOUSE_BUTTON_3
}