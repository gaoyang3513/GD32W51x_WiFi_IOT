TARGET ?= haltest

###############################################################################
# Compiler
CC := arm-buildroot-linux-uclibcgnueabihf-gcc

###############################################################################
# Version
MAJOR_VERSION ?= 1
MINOR_VERSION ?= 0

###############################################################################
# Path definitions

# Use if application directory contains multiple targets
TOPDIR         = .
BLDDIR         = $(TOPDIR)/build
SRCDIR         = $(TOPDIR)/src
HEADERDIR      = $(TOPDIR)/include 

###############################################################################
# Application Source files

# Note: Path to source file is found using vpath below, so only .c filename is required
SOURCE_FILES_C := $(wildcard $(SRCDIR)/*.c)

###############################################################################

# Standard Application header search paths

CFLAGS += -I$(HEADERDIR)
LDFLAGS += -lpthread

###############################################################################

APPOBJS_TMP = $(SOURCE_FILES_C:.c=.o)
APPOBJS = $(subst src,build,$(APPOBJS_TMP))

###############################################################################
# Application dynamic dependencies

APPDEPS := $(APPOBJS:.o=.d)

###############################################################################
# Linker

# Add application libraries before chip specific libraries to linker so
# symbols are resolved correctly (i.e. ordering is significant for GCC)

###############################################################################
# Dependency rules
.PHONY: prepare all clean

all: | prepare $(BLDDIR)/$(TARGET)

prepare:
	-@mkdir -p $(BLDDIR)

$(BLDDIR)/%.o: $(SRCDIR)/%.c
	$(info Compiling $< ...)
	$(CC) -o $@ -c $< $(CFLAGS) -MD -MF $(BLDDIR)/$*.d -MP

$(BLDDIR)/$(TARGET): $(APPOBJS)
	$(info Linking $@ ...)
	$(CC) $(LDFLAGS) -o $@ $(APPOBJS) $(LDFLAGS)
###############################################################################

clean:
	rm -rf $(BLDDIR)

###############################################################################
