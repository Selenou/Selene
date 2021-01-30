#version 330 core
			
layout(location = 0) out vec4 color;

in vec2 v_TexCoord;
in vec2 v_TileSize;
in vec2 v_TextureUV;

uniform sampler2D u_Texture;

void main()
{
	float x = v_TextureUV.x + (fract(v_TexCoord.x) * v_TileSize.x);		
	float y = v_TextureUV.y + (fract(v_TexCoord.y) * v_TileSize.y);				

	color = texture(u_Texture, vec2(x,y));
}