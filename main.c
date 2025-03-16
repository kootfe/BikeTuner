#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int cc;
    int pistons;
    float hp; //for engine
    int redline;
    float torque;
} Engine;

typedef struct {
    char *name;
    char *brand;
    int maxSpeed;
    float ptwr; //Power to Weight Ratio.
    float weight;
    char *nick;
    float primaryratio;
    float finaldrive;
    Engine engine;
    Gearbox gbx;
} Bike;

typedef struct {
    int gearcount;
    float *gearratios;
} Gearbox;


Engine buildBikeEngine() {
    printf("--------------Engine Build->");
    printf("Whats your engine cc?\n->");

    int cc;
    scanf("%d", &cc);
    printf("\nRedline?\n->");

    int redline;
    scanf("%d", &redline);
    printf("\nTorque?(lb-ft)\n->");
    
    float torque;
    scanf("%f", &torque);
    printf("\nCylinder Count?\n->");
    
    int pistons;
    scanf("%d", &pistons);
    
    float hp = (torque*redline)/5252.0f;
    
    printf("\nEngine overlay:\nHP->%f\nRPM->%d\nTorque->%f\nCC->%d\nPistons->%d", hp, redline, torque, cc, pistons);
    
    Engine eng = {cc, pistons, hp, redline, torque};
    return eng;
}

Gearbox buildBikeGearbox() {
    printf("-------------GearBox Build->");
    
    int gearcount;
    printf("How many gears you have zibiddy boi :3\n->");
    scanf("%d", &gearcount);
    
    if (gearcount <= 0) err("I don't think you understadn this....");

    float *ratios = (float*)malloc(sizeof(float)*gearcount);
    if (ratios == NULL) err("Well thats not my problem. It works on my machine...");

    for (int i = 0; i < gearcount; i++) {
        float temp;
        if (i == 0) {
            printf("1st Gear Ratio: ");
        } else if (i == 1) {
            printf("\n2nd Gear Ratio: ");
        } else {
            printf("\n%dth Gear Ratio: ", i+1);
        }
        scanf("%f", &temp);
        ratios[i] = temp;
    }
    
    Gearbox gbx = {gearcount, ratios};
    return gbx;
}

void buildBike() { //Finaly; (i did this at end :3);
    Bike osbir;
    osbir.engine = buildBikeEngine();
    osbir.gbx = buildBikeGearbox();
    char *name, *brand, *nick;
    float weight, ptwr, prat, fdr;
    int maxspd;
    printf("\nWeight: ");
    scanf("%f", &weight);
    ptwr = hp/osbir.engine.hp;
    printf("\nPrimary Ratio: ");
    scanf("%f", &prat);
    printf("\nFinal Drive Ratio: ");
    scanf("%f", &fdr);
    printf("\n")
}

void freeGbx(Gearbox gbx) {
    free(gbx.gearratios);
}

void err(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(-1);
}

int main() {
    Bike myBike;
    freeGbx(myBike.gbx);
    return 0;
}
