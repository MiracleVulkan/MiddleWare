#version 330 core
in vec2 TexCoords;

out vec4 color;

uniform sampler2D texture1;

void main()
{             
    vec4 textcolor = texture(texture1, TexCoords);
	if(textcolor.a < 0.1)
	discard;
	color = textcolor;
}