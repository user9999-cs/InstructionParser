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
#include "ASMParser.h"
#include "infoRegister.h"
#include "infOp.h"

#include <inttypes.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

opie getOpType(iType type);
static iType getCommand(char* userInput);

static void init_pASM(ParseResult* pASM);
void getBin(int16_t integer, char* ptr);

regis regInfo(char* regist);


ParseResult* parseASM(const char* const pASM) 
{
	
	ParseResult* result = calloc(1, sizeof(ParseResult));
	init_pASM(result);
	char helperArray[100];
	char* command;
	result->ASMInstruction = calloc(strlen(pASM)+1, sizeof(char));
	result->Mnemonic = calloc(5, sizeof(char));
	result->Opcode = calloc(7, sizeof(char));
	strcpy(helperArray, pASM);
	strcat(result->ASMInstruction, helperArray);
	command = strtok(helperArray, " ");
	iType userInstruction = getCommand(command);
	opie code = getOpType(userInstruction);
	strcpy(result->Mnemonic, command);
	strcpy(result->Opcode, code.opcode);
	char* rdOp = NULL;
	char* rsOp = NULL;
	char* rtOp = NULL;
	if (userInstruction == ADD || userInstruction == SUB || userInstruction == MUL) 
	{
		uint8_t rd, rs, rt;
		rdOp = strtok(NULL, ", ");
		rsOp = strtok(NULL, ", ");
		rtOp = strtok(NULL, ", ");
		rd = regInfo(rdOp).regNum;
		rs = regInfo(rsOp).regNum;
		rt = regInfo(rtOp).regNum;
		result->rdName = calloc(strlen(rdOp)+1, sizeof(char));
		result->rsName = calloc(strlen(rsOp)+1, sizeof(char));
		result->rtName = calloc(strlen(rtOp)+1, sizeof(char));
		result->Funct = calloc(7, sizeof(char));
		result->RD = calloc(6, sizeof(char));
		result->RS = calloc(6, sizeof(char));
		result->RT = calloc(6, sizeof(char));
		strcpy(result->Funct, code.Funct);
		strcpy(result->rdName, rdOp);
		strcpy(result->rsName, rsOp);
		strcpy(result->rtName, rtOp);
		result->rd = rd;
		result->rs = rs;
		result->rt = rt;
		strcpy(result->RD, regInfo(rdOp).binNum);
		strcpy(result->RS, regInfo(rsOp).binNum);
		strcpy(result->RT, regInfo(rtOp).binNum);
	}
	else if (userInstruction == LUI) 
	{
		int16_t imm;
		rtOp = strtok(NULL, ", ");
		imm = atoi(strtok(NULL, ", "));
		result->RS = calloc(6, sizeof(char));
		result->RT = calloc(6, sizeof(char));
		result->IMM = calloc(17, sizeof(char));
		result->rtName = calloc(strlen(rtOp)+1, sizeof(char));
		result->Imm = imm;
		imm = 0xFFFF & imm;
		char * currBin = calloc(17, sizeof(char));
		getBin(imm, currBin);
		strcpy(result->IMM, currBin);
		strcpy(result->rtName, rtOp);
		free(currBin);
		result->rs = 0;
		result->rt = regInfo(rtOp).regNum;
		strcpy(result->RS, "00000");
		strcpy(result->RT, regInfo(rtOp).binNum);
	}
	else if (userInstruction == ADDI || userInstruction == BEQ) 
	{
		uint8_t rs, rt;
		int32_t imm;
		if (userInstruction == ADDI) 
		{
			rtOp = strtok(NULL, ", ");
			rsOp = strtok(NULL, ", ");
		}
		else 
		{
			rsOp = strtok(NULL, ", ");
			rtOp = strtok(NULL, ", ");
		}
		imm = atoi(strtok(NULL, ", "));
		rs = regInfo(rsOp).regNum;
		rt = regInfo(rtOp).regNum;
		result->rsName = calloc(strlen(rsOp)+1, sizeof(char));
		result->rtName = calloc(strlen(rtOp)+1, sizeof(char));
		result->RS = calloc(6, sizeof(char));
		result->RT = calloc(6, sizeof(char));
		result->IMM = calloc(17, sizeof(char));
		strcpy(result->rsName, rsOp);
		strcpy(result->rtName, rtOp);
		result->rs = rs;
		result->rt = rt;
		strcpy(result->RS, regInfo(rsOp).binNum);
		strcpy(result->RT, regInfo(rtOp).binNum);
		result->Imm = imm;
		imm = 0x0000FFFF & imm;
		char* currBin = calloc(20, sizeof(char));
		getBin(imm, currBin);
		int x = 0;
		for (x = 0; x < 16 - strlen(currBin); x++) 
		{
			strcat(result->IMM, "0");
		}
		strcat(result->IMM, currBin);
		free(currBin);
	}
	else if (userInstruction == LW || userInstruction == SW) 
	{
		rtOp = strtok(NULL, ", ");
		int16_t imm = atoi(strtok(NULL, "("));
		rsOp = strtok(NULL, ")");
		result->RS = calloc(6, sizeof(char));
		result->RT = calloc(6, sizeof(char));
		result->IMM = calloc(17, sizeof(char));
		result->rsName = calloc(strlen(rsOp)+1, sizeof(char));
		result->rtName = calloc(strlen(rsOp)+1, sizeof(char));
		result->Imm = imm;
		char* currBin = calloc(20, sizeof(char));
		getBin(imm, currBin);
		int k = 0;
		for (k = 0; k < 16 - strlen(currBin); k++) 
		{
			strcat(result->IMM, "0");
		}
		strcat(result->IMM, currBin);
		strcpy(result->rsName, rsOp);
		strcpy(result->rtName, rtOp);
		free(currBin);
		result->rs = regInfo(rsOp).regNum;
		result->rt = regInfo(rtOp).regNum;
		strcpy(result->RS, regInfo(rsOp).binNum);
		strcpy(result->RT, regInfo(rtOp).binNum);
	}
	return result;
}

void getBin(int16_t integer, char* ptr) 
{	
	for (int x = 15; x >= 0; x--) 
	{
		if ((integer & 0x1) == 1) 
		{
			ptr[x] = '1';
		}
		else 
		{
			
			ptr[x] = '0';
		}
		integer = integer >> 1;
	}
}

static void init_pASM(ParseResult* pASM) 
{
	pASM->rdName = NULL;
	pASM->rsName = NULL;
	pASM->rtName = NULL;
	pASM->ASMInstruction = NULL;
	pASM->Mnemonic = NULL;
	pASM->Imm = 0;
	pASM->rd = 255;
	pASM->rs = 255;
	pASM->rt = 255;
	pASM->RD = NULL;
	pASM->RS = NULL;
	pASM->RT = NULL;
	pASM->IMM = NULL;
	pASM->Opcode = NULL;
	pASM->Funct = NULL;
}


static iType getCommand(char* userInput) 
{
	if (strcmp(userInput, "add") == 0) 
	{
		return ADD;
	}
	else if (strcmp(userInput, "sub") == 0) 
	{
		return SUB;
	}
	else if (strcmp(userInput, "addi") == 0) 
	{
		return ADDI;
	}
	else if (strcmp(userInput, "mul") == 0) 
	{
		return MUL;
	}
	else if (strcmp(userInput, "beq") == 0) 
	{
		return BEQ;
	}
	else if (strcmp(userInput, "lui") == 0) 
	{
		return LUI;
	}
	else if (strcmp(userInput, "lw") == 0) 
	{
		return LW;
	}
	else 
	{
		return SW;
	}
}
