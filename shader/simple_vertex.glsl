#version 330 core
layout(location=0) in vec3 vVertex;
uniform mat4 MVP;
uniform float time;
uniform int depth;
uniform int width;
uniform bool move = false;
uniform float amp = 1;
const float PI = 3.14159;
int instance = gl_InstanceID;
void main()
{
    float x = vVertex.x;
    float y = vVertex.y;
    float z = vVertex.z;

    int modz = instance / depth;
    int modx = instance % depth;

    if (move)
        y = y + (200)*sin(-PI+time+instance);

    gl_Position = MVP*vec4(x + (modx*0.2), y, z + (modz*0.2), 1);

}
