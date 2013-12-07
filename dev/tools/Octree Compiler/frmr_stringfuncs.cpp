#include "frmr_stringfuncs.h"

// splits string into a vector of its individual words, like a Python string split
vector<string> SplitString( const string p_line )
{
    vector<string> outVector;
    string word = "";

    for ( unsigned int wordIndex = 0; wordIndex < p_line.length(); wordIndex++ )
    {
        if ( p_line[wordIndex] == ' ' or p_line[wordIndex] == '\t' )
        {
            if ( word.length() > 0 )
            {
                outVector.push_back( word );
                word = "";
            }
        }
        else
        {
            word.append( p_line.c_str(), wordIndex, 1 );
        }
    }
    outVector.push_back( word );
    return outVector;
}

// look for substring within string, use instead of string::find to avoid size_t variables
bool SubStringPresent( const string p_string, const string p_subString )
{
    string subStringFound = "";
    bool found;

    for ( unsigned int charIndex = 0; charIndex < p_string.length(); charIndex++ )
    {
        if ( p_string[charIndex] == p_subString[0] )
        {
            found = true;
            for ( unsigned int addIndex = 0; addIndex < p_subString.length(); addIndex++ )
            {
                if ( p_string[charIndex+addIndex] != p_subString[addIndex] )
                {
                    found = false;
                }
            }
            if ( found )
            {
                return found;
            }
        }
    }
    return false;
}

string TruncatePath( const string p_path )
{
    return p_path.substr( p_path.rfind('/')+1);
}

int FindIndexOfString( const string p_target, const vector<string> p_stringList )
{
    for ( unsigned int stringIndex = 0; stringIndex < p_stringList.size(); stringIndex++ )
    {
        if ( p_stringList[stringIndex] == p_target )
        {
            return stringIndex;
        }
    }
    return -1;
}
