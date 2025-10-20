#version 300 es
precision mediump float;

layout(location = 0) in vec3 vertexPosition_modelspace;
layout(location = 1) in vec3 vertexColor;

out vec3 fragmentColor;

uniform mat4 MVP;

void main() {
    gl_PointSize = 19.0f;
	gl_Position =  MVP * vec4(vertexPosition_modelspace,1);
	fragmentColor = vertexColor;
}

