#include <iostream>
//#include <cstring>
//#include <stdio.h>
using namespace std;

/***************************************************************************************************************/

class ParsingData
{
	int numOfAtoms, numOfBonds, numOfMolecules;
}; /* parsing data */

/***************************************************************************************************************/

class Atom
{
	int id, subst_id, statusBit;
	char name[10], atomType[10], subst_name[10];
	float x, y, z, charge;
	public:
		void set_values (int id_p, char name_p[], float x_p, float y_p, float z_p, char atomType_p[], int subst_id_p, char subst_name_p[], float charge_p, char statusBit[]);
}; /* class Atom */

/***************************************************************************************************************/

void Atom::set_values (int id_p, char name_p[], float x_p, float y_p, float z_p, char atomType_p[], int subst_id_p, char subst_name_p[], float charge_p, char statusBit_p[])
{ /* atom set values */

	/* set literal values */
	id = id_p;
//	strcpy(name, name_p);
	x = x_p;
	y = y_p;
	z = z_p;
//	strcpy(atomType, atomType_p);
	subst_id = subst_id_p;
//	strcpy(subst_name, subst_name_p);
	charge = charge_p;
	
	/* Because the statusBit is a string with only 8 possible values, I'll store it as an integer */
	statusBit = -1;	/* the default value, if the status bit is unassigned */
/*	if(strcmp(statusBit_p, "DSPMOD") == 0)
		statusBit = 1;
	if(strcmp(statusBit_p, "TYPECOL") == 0)
		statusBit = 2;
	if(strcmp(statusBit_p, "CAP") == 0)
		statusBit = 3;
	if(strcmp(statusBit_p, "BACKBONE") == 0)
		statusBit = 4;
	if(strcmp(statusBit_p, "DICT") == 0)
		statusBit = 5;
	if(strcmp(statusBit_p, "ESSENTIAL") == 0)
		statusBit = 6;
	if(strcmp(statusBit_p, "WATER") == 0)
		statusBit = 7;
	if(strcmp(statusBit_p, "DIRECT") == 0)
		statusBit = 8;*/
} /* atom set values */

/***************************************************************************************************************/

class Bond
{ /* class bond */

	int id, originAtomID, targetAtomID, bondType, statusBit;
	
	public:
		void set_values (int id_p, int originAtom_p, int targetAtom_p, char bondType_p[],  char statusBit_p[]);
		
}; /* class bond */

/***************************************************************************************************************/
void Bond::set_values(int id_p, int originAtom_p, int targetAtom_p, char bondType_p[],  char statusBit_p[])
{ /* bond set values */

	/* set literal values */
	id = id_p;
	originAtomID = originAtom_p;
	targetAtomID = targetAtom_p;
	
	/* Because the bondType is a string with only 8 possible values, I'll store it as an integer */
/*	if(strcmp(bondType_p, "1") == 0)
		bondType = 1;
	if(strcmp(bondType_p, "2") == 0)
		bondType = 2;
	if(strcmp(bondType_p, "3") == 0)
		bondType = 3;
	if(strcmp(bondType_p, "am") == 0)
		bondType = 4;
	if(strcmp(bondType_p, "ar") == 0)
		bondType = 5;
	if(strcmp(bondType_p, "du") == 0)
		bondType = 6;
	if(strcmp(bondType_p, "un") == 0)
		bondType = 7;
	if(strcmp(bondType_p, "nc") == 0)
		bondType = 8;
	
	/* Because the statusBit is a string with only 6 possible values, I'll store it as an integer */
	statusBit = -1;	/* the default value, if the status bit is unassigned */
/*	if(strcmp(statusBit_p, "TYPECOL") == 0)
		statusBit = 1;
	if(strcmp(statusBit_p, "GROUP") == 0)
		statusBit = 2;
	if(strcmp(statusBit_p, "CAP") == 0)
		statusBit = 3;
	if(strcmp(statusBit_p, "BACKBONE") == 0)
		statusBit = 4;
	if(strcmp(statusBit_p, "DICT") == 0)
		statusBit = 5;
	if(strcmp(statusBit_p, "INTERRES") == 0)
		statusBit = 6;*/

} /* bond set values */

/***************************************************************************************************************/

class Molecule
{ /* class molecule */

	int numAtoms, numBonds, numSubStructs, numFeatures, numSets, moleculeType, chargeType, statusBits;
	char name[50], comments[100];
	
	public:
		void set_values(char name_p[], int numAtoms_p, int numBonds_p, int numSubStructs_p, int numFeatures_p, int numSets_p, char moleculeType_p[], char chargeType_p[], char statusBits_p[], char comments_p[]);

}; /* class molecule */


/***************************************************************************************************************/

void Molecule::set_values(char name_p[], int numAtoms_p, int numBonds_p, int numSubStructs_p, int numFeatures_p, int numSets_p, char moleculeType_p[], char chargeType_p[], char statusBit_p[], char comments_p[])
{ /* molecule set values */
	
	/* set literal values */
//	strcpy(name, name_p);
	numAtoms = numAtoms_p;
	numBonds = numBonds_p;
	numSubStructs = numSubStructs_p;
	numFeatures = numFeatures_p;
	numSets = numSets_p;
//	strcpy(comments, comments_p);

	/* Because the moleculeType is a string with only 5 possible values, I'll store it as an integer */
	moleculeType = -1; /* default value, if the moleculeType is unassigned */
/*	if(strcmp(moleculeType_p, "SMALL") == 0)
		moleculeType = 1;
	if(strcmp(moleculeType_p, "BIOPOLYMER") == 0)
		moleculeType = 2;
	if(strcmp(moleculeType_p, "PROTEIN") == 0)
		moleculeType = 3;
	if(strcmp(moleculeType_p, "NUCLEIC_ACID") == 0)
		moleculeType = 4;
	if(strcmp(moleculeType_p, "SACCHARIDE") == 0)
		moleculeType = 5;

	/* Because the chargeType is a string with only 12 possible values, I'll store it as an integer */
	chargeType = -1; /* default value, if the chargeType is unassigned */
/*	if(strcmp(chargeType_p, "NO_CHARGES") == 0)
		chargeType = 1;
	if(strcmp(chargeType_p, "DEL_RE") == 0)
		chargeType = 2;
	if(strcmp(chargeType_p, "GASTEIGER") == 0)
		chargeType = 3;
	if(strcmp(chargeType_p, "GAST_HUCK") == 0)
		chargeType = 4;
	if(strcmp(chargeType_p, "HUCKEL") == 0)
		chargeType = 5;
	if(strcmp(chargeType_p, "PULLMAN") == 0)
		chargeType = 6;
	if(strcmp(chargeType_p, "GAUSS80_CHARGES") == 0)
		chargeType = 7;
	if(strcmp(chargeType_p, "AMPAC_CHARGES") == 0)
		chargeType = 8;
	if(strcmp(chargeType_p, "MULLIKEN_CHARGES") == 0)
		chargeType = 9;
	if(strcmp(chargeType_p, "DICT_CHARGES") == 0)
		chargeType = 10;
	if(strcmp(chargeType_p, "MMFF94_CHARGES") == 0)
		chargeType = 11;
	if(strcmp(chargeType_p, "USER_CHARGES") == 0)
		chargeType = 12;

	/* Because the statusBits is a string with only 6 possible values, I'll store it as an integer */
	statusBits = -1; /* default value, if the statusBits is unassigned */
/*	if(strcmp(statusBit_p, "system") == 0 || strcmp(statusBit_p, "System") == 0 || strcmp(statusBit_p, "SYSTEM") == 0)
		statusBits = 1;
	if(strcmp(statusBit_p, "invalid_charges") == 0 || strcmp(statusBit_p, "Invalid_charges") == 0 || strcmp(statusBit_p, "INVALID_CHARGES") == 0)
		statusBits = 2;
	if(strcmp(statusBit_p, "analyzed") == 0 || strcmp(statusBit_p, "Analyzed") == 0 || strcmp(statusBit_p, "ANALYZED") == 0)
		statusBits = 3;
	if(strcmp(statusBit_p, "substituted") == 0 || strcmp(statusBit_p, "Substituted") == 0 || strcmp(statusBit_p, "SUBSTITUTED") == 0)
		statusBits = 4;
	if(strcmp(statusBit_p, "altered") == 0 || strcmp(statusBit_p, "Altered") == 0 || strcmp(statusBit_p, "ALTERED") == 0)
		statusBits = 5;
	if(strcmp(statusBit_p, "ref_angle") == 0 || strcmp(statusBit_p, "Ref_angle") == 0 || strcmp(statusBit_p, "REF_ANGLE") == 0)
		statusBits = 6;*/

} /* molecule set values */

/***************************************************************************************************************/

int parseAtom()
{
	/*
		Input: line from file 
		Output: atom
	*/
	/***/
} /* parse atom */

/***************************************************************************************************************/

int parseBond()
{
	/* 
		Input: line from file
		Output: bond
	*/
} /* parse bond */

/***************************************************************************************************************/

int parseMolecule()
{
	/*
		Input: line from file, and open file that is currently in a molecule section
		Output: molecule, and the file in the input has advanced to the next section
	*/
} /* parse molecule */

/***************************************************************************************************************/

int getAtoms()
{
	/*
		Input: An open file that is currently in an atom section
		Output: All atoms are read from that section, and the next section type or eof flag is returned
	*/

	/* read line from file */
	/* while not eof and line doesn't start with @ */
		/* parse atom */
		/* read line from file */

	/* return value should be:
		1	if the file enters an atom section
		2	if the file enters a bond section
		3	if the file enters a molecule section
		-1	if eof
	*/
	/* return */

} /* get atoms */

/***************************************************************************************************************/

int getBonds()
{
	/*
		Input: An open file that is currently in a bond section
		Output: All bonds are read from that section, and the next section type or eof flag is returned
	*/

	/* read line from file */
	/* while not eof and line doesn't start with @ */
		/* parse bond */
		/* read line from file */

	/* return value should be:
		1	if the file enters an atom section
		2	if the file enters a bond section
		3	if the file enters a molecule section
		-1	if eof
	*/
	/* return */

} /* get bonds */

/***************************************************************************************************************/

int getMolecules()
{
	/*
		Input: An open file that is currently in a molecule section
		Output: All molecules are read from that section, and the next section type or eof flag is returned
	*/

	/* read line from file */
	/* while not eof and line doesn't start with @ */
		/* parse molecule */
		/* read line from file */

	/* return value should be:
		1	if the file enters an atom section
		2	if the file enters a bond section
		3	if the file enters a molecule section
		-1	if eof
	*/
	/* return */

} /* get molecules */

/***************************************************************************************************************/

void readFile()
{
	/*
		Input: An open file with the pointer at the beginning
		Output: The file is parsed, then closed 
	*/

	/* read the first line of the file, and determine the section */
	/* while not eof */
		/* if file is in atom section, then get atoms */
		/* if file is in bonds section, then get bonds */
		/* if file is in molecules section, then get molecules */
	/* close file */

} /* read file */

/***************************************************************************************************************/

int main () 
{
	Atom rect;
	//FILE *fileNames;
	char buffer[50];

	/* open list of files */
	/*fileNames = fopen("listOfFiles.txt", "r");
	fscanf(fileNames, " %[^\n]", buffer);
	
	while(!feof(fileNames))
	{
		printf("%s\n", buffer);
		fscanf(fileNames, " %[^\n]", buffer);
	}

	fclose(fileNames);*/

	/* for each filename in the list of files */
		/* open file */
		/* read file */
	/* close list of files */
	/* give output */

	cout << "The program was successful\n";
	return 0;
}
