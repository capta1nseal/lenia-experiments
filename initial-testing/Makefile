SRCDIR  = src
BINDIR  = bin
OBJDIR := $(BINDIR)/obj
DEPDIR := $(BINDIR)/dep
TARGET  = lenia-testing

SRCS := $(shell find $(SRCDIR) -name "*.cpp")
OBJS := $(SRCS:$(SRCDIR)/%.cpp=$(OBJDIR)/%.o)
DEPS := $(SRCS:$(SRCDIR)/%.cpp=¤(DEPDIR)/%.d)
TREE := $(sort $(patsubst %/,%,$(dir $(OBJS))))

CPPFLAGS     = -MMD -MP -MF $(@:$(OBJDIR)/%.o=$(DEPDIR)/%.d)
CXXWARNFLAGS = -Wall -Wextra -Wpedantic -Wshadow -Wnon-virtual-dtor -Wold-style-cast -Wcast-align -Wzero-as-null-pointer-constant -Wunused -Woverloaded-virtual -Wformat=2 -Werror=vla -Wmisleading-indentation -Wduplicated-cond -Wduplicated-branches -Wlogical-op -Wnull-dereference
CXXFLAGS    := -std=c++20 -O3 $(CXXWARNFLAGS)
LINKFLAGS    = -lSDL2 -lSDL2main# -lfftw3 -lm

.PHONY: build test clean

$(TARGET): $(OBJS)
	g++ -o $(BINDIR)/$@ $^ $(CXXFLAGS) $(LINKFLAGS)

build: $(TARGET)

test: $(TARGET)
	cd  $(BINDIR); ./$(TARGET); cd ..

.SECONDEXPANSION:
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp | $$(@D)
	g++ $(CPPFLAGS) $(CXXFLAGS) -o $@ -c $<

$(TREE): %:
	mkdir -p $@
	mkdir -p $(@:$(OBJDIR)%=$(DEPDIR)%)

clean:
	rm -r $(BINDIR)

ifeq "$(MAKECMDGOALS)" ""
-INCLUDE $(DEPS)
endif
