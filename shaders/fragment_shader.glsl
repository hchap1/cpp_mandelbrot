#version 330 core
in vec2 screen_pos;
out vec4 FragColor;

void main() {

	float oa = screen_pos.x * 2.0f;
	float ob = screen_pos.y * 2.0f;

	float a = oa;
	float b = ob;

	float old_a;
	float dx;
	float dy;

	int iterations = 100;
	float stability = 0.0f;

	for (int i = 0; i < iterations; i++) {
		old_a = a;
		a = a * a - b * b + oa;
		b = 2.0f * old_a * b + ob;

		dx = pow(oa - a, 2.0f);
		dy = pow(ob - b, 2.0f);

		if (dx + dy > 4.0f) {
			break;
		}
		stability += 1.0f;
	}

	float colour = stability / float(iterations);

    FragColor = vec4(colour, 0.0f, 0.0f, 1.0f);
} 
