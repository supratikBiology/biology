#include <cstring>
#include <vector>

#include "Molecule.h"

#include "EdgeAggregator.h"


void Molecule::SetValues(char name_p[], int numAtoms_p, int numBonds_p, int numSubStructs_p, int numFeatures_p, int numSets_p, char moleculeType_p[], char chargeType_p[], char statusBit_p[], char comments_p[], eFileSourcesT fSource)
{
	/* set literal values */
	this->name = name_p;
	this->numAtoms = numAtoms_p;
	this->numBonds = numBonds_p;
	this->numSubStructs = numSubStructs_p;
	this->numFeatures = numFeatures_p;
	this->numSets = numSets_p;
	this->comments, comments_p;
	this->fSource = fSource;

	/* Because the moleculeType is a string with only 5 possible values, I'll store it as an integer */
	this->typeOfMolecule = -1; /* default value, if the moleculeType is unassigned */
	if(strcmp(moleculeType_p, "SMALL") == 0)          this->typeOfMolecule = 1;
	if(strcmp(moleculeType_p, "BIOPOLYMER") == 0)     this->typeOfMolecule = 2;
	if(strcmp(moleculeType_p, "PROTEIN") == 0)        this->typeOfMolecule = 3;
	if(strcmp(moleculeType_p, "NUCLEIC_ACID") == 0)   this->typeOfMolecule = 4;
	if(strcmp(moleculeType_p, "SACCHARIDE") == 0)     this->typeOfMolecule = 5;

	/* Because the chargeType is a string with only 12 possible values, I'll store it as an integer */
	this->chargeType = -1; /* default value, if the chargeType is unassigned */
	if(strcmp(chargeType_p, "NO_CHARGES") == 0)       this->chargeType = 1;
	if(strcmp(chargeType_p, "DEL_RE") == 0)           this->chargeType = 2;
	if(strcmp(chargeType_p, "GASTEIGER") == 0)        this->chargeType = 3;
	if(strcmp(chargeType_p, "GAST_HUCK") == 0)        this->chargeType = 4;
	if(strcmp(chargeType_p, "HUCKEL") == 0)           this->chargeType = 5;
	if(strcmp(chargeType_p, "PULLMAN") == 0)          this->chargeType = 6;
	if(strcmp(chargeType_p, "GAUSS80_CHARGES") == 0)  this->chargeType = 7;
	if(strcmp(chargeType_p, "AMPAC_CHARGES") == 0)    this->chargeType = 8;
	if(strcmp(chargeType_p, "MULLIKEN_CHARGES") == 0) this->chargeType = 9;
	if(strcmp(chargeType_p, "DICT_CHARGES") == 0)     this->chargeType = 10;
	if(strcmp(chargeType_p, "MMFF94_CHARGES") == 0)   this->chargeType = 11;
	if(strcmp(chargeType_p, "USER_CHARGES") == 0)     this->chargeType = 12;

	/* Because the statusBits is a string with only 6 possible values, I'll store it as an integer */
	this->statusBits = -1; /* default value, if the statusBits is unassigned */
	if(strcmp(statusBit_p, "system") == 0 || strcmp(statusBit_p, "System") == 0 || strcmp(statusBit_p, "SYSTEM") == 0)
		this->statusBits = 1;
	if(strcmp(statusBit_p, "invalid_charges") == 0 || strcmp(statusBit_p, "Invalid_charges") == 0 || strcmp(statusBit_p, "INVALID_CHARGES") == 0)
		this->statusBits = 2;
	if(strcmp(statusBit_p, "analyzed") == 0 || strcmp(statusBit_p, "Analyzed") == 0 || strcmp(statusBit_p, "ANALYZED") == 0)
		this->statusBits = 3;
	if(strcmp(statusBit_p, "substituted") == 0 || strcmp(statusBit_p, "Substituted") == 0 || strcmp(statusBit_p, "SUBSTITUTED") == 0)
		this->statusBits = 4;
	if(strcmp(statusBit_p, "altered") == 0 || strcmp(statusBit_p, "Altered") == 0 || strcmp(statusBit_p, "ALTERED") == 0)
		this->statusBits = 5;
	if(strcmp(statusBit_p, "ref_angle") == 0 || strcmp(statusBit_p, "Ref_angle") == 0 || strcmp(statusBit_p, "REF_ANGLE") == 0)
		this->statusBits = 6;

}

/****************************************************************************************/

int Molecule::Parse(char moleculeName[], char moleculeStats[], char typeOfMolecule[], char moleculeCharge[], char moleculeStatusBits[], char comments[], eFileSourcesT fSource)
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
	SetValues(moleculeName, numAtoms_p, numBonds_p, numSubStructs_p, numFeatures_p, numSets_p, typeOfMolecule, moleculeCharge, moleculeStatusBits, comments, fSource);

} /* parseMolecule */

/****************************************************************************************/

std::vector<EdgeAggregator> Molecule::Compose(const Molecule& thatMolecule)
{
    std::vector<EdgeAggregator> newMolecules;
    
    return newMolecules;
}

bool Molecule::Equals(const Molecule&) const
{
    return false;
}

std::string Molecule::toString() const
{
    return this->name;
}

std::ostream& operator<< (std::ostream& os, Molecule& mol)
{
    os << mol.toString();
    
    return os;
}