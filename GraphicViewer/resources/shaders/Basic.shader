#shader vertex
#version 330 core //glsl version

layout(location = 0) in vec3 aPos;
layout(location = 1) in vec3 vcolor;
layout(location = 2) in vec2 aTex;

out vec3 color;
uniform float scale;
out vec2 texCoord;

void main()
{
	gl_Position = vec4(aPos.x + aPos.x * scale, aPos.y + aPos.y * scale, aPos.z + aPos.z * scale, 1.0);
	color = vcolor;
	texCoord = aTex;
}


#shader fragment
#version 330 core

out vec4 FragColor;
in vec3 color;
in vec2 texCoord;

uniform sampler2D tex0;

void main()
{
	//FragColor = vec4(0.8f,0.3f,0.02f,1.0f);
	/*FragColor = vec4(color, 1.0f);*/
	FragColor = texture(tex0, texCoord);
}