#ifndef ASSET_MANAGER_H
#define ASSET_MANAGER_H

#include <map>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

using std::map;
using std::string;
using std::vector;

class AssetManager
{
public:
    enum class SearchMode
    {
        ALL,
        PERMANENT,
        TEMPORARY
    };

private:
    map<string, GLuint> permanentTextures;
    map<string, GLuint> temporaryTextures;

public:
    void    DeleteTemporaryAssets();
    GLuint  GetTexture( const string &textureName, const SearchMode mode ) const;
    bool    LoadTemporaryTextures( const vector<string> &temporaryTextureFilenames );
    GLuint  LoadTexture( const string &filename, const bool filter, const bool mask ) const;
    string  StripFilename( const string &filename ) const;

public:
    AssetManager( const string assetListFilename, const bool filterTextures );
};

#endif // ASSET_MANAGER_H
