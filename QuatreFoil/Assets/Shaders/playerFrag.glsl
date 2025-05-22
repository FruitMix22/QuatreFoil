#version 330 core
out vec4 FragColor;

uniform sampler2D inputTexture;
uniform vec2 uvOffset;
uniform vec2 uvScale;

in vec2 TexCoord;

void main()
{
    vec2 sheetUV = uvOffset + TexCoord * uvScale;
    FragColor = texture(inputTexture, sheetUV);
} 