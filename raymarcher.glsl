
#define MaxRaySteps 128.
#define MaxShadowRaySteps 64.
#define MinDistance 0.0001
#define R iResolution.xy
#define Iterations 3

float DE(in vec3 p) {
    p.xy = mod((p.xy), 1.0) - vec2(0.5);
    return length(p) - 0.3;
    // return min( length(p)-1.0 , length(p-vec3(2.0,0.0,0.0))-1.0 );

}

vec3 calcNormal(in vec3 p) {
    const vec3 smallStep = vec3(0.001, 0.0, 0.0);

    float gradX = DE(p + smallStep.xyy) - DE(p - smallStep.xyy);
    float gradY = DE(p + smallStep.yxy) - DE(p - smallStep.yxy);
    float gradZ = DE(p + smallStep.yyx) - DE(p - smallStep.yyx);

    vec3 normal = vec3(gradX, gradY, gradZ);

    return normalize(normal);
}

float trace(in vec3 from, in vec3 direction) {
    float totalDistance = 0.0;


    float steps;
    

    for (steps = 0.; steps < MaxRaySteps; ++steps) {
        vec3 p = from + totalDistance * direction;
        float distance = DE(p);
        totalDistance += distance;
        
        if (distance < MinDistance) {
            break;
        }
    }
    if (steps == MaxRaySteps) {
        return 1.0 - float(steps)/float(MaxRaySteps)*.99;
    }
    return 1.0 - float(steps)/float(MaxRaySteps);
}

void mainImage( out vec4 fragColor, in vec2 fragCoord ) {
    // pixel coordinates
    vec2 uv = (2.*fragCoord-R)/iResolution.y;

    vec3 cameraPos = vec3(0.0, 0.0, -5.0);
    vec3 ro = cameraPos;
    vec3 rd = vec3(uv, 1.0) + vec3(1.0, -0.5, 1.0);
    // vec3 rd = vec3(uv, 1.0);

    vec3 shadedColor = vec3(1.0, 0.0, 0.0) * trace(ro, rd);

    // Output to screen
    fragColor = vec4(shadedColor,1.0);
}