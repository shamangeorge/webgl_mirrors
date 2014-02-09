const float v=3.14159;
uniform sampler2D tData;
uniform vec2 texelSize,mousePoint;
uniform int mouseActive;
uniform float radius,strength;
varying vec2 vUv;
void main(){
	vec4 t=texture2D(tData,vUv);
	if(mouseActive>=1){
		float m=max(0.,1.-length(mousePoint-vUv)/radius);
		m=.5-cos(m*v)*.5;
		t.r-=m*strength;
	}
	vec2 m=vec2(texelSize.r,0.),r=vec2(0.,texelSize.g);
	float f=(texture2D(tData,vUv-m).r+texture2D(tData,vUv-r).r+texture2D(tData,vUv+m).r+texture2D(tData,vUv+r).r)*.25;
	t.g+=(f-t.r)*2.;
	t.g*=.995;
	t.r+=t.g;
	t.r*=.995;
	gl_FragColor=vec4(t.r,t.g,t.b,1.);
}