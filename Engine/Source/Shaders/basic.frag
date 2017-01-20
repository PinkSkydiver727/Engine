#version 330

layout (location = 0) out vec4 color;

uniform vec4 colour;
uniform vec2 light_pos;
uniform sampler2D textures[32];

in DATA
{
	vec4 position;
	vec2 uv;
	float tid;
	vec4 color;
} fs_in;

void main()
{
	float intensity = 1.0f / length(fs_in.position.xy - light_pos);
	//color = colour * intensity;

	vec4 texColor = fs_in.color;
	if(fs_in.tid > 0.0)
	{
		int tid = int(fs_in.tid - 0.5); // guarenteed floor rounding;
		texColor = texture(textures[tid], fs_in.uv);
	}
	color = texColor; //* intensity;
}