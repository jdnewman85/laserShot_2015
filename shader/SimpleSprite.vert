attribute vec2 vertPos;
varying vec2 fragTexCoord;

void main(void) {
	fragTexCoord = vec2(clamp(vertPos.x, 0.0, 1.0), clamp(vertPos.y*-1.0, 0.0, 1.0));

	gl_Position = vec4(vertPos, 1.0, 1.0);
}
