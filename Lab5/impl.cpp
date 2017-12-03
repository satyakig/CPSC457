/*
 * impl.cpp
 * 
 * Student Name: Satyaki Ghosh
 * Student Number: 10077685
 * 
 * Assignment 5
 * Question 7
 * T-01
 * CPSC 457 Fall 2017
 */

#include <stdio.h>
#include <string>
#include <vector>
#include <iostream>

using namespace std;

typedef std::string SS;
typedef std::vector<SS> VS;

struct DEntry {
    SS fname = SS(4096, 0);
    int size = 0;
    int startIndex = 0;
    int findex = 0;
    bool tooManyBlocks = false;
    bool tooFewBlocks = false;
    bool hasCycle = false;
    bool sharesBlocks = false;
};

struct BLOCKS {
    int index;
    int nextIndex;
    bool free = true;
    vector <int> files;
};

vector <DEntry> entries;
vector <BLOCKS> fatM;
int blockSize, nFiles, fatSize;

static SS join(const VS & toks, const SS & sep) {
    SS res;
    bool first = true;
    for(auto & t : toks) { res += (first ? "" : sep) + t; first = false;}
    return res;
}

bool ifCycle(int index, int fileIndex) {
    for(int i = 0; i < fatM.at(index).files.size(); i++) {
        if(fatM.at(index).files.at(i) == fileIndex)
            return true;
    }
    return false;
}

// re-implement this function
//
// Parameters:
//   blockSize - contains block size as read in from input
//   files - array containing the entries as read in from input
//   fat - array representing the FAT as read in from input
// Return value:
//   the function should return the number of free blocks
//   also, for ever entry in the files[] array, you need to set the appropriate flags:
//      i.e. tooManyBlocks, tooFewBlocks, hasCycle and sharesBlocks
int checkConsistency()
{
    for(int entriesIndex = 0; entriesIndex < entries.size(); entriesIndex++) {
        int blockIndex = entries.at(entriesIndex).startIndex;
        int size = entries.at(entriesIndex).size;
        int blocksNeeded = entries.at(entriesIndex).size / blockSize;
        if(entries.at(entriesIndex).size % blockSize != 0)
            blocksNeeded += 1;

        int blocksHave = 0;
        while(blockIndex != -1) {
            bool cycle = ifCycle(blockIndex, entriesIndex);
            if(cycle) {
                entries.at(entriesIndex).hasCycle = true;
                break;
            }
            else {
                fatM.at(blockIndex).free = false;
                fatM.at(blockIndex).files.push_back(entriesIndex);
                blocksHave++;
            }
            blockIndex = fatM.at(blockIndex).nextIndex;
        }            
        if(blocksHave > blocksNeeded)
            entries.at(entriesIndex).tooManyBlocks = true;
        if(blocksHave < blocksNeeded)
            entries.at(entriesIndex).tooFewBlocks = true;                   
    }

    for(int i = 0; i < fatM.size(); i++) {        
        if(fatM.at(i).free == false && fatM.at(i).files.size() > 1) {
            for(int j = 0; j < fatM.at(i).files.size(); j++)
                entries.at(fatM.at(i).files.at(j)).sharesBlocks = true;                        
        }
    }

    int freeBlocks = 0;
    for(int i = 0; i < fatM.size(); i++) {
        if(fatM.at(i).free)
            freeBlocks++;
    }
    return freeBlocks;
}

int main()
{
    try {
        // read in blockSize, nFiles, fatSize
        if(3 != scanf("%d %d %d", &blockSize, &nFiles, &fatSize))
            throw "cannot read blockSize, nFiles and fatSize";
        if(blockSize < 1 || blockSize > 1024) throw "bad block size";
        if(nFiles < 0 || nFiles > 50) throw "bad number of files";
        if(fatSize < 1 || fatSize > 200000) throw "bad FAT size";
        // read in the entries
        for(int i = 0 ; i < nFiles ; i ++) {
            DEntry e;
            if(3 != scanf("%s %d %d", (char *) e.fname.c_str(), & e.startIndex, & e.size))
                throw "bad file entry";
            e.fname = e.fname.c_str();
            if(e.fname.size() < 1 || e.fname.size() > 16)
                throw "bad filename in file entry";
            if(e.startIndex < -1 || e.startIndex >= fatSize) throw "bad first block in fille entry";
            if(e.size < 0 || e.size > 1073741824) throw "bad file size in file entry";
            e.findex = i;
            entries.push_back(e);
        }
        // read in the FAT
        vector<int> fat(fatSize);
        for(int i = 0 ; i < fatSize ; i ++ ) {
            if(1 != scanf("%d", & fat[i])) throw "could not read FAT entry";
            if(fat[i] < -1 || fat[i] >= fatSize) throw "bad FAT entry";
        }
        for(int i = 0 ; i < fatSize ; i ++ ) {
            BLOCKS temp;
            temp.index = i;
            temp.nextIndex = fat.at(i);
            fatM.push_back(temp);
        }

        int nFreeBlocks = checkConsistency();

        size_t maxflen = 0;
        for(auto & e : entries) maxflen = max(maxflen, e.fname.size());
        SS fmt = "  %" + to_string(maxflen) + "s: %s\n";
        
        printf("Issues with files:\n");
        for(auto & e : entries) {
            VS issues;
            if(e.tooFewBlocks) issues.push_back("not enough blocks");
            if(e.tooManyBlocks) issues.push_back("too many blocks");
            if(e.hasCycle) issues.push_back("contains cycle");
            if(e.sharesBlocks) issues.push_back("shares blocks");
            printf(fmt.c_str(), e.fname.c_str(), join(issues, ", ").c_str());
        }
        printf("Number of free blocks: %d\n", nFreeBlocks);

    }
    catch( const char * err) {
        fprintf(stderr, "Error: %s\n", err);
    }
    catch( ... ) {
        fprintf(stderr, "Error: unknown.\n");
    }
    return 0;
}
