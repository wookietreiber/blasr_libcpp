#ifndef _BLASR_FASTA_SEQUENCE_HPP_
#define _BLASR_FASTA_SEQUENCE_HPP_

#include <string>
#include <iostream>
#include <stdint.h>
#include <string>
#include <cstring>
#include <ostream>
#include "Types.h"
#include "NucConversion.hpp"
#include "Enumerations.h"
#include "DNASequence.hpp"
#include "reads/ZMWGroupEntry.hpp"

//
// NO proteins for now.
class FASTASequence : public DNASequence {
private:
    // Whether or not to delete title in Free() 
    // regardless of deleteOnExit (to prevent memory leak
    // when ReferenceSubstring and CopyTitle are called together).
    bool deleteTitleOnExit; 

public:
    char *title;
    int titleLength;

    FASTASequence();
    inline ~FASTASequence();

    void PrintSeq(std::ostream &out, int lineLength = 50, char delim='>');

    int GetStorageSize();

    std::string GetName() const;

    virtual bool StoreHoleNumber(int holeNumber);
    virtual bool StoreHoleStatus(unsigned char holeStatus);
    virtual bool StorePlatformId(PlatformId platformId);
    virtual bool StoreZMWData(ZMWGroupEntry &data);
    virtual bool StoreXY(int16_t xy[]);

    bool GetHoleNumber (int &holeNumberP); 

    bool GetXY(int xyP[]); 

    void ShallowCopy(const FASTASequence &rhs); 

    std::string GetTitle() const; 

    void DeleteTitle();

    void CopyTitle(const char* str, int strlen); 

    void CopyTitle(std::string str);

    void GetFASTATitle(std::string& fastaTitle); 

    void CopySubsequence(FASTASequence &rhs, int readStart, int readEnd=-1); 

    void AppendToTitle(std::string str); 

    void Assign(FASTASequence &rhs); 

    void MakeRC(FASTASequence &rhs, DNALength rhsPos=0, DNALength rhsLength=0); 

    void ReverseComplementSelf(); 

    void operator=(const FASTASequence &rhs); 

    void Copy(const FASTASequence &rhs); 

    void Copy(const std::string & rhsTitle, const std::string & rhsSeq);

    void Copy(const std::string & rhsSeq);

#ifdef USE_PBBAM
    /// Copies a BamRecord as a FASTASequence.
    void Copy(const PacBio::BAM::BamRecord & record);
#endif

    void Free(); 
};


inline FASTASequence::~FASTASequence(){
    FASTASequence::Free();
}

#endif
