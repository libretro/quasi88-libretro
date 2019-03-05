# QUASI88-libretro
A port of QUASI88 to the libretro specification. This is a WIP port with some currently unsupported features:

* Support for games that load more than 2 disks, or swapping disks at runtime
* Tape support
* Loading BIOS files from multiple possible filenames
* Some keys are not mapped to the libretro keyboard yet

# BIOS
BIOS files should be placed in `/system/quasi88`. The following are supported but not all are required for all software:

* n88.rom
* n88_0.rom
* n88_1.rom
* n88_2.rom
* n88_3.rom
* n88n.rom
* disk.rom
* n88knj1.rom
* n88knj2.rom
* n88jisho.rom

# Copyright
QUASI88 is an emulator by Showzoh Fukunaga licensed under the BSD 3-Clause license. This libretro port is distributed in the same way.

The sound processing portion of QUASI88 uses source code from MAME and XMAME. The copyright to this source code belongs to its corresponding authors. Please refer to license/MAME.TXT for licensing information.

The sound processing portion of QUASI88 also uses source code from the FM audio generator "fmgen". The copyright to this source code belongs to cisc. Please refer to license/FMGEN.TXT (in Japanese) for licensing information.