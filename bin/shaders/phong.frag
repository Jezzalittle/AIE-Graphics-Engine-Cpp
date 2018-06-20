// classic Phong fragment shader 
#version 410
 in vec4 vPosition;
 in vec3 vNormal; 
 in vec3 vTangent;
 in vec3 vBiTangent;
 in vec2 vTexCoord; 
  


struct Light
{
	vec3 m_direction;
	vec3 m_ambient;
	vec3 m_diffuse;
	vec3 m_specular;	
};
#define NR_LIGHTS 2
uniform Light lights[NR_LIGHTS];
uniform int  HasTextures;

 
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
 

vec3 CalcDirLight(Light light, vec3 a_normalNormalised, vec3 a_viewVector)
{
	vec3 lightDir = normalize(light.m_direction);
	
	float lambertTerm;
	vec3 diffuse; 
	vec3 ambient; 
	vec3 specular;
	float specularTerm;
	vec3 reflectionVector;
	vec3 texDiffuse; 
	vec3 texSpecular;
	
	if(HasTextures == 1)//Has textures
	{
		lambertTerm = max( 0, min( 1, dot( a_normalNormalised, lightDir)));	
	
		texDiffuse = texture( diffuseTexture, vTexCoord ).rgb;
		texSpecular = texture( specularTexture, vTexCoord ).rgb;

		reflectionVector = reflect( lightDir, a_normalNormalised);
	
		specularTerm = pow(max(0, dot(reflectionVector, a_viewVector)), specularPower);
	
		diffuse = light.m_diffuse * Kd * texDiffuse * lambertTerm;
		ambient = light.m_ambient * Ka;
		specular = light.m_specular * Ks * texSpecular * specularTerm;
	}
	
	
	else//Has no textures
	{
		lambertTerm = max( 0, min( 1, dot( a_normalNormalised, lightDir)));	

		reflectionVector = reflect( lightDir, a_normalNormalised);
	
		specularTerm = pow(max(0, dot(reflectionVector, a_viewVector)), specularPower);
	
		diffuse = light.m_diffuse * Kd * lambertTerm;
		ambient = light.m_ambient * Ka;
		specular = light.m_specular * Ks * specularTerm;
	}
	return(diffuse + ambient + specular);
}



  void main() 
  {     
	  // ensure normal and light direction are normalised  
	  vec3 N = normalize(vNormal);  
	  vec3 T = normalize(vTangent); 
	  vec3 B = normalize(vBiTangent); 
	  
	  mat3 TBN = mat3(T,B,N);       
	  

	  vec3 texNormal = texture( normalTexture, vTexCoord ).rgb;   
	  
	  if(HasTextures == 1)
	  {
		N = TBN * (texNormal * 2 - 1);    
	  }

	   
	  // calculate view vector and reflection vector   
	  vec3 V = normalize(cameraPosition - vPosition.xyz);  
	   
	  vec3 result = vec3(0,0,0);
	  
	  for(int i = 0; i < NR_LIGHTS; i++)
	  {
		 result += CalcDirLight(lights[i], N, V);
	  }
 	   
	   // output final colour    
	   FragColour = vec4(result,1); //FragColour = vec4( ambient + diffuse + specular, 1 ); 
   
   }