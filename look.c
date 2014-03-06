#include <stdio.h>
#include <string.h>

/* enumerated file sources */
/*#define active 1
#define decoy 2
#define crystal 3

*/
/****************************************************************************************/


enum eFileSources
{
	active=1, decoy=2, crystal=3
};


//typedef int enum eFileSources;

typedef struct
{
	enum eFileSources fSource;
	int id, subst_id, statusBit;
	char name[10], typeOfAtom[10], subst_name[10];
	float x, y, z, charge;
} atomType;

typedef struct
{
	enum eFileSources fSource;
	int id, originAtomID, targetAtomID, typeOfBond, statusBit;
} bondType;

typedef struct
{
	enum eFileSources fSource;
	int numAtoms, numBonds, numSubStructs, numFeatures, numSets, typeOfMolecule, chargeType, statusBits;
	char name[50], comments[100];
} moleculeType;

/****************************************************************************************/

void Atom_set_values(atomType *a, int id_p, char name_p[], float x_p, float y_p, float z_p, char atomType_p[], int subst_id_p, char subst_name_p[], float charge_p, char statusBit_p[], enum eFileSources fSource);
void Bond_set_values(bondType *b, int id_p, int originAtom_p, int targetAtom_p, char bondType_p[],  char statusBit_p[], enum eFileSources fSource);
int getAtoms(FILE *f, int *numberOfAtoms, int *numberOfBonds, int *numberOfMolecules, enum eFileSources fSource);
int getBonds(FILE *f, int *numberOfAtoms, int *numberOfBonds, int *numberOfMolecules, enum eFileSources fSource);
int getMolecules(FILE *f, int *numberOfAtoms, int *numberOfBonds, int *numberOfMolecules, enum eFileSources fSource);
void Molecule_set_values(moleculeType *m, char name_p[], int numAtoms_p, int numBonds_p, int numSubStructs_p, int numFeatures_p, int numSets_p, char moleculeType_p[], char chargeType_p[], char statusBit_p[], char comments_p[], enum eFileSources fSource);
int parseAtom(atomType *a, char buffer[], enum eFileSources fSource);
int parseBond(bondType *b, char buffer[], enum eFileSources fSource);
int parseMolecule(moleculeType *m, char moleculeName[], char moleculeStats[], char typeOfMolecule[], char moleculeCharge[], char moleculeStatusBits[], char comments[], enum eFileSources fSource);
void readFile(FILE *f, int *numberOfAtoms, int *numberOfBonds, int *numberOfMolecules, enum eFileSources fSource);
int showFile(FILE *f, int x);

/****************************************************************************************/

int main(void)
{
	FILE *fileNames;
	FILE *currentFile;
	enum eFileSources fSource;
	char buffer[500], nameOfFile[20];
	int numberOfAtoms = 0, numberOfBonds = 0, numberOfMolecules = 0;

	/* open list of files */
	fileNames = fopen("listOfFiles.txt", "r");
	
	/* for each filename in the list of files */
	fscanf(fileNames, " %[^\n]", nameOfFile);
	while(!feof(fileNames))
	{
		printf("%s\n", nameOfFile);

		/* document filesource name */
		switch(nameOfFile[0])
		{
			case 'c' :
				fSource = crystal;
				break;
			case 'a' :
				fSource = active;
				break;
			case 'd' :
				fSource = decoy;
				break;
		}
		
		/* open file */
		currentFile = fopen(nameOfFile, "r");

		/* read file */
		readFile(currentFile, &numberOfAtoms, &numberOfBonds, &numberOfMolecules, fSource);

		fscanf(fileNames, " %[^\n]", nameOfFile);
	}

	/* close list of files */
	fclose(fileNames);

	/* give output */
	printf("%d atoms\n", numberOfAtoms);
	printf("%d bonds\n", numberOfBonds);
	printf("%d molecules\n", numberOfMolecules);

	printf("Done.\n");
	return 0;
} /* main */

/****************************************************************************************/

int showFile(FILE *f, int x)
{
  char buffer[1000];
  int lines = x;

  fscanf(f, " %[^\n]", buffer);
  while(!feof(f))
  {
    printf("%s\n", buffer);
    lines++;
    fscanf(f, " %[^\n]", buffer);
  }
  printf("lines = %d\n", lines);
  return lines;

} /* show file */

/****************************************************************************************/

void Atom_set_values(atomType *a, int id_p, char name_p[], float x_p, float y_p, float z_p, char atomType_p[], int subst_id_p, char subst_name_p[], float charge_p, char statusBit_p[], enum eFileSources fSource)
{
	/* set literal values */
	a->id = id_p;
	strcpy(a->name, name_p);
	a->x = x_p;
	a->y = y_p;
	a->z = z_p;
	strcpy(a->typeOfAtom, atomType_p);
	a->subst_id = subst_id_p;
	strcpy(a->subst_name, subst_name_p);
	a->charge = charge_p;
	a->fSource = fSource;
	
	/* Because the statusBit is a string with only 8 possible values, I'll store it as an integer */
	a->statusBit = -1;	/* the default value, if the status bit is unassigned */
	if(strcmp(statusBit_p, "DSPMOD") == 0)
		a->statusBit = 1;
	if(strcmp(statusBit_p, "TYPECOL") == 0)
		a->statusBit = 2;
	if(strcmp(statusBit_p, "CAP") == 0)
		a->statusBit = 3;
	if(strcmp(statusBit_p, "BACKBONE") == 0)
		a->statusBit = 4;
	if(strcmp(statusBit_p, "DICT") == 0)
		a->statusBit = 5;
	if(strcmp(statusBit_p, "ESSENTIAL") == 0)
		a->statusBit = 6;
	if(strcmp(statusBit_p, "WATER") == 0)
		a->statusBit = 7;
	if(strcmp(statusBit_p, "DIRECT") == 0)
		a->statusBit = 8;
} /* Atom_set_values */

/****************************************************************************************/

void Bond_set_values(bondType *b, int id_p, int originAtom_p, int targetAtom_p, char bondType_p[],  char statusBit_p[], enum eFileSources fSource)
{
	/* set literal values */
	b->id = id_p;
	b->originAtomID = originAtom_p;
	b->targetAtomID = targetAtom_p;
	b->fSource = fSource;
	
	/* Because the bondType is a string with only 8 possible values, I'll store it as an integer */
	if(strcmp(bondType_p, "1") == 0)
		b->typeOfBond = 1;
	if(strcmp(bondType_p, "2") == 0)
		b->typeOfBond = 2;
	if(strcmp(bondType_p, "3") == 0)
		b->typeOfBond = 3;
	if(strcmp(bondType_p, "am") == 0)
		b->typeOfBond = 4;
	if(strcmp(bondType_p, "ar") == 0)
		b->typeOfBond = 5;
	if(strcmp(bondType_p, "du") == 0)
		b->typeOfBond = 6;
	if(strcmp(bondType_p, "un") == 0)
		b->typeOfBond = 7;
	if(strcmp(bondType_p, "nc") == 0)
		b->typeOfBond = 8;
	
	/* Because the statusBit is a string with only 6 possible values, I'll store it as an integer */
	b->statusBit = -1;	/* the default value, if the status bit is unassigned */
	if(strcmp(statusBit_p, "TYPECOL") == 0)
		b->statusBit = 1;
	if(strcmp(statusBit_p, "GROUP") == 0)
		b->statusBit = 2;
	if(strcmp(statusBit_p, "CAP") == 0)
		b->statusBit = 3;
	if(strcmp(statusBit_p, "BACKBONE") == 0)
		b->statusBit = 4;
	if(strcmp(statusBit_p, "DICT") == 0)
		b->statusBit = 5;
	if(strcmp(statusBit_p, "INTERRES") == 0)
		b->statusBit = 6;

} /* Bond_set_values */


/****************************************************************************************/

int getAtoms(FILE *f, int *numberOfAtoms, int *numberOfBonds, int *numberOfMolecules, enum eFileSources fSource)
{
	/*
		Input: An open file that is currently in an atom section
		Output: All atoms are read from that section, and the next section type or eof flag is returned
	*/

	char buffer[500];
	atomType a;

	/* read line from file */
	fscanf(f, " %[^\n]", buffer);

	while(!feof(f) && buffer[0] != '@')
	{ /* while not eof and line doesn't start with @ */

		(*numberOfAtoms)++;

		/* parse atom */
		parseAtom(&a, buffer, fSource);

		/* spot checking atoms */
		if((*numberOfAtoms) % 10000 == 0)
		{ /* every 10,000 atoms will be displayed */

			printf("Atom:\tid=%d name=%s\tcoord=(%.3f,%.3f,%.3f)\ttype=%s\tsubstID=%d substName=%s \tcharge=%.3f \tstatusBit=%d\tSource=%d\n",
				a.id, a.name, a.x, a.y, a.z, a.typeOfAtom, a.subst_id, a.subst_name, a.charge, a.statusBit, a.fSource);

		} /* every 10,000 atoms will be displayed */


		/* read line from file */
		fscanf(f, " %[^\n]", buffer);

	} /* while not eof and line doesn't start with @ */

	/* return value should be:
		1	if the file enters an atom section
		2	if the file enters a bond section
		3	if the file enters a molecule section
		-1	if eof
	*/

	/* return */
	if(feof(f))
		return -1;
	if(buffer[9] == 'A')
		return 1;
	if(buffer[9] == 'B')
		return 2;
	if(buffer[9] == 'M')
		return 3;

	/* error */
	return -2;

} /* getAtoms */

/****************************************************************************************/

int getBonds(FILE *f, int *numberOfAtoms, int *numberOfBonds, int *numberOfMolecules, enum eFileSources fSource)
{
	/*
		Input: An open file that is currently in a bond section
		Output: All bonds are read from that section, and the next section type or eof flag is returned
	*/

	char buffer[500];
	bondType b;

	/* read line from file */
	fscanf(f, " %[^\n]", buffer);

	while(!feof(f) && buffer[0] != '@')
	{ /* while not eof and line doesn't start with @ */

		(*numberOfBonds)++;

		/* parse bond */
		parseBond(&b, buffer, fSource);


		/* spot checking bonds */
		if((*numberOfBonds) % 10000 == 0)
		{ /* every 10,000 bonds will be displayed */

			printf("Bond:\tid=%d originID=%d targetID=%d bondTypeID=%d statusBitID=%d\tsource=%d\n",
				b.id, b.originAtomID, b.targetAtomID, b.typeOfBond, b.statusBit, b.fSource);

		} /* every 10,000 bonds will be displayed */

		/* read line from file */
		fscanf(f, " %[^\n]", buffer);

	} /* while not eof and line doesn't start with @ */

	/* return value should be:
		1	if the file enters an atom section
		2	if the file enters a bond section
		3	if the file enters a molecule section
		-1	if eof
	*/

	/* return */
	if(feof(f))
		return -1;
	if(buffer[9] == 'A')
		return 1;
	if(buffer[9] == 'B')
		return 2;
	if(buffer[9] == 'M')
		return 3;

	/* error */
	return -2;

} /* getBonds */

/****************************************************************************************/

int getMolecules(FILE *f, int *numberOfAtoms, int *numberOfBonds, int *numberOfMolecules, enum eFileSources fSource)
{
	/*
		Input: An open file that is currently in a molecule section
		Output: All molecules are read from that section, and the next section type or eof flag is returned
	*/

	moleculeType m;
	char moleculeName[500], moleculeStats[500], typeOfMolecule[500], moleculeCharge[500], moleculeStatusBits[500], comments[500], buffer[500];

	/* initialize strings */
	strcpy(moleculeName, "");
	strcpy(moleculeStats, "");
	strcpy(typeOfMolecule, "");
	strcpy(moleculeCharge, "");
	strcpy(moleculeStatusBits, "");
	strcpy(comments, "");

	/* read name of molecule */
	fscanf(f, " %[^\n]", moleculeName);

	/* read molecule stats line */
	fscanf(f, " %[^\n]", moleculeStats);

	/* read molecule type */
	fscanf(f, " %[^\n]", typeOfMolecule);

	/* read charge type */
	fscanf(f, " %[^\n]", moleculeCharge);

	/* read line into buffer */
	fscanf(f, " %[^\n]", buffer);

	if(buffer[0] != '@')
	{ /* if buffer doesn't start with @ */

		/* copy buffer into status bits */
		strcpy(moleculeStatusBits, buffer);

		/* read line into buffer */
		fscanf(f, " %[^\n]", buffer);

		if(buffer[0] != '@')
		{ /* if buffer doesn't start with @ */

			/* copy buffer into comments */
			strcpy(comments, buffer);

		} /* if buffer doesn't start with @ */

	} /* if buffer doesn't start with @ */

	(*numberOfMolecules)++;

	/* parse molecule */
	parseMolecule(&m, moleculeName, moleculeStats, typeOfMolecule, moleculeCharge, moleculeStatusBits, comments, fSource);


	/* spot checking molecules */
	if((*numberOfBonds) % 1000 == 0)
	{ /* every 1,000 bonds will be displayed */

		printf("Molecule:\tname=%s numOfAtoms=%d numOfBonds=%d numOfSubst=%d numOfFeat=%d numOfSets=%d molTypeId=%d chargeTypeId=%d statusBitId=%d comment=%s\tSourse=%d\n",
			m.name, m.numAtoms, m.numBonds, m.numSubStructs, m.numFeatures, m.numSets, m.typeOfMolecule, m.chargeType, m.statusBits, m.comments, m.fSource);

	} /* every 10,000 bonds will be displayed */


	/* if next section can't be determined, read line from file to find next section */
	while(!feof(f) && buffer[0] != '@')
		fscanf(f, " %[^\n]", buffer);

	/* return value should be:
		1	if the file enters an atom section
		2	if the file enters a bond section
		3	if the file enters a molecule section
		-1	if eof
	*/

	/* return */
	if(feof(f))
		return -1;
	if(buffer[9] == 'A')
		return 1;
	if(buffer[9] == 'B')
		return 2;
	if(buffer[9] == 'M')
		return 3;

	/* error */
	return -2;

} /* getMolecules */

/****************************************************************************************/

void Molecule_set_values(moleculeType *m, char name_p[], int numAtoms_p, int numBonds_p, int numSubStructs_p, int numFeatures_p, int numSets_p, char moleculeType_p[], char chargeType_p[], char statusBit_p[], char comments_p[], enum eFileSources fSource)
{
	/* set literal values */
	strcpy(m->name, name_p);
	m->numAtoms = numAtoms_p;
	m->numBonds = numBonds_p;
	m->numSubStructs = numSubStructs_p;
	m->numFeatures = numFeatures_p;
	m->numSets = numSets_p;
	strcpy(m->comments, comments_p);
	m->fSource = fSource;

	/* Because the moleculeType is a string with only 5 possible values, I'll store it as an integer */
	m->typeOfMolecule = -1; /* default value, if the moleculeType is unassigned */
	if(strcmp(moleculeType_p, "SMALL") == 0)
		m->typeOfMolecule = 1;
	if(strcmp(moleculeType_p, "BIOPOLYMER") == 0)
		m->typeOfMolecule = 2;
	if(strcmp(moleculeType_p, "PROTEIN") == 0)
		m->typeOfMolecule = 3;
	if(strcmp(moleculeType_p, "NUCLEIC_ACID") == 0)
		m->typeOfMolecule = 4;
	if(strcmp(moleculeType_p, "SACCHARIDE") == 0)
		m->typeOfMolecule = 5;

	/* Because the chargeType is a string with only 12 possible values, I'll store it as an integer */
	m->chargeType = -1; /* default value, if the chargeType is unassigned */
	if(strcmp(chargeType_p, "NO_CHARGES") == 0)
		m->chargeType = 1;
	if(strcmp(chargeType_p, "DEL_RE") == 0)
		m->chargeType = 2;
	if(strcmp(chargeType_p, "GASTEIGER") == 0)
		m->chargeType = 3;
	if(strcmp(chargeType_p, "GAST_HUCK") == 0)
		m->chargeType = 4;
	if(strcmp(chargeType_p, "HUCKEL") == 0)
		m->chargeType = 5;
	if(strcmp(chargeType_p, "PULLMAN") == 0)
		m->chargeType = 6;
	if(strcmp(chargeType_p, "GAUSS80_CHARGES") == 0)
		m->chargeType = 7;
	if(strcmp(chargeType_p, "AMPAC_CHARGES") == 0)
		m->chargeType = 8;
	if(strcmp(chargeType_p, "MULLIKEN_CHARGES") == 0)
		m->chargeType = 9;
	if(strcmp(chargeType_p, "DICT_CHARGES") == 0)
		m->chargeType = 10;
	if(strcmp(chargeType_p, "MMFF94_CHARGES") == 0)
		m->chargeType = 11;
	if(strcmp(chargeType_p, "USER_CHARGES") == 0)
		m->chargeType = 12;

	/* Because the statusBits is a string with only 6 possible values, I'll store it as an integer */
	m->statusBits = -1; /* default value, if the statusBits is unassigned */
	if(strcmp(statusBit_p, "system") == 0 || strcmp(statusBit_p, "System") == 0 || strcmp(statusBit_p, "SYSTEM") == 0)
		m->statusBits = 1;
	if(strcmp(statusBit_p, "invalid_charges") == 0 || strcmp(statusBit_p, "Invalid_charges") == 0 || strcmp(statusBit_p, "INVALID_CHARGES") == 0)
		m->statusBits = 2;
	if(strcmp(statusBit_p, "analyzed") == 0 || strcmp(statusBit_p, "Analyzed") == 0 || strcmp(statusBit_p, "ANALYZED") == 0)
		m->statusBits = 3;
	if(strcmp(statusBit_p, "substituted") == 0 || strcmp(statusBit_p, "Substituted") == 0 || strcmp(statusBit_p, "SUBSTITUTED") == 0)
		m->statusBits = 4;
	if(strcmp(statusBit_p, "altered") == 0 || strcmp(statusBit_p, "Altered") == 0 || strcmp(statusBit_p, "ALTERED") == 0)
		m->statusBits = 5;
	if(strcmp(statusBit_p, "ref_angle") == 0 || strcmp(statusBit_p, "Ref_angle") == 0 || strcmp(statusBit_p, "REF_ANGLE") == 0)
		m->statusBits = 6;

} /* Molecule_set_values */

/****************************************************************************************/

int parseAtom(atomType *a, char buffer[], enum eFileSources fSource)
{
	/*
		Input: line from file 
		Output: atom
	*/

	int index = 0;
	int endOfString;
	char temp[500];
	int tempLength;
	int id, subst_id;
	char name[100], typeOfAtom[10], subst_name[100], statusBit[100];
	float x, y, z, charge;

	/* initialization*/
	subst_id = -1;
	strcpy(subst_name, "");
	charge = 0.0;
	strcpy(statusBit, "");

	/* get id */
	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	id = buffer[index] - '0';
	index++;

	while(buffer[index] != ' ' && buffer[index] != '\t' && buffer[index] != '\n' && buffer[index] != '\0')
	{ /* parse number */

		id *= 10;
		id += buffer[index] - '0';
		index++;
	} /* parse number */

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	/* get name */
	sscanf(buffer + index, " %s", name);
	index += strlen(name);

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	/* get x */
	sscanf(buffer + index, " %f", &x);
	while(buffer[index] != ' ' && buffer[index] != '\t')		//get past non-white space
		index++;

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	/* get y */
	sscanf(buffer + index, " %f", &y);
	while(buffer[index] != ' ' && buffer[index] != '\t')		//get past non-white space
		index++;

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	/* get z */
	sscanf(buffer + index, " %f", &z);
	while(buffer[index] != ' ' && buffer[index] != '\t')		//get past non-white space
		index++;

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	/* get type of item */
	sscanf(buffer + index, " %s", typeOfAtom);
	index += strlen(typeOfAtom);

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	if(buffer[index] != '\n' && buffer[index] != '\0')
	{ /* if not end of line */

		/* get subst_id */
		subst_id = buffer[index] - '0';
		index++;

		while(buffer[index] != ' ' && buffer[index] != '\t' && buffer[index] != '\n' && buffer[index] != '\0')
		{ /* parse number */

			subst_id *= 10;
			subst_id += buffer[index] - '0';
			index++;

		} /* parse number */
	} /* if not end of line */

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	if(buffer[index] != '\n' && buffer[index] != '\0')
	{ /* if not end of line */

		/* get subst_name */
		sscanf(buffer + index, " %s", subst_name);
		index += strlen(subst_name);

	} /* if not end of line */

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	if(buffer[index] != '\n' && buffer[index] != '\0')
	{ /* if not end of line */

		/* get charge */
		sscanf(buffer + index, " %f", &charge);
		while(buffer[index] != ' ' && buffer[index] != '\t' && buffer[index] != '\n' && buffer[index] != '\0')		//get past non-white space
			index++;

	} /* if not end of line */

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	if(buffer[index] != '\n' && buffer[index] != '\0')
	{ /* if not end of line */

		/* get status_bit */
		sscanf(buffer + index, " %s", statusBit);

	} /* if not end of line */

	/* set atom values */
	Atom_set_values(a, id, name, x, y, z, typeOfAtom, subst_id, subst_name, charge, statusBit, fSource);

} /* parseAtom */

/****************************************************************************************/

int parseBond(bondType *b, char buffer[], enum eFileSources fSource)
{
	/* 
		Input: line from file
		Output: bond
	*/
	
	int id;
	int originAtom;
	int targetAtom;
	char bondType[500];
	char statusBit[500];
	int index = 0;

	/* initialize */
	strcpy(statusBit, "");

	/* get id */
	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	id = buffer[index] - '0';
	index++;

	while(buffer[index] != ' ' && buffer[index] != '\t' && buffer[index] != '\n' && buffer[index] != '\0')
	{ /* parse number */

		id *= 10;
		id += buffer[index] - '0';
		index++;
	} /* parse number */

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	/* get origin atom */
	originAtom = buffer[index] - '0';
	index++;

	while(buffer[index] != ' ' && buffer[index] != '\t' && buffer[index] != '\n' && buffer[index] != '\0')
	{ /* parse number */

		originAtom *= 10;
		originAtom += buffer[index] - '0';
		index++;

	} /* parse number */

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	/* get target atom */
	targetAtom = buffer[index] - '0';
	index++;

	while(buffer[index] != ' ' && buffer[index] != '\t' && buffer[index] != '\n' && buffer[index] != '\0')
	{ /* parse number */

		targetAtom *= 10;
		targetAtom += buffer[index] - '0';
		index++;

	} /* parse number */

	while(buffer[index] == ' ' || buffer[index] == '\t')		//get past white space
		index++;

	/* get bond type */
	sscanf(buffer + index, " %s", bondType);
	index += strlen(bondType);

	if(buffer[index] != '\n' && buffer[index] != '\0')
	{ /* if not end of line */

		/* get status bit */
		sscanf(buffer + index, " %s", statusBit);

	} /* if not end of line */
	
	/* set bond values */
	Bond_set_values(b, id, originAtom, targetAtom, bondType, statusBit, fSource);

} /* parseBond */

/****************************************************************************************/

int parseMolecule(moleculeType *m, char moleculeName[], char moleculeStats[], char typeOfMolecule[], char moleculeCharge[], char moleculeStatusBits[], char comments[], enum eFileSources fSource)
{
	/*
		Input: line from file, and open file that is currently in a molecule section
		Output: molecule, and the file in the input has advanced to the next section
	*/

	int numAtoms_p; 
	int numBonds_p; 
	int numSubStructs_p; 
	int numFeatures_p; 
	int numSets_p;
	int index = 0;

	/* get number of atoms from stats */
	while(moleculeStats[index] == ' ' || moleculeStats[index] == '\t')	//get past white space
		index++;
	numAtoms_p = moleculeStats[index] - '0';
	index++;
	while(moleculeStats[index] != ' ' && moleculeStats[index] != '\t' && moleculeStats[index] != '\n' && moleculeStats[index] != '\0')
	{ /* parse number */
		numAtoms_p *= 10;
		numAtoms_p += moleculeStats[index] - '0';
		index++;
	} /* parse number */

	while(moleculeStats[index] == ' ' || moleculeStats[index] == '\t')	//get past white space but not newline
		index++;
	
	if(moleculeStats[index] != '\n' && moleculeStats[index] != '\0')
	{ /* if not end of line */

		/* get number of bonds */
		numBonds_p = moleculeStats[index] - '0';
		index++;
		while(moleculeStats[index] != ' ' && moleculeStats[index] != '\t' && moleculeStats[index] != '\n' && moleculeStats[index] != '\0')
		{ /* parse number */
			numBonds_p *= 10;
			numBonds_p += moleculeStats[index] - '0';
			index++;
		} /* parse number */

	} /* if not end of line */

	while(moleculeStats[index] == ' ' || moleculeStats[index] == '\t')	//get past white space but not newline
		index++;

	if(moleculeStats[index] != '\n' && moleculeStats[index] != '\0')
	{ /* if not end of line */

		numSubStructs_p = moleculeStats[index] - '0';
		index++;
		while(moleculeStats[index] != ' ' && moleculeStats[index] != '\t' && moleculeStats[index] != '\n' && moleculeStats[index] != '\0')
		{ /* get num_subst */
			numSubStructs_p *= 10;
			numSubStructs_p += moleculeStats[index] - '0';
			index++;	
		} /* parse number */
	} /* if not end of line */

	while(moleculeStats[index] == ' ' || moleculeStats[index] == '\t')	//get past white space but not newline
		index++;

	if(moleculeStats[index] != '\n' && moleculeStats[index] != '\0')
	{ /* if not end of line */
		
		numFeatures_p = moleculeStats[index] - '0';
		index++;
		while(moleculeStats[index] != ' ' && moleculeStats[index] != '\t' && moleculeStats[index] != '\n' && moleculeStats[index] != '\0')
		{ /* get num_feat */
			numFeatures_p *= 10;
			numFeatures_p += moleculeStats[index] - '0';
			index++;
		} /* parse number */
	} /* if not end of line */

	while(moleculeStats[index] == ' ' || moleculeStats[index] == '\t')	//get past white space but not newline
		index++;

	if(moleculeStats[index] != '\n' && moleculeStats[index] != '\0')
	{ /* if not end of line */
		
		numSets_p = moleculeStats[index] - '0';
		index++;
		while(moleculeStats[index] != ' ' && moleculeStats[index] != '\t' && moleculeStats[index] != '\n' && moleculeStats[index] != '\0')
		{ /* get num_set */
			numSets_p *= 10;
			numSets_p += moleculeStats[index] - '0';
			index++;
		} /* parse number */
	} /* if not end of line */

	/* set molecule values */
	Molecule_set_values(m, moleculeName, numAtoms_p, numBonds_p, numSubStructs_p, numFeatures_p, numSets_p, typeOfMolecule, moleculeCharge, moleculeStatusBits, comments, fSource);

} /* parseMolecule */

/****************************************************************************************/

void readFile(FILE *f, int *numberOfAtoms, int *numberOfBonds, int *numberOfMolecules, enum eFileSources fSource)
{
	/*
		Input: An open file with the pointer at the beginning
		Output: The file is parsed, then closed 
	*/

	char buffer[500];
	int sectionFlag;

	/* read the first line of the file, and determine the section */
	fscanf(f, " %[^\n]", buffer);
	if(buffer[9] == 'A')
		sectionFlag = 1;
	if(buffer[9] == 'B')
		sectionFlag = 2;
	if(buffer[9] == 'M')
		sectionFlag = 3;

	while(!feof(f) && sectionFlag != -1)
	{ /* while not eof */

		/* if file is in atom section, then get atoms */
		if(sectionFlag == 1)
			sectionFlag = getAtoms(f, numberOfAtoms, numberOfBonds, numberOfMolecules, fSource);

		/* if file is in bonds section, then get bonds */
		else if(sectionFlag == 2)
			sectionFlag = getBonds(f, numberOfAtoms, numberOfBonds, numberOfMolecules, fSource);

		/* if file is in molecules section, then get molecules */
		else if(sectionFlag == 3)
			sectionFlag = getMolecules(f, numberOfAtoms, numberOfBonds, numberOfMolecules, fSource);

	} /* while not eof */

	/* close file */
	fclose(f);

} /* readFile */

/****************************************************************************************/