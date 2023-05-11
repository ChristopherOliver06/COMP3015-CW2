#version 460

in vec4 Position;
in vec3 Normal;
in vec2 TexCoord;
in vec3 Vec;
layout (binding = 1) uniform samplerCube SkyBoxTexture;
layout (binding = 2) uniform sampler2D Noisetex;

layout (location = 0) out vec4 FragColor;
layout (binding = 0) uniform sampler2D Tex1;

uniform float noiseScale = 1.0;
uniform float noisePower = 0.1;

uniform vec4 SkyColour = vec4(0.3, 0.3, 0.9, 1.0);
uniform vec4 CloudColour = vec4(1.0, 1.0, 1.0, 1.0);

uniform struct LightInfo{
	vec4 Position;
	vec3 La; //ambient
	vec3 Ld; //diffuse
	vec3 Ls; //specular
} Lights[3];

uniform struct MaterialInfo{
	vec3 Ka; //ambient
	vec3 Kd; //diffuse
	vec3 Ks; //specular
	float Shininess; //shininess factor
} Material;

uniform struct FogInfo{
float MaxDistance;
float MinDistance;
vec3 Colour;
} fog;

vec3 phong( int light,vec3 n,vec4 pos)
{
	vec3 texcolour= texture(Tex1, TexCoord).rgb;
	vec3 ambient=Lights[light].La*texcolour;

	vec3 s=normalize(vec3(Lights[light].Position-pos));
	float sDotN=max(dot(s,n), 0.0);
	vec3 diffuse=Lights[light].Ld*Material.Kd*sDotN;
	vec3 spec=vec3(0.0);
	if (sDotN>0.0)
	{
		vec3 v=normalize(-pos.xyz);
		vec3 r=reflect(-s,n);
		spec=Lights[light].Ls*Material.Ks*pow(max(dot(r,v),0.0),Material.Shininess);
	}
	return ambient+diffuse+spec;
}

void main() {

	//vec3 noiseVec = normalize(Vec) * noiseScale;
	//float noiseVal = texture(Noisetex, noiseVec.xy).r;
	//noiseVal = (noiseVal - 0.5) * 2.0;


	// Calculate the fog in the scene
	//float Distance = abs(Position.z);
	//float fogDensity = (fog.MaxDistance - Distance)/(fog.MaxDistance - fog.MinDistance);
	//fogDensity = clamp(fogDensity, 0.0, 1.0);

	//vec3 Colour=vec3(0.0);

	//for (int i=0; i<3; i++)
	//	Colour+=phong(i,Normal,Position);
    //vec3 texColour = texture(SkyBoxTexture, normalize(Vec)).rgb;
    //FragColor = vec4( Colour + texColour, 1.0 );
	//Colour = mix(fog.Colour, Colour, fogDensity);

	
	//texColour += noiseVal * noisePower; 

	vec3 Colour = vec3(0.0);
    for (int i = 0; i < 3; i++)
        Colour+=phong(i, Normal, Position);

    //
    vec3 noiseVec = normalize(Vec) * noiseScale;
    float noiseVal = texture(Noisetex, noiseVec.xy).r;
    noiseVal = (noiseVal - 0.5) * 2.0;

    if (noisePower > 0.0) {
	
		vec3 tex = texture(SkyBoxTexture, normalize(Vec)).rgb;
		tex += noiseVal * noisePower;
		FragColor = vec4(Colour + tex, 1.0);

        //vec3 noiseColor = vec3(0.5, 0.5, 0.5) + noiseVal * noisePower;
        //vec3 finalColor = mix(SkyColour.rgb, CloudColour.rgb, noiseColor);
        //FragColor = vec4(Colour + finalColor, 1.0);
    } else {
	
        FragColor = vec4(Colour, 1.0);
    }

}


