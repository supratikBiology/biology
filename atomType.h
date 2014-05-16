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
	int id, subst_id, statusBit;
	char name[10], typeOfAtom[10], subst_name[10];
	float x, y, z, charge;
} atomType;

/****************************************************************************************/

void Atom_set_values(atomType *a, int id_p, char name_p[], float x_p, float y_p, float z_p, char atomType_p[], int subst_id_p, char subst_name_p[], float charge_p, char statusBit_p[], enum eFileSources fSource);
int parseAtom(atomType *a, char buffer[], enum eFileSources fSource);