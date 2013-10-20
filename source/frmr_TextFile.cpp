#include <fstream>
#include <iostream>

#include "frmr_TextFile.h"

using std::cout;
using std::endl;

vector<string> frmr::TextFile::SplitString( const string inString ) const
{
    vector<string> outVector;
    string word = "";

    for ( unsigned int charIndex = 0; charIndex < inString.length(); charIndex++ )
    {
        if ( inString[charIndex] == ' ' || inString[charIndex] == '\t' )
        {
            if ( word.length() > 0 )
            {
                outVector.push_back( word );
                word = "";
            }
        }
        else
        {
            word += inString[charIndex];
        }
    }

	if ( word.length() > 0 )
	{
		outVector.push_back( word );
	}

    return outVector;
}

int frmr::TextFile::GetNumOfLines() const
{
    return lines.size();
}

vector<vector<string>> frmr::TextFile::GetLines() const
{
    return lines;
}

frmr::TextFile::TextFile( const string filename )
{
    std::ifstream readFile;
    readFile.open( filename.c_str() );

    if ( readFile.is_open() )
    {
        string fullLine;
        while ( getline( readFile, fullLine ) )
        {
            if ( !( fullLine == "" || fullLine == "\n" ) )
            {
				lines.push_back( SplitString( fullLine ) );
            }
        }
    }
    else
    {
        cout << "frmr::TextFile::TextFile() - Could not open file " << filename << endl;
    }
    readFile.close();
}
