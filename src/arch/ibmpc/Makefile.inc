# src/arch/ibmpc/Makefile.inc

rel := src/arch/ibmpc

DIRS += $(rel)
DIST += $(rel)/Makefile.inc

# ----------------------------------------------------------------------

PCE_IBMPC_CFLAGS  := $(CFLAGS_DEFAULT)
PCE_IBMPC_LDFLAGS := $(LDFLAGS_DEFAULT)
PCE_IBMPC_LIBS    := $(LIBS)

ifeq "$(PCE_ENABLE_SDL)" "1"
	PCE_IBMPC_CFLAGS += $(PCE_SDL_CFLAGS)
	PCE_IBMPC_LIBS += $(PCE_SDL_LIBS)
endif

ifeq "$(PCE_ENABLE_X11)" "1"
	PCE_IBMPC_CFLAGS += $(PCE_X11_CFLAGS)
	PCE_IBMPC_LIBS += $(PCE_X11_LIBS)
endif

ifeq "$(PCE_HOST_WINDOWS)" "1"
	PCE_IBMPC_LIBS += -mconsole
endif

ifeq "$(PCE_ENABLE_READLINE)" "1"
	PCE_IBMPC_LIBS += $(PCE_READLINE_LIBS)
endif

$(rel)/%.o: $(rel)/%.c
	$(QP)echo "  CC     $@"
	$(QR)$(CC) -c $(PCE_IBMPC_CFLAGS) -o $@ $<

# ----------------------------------------------------------------------

PCE_IBMPC_BAS  := \
	atari-pc \
	cmd \
	covox \
	ems \
	hook \
	ibmpc \
	int13 \
	keyboard \
	m24 \
	main \
	msg \
	speaker \
	xms

PCE_IBMPC_SRC  := $(foreach f,$(PCE_IBMPC_BAS),$(rel)/$(f).c)
PCE_IBMPC_OBJ  := $(foreach f,$(PCE_IBMPC_BAS),$(rel)/$(f).o)
PCE_IBMPC_HDR  := $(foreach f,$(PCE_IBMPC_BAS),$(rel)/$(f).h)
PCE_IBMPC_MAN1 := $(rel)/pce-ibmpc.1
PCE_IBMPC_ETC  := $(rel)/pce-ibmpc.cfg
PCE_IBMPC_BIN  := $(rel)/pce-ibmpc$(EXEEXT)

PCE_IBMPC_OBJ_EXT := \
	src/chipset/clock/mc146818a.o \
	src/chipset/82xx/e8237.o \
	src/chipset/82xx/e8250.o \
	src/chipset/82xx/e8253.o \
	src/chipset/82xx/e8255.o \
	src/chipset/82xx/e8259.o \
	src/chipset/82xx/e8272.o \
	src/chipset/e6845.o \
	src/devices/cassette.o \
	src/devices/device.o \
	src/devices/fdc.o \
	src/devices/hdc.o \
	src/devices/memory.o \
	src/devices/nvram.o \
	src/devices/parport.o \
	src/devices/serport.o \
	src/drivers/options.o \
	src/lib/brkpt.o \
	src/lib/cfg.o \
	src/lib/ciff.o \
	src/lib/cmd.o \
	src/lib/console.o \
	src/lib/endian.o \
	src/lib/getopt.o \
	src/lib/inidsk.o \
	src/lib/iniram.o \
	src/lib/initerm.o \
	src/lib/log.o \
	src/lib/monitor.o \
	src/lib/msg.o \
	src/lib/msgdsk.o \
	src/lib/path.o \
	src/lib/string.o \
	src/lib/sysdep.o \
	$(LIBPCE_LOAD_OBJ) \
	$(LIBINI_OBJ) \
	$(CPU_8086_OBJ) \
	$(DEV_VID_OBJ) \
	$(DRV_BLK_OBJ) \
	$(DRV_PRI_OBJ) \
	$(DRV_PSI_OBJ) \
	$(DRV_PTI_OBJ) \
	$(DRV_CHR_OBJ) \
	$(DRV_SND_OBJ) \
	$(DRV_TRM_OBJ)

ifeq "$(PCE_ENABLE_TUN)" "1"
PCE_IBMPC_OBJ_EXT += src/lib/tun.o
endif

ifeq "$(PCE_BUILD_IBMPC)" "1"
BIN  += $(PCE_IBMPC_BIN)
ETC  += $(PCE_IBMPC_ETC)
MAN1 += $(PCE_IBMPC_MAN1)
endif

CLN  += $(PCE_IBMPC_BIN) $(PCE_IBMPC_OBJ) $(PCE_IBMPC_ETC)
DIST += $(PCE_IBMPC_SRC) $(PCE_IBMPC_HDR) $(PCE_IBMPC_MAN1)
DIST += $(rel)/pce-ibmpc.cfg.in $(rel)/pce.inc $(rel)/pce-lib.inc

$(rel)/cmd.o:		$(rel)/cmd.c
$(rel)/covox.o:		$(rel)/covox.c
$(rel)/ems.o:		$(rel)/ems.c
$(rel)/hook.o:		$(rel)/hook.c
$(rel)/ibmpc.o:		$(rel)/ibmpc.c
$(rel)/int13.o:		$(rel)/int13.c
$(rel)/keyboard.o:	$(rel)/keyboard.c
$(rel)/m24.o:		$(rel)/m24.c
$(rel)/main.o:		$(rel)/main.c
$(rel)/msg.o:		$(rel)/msg.c
$(rel)/speaker.o:	$(rel)/speaker.c
$(rel)/xms.o:		$(rel)/xms.c

$(rel)/pce-ibmpc$(EXEEXT): $(PCE_IBMPC_OBJ_EXT) $(PCE_IBMPC_OBJ)
	$(QP)echo "  LD     $@"
	$(QR)$(LD) $(PCE_IBMPC_LDFLAGS) -o $@ $(PCE_IBMPC_OBJ) $(PCE_IBMPC_OBJ_EXT) $(PCE_IBMPC_LIBS) -lm

$(rel)/pce-ibmpc.cfg: $(rel)/pce-ibmpc.cfg.in
	$(QP)echo "  SED    $@"
	$(QR)sed -e "s]PCE_DIR_DATA]$(datadir)]g" < $< > $@
