//attribute vec2 position;
//attribute vec2 size;
//attribute vec2 scale;
//attribute float angle;
//attribute vec4 color;

attribute vec4 vertex;
varying vec2 fragTexCoord;

void main(void) {
	fragTexCoord = vec2(clamp(vertex.x, 0.0, 1.0), clamp(vertex.y*-1.0, 0.0, 1.0));

	gl_Position = vertex;
}
