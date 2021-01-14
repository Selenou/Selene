#version 330 core
			
layout(location = 0) in vec3 a_Position;

uniform mat4 u_ViewProjection;

out vec3 v_TexCoord;

void main()
{
	v_TexCoord = vec3(a_Position.xy, -a_Position.z); // flip z because cubermap in  opengl uses RenderMap LH coordinates
	gl_Position = u_ViewProjection * vec4(a_Position, 1.0);
}