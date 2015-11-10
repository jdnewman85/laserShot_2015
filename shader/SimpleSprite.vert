attribute vec2 position;
varying vec2 fragTexCoord;

void main(void) {
	fragTexCoord = vec2(clamp(position.x, 0.0, 1.0), clamp(position.y*-1.0, 0.0, 1.0));

	gl_Position = vec4(position*0.1, 1.0, 1.0);
}
