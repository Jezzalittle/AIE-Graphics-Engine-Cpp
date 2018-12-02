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

#define NR_LIGHTS 1
uniform Light lights[NR_LIGHTS];
uniform int  HasTextures;

const float e = 2.71828182845904523536028747135;
const float pi = 3.1415926535897932384626433832;

//uniform float roughness;
const float roughness  = 0.1f;

//uniform float refelctionCoefficient 
const float refelctionCoefficient = 0.2f;

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
 

vec3 CalcDirLight(Light light, vec3 a_normal, vec3 a_viewVector)
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
		float R2 = roughness * roughness;

		//lambertTerm = max( 0, min( 1, dot( a_normalNormalised, lightDir)));	
		
		float NdL = max(0.0f, dot(a_normal, lightDir));
		float NdE = max(0.0f, dot(a_normal, a_viewVector));
		

		//oren-nayar diffuse term
		float A = 1.0f - 0.5f * R2 / (R2 + 0.33f);
		float B = 0.45f * R2 / (R2 + 0.09f);


		//CX = max(0,cos(r,i))
		vec3 lightProjected = normalize(lightDir - a_normal * NdL);
		vec3 viewProjected = normalize(a_viewVector - a_normal * NdE);
		float CX = max(0.0f, dot(lightProjected, viewProjected));

		//DX = sin(alpha) * tan(beta)
		float alpha = sin(max(acos(NdE), acos(NdL)));
		float beta = tan(min(acos(NdE), acos(NdL)));
		float DX = alpha * beta;

		lambertTerm = NdL * (A + B * CX * DX);
	
		texDiffuse = texture( diffuseTexture, vTexCoord ).rgb;
		texSpecular = texture( specularTexture, vTexCoord ).rgb;

		reflectionVector = reflect( lightDir, a_normal);
	
		
		//specularTerm = pow(max(0, dot(reflectionVector, a_viewVector)), specularPower);
		

	float NdotL = max(0, dot(a_normal, lightDir));
	if (NdotL > 0) 
	{

		//Cook-Torrance Specular Term

		vec3 H = normalize(lightDir + a_viewVector);
		float NdotH = max(0, dot(a_normal, H));
		float NdotV = max(0, dot(a_normal, a_viewVector));
		float VdotH = max(0, dot(lightDir, H));

		// Fresnel reflectance
		float F = pow(1.0 - VdotH, 5.0);
		F *= (1.0 - 0.8f);
		F += 0.8f;

		// Microfacet distribution by Beckmann
		float m_squared = roughness * roughness;
		float r1 = 1.0 / (4.0 * m_squared * pow(NdotH, 4.0));
		float r2 = (NdotH * NdotH - 1.0) / (m_squared * NdotH * NdotH);
		float D = r1 * exp(r2);

		// Geometric shadowing
		float two_NdotH = 2.0 * NdotH;
		float g1 = (two_NdotH * NdotV) / VdotH;
		float g2 = (two_NdotH * NdotL) / VdotH;
		float G = min(1.0, min(g1, g2));

		specularTerm = (F * D * G) / (pi * NdotL * NdotV);


	}

//		vec3 H = normalize( lightDir + a_normalNormalised ); // light and view half/avrage vector
//		float NdH = max(dot(a_normalNormalised, H), 0.0f);
//		float NdH2 = NdH * NdH;
//
//		//Beckmann Distibition (how the light is distributed across a surface
//		float exponent = -(1 - NdH2) / (NdH2 * R2);
//		float D = pow(e,exponent) / (R2 * NdH2 * NdH2);
//		
//		//Schlick's Approximation of Fresnel (what happens to light on the edge of different materials)
//		float F = refelctionCoefficient + (1 - refelctionCoefficient) * pow(1 - NdE, 5);
//		
//		//Geometric Attenuation Factor (simulates shadowing caused by the microfacets(imperfections) on a surface
//		float X = 2.0f * NdH / dot(a_viewVector, H);
//		float G = min(1, min(X * NdE, X * NdL));
//
//		//Claculate Cook-Torrance
//		specularTerm = max((D*G*F) / (NdE * pi), 0.0f);

		diffuse = light.m_diffuse * Kd * texDiffuse * NdotL * lambertTerm;
		ambient = light.m_ambient * Ka;
		specular = light.m_specular  * Ks * NdotL * (0.2f + specularTerm * (1.0f - 0.2f));
	}
	
	
	else//Has no textures
	{
		lambertTerm = max( 0, min( 1, dot( a_normal, lightDir)));	

		reflectionVector = reflect( lightDir, a_normal);
	
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
	  

	  vec3 texNormal = texture(normalTexture, vTexCoord).rgb;   
	  
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