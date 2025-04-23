#version 330 core
out vec4 FragColor;

uniform vec4 colour;
uniform sampler2D inputTexture;

in vec2 TexCoord;

void main()
{
    FragColor = texture(inputTexture, TexCoord) * colour;
} 