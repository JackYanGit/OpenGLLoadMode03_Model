#version 330 core							   
//in vec4 vertexColor;
in vec2 TextCoord;
in vec3 FragPos;
//法向量
in vec3 Normal;

struct Material{
	vec3 ambient; 
	sampler2D diffuse;
	sampler2D specular;
	sampler2D emission;
	float shininess;
};

struct LightDirectional{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;
};

struct LightPoint{
	vec3 pos;
	vec3 color;

	float constant;
	float linear;
	float quadratic;
};


struct LightSpot{
	vec3 pos;
	vec3 color;
	vec3 dirToLight;

	float constant;
	float linear;
	float quadratic;

	float cosPhyInner;
	float cosPhyOutter;
};
uniform LightDirectional lightD;
uniform LightPoint lightP[4];
uniform LightSpot lightS;
uniform Material material;
//uniform sampler2D ourTexture;
//uniform sampler2D ourFace; 	
uniform vec3 ambientColor;
uniform vec3 cameraPos;

out vec4 FragColor;	
//////////////光照模型//////////////////////
vec3 lightingMode(Material material,vec3 lightColor,vec3 lightDir,vec3 uNormal,vec3 dirToCamera, bool glow){
	vec3 resultColor;
	//specular
	vec3 reflectVec =reflect(lightDir,uNormal);
	float specularAmount = pow(max(dot(reflectVec,dirToCamera),0.0f),material.shininess);
	vec3 specular = texture(material.specular,TextCoord).rgb*specularAmount*lightColor;

	//deffuse
	float diffuseAmount = max(dot(lightDir,uNormal),0.0f);
	vec3 diffuse = texture(material.diffuse,TextCoord).rgb* diffuseAmount*lightColor;

	//ambient
	vec3 ambient = texture(material.diffuse,TextCoord).rgb*ambientColor;
	ambient = ambient/2+ambient*(specularAmount+diffuseAmount);
	//vec3 ambient = texture(material.diffuse,TextCoord).rgb*ambientColor*(specularAmount+diffuseAmount);

	//emission
	vec3 emission=vec3(0,0,0);
	if(glow){
		emission = texture(material.emission,TextCoord).rgb;
	}
	return resultColor = ambient+diffuse+specular+emission;
}
//计算平行光
vec3 CalcLightDirectional(LightDirectional light,vec3 uNormal,vec3 dirToCamera){
	return lightingMode(material,light.color,light.dirToLight,uNormal,dirToCamera,true);
}
//计算点光源
vec3 CalcLightPoint(LightPoint light,vec3 uNormal,vec3 dirToCamera){
	vec3 resultColor=vec3(0,0,0);
	//attenuation衰减系数
	float dist = length(light.pos-FragPos);
	float attenuation = 1/(light.constant+light.linear*dist+light.quadratic*dist*dist);
	resultColor = light.color*attenuation;
	vec3 lightDir = normalize(light.pos-FragPos);
	return lightingMode(material,resultColor,lightDir,uNormal,dirToCamera,false);
}
//计算聚光灯
vec3 CalcLightSpot(LightSpot light,vec3 uNormal,vec3 dirToCamera){
	vec3 resultColor=vec3(0,0,0);
	//attenuation衰减系数
	float dist = length(light.pos-FragPos);
	float attenuation = 1/(light.constant+light.linear*dist+light.quadratic*dist*dist);

	float cosTheta = dot(normalize(FragPos - light.pos),-1*light.dirToLight);
	float spotRatio = (cosTheta-light.cosPhyOutter)/(light.cosPhyInner-light.cosPhyOutter);
	if(cosTheta>light.cosPhyInner){
		//inside
		resultColor = light.color*attenuation;
	}else if(cosTheta>light.cosPhyOutter){
		//middle
		resultColor = light.color*spotRatio*attenuation;
	}else{
		//outside
		resultColor = light.color*0.0f;
	}
	vec3 lightDir = normalize(light.pos-FragPos);
	return lightingMode(material,resultColor,lightDir,uNormal,dirToCamera,false);
}

void main()								   
{		
	vec3 finalColor=vec3(0,0,0);
	//1、LightDirection 平行光
	vec3 uNormal=normalize(Normal);
	vec3 dirToCamera=normalize(cameraPos-FragPos);
	finalColor += CalcLightDirectional(lightD,uNormal,dirToCamera);
	//2、LightPoint 点光源
//	for(int i=0;i<4;i++){
//		finalColor += CalcLightPoint(lightP[i],uNormal,dirToCamera);
//	}
	//3、LightSpot 聚光灯
	finalColor += CalcLightSpot(lightS,uNormal,dirToCamera);


	FragColor = vec4(finalColor,1.0f);
}											   