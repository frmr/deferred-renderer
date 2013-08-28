varying vec3 normal;

void main( void )
{
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
	normal = normalize( gl_NormalMatrix * gl_Normal );

    gl_FrontColor = vec4(1.0, 1.0, 1.0, 1.0);
}
