BUILD_DIR   = build
INC         = inc
CXX         = g++-9
CXXFLAGS    = -I$(INC)

#VPATH = src inc # VPATH: Search Path for All Dependencies

# We create a list of all object files to make from the source files
# found in src/.
SOURCES_LIST    = $(wildcard src/*.cc)
OBJS            = $(subst src/,$(BUILD_DIR)/, $(subst .cc,.o, $(SOURCES_LIST)) )

# List of headers
HEADERS_LIST    := $(wildcard inc/*.h)
HEADERS         := $(HEADERS_LIST)

# Creates object files in $(BUILD_DIR)
$(BUILD_DIR)/%.o : src/%.cc $(HEADERS_LIST)
    mkdir -p $(@D)
    $(CXX) -c -o $@ $<  $(CXXFLAGS)

# Creates the executable
$(BUILD_DIR)/cryptopals : $(OBJS)
    $(CXX) -o $@ $^ $(CXXFLAGS)

.PHONY : clean
clean:
    -rm -r ${BUILD_DIR}
