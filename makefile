# MOA Makefile
# Southeastern Policy Institute, 2020

# Project Name and Version
PROJECT_NAME:= LIBSMALLESTNUMBERFROMLIST
PROJECT_VER := 0x0001

#   Alter $TARGET environment variable according to desired target
DEBUG     := DEBUG
ifeq ($(TARGET),WIN32)
  DEFS    := WINVER=0x0501 UNICODE $(TARGET) $(DEBUG)
  UNDEFS  :=
  PREFIX  := i686-w64-mingw32-
  REQDIR  += /usr/i686-w64-mingw32/lib
  REQS    +=
#   Otherwise, no unicode.  Use defaults.
else
  DEFS    := $(DEBUG)
  UNDEFS  := UNICODE
  PREFIX  :=
  REQS    +=
endif

# Commands
AR        := $(PREFIX)ar
AS        := nasm
CC        := $(PREFIX)gcc
CPP       := $(PREFIX)g++
LD        := $(PREFIX)g++
RES       := $(PREFIX)windres
STRIP     := $(PREFIX)strip

# Directories
MAINDIR   := $(CURDIR)
SRCDIR    := $(MAINDIR)/src
INCDIR    := $(MAINDIR)/inc
BINDIR    := $(MAINDIR)/bin
OBJDIR    := $(MAINDIR)/obj
RESDIR    := $(MAINDIR)/res
LIBDIR    := $(MAINDIR)/lib


# Project Names
LIB_PROJ  := $(patsubst $(SRCDIR)/lib%,%,\
             $(filter $(SRCDIR)/lib%,$(wildcard $(SRCDIR)/*)))
BIN_PROJ  := $(patsubst $(SRCDIR)/%,%,\
             $(filter-out $(SRCDIR)/lib%,$(wildcard $(SRCDIR)/*)))

# Output Files
ifeq ($(TARGET),WIN32)
  LIB_OUT := $(LIB_PROJ:%=$(LIBDIR)/%.dll)
  BIN_OUT := $(BIN_PROJ:%=$(BINDIR)/%.exe)
else
  LIB_OUT := $(LIB_PROJ:%=$(LIBDIR)/lib%.a)
  BIN_OUT := $(BIN_PROJ:%=$(BINDIR)/%)
endif

# Source Files
SRC := $(wildcard $(SRCDIR)/*/*.*)

# Intermediate Files
OBJ       := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRC:.cpp=.o))
OBJ       := $(OBJ:.c=.o)
OBJ       := $(OBJ:.asm=.o)
OBJ       := $(OBJ:.rc=.o)

# Flags
ifeq ($(TARGET),WIN32)
  ASFLAGS := -f win32
  LDFLAGS += -mwindows
else
  ASFLAGS := -f elf
endif
CPPFLAGS  := -c -Wall -fPIC -ffreestanding -fno-builtin -nostdinc++ \
             -fno-exceptions -fno-ident \
             $(INCDIR:%=-I%) $(DEFS:%=-D%) $(UNDEFS:%=-U%)
CFLAGS    := -c -Wall -fPIC -ffreestanding -fno-builtin \
             -fno-exceptions -fno-ident \
             $(INCDIR:%=-I%) $(DEFS:%=-D%) $(UNDEFS:%=-U%)
LDFLAGS   += -fno-ident -ffreestanding -fno-builtin -fno-exceptions \
             $(LIBDIR:%=-L%) $(REQS:%=-l%)

# Rules
$(OBJDIR)/%.o : $(SRCDIR)/%.cpp
	@echo ===== BUILDING $@ =====
	@$(CPP) $(CPPFLAGS) -o $@ $<

$(OBJDIR)/%.o : $(SRCDIR)/%.c
	@echo ===== BUILDING $@ =====
	@$(CC) $(CFLAGS) -o $@ $<

$(OBJDIR)/%.o : $(SRCDIR)/%.asm
	@echo ===== BUILDING $@ =====
	@$(AS) $(ASFLAGS) -o $@ $<

# Windows Rules
ifeq ($(TARGET),WIN32)
$(LIBDIR)/%.dll : LDFLAGS += -shared -Wl,--out-implib,$(LIBDIR)/lib$(lastword\
 $(subst /, ,$(patsubst %.dll,%.a,$*))).a $(REQDIR:%=-L%)
$(LIBDIR)/%.dll : $(OBJ)
	@echo ===== BUILDING $@ =====
	@$(LD) $(filter \
  $(OBJDIR)/$(lastword $(subst /, ,$(patsubst %.dll,%,$*)))/%.o,$^) \
  $(LDFLAGS) -o $@

$(BINDIR)/%.exe : $(OBJ)
	@echo ===== BUILDING $@ =====
	@$(LD) $(filter \
  $(OBJDIR)/$(lastword $(subst /, ,$(patsubst %.exe,%,$*)))/%.o,$^) \
  $(LDFLAGS) $(LIB_PROJ:%=-l%) -o $@

# *NIX Rules
else
$(LIBDIR)/%.a : $(OBJ)
	@echo ===== BUILDING $@ =====
	@$(AR) rcs $@ $(filter \
  $(OBJDIR)/$(lastword $(subst /, ,$(patsubst %.a,%,$*)))/%.o,$^)

$(BINDIR)/% : $(OBJ)
	@echo ===== BUILDING $@ =====
	@$(LD) $(filter \
    $(OBJDIR)/$(lastword $(subst /, ,$(patsubst %.a,%,$*)))/%.o,$^) \
    $(LDFLAGS) $(LIB_PROJ:%=-l%) -o $@
endif

.PHONY : all clean

all : $(LIB_OUT) $(BIN_OUT)
	@$(STRIP) -s $^
	@echo Done!

clean :
	@clear
	@$(RM) $(wildcard $(OBJDIR)/*/*.o) $(wildcard $(LIB_PROJ:%=$(LIBDIR)/*%*))\
  $(wildcard $(BIN_PROJ:%=$(BINDIR)/%*))