/*this is a linker file to explicitly link kernel
 */

OUTPUT_FORMAT(elf32-i386)
ENTRY(_start)
SECTIONS
{
    . = 0x100000;           /*kernel code starts at this memory address */
    .text : { *(.text) }
    .data : { *(.data) }
    .bss : { *(.bss) }
}


