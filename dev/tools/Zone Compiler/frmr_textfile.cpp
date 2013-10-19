#include <fstream>

#include "frmr_textfile.h"
#include "frmr_stringfuncs.h"

TextFile::TextFile( const string p_filename )
{
    std::ifstream readFile;
    readFile.open( p_filename.c_str() );

    if ( readFile.is_open() )
    {
        string fullLine;
        while ( getline( readFile, fullLine ) )
        {
            if ( !( fullLine == "" || fullLine == "\n" ) )
            {
                vector<string> splitLine = SplitString( fullLine );
                lines.push_back( splitLine );
            }
        }
    }
    readFile.close();
    numOfLines = lines.size();
}

unsigned int TextFile::GetNumOfLines() const
{
    return numOfLines;
}

vector< vector<string> > TextFile::GetLines() const
{
    return lines;
}
