/*
    SIMP MIPS Pipelined Architecture Simulation Package

    Memory class implementation

    Copyright (C) 2016  Jay B. Brockman

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "Memory.h"
#include "elf.h"

Memory::Memory(unsigned tSize, unsigned dSize, unsigned hSize, unsigned sSize)
: textSize    (tSize),
  textBase    (0x400000),
  textBound   (textBase + tSize - 1),
  dataSize    (dSize),
  dataBase    (0x10000000),
  dataBound   (dataBase + dSize - 1),
  heapSize    (hSize),
  heapBase    (0x10040000),
  heapBound   (heapBase),
  stackSize   (sSize),
  stackBound  (0x7fffffff),
  stackBase   (stackBound - sSize + 1),
  textMemory  (new uint8_t [tSize]),
  dataMemory  (new uint8_t [dSize]),
  heapMemory  (new uint8_t [hSize]),
  stackMemory (new uint8_t [sSize]),
  mainAddr    (0),
  initPc      (0),
  initSp      (0x7ffff240),
  initGp      (0x10008000)
{
//    printf("created memory\n");
//    printf("dataBase = %x  dataBound = %x\n", dataBase, dataBound);
//    printf("heapBase = %x  heapBound = %x\n", heapBase, heapBound);
//    printf("stackBase = %x  stackBound = %x\n", stackBase, stackBound);
//    printf("textBase = %x  textBound = %x\n", textBase, textBound);
}

Memory::~Memory() {
  // TODO Auto-generated destructor stub
}

void Memory::loadText(void *source, unsigned numBytes) {
  assert(numBytes <= textSize && "text to load exceeds memory size");
  memcpy(textMemory, source, numBytes);
}

void Memory::loadData(void *source, unsigned numBytes) {
  assert(numBytes <= dataSize && "data to load exceeds memory size");
  memcpy(dataMemory, source, numBytes);
}

void Memory::readSpimLogFile(char *filename) {
  ifstream logfile;
  logfile.open(filename);
  assert(logfile && "unable to open logfile");
  string line;
  size_t found;
  unsigned a, d0, d1, d2, d3;

  while (!getline(logfile, line).eof()) {
    found = line.find("User Text Segment");
    if (found != string::npos)
      break;
  }
  assert(!logfile.eof() && "couldn't find User Text Segment");
  do {
    getline(logfile, line);
    sscanf(line.c_str(), "[%x] %x", &a, &d0);
    write(32, a, d0);
  } while(line[0] == '[');

  while (!getline(logfile, line).eof()) {
    found = line.find("User data segment");
    if (found != string::npos)
      break;
  }
  assert(!logfile.eof() && "couldn't find User data segment");
  do {
    getline(logfile, line);
    if (line[10] != '.') {
      sscanf(line.c_str(), "[%x] %x %x %x %x", &a, &d0, &d1, &d2, &d3);
      write(32, a, d0);
      write(32, a+4, d1);
      write(32, a+8, d2);
      write(32, a+12, d3);
    }
  } while(line[0] == '[');
  initPc  = 0x00400000;
}

uint32_t Memory::read(unsigned size, uint32_t addr) {
    uint8_t *dataPtr = getMemoryPtr(addr);
    uint32_t returnData;
    switch (size) {
    case 8:
        returnData = *dataPtr;
        break;
    case 16:
        returnData = *((uint16_t *) dataPtr);
        break;
    case 32:
        returnData = *((uint32_t *) dataPtr);
        break;
    default:
        assert(false && "unknown size");
    }
    return returnData;
}

void Memory::write(unsigned size, uint32_t addr, uint32_t data) {
    uint8_t *memPtr = getMemoryPtr(addr);
     switch (size) {
     case 8:
         *memPtr = data;
         break;
     case 16:
         *((uint16_t *) memPtr) = data;
         break;
     case 32:
         *((uint32_t *) memPtr) = data;
         break;
     default:
         assert(false && "unknown size");
     }
}

uint8_t* Memory::getMemoryPtr(unsigned addr) {
  if (addr >= dataBase && addr <= dataBound) {
    return dataMemory + (addr - dataBase);
  }
  if (addr >= heapBase && addr <= heapBound) {
    return heapMemory + (addr - heapBase);
  }
  if (addr >= stackBase && addr <= stackBound) {
    return stackMemory + (addr - stackBase);
  }
  if (addr >= textBase && addr <= textBound) {
    return textMemory + (addr - textBase);
  }
  printf("Memory access error:  %08x\n", addr);
  printf("text=[%08x, %08x]  data=[%08x, %08x]  stack=[%08x, %08x]\n",
      textBase, textBound, dataBase, dataBound, stackBase, stackBound);
  assert(false && "memory access out of range");
  return 0;  // shouldn't get here
}

unsigned Memory::alloc(unsigned n) {
  // word align address of allocated memory
  unsigned allocAddr = (heapBound + 0x3) & ~0x3;
  heapBound = allocAddr + n;
  assert((heapBound - heapBase) < heapSize && "alloc exceeds heapSize");
  return allocAddr;
}

void Memory::readElfFile(char *filename) {
  FILE *fp = fopen(filename, "r");
  assert(fp != 0 && "unable to open input file");

  // Read ELF header
  Elf32_Ehdr *ehdr = (Elf32_Ehdr *) malloc(sizeof(Elf32_Ehdr));
  fread(ehdr, sizeof(Elf32_Ehdr), 1, fp);

  // Read section headers
  int sh_table_size = ehdr->e_shentsize * ehdr->e_shnum;
  Elf32_Shdr *sh_table = (Elf32_Shdr *) malloc(sh_table_size);
  fseek(fp, ehdr->e_shoff, SEEK_SET);
  fread(sh_table, sh_table_size, 1, fp);

  // Read section header string table
  int shstrtab_size = sh_table[ehdr->e_shstrndx].sh_size;
  int shstrtab_offset = sh_table[ehdr->e_shstrndx].sh_offset;
  int text_sh_idx,
  data_sh_idx,
  sdata_sh_idx,
  sbss_sh_idx,
  bss_sh_idx,
  symtab_sh_idx,
  strtab_sh_idx;
  unsigned char *shstrtab = (unsigned char *) malloc(shstrtab_size);
  fseek(fp, shstrtab_offset, SEEK_SET);
  fread(shstrtab, shstrtab_size, 1, fp);

  // Determine which entries in the section header table correspond
  // to the following sections:
  // .text, .data, .sdata, .sbss, .bss, .symtab, .strtab
  for (int i = 0;  i < ehdr->e_shnum;  i++) {
    char *sh_name = (char *) (shstrtab + sh_table[i].sh_name);
    int sh_size = sh_table[i].sh_size;
    if (strcmp(sh_name, ".text") == 0)
      text_sh_idx = i;
    else if (strcmp(sh_name, ".data") == 0)
      data_sh_idx = i;
    else if (strcmp(sh_name, ".sdata") == 0)
      sdata_sh_idx = i;
    else if (strcmp(sh_name, ".sbss") == 0)
      sbss_sh_idx = i;
    else if (strcmp(sh_name, ".bss") == 0)
      bss_sh_idx = i;
    else if (strcmp(sh_name, ".symtab") == 0)
      symtab_sh_idx = i;
    else if (strcmp(sh_name, ".strtab") == 0)
      strtab_sh_idx = i;
  }

  // Read the text section
  int text_size = sh_table[text_sh_idx].sh_size;
  int text_offset = sh_table[text_sh_idx].sh_offset;
  int text_entsize = sh_table[text_sh_idx].sh_entsize;
  Elf32_Word *text_section = (Elf32_Word *) malloc(text_size);
  fseek(fp, text_offset, SEEK_SET);
  fread(text_section, text_size, 1, fp);

  // read the string table section
  int strtab_size = sh_table[strtab_sh_idx].sh_size;
  int strtab_offset = sh_table[strtab_sh_idx].sh_offset;
  int strtab_entsize = sh_table[strtab_sh_idx].sh_entsize;
  unsigned char *strtab_section = (unsigned char *) malloc(strtab_size);
  fseek(fp, strtab_offset, SEEK_SET);
  fread(strtab_section, strtab_size, 1, fp);

  // read the symbol table section
  int symtab_size = sh_table[symtab_sh_idx].sh_size;
  int symtab_offset = sh_table[symtab_sh_idx].sh_offset;
  int symtab_entsize = sh_table[symtab_sh_idx].sh_entsize;
  Elf32_Sym *symtab_section = (Elf32_Sym *) malloc(symtab_size);
  fseek(fp, symtab_offset, SEEK_SET);
  fread(symtab_section, symtab_size, 1, fp);

  // Fill symbolTable map
  for (int i = 0;  i < symtab_size/symtab_entsize;  i++) {
    string label = string((char *) (strtab_section + symtab_section[i].st_name));
    uint32_t address = symtab_section[i].st_value;
    symbolTable[label] = address;
  }

  // Find main
  for (int i = 0;  i < symtab_size/symtab_entsize;  i++) {
    if (!strcmp((char *) (strtab_section + symtab_section[i].st_name), "main") &&
        ELF32_ST_TYPE(symtab_section[i].st_info) == STT_FUNC) {
      mainAddr = symtab_section[i].st_value;
      break;
    }
  }

  // Read program headers
  int ph_table_size = ehdr->e_phentsize * ehdr->e_phnum;
  Elf32_Phdr *ph_table = (Elf32_Phdr *) malloc(ph_table_size);
  fseek(fp, ehdr->e_phoff, SEEK_SET);
  fread(ph_table, ph_table_size, 1, fp);

  // Identify text and data segments
//  printf("\nIdentify text and data segments\n");
  int text_ph_idx;
  Elf32_Off   text_p_offset;
  Elf32_Addr  text_p_vaddr;
  Elf32_Word  text_p_filesz;
  Elf32_Word  text_p_memsz;
  Elf32_Word  text_p_align;
  int data_ph_idx;
  Elf32_Off   data_p_offset;
  Elf32_Addr  data_p_vaddr;
  Elf32_Word  data_p_filesz;
  Elf32_Word  data_p_memsz;
  Elf32_Word  data_p_align;
//  printf("     idx   offset     vaddr   filesz    memsz    align    bound\n");
  for (int i = 0; i < ehdr->e_phnum; i++) {
    if (sh_table[text_sh_idx].sh_addr >= ph_table[i].p_vaddr &&
        sh_table[text_sh_idx].sh_addr < ph_table[i].p_vaddr + ph_table[i].p_memsz) {
      text_ph_idx = i;
      text_p_offset = ph_table[i].p_offset;
      text_p_vaddr =  ph_table[i].p_vaddr;
      text_p_filesz = ph_table[i].p_filesz;
      text_p_memsz =  ph_table[i].p_memsz;
      text_p_align =  ph_table[i].p_align;
//      printf("text: %2d %8d  %08x %8d %8d %08x %08x\n",
//          text_ph_idx, text_p_offset, text_p_vaddr, text_p_filesz, text_p_memsz, text_p_align, text_p_vaddr+text_p_memsz-1);
    }
    if (sh_table[data_sh_idx].sh_addr >= ph_table[i].p_vaddr &&
        sh_table[data_sh_idx].sh_addr < ph_table[i].p_vaddr + ph_table[i].p_memsz) {
      data_ph_idx = i;
      data_p_offset = ph_table[i].p_offset;
      data_p_vaddr =  ph_table[i].p_vaddr;
      data_p_filesz = ph_table[i].p_filesz;
      data_p_memsz =  ph_table[i].p_memsz;
      data_p_align =  ph_table[i].p_align;
//      printf("data: %2d %8d  %08x %8d %8d %08x %08x\n",
//          data_ph_idx, data_p_offset, data_p_vaddr, data_p_filesz, data_p_memsz, data_p_align, data_p_vaddr+data_p_memsz-1);
    }
  }
//  printf("text allotment: %d\n", data_p_vaddr - text_p_vaddr);

  // Allocate and initialize memory for text and data segments
  textSize = text_p_memsz;
  textBase = text_p_vaddr;
  textBound = textBase + textSize - 1;
  delete textMemory;
  textMemory = new uint8_t [textSize];
  fseek(fp, text_p_offset, SEEK_SET);
  fread(textMemory, text_p_filesz, 1, fp);
  Elf32_Word mem_word;
  assert(data_p_memsz <= dataSize && "ELF data_p_memsz exceeds dataSize");
  dataBase = data_p_vaddr;
  dataBound = dataBase + data_p_memsz - 1;
  fseek(fp, data_p_offset, SEEK_SET);
  fread(dataMemory, data_p_filesz, 1, fp);

//  printf("text: [%08x, %08x]\n", textBase, textBound);
//  printf("data: [%08x, %08x]\n", dataBase, dataBound);

  uint32_t entry = ehdr->e_entry;
//  printf("entry:  %08x\n", entry);
  write(32, entry, 0x0c000000 | ((mainAddr << 6) >> 8));  // jal main
  write(32, entry+4, 0x00000000);                // nop
  write(32, entry+8, 0x3402000a);                // ori $v0, $0, 10
  write(32, entry+12, 0x0000000c);               // syscall
  initPc  = entry;
}

uint32_t Memory::getSymbolAddr(char *symbol) {
    return symbolTable[string(symbol)];
}


