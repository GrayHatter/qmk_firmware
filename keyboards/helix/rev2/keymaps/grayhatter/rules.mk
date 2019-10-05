# Build Options
#   change to "no" to disable the options, or define them in the Makefile in
#   the appropriate keymap folder that will get included automatically
#
BOOTMAGIC_ENABLE = no       # Virtual DIP switch configuration(+1000)
MOUSEKEY_ENABLE = no       # Mouse keys(+4700)
EXTRAKEY_ENABLE = no       # Audio control and System control(+450)
CONSOLE_ENABLE = no         # Console for debug(+400)
COMMAND_ENABLE = no        # Commands for debug and configuration
NKRO_ENABLE = yes           # Nkey Rollover - if this doesn't work, see here: https://github.com/tmk/tmk_keyboard/wiki/FAQ#nkro-doesnt-work
BACKLIGHT_ENABLE = no      # Enable keyboard backlight functionality
MIDI_ENABLE = no            # MIDI controls
AUDIO_ENABLE = no           # Audio output on port C6
UNICODE_ENABLE = no         # Unicode
BLUETOOTH_ENABLE = no       # Enable Bluetooth with the Adafruit EZ-Key HID
RGBLIGHT_ENABLE = no        # Enable WS2812 RGB underlight.
SWAP_HANDS_ENABLE = no        # Enable one-hand typing
LEADER_ENABLE = yes         # Enable one-hand typing

RGB_MATRIX_ENABLE = WS2812
RGB_MATRIX_KEYPRESSES = yes
RGB_MATRIX_FRAMEBUFFER_EFFECTS = yes
RGB_MATRIX_KEYREACTIVE_ENABLED = yes

HELIX_ROWS = 5              # Helix Rows is 4 or 5
OLED_ENABLE = no            # OLED_ENABLE
LOCAL_GLCDFONT = no         # use each keymaps "helixfont.h" insted of "common/glcdfont.c"
LED_BACK_ENABLE = no        # LED backlight (Enable WS2812 RGB underlight.)
LED_UNDERGLOW_ENABLE = no   # LED underglow (Enable WS2812 RGB underlight.)
LED_ANIMATIONS = no        # LED animations
IOS_DEVICE_ENABLE = no      # connect to IOS device (iPad,iPhone)
Link_Time_Optimization = no # if firmware size over limit, try this option

####  LED_BACK_ENABLE and LED_UNDERGLOW_ENABLE.
####    Do not enable these with audio at the same time.

### Helix keyboard 'default' keymap: convenient command line option
##    make HELIX=<options> helix:defualt
##    option= oled | back | under | na | ios
##    ex.
##      make HELIX=oled          helix:defualt
##      make HELIX=oled,back     helix:defualt
##      make HELIX=oled,under    helix:defualt
##      make HELIX=oled,back,na  helix:defualt
##      make HELIX=oled,back,ios helix:defualt
##
ifneq ($(strip $(HELIX)),)
  ifeq ($(findstring oled,$(HELIX)), oled)
    OLED_ENABLE = yes
  endif
  ifeq ($(findstring back,$(HELIX)), back)
    LED_BACK_ENABLE = yes
  else ifeq ($(findstring under,$(HELIX)), under)
    LED_UNDERGLOW_ENABLE = yes
  endif
  ifeq ($(findstring na,$(HELIX)), na)
    LED_ANIMATIONS = no
  endif
  ifeq ($(findstring ios,$(HELIX)), ios)
    IOS_DEVICE_ENABLE = yes
  endif
  ifeq ($(findstring right,$(HELIX)), right)
    OPT_DEFS += -DHELIX_RIGHTBOARD
  endif
  $(eval $(call HELIX_CUSTOMISE_MSG))
  $(info )
endif

# Uncomment these for checking
#   jp: コンパイル時にカスタマイズの状態を表示したい時はコメントをはずします。
# $(eval $(call HELIX_CUSTOMISE_MSG))
# $(info )

ifneq ($(strip $(HELIX_ROWS)), 4)
  ifneq ($(strip $(HELIX_ROWS)), 5)
    $(error HELIX_ROWS = $(strip $(HELIX_ROWS)) is unexpected value)
  endif
endif
OPT_DEFS += -DHELIX_ROWS=$(strip $(HELIX_ROWS))


ifeq ($(strip $(OLED_ENABLE)), yes)
    OPT_DEFS += -DOLED_ENABLE
endif

ifeq ($(strip $(LOCAL_GLCDFONT)), yes)
    OPT_DEFS += -DLOCAL_GLCDFONT
endif

ifeq ($(strip $(Link_Time_Optimization)),yes)
    EXTRAFLAGS += -flto -DUSE_Link_Time_Optimization
endif



# Do not enable SLEEP_LED_ENABLE. it uses the same timer as BACKLIGHT_ENABLE
SLEEP_LED_ENABLE = no    # Breathing sleep LED during USB suspend
OPT_DEFS += -DRGB_MATRIX_KEYPRESSES -DRGB_MATRIX_FRAMEBUFFER_EFFECTS
# Uncomment these for debugging
# $(info -- RGBLIGHT_ENABLE=$(RGBLIGHT_ENABLE))
# $(info -- OPT_DEFS=$(OPT_DEFS))
# $(info )
