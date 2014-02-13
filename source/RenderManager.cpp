#include "RenderManager.h"

#include "IcosphereGenerator.h"

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
bool RenderManager::InvertMatrixGL( const float matrixIn[16], float matrixOut[16] ) const
{
    float inv[16];
    float det;
    int i;

    inv[0] = matrixIn[5] * matrixIn[10] * matrixIn[15] - matrixIn[5] * matrixIn[11] * matrixIn[14] - matrixIn[9] * matrixIn[6] * matrixIn[15] + matrixIn[9] * matrixIn[7] * matrixIn[14] + matrixIn[13] * matrixIn[6] * matrixIn[11] - matrixIn[13] * matrixIn[7] * matrixIn[10];
    inv[4] = -matrixIn[4] * matrixIn[10] * matrixIn[15] + matrixIn[4] * matrixIn[11] * matrixIn[14] + matrixIn[8] * matrixIn[6] * matrixIn[15] - matrixIn[8] * matrixIn[7] * matrixIn[14] - matrixIn[12] * matrixIn[6] * matrixIn[11] + matrixIn[12] * matrixIn[7] * matrixIn[10];
    inv[8] = matrixIn[4] * matrixIn[9] * matrixIn[15] - matrixIn[4] * matrixIn[11] * matrixIn[13] - matrixIn[8] * matrixIn[5] * matrixIn[15] + matrixIn[8] * matrixIn[7] * matrixIn[13] + matrixIn[12] * matrixIn[5] * matrixIn[11] - matrixIn[12] * matrixIn[7] * matrixIn[9];
    inv[12] = -matrixIn[4] * matrixIn[9] * matrixIn[14] + matrixIn[4] * matrixIn[10] * matrixIn[13] + matrixIn[8] * matrixIn[5] * matrixIn[14] - matrixIn[8] * matrixIn[6] * matrixIn[13] - matrixIn[12] * matrixIn[5] * matrixIn[10] + matrixIn[12] * matrixIn[6] * matrixIn[9];
    inv[1] = -matrixIn[1] * matrixIn[10] * matrixIn[15] + matrixIn[1] * matrixIn[11] * matrixIn[14] + matrixIn[9] * matrixIn[2] * matrixIn[15] - matrixIn[9] * matrixIn[3] * matrixIn[14] - matrixIn[13] * matrixIn[2] * matrixIn[11] + matrixIn[13] * matrixIn[3] * matrixIn[10];
    inv[5] = matrixIn[0] * matrixIn[10] * matrixIn[15] - matrixIn[0] * matrixIn[11] * matrixIn[14] - matrixIn[8] * matrixIn[2] * matrixIn[15] + matrixIn[8] * matrixIn[3] * matrixIn[14] + matrixIn[12] * matrixIn[2] * matrixIn[11] - matrixIn[12] * matrixIn[3] * matrixIn[10];
    inv[9] = -matrixIn[0] * matrixIn[9] * matrixIn[15] + matrixIn[0] * matrixIn[11] * matrixIn[13] + matrixIn[8] * matrixIn[1] * matrixIn[15] - matrixIn[8] * matrixIn[3] * matrixIn[13] - matrixIn[12] * matrixIn[1] * matrixIn[11] + matrixIn[12] * matrixIn[3] * matrixIn[9];
    inv[13] = matrixIn[0] * matrixIn[9] * matrixIn[14] - matrixIn[0] * matrixIn[10] * matrixIn[13] - matrixIn[8] * matrixIn[1] * matrixIn[14] + matrixIn[8] * matrixIn[2] * matrixIn[13] + matrixIn[12] * matrixIn[1] * matrixIn[10] - matrixIn[12] * matrixIn[2] * matrixIn[9];
    inv[2] = matrixIn[1] * matrixIn[6] * matrixIn[15] - matrixIn[1] * matrixIn[7] * matrixIn[14] - matrixIn[5] * matrixIn[2] * matrixIn[15] + matrixIn[5] * matrixIn[3] * matrixIn[14] + matrixIn[13] * matrixIn[2] * matrixIn[7] - matrixIn[13] * matrixIn[3] * matrixIn[6];
    inv[6] = -matrixIn[0] * matrixIn[6] * matrixIn[15] + matrixIn[0] * matrixIn[7] * matrixIn[14] + matrixIn[4] * matrixIn[2] * matrixIn[15] - matrixIn[4] * matrixIn[3] * matrixIn[14] - matrixIn[12] * matrixIn[2] * matrixIn[7] + matrixIn[12] * matrixIn[3] * matrixIn[6];
    inv[10] = matrixIn[0] * matrixIn[5] * matrixIn[15] - matrixIn[0] * matrixIn[7] * matrixIn[13] - matrixIn[4]  * matrixIn[1] * matrixIn[15] + matrixIn[4] * matrixIn[3] * matrixIn[13] + matrixIn[12] * matrixIn[1] * matrixIn[7] - matrixIn[12] * matrixIn[3] * matrixIn[5];
    inv[14] = -matrixIn[0] * matrixIn[5] * matrixIn[14] + matrixIn[0] * matrixIn[6] * matrixIn[13] + matrixIn[4] * matrixIn[1] * matrixIn[14] - matrixIn[4] * matrixIn[2] * matrixIn[13] - matrixIn[12] * matrixIn[1] * matrixIn[6] + matrixIn[12] * matrixIn[2] * matrixIn[5];
    inv[3] = -matrixIn[1] * matrixIn[6] * matrixIn[11] + matrixIn[1] * matrixIn[7] * matrixIn[10] + matrixIn[5] * matrixIn[2] * matrixIn[11] - matrixIn[5] * matrixIn[3] * matrixIn[10] - matrixIn[9] * matrixIn[2] * matrixIn[7] + matrixIn[9] * matrixIn[3] * matrixIn[6];
    inv[7] = matrixIn[0] * matrixIn[6] * matrixIn[11] - matrixIn[0] * matrixIn[7] * matrixIn[10] - matrixIn[4] * matrixIn[2] * matrixIn[11] + matrixIn[4] * matrixIn[3] * matrixIn[10] + matrixIn[8] * matrixIn[2] * matrixIn[7] - matrixIn[8] * matrixIn[3] * matrixIn[6];
    inv[11] = -matrixIn[0] * matrixIn[5] * matrixIn[11] + matrixIn[0] * matrixIn[7] * matrixIn[9] + matrixIn[4] * matrixIn[1] * matrixIn[11] - matrixIn[4] * matrixIn[3] * matrixIn[9] - matrixIn[8] * matrixIn[1] * matrixIn[7] + matrixIn[8] * matrixIn[3] * matrixIn[5];
    inv[15] = matrixIn[0] * matrixIn[5] * matrixIn[10] - matrixIn[0] * matrixIn[6] * matrixIn[9] - matrixIn[4] * matrixIn[1] * matrixIn[10] + matrixIn[4] * matrixIn[2] * matrixIn[9] + matrixIn[8] * matrixIn[1] * matrixIn[6] - matrixIn[8] * matrixIn[2] * matrixIn[5];

    det = matrixIn[0] * inv[0] + matrixIn[1] * inv[4] + matrixIn[2] * inv[8] + matrixIn[3] * inv[12];

    if ( det < 0.001f && det > -0.001f )
    {
        return false;
    }

    det = 1.0f / det;

    for ( i = 0; i < 16; i++ )
    {
        matrixOut[i] = inv[i] * det;
    }

    return true;
}

//this code is from GLU's MultiplyMatrices4by4OpenGL_FLOAT(), although the parameters have been renamed
void RenderManager::MultiplyMatricesGL( const float matrixInA[16], const float matrixInB[16], float matrixOut[16] ) const
{
    matrixOut[0] = matrixInA[0] * matrixInB[0] + matrixInA[4] * matrixInB[1] + matrixInA[8] * matrixInB[2] + matrixInA[12] * matrixInB[3];
    matrixOut[4] = matrixInA[0] * matrixInB[4] + matrixInA[4] * matrixInB[5] + matrixInA[8] * matrixInB[6] + matrixInA[12] * matrixInB[7];
    matrixOut[8] = matrixInA[0] * matrixInB[8] + matrixInA[4] * matrixInB[9] + matrixInA[8] * matrixInB[10] + matrixInA[12] * matrixInB[11];
    matrixOut[12] = matrixInA[0] * matrixInB[12] + matrixInA[4] * matrixInB[13] + matrixInA[8] * matrixInB[14] + matrixInA[12] * matrixInB[15];
    matrixOut[1] = matrixInA[1] * matrixInB[0] + matrixInA[5] * matrixInB[1] + matrixInA[9] * matrixInB[2] + matrixInA[13] * matrixInB[3];
    matrixOut[5] = matrixInA[1] * matrixInB[4] + matrixInA[5] * matrixInB[5] + matrixInA[9] * matrixInB[6] + matrixInA[13] * matrixInB[7];
    matrixOut[9] = matrixInA[1] * matrixInB[8] + matrixInA[5] * matrixInB[9] + matrixInA[9] * matrixInB[10] + matrixInA[13] * matrixInB[11];
    matrixOut[13] = matrixInA[1] * matrixInB[12] + matrixInA[5] * matrixInB[13] + matrixInA[9] * matrixInB[14] + matrixInA[13] * matrixInB[15];
    matrixOut[2] = matrixInA[2] * matrixInB[0] + matrixInA[6] * matrixInB[1] + matrixInA[10] * matrixInB[2] + matrixInA[14] * matrixInB[3];
    matrixOut[6] = matrixInA[2] * matrixInB[4] + matrixInA[6] * matrixInB[5] + matrixInA[10] * matrixInB[6] + matrixInA[14] * matrixInB[7];
    matrixOut[10] = matrixInA[2] * matrixInB[8] + matrixInA[6] * matrixInB[9] + matrixInA[10] * matrixInB[10] + matrixInA[14] * matrixInB[11];
    matrixOut[14] = matrixInA[2] * matrixInB[12] + matrixInA[6] * matrixInB[13] + matrixInA[10] * matrixInB[14] + matrixInA[14] * matrixInB[15];
    matrixOut[3] = matrixInA[3] * matrixInB[0] + matrixInA[7] * matrixInB[1] + matrixInA[11] * matrixInB[2] + matrixInA[15] * matrixInB[3];
    matrixOut[7] = matrixInA[3] * matrixInB[4] + matrixInA[7] * matrixInB[5] + matrixInA[11] * matrixInB[6] + matrixInA[15] * matrixInB[7];
    matrixOut[11] = matrixInA[3] * matrixInB[8] + matrixInA[7] * matrixInB[9] + matrixInA[11] * matrixInB[10] + matrixInA[15] * matrixInB[11];
    matrixOut[15] = matrixInA[3] * matrixInB[12] + matrixInA[7] * matrixInB[13] + matrixInA[11] * matrixInB[14] + matrixInA[15] * matrixInB[15];
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
    gluPerspective( (float) engineCfg.GetActiveHeight() / (float) engineCfg.GetActiveWidth() * (float) engineCfg.GetFOV(), (float) engineCfg.GetActiveWidth() / (float) engineCfg.GetActiveHeight(), 1.0f, 5000.0f );
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
    glUniform1i( surfaceTextureID, 0 );

    glPushMatrix();
        gameSim.RenderLit( engineCfg.GetFOV(), (float) engineCfg.GetActiveHeight() / (float) engineCfg.GetActiveWidth() * (float) engineCfg.GetFOV() );
        int viewportParams[4];
        float modelViewParams[16];
        float projectionParams[16];
        float perspectiveMatrix[16];

        glGetIntegerv( GL_VIEWPORT, viewportParams );
        glGetFloatv( GL_MODELVIEW_MATRIX, modelViewParams );
        glGetFloatv( GL_PROJECTION_MATRIX, projectionParams );
        MultiplyMatricesGL( projectionParams, modelViewParams, perspectiveMatrix );
        InvertMatrixGL( perspectiveMatrix, perspectiveMatrix );

    glPopMatrix();

    StopRenderToFBO();

    //render depth buffer onto a fullscreen quad
    glClear( GL_DEPTH_BUFFER_BIT );
    SetToOrthogonalProjection( engineCfg );
    glUseProgram( depthTransferShader.GetProgramHandler() );
    glActiveTexture( GL_TEXTURE0 );
	glBindTexture( GL_TEXTURE_2D, depthTexture );
	glUniform1i( depthID, 0 );
    glCallList( fullscreenQuad );

    glDepthMask( GL_FALSE ); //disable writing to the depth buffer
    glDisable( GL_DEPTH_TEST );

    //send all the textures, the viewport parameters and the perspective matrix to the deferred rendering shader so we don't have to do it for every light
    glUseProgram( deferredRenderingShader.GetProgramHandler() );
	glUniform1i( normalsID, 0 );
	glUniform1i( diffuseID, 1 );
	glUniform1i( depthID, 2 );
    glUniform4iv( viewportParamsID, 4, viewportParams );
    glUniformMatrix4fv( perspectiveMatrixID, 16, false, perspectiveMatrix );
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
        glUniform3f( lightPositionID, lightIt.GetPosition().GetX(), lightIt.GetPosition().GetY(), lightIt.GetPosition().GetZ() );
        glUniform3f( lightColorID, lightIt.GetColor().GetX(), lightIt.GetColor().GetY(), lightIt.GetColor().GetZ() );
        glUniform1f( lightLinearAttenuationID, lightIt.GetLinearAttenuation() );
        glUniform1f( lightQuadraticAttenuationID, lightIt.GetQuadraticAttenuation() );

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
    gameSim.RenderLit( engineCfg.GetFOV(), engineCfg.GetActiveHeight() / engineCfg.GetActiveWidth() * engineCfg.GetFOV() );
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
	surfaceTextureID = glGetUniformLocation( deferredShadingShader.GetProgramHandler(), "surfaceTexture" );

	// Get the handles from the shader
	normalsID = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "normalsTexture" );
	diffuseID = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "diffuseTexture" );
	depthID = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "depthTexture" );

	viewportParamsID = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "viewportParams" );
	perspectiveMatrixID = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "perspectiveMatrix" );

	lightPositionID = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "lightPosition" );
	lightColorID = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "lightColor" );
	lightLinearAttenuationID = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "lightLinearAttenuation" );
    lightQuadraticAttenuationID = glGetUniformLocation( deferredRenderingShader.GetProgramHandler(), "lightQuadraticAttenuation" );


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
