uniform sampler2D tDataSampler;
uniform float divCaustic;
uniform vec2 texelSize;
varying vec2 vUv;
void main(){
	float v=0.;
	v+=mod(texture2D(tDataSampler,vUv+vec2(0.,-3.*texelSize.g)).r,1000.)/255.;
	v+=mod(texture2D(tDataSampler,vUv+vec2(0.,-2.*texelSize.g)).g,1000.)/255.;
	v+=mod(texture2D(tDataSampler,vUv+vec2(0.,-1.*texelSize.g)).b,1000.)/255.;
	v+=floor(texture2D(tDataSampler,vUv).r/1e+06)/255.;
	v+=floor(texture2D(tDataSampler,vUv+vec2(0.,texelSize.g)).r/1000.)/255.;
	v+=floor(texture2D(tDataSampler,vUv+vec2(0.,2.*texelSize.g)).g/1000.)/255.;
	v+=floor(texture2D(tDataSampler,vUv+vec2(0.,3.*texelSize.g)).b/1000.)/255.;
	v/=divCaustic;
	gl_FragColor=vec4(v,v,v,1.);
}