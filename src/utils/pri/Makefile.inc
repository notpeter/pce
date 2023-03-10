# src/utils/pri/Makefile.inc

rel := src/utils/pri

DIRS += $(rel)
DIST += $(rel)/Makefile.inc

PRI_BAS := \
	comment \
	decode \
	delete \
	edit \
	encode \
	event \
	info \
	list \
	merge \
	new \
	pri-mac-gcr \
	rotate \
	text-ibm-fm \
	text-ibm-mfm \
	text-mac-gcr \
	text-raw \
	text \
	weak \
	main

PRI_SRC := $(foreach f,$(PRI_BAS),$(rel)/$(f).c)
PRI_OBJ := $(foreach f,$(PRI_BAS),$(rel)/$(f).o)
PRI_HDR := $(rel)/main.h $(rel)/pri-mac-gcr.h $(rel)/text.h
PRI_MAN1 := $(rel)/pri.1
PRI_BIN := $(rel)/pri$(EXEEXT)

PRI_OBJ_EXT := \
	src/lib/getopt.o \
	src/lib/sysdep.o \
	$(DRV_PSI_OBJ) \
	$(DRV_PRI_OBJ)

BIN  += $(PRI_BIN)
MAN1 += $(PRI_MAN1)
CLN  += $(PRI_BIN) $(PRI_OBJ)
DIST += $(PRI_SRC) $(PRI_HDR) $(PRI_MAN1)

$(rel)/comment.o:  $(rel)/comment.c
$(rel)/decode.o:   $(rel)/decode.c
$(rel)/delete.o:   $(rel)/delete.c
$(rel)/edit.o:     $(rel)/edit.c
$(rel)/encode.o:   $(rel)/encode.c
$(rel)/event.o:    $(rel)/event.c
$(rel)/info.o:     $(rel)/info.c
$(rel)/list.o:     $(rel)/list.c
$(rel)/merge.o:    $(rel)/merge.c
$(rel)/new.o:      $(rel)/new.c
$(rel)/pri-mac-gcr.o: $(rel)/pri-mac-gcr.c
$(rel)/rotate.o:   $(rel)/rotate.c
$(rel)/text-ibm-fm.o:  $(rel)/text-ibm-fm.c
$(rel)/text-ibm-mfm.o: $(rel)/text-ibm-mfm.c
$(rel)/text-mac-gcr.o: $(rel)/text-mac-gcr.c
$(rel)/text-raw.o:     $(rel)/text-raw.c
$(rel)/text.o:     $(rel)/text.c
$(rel)/weak.o:     $(rel)/weak.c
$(rel)/main.o:     $(rel)/main.c

$(rel)/pri$(EXEEXT): $(PRI_OBJ_EXT) $(PRI_OBJ)
	$(QP)echo "  LD     $@"
	$(QR)$(LD) $(LDFLAGS_DEFAULT) -o $@ $(PRI_OBJ) $(PRI_OBJ_EXT)
