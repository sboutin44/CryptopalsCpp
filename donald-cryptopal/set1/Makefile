
BASE=$(CURDIR)
SRCDIR=$(BASE)/src
HEADDIR=$(BASE)/include
BUILD=$(BASE)/build
LIBDIR=$(BUILD)/obj

CC=gcc
CXX=g++
CXXFLAGS= -Wall -O3 -I$(HEADDIR)
LDFLAGS=

BIN=$(BUILD)/cryptopal

SRCXX=$(wildcard $(SRCDIR)/*.cxx)
OBJXX=$(SRCXX:$(SRCDIR)/%.cxx=$(LIBDIR)/%.o)

all: $(BIN)

$(BIN): $(OBJXX)
	@$(CXX) -o $@ $^ $(LDFLAGS)

$(LIBDIR)/%.o: $(SRCDIR)/%.cxx $(wildcard $(HEADDIR)/*.hxx)
	@mkdir -p $(@D)
	@$(CXX) -o $@ -c $<  $(CXXFLAGS)

.PHONY: clean mrpropre

clean:
	rm -rf $(LIBDIR)

mrpropre: clean
	rm -fr $(BUILD)
