#ifndef RENDER_MANAGER_H
#define RENDER_MANAGER_H

#include "GL/glew.h"

#include <SFML/Graphics.hpp>
#include <SFML/OpenGL.hpp>

#include "Config.h"
#include "Simulation.h"
#include "frmr_Shader.h"
#include "frmr_Vec3f.h"

class RenderManager
{
private:
    frmr::Vec3f     ambientLightColor;
    frmr::Shader    deferredShadingShader;
    frmr::Shader    deferredRenderingShader;
    frmr::Shader    depthTransferShader;

    GLuint          m_testTexture;
    GLuint          m_testTextureID;

    GLuint			m_fbo; // The FBO ID

	GLuint			m_normalsRT; // The normals render target
	GLuint	        m_normalsTexture; // The OpenGL texture for the normals render target
	GLuint          m_diffuseRT;
	GLuint          m_diffuseTexture;
	GLuint          m_depthRT;
	GLuint          m_depthTexture;

	GLuint			m_normalsID; // Normals texture handle for the shader
	GLuint          m_diffuseID;
	GLuint          m_depthID;

	GLuint          m_viewportParamsID;
	GLuint          m_perspectiveMatrixID;

	GLuint          m_lightPositionID;
	GLuint          m_lightColorID;
	GLuint          m_lightLinearAttenuationID;
	GLuint          m_lightQuadraticAttenuationID;

	GLuint          icosphere;
	GLuint          fullscreenQuad;

private:
    GLuint  CreateFullscreenQuad( const EngineConfig &engineCfg ) const;
    bool    InvertMatrixGL( const float matrixIn[16], float matrixOut[16] ) const;
    void    MultiplyMatricesGL( const float matrixInA[16], const float matrixInB[16], float matrixOut[16] ) const;
    void    SetToOrthogonalProjection( const EngineConfig &engineCfg ) const;
    void    SetToPerspectiveProjection( const EngineConfig &engineCfg ) const;
    void    StartRenderToFBO( const EngineConfig &engineCfg ) const;
    void    StopRenderToFBO() const;

public:
    void Render( const Simulation &gameSim, const EngineConfig &engineCfg ) const;
    void SetupOpenGL( const EngineConfig &engineCfg ) const;
    void SimpleRender( const Simulation &gameSim, const EngineConfig &engineCfg ) const;

public:
    RenderManager( const EngineConfig &engineCfg );
    ~RenderManager();
};

#endif // RENDER_MANAGER_H
