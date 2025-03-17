#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define hpconst 5252.0f;

void err(const char *msg) {
    fprintf(stderr, "Error: %s\n", msg);
    exit(-1);
}

typedef struct {
    int cc;          // Engine displacement in cubic centimeters (cc)
    int pistons;     // Number of pistons
    float hp;        // Horsepower of the engine
    int redline;     // Maximum engine RPM (redline)
    float torque;    // Torque in lb-ft
} Engine;


typedef struct {
    int gearcount;       // Number of gears in the gearbox
    float *gearratios;   // Array of gear ratios for each gear
} Gearbox;

typedef struct {
    char *model;         // Bike model
    char *brand;         // Bike brand
    int maxSpeed;        // Maximum speed of the bike (calculated later)
    float ptwr;          // Power-to-weight ratio
    float weight;        // Weight of the bike
    char *nick;          // Nickname for the bike (optional)
    float prat;          // Primary ratio
    float fdr;           // Final drive ratio
    Engine engine;       // Engine object
    Gearbox gbx;         // Gearbox object
} Bike;


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
    
    float hp = (torque * redline) / hpconst;
    
    printf("\nEngine overlay:\nHP->%f\nRPM->%d\nTorque->%f\nCC->%d\nPistons->%d\n", hp, redline, torque, cc, pistons);
    
    Engine eng = {cc, pistons, hp, redline, torque};
    return eng;
}

Gearbox buildBikeGearbox() {
    printf("\n-------------GearBox Build->");
    
    int gearcount;
    printf("How many gears you have zibiddy boi :3\n->");
    scanf("%d", &gearcount);
    
    if (gearcount <= 0) err("I don't think you understand this....");
    
    float *ratios = (float *)malloc(sizeof(float) * gearcount);
    if (ratios == NULL) err("Memory allocation failed."); // Updated error message
    
    for (int i = 0; i < gearcount; i++) {
        printf("%d%s Gear Ratio: ", i + 1, (i == 0) ? "st" : (i == 1) ? "nd" : "th"); // Fixed gear suffix formatting
        scanf("%f", &ratios[i]);
    }
    
    Gearbox gbx = {gearcount, ratios};
    return gbx;
}

float speedTest(Bike *bike) {
    int temp = bike->gbx.gearcount;
    float totalratio = bike->gbx.gearratios[temp - 1] * bike->fdr;
    float bottom = totalratio * 60;
    float top = bike->engine.redline * 1.85f; // Changed 2 to 1.85 to approximate a real tire circumference in meters
    float topkmh = top / bottom;
    return topkmh * 3.6f; // Convert m/s to km/h
}

Bike buildBike() {
    Bike bike;
    bike.engine = buildBikeEngine();
    bike.gbx = buildBikeGearbox();

    printf("\nWeight: ");
    scanf("%f", &bike.weight);
    bike.ptwr = bike.engine.hp / bike.weight;

    printf("\nPrimary Ratio: ");
    scanf("%f", &bike.prat);

    printf("\nFinal Drive Ratio: ");
    scanf("%f", &bike.fdr);
    
    getchar(); // Consume newline character

    char temp[100];

    printf("\nModel: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    bike.model = strdup(temp);

    printf("\nBrand: ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    bike.brand = strdup(temp);

    printf("\nNick(* for none): ");
    fgets(temp, sizeof(temp), stdin);
    temp[strcspn(temp, "\n")] = '\0';
    bike.nick = (strcmp(temp, "*") == 0) ? NULL : strdup(temp);
    
    bike.maxSpeed = (int)speedTest(&bike); // Fixed to ensure maxSpeed is an integer

    return bike;
}

void freeBike(Bike *bike) {
    free(bike->model);
    free(bike->brand);
    if (bike->nick) free(bike->nick);
    free(bike->gbx.gearratios);
}

void bikeOverlay(Bike bike) {
    printf("---Engine->\n");
    printf("CC-> %d\nPistons-> %d\nRedLine-> %d\nHp-> %.2f\nTorque-> %.2f\n", 
            bike.engine.cc, bike.engine.pistons, bike.engine.redline, bike.engine.hp, bike.engine.torque);
    
    printf("--GearBox->\nGear Count-> %d\n", bike.gbx.gearcount);
    for (size_t i = 0; i < bike.gbx.gearcount; i++) {
        printf("%lu%s Gear Ratio: %.4f\n", i + 1, (i == 0) ? "st" : (i == 1) ? "nd" : "th", bike.gbx.gearratios[i]);
    }
    
    printf("-----Bike->\n");
    printf("Model-> %s\nBrand-> %s\n", bike.model, bike.brand);
    if (bike.nick) printf("Nick-> %s\n", bike.nick);
    printf("Max Speed-> %d km/h\n", bike.maxSpeed);
}

int main() {
    Bike myBike = buildBike();
    bikeOverlay(myBike); // Added to display the bike details
    freeBike(&myBike);
    return 0;
}