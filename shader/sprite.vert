attribute vec4 vertex;
attribute vec2 vertTexCoord;
varying vec2 fragTexCoord;

void main(void) {
	fragTexCoord = vertTexCoord;

	gl_Position = vertex;
}
