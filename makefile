# Copyright © 2020 Sebastien BOUTIN
#
# Permission is hereby granted, free of charge, to any person obtaining a copy of
# this software and associated documentation files (the "Software"), to deal in
# the Software without restriction, including without limitation the rights to
# use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
# of the Software, and to permit persons to whom the Software is furnished to do
# so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
#
# Except as contained in this notice, the name(s) of the above copyright holders
# shall not be used in advertising or otherwise to promote the sale, use or other
# dealings in this Software without prior written authorization.

BUILD_DIR   = build
INC         = inc
CXX         = clang++ 
CXXFLAGS    = -Wall -g -I$(INC)

#VPATH = src inc # VPATH: Search Path for All Dependencies

# We create a list of all object files to make from the source files
# found in src/.
SRC_LIST    		= $(wildcard src/*.cc)
TST_SRC_LIST    = $(wildcard test/*.cc)
OBJS            = $(subst src/,$(BUILD_DIR)/, $(subst .cc,.o, $(SRC_LIST)) )
TST_OBJS        = $(subst test/,$(BUILD_DIR)/, $(subst .cc,.o, $(TST_SRC_LIST)) )

# List of headers
HEADERS_LIST    := $(wildcard inc/*.h)
HEADERS         := $(HEADERS_LIST)

# Creates object files from sources in $(BUILD_DIR)
$(BUILD_DIR)/%.o : src/%.cc $(HEADERS_LIST)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Creates object files for tests in $(BUILD_DIR).
$(BUILD_DIR)/%.o : test/%.cc $(HEADERS_LIST)
	mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c -o $@ $<

# Creates the executable
$(BUILD_DIR)/cryptopals : $(OBJS) $(TST_OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

.PHONY : clean
clean:
	-rm -r ${BUILD_DIR}
