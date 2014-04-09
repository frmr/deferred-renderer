#include "RenderManager.h"

#include "IcosphereGenerator.h"
#include "ProjectionState.h"
#include <iostream>

using std::cout;
using std::endl;

GLuint RenderManager::CreateFullscreenQuad( const EngineConfig &engineCfg ) const
{
    GLuint quadDisplayList = glGenLists( 1 );

    glNewList( quadDisplayList, GL_COMPILE );
        glBegin(GL_QUADS);
            glTexCoord2f(0.0f, 1.0f);
            glVertex2f(0.0f, 0.0f);
            glTexCoord2f(0.0f, 0.0f);
            glVertex2f(0.0f, (float) engineCfg.GetActiveHeight());
            glTexCoord2f(1.0f, 0.0f);
            glVertex2f( (float) engineCfg.GetActiveWidth(), (float) engineCfg.GetActiveHeight() );
            glTexCoord2f(1.0f, 1.0f);
            glVertex2f( (float) engineCfg.GetActiveWidth(), 0.0f );
        glEnd();
    glEndList();

    return quadDisplayList;
}

//this code is from MESA implementation of GLU's gluInvertMatrix(), although it is slightly modified
bool RenderManager::InvertMatrixGL( const float matIn[16], float matOut[16] ) const
{
    float inv[16];
    float det;
    int i;

    inv[0] = matIn[5] * matIn[10] * matIn[15] - matIn[5] * matIn[11] * matIn[14] - matIn[9] * matIn[6] * matIn[15] + matIn[9] * matIn[7] * matIn[14] + matIn[13] * matIn[6] * matIn[11] - matIn[13] * matIn[7] * matIn[10];
    inv[4] = -matIn[4] * matIn[10] * matIn[15] + matIn[4] * matIn[11] * matIn[14] + matIn[8] * matIn[6] * matIn[15] - matIn[8] * matIn[7] * matIn[14] - matIn[12] * matIn[6] * matIn[11] + matIn[12] * matIn[7] * matIn[10];
    inv[8] = matIn[4] * matIn[9] * matIn[15] - matIn[4] * matIn[11] * matIn[13] - matIn[8] * matIn[5] * matIn[15] + matIn[8] * matIn[7] * matIn[13] + matIn[12] * matIn[5] * matIn[11] - matIn[12] * matIn[7] * matIn[9];
    inv[12] = -matIn[4] * matIn[9] * matIn[14] + matIn[4] * matIn[10] * matIn[13] + matIn[8] * matIn[5] * matIn[14] - matIn[8] * matIn[6] * matIn[13] - matIn[12] * matIn[5] * matIn[10] + matIn[12] * matIn[6] * matIn[9];
    inv[1] = -matIn[1] * matIn[10] * matIn[15] + matIn[1] * matIn[11] * matIn[14] + matIn[9] * matIn[2] * matIn[15] - matIn[9] * matIn[3] * matIn[14] - matIn[13] * matIn[2] * matIn[11] + matIn[13] * matIn[3] * matIn[10];
    inv[5] = matIn[0] * matIn[10] * matIn[15] - matIn[0] * matIn[11] * matIn[14] - matIn[8] * matIn[2] * matIn[15] + matIn[8] * matIn[3] * matIn[14] + matIn[12] * matIn[2] * matIn[11] - matIn[12] * matIn[3] * matIn[10];
    inv[9] = -matIn[0] * matIn[9] * matIn[15] + matIn[0] * matIn[11] * matIn[13] + matIn[8] * matIn[1] * matIn[15] - matIn[8] * matIn[3] * matIn[13] - matIn[12] * matIn[1] * matIn[11] + matIn[12] * matIn[3] * matIn[9];
    inv[13] = matIn[0] * matIn[9] * matIn[14] - matIn[0] * matIn[10] * matIn[13] - matIn[8] * matIn[1] * matIn[14] + matIn[8] * matIn[2] * matIn[13] + matIn[12] * matIn[1] * matIn[10] - matIn[12] * matIn[2] * matIn[9];
    inv[2] = matIn[1] * matIn[6] * matIn[15] - matIn[1] * matIn[7] * matIn[14] - matIn[5] * matIn[2] * matIn[15] + matIn[5] * matIn[3] * matIn[14] + matIn[13] * matIn[2] * matIn[7] - matIn[13] * matIn[3] * matIn[6];
    inv[6] = -matIn[0] * matIn[6] * matIn[15] + matIn[0] * matIn[7] * matIn[14] + matIn[4] * matIn[2] * matIn[15] - matIn[4] * matIn[3] * matIn[14] - matIn[12] * matIn[2] * matIn[7] + matIn[12] * matIn[3] * matIn[6];
    inv[10] = matIn[0] * matIn[5] * matIn[15] - matIn[0] * matIn[7] * matIn[13] - matIn[4]  * matIn[1] * matIn[15] + matIn[4] * matIn[3] * matIn[13] + matIn[12] * matIn[1] * matIn[7] - matIn[12] * matIn[3] * matIn[5];
    inv[14] = -matIn[0] * matIn[5] * matIn[14] + matIn[0] * matIn[6] * matIn[13] + matIn[4] * matIn[1] * matIn[14] - matIn[4] * matIn[2] * matIn[13] - matIn[12] * matIn[1] * matIn[6] + matIn[12] * matIn[2] * matIn[5];
    inv[3] = -matIn[1] * matIn[6] * matIn[11] + matIn[1] * matIn[7] * matIn[10] + matIn[5] * matIn[2] * matIn[11] - matIn[5] * matIn[3] * matIn[10] - matIn[9] * matIn[2] * matIn[7] + matIn[9] * matIn[3] * matIn[6];
    inv[7] = matIn[0] * matIn[6] * matIn[11] - matIn[0] * matIn[7] * matIn[10] - matIn[4] * matIn[2] * matIn[11] + matIn[4] * matIn[3] * matIn[10] + matIn[8] * matIn[2] * matIn[7] - matIn[8] * matIn[3] * matIn[6];
    inv[11] = -matIn[0] * matIn[5] * matIn[11] + matIn[0] * matIn[7] * matIn[9] + matIn[4] * matIn[1] * matIn[11] - matIn[4] * matIn[3] * matIn[9] - matIn[8] * matIn[1] * matIn[7] + matIn[8] * matIn[3] * matIn[5];
    inv[15] = matIn[0] * matIn[5] * matIn[10] - matIn[0] * matIn[6] * matIn[9] - matIn[4] * matIn[1] * matIn[10] + matIn[4] * matIn[2] * matIn[9] + matIn[8] * matIn[1] * matIn[6] - matIn[8] * matIn[2] * matIn[5];

    det = matIn[0] * inv[0] + matIn[1] * inv[4] + matIn[2] * inv[8] + matIn[3] * inv[12];

    if ( det < 0.001f && det > -0.001f )
    {
        return false;
    }

    det = 1.0f / det;

    for ( i = 0; i < 16; i++ )
    {
        matOut[i] = inv[i] * det;
    }

    return true;
}

//this code is from GLU's MultiplyMatrices4by4OpenGL_FLOAT(), although the parameters have been renamed
void RenderManager::MultiplyMatricesGL( const float matInA[16], const float matInB[16], float matOut[16] ) const
{
    matOut[0] = matInA[0] * matInB[0] + matInA[4] * matInB[1] + matInA[8] * matInB[2] + matInA[12] * matInB[3];
    matOut[4] = matInA[0] * matInB[4] + matInA[4] * matInB[5] + matInA[8] * matInB[6] + matInA[12] * matInB[7];
    matOut[8] = matInA[0] * matInB[8] + matInA[4] * matInB[9] + matInA[8] * matInB[10] + matInA[12] * matInB[11];
    matOut[12] = matInA[0] * matInB[12] + matInA[4] * matInB[13] + matInA[8] * matInB[14] + matInA[12] * matInB[15];
    matOut[1] = matInA[1] * matInB[0] + matInA[5] * matInB[1] + matInA[9] * matInB[2] + matInA[13] * matInB[3];
    matOut[5] = matInA[1] * matInB[4] + matInA[5] * matInB[5] + matInA[9] * matInB[6] + matInA[13] * matInB[7];
    matOut[9] = matInA[1] * matInB[8] + matInA[5] * matInB[9] + matInA[9] * matInB[10] + matInA[13] * matInB[11];
    matOut[13] = matInA[1] * matInB[12] + matInA[5] * matInB[13] + matInA[9] * matInB[14] + matInA[13] * matInB[15];
    matOut[2] = matInA[2] * matInB[0] + matInA[6] * matInB[1] + matInA[10] * matInB[2] + matInA[14] * matInB[3];
    matOut[6] = matInA[2] * matInB[4] + matInA[6] * matInB[5] + matInA[10] * matInB[6] + matInA[14] * matInB[7];
    matOut[10] = matInA[2] * matInB[8] + matInA[6] * matInB[9] + matInA[10] * matInB[10] + matInA[14] * matInB[11];
    matOut[14] = matInA[2] * matInB[12] + matInA[6] * matInB[13] + matInA[10] * matInB[14] + matInA[14] * matInB[15];
    matOut[3] = matInA[3] * matInB[0] + matInA[7] * matInB[1] + matInA[11] * matInB[2] + matInA[15] * matInB[3];
    matOut[7] = matInA[3] * matInB[4] + matInA[7] * matInB[5] + matInA[11] * matInB[6] + matInA[15] * matInB[7];
    matOut[11] = matInA[3] * matInB[8] + matInA[7] * matInB[9] + matInA[11] * matInB[10] + matInA[15] * matInB[11];
    matOut[15] = matInA[3] * matInB[12] + matInA[7] * matInB[13] + matInA[11] * matInB[14] + matInA[15] * matInB[15];
}

void RenderManager::ResetViewport( const EngineConfig &engineCfg ) const
{
    glViewport( 0, 0, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight() );
}

void RenderManager::SetToOrthogonalProjection( const EngineConfig &engineCfg ) const
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    glOrtho(0.0, (double) engineCfg.GetActiveWidth(), (double) engineCfg.GetActiveHeight(), 0.0, -1.0, 1.0);
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void RenderManager::SetToPerspectiveProjection( const EngineConfig &engineCfg ) const
{
    glMatrixMode( GL_PROJECTION );
    glLoadIdentity();
    gluPerspective( engineCfg.GetActiveVerticalFOV(), (float) engineCfg.GetActiveWidth() / (float) engineCfg.GetActiveHeight(), 1.0f, 5000.0f );
    glMatrixMode( GL_MODELVIEW );
    glLoadIdentity();
}

void RenderManager::StartRenderToFBO( const EngineConfig &engineCfg ) const
{
    glBindFramebuffer( GL_FRAMEBUFFER, fbo );
	glPushAttrib( GL_VIEWPORT_BIT );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //clear the FBO

	glActiveTexture( GL_TEXTURE0 );
	glEnable( GL_TEXTURE_2D );

	// Specify what to render and start acquiring
	GLenum buffers[] = { GL_COLOR_ATTACHMENT0, GL_COLOR_ATTACHMENT1 };
	glDrawBuffers(2, buffers);
}

void RenderManager::StopRenderToFBO() const
{
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glPopAttrib();
}

void RenderManager::Render( const Simulation &gameSim, const EngineConfig &engineCfg ) const
{
    SetToPerspectiveProjection( engineCfg );

    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT ); //clear the screen buffer
    glUseProgram( deferredShadingShader.GetProgramHandler() );

    glDepthMask( GL_TRUE ); //enable writing to the depth buffer
    glEnable( GL_DEPTH_TEST );

    StartRenderToFBO( engineCfg );

    glEnable( GL_CULL_FACE );
    glCullFace( GL_BACK );

    //bind the surface texture and pass it to the shader
    glActiveTexture( GL_TEXTURE0 );
    glUniform1i( surfaceTextureId, 0 );

	//render the simulation
	ProjectionState cameraProjection = gameSim.RenderLit( engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight() );
	int viewportMatrix[4];
	float perspectiveMatrix[16];

	cameraProjection.CopyViewportMatrix( viewportMatrix );
	cameraProjection.CopyPerspectiveMatrix( perspectiveMatrix );

    StopRenderToFBO();

    //render depth buffer onto a fullscreen quad
    glClear( GL_DEPTH_BUFFER_BIT );
    SetToOrthogonalProjection( engineCfg );
    glUseProgram( depthTransferShader.GetProgramHandler() );
    glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, depthTexture );
	glUniform1i( depthId, 0 );
    glCallList( fullscreenQuad );

    glDepthMask( GL_FALSE ); //disable writing to the depth buffer
    glDisable( GL_DEPTH_TEST );

    //send all the textures, the viewport parameters and the perspective matrix to the deferred rendering shader so we don't have to do it for every light
    glUseProgram( deferredRenderingShader.GetProgramHandler() );
	glUniform1i( normalsId, 0 );
	glUniform1i( diffuseId, 1 );
	glUniform1i( depthId, 2 );
    glUniform4iv( viewportParamsId, 4, viewportMatrix );
    glUniformMatrix4fv( perspectiveMatrixId, 16, false, perspectiveMatrix );
    glUseProgram( 0 );

    glColor4f( 1.0f, 1.0f, 1.0f, 1.0f );

    glEnable( GL_STENCIL_TEST );
    glClearStencil( 0 );

    //const vector<Light> staticLights;// = gameSim.GetStaticLights();
    vector<Light> staticLights = gameSim.GetStaticLights();

    glDisable( GL_BLEND );

    for ( auto lightIt : staticLights )
    {
        SetToPerspectiveProjection( engineCfg );

        glUseProgram( 0 );

        glColorMask( GL_FALSE, GL_FALSE, GL_FALSE, GL_FALSE ); //disable writing to the color buffer
        glStencilMask( 0xFF ); //enable writing to the stencil buffer

        glClear( GL_STENCIL_BUFFER_BIT );

        glStencilFunc( GL_NEVER, 1, 0xFF ); // never pass stencil test
        glStencilOp( GL_REPLACE, GL_KEEP, GL_KEEP );  // replace stencil buffer values to ref=1

        glRotatef( -gameSim.GetCamera().GetRotation().GetX(), 1.0f, 0.0f, 0.0f );
        glRotatef( -gameSim.GetCamera().GetRotation().GetY(), 0.0f, 1.0f, 0.0f );
        glTranslatef( -gameSim.GetCamera().GetPosition().GetX(), -gameSim.GetCamera().GetPosition().GetY(), -gameSim.GetCamera().GetPosition().GetZ() );

        glPushMatrix();
            //render light radius at correct location and scale
            glTranslatef( lightIt.GetPosition().GetX(), lightIt.GetPosition().GetY(), lightIt.GetPosition().GetZ() );
            glScalef( lightIt.GetRadius(), lightIt.GetRadius(), lightIt.GetRadius() );

            glDisable( GL_CULL_FACE );
            glDisable( GL_DEPTH_TEST ); //TODO: use the stencil buffer with depth fail and cull front face
            glBindTexture( GL_TEXTURE_2D, 0 );
            glCallList( icosphere );
        glPopMatrix();

        //shadows
        glEnable( GL_DEPTH_TEST ); //using the depth buffer from the FBO
        glEnable( GL_CULL_FACE );
        glCullFace( GL_FRONT );
        //increment on depth fail
        glStencilFunc( GL_EQUAL, 1, 0xFF );
        glStencilOp( GL_KEEP, GL_INCR, GL_KEEP );
        lightIt.RenderShadowVolume();
        glCullFace( GL_BACK );
        //decrement on depth fail
        glStencilFunc( GL_EQUAL, 2, 0xFF );
        glStencilOp( GL_KEEP, GL_DECR, GL_KEEP );
        lightIt.RenderShadowVolume();

        glDisable( GL_DEPTH_TEST );

        //light only where the stencil buffer is equal to 2
        glStencilFunc( GL_EQUAL, 1, 0xFF );

        glColorMask( GL_TRUE, GL_TRUE, GL_TRUE, GL_TRUE ); //enable writing to the color buffer
        glStencilMask( 0x00 ); //disable writing to the stencil buffer

        SetToOrthogonalProjection( engineCfg );

        glUseProgram( deferredRenderingShader.GetProgramHandler() );

        //pass the light's attributes to the shader
        glUniform3f( lightPositionId, lightIt.GetPosition().GetX(), lightIt.GetPosition().GetY(), lightIt.GetPosition().GetZ() );
        glUniform3f( lightColorId, lightIt.GetColor().GetX(), lightIt.GetColor().GetY(), lightIt.GetColor().GetZ() );
        glUniform1f( lightLinearAttenuationId, lightIt.GetLinearAttenuation() );
        glUniform1f( lightQuadraticAttenuationId, lightIt.GetQuadraticAttenuation() );

        glDisable( GL_CULL_FACE );

        //enable blending so that each new quad adds to whatever's in the render buffer
        glEnable( GL_BLEND );
        glBlendFunc( GL_ONE, GL_ONE );

        //bind the diffuse, normal and depth maps before rendering fullscreen quad
        glActiveTexture( GL_TEXTURE0 );
        glBindTexture( GL_TEXTURE_2D, normalsTexture );

        glActiveTexture( GL_TEXTURE1 );
        glBindTexture( GL_TEXTURE_2D, diffuseTexture );

        glActiveTexture( GL_TEXTURE2 );
        glBindTexture( GL_TEXTURE_2D, depthTexture );

        glCallList( fullscreenQuad );

        glDisable( GL_BLEND );
    }

    glDisable(GL_STENCIL_TEST );

    // Reset OpenGL state
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE2);
	glBindTexture(GL_TEXTURE_2D, 0);

	glUseProgram( 0 );

    //change to perspective projection
	//enable depth test
	//enable depth mask
	//draw projectiles

    //change to orthogonal projection
	//disable depth test
	//disable depth mask
	//draw HUD
	//draw UI
}

void RenderManager::SetupOpenGL( const EngineConfig &engineCfg ) const
{
    glewInit();
    ResetViewport( engineCfg );
    SetToPerspectiveProjection( engineCfg );
    glClearColor( 0.1f, 0.0f, 0.0f, 0.0f );
}

void RenderManager::SimpleRender( const Simulation &gameSim, const EngineConfig &engineCfg ) const
{
    glEnable( GL_TEXTURE_2D );
    SetToPerspectiveProjection( engineCfg );
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );
    glEnable( GL_DEPTH_TEST );
    glDisable( GL_CULL_FACE );
    glUseProgram( 0 );
    //gameSim.RenderLit( engineCfg.GetFOV(), engineCfg.GetActiveVerticalFOV() );
    gameSim.RenderLit( engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight() );
}

RenderManager::RenderManager( const EngineConfig &engineCfg )
{
    SetupOpenGL( engineCfg );
    deferredShadingShader.Load( "../data/shaders/deferredShading.vert", "../data/shaders/deferredShading.frag" );
    deferredRenderingShader.Load( "../data/shaders/deferredRendering.vert", "../data/shaders/deferredRendering.frag" );
    depthTransferShader.Load( "../data/shaders/depthTransfer.vert", "../data/shaders/depthTransfer.frag" );

    // Generate the OGL resources for what we need
	glGenFramebuffers(1, &fbo);
	glGenRenderbuffers(1, &normalsRT);
	glGenRenderbuffers(1, &diffuseRT);
	glGenRenderbuffers(1, &depthRT );

    // Bind the FBO so that the next operations will be bound to it
	glBindFramebuffer(GL_FRAMEBUFFER, fbo);

	// Bind the normal render target
	glBindRenderbuffer(GL_RENDERBUFFER, normalsRT);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB8, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_RENDERBUFFER, normalsRT);

    glBindRenderbuffer(GL_RENDERBUFFER, diffuseRT);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_RGB8, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_RENDERBUFFER, diffuseRT);

	glBindRenderbuffer(GL_RENDERBUFFER, depthRT);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight());
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, depthRT);

	// Generate and bind the OGL texture for normals
	glGenTextures(1, &normalsTexture);
	glBindTexture(GL_TEXTURE_2D, normalsTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight(), 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Attach the texture to the FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, normalsTexture, 0);

    // Generate and bind the OGL texture for diffuse
	glGenTextures(1, &diffuseTexture);
	glBindTexture(GL_TEXTURE_2D, diffuseTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB8, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight(), 0, GL_RGB, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Attach the texture to the FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT1, GL_TEXTURE_2D, diffuseTexture, 0);

    // Generate and bind the OGL texture for depth
	glGenTextures(1, &depthTexture);
	glBindTexture(GL_TEXTURE_2D, depthTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, engineCfg.GetActiveWidth(), engineCfg.GetActiveHeight(), 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	// Attach the texture to the FBO
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, depthTexture, 0);
    //check that FBO is complete

    if ( glCheckFramebufferStatus( GL_FRAMEBUFFER ) != GL_FRAMEBUFFER_COMPLETE )
    {
        cout << "RenderManager::RenderManager() - FBO is not complete." << endl;
    }

	glBindFramebuffer(GL_FRAMEBUFFER, 0);
    glDisable(GL_LIGHTING);

    //get the memory location of the surface texture in the shader
	surfaceTextureId = glGetUniformLocation( deferredShadingShader.GetProgramHandler(), "surfaceTexture" );

	// Get the handles from the shader
	normalsId = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "normalsTexture" );
	diffuseId = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "diffuseTexture" );
	depthId = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "depthTexture" );

	viewportParamsId = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "viewportParams" );
	perspectiveMatrixId = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "perspectiveMatrix" );

	lightPositionId = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "lightPosition" );
	lightColorId = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "lightColor" );
	lightLinearAttenuationId = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "lightLinearAttenuation" );
    lightQuadraticAttenuationId = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "lightQuadraticAttenuation" );


    fullscreenQuad = CreateFullscreenQuad( engineCfg );
	icosphere = IcosphereGenerator::GenerateIcosphereDisplayList( 1 );
}

RenderManager::~RenderManager()
{
    glDeleteTextures(1, &normalsTexture);
    glDeleteTextures(1, &diffuseTexture);
    glDeleteTextures(1, &depthTexture );
	glDeleteFramebuffers(1, &fbo);
	glDeleteRenderbuffers(1, &normalsRT);
	glDeleteRenderbuffers(1, &diffuseRT);
	glDeleteRenderbuffers(1, &depthRT);
	glDeleteLists( icosphere, 1 );
	glDeleteLists( fullscreenQuad, 1 );
}
