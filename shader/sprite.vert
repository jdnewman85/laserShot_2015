//attribute vec2 position;
//attribute vec2 size;
//attribute vec2 scale;
//attribute float angle;
//attribute vec4 color;

attribute vec4 vertex;
attribute vec2 vertTexCoord;
varying vec2 fragTexCoord;

void main(void) {
	fragTexCoord = vertTexCoord;

	gl_Position = vertex;
}
