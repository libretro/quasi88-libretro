# Frame contract, savestate determinism, input-across-load and disk
# insertion test, run by hand:
#   make check
# Builds the core, then links the test against the core's own objects.
# Works on Linux and MSYS2 MINGW64.

CORE_DIR  := ../..
CC        ?= cc
CXX       ?= c++
CFLAGS    ?= -O2
CFLAGS    += -std=c89 -Wall -I$(CORE_DIR)/src/LIBRETRO/libretro-common/include
CORE_OBJS  = $(addprefix $(CORE_DIR)/,$(shell $(MAKE) -s --no-print-directory -C $(CORE_DIR) print-objects))

ifeq ($(OS),Windows_NT)
EXE := .exe
endif

TEST := frame_contract$(EXE)

all: $(TEST)

core: FORCE
	$(MAKE) -C $(CORE_DIR)

frame_contract.o: frame_contract.c
	$(CC) $(CFLAGS) -c -o $@ $<

$(TEST): frame_contract.o core
	$(CXX) -o $@ frame_contract.o $(CORE_OBJS) -Wl,--wrap=sound_frame_update -Wl,--wrap=retro_disks_start -Wl,--wrap=retro_disks_cycle -Wl,--wrap=retro_disks_set $(LDFLAGS) -lm

check: $(TEST)
	./$(TEST) boot
	./$(TEST) main
	./$(TEST) dual
	./$(TEST) input
	head -c 348848 /dev/zero > frame_contract_disk.d88
	./$(TEST) disk frame_contract_disk.d88
	cp frame_contract_disk.d88 frame_contract_disk
	./$(TEST) disk frame_contract_disk
	rm -f frame_contract_disk.d88 frame_contract_disk

clean:
	rm -f frame_contract.o $(TEST)

FORCE:

.PHONY: all core check clean FORCE
