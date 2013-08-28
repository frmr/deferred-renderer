varying vec3 normals;

void main( void )
{
	// Move the normals back from the camera space to the world space
	mat3 worldRotationInverse = transpose(mat3(gl_ModelViewMatrix));
	
	gl_Position		= gl_ModelViewProjectionMatrix * gl_Vertex;
	normals			= normalize(worldRotationInverse * gl_NormalMatrix * gl_Normal);
	gl_TexCoord[0]	= gl_MultiTexCoord0;
    gl_FrontColor	= vec4(1.0, 1.0, 1.0, 1.0);
}