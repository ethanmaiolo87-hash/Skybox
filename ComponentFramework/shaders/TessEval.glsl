#version 450
#extension GL_arb_separate_shader_objects : enable

layout (triangles, equal_spacing, ccw) in;

uniform mat4 projectionMatrix;
uniform mat4 viewMatrix;
uniform mat4 modelMatrix;
uniform vec3 lightPos;
layout( binding = 0 )uniform sampler2D textureData;

in vec2 uvCoordFromCtrl[];
in vec3 normalFromCtrl[];
 uniform float tesslevel;
out vec2 uvCoordFromEval;
out vec3 normalFromEval;
out vec3 lightDir;
out vec3 eyeDir;
out float fogAmount;
vec2 interpolateVec2(vec2 v0, vec2 v1, vec2 v2) {
    return gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

vec3 interpolateVec3(vec3 v0, vec3 v1, vec3 v2) {
    return  gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

vec4 interpolateVec4(vec4 v0, vec4 v1, vec4 v2) {
    return  gl_TessCoord.x * v0 + gl_TessCoord.y * v1 + gl_TessCoord.z * v2;
}

void main() {
   
   
    uvCoordFromEval = interpolateVec2(uvCoordFromCtrl[0], uvCoordFromCtrl[1], uvCoordFromCtrl[2]);
    normalFromEval =  interpolateVec3(normalFromCtrl[0], normalFromCtrl[1], normalFromCtrl[2]);
    /// Interpolate position across the triangle
    vec4 position = interpolateVec4(gl_in[0].gl_Position, gl_in[1].gl_Position, gl_in[2].gl_Position);
   vec3 vertPos = vec3(viewMatrix * modelMatrix * position);
   lightDir = normalize(lightPos - vertPos);
    vec3 vertDir = normalize(vertPos);
    eyeDir = -vertDir;
   vec4 height = texture(textureData,uvCoordFromEval);

  float density = 0.20;
  float dis = length(vertPos);
  fogAmount = 1.0  - exp(-dis * density);


    position.z = height.r;
    gl_Position =  projectionMatrix * viewMatrix * modelMatrix * position ;
}
