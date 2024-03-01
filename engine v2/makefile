.PHONY: clean

TARGET_EXEC ?= Game.exe

SOURCE_DIR = engine
OUTPUT_DIR = output

SRCS := $(shell find $(SOURCE_DIR) -name "*.cxx")
OBJS := $(SRCS:%=$(OUTPUT_DIR)/%.o)
DEPS := $(OBJS:.o=.d)

INCLUDE_DIRS := $(shell find $(SOURCE_DIR) -type d)
INCLUDE_FLAG := $(addprefix -I,$(INCLUDE_DIRS))

C++ ?= g++

COMPILER_VERS ?= -std=c++20
COMPILER_FLAG ?= $(COMPILER_VERS) $(INCLUDE_FLAG) -MMD -MP

MKDIR ?= mkdir -p

$(OUTPUT_DIR)/$(TARGET_EXEC): $(OBJS)
	@echo $(OBJS)
	$(C++) $(COMPILER_FLAG) -o $@ $(OBJS)

$(OUTPUT_DIR)/%.cxx.o: %.cxx
	$(MKDIR) $(dir $@)
	$(C++) $(COMPILER_FLAG) -o $@ -c $<

clean:
	$(RM) -r $(OUTPUT_DIR)

-include $(DEPS)