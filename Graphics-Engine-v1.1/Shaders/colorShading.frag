#version 430
//The fragment shader operates on each pixel in a given polygon

in vec2 fragmentPosition;
in vec4 fragmentColor;
in vec2 fragmentUV;

out vec4 color;

uniform float time;
uniform sampler2D mySampler;

void main() {

	vec4 textureColor = texture(mySampler, fragmentUV);
	
    color = textureColor * vec4(fragmentColor.r * (cos(fragmentPosition.x * 0.3 +time) + 1.0) * 0.5,
				 fragmentColor.g * (cos(fragmentPosition.x * 0.1 +time) + 1.0) * 0.5,
				 fragmentColor.b * (sin(fragmentPosition.x * 0.1 +time) + 1.0) * 0.5, fragmentColor.a);
}