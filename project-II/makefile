############# CC FLAGS ###############################
NAME = solution
CC = g++
CPPFLAGS = -Wall -Wextra -g -std=c++17

########### PROJECT DIRS #########################
SRCDIR := src
INCLUDEDIR := ./include
BUILDDIR := build
BINDIR := bin

########### OBJECTS ##################################
TARGET := $(BINDIR)/$(NAME)
SRCS := $(shell find $(SRCDIR) -name *.cpp)
HDRS := $(shell find $(INCLUDEDIR) -name *.h)
OBJS := $(patsubst $(SRCDIR)/%.cpp,$(BUILDDIR)/%.o,$(SRCS))

########### AUX TARGETS ##############################
$(BUILDDIR)/%.o: $(SRCDIR)/%.cpp $(HDRS) | $(BUILDDIR)
	@echo Compiling $<
	$(CC) $(CPPFLAGS) $(DEFS) $(DEPS_INCLUDES) -I$(INCLUDEDIR) -O0 -Wall -c -o "$(BUILDDIR)/$(notdir $@)" "$<"

$(TARGET): $(OBJS) | $(BINDIR)
	@echo Linking $@
	$(CC) $(CPPFLAGS) $(DEFS) -o $(TARGET) $(addprefix $(BUILDDIR)/,$(notdir $(OBJS))) $(LIBS)
	@echo 'Build complete!'

$(BUILDDIR):
	@mkdir -p $(BUILDDIR)

$(BINDIR):
	@mkdir -p $(BINDIR)

########### TARGETS ##################################
all: $(TARGET)

clean:
	rm -rf $(BUILDDIR)/* $(BINDIR)/*

.PHONY: all clean
