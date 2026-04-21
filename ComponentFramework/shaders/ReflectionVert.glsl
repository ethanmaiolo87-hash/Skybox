#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 inVertex;
layout(location = 1) in vec3 inNormal;
layout(location = 2) in vec2 inUVCoord;

layout(location = 0) uniform mat4 modelMatrix;
layout(location = 1) uniform mat4 viewMatrix;
layout(location = 2) uniform mat4 projectionMatrix;

layout(location = 0) out vec3 uvwCoord;

  


void main() {
    mat3 normalMatrix = mat3(transpose(inverse(modelMatrix)));
   vec3 vertNormal = normalize(normalMatrix * inNormal); 
    vec3 vertPos = vec3( modelMatrix * inVertex);
    vec3 vertDir = normalize(vertPos);
    uvwCoord = reflect(vertDir, vertNormal);
   // uvwCoord = refract(-vertDir, -vertNormal, 1.0);

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * inVertex;
    
}