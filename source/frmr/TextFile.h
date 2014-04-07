#ifndef FRMR_TEXTFILE_H
#define FRMR_TEXTFILE_H

#include <vector>
#include <string>

using std::vector;
using std::string;

namespace frmr
{
	class TextFile
	{
	private:
		vector<vector<string>> lines;

	private:
		vector<string> SplitString( const string inString ) const;

	public:
		int GetNumOfLines() const;
		vector<vector<string>> GetLines() const;
		TextFile( const string filename );
	};
}
#endif
