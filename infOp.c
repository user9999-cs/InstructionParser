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
#include "infOp.h"
opie getOpType(iType type)
{
	switch (type) {
		case ADD:
			return operationTable[0];
		case ADDI:
			return operationTable[1];
		case LUI:
			return operationTable[2];
		case LW:
			return operationTable[3];
		case SUB:
			return operationTable[4];
		case MUL:
			return operationTable[5];
		case BEQ:
			return operationTable[6];
		case SW:
			return operationTable[7];
		default:
			return operationTable[0];
		}
	}
