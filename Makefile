# Central snake game Makefile
# 2023

# Make sure to define rule for each target
SHELL := bash

CXX := g++
CXXFLAGS := -Wall
include txx.mk

# Define targets
TARGETS := target

# Determine the object files
OBJ := main.o model.o view.o controller.o

# Use submodules instead of recursion
MODULES :=
# Include description for each submodule
include $(patsubst %, %/module.mk, $(MODULES))

# Target specific object files
target: $(OBJ)
	echo $(OBJ)
	$(CXX) -o $@ $(OBJ) $(CXXFLAGS) $(LDFLAGS)

clean:
	rm -f $(TARGETS)
	rm -rf *.o *.d
	rm -rf $(addsuffix /*.o, $(MODULES))
	rm -rf $(addsuffix /*.d, $(MODULES))

.PHONY: clean

# Dependencies
include $(OBJ:.o=.d)

%.d: %.cc
	./depend.sh `dirname $*` $(CXXFLAGS) $< > $@

