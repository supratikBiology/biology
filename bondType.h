#ifndef _STDIO_H_
#define _STDIO_H_ 1
#include <stdio.h>
#endif

#ifndef _STRING_H_
#define _STRING_H_ 1
#include <string.h>
#endif

/****************************************************************************************/

#ifndef _ENUM_FILE_SOURCE
#define _ENUM_FILE_SOURCE 1
enum eFileSources
{
	active=1, decoy=2, crystal=3
};
#endif

typedef struct
{
	enum eFileSources fSource;
	int id, originAtomID, targetAtomID, typeOfBond, statusBit;
} bondType;

/****************************************************************************************/

void Bond_set_values(bondType *b, int id_p, int originAtom_p, int targetAtom_p, char bondType_p[],  char statusBit_p[], enum eFileSources fSource);
int parseBond(bondType *b, char buffer[], enum eFileSources fSource);