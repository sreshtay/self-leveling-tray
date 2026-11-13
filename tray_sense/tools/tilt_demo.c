/*
gcc tilt_demo.c -lm -o tilt_demo && ./tilt_demo

Checks pitch and roll formula using made up accelerometer readings since I do not have the physical material on me.


*/
#include <stdio.h>
#include <math.h>

int main(void) {
    float tests[][3] = {
        {0, 0, 1}, 
        {0.5f, 0, 0.866f}, 
        {0, 0.5f, 0.866f},
        {-0.5f, 0, 0.866f}, 
    };
    for (int i = 0; i < 4; i++) {
        float x = tests[i][0];
        float y = tests[i][1];
        float z = tests[i][2];
        float pitch = atanf(x / sqrtf(y*y + z*z)) * 180.0f / 3.14;
        float roll = atanf(y / sqrtf(x*x + z*z)) * 180.0f / 3.14;
        printf("x=%5.3f y=%5.3f z=%5.3f -> pitch %6.2f, roll %6.2f\n", x, y, z, pitch, roll);
    
    }
    return 0;
}