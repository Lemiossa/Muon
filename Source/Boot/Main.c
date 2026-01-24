/**
 * Main.c
 * Created by Matheus Leme Da Silva
 */
#include "Fat.h"
#include "Types.h"
#include "Util.h"
#include "Vga.h"

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
void FilenameToFatname(char *filename, char *out);

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

  struct FatPart p;
  if (FatInit(BootDrive, PartTable[part].StartLBA, &p) != 0) {
    Puts("Failed to initialize partition\r\n");
    Panic();
  }

#define FILEPATH "/kernel.txt"

  struct FatDirEntry e;
  if (FatFind(p, FILEPATH, &e) != 0)
    Puts("File" FILEPATH " not found!\r\n");
  else
    Puts("File " FILEPATH " found!\r\n");

  Puts("Cluster : 0x");
  PutHexU16(e.ClstLo);
  Puts("\r\n");

  for (;;)
    ;
}
