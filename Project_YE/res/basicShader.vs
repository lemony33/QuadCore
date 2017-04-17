#version 430 core

// mesh header file 참고
in vec3 position; // 1. shader 첫번째 // main.cpp 파일에 Vertex vertices[]에 위치를 정확히 그려줘야 그림이 그려진다 -> 그 전까지는 position과 color 선언만 해준거임.
in vec2 texCoord; // texture
in vec3 normal;   // lighting

out vec2 texCoord0;  // texture
out vec3 normal0;    // lighting

uniform mat4 transform;  // uniform 에 transform을 set한다

void main()
{
	gl_Position = transform * vec4(position, 1.0); // trnasform

	texCoord0 = texCoord;
	normal0 = (transform * vec4(normal, 0.0)).xyz;	   //lighting
}

