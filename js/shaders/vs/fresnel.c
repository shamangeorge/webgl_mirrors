varying vec2 vUv;
varying mat4 mvm;
void main() {
	vUv = vec2( uv.x,  uv.y );
	mvm = modelViewMatrix;
	gl_Position = projectionMatrix * modelViewMatrix * vec4( position, 1.0 );
}