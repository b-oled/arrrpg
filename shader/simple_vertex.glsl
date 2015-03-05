#version 330 core
layout(location=0) in vec3 vVertex;
in int gl_InstanceID;
uniform mat4 MVP;
uniform float time;
const float amplitude = 0.125;
const float frequency = 4;
const float PI = 3.14159;
void main()
{
    float y = vVertex.y;
    if(time > 0)
    {
        float distance = length(vVertex);
        y = amplitude*sin(-PI*distance*frequency+time);
    }

    gl_InstanceID;
    int tenner = gl_InstanceID / 100;
    int mod = gl_InstanceID % 100;

    gl_Position = MVP*vec4(vVertex.x + (mod*0.2), y + (tenner*0.2), vVertex.z,1);

}
