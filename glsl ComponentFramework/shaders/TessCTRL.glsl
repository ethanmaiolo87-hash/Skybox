#version 400 core
layout(vertices = 3) out;

uniform float TessLevel; // declare the uniform

void main() {
    if (gl_InvocationID == 0) {
        // use the uniform to set tessellation levels
        gl_TessLevelOuter[0] = TessLevel;
        gl_TessLevelOuter[1] = TessLevel;
        gl_TessLevelOuter[2] = TessLevel;
        gl_TessLevelInner[0] = TessLevel;
    }
    // pass positions through
    gl_out[gl_InvocationID].gl_Position = gl_in[gl_InvocationID].gl_Position;
}