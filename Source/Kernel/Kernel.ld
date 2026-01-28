ENTRY(_START)

SECTIONS
{
	. = 0x100000;
	__start_addr = .;
	.text : {
		__text_start_addr = .;
		*(.text.entry)
		*(.text)
		__text_end_addr = .;
	}

	.data : {
		__data_start_addr = .;
		*(.data)
		__data_end_addr = .;
	}

	.bss : {
		__bss_start_addr = .;
		*(.bss)
		__bss_end_addr = .;
	}

	__end_addr = .;
}
