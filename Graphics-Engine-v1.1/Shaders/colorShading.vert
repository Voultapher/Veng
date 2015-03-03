#version 430
//The vertex shader operates on each vertex

//input data from the VBO. Each vertex is 2 floats
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 P;

void main() {
    gl_Position.xy = (P * vec4(vertexPosition, 0.0, 1.0)).xy;
    gl_Position.z = 0.0;
    
    //Indicate that the coordinates are normalized
    gl_Position.w = 1.0;
	
	fragmentColor = vertexColor;
	fragmentPosition = vertexPosition;
	fragmentUV = vertexUV;
	fragmentUV.y = 1-fragmentUV.y;
}