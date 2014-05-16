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
	int id, numAtoms, numBonds, numSubStructs, numFeatures, numSets, typeOfMolecule, chargeType, statusBits;
	char name[50], comments[100];
} moleculeType;

/****************************************************************************************/

void Molecule_set_values(moleculeType *m, char name_p[], int numAtoms_p, int numBonds_p, int numSubStructs_p, int numFeatures_p, int numSets_p, char moleculeType_p[], char chargeType_p[], char statusBit_p[], char comments_p[], enum eFileSources fSource);
int parseMolecule(moleculeType *m, char moleculeName[], char moleculeStats[], char typeOfMolecule[], char moleculeCharge[], char moleculeStatusBits[], char comments[], enum eFileSources fSource);
