
BASE=$(CURDIR)
SRCDIR=$(BASE)/src
SRCDIRTEST=$(BASE)/test
HEADDIR=$(BASE)/inc
BUILD=$(BASE)/build
LIBDIR=$(BUILD)/obj

CC=gcc
CXX=g++
CXXFLAGS= -Wall -O3 -g
LDFLAGS=

BIN=$(BUILD)/cryptopal

SRCXX=$(wildcard $(SRCDIR)/*.cxx)
SRCXXTEST=$(wildcard $(SRCDIRTEST)/*.cxx)
OBJXX=$(SRCXX:$(SRCDIR)/%.cxx=$(LIBDIR)/%.o) $(SRCXXTEST:$(SRCDIRTEST)/%.cxx=$(LIBDIR)/%.o)


all: $(BIN)

$(BIN): $(OBJXX)
	@$(CXX) -o $@ $^ $(LDFLAGS)

$(LIBDIR)/%.o: $(SRCDIR)/%.cxx 
	@mkdir -p $(@D)
	@$(CXX) -o $@ -c $<  $(CXXFLAGS) -I$(HEADDIR)

$(LIBDIR)/%.o: $(SRCDIRTEST)/%.cxx 
	@mkdir -p $(@D)
	@$(CXX) -o $@ -c $<  $(CXXFLAGS) -I$(HEADDIR)

.PHONY: clean mrpropre

clean:
	rm -rf $(LIBDIR)

mrpropre: clean
	rm -fr $(BUILD)
