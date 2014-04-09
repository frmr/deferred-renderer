#include <iostream>
#include "AssetManager.h"
#include "frmr/TextFile.h"

#define GL_R8 0x8229 //needed to make use of sized internal OpenGL format

using std::cout;
using std::endl;

void AssetManager::DeleteTemporaryAssets()
{
    for ( auto texIt : temporaryTextures )
    {
        glDeleteTextures( 1, &texIt.second );
    }

    temporaryTextures.clear();
}

GLuint AssetManager::GetTexture( const string &textureName, const SearchMode mode ) const
{
    if ( mode == SearchMode::ALL || mode == SearchMode::PERMANENT )
    {
        //perform binary search
        for ( auto texIt : permanentTextures )
        {
            if ( texIt.first == textureName )
            {
                return texIt.second;
            }
        }
    }

    if ( mode == SearchMode::ALL || mode == SearchMode::TEMPORARY )
    {
        for ( auto texIt : temporaryTextures )
        {
            if ( texIt.first == textureName )
            {
                return texIt.second;
            }
        }
    }

    cout << "AssetManager::GetTexture() - Could not find texture " << textureName << "." << endl;
    return 0;
}

bool AssetManager::LoadTemporaryTextures( const vector<string> &temporaryTextureFilenames )
{
    //load textures into temporaryTextures
    //sort alphabetically
    return true;
}

GLuint AssetManager::LoadTexture( const string &filename, const bool filter, const bool mask ) const
{
    sf::Image imageData;
    imageData.loadFromFile( filename );
    GLuint textureId;
    glGenTextures( 1, &textureId );
    glBindTexture( GL_TEXTURE_2D, textureId );
    if ( mask )
    {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_R8, imageData.getSize().x, imageData.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.getPixelsPtr() );
    }
    else
    {
        glTexImage2D( GL_TEXTURE_2D, 0, GL_RGBA, imageData.getSize().x, imageData.getSize().y, 0, GL_RGBA, GL_UNSIGNED_BYTE, imageData.getPixelsPtr() );
    }

    if ( filter )
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR );
    }
    else
    {
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST );
        glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST );
    }

    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT );
    glTexParameteri( GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT );

    return textureId;
}

string AssetManager::StripFilename( const string &filename ) const
{
    size_t lastSlash = filename.find_last_of( "/" );
    if ( lastSlash == std::string::npos )
    {
        cout << "AssetManager::StripFilename() - Filename " << filename << " does not contain a slash." << endl;
        lastSlash = 0;
    }
    else
    {
        if ( lastSlash < filename.length() )
        {
            lastSlash++;
        }
    }
    return filename.substr( lastSlash, std::string::npos );
}

AssetManager::AssetManager( const string assetListFilename, const bool filterTextures )
{
    frmr::TextFile listFile( assetListFilename );

    for ( auto lineIt : listFile.GetLines() )
    {
        if ( lineIt.size() < 2 )
        {
            cout << "AssetManager::AssetManager() - Encountered line with too few arguments." << endl;
        }
        else
        {
            if ( lineIt[0] == "texture" || lineIt[0] == "Texture" || lineIt[0] == "tex" || lineIt[0] == "Tex" )
            {
                permanentTextures[StripFilename( lineIt[1] )] = LoadTexture( lineIt[1], filterTextures, false );
                cout << "Loaded " << lineIt[1] << " as " << StripFilename( lineIt[1] ) << endl;
            }
            else if ( lineIt[0] == "mask" || lineIt[0] == "Mask" )
            {
                permanentTextures[StripFilename( lineIt[1] )] = LoadTexture( lineIt[1], filterTextures, true );
            }
            else if ( lineIt[0] == "billboard" || lineIt[0] == "Billboard" || lineIt[0] == "bill" || lineIt[0] == "Bill" )
            {

            }
            else
            {
                cout << "AssetManager::AssetManager() - Unrecognised command while loading assets: " << lineIt[0] << endl;
            }
        }
    }
    //sort alphabetically
}
