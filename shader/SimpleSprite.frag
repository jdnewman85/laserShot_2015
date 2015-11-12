varying lowp vec2 fragTexCoord;
uniform sampler2D Texture;

void main(void) {
	gl_FragColor = vec4(1.0, 0.0, 0.0, 1.0); //texture2D(Texture, fragTexCoord);
}
