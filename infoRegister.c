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
#include "infoRegister.h"
#include <string.h>
regis regInfo(char* regist)
{
	if (strcmp("$t0", regist) == 0) {
		return regTable[0];
	}
	else if (strcmp("$t1", regist) == 0) {
		return regTable[1];
	}
	else if (strcmp("$t2", regist) == 0) {
		return regTable[2];
	}
	else if (strcmp("$t3", regist) == 0) {
		return regTable[3];
	}
	else if (strcmp("$s0", regist) == 0) {
		return regTable[4];
	}
	else if (strcmp("$s1", regist) == 0) {
		return regTable[5];
	}
	else if (strcmp("$s2", regist) == 0) {
		return regTable[6];
	}
	else {
		return regTable[7];
	}
}
	
