#define N 7
#define N_HALF 3

vec2 getIntersection(sampler2D normalMap, sampler2D heightMap, vec2 uvCoord, vec2 texelSize){
	vec3 normal = texture2D(normalMap, uvCoord).rgb;
	float P_Y = texture2D(heightMap, uvCoord).r, k = P_Y * normal.g * 64.;
	return vec2(normal.r * k * texelSize.r, normal.b * k * texelSize.g);
}

uniform sampler2D tData, tNormalMap;
uniform vec2 texelSize, P_G;
varying vec2 vUv;

void main(){
	vec2 P_C = vUv, P_G = vec2(.5,.5);
	float intensity[N];
	for(int ii = 0; ii < N; ii++){
		intensity[ii]=0.;
	}

	float P_Gy[N];

	for(int iii = -N_HALF; iii <= N_HALF; iii++){
		P_Gy[iii + N_HALF] = P_G.g + float(iii) * texelSize.g;
	}
	for(int i = 0; i < N; i++){
		vec2 pN = P_C + float(i - N_HALF) * texelSize, intersection = getIntersection(tNormalMap, tData, pN, texelSize);
		float ax = max(0., 1.-abs(P_G.r - intersection.r));
		for(int j = 0; j < N; j++){
			float ay = max( 0., 1. - abs(P_Gy[j] - intersection.g));
			intensity[j] += ax * ay;
		}
	}
	float rChannel = floor(intensity[3] * 255.) * 1e+06 + floor(intensity[4] * 255.) * 1000. + floor(intensity[0] * 255.),
	gChannel = floor(intensity[5] * 255.) * 1000. + floor(min(intensity[1], 3.9) * 255.),
	bChannel = floor(intensity[6] * 255.) * 1000. + floor(min(intensity[2], 3.9) * 255.);
	gl_FragColor = vec4(rChannel, gChannel, bChannel, 1.);
}