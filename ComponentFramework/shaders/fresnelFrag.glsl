#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;

layout(location = 0) in vec3 uvwReflect;
layout(location = 1) in vec3 uvwRefract;
layout(location = 2) in float ratio;

uniform samplerCube skybox;

void main() {
    vec4 reflectColour = texture(skybox, uvwReflect);
    vec4 refractColour = texture(skybox, uvwRefract);
    fragColor = mix(refractColour, reflectColour, ratio);
}