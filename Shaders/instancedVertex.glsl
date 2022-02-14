#version 330 core
layout(std140) uniform Transforms
{
  mat4 modelMatrix[10];
};

uniform mat4 viewMatrix;
uniform mat4 projMatrix;
uniform vec4 plane;

in vec3 position;
in vec4 colour;
in vec3 normal;
in vec4 tangent;
in vec2 texCoord;

out Vertex {
 vec4 colour;
 vec2 texCoord;
 vec3 normal;
 vec3 tangent; 
 vec3 binormal;
 vec3 worldPos;
 vec3 position;
} OUT;

void main ( void ) {
 mat4 trans;
 if (gl_InstanceID != 0) {
   trans = modelMatrix[gl_InstanceID];
 }
 
 vec4 worldPos = ( trans * vec4 ( position,1));
 gl_ClipDistance[0] = dot(worldPos,plane);

 OUT.colour = colour;
 OUT.texCoord = texCoord;

 mat3 normalMatrix = transpose ( inverse ( mat3 ( trans )));

 vec3 wNormal = normalize ( normalMatrix * normalize ( normal ));
 vec3 wTangent = normalize ( normalMatrix * normalize ( tangent.xyz ));

 OUT.normal = wNormal;
 OUT.tangent = wTangent;
 OUT.binormal = cross ( wTangent , wNormal ) * tangent.w;

 OUT.worldPos = worldPos.xyz;

 gl_Position = ( projMatrix * viewMatrix ) * worldPos;
}
