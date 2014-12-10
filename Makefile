#(C)2004-2005 AMX Mod X Development Team
# Makefile written by David "BAILOPAN" Anderson

HLSDK = ../../../hlsdk
MM_ROOT = ../../metamod/metamod

### EDIT BELOW FOR OTHER PROJECTS ###

OPT_FLAGS = -O2 -funroll-loops -s -pipe -fomit-frame-pointer -fno-strict-aliasing
DEBUG_FLAGS = -g -ggdb3
CPP = gcc
NAME = rage

BIN_SUFFIX_32 = amxx_i386.so
BIN_SUFFIX_64 = amxx_amd64.so

OBJECTS = \
./command/implementations/command_errors.cpp \
./command/implementations/command_functions.cpp \
./command/implementations/command_handler.cpp \
./command/implementations/command_modules.cpp \
./command/implementations/command_rage.cpp \
./commands_manager/commands_manager.cpp \
./config_parser/config_parser.cpp \
./error_manager/error_manager.cpp \
./function/function.cpp \
./function/function_safe.cpp \
./function_creator/function_creator.cpp \
./global/global.cpp \
./handlers_manager/handlers_manager.cpp \
./handler_creator_manager/handler_creator_manager.cpp \
./libraries_manager/libraries_manager.cpp \
./library/library.cpp \
./manager/manager.cpp \
./memory/memory.cpp \
./modules_manager/modules_manager.cpp \
./NEW_Util.cpp \
./parser/filehandler.cpp \
./parser/node_types/parser_node_array.cpp \
./parser/node_types/parser_node_labeled.cpp \
./parser/node_types/parser_node_labeled_array.cpp \
./parser/node_types/parser_node_labeled_scalar.cpp \
./parser/node_types/parser_node_num.cpp \
./parser/node_types/parser_node_string.cpp \
./parser/parser.cpp \
./parser/parser_node.cpp \
./parser/worker_types/parser_worker_any_string.cpp \
./parser/worker_types/parser_worker_array.cpp \
./parser/worker_types/parser_worker_array_entry.cpp \
./parser/worker_types/parser_worker_decimal.cpp \
./parser/worker_types/parser_worker_hex.cpp \
./parser/worker_types/parser_worker_labeled_array.cpp \
./parser/worker_types/parser_worker_labeled_scalar.cpp \
./parser/worker_types/parser_worker_multi.cpp \
./parser/worker_types/parser_worker_num.cpp \
./parser/worker_types/parser_worker_quoted_string.cpp \
./parser/worker_types/parser_worker_scalar.cpp \
./parser/worker_types/parser_worker_string.cpp \
./patcher/patcher.cpp \
./rage/rage.cpp \
./sdk/amxxmodule.cpp \
./util/util.cpp \
./virtual_function/virtual_function.cpp

LINK = 

INCLUDE = -I. -I$(HLSDK) -I$(HLSDK)/dlls -I$(HLSDK)/engine -I$(HLSDK)/game_shared -I$(HLSDK)/game_shared \
	-I$(MM_ROOT) -I$(HLSDK)/common -Isdk -I./include

GCC_VERSION := $(shell $(CPP) -dumpversion >&1 | cut -b1)

ifeq "$(GCC_VERSION)" "4"
        OPT_FLAGS += -fvisibility=hidden -fvisibility-inlines-hidden
endif

ifeq "$(DEBUG)" "true"
	BIN_DIR = Debug
	CFLAGS = $(DEBUG_FLAGS)
else
	BIN_DIR = Release
	CFLAGS = $(OPT_FLAGS)
endif

CFLAGS += -DNDEBUG -Wall -Wno-non-virtual-dtor -fno-exceptions -DHAVE_STDINT_H -fno-rtti -static-libgcc -m32
#CFLAGS += -DNDEBUG -Wall -Wno-non-virtual-dtor -Werror -fno-exceptions -DHAVE_STDINT_H -fno-rtti -static-libgcc -m32

ifeq "$(AMD64)" "true"
	BINARY = $(NAME)_$(BIN_SUFFIX_64)
	CFLAGS += -DPAWN_CELL_SIZE=64 -DHAVE_I64 -m64 
else
	BINARY = $(NAME)_$(BIN_SUFFIX_32)
	CFLAGS += -DPAWN_CELL_SIZE=32 -DJIT -DASM32
	OPT_FLAGS += -march=i586
endif

OBJ_LINUX := $(OBJECTS:%.cpp=$(BIN_DIR)/%.o)

$(BIN_DIR)/%.o: %.cpp
	$(CPP) $(INCLUDE) $(CFLAGS) -o $@ -c $<

all:
	mkdir -p $(BIN_DIR)
	mkdir -p $(BIN_DIR)/sdk
	$(MAKE) rage

amd64:
	$(MAKE) all AMD64=true

rage: $(OBJ_LINUX)
	$(CPP) $(INCLUDE) $(CFLAGS) $(OBJ_LINUX) $(LINK) -shared -ldl -lm -o$(BIN_DIR)/$(BINARY)

debug:	
	$(MAKE) all DEBUG=true

default: all

clean:
	rm -rf Release/sdk/*.o
	rm -rf Release/*.o
	rm -rf Release/$(NAME)_$(BIN_SUFFIX_32)
	rm -rf Release/$(NAME)_$(BIN_SUFFIX_64)
	rm -rf Release/parser/*.o
	rm -rf Release/parser/node_types/*.o
	rm -rf Release/parser/worker_types/*.o
	rm -rf Release/memory/*.o
	rm -rf Release/global/*.o
	rm -rf Release/util/*.o
	rm -rf Release/handlers_manager/*.o
	rm -rf Release/handler/*.o
	rm -rf Release/library/*.o
	rm -rf Release/command/*.o
	rm -rf Release/command/implementations/*.o
	rm -rf Release/commands_manager/*.o
	rm -rf Release/function/*.o
	rm -rf Release/libraries_manager/*.o
	rm -rf Release/patcher/*.o
	rm -rf Release/config_parser/*.o
	rm -rf Release/error_manager/*.o
	rm -rf Release/function_creator/*.o
	rm -rf Release/modules_manager/*.o
	rm -rf Release/rage/*.o
	rm -rf Release/virtual_function/*.o
	rm -rf Release/manager/*.o
	rm -rf Release/handler_creator_manager/*.o
	rm -rf Debug/sdk/*.o
	rm -rf Debug/*.o
	rm -rf Debug/$(NAME)_$(BIN_SUFFIX_32)
	rm -rf Debug/$(NAME)_$(BIN_SUFFIX_64)
