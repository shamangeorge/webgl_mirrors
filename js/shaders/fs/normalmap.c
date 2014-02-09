uniform sampler2D tData;
uniform float deltaNormal;
uniform vec2 texelSize;
varying vec2 vUv;
void main(){
	vec3 t = vec3( 2. , max( texture2D( tData, vUv + vec2( texelSize.r, 0.) ).r, texture2D( tData, vUv + vec2( texelSize.r, 0.)).b) - max(texture2D( tData, vUv - vec2( texelSize.r, 0.)).r, texture2D( tData, vUv - vec2( texelSize.r, 0.) ).b), 0.),
	v = vec3( 0., max( texture2D( tData, vUv + vec2( 0., texelSize.g) ).r, texture2D( tData, vUv + vec2( 0., texelSize.g)).b) - max( texture2D( tData, vUv - vec2( 0., texelSize.g) ).r, texture2D( tData, vUv - vec2( 0., texelSize.g) ).b), 2.),
	r = cross(t,v);
	gl_FragColor=vec4(r,1.);
}