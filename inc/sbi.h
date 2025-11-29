#ifndef SBI_H
#define SBI_H

// SBI function call arguments
struct sbiargs {
	unsigned long x0; // SBI function call first argument
	unsigned long x1; // SBI function call second argument
	unsigned long x2; // SBI function call third argument
	unsigned long x3; // SBI function call fourth argument
	unsigned long x4; // SBI function call fifth argument
	unsigned long x5; // SBI function call sixth argument
};

// SBI function specification
struct sbifunc {
	unsigned long fid; // SBI function ID
	unsigned long eid; // SBI extension ID
};

// Return value for SBI calls
struct sbiret {
	long error; // SBI error code
	// SBI return value
	union {
		long value; // SBI return value, signed
		unsigned long uvalue; // SBI return value, unsigned
	};
};

// Handles an SBI function call `func`, with arguments `args`
struct sbiret handle_sbi(struct sbiargs args, struct sbifunc func);

#endif