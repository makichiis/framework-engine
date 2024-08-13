#include <math.h>

// LUT
static int Noise_p[512] = {
    151,160,137,91,90,15,
    131,13,201,95,96,53,194,233,7,225,140,36,103,30,69,142,8,99,37,240,21,10,23,
    190, 6,148,247,120,234,75,0,26,197,62,94,252,219,203,117,35,11,32,57,177,33,
    88,237,149,56,87,174,20,125,136,171,168, 68,175,74,165,71,134,139,48,27,166,
    77,146,158,231,83,111,229,122,60,211,133,230,220,105,92,41,55,46,245,40,244,
    102,143,54, 65,25,63,161, 1,216,80,73,209,76,132,187,208, 89,18,169,200,196,
    135,130,116,188,159,86,164,100,109,198,173,186, 3,64,52,217,226,250,124,123,
    5,202,38,147,118,126,255,82,85,212,207,206,59,227,47,16,58,17,182,189,28,42,
    223,183,170,213,119,248,152, 2,44,154,163, 70,221,153,101,155,167, 43,172,9,
    129,22,39,253, 19,98,108,110,79,113,224,232,178,185, 112,104,218,246,97,228,
    251,34,242,193,238,210,144,12,191,179,162,241, 81,51,145,235,249,14,239,107,
    49,192,214, 31,181,199,106,157,184, 84,204,176,115,121,50,45,127, 4,150,254,
    138,236,205,93,222,114,67,29,24,72,243,141,128,195,78,66,215,61,156,180,
    151
};

inline double Noise_fade(double t) {
    return t * t * t * (t * (t * 6 - 15) + 10);
}

inline double Noise_lerp(double t, double a, double b) {
    return a + t * (b - a);
}

inline double Noise_grad(int hash, double x, double y, double z) {
    int h = hash & 15;
    double u = h < 8 ? x : y, v = h < 4 ? y : h == 12 || h == 14 ? x : z;
    return ((h & 1) ? -u : u) + ((h & 2) ? -v : v);
}

// 1D Perlin Noise
double Noise_perlin1D(double x) {
    int X = (int)floor(x) & 255;
    x -= floor(x);
    double u = Noise_fade(x);
    return Noise_lerp(u, Noise_grad(Noise_p[X], x, 0, 0), Noise_grad(Noise_p[X + 1], x - 1, 0, 0));
}

// 2D Perlin Noise
double Noise_perlin2D(double x, double y) {
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    x -= floor(x);
    y -= floor(y);
    double u = Noise_fade(x);
    double v = Noise_fade(y);
    int A = Noise_p[X] + Y;
    int B = Noise_p[X + 1] + Y;
    return Noise_lerp(v, Noise_lerp(u, Noise_grad(Noise_p[A], x, y, 0), Noise_grad(Noise_p[B], x - 1, y, 0)),
                Noise_lerp(u, Noise_grad(Noise_p[A + 1], x, y - 1, 0), Noise_grad(Noise_p[B + 1], x - 1, y - 1, 0)));
}

// 3D Perlin Noise
double Noise_perlin3D(double x, double y, double z) {
    int X = (int)floor(x) & 255;
    int Y = (int)floor(y) & 255;
    int Z = (int)floor(z) & 255;
    x -= floor(x);
    y -= floor(y);
    z -= floor(z);
    double u = Noise_fade(x);
    double v = Noise_fade(y);
    double w = Noise_fade(z);
    int A = Noise_p[X] + Y, AA = Noise_p[A] + Z, AB = Noise_p[A + 1] + Z;
    int B = Noise_p[X + 1] + Y, BA = Noise_p[B] + Z, BB = Noise_p[B + 1] + Z;
    return Noise_lerp(w, Noise_lerp(v, Noise_lerp(u, Noise_grad(Noise_p[AA], x, y, z), Noise_grad(Noise_p[BA], x - 1, y, z)),
        Noise_lerp(u, Noise_grad(Noise_p[AB], x, y - 1, z), Noise_grad(Noise_p[BB], x - 1, y - 1, z))),
        Noise_lerp(v, Noise_lerp(u, Noise_grad(Noise_p[AA + 1], x, y, z - 1), Noise_grad(Noise_p[BA + 1], x - 1, y, z - 1)),
        Noise_lerp(u, Noise_grad(Noise_p[AB + 1], x, y - 1, z - 1), Noise_grad(Noise_p[BB + 1], x - 1, y - 1, z - 1))));
}
