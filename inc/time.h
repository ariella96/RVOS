#ifndef TIME_H
#define TIME_H

// Write to the mtimecmp register
void write_mtimecmp(unsigned long time);

unsigned long read_mtime();

#endif