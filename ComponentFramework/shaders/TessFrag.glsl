#version 450
#extension GL_arb_separate_shader_objects : enable

in vec2 uvCoordFromEval;
in vec3 normalFromEval;
in vec3 lightDir;
in vec3 eyeDir;
out vec4 fragColor;
in float fogAmount;
layout( binding = 1 ) uniform sampler2D normaltexture;
layout( binding = 2 ) uniform sampler2D diffusetexture;


void main() {
 vec4 ks = vec4(0.3, 0.3, 0.3, 0.0);
	vec4 kd = vec4(130.0, 178.0, 255.0, 0.0) / 255.0;
	vec4 ka = 0.1 * kd;
	vec4 textureColor = texture(diffusetexture, uvCoordFromEval);
	vec4 normalFromTexture = texture(normaltexture, uvCoordFromEval);
	vec3 vertNormal = normalFromTexture.xyz * 2.0 - 1.0;
	float diff = max(dot(vertNormal, lightDir), 0.0);
	vec3 reflection = normalize(reflect(-lightDir, vertNormal));
	float spec = max(dot(eyeDir, reflection), 0.0);
	spec = pow(spec,14.0);
		

vec4 fogColor = vec4(0.2, 0.3 , 0.5, 0.0);
    vec4 FC =  (ka + (diff * kd) + (spec * ks)) * textureColor;	
	fragColor =  mix(FC, fogColor, fogAmount);
	
    //fragColor = vec4(1.0,1.0,1.0,1.0);
}