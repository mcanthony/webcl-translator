#version 100
attribute vec3 position;
attribute vec2 texcoord;

varying vec3 pos;
varying vec2 uv;

uniform vec2 screenSize;

void main()
{
    gl_Position = vec4(position,1.0);
    pos = position;
    uv = texcoord;
}
