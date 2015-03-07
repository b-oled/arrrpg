#version 330 core
layout(location=0) in vec3 vVertex;
uniform mat4 MVP;
uniform float time;
uniform int rows;
uniform int cols;
uniform bool move = false;
uniform float amp = 1;
const float PI = 3.14159;
int instance = gl_InstanceID;
void main()
{
    float x = vVertex.x;
    float y = vVertex.y;
    float z = vVertex.z;

    if (move)
        z = z + (instance%200)*sin(-PI+time+instance);

    int mody = instance / rows;
    int modx = instance % cols;

    gl_Position = MVP*vec4(x + (modx*0.2), y + (mody*0.2), z, 1);

}
