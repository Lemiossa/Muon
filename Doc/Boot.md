# Boot

MuonOS uses its own Bootloader.

## Stage 1
MuonBootloader stage 1 is basically the MBR, it loads the second stage in sectors 1-62 in 0x8000;
It uses the 0x42 function of the in 0x13 to load sectors.

Access: [Bootsect.asm](https://github.com/Lemiossa/Muon/blob/main/Source/Boot/Bootsect.asm)

## Stage 2
Stage 2 of MuonBootloader starts at sector 1 can have up to 62 sectors.
It reads the MBR(sector 0) of the disk and looks for the first bootable partition, otherwise it will use partition 0.
It reads the VBR of that partition and considers FAT(Doesn't support another file system yet).
It supports FAT12, 16 and 32, however, it only supports 512 bytes per sector, otherwise it will panic.
Before loading the file, it takes the map from the E820 memory using the BIOS.
Creates a boot structure for the kernel, for example, where the memory map is located.
Loads the file defined by the FILEPATH macro at 0x100000(1MiB). Displays the number of bytes read and reads in chunks of 65536 bytes.
Before jumping to the kernel, passes the address of the boot structure to EAX.

The main file: [Main.c](https://github.com/Lemiossa/Muon/blob/main/Source/Boot/Main.c)

***The Bootloader jump to the kernel in protected mode***
