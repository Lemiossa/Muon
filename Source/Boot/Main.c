/**
 * Main.c
 * Created by Matheus Leme Da Silva
 */
#include "Types.h"
#include "Util.h"
#include "Vga.h"

extern U8 BootDrive;

void DiskReset(U8 drive);
U8 ExtendedDiskRead(U8 drive, U32 lba, void *buffer);

// Prints error message and halt system
void Panic(void) {
  Puts("Bootloader panic!\r\n");
  Puts("System halted!\r\n");
  for (;;)
    ;
}

// Read LBA sector using BIOS and copy to BUFFER
// Useful for if you want to charge things above 1MiB
void DiskRead(U8 drive, U32 lba, void *buffer) {
  void *lbuf = (void *)0x5000;
  Memset(lbuf, 0, 512);
  Memset(buffer, 0, 512);

  U8 ret;
  for (int i = 0; i < 3; i++) {
    ret = ExtendedDiskRead(drive, lba, lbuf);
    if (ret == 0) {
      Memcpy(buffer, lbuf, 512);
      break;
    } else if (i <= 2) {
      DiskReset(drive);
    }
  }

  if (ret != 0) {
    Puts("Failed tu read sector: 0x");
    PutHexU32(lba);
    Puts("\r\nError code: 0x");
    PutHexU8(ret);
    Puts("\r\n");
    Panic();
  }
}

struct Bpb {
  U8 Jump[3];
  U8 OemName[8];
  U16 BytesPerSct;
  U8 SctsPerClst;
  U16 ResScts;
  U8 FatCount;
  U16 RootDirEnts;
  U16 TotalScts16;
  U8 MediaDesc;
  U16 SctsPerFat;
  U16 SctsPerTrack;
  U16 Heads;
  U32 HiddenScts;
  U32 TotalScts32;
} __attribute__((packed));

struct Ebpb {
  U8 DriveNum;
  U8 Res;
  U8 Sig;
  U32 VolId;
  U8 VolLabel[11];
  U8 SysId[8];
} __attribute__((packed));

#define READ_ONLY 0x01
#define HIDDEN 0x02
#define SYSTEM 0x04
#define VOLUME_ID 0x08
#define DIRECTORY 0x10
#define ARCHIVE 0x20

struct FatDirEntry {
  U8 Name[11];
  U8 Attr;
  U8 Res;
  U8 Res1;
  U16 CtdTime;
  U16 CtdDate;
  U16 AcsDate;
  U16 ClstHi;
  U16 ModTime;
  U16 ModDate;
  U16 ClstLo;
  U32 FileSz;
} __attribute__((packed));

struct MbrPart {
  U8 BootSig;
  U8 StartHead, StartSct, StartCyl;
  U8 Type;
  U8 EndHead, EndSct, EndCyl;
  U32 StartLBA;
  U32 TotalScts;
} __attribute__((packed));

U8 Mbr[512];
struct MbrPart *PartTable = (struct MbrPart *)&Mbr[446];
int part = 0;

U32 GTotalScts = 0;
U32 GFatSz = 0;
U32 GRootDirScts = 0;
U32 GDataScts = 0;

U32 GDataLba = 0;
U32 GFatLba = 0;
U32 GRootLba = 0;

// The Main function don't return
void Main(void) {
  Clear();
  Puts("Loading...");

  // Read the MBR
  DiskRead(BootDrive, 0, Mbr);
  if (Mbr[510] != 0x55 && Mbr[511] != 0xAA) {
    Puts("Invalid MBR!\r\n");
    Panic();
  }

  for (int i = 0; i < 4; i++) {
    if (PartTable[i].BootSig)
      part = i;
  }

  U8 buf[512];
  DiskRead(BootDrive, PartTable[part].StartLBA, buf);

  struct Bpb *bpb = (struct Bpb *)buf;
  if (bpb->BytesPerSct == 0) {
    Puts("Invalid BPB\r\n");
    Panic();
  }

  // https://wiki.osdev.org/FAT
  GTotalScts = bpb->TotalScts16 == 0 ? bpb->TotalScts32 : bpb->TotalScts16;
  GFatSz = bpb->SctsPerFat;
  GRootDirScts =
      ((bpb->RootDirEnts * 32) + (bpb->BytesPerSct - 1)) / bpb->BytesPerSct;
  GFatLba = PartTable[part].StartLBA + bpb->ResScts;
  GDataLba = GFatLba + (bpb->FatCount * GFatSz) + GRootDirScts;
  GDataScts =
      GTotalScts - (bpb->ResScts + (bpb->FatCount * GFatSz) + GRootDirScts);
  GRootLba = GDataLba - GRootDirScts;

  U32 TotalClsts = GDataScts / bpb->SctsPerClst;

  if (TotalClsts < 4085) {
    Puts("Is FAT12");
  } else if (TotalClsts < 65525) {
    Puts("Is FAT16");
  }

  for (;;)
    ;
}
