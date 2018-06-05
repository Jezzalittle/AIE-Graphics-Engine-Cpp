// classic Phong fragment shader 
#version 410
 in vec4 vPosition;
 in vec3 vNormal; 
 in vec3 vTangent;
 in vec3 vBiTangent;
 in vec2 vTexCoord; 
  
  // ambient light colour 
 uniform vec3 Ia;
 
 // diffuse light colour
 uniform vec3 Id; 
 
  // specular light colour 
 uniform vec3 Is; 

 uniform vec3 LightDirection;
 

 
  // ambient material colour
 uniform vec3 Ka; 
 
  // diffuse material colour 
 uniform vec3 Kd; 
 
  // specular material colour 
 uniform vec3 Ks; 
 
  // material specular power 
 uniform float specularPower; 
 uniform vec3 cameraPosition; 
 uniform sampler2D diffuseTexture;
 uniform sampler2D specularTexture;
 uniform sampler2D normalTexture;

  out vec4 FragColour; 
 
  void main() 
  {     
  // ensure normal and light direction are normalised  
  vec3 N = normalize(vNormal);  
  vec3 T = normalize(vTangent); 
  vec3 B = normalize(vBiTangent); 
  vec3 L = normalize(LightDirection);
  
  mat3 TBN = mat3(T,B,N);       
  // calculate lambert term (negate light direction)  
  
  float lambertTerm = max( 0, min( 1, dot( N, -L ) ) );  
  
   // output lambert as grayscale   
   //FragColour = vec4( lambertTerm, lambertTerm, lambertTerm, 1 );  
   vec3 texDiffuse = texture(diffuseTexture, vTexCoord).rgb;  
   vec3 texSpecular = texture(specularTexture, vTexCoord).rgb; 
   vec3 texNormal = texture( normalTexture, vTexCoord ).rgb;   
   
   N = TBN * (texNormal * 2 - 1);    
   
   // calculate view vector and reflection vector   
   vec3 V = normalize(cameraPosition - vPosition.xyz);  
   vec3 R = reflect( L, N );   
   
   // calculate specular term   
   float specularTerm = pow( max( 0, dot( R, V ) ), specularPower );  
   
   // calculate each colour prop.    
   vec3 ambient = Ia * Ka;    
   vec3 diffuse = Id * Kd * texDiffuse * lambertTerm;  
   vec3 specular = Is * Ks * texSpecular * specularTerm;   
   
   // output final colour    
   FragColour = vec4( ambient + diffuse + specular, 1 ); 
   
   }