attribute vec2 vertPos;
attribute vec2 vertTexCoord;
varying vec2 fragTexCoord;

void main(void) {
	fragTexCoord = vertTexCoord;

	gl_Position = vec4(vertPos, 1.0, 1.0);
}
