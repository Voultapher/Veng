#version 430
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

 // uniform float time;
uniform sampler2D mySampler;

void main() {

	vec4 textureColor = texture(mySampler, fragmentUV);
    color = textureColor * fragmentColor;
}