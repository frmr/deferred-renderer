#include <fstream>
#include <iostream>

#include "../frmr/TextFile.h"

using std::cout;
using std::endl;

vector<string> frmr::TextFile::SplitString( const string inString ) const
{
    vector<string> wordList;
    string word = "";

    for ( auto charIt : inString )
    {
        if ( charIt == ' ' || charIt == '\t' )
        {
            if ( !word.empty() )
            {
                wordList.push_back( word );
                word.clear();
            }
        }
        else
        {
            word += charIt;
        }
    }

	if ( !word.empty() )
	{
		wordList.push_back( word );
	}

    return wordList;
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
            if ( fullLine != "" && fullLine != "\n" )
            {
				lines.push_back( SplitString( fullLine ) );
            }
        }
    }
    else
    {
        cout << "frmr::TextFile::TextFile() - Could not open file " << filename << "." << endl;
    }
    readFile.close();
}
