#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "GLEW/glew.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Config.h"
#include "Simulation.h"
#include "frmr/Shader.h"
#include "frmr/Vec3f.h"

class RenderManager
{
private:
    //frmr::Vec3f     ambientLightColor;

    frmr::Shader    geometryPassShader;
    frmr::Shader    lightPassShader;
    frmr::Shader    depthTransferShader;

    GLuint			deferredFbo; // The FBO Id

    GLuint          surfaceTextureId;

	GLuint			normalsRT; // The normals render target
	GLuint	        normalsTexture; // The OpenGL texture for the normals render target
	GLuint          diffuseRT;
	GLuint          diffuseTexture;
	GLuint          depthRT;
	GLuint          depthTexture;

	GLuint			normalsId; // Normals texture handle for the shader
	GLuint          diffuseId;
	GLuint          depthId;

	GLuint          viewportParamsId;
	GLuint          perspectiveMatrixId;

	GLuint          lightPositionId;
	GLuint          lightColorId;
	GLuint          lightLinearAttenuationId;
	GLuint          lightQuadraticAttenuationId;

	GLuint			shadowFbo;
	GLuint			shadowDepth;	//texture?
	GLuint			shadowMap;

	GLuint          icosphere;
	GLuint          fullscreenQuad;

private:
	void	CreateDeferredFbo( const EngineConfig &engineCfg );
	void	CreateShadowCubemap();
    GLuint  CreateFullscreenQuad( const EngineConfig &engineCfg ) const;
    void    ResetViewport( const EngineConfig &engineCfg ) const;
    void    BindDeferredFbo() const;
    void    UnbindDeferredFbo() const;
	void	BindShadowFbo( const GLenum cubeFace ) const;
	void	UnbindShadowFbo() const;
public:
    void Render( const Simulation &gameSim, const EngineConfig &engineCfg ) const;
    void SetupOpenGL( const EngineConfig &engineCfg ) const;
    void SimpleRender( const Simulation &gameSim, const EngineConfig &engineCfg ) const;

public:
    RenderManager( const EngineConfig &engineCfg );
    ~RenderManager();
};

#endif // RENDER_MANAGER_H
