#ifndef FRMR_TEXTFILE_H
#define FRMR_TEXTFILE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

class TextFile
{
private:
    unsigned int                numOfLines;
    vector< vector<string> >    lines;

public:
    unsigned int GetNumOfLines() const;
    vector< vector<string> > GetLines() const;
    TextFile( const string p_filename );
};

#endif
