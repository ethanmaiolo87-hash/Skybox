#version 450
#extension GL_arb_separate_shader_objects : enable

layout(location = 0) out vec4 fragColor;
layout(location = 0) in vec3 uvwCoord;

uniform samplerCube skybox;
void main(){
fragColor = texture(skybox,uvwCoord);


}
