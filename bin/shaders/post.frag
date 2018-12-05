// post-processing fragment shader
#version 410

in vec2 vTexCoord;

uniform int hasBlur;
uniform float blurAmount;
uniform int hasDistort;
uniform float distortAmount;
uniform sampler2D colourTexture;

out vec4 FragColour;

vec4 finalTexture;


// just output the colour unchanged
vec4 Default(vec2 texCoord) 
{
	return texture( colourTexture, texCoord );
}


// simple box blur 
vec4 BoxBlur(vec2 texCoord) 
{    

	vec2 texel = blurAmount / textureSize(colourTexture, 0);  
 
	// 9-tap box kernel  
	vec4 colour = texture(colourTexture, texCoord);   
	colour += texture(colourTexture, texCoord + texel * vec2(-1,1));   
	colour += texture(colourTexture, texCoord + texel * vec2(-1,0));   
	colour += texture(colourTexture, texCoord + texel * vec2(-1,-1));   
	colour += texture(colourTexture, texCoord + texel * vec2(0,1));   
	colour += texture(colourTexture, texCoord + texel * vec2(0,-1));  
	colour += texture(colourTexture, texCoord + texel * vec2(1,1));   
	colour += texture(colourTexture, texCoord + texel * vec2(1,0));  
	colour += texture(colourTexture, texCoord + texel * vec2(1,-1)); 
	
	return colour / 9; 
 }

 vec4 Distort(vec2 texCoord) 
 { 
 
	vec2 mid = vec2(0.5f); 
	
	float distanceFromCentre = distance(texCoord, mid);  
	vec2 normalizedCoord = normalize(texCoord - mid);  
	float bias = distanceFromCentre + sin(distanceFromCentre * distortAmount) * 0.05f; 
	
	vec2 newCoord = mid + bias * normalizedCoord;  
	return texture(colourTexture, newCoord); 
 }

void main() 
{
	// calculate texel size
	vec2 texSize = textureSize( colourTexture, 0 );
	vec2 texelSize = 1.0f / texSize;
	
	// adjust texture coordinate
	vec2 scale = (texSize - texelSize) / texSize;
	vec2 texCoord = vTexCoord / scale + texelSize * 0.5f;
	

	finalTexture = Default(texCoord);
	
	// sample post effect
	if(hasDistort > 0)
	{
		finalTexture = Distort(texCoord);
	}


	if(hasBlur > 0)
	{
		finalTexture *= BoxBlur(texCoord);
	}

	FragColour = finalTexture;

}