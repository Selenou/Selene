#version 330 core

layout(location = 0) in vec3 a_Position;
layout(location = 1) in vec2 a_TexCoord;
layout(location = 2) in uint a_CustomFlags;

uniform mat4 u_ViewProjection;
uniform mat4 u_Model;
uniform sampler2D u_Texture;

out vec3 v_TexCoord;

void main()
{
	int blockType = int(a_CustomFlags);
	v_TexCoord = vec3(a_TexCoord,blockType-1);
	gl_Position = u_ViewProjection * u_Model * vec4(a_Position, 1.0);	
}