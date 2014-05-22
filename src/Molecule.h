#ifndef _MOLECULE_GUARD
#define _MOLECULE_GUARD 1

#include <string>
#include <vector>

class EdgeAggregator;

typedef enum
{
	active=1,
   decoy=2,
   crystal=3
} eFileSourcesT;

class Molecule
{
  public:
    eFileSourcesT fSource;
    int id;
    int numAtoms;
    int numBonds;
    int numSubStructs;
    int numFeatures;
    int numSets;
    int typeOfMolecule;
    int chargeType;
    int statusBits;
	 std::string name;
    std::string comments;

    Molecule() {}
    ~Molecule() {}

    void setGraphID(int id) { graphID = id; }
    int getGraphID() { return graphID; }
    virtual std::vector<EdgeAggregator> Compose(const Molecule&);
    virtual bool Equals(const Molecule&) const;

    void SetValues(char name_p[], int numAtoms_p, int numBonds_p, int numSubStructs_p, int numFeatures_p, int numSets_p, char moleculeType_p[], char chargeType_p[], char statusBit_p[], char comments_p[], eFileSourcesT fSource);
    int Parse(char moleculeName[], char moleculeStats[], char typeOfMolecule[], char moleculeCharge[], char moleculeStatusBits[], char comments[], eFileSourcesT fSource);

    std::string toString() const;
    friend std::ostream& operator<< (std::ostream& os, Molecule& mol);

  private:
    int graphID;
};

#endif