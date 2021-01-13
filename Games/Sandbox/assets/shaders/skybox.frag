#version 330 core
			
layout(location = 0) out vec4 color;

in vec3 v_TexCoord;

uniform samplerCube u_Texture;

void main()
{
	color = texture(u_Texture, v_TexCoord);
}