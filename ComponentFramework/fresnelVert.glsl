#version 450
#extension GL_ARB_separate_shader_objects : enable

layout(location = 0) in vec4 vVertex;
layout(location = 1) in vec3 vNormal;

uniform mat4 modelMatrix;
uniform mat4 viewMatrix;
uniform mat4 projectionMatrix;

layout(location = 0) out vec3 uvwReflect;
layout(location = 1) out vec3 uvwRefract;
layout(location = 2) out float ratio;


void main() {
    vec3 vertNormal = normalize((mat3(transpose(inverse(modelMatrix))) * vNormal));
    vec3 vertPos = vec3(viewMatrix * modelMatrix * vVertex);
    vec3 vertDir = normalize(vertPos);

    float refractiveRatio = 0.671;

    uvwReflect = reflect(vertDir, vertNormal);
    uvwRefract = refract(vertDir, vertNormal, refractiveRatio);

    //find the critical angle
    float critAngle = asin(refractiveRatio);
    //find the angle of incidence
    float iAngle = dot(vertDir,vertNormal);

    float cosTheta = clamp(dot(-vertDir, vertNormal), 0.0, 1.0);
    float R0 = pow((1.0 - refractiveRatio) / (1.0 + refractiveRatio), 2.0);
    ratio = R0 + (1.0 - R0) * pow(1.0 - cosTheta, 5.0);

    gl_Position = projectionMatrix * viewMatrix * modelMatrix * vVertex;

}