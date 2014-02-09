uniform float causticRatio;
uniform vec2 uGroundRepeat;
uniform vec3 viewPosition, heightMapFactor, lightDir;
uniform sampler2D tData, tNormalMap, tGround, tSky, tCaustic;
uniform int caustics, dirLight;
uniform vec2 texelSize;
varying vec2 vUv;
varying mat4 mvm;

void main(){
	vec3 	v = vec3(vUv.r * heightMapFactor.r, texture2D(tData, vUv).r * heightMapFactor.g, vUv.g * heightMapFactor.b),
			t = vec3(	vUv.r * 256. - 128., texture2D(tData, vUv).r * heightMapFactor.g, vUv.g * 256. - 128.), 
			r = -normalize(texture2D(tNormalMap, vUv).rgb), 
			b = v - vec3(	heightMapFactor.r / 2., 256., heightMapFactor.b/2.), 
			n = t - vec3(0.,300.,0.), 
			h = reflect(-normalize(b), r), 
			u = refract(normalize(b),r,1.);
	vec3 	m = refract(normalize(n), r, 1.);
	vec4 	a = texture2D(tSky, vec2(h.r, h.b) ),
			g = texture2D(tGround, vec2(u.r, u.b) / u.g * uGroundRepeat + .5);
	if ( caustics == 1 ) {
		g *= pow(max(texture2D(tCaustic, vec2(m.r, m.b) + .5).r, .35) + .5, 4.);
	}
	g.a = 1.;
	gl_FragColor = mix(g,a, .2);
	if ( dirLight == 1 ) {
		float d = pow(max(dot(r,normalize(lightDir))+.2,1.),8.);
		vec3 c = vec3(d, d, d);
		gl_FragColor.rgb *=c;
	}
}