//  On my honor:
//
// - I have not discussed the C language code in my program with 
//   anyone other than my instructor or the teaching assistants 
//   assigned to this course.
//
//
// - I have not used C language code obtained from another student,
//   the Internet, or any other unauthorized source, either modified 
//   or unmodified.
//
//
// - If any C language code or documentation used in my program
//   was obtained from an authorized source, such as a text book or
//   course notes, that has been clearly noted with a proper citation 
//   in the comments of my program.
//
//
//
// - I have not designed this program in such a way as to defeat or 
//   interfere with the normal operation of the Curator System.
//
//   Karthikeya
//   karthikeyag
//
#ifndef OPCODE_H
#define OPCODE_H
enum _instruction {ADD, ADDI, LUI, LW, SUB, MUL, BEQ, SW};
typedef enum _instruction iType;

struct _operation {
	iType mnemonic;
	char* opcode;
	char* Funct;
};

typedef struct _operation opie;
static opie operationTable[8] = {
	{ADD, "000000", "100000"},
	{ADDI, "001000", "001000"},
	{LUI, "001111", "001111"},
	{LW, "100011", "100011"},
	{SUB, "000000", "100010"},
	{MUL, "011100", "000010"},
	{BEQ, "000100", "000100"},
	{SW, "101011", "101011"}
};
#endif
