#ifndef FRMR_STRINGFUNCS_H
#define FRMR_STRINGFUNCS_H

#include <vector>
#include <string>

using std::vector;
using std::string;

// splits string into a vector of its individual words, like a Python string split
vector<string> SplitString( const string p_line );
bool SubStringPresent( const string p_string, const string p_subString ); // look for substring within string, use instead of string::find to avoid size_t variables
string TruncatePath( const string p_path );
int FindIndexOfString( const string p_target, const vector<string> p_stringList );

#endif
