#version 330 core
layout(location=0) in vec3 position;
uniform mat4 matrix;
uniform float time;
const float amplitude = 0.125;
const float frequency = 4;
const float PI = 3.14159;
void main()
{
    float y = position.y;
    if(time > 0)
    {
        float distance = length(position);
        y = amplitude*sin(-PI*distance*frequency+time);
    }

    gl_Position = matrix*vec4(position.x, y, position.z,1);

}
