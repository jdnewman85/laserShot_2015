attribute vec2 vertex;
varying vec2 fragTexCoord;

void main(void) {
	fragTexCoord = vec2(clamp(vertex.x, 0.0, 1.0), clamp(vertex.y*-1.0, 0.0, 1.0));

	gl_Position = vec4(vertex, 1.0, 1.0);
}
