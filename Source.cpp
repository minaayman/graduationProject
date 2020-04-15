#include "SDL.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include<math.h>
#undef main
using namespace std;

void dramRectangle(SDL_Renderer* renderer, int x, int y, int w, int h)
{
    int m = 4;
    SDL_Rect rect;
    rect.x = x * m;
    rect.y = y * m;
    rect.w = w * m;
    rect.h = h * m;



    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
    SDL_RenderDrawRect(renderer, &rect);
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}


void drawLine(SDL_Renderer* renderer, int x1, int y1, int x2, int y2, float color)
{
    int m = 4;
    int g = 1;
    int b = 1;
    int r = 1;
    if (color > 1) { g = 0; b = 0; r = 1; }

    SDL_SetRenderDrawColor(renderer, r * 255, g * 255, b * 255, 255);
    SDL_RenderDrawLine(renderer, m * x1, m * y1, m * x2, m * y2);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
    SDL_RenderPresent(renderer);
}


struct Point
{
    float x, y;
};

float** generateArray(int r, int c) {
    float** matrix = new float* [r];
    for (int i = 0; i < r; i++) {
        matrix[i] = new float[c];

    }
    return matrix;
}

double** generateArrayDouble(int r, int c) {
    double** matrix = new double* [r];
    for (int i = 0; i < r; i++) {
        matrix[i] = new double[c];

    }
    return matrix;
}

void printArray(float** arr, int r, int c) {
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {

            std::cout << arr[i][j] << ',';

        }
        std::cout << endl;
    }
}

double totalArea(float** arrCoordenat, float** arrModuleDimension, int m)
{
    double maxX = 0, maxY = 0, minX = 0, minY = 0;

    for (int i = 0; i < m; i++) {

        Point lgen = { arrCoordenat[i][0],arrCoordenat[i][1] + arrModuleDimension[i][1] };
        Point rgen = { arrCoordenat[i][0] + arrModuleDimension[i][0] , arrCoordenat[i][1] };
        if (i == 0) {
            maxX = arrCoordenat[i][0] + arrModuleDimension[i][0];
            maxY = arrCoordenat[i][1] + arrModuleDimension[i][1];
            minX = arrCoordenat[i][0];
            minY = arrCoordenat[i][1];
        }
        else {
            if (arrCoordenat[i][0] + arrModuleDimension[i][0] > maxX) { maxX = arrCoordenat[i][0] + arrModuleDimension[i][0]; }
            if (arrCoordenat[i][1] + arrModuleDimension[i][1] > maxY) { maxY = arrCoordenat[i][1] + arrModuleDimension[i][1]; }
            if (arrCoordenat[i][0] < minX) { minX = arrCoordenat[i][0]; }
            if (arrCoordenat[i][1] < minY) { minY = arrCoordenat[i][1]; }

        }


    }
    double area = (maxX - minX) * (maxY - minY);

    return area;

}
float aspectRatio(float** arrCoordenat, float** arrModuleDimension, int m) {
    float maxX = 0, maxY = 0, minX = 0, minY = 0;

    for (int i = 0; i < m; i++) {

        Point lgen = { arrCoordenat[i][0],arrCoordenat[i][1] + arrModuleDimension[i][1] };
        Point rgen = { arrCoordenat[i][0] + arrModuleDimension[i][0] , arrCoordenat[i][1] };
        if (i == 0) {
            maxX = arrCoordenat[i][0] + arrModuleDimension[i][0];
            maxY = arrCoordenat[i][1] + arrModuleDimension[i][1];
            minX = arrCoordenat[i][0];
            minY = arrCoordenat[i][1];
        }
        else {
            if (arrCoordenat[i][0] + arrModuleDimension[i][0] > maxX) { maxX = arrCoordenat[i][0] + arrModuleDimension[i][0]; }
            if (arrCoordenat[i][1] + arrModuleDimension[i][1] > maxY) { maxY = arrCoordenat[i][1] + arrModuleDimension[i][1]; }
            if (arrCoordenat[i][0] < minX) { minX = arrCoordenat[i][0]; }
            if (arrCoordenat[i][1] < minY) { minY = arrCoordenat[i][1]; }

        }


    }
    float aspectRatio = (maxX - minX) / (maxY - minY);
    float diff = abs(1 - ((maxX - minX) / (maxY - minY)));

    return diff;


}



double calculateSummitionHpwl(float** arrConnection, float** arrMappedPinsCoordinates, float** arrNetPinsCoordinates, float** netPriority, int m, int nets, int pins) {
    double Hpwl = 0;
    double  L = 0;
    double maxX = 0; double maxY = 0; double minX = 10000; double minY = 10000;
    float prior = 1;
    for (int s = 0; s < m; s++) {

        for (int q = 0; q < nets; q++) {


            if (arrConnection[q][0] == s) {
                for (int i = 0; i < pins; i++) { ////////////////////////to go throw the arrPinCoordinates////////////////////////////////
                    if ((arrMappedPinsCoordinates[i][0] == s) && (arrConnection[q][2] == arrMappedPinsCoordinates[i][1])) {
                        arrNetPinsCoordinates[0][0] = arrMappedPinsCoordinates[i][2];
                        arrNetPinsCoordinates[0][1] = arrMappedPinsCoordinates[i][3];

                    }
                }
                if (arrNetPinsCoordinates[0][0] > maxX) {
                    maxX = arrNetPinsCoordinates[0][0];
                }
                if (arrNetPinsCoordinates[0][1] > maxY) {
                    maxY = arrNetPinsCoordinates[0][1];
                }
                if (arrNetPinsCoordinates[0][0] < minX) {
                    minX = arrNetPinsCoordinates[0][0];
                }
                if (arrNetPinsCoordinates[0][1] < minY) {
                    minY = arrNetPinsCoordinates[0][1];
                }

                for (int i = 0; i < pins; i++) {
                    if ((arrMappedPinsCoordinates[i][0] == arrConnection[q][1]) && (arrConnection[q][3] == arrMappedPinsCoordinates[i][1])) {
                        arrNetPinsCoordinates[0][0] = arrMappedPinsCoordinates[i][2];
                        arrNetPinsCoordinates[0][1] = arrMappedPinsCoordinates[i][3];
                        // printArray(arrNetPinsCoordinates, 1, 2);
                    }
                }
                if (arrNetPinsCoordinates[0][0] > maxX) {
                    maxX = arrNetPinsCoordinates[0][0];
                }
                if (arrNetPinsCoordinates[0][1] > maxY) {
                    maxY = arrNetPinsCoordinates[0][1];
                }
                if (arrNetPinsCoordinates[0][0] < minX) {
                    minX = arrNetPinsCoordinates[0][0];
                }
                if (arrNetPinsCoordinates[0][1] < minY) {
                    minY = arrNetPinsCoordinates[0][1];
                }
            }
            if (arrConnection[q][0] == s) {

                Hpwl = ((maxX - minX) + (maxY - minY)) * prior;
                maxX = 0;
                minX = 10000;
                maxY = 0;
                minY = 10000;

                L = L + netPriority[q][0] * Hpwl;


            }
        }
    }
    return L;
}

void mappingPinsToModules(float** arrMappedPinsCoordinates, float** arrPinsCoordinates, float** arrCoordenat, int pins) {
    int k = 1;
    int flag3 = 0;
    for (int i = 0; i < pins; i++) {

        if (arrPinsCoordinates[i][0] == 0) {
            arrMappedPinsCoordinates[i][0] = 0;
            arrMappedPinsCoordinates[i][1] = k;
            //cout << arrPinsCoordinates[i][2]<<endl<< arrCoordenat[0][0];
            arrMappedPinsCoordinates[i][2] = arrPinsCoordinates[i][2] + arrCoordenat[0][0];
            arrMappedPinsCoordinates[i][3] = arrPinsCoordinates[i][3] + arrCoordenat[0][1];

            k++;
            // printArray(arrMappedPinsCoordinates, pins, 4);
            // cout << "********************************************************************************************************************" << endl;

        }
        else if (arrPinsCoordinates[i][0] == 1) {
            if (flag3 == 0) k = 1;
            arrMappedPinsCoordinates[i][0] = 1;
            arrMappedPinsCoordinates[i][1] = k;
            arrMappedPinsCoordinates[i][2] = arrPinsCoordinates[i][2] + arrCoordenat[1][0];
            arrMappedPinsCoordinates[i][3] = arrPinsCoordinates[i][3] + arrCoordenat[1][1];
            k++;
            flag3 = 1;
            //  printArray(arrMappedPinsCoordinates, pins, 4);
            //  cout << "********************************************************************************************************************" << endl;
        }
        else if (arrPinsCoordinates[i][0] == 2) {
            if (flag3 == 1) k = 1;
            arrMappedPinsCoordinates[i][0] = 2;
            arrMappedPinsCoordinates[i][1] = k;
            arrMappedPinsCoordinates[i][2] = arrPinsCoordinates[i][2] + arrCoordenat[2][0];
            arrMappedPinsCoordinates[i][3] = arrPinsCoordinates[i][3] + arrCoordenat[2][1];
            k++;
            flag3 = 0;

            //  printArray(arrMappedPinsCoordinates, pins, 4);
             // cout << "********************************************************************************************************************" << endl;
        }
        else if (arrPinsCoordinates[i][0] == 3) {
            if (flag3 == 0) k = 1;
            arrMappedPinsCoordinates[i][0] = 3;
            arrMappedPinsCoordinates[i][1] = k;
            arrMappedPinsCoordinates[i][2] = arrPinsCoordinates[i][2] + arrCoordenat[3][0];
            arrMappedPinsCoordinates[i][3] = arrPinsCoordinates[i][3] + arrCoordenat[3][1];
            k++;
            flag3 = 1;
            // printArray(arrMappedPinsCoordinates, pins, 4);
             //cout << "********************************************************************************************************************" << endl;
        }
        else if (arrPinsCoordinates[i][0] == 4) {
            if (flag3 == 1) k = 1;
            arrMappedPinsCoordinates[i][0] = 4;
            arrMappedPinsCoordinates[i][1] = k;
            arrMappedPinsCoordinates[i][2] = arrPinsCoordinates[i][2] + arrCoordenat[4][0];
            arrMappedPinsCoordinates[i][3] = arrPinsCoordinates[i][3] + arrCoordenat[4][1];
            k++;
            flag3 = 0;
            // printArray(arrMappedPinsCoordinates, pins, 4);
            // cout << "********************************************************************************************************************" << endl;
        }
        else if (arrPinsCoordinates[i][0] == 5) {
            if (flag3 == 0) k = 1;
            arrMappedPinsCoordinates[i][0] = 5;
            arrMappedPinsCoordinates[i][1] = k;
            arrMappedPinsCoordinates[i][2] = arrPinsCoordinates[i][2] + arrCoordenat[5][0];
            arrMappedPinsCoordinates[i][3] = arrPinsCoordinates[i][3] + arrCoordenat[5][1];
            k++;
            flag3 = 1;
            //printArray(arrMappedPinsCoordinates, pins, 4);
           // cout << "********************************************************************************************************************" << endl;
        }
        else if (arrPinsCoordinates[i][0] == 6) {
            if (flag3 == 1) k = 1;
            arrMappedPinsCoordinates[i][0] = 6;
            arrMappedPinsCoordinates[i][1] = k;
            arrMappedPinsCoordinates[i][2] = arrPinsCoordinates[i][2] + arrCoordenat[6][0];
            arrMappedPinsCoordinates[i][3] = arrPinsCoordinates[i][3] + arrCoordenat[6][1];
            k++;
            flag3 = 0;
            // printArray(arrMappedPinsCoordinates, pins, 4);
            // cout << "********************************************************************************************************************" << endl;
        }

    }
}

bool doOverlap(Point l1, Point r1, Point l2, Point r2)
{
    // If one rectangle is on left side of other 
    if (l1.x > r2.x || l2.x > r1.x)
        return false;

    // If one rectangle is above other 
    if (l1.y < r2.y || l2.y < r1.y)
        return false;

    return true;
}

float ThermalDistanceConstrain(float** arrCoordenat, float** arrModuleDimension, float** arrCriticalModulesIndex, int mCritical, int arrThermalModuleIndex) {
    float xt = 0, yt = 0, xc = 0, yc = 0;
    float distance = 0, totalDistance = 0;
    xt = arrCoordenat[arrThermalModuleIndex][0] + (arrModuleDimension[arrThermalModuleIndex][0] / 2);////////////// 3ayez ada5al 2el module dimension fel 7esbah
    yt = arrCoordenat[arrThermalModuleIndex][1] + (arrModuleDimension[arrThermalModuleIndex][1] / 2);

    for (int i = 0; i < mCritical; i++) {
        xc = arrCoordenat[(int)arrCriticalModulesIndex[i][0]][0] + (arrModuleDimension[(int)arrCriticalModulesIndex[i][0]][0] / 2);
        yc = arrCoordenat[(int)arrCriticalModulesIndex[i][0]][1] + (arrModuleDimension[(int)arrCriticalModulesIndex[i][0]][1] / 2);

        distance = sqrt(pow(xt - xc, 2) + pow(yt - yc, 2));
        totalDistance += distance;
    }
    return totalDistance;
}

void generateCombinations(float** arrNumberModulesShapes, float** arrGenerateCombinations, int noOfModules, int mul) {

    int K, E, P, S = 0;



    for (int j = 1; j <= noOfModules; j++) {

        K = noOfModules - j;
        E = (K + 1) * 10;
        P = 1;

        for (int i = 0; i < mul; i++) { ////////////////////// 5aly 27 deh dynamic

            if (j == 1) {
                arrGenerateCombinations[i][K] = E + P;
                P++;

                if (P == arrNumberModulesShapes[K][0] + 1) { P = 1; }
            }
            else {

                arrGenerateCombinations[i][K] = E + P;
                for (int m = 1; m < j; m++) {
                    if ((arrGenerateCombinations[i][K + m] - (K + m + 1) * 10) == arrNumberModulesShapes[K + m][0]) {
                        S++;
                    }
                }
                if (((arrGenerateCombinations[i][K] - E) == arrNumberModulesShapes[K][0]) && j == S + 1) { P = 0; }
                if (j == S + 1) { P++; }
                S = 0;

            }



        }

    }

}

void convertArraysModuleDimensions(float** arrModuleDimensionAllShapes, float** arrGenerateCombinations, float** arrModuleDimension, int noOfModules, int AllShapesNumber, int w) {
    for (int f = 0; f < noOfModules; f++) {
        for (int h = 0; h < AllShapesNumber; h++) {
            if (arrModuleDimensionAllShapes[h][0] == arrGenerateCombinations[w][f]) {
                arrModuleDimension[f][0] = arrModuleDimensionAllShapes[h][1];
                arrModuleDimension[f][1] = arrModuleDimensionAllShapes[h][2];
            }
        }
    }
}

void convertArraysPinCoordinates(float** arrGeneratePinCombinations, float** arrGenerateCombinations, float** arrPinsCoordinates, float** arrPinNewCoordinates, int noOfModules, int AllPinsNumber, int w, int i) {

    int qw = 0;
    for (int f = 0; f < noOfModules; f++) {
        for (int h = 0; h < AllPinsNumber; h++) {
            if ((arrPinsCoordinates[h][0] == arrGenerateCombinations[w][f]) && (arrPinsCoordinates[h][4] == arrGeneratePinCombinations[i][f])) {
                arrPinNewCoordinates[qw][0] = f;
                arrPinNewCoordinates[qw][1] = arrPinsCoordinates[h][1];
                arrPinNewCoordinates[qw][2] = arrPinsCoordinates[h][2];
                arrPinNewCoordinates[qw][3] = arrPinsCoordinates[h][3];
                qw++;
            }
        }
    }





}

void perturbeToCalculateNormalizationValuesAreaHpwlThermalconstAspect(float** arrMax, float** arrMin, float** arrGetAverage, float** arrCriticalModulesIndex, float** netPriority, float** arrNetPinsCoordinates, float** arrMappedPinsCoordinates, float** arrPinNewCoordinates, float** arrConnection, float** arrCoordenat, float** arrModuleDimension, int xGrid, int yGrid, int noOfModules, int nets, int pins, int mCritical) {

    int randomModuleSelectionX; int randomModuleSelectionY; float overlapTerm; float costNew; float deltaCost;
    float randomXForModule; float randomYForModule;

    int  randModuleSelection1;
    int  randModuleSelection2;
    int randnumx;
    int randnumy;
    int d = 0;
    Point lgen1 = { 0,0 }, rgen1 = { 0,0 }, lq1 = { 0,0 }, rq1 = { 0,0 };
    Point lgen2 = { 0,0 }, rgen2 = { 0,0 }, lq2 = { 0,0 }, rq2 = { 0,0 };
    Point lgen = { 0,0 }, rgen = { 0,0 }, lq = { 0,0 }, rq = { 0,0 };
    int ctest = 0;
    float newThermalConst = 0;
    float Lnew = 0;
    float areaAfter = 0;
    float aspectRatioNew = 0;
    float maxArea = 0;
    float minArea = 0;
    float maxHpwl = 0;
    float minHpwl = 0;
    float maxThermal = 0;
    float minThermal = 0;
    float maxAspect = 0;
    float minAspect = 0;

    for (int i = 0; i < noOfModules; i++)
    {

        randnumx = rand() % xGrid;
        randnumy = rand() % yGrid;


        arrCoordenat[i][0] = randnumx;
        arrCoordenat[i][1] = randnumy;
    }
    // cout << endl << "arrCoordinates1=" << endl;
    // printArray(arrCoordenat, noOfModules, 2);

    for (int i = 0; i < 10000; i++) {

        ////////////// swap code///////////////////////////////////////////////////////////


        randModuleSelection1 = rand() % noOfModules;

        randomXForModule = rand() % xGrid;
        randomYForModule = rand() % yGrid;


        randomModuleSelectionX = arrCoordenat[randModuleSelection1][0];
        randomModuleSelectionY = arrCoordenat[randModuleSelection1][1];

        arrCoordenat[randModuleSelection1][0] = randomXForModule;
        arrCoordenat[randModuleSelection1][1] = randomYForModule;
        while (1) {
            ctest = 0;
            for (int q = 0; q < noOfModules; q++)
            {

                if (q != randModuleSelection1) {
                    lgen1 = { arrCoordenat[randModuleSelection1][0],arrCoordenat[randModuleSelection1][1] + arrModuleDimension[randModuleSelection1][1] };
                    rgen1 = { arrCoordenat[randModuleSelection1][0] + arrModuleDimension[randModuleSelection1][0] , arrCoordenat[randModuleSelection1][1] };
                    lq1 = { arrCoordenat[q][0],arrCoordenat[q][1] + arrModuleDimension[q][1] };
                    rq1 = { arrCoordenat[q][0] + arrModuleDimension[q][0] , arrCoordenat[q][1] };

                    if (doOverlap(lgen1, rgen1, lq1, rq1)) {
                        ctest++;
                    }
                }
            }
            if (ctest != 0)
            {
                randnumx = rand() % xGrid;
                randnumy = rand() % yGrid;

                arrCoordenat[randModuleSelection1][0] = randnumx;
                arrCoordenat[randModuleSelection1][1] = randnumy;
            }
            else {
                break;



            }

        }


        /////////////////////////////////////////////calculating new hpwl////////////////////////////////////////////////////
        mappingPinsToModules(arrMappedPinsCoordinates, arrPinNewCoordinates, arrCoordenat, pins);
        //  cout << endl << "arrCoordinates2=" << endl;
         // printArray(arrCoordenat,noOfModules,2);
         // cout << endl << "mapped pins" << endl;
         // printArray(arrMappedPinsCoordinates, pins, 4);

        Lnew = calculateSummitionHpwl(arrConnection, arrMappedPinsCoordinates, arrNetPinsCoordinates, netPriority, noOfModules, nets, pins);
        //  cout << endl << "Lnew = " << Lnew << endl;
        areaAfter = totalArea(arrCoordenat, arrModuleDimension, noOfModules);
        // cout << endl << "areaAfter = " << areaAfter << endl;
         ///////////////////////////////////////// calculating delta L///////////////////////////
        newThermalConst = (1 / ThermalDistanceConstrain(arrCoordenat, arrModuleDimension, arrCriticalModulesIndex, mCritical, 6));
        aspectRatioNew = aspectRatio(arrCoordenat, arrModuleDimension, noOfModules);

        if (i == 0) {
            arrMax[0][0] = Lnew; arrMax[0][1] = areaAfter; arrMax[0][2] = newThermalConst; arrMax[0][3] = aspectRatioNew;
            arrMin[0][0] = Lnew; arrMin[0][1] = areaAfter; arrMin[0][2] = newThermalConst; arrMin[0][3] = aspectRatioNew;
        }
        else
        {
            if (Lnew > arrMax[0][0]) { arrMax[0][0] = Lnew; }
            if (areaAfter > arrMax[0][1]) { arrMax[0][1] = areaAfter; }
            if (newThermalConst > arrMax[0][2]) { arrMax[0][2] = newThermalConst; }
            if (aspectRatioNew > arrMax[0][3]) { arrMax[0][3] = aspectRatioNew; }

            if (Lnew < arrMin[0][0]) { arrMin[0][0] = Lnew; }
            if (areaAfter < arrMin[0][1]) { arrMin[0][1] = areaAfter; }
            if (newThermalConst < arrMin[0][2]) { arrMin[0][2] = newThermalConst; }
            if (aspectRatioNew < arrMin[0][0]) { arrMin[0][0] = aspectRatioNew; }

        }
    }
    arrGetAverage[0][0] = Lnew / 10000; arrGetAverage[0][1] = areaAfter / 10000; arrGetAverage[0][2] = newThermalConst / 10000; arrGetAverage[0][3] = aspectRatioNew / 10000;
}

int findSmallestPatternShapesIndex(float** arrMinCostArrayAll, int mul) {

    float temp = arrMinCostArrayAll[0][0];
    int index = 0;
    for (int i = 0; i < mul; i++) {
        if (temp > arrMinCostArrayAll[i][0]) {
            temp = arrMinCostArrayAll[i][0];
            index = i;
        }
    }
    return index;
}

int main()
{
    SDL_Init(SDL_INIT_VIDEO);//initialize
    SDL_Window* window = SDL_CreateWindow("title", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 800, SDL_WINDOW_SHOWN);
    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, 0);

    SDL_RenderClear(renderer);

    /* initializr random seed*/

    srand(time(NULL));

    int noOfModules = 7;// number of modules   
    int mCritical = 4;
    int C = 2;
    int flag = 0;
    int flag2 = 0;
    int min;
    int max;
    int moduleIndex;
    int randnumx;
    int randnumy;
    int sumOfModuleWidth = 0;
    int sumOfModuleHieght = 0;
    int xGrid;
    int yGrid;
    int g = 0;
    int  randModuleSelection1;
    int  randModuleSelection2;

    /////////////////////////////////////////////////////////identfying arrays /////////////////////////////////////////////////////////////////////////////////////

    float** arrCoordenat;
    float** arrModuleDimensionAllShapes;
    float** arrModuleDimension;
    float** arrConnection;
    float** arrPinsCoordinates;
    float** arrMappedPinsCoordinates;
    float** arrNetPinsCoordinates;//msh hatenfa3 law 2el pin 2el wa7da waslah bekaza pin tanya 3ashan ana 3amelha 2,2 
    float** arrHpwl;
    float** arrMinCoordinatesArray;
    float** arrNetPinsCoordinatesSdl;
    float** arrDrawingConnection;
    float** arrPinNewCoordinates;
    float** arrCriticalModulesIndex;
    float** netPriority;
    float** arrNumberModulesShapes;
    float** arrGenerateCombinations;
    float** arrGetAverage;
    float** arrMax;
    float** arrMin;
    float** arrTraing; //array for patterns
    float** arrArea;
    float** arrLength;
    float** arrThermal;
    float** arrCoordinatesTrain;
    float** arrCostTraining;
    float** arrNumberPinShapes;
    float** arrGeneratePinCombinations;
    float** lengthOfPinsPattern;

    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    int arrHpwlnew[5] = { 0 };
    int arrModulesInConnectionCorrdinates[5][2];
    float maxX = 0; float minX = 10000; float maxY = 0; float minY = 10000; int Temp = 1000; int frozen = 0; double Lold = 0; double Lnew = 0;

    int swapTimes = 1000;/////// swap times per gate
    int deltaL = 0;

    int nets = 28;
    int pins = 56;

    int c = 0;
    int SOld = 0;
    // int g = 0;
    float Hpwl = 0;
    double areaBefore = 0;
    double areaAfter = 0;
    double aspectRatioOld = 0;
    double aspectRatioNew = 0;




    ///////////////////////////////////////////////////////changes if shapes changed ////////////////////////////////////////////////////////////////////////////


    int AllShapesNumber = 8;/// 2el mafrooooooooooood ageboh be2eny 2a3mel summition 3ala (kol module*no.of shapes beta3et 2el module dah)
    int AllPinsNumber = 116;

    //arrModuleDimensionAllShapes
    //arrPinsCoordinates


    ///////////////////////////////////////////////////////////////////////////////generating arrays //////////////////////////////////////////////////////////////////////////

    arrModuleDimensionAllShapes = generateArray(AllShapesNumber, 3);
    arrModuleDimension = generateArray(noOfModules, 2);
    arrCoordenat = generateArray(noOfModules, C);
    arrMinCoordinatesArray = generateArray(noOfModules, c);
    arrConnection = generateArray(nets, 4);
    arrPinsCoordinates = generateArray(AllPinsNumber, 5);
    arrMappedPinsCoordinates = generateArray(pins, 4);
    arrNetPinsCoordinates = generateArray(1, 2);//////////// 3ayez input leya howa 2el net 2el wa7da feha maximum kam pin
    arrNetPinsCoordinatesSdl = generateArray(2, 2);
    arrDrawingConnection = generateArray(nets, 4);
    arrPinNewCoordinates = generateArray(pins, 4);
    arrCriticalModulesIndex = generateArray(mCritical, 1);
    netPriority = generateArray(nets, 1);
    arrNumberModulesShapes = generateArray(noOfModules, 1);
    arrGetAverage = generateArray(1, 4);
    arrMax = generateArray(1, 4);
    arrMin = generateArray(1, 4);
    arrTraing = generateArray(1000, 3);
    arrArea = generateArray(1000, 1);
    arrLength = generateArray(1000, 1);
    arrThermal = generateArray(1000, 1);
    arrCoordinatesTrain = generateArray(1000, 14);
    arrCostTraining = generateArray(1000, 1);
    arrNumberPinShapes = generateArray(noOfModules, 1);
    // arrGenerateCombinations = generateArray(mul, noOfModules); //me3arafhaa ta7t 3ashan me7tag 2a7seb 2el mul mn el for loop abl ma3melaha generate

    //////////////////////////////////////////////////////////////////////////generating weights of cost function in traing array///////////////////////////////////

    for (int trainingIterations = 0; trainingIterations < 1000; trainingIterations++)
    {
        if (trainingIterations % 10 == 0)
        {
            for (int trainingInner = 0; trainingInner < 10; trainingInner++)
            {
                arrTraing[trainingIterations + trainingInner][0] = 0.1 + 0.1 * trainingInner;
                if (trainingIterations < 100)
                {
                    arrTraing[trainingIterations + trainingInner][1] = 0.1 + 0.1 * (trainingIterations / 10);
                }
                if (trainingIterations > 100)
                {
                    arrTraing[trainingIterations + trainingInner][1] = 0.1 + 0.1 * (trainingIterations / 10) - trainingIterations / 100;
                }
            }
        }
        if (trainingIterations % 100 == 0)
        {
            for (int trainingOuter = 0; trainingOuter < 100; trainingOuter++)
            {
                arrTraing[trainingIterations + trainingOuter][2] = 0.1 + 0.1 * (trainingIterations / 100);
            }
        }
    }

    //////////////////////////////////////////////////////////benesta5dem 2el array deh fe functoin " calculateSummitionHpwl "//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    for (int np = 0; np < nets; np++)netPriority[np][0] = 1;
    netPriority[0][0] = 30;
    netPriority[1][0] = 30;
    netPriority[2][0] = 30;
    netPriority[3][0] = 30;
    netPriority[4][0] = 30;
    netPriority[5][0] = 30;
    netPriority[6][0] = 30;
    netPriority[7][0] = 30;


    ///////////////////////////////////////////////////////////////////arrConnections(module1,module2,pin1,pin2)//////////////////////////////////////////////



    arrConnection[0][0] = 0; arrConnection[0][1] = 1; arrConnection[0][2] = 1; arrConnection[0][3] = 1;///C-D
    arrConnection[1][0] = 0; arrConnection[1][1] = 1; arrConnection[1][2] = 2; arrConnection[1][3] = 2;///C-D
    arrConnection[2][0] = 1; arrConnection[2][1] = 2; arrConnection[2][2] = 3; arrConnection[2][3] = 1;//D-E
    arrConnection[3][0] = 1; arrConnection[3][1] = 2; arrConnection[3][2] = 4; arrConnection[3][3] = 2;//D-E
    arrConnection[4][0] = 1; arrConnection[4][1] = 3; arrConnection[4][2] = 5; arrConnection[4][3] = 1;//D-F
    arrConnection[5][0] = 1; arrConnection[5][1] = 3; arrConnection[5][2] = 6; arrConnection[5][3] = 2;//D-F
    arrConnection[6][0] = 2; arrConnection[6][1] = 3; arrConnection[6][2] = 3; arrConnection[6][3] = 3;//E-F
    arrConnection[7][0] = 2; arrConnection[7][1] = 3; arrConnection[7][2] = 4; arrConnection[7][3] = 4;//E-F
    arrConnection[8][0] = 4; arrConnection[8][1] = 0; arrConnection[8][2] = 1; arrConnection[8][3] = 3;
    arrConnection[9][0] = 4; arrConnection[9][1] = 0; arrConnection[9][2] = 2; arrConnection[9][3] = 4;
    arrConnection[10][0] = 4; arrConnection[10][1] = 1; arrConnection[10][2] = 3; arrConnection[10][3] = 7;
    arrConnection[11][0] = 4; arrConnection[11][1] = 1; arrConnection[11][2] = 4; arrConnection[11][3] = 8;
    arrConnection[12][0] = 4; arrConnection[12][1] = 2; arrConnection[12][2] = 5; arrConnection[12][3] = 5;
    arrConnection[13][0] = 4; arrConnection[13][1] = 2; arrConnection[13][2] = 6; arrConnection[13][3] = 6;
    arrConnection[14][0] = 5; arrConnection[14][1] = 4; arrConnection[14][2] = 1; arrConnection[14][3] = 7;//B
    arrConnection[15][0] = 5; arrConnection[15][1] = 4; arrConnection[15][2] = 2; arrConnection[15][3] = 8;//B
    arrConnection[16][0] = 5; arrConnection[16][1] = 0; arrConnection[16][2] = 3; arrConnection[16][3] = 5;//B
    arrConnection[17][0] = 5; arrConnection[17][1] = 0; arrConnection[17][2] = 4; arrConnection[17][3] = 6;//B
    arrConnection[18][0] = 5; arrConnection[18][1] = 3; arrConnection[18][2] = 5; arrConnection[18][3] = 5;//B
    arrConnection[19][0] = 5; arrConnection[19][1] = 3; arrConnection[19][2] = 6; arrConnection[19][3] = 6;//B
    arrConnection[20][0] = 5; arrConnection[20][1] = 4; arrConnection[20][2] = 9; arrConnection[20][3] = 11;//B
    arrConnection[21][0] = 5; arrConnection[21][1] = 4; arrConnection[21][2] = 10; arrConnection[21][3] = 12;//B
    arrConnection[22][0] = 5; arrConnection[22][1] = 4; arrConnection[22][2] = 7; arrConnection[22][3] = 9;//B
    arrConnection[23][0] = 5; arrConnection[23][1] = 4; arrConnection[23][2] = 8; arrConnection[23][3] = 10;//B
    arrConnection[24][0] = 4; arrConnection[24][1] = 6; arrConnection[24][2] = 13; arrConnection[24][3] = 1;
    arrConnection[25][0] = 4; arrConnection[25][1] = 6; arrConnection[25][2] = 14; arrConnection[25][3] = 2;
    arrConnection[26][0] = 4; arrConnection[26][1] = 6; arrConnection[26][2] = 15; arrConnection[26][3] = 3;
    arrConnection[27][0] = 4; arrConnection[27][1] = 6; arrConnection[27][2] = 16; arrConnection[27][3] = 4;

    ////////////////////////////////////////////////////// arrNumberModulesShapes(no.of shapes of each module)///////////////////////////////////////////////////////////////////////////////////

    arrNumberModulesShapes[0][0] = 1;
    arrNumberModulesShapes[1][0] = 1;
    arrNumberModulesShapes[2][0] = 1;
    arrNumberModulesShapes[3][0] = 1;
    arrNumberModulesShapes[4][0] = 1;
    arrNumberModulesShapes[5][0] = 1;
    arrNumberModulesShapes[6][0] = 2;
    //////////////////////////////////////////for loop to calculate the number of modules combinations that can be generated////////////////////////////////////////////////////////////////////////////////
    int mul = 1;

    for (int i = 0; i < noOfModules; i++) {

        mul = mul * arrNumberModulesShapes[i][0];

    }


    arrGenerateCombinations = generateArray(mul, noOfModules);

    generateCombinations(arrNumberModulesShapes, arrGenerateCombinations, noOfModules, mul);

    cout << endl << "generated Combination of modules = " << endl;

    printArray(arrGenerateCombinations, mul, noOfModules);

    ////////////////////////////////////////////////////// arrNumberModulesShapes(no.of pin shapes of each module)///////////////////////////////////////////////////////////////////////////////////

    arrNumberPinShapes[0][0] = 1;
    arrNumberPinShapes[1][0] = 1;
    arrNumberPinShapes[2][0] = 1;
    arrNumberPinShapes[3][0] = 1;
    arrNumberPinShapes[4][0] = 4;
    arrNumberPinShapes[5][0] = 1;
    arrNumberPinShapes[6][0] = 2;

    //////////////////////////////////////////for loop to calculate the number of modules combinations that can be generated////////////////////////////////////////////////////////////////////////////////
    int mulPin = 1;

    for (int i = 0; i < noOfModules; i++) {

        mulPin = mulPin * arrNumberPinShapes[i][0];

    }


    arrGeneratePinCombinations = generateArray(mulPin, noOfModules);

    lengthOfPinsPattern = generateArray(mulPin, 1);

    generateCombinations(arrNumberPinShapes, arrGeneratePinCombinations, noOfModules, mulPin);
    cout << endl << "generated Combination of pins = " << endl;
    printArray(arrGeneratePinCombinations, mulPin, noOfModules);
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

    float** arrMinCoordinatesArrayAll;/////////////////////////// 3ameltelhaaa generate ta7t ba3d ma 3araft 2el mul
    arrMinCoordinatesArrayAll = generateArray(mul * noOfModules, 2);
    float** arrMinCostArrayAll;
    arrMinCostArrayAll = generateArray(mul, 1);
    float** arrMinAreaArrayAll;
    arrMinAreaArrayAll = generateArray(mul, 1);
    float** arrMinHpwlArrayAll;
    arrMinHpwlArrayAll = generateArray(mul, 1);
    float** arrMinAspectRatioArrayAll;
    arrMinAspectRatioArrayAll = generateArray(mul, 1);
    float** arrMinThermalDistanceArrayAll;
    arrMinThermalDistanceArrayAll = generateArray(mul, 1);
    float** arrMinIndexOfPinPatterns;
    arrMinIndexOfPinPatterns = generateArray(mulPin, 1);

    //////////////////////////////////////////////////////////////////arrModuleDimension(indexModule,width,hieght)////////////////////////////////////////



    arrModuleDimensionAllShapes[0][0] = 11; arrModuleDimensionAllShapes[0][1] = 5;  arrModuleDimensionAllShapes[0][2] = 5;
    //arrModuleDimensionAllShapes[1][0] = 12; arrModuleDimensionAllShapes[1][1] = 6;  arrModuleDimensionAllShapes[1][2] = 6;
    arrModuleDimensionAllShapes[1][0] = 21; arrModuleDimensionAllShapes[1][1] = 5;  arrModuleDimensionAllShapes[1][2] = 10;
    //arrModuleDimensionAllShapes[3][0] = 22; arrModuleDimensionAllShapes[3][1] = 5;  arrModuleDimensionAllShapes[3][2] = 15;
    arrModuleDimensionAllShapes[2][0] = 31; arrModuleDimensionAllShapes[2][1] = 5;  arrModuleDimensionAllShapes[2][2] = 10;
    arrModuleDimensionAllShapes[3][0] = 41; arrModuleDimensionAllShapes[3][1] = 5;  arrModuleDimensionAllShapes[3][2] = 20;
    arrModuleDimensionAllShapes[4][0] = 51; arrModuleDimensionAllShapes[4][1] = 30; arrModuleDimensionAllShapes[4][2] = 30;
    arrModuleDimensionAllShapes[5][0] = 61; arrModuleDimensionAllShapes[5][1] = 50; arrModuleDimensionAllShapes[5][2] = 20;
    arrModuleDimensionAllShapes[6][0] = 71; arrModuleDimensionAllShapes[6][1] = 10; arrModuleDimensionAllShapes[6][2] = 30;
    arrModuleDimensionAllShapes[7][0] = 72; arrModuleDimensionAllShapes[7][1] = 30; arrModuleDimensionAllShapes[7][2] = 10;
    ////////////////////////////////////////////////////////////////arrCriticalModulesIndex/////////////////////////////////////////////

    arrCriticalModulesIndex[0][0] = 0;
    arrCriticalModulesIndex[1][0] = 1;
    arrCriticalModulesIndex[2][0] = 2;
    arrCriticalModulesIndex[3][0] = 3;

    /////////////////////////////////////////////////////////////////arrPinsCoordinates(module,pin,x,y)//////////////////////////////////////////



    arrPinsCoordinates[0][0] = 11;  arrPinsCoordinates[0][1] = 1; arrPinsCoordinates[0][2] = 1.25; arrPinsCoordinates[0][3] = 0; arrPinsCoordinates[0][4] = 11;
    arrPinsCoordinates[1][0] = 11;  arrPinsCoordinates[1][1] = 2; arrPinsCoordinates[1][2] = 3.75; arrPinsCoordinates[1][3] = 0; arrPinsCoordinates[1][4] = 11;
    arrPinsCoordinates[2][0] = 11;  arrPinsCoordinates[2][1] = 3; arrPinsCoordinates[2][2] = 0; arrPinsCoordinates[2][3] = 3.75; arrPinsCoordinates[2][4] = 11;
    arrPinsCoordinates[3][0] = 11;  arrPinsCoordinates[3][1] = 4; arrPinsCoordinates[3][2] = 0; arrPinsCoordinates[3][3] = 1.25; arrPinsCoordinates[3][4] = 11;
    arrPinsCoordinates[4][0] = 11;  arrPinsCoordinates[4][1] = 5; arrPinsCoordinates[4][2] = 1.25; arrPinsCoordinates[4][3] = 5; arrPinsCoordinates[4][4] = 11;
    arrPinsCoordinates[5][0] = 11;  arrPinsCoordinates[5][1] = 6; arrPinsCoordinates[5][2] = 3.75; arrPinsCoordinates[5][3] = 5; arrPinsCoordinates[5][4] = 11;

    arrPinsCoordinates[6][0] = 21;  arrPinsCoordinates[6][1] = 1; arrPinsCoordinates[6][2] = 1.25; arrPinsCoordinates[6][3] = 10; arrPinsCoordinates[6][4] = 21;
    arrPinsCoordinates[7][0] = 21;  arrPinsCoordinates[7][1] = 2; arrPinsCoordinates[7][2] = 3.75; arrPinsCoordinates[7][3] = 10; arrPinsCoordinates[7][4] = 21;
    arrPinsCoordinates[8][0] = 21;  arrPinsCoordinates[8][1] = 3; arrPinsCoordinates[8][2] = 1.25; arrPinsCoordinates[8][3] = 0;  arrPinsCoordinates[8][4] = 21;
    arrPinsCoordinates[9][0] = 21;  arrPinsCoordinates[9][1] = 4; arrPinsCoordinates[9][2] = 3.75; arrPinsCoordinates[9][3] = 0;  arrPinsCoordinates[9][4] = 21;
    arrPinsCoordinates[10][0] = 21;  arrPinsCoordinates[10][1] = 5; arrPinsCoordinates[10][2] = 5; arrPinsCoordinates[10][3] = 7.5; arrPinsCoordinates[10][4] = 21;
    arrPinsCoordinates[11][0] = 21;  arrPinsCoordinates[11][1] = 6; arrPinsCoordinates[11][2] = 5; arrPinsCoordinates[11][3] = 2.5; arrPinsCoordinates[11][4] = 21;
    arrPinsCoordinates[12][0] = 21;  arrPinsCoordinates[12][1] = 7; arrPinsCoordinates[12][2] = 0; arrPinsCoordinates[12][3] = 7.5; arrPinsCoordinates[12][4] = 21;
    arrPinsCoordinates[13][0] = 21;  arrPinsCoordinates[13][1] = 8; arrPinsCoordinates[13][2] = 0; arrPinsCoordinates[13][3] = 2.5; arrPinsCoordinates[13][4] = 21;

    arrPinsCoordinates[14][0] = 31;  arrPinsCoordinates[14][1] = 1; arrPinsCoordinates[14][2] = 1.25; arrPinsCoordinates[14][3] = 10; arrPinsCoordinates[14][4] = 31;
    arrPinsCoordinates[15][0] = 31;  arrPinsCoordinates[15][1] = 2; arrPinsCoordinates[15][2] = 3.75; arrPinsCoordinates[15][3] = 10; arrPinsCoordinates[15][4] = 31;
    arrPinsCoordinates[16][0] = 31;  arrPinsCoordinates[16][1] = 3; arrPinsCoordinates[16][2] = 5; arrPinsCoordinates[16][3] = 7.5;   arrPinsCoordinates[16][4] = 31;
    arrPinsCoordinates[17][0] = 31;  arrPinsCoordinates[17][1] = 4; arrPinsCoordinates[17][2] = 5; arrPinsCoordinates[17][3] = 2.5;   arrPinsCoordinates[17][4] = 31;
    arrPinsCoordinates[18][0] = 31;  arrPinsCoordinates[18][1] = 5; arrPinsCoordinates[18][2] = 0; arrPinsCoordinates[18][3] = 7.5;   arrPinsCoordinates[18][4] = 31;
    arrPinsCoordinates[19][0] = 31;  arrPinsCoordinates[19][1] = 6; arrPinsCoordinates[19][2] = 0; arrPinsCoordinates[19][3] = 2.5;   arrPinsCoordinates[19][4] = 31;


    arrPinsCoordinates[20][0] = 41;  arrPinsCoordinates[20][1] = 1; arrPinsCoordinates[20][2] = 0; arrPinsCoordinates[20][3] = 17.5; arrPinsCoordinates[20][4] = 41;
    arrPinsCoordinates[21][0] = 41;  arrPinsCoordinates[21][1] = 2; arrPinsCoordinates[21][2] = 0; arrPinsCoordinates[21][3] = 12.5; arrPinsCoordinates[21][4] = 41;
    arrPinsCoordinates[22][0] = 41;  arrPinsCoordinates[22][1] = 3; arrPinsCoordinates[22][2] = 0; arrPinsCoordinates[22][3] = 7.5;  arrPinsCoordinates[22][4] = 41;
    arrPinsCoordinates[23][0] = 41;  arrPinsCoordinates[23][1] = 4; arrPinsCoordinates[23][2] = 0; arrPinsCoordinates[23][3] = 2.5;  arrPinsCoordinates[23][4] = 41;
    arrPinsCoordinates[24][0] = 41;  arrPinsCoordinates[24][1] = 5; arrPinsCoordinates[24][2] = 1.25; arrPinsCoordinates[24][3] = 20; arrPinsCoordinates[24][4] = 41;
    arrPinsCoordinates[25][0] = 41;  arrPinsCoordinates[25][1] = 6; arrPinsCoordinates[25][2] = 3.75; arrPinsCoordinates[25][3] = 20; arrPinsCoordinates[25][4] = 41;

    arrPinsCoordinates[26][0] = 51;  arrPinsCoordinates[26][1] = 1; arrPinsCoordinates[26][2] = 30;   arrPinsCoordinates[26][3] = 27.5; arrPinsCoordinates[26][4] = 51;
    arrPinsCoordinates[27][0] = 51;  arrPinsCoordinates[27][1] = 2; arrPinsCoordinates[27][2] = 30;   arrPinsCoordinates[27][3] = 22.5; arrPinsCoordinates[27][4] = 51;
    arrPinsCoordinates[28][0] = 51;  arrPinsCoordinates[28][1] = 3; arrPinsCoordinates[28][2] = 30;   arrPinsCoordinates[28][3] = 17.5; arrPinsCoordinates[28][4] = 51;
    arrPinsCoordinates[29][0] = 51;  arrPinsCoordinates[29][1] = 4; arrPinsCoordinates[29][2] = 30;   arrPinsCoordinates[29][3] = 12.5; arrPinsCoordinates[29][4] = 51;
    arrPinsCoordinates[30][0] = 51;  arrPinsCoordinates[30][1] = 5; arrPinsCoordinates[30][2] = 30;   arrPinsCoordinates[30][3] = 7.5;  arrPinsCoordinates[30][4] = 51;
    arrPinsCoordinates[31][0] = 51;  arrPinsCoordinates[31][1] = 6; arrPinsCoordinates[31][2] = 30;   arrPinsCoordinates[31][3] = 2.5;  arrPinsCoordinates[31][4] = 51;
    arrPinsCoordinates[32][0] = 51;  arrPinsCoordinates[32][1] = 7; arrPinsCoordinates[32][2] = 12.5; arrPinsCoordinates[32][3] = 30;   arrPinsCoordinates[32][4] = 51;
    arrPinsCoordinates[33][0] = 51;  arrPinsCoordinates[33][1] = 8; arrPinsCoordinates[33][2] = 17.5; arrPinsCoordinates[33][3] = 30;   arrPinsCoordinates[33][4] = 51;
    arrPinsCoordinates[34][0] = 51;  arrPinsCoordinates[34][1] = 9; arrPinsCoordinates[34][2] = 22.5; arrPinsCoordinates[34][3] = 30;   arrPinsCoordinates[34][4] = 51;
    arrPinsCoordinates[35][0] = 51;  arrPinsCoordinates[35][1] = 10; arrPinsCoordinates[35][2] = 27.5; arrPinsCoordinates[35][3] = 30;  arrPinsCoordinates[35][4] = 51;
    arrPinsCoordinates[36][0] = 51;  arrPinsCoordinates[36][1] = 11; arrPinsCoordinates[36][2] = 2.5; arrPinsCoordinates[36][3] = 30;   arrPinsCoordinates[36][4] = 51;
    arrPinsCoordinates[37][0] = 51;  arrPinsCoordinates[37][1] = 12; arrPinsCoordinates[37][2] = 7.5; arrPinsCoordinates[37][3] = 30;   arrPinsCoordinates[37][4] = 51;
    arrPinsCoordinates[38][0] = 51;  arrPinsCoordinates[38][1] = 13; arrPinsCoordinates[38][2] = 6; arrPinsCoordinates[38][3] = 0;      arrPinsCoordinates[38][4] = 51;
    arrPinsCoordinates[39][0] = 51;  arrPinsCoordinates[39][1] = 14; arrPinsCoordinates[39][2] = 12; arrPinsCoordinates[39][3] = 0;     arrPinsCoordinates[39][4] = 51;
    arrPinsCoordinates[40][0] = 51;  arrPinsCoordinates[40][1] = 15; arrPinsCoordinates[40][2] = 18; arrPinsCoordinates[40][3] = 0;     arrPinsCoordinates[40][4] = 51;
    arrPinsCoordinates[41][0] = 51;  arrPinsCoordinates[41][1] = 16; arrPinsCoordinates[41][2] = 24; arrPinsCoordinates[41][3] = 0;     arrPinsCoordinates[41][4] = 51;

    arrPinsCoordinates[42][0] = 61;  arrPinsCoordinates[42][1] = 1; arrPinsCoordinates[42][2] = 12.5; arrPinsCoordinates[42][3] = 0; arrPinsCoordinates[42][4] = 61;
    arrPinsCoordinates[43][0] = 61;  arrPinsCoordinates[43][1] = 2; arrPinsCoordinates[43][2] = 17.5; arrPinsCoordinates[43][3] = 0; arrPinsCoordinates[43][4] = 61;
    arrPinsCoordinates[44][0] = 61;  arrPinsCoordinates[44][1] = 3; arrPinsCoordinates[44][2] = 32.5; arrPinsCoordinates[44][3] = 0; arrPinsCoordinates[44][4] = 61;
    arrPinsCoordinates[45][0] = 61;  arrPinsCoordinates[45][1] = 4; arrPinsCoordinates[45][2] = 37.5; arrPinsCoordinates[45][3] = 0; arrPinsCoordinates[45][4] = 61;
    arrPinsCoordinates[46][0] = 61;  arrPinsCoordinates[46][1] = 5; arrPinsCoordinates[46][2] = 42.5; arrPinsCoordinates[46][3] = 0; arrPinsCoordinates[46][4] = 61;
    arrPinsCoordinates[47][0] = 61;  arrPinsCoordinates[47][1] = 6; arrPinsCoordinates[47][2] = 47.5; arrPinsCoordinates[47][3] = 0; arrPinsCoordinates[47][4] = 61;
    arrPinsCoordinates[48][0] = 61;  arrPinsCoordinates[48][1] = 7; arrPinsCoordinates[48][2] = 22.5; arrPinsCoordinates[48][3] = 0; arrPinsCoordinates[48][4] = 61;
    arrPinsCoordinates[49][0] = 61;  arrPinsCoordinates[49][1] = 8; arrPinsCoordinates[49][2] = 27.5; arrPinsCoordinates[49][3] = 0; arrPinsCoordinates[49][4] = 61;
    arrPinsCoordinates[50][0] = 61;  arrPinsCoordinates[50][1] = 9; arrPinsCoordinates[50][2] = 2.5;  arrPinsCoordinates[50][3] = 0; arrPinsCoordinates[50][4] = 61;
    arrPinsCoordinates[51][0] = 61;  arrPinsCoordinates[51][1] = 10; arrPinsCoordinates[51][2] = 7.5;  arrPinsCoordinates[51][3] = 0; arrPinsCoordinates[51][4] = 61;



    /* arrPinsCoordinates[48][0] = 12;  arrPinsCoordinates[48][1] = 1; arrPinsCoordinates[48][2] = 1; arrPinsCoordinates[48][3] = 0;
     arrPinsCoordinates[49][0] = 12;  arrPinsCoordinates[49][1] = 2; arrPinsCoordinates[49][2] = 4; arrPinsCoordinates[49][3] = 0;
     arrPinsCoordinates[50][0] = 12;  arrPinsCoordinates[50][1] = 3; arrPinsCoordinates[50][2] = 0; arrPinsCoordinates[50][3] = 4;
     arrPinsCoordinates[51][0] = 12;  arrPinsCoordinates[51][1] = 4; arrPinsCoordinates[51][2] = 0; arrPinsCoordinates[51][3] = 1;
     arrPinsCoordinates[52][0] = 12;  arrPinsCoordinates[52][1] = 5; arrPinsCoordinates[52][2] = 1; arrPinsCoordinates[52][3] = 6;
     arrPinsCoordinates[53][0] = 12;  arrPinsCoordinates[53][1] = 6; arrPinsCoordinates[53][2] = 4; arrPinsCoordinates[53][3] = 6;


     arrPinsCoordinates[54][0] = 22;  arrPinsCoordinates[54][1] = 1; arrPinsCoordinates[54][2] = 1.25; arrPinsCoordinates[54][3] = 15;
     arrPinsCoordinates[55][0] = 22;  arrPinsCoordinates[55][1] = 2; arrPinsCoordinates[55][2] = 3.75; arrPinsCoordinates[55][3] = 15;
     arrPinsCoordinates[56][0] = 22;  arrPinsCoordinates[56][1] = 3; arrPinsCoordinates[56][2] = 1.25; arrPinsCoordinates[56][3] = 0;
     arrPinsCoordinates[57][0] = 22;  arrPinsCoordinates[57][1] = 4; arrPinsCoordinates[57][2] = 3.75; arrPinsCoordinates[57][3] = 0;
     arrPinsCoordinates[58][0] = 22;  arrPinsCoordinates[58][1] = 5; arrPinsCoordinates[58][2] = 5;    arrPinsCoordinates[58][3] = 10;
     arrPinsCoordinates[59][0] = 22;  arrPinsCoordinates[59][1] = 6; arrPinsCoordinates[59][2] = 5;    arrPinsCoordinates[59][3] = 2.5;
     arrPinsCoordinates[60][0] = 22;  arrPinsCoordinates[60][1] = 7; arrPinsCoordinates[60][2] = 0;    arrPinsCoordinates[60][3] = 10;
     arrPinsCoordinates[61][0] = 22;  arrPinsCoordinates[61][1] = 8; arrPinsCoordinates[61][2] = 0;    arrPinsCoordinates[61][3] = 2.5;
     */


     /* arrPinsCoordinates[62][0] = 71;  arrPinsCoordinates[62][1] = 1; arrPinsCoordinates[62][2] = 10 ; arrPinsCoordinates[62][3] = 6;
      arrPinsCoordinates[63][0] = 71;  arrPinsCoordinates[63][1] = 2; arrPinsCoordinates[63][2] = 10;  arrPinsCoordinates[63][3] = 12;
      arrPinsCoordinates[64][0] = 71;  arrPinsCoordinates[64][1] = 3; arrPinsCoordinates[64][2] = 10;  arrPinsCoordinates[64][3] = 18;
      arrPinsCoordinates[65][0] = 71;  arrPinsCoordinates[65][1] = 4; arrPinsCoordinates[65][2] = 10;  arrPinsCoordinates[65][3] = 24; */

    arrPinsCoordinates[52][0] = 71;  arrPinsCoordinates[52][1] = 1; arrPinsCoordinates[52][2] = 10;  arrPinsCoordinates[52][3] = 6; arrPinsCoordinates[52][4] = 71;
    arrPinsCoordinates[53][0] = 71;  arrPinsCoordinates[53][1] = 2; arrPinsCoordinates[53][2] = 10;  arrPinsCoordinates[53][3] = 12; arrPinsCoordinates[53][4] = 71;
    arrPinsCoordinates[54][0] = 71;  arrPinsCoordinates[54][1] = 3; arrPinsCoordinates[54][2] = 10;  arrPinsCoordinates[54][3] = 18; arrPinsCoordinates[54][4] = 71;
    arrPinsCoordinates[55][0] = 71;  arrPinsCoordinates[55][1] = 4; arrPinsCoordinates[55][2] = 10;  arrPinsCoordinates[55][3] = 24; arrPinsCoordinates[55][4] = 71;

    arrPinsCoordinates[56][0] = 72;  arrPinsCoordinates[56][1] = 1; arrPinsCoordinates[56][2] = 6;  arrPinsCoordinates[56][3] = 0; arrPinsCoordinates[56][4] = 71;
    arrPinsCoordinates[57][0] = 72;  arrPinsCoordinates[57][1] = 2; arrPinsCoordinates[57][2] = 12;  arrPinsCoordinates[57][3] = 0; arrPinsCoordinates[57][4] = 71;
    arrPinsCoordinates[58][0] = 72;  arrPinsCoordinates[58][1] = 3; arrPinsCoordinates[58][2] = 18;  arrPinsCoordinates[58][3] = 0; arrPinsCoordinates[58][4] = 71;
    arrPinsCoordinates[59][0] = 72;  arrPinsCoordinates[59][1] = 4; arrPinsCoordinates[59][2] = 24;  arrPinsCoordinates[59][3] = 0; arrPinsCoordinates[59][4] = 71;
    ////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
    arrPinsCoordinates[60][0] = 72;  arrPinsCoordinates[60][1] = 1; arrPinsCoordinates[60][2] = 6;  arrPinsCoordinates[60][3] = 10; arrPinsCoordinates[60][4] = 72;
    arrPinsCoordinates[61][0] = 72;  arrPinsCoordinates[61][1] = 2; arrPinsCoordinates[61][2] = 12;  arrPinsCoordinates[61][3] = 10; arrPinsCoordinates[61][4] = 72;
    arrPinsCoordinates[62][0] = 72;  arrPinsCoordinates[62][1] = 3; arrPinsCoordinates[62][2] = 18;  arrPinsCoordinates[62][3] = 10; arrPinsCoordinates[62][4] = 72;
    arrPinsCoordinates[63][0] = 72;  arrPinsCoordinates[63][1] = 4; arrPinsCoordinates[63][2] = 24;  arrPinsCoordinates[63][3] = 10; arrPinsCoordinates[63][4] = 72;

    arrPinsCoordinates[64][0] = 71;  arrPinsCoordinates[64][1] = 1; arrPinsCoordinates[64][2] = 0;  arrPinsCoordinates[64][3] = 6; arrPinsCoordinates[64][4] = 72;
    arrPinsCoordinates[65][0] = 71;  arrPinsCoordinates[65][1] = 2; arrPinsCoordinates[65][2] = 0;  arrPinsCoordinates[65][3] = 12; arrPinsCoordinates[65][4] = 72;
    arrPinsCoordinates[66][0] = 71;  arrPinsCoordinates[66][1] = 3; arrPinsCoordinates[66][2] = 0;  arrPinsCoordinates[66][3] = 18; arrPinsCoordinates[66][4] = 72;
    arrPinsCoordinates[67][0] = 71;  arrPinsCoordinates[67][1] = 4; arrPinsCoordinates[67][2] = 0;  arrPinsCoordinates[67][3] = 24; arrPinsCoordinates[67][4] = 72;

    arrPinsCoordinates[68][0] = 51;  arrPinsCoordinates[68][1] = 1; arrPinsCoordinates[68][2] = 0;   arrPinsCoordinates[68][3] = 27.5; arrPinsCoordinates[68][4] = 52;
    arrPinsCoordinates[69][0] = 51;  arrPinsCoordinates[69][1] = 2; arrPinsCoordinates[69][2] = 0;   arrPinsCoordinates[69][3] = 22.5; arrPinsCoordinates[69][4] = 52;
    arrPinsCoordinates[70][0] = 51;  arrPinsCoordinates[70][1] = 3; arrPinsCoordinates[70][2] = 0;   arrPinsCoordinates[70][3] = 17.5; arrPinsCoordinates[70][4] = 52;
    arrPinsCoordinates[71][0] = 51;  arrPinsCoordinates[71][1] = 4; arrPinsCoordinates[71][2] = 0;   arrPinsCoordinates[71][3] = 12.5; arrPinsCoordinates[71][4] = 52;
    arrPinsCoordinates[72][0] = 51;  arrPinsCoordinates[72][1] = 5; arrPinsCoordinates[72][2] = 0;   arrPinsCoordinates[72][3] = 7.5;  arrPinsCoordinates[72][4] = 52;
    arrPinsCoordinates[73][0] = 51;  arrPinsCoordinates[73][1] = 6; arrPinsCoordinates[73][2] = 0;   arrPinsCoordinates[73][3] = 2.5;  arrPinsCoordinates[73][4] = 52;
    arrPinsCoordinates[74][0] = 51;  arrPinsCoordinates[74][1] = 7; arrPinsCoordinates[74][2] = 12.5; arrPinsCoordinates[74][3] = 30;   arrPinsCoordinates[74][4] = 52;
    arrPinsCoordinates[75][0] = 51;  arrPinsCoordinates[75][1] = 8; arrPinsCoordinates[75][2] = 17.5; arrPinsCoordinates[75][3] = 30;   arrPinsCoordinates[75][4] = 52;
    arrPinsCoordinates[76][0] = 51;  arrPinsCoordinates[76][1] = 9; arrPinsCoordinates[76][2] = 22.5; arrPinsCoordinates[76][3] = 30;   arrPinsCoordinates[76][4] = 52;
    arrPinsCoordinates[77][0] = 51;  arrPinsCoordinates[77][1] = 10; arrPinsCoordinates[77][2] = 27.5; arrPinsCoordinates[77][3] = 30;   arrPinsCoordinates[77][4] = 52;
    arrPinsCoordinates[78][0] = 51;  arrPinsCoordinates[78][1] = 11; arrPinsCoordinates[78][2] = 2.5; arrPinsCoordinates[78][3] = 30;   arrPinsCoordinates[78][4] = 52;
    arrPinsCoordinates[79][0] = 51;  arrPinsCoordinates[79][1] = 12; arrPinsCoordinates[79][2] = 7.5; arrPinsCoordinates[79][3] = 30;   arrPinsCoordinates[79][4] = 52;
    arrPinsCoordinates[80][0] = 51;  arrPinsCoordinates[80][1] = 13; arrPinsCoordinates[80][2] = 6;   arrPinsCoordinates[80][3] = 0;    arrPinsCoordinates[80][4] = 52;
    arrPinsCoordinates[81][0] = 51;  arrPinsCoordinates[81][1] = 14; arrPinsCoordinates[81][2] = 12;  arrPinsCoordinates[81][3] = 0;    arrPinsCoordinates[81][4] = 52;
    arrPinsCoordinates[82][0] = 51;  arrPinsCoordinates[82][1] = 15; arrPinsCoordinates[82][2] = 18;  arrPinsCoordinates[82][3] = 0;    arrPinsCoordinates[82][4] = 52;
    arrPinsCoordinates[83][0] = 51;  arrPinsCoordinates[83][1] = 16; arrPinsCoordinates[83][2] = 24;  arrPinsCoordinates[83][3] = 0;    arrPinsCoordinates[83][4] = 52;

    arrPinsCoordinates[84][0] = 51;  arrPinsCoordinates[84][1] = 1; arrPinsCoordinates[84][2] = 30;   arrPinsCoordinates[84][3] = 27.5; arrPinsCoordinates[84][4] = 53;
    arrPinsCoordinates[85][0] = 51;  arrPinsCoordinates[85][1] = 2; arrPinsCoordinates[85][2] = 30;   arrPinsCoordinates[85][3] = 22.5; arrPinsCoordinates[85][4] = 53;
    arrPinsCoordinates[86][0] = 51;  arrPinsCoordinates[86][1] = 3; arrPinsCoordinates[86][2] = 30;   arrPinsCoordinates[86][3] = 17.5; arrPinsCoordinates[86][4] = 53;
    arrPinsCoordinates[87][0] = 51;  arrPinsCoordinates[87][1] = 4; arrPinsCoordinates[87][2] = 30;   arrPinsCoordinates[87][3] = 12.5; arrPinsCoordinates[87][4] = 53;
    arrPinsCoordinates[88][0] = 51;  arrPinsCoordinates[88][1] = 5; arrPinsCoordinates[88][2] = 30;   arrPinsCoordinates[88][3] = 7.5;  arrPinsCoordinates[88][4] = 53;
    arrPinsCoordinates[89][0] = 51;  arrPinsCoordinates[89][1] = 6; arrPinsCoordinates[89][2] = 30;   arrPinsCoordinates[89][3] = 2.5;  arrPinsCoordinates[89][4] = 53;
    arrPinsCoordinates[90][0] = 51;  arrPinsCoordinates[90][1] = 7; arrPinsCoordinates[90][2] = 12.5; arrPinsCoordinates[90][3] = 0;   arrPinsCoordinates[90][4] = 53;
    arrPinsCoordinates[91][0] = 51;  arrPinsCoordinates[91][1] = 8; arrPinsCoordinates[91][2] = 17.5; arrPinsCoordinates[91][3] = 0;   arrPinsCoordinates[91][4] = 53;
    arrPinsCoordinates[92][0] = 51;  arrPinsCoordinates[92][1] = 9; arrPinsCoordinates[92][2] = 22.5; arrPinsCoordinates[92][3] = 0;   arrPinsCoordinates[92][4] = 53;
    arrPinsCoordinates[93][0] = 51;  arrPinsCoordinates[93][1] = 10; arrPinsCoordinates[93][2] = 27.5; arrPinsCoordinates[93][3] = 0;  arrPinsCoordinates[93][4] = 53;
    arrPinsCoordinates[94][0] = 51;  arrPinsCoordinates[94][1] = 11; arrPinsCoordinates[94][2] = 2.5; arrPinsCoordinates[94][3] = 0;   arrPinsCoordinates[94][4] = 53;
    arrPinsCoordinates[95][0] = 51;  arrPinsCoordinates[95][1] = 12; arrPinsCoordinates[95][2] = 7.5; arrPinsCoordinates[95][3] = 0;   arrPinsCoordinates[95][4] = 53;
    arrPinsCoordinates[96][0] = 51;  arrPinsCoordinates[96][1] = 13; arrPinsCoordinates[96][2] = 6; arrPinsCoordinates[96][3] = 30;      arrPinsCoordinates[96][4] = 53;
    arrPinsCoordinates[97][0] = 51;  arrPinsCoordinates[97][1] = 14; arrPinsCoordinates[97][2] = 12; arrPinsCoordinates[97][3] = 30;     arrPinsCoordinates[97][4] = 53;
    arrPinsCoordinates[98][0] = 51;  arrPinsCoordinates[98][1] = 15; arrPinsCoordinates[98][2] = 18; arrPinsCoordinates[98][3] = 30;     arrPinsCoordinates[98][4] = 53;
    arrPinsCoordinates[99][0] = 51;  arrPinsCoordinates[99][1] = 16; arrPinsCoordinates[99][2] = 24; arrPinsCoordinates[99][3] = 30;     arrPinsCoordinates[99][4] = 53;

    arrPinsCoordinates[100][0] = 51;  arrPinsCoordinates[100][1] = 1; arrPinsCoordinates[100][2] = 0;   arrPinsCoordinates[100][3] = 27.5; arrPinsCoordinates[100][4] = 54;
    arrPinsCoordinates[101][0] = 51;  arrPinsCoordinates[101][1] = 2; arrPinsCoordinates[101][2] = 0;   arrPinsCoordinates[101][3] = 22.5; arrPinsCoordinates[101][4] = 54;
    arrPinsCoordinates[102][0] = 51;  arrPinsCoordinates[102][1] = 3; arrPinsCoordinates[102][2] = 0;   arrPinsCoordinates[102][3] = 17.5; arrPinsCoordinates[102][4] = 54;
    arrPinsCoordinates[103][0] = 51;  arrPinsCoordinates[103][1] = 4; arrPinsCoordinates[103][2] = 0;   arrPinsCoordinates[103][3] = 12.5; arrPinsCoordinates[103][4] = 54;
    arrPinsCoordinates[104][0] = 51;  arrPinsCoordinates[104][1] = 5; arrPinsCoordinates[104][2] = 0;   arrPinsCoordinates[104][3] = 7.5;  arrPinsCoordinates[104][4] = 54;
    arrPinsCoordinates[105][0] = 51;  arrPinsCoordinates[105][1] = 6; arrPinsCoordinates[105][2] = 0;   arrPinsCoordinates[105][3] = 2.5;  arrPinsCoordinates[105][4] = 54;
    arrPinsCoordinates[106][0] = 51;  arrPinsCoordinates[106][1] = 7; arrPinsCoordinates[106][2] = 12.5; arrPinsCoordinates[106][3] = 0;   arrPinsCoordinates[106][4] = 54;
    arrPinsCoordinates[107][0] = 51;  arrPinsCoordinates[107][1] = 8; arrPinsCoordinates[107][2] = 17.5; arrPinsCoordinates[107][3] = 0;   arrPinsCoordinates[107][4] = 54;
    arrPinsCoordinates[108][0] = 51;  arrPinsCoordinates[108][1] = 9; arrPinsCoordinates[108][2] = 22.5; arrPinsCoordinates[108][3] = 0;   arrPinsCoordinates[108][4] = 54;
    arrPinsCoordinates[109][0] = 51;  arrPinsCoordinates[109][1] = 10; arrPinsCoordinates[109][2] = 27.5; arrPinsCoordinates[109][3] = 0;  arrPinsCoordinates[109][4] = 54;
    arrPinsCoordinates[110][0] = 51;  arrPinsCoordinates[110][1] = 11; arrPinsCoordinates[110][2] = 2.5; arrPinsCoordinates[110][3] = 0;   arrPinsCoordinates[110][4] = 54;
    arrPinsCoordinates[111][0] = 51;  arrPinsCoordinates[111][1] = 12; arrPinsCoordinates[111][2] = 7.5; arrPinsCoordinates[111][3] = 0;   arrPinsCoordinates[111][4] = 54;
    arrPinsCoordinates[112][0] = 51;  arrPinsCoordinates[112][1] = 13; arrPinsCoordinates[112][2] = 6; arrPinsCoordinates[112][3] = 30;    arrPinsCoordinates[112][4] = 54;
    arrPinsCoordinates[113][0] = 51;  arrPinsCoordinates[113][1] = 14; arrPinsCoordinates[113][2] = 12; arrPinsCoordinates[113][3] = 30;   arrPinsCoordinates[113][4] = 54;
    arrPinsCoordinates[114][0] = 51;  arrPinsCoordinates[114][1] = 15; arrPinsCoordinates[114][2] = 18; arrPinsCoordinates[114][3] = 30;   arrPinsCoordinates[114][4] = 54;
    arrPinsCoordinates[115][0] = 51;  arrPinsCoordinates[115][1] = 16; arrPinsCoordinates[115][2] = 24; arrPinsCoordinates[115][3] = 30;   arrPinsCoordinates[115][4] = 54;



    //////////////////////////////////////////// Code beginning //////////////////////////////////////////////////////////////////////////////////////////////////
    int U = 0, z = 0;
    double Lnorm, Anorm, Tnorm, ASPnorm;
    double Lnormn, Anormn, Tnormn, ASPnormn;
    float minSol;
    double areaMin;
    float Lmin;
    float chosenThermalConst;
    float chosenAspectRatio;
    int randomModuleSelectionX; int randomModuleSelectionY; float overlapTerm; double costNew; double deltaCost;
    float randomXForModule; float randomYForModule;
    float Lavg;
    float Aavg;
    float Tavg;
    float c1 = 0;
    float c2 = 0;
    float c3 = 1;
    int indexLengthPattern;
    int minIndexLengthPattern;

    for (int w = 0; w < mul; w++)
    {
        sumOfModuleWidth = 0;
        sumOfModuleHieght = 0;

        convertArraysModuleDimensions(arrModuleDimensionAllShapes, arrGenerateCombinations, arrModuleDimension, noOfModules, AllShapesNumber, w);

        for (int i = 0; i < 1; i++) {

            convertArraysPinCoordinates(arrGeneratePinCombinations, arrGenerateCombinations, arrPinsCoordinates, arrPinNewCoordinates, noOfModules, AllPinsNumber, w, i);

        }


        cout << endl << "arrPinNewCoordinates = " << endl;

        printArray(arrPinNewCoordinates, pins, 4);
        //printArray(arrModuleDimension, noOfModules, 2);

        for (int i = 0; i < noOfModules; i++) {

            sumOfModuleWidth = sumOfModuleWidth + arrModuleDimension[i][0];
            sumOfModuleHieght = sumOfModuleHieght + arrModuleDimension[i][1];

        }
        xGrid = 0.75 * sumOfModuleWidth;//xGrid in micro
        yGrid = 0.75 * sumOfModuleHieght;//yGrid in micro

        perturbeToCalculateNormalizationValuesAreaHpwlThermalconstAspect(arrMax, arrMin, arrGetAverage, arrCriticalModulesIndex, netPriority, arrNetPinsCoordinates, arrMappedPinsCoordinates, arrPinNewCoordinates, arrConnection, arrCoordenat, arrModuleDimension, xGrid, yGrid, noOfModules, nets, pins, mCritical);
        float costCompare = 0;

        for (int t = 0; t < 2; t++) {


            //////////////////////////////////////////////intializing the array of coordinates with random values////////////////////////////

            for (int i = 0; i < noOfModules; i++)
            {

                randnumx = rand() % xGrid;
                randnumy = rand() % yGrid;


                arrCoordenat[i][0] = randnumx;
                arrCoordenat[i][1] = randnumy;


            }



            ///////////////////////////////////////////////drawing initial random placement///////////////////////////////////////////////////
            for (int xm = 0; xm < noOfModules; xm++)
            {
                dramRectangle(renderer, arrCoordenat[xm][0], arrCoordenat[xm][1], arrModuleDimension[xm][0], arrModuleDimension[xm][1]);
            }

            SDL_Delay(1000);
            SDL_RenderClear(renderer);
            //////////////////////////////////////////////////////Mapping the pins of the modules to the real coordinates ////////////////////////////////

            mappingPinsToModules(arrMappedPinsCoordinates, arrPinNewCoordinates, arrCoordenat, pins);

            ////////////////////////////////////////////////calculating Hpwl before simulated annealing ///////////////////////////////////////////////////////////////////

            Lold = (double)calculateSummitionHpwl(arrConnection, arrMappedPinsCoordinates, arrNetPinsCoordinates, netPriority, noOfModules, nets, pins);


            /////////////////////////////////////////////////////////////calculating total area before simulated annealing ////////////////////////////////////////

            areaBefore = (double)totalArea(arrCoordenat, arrModuleDimension, noOfModules);

            /////////////////////////////////////////////////////////////calculating (1/thermal distance) before simulated annealing ////////////////////////////////////////

            double thermalConst = 1 / ThermalDistanceConstrain(arrCoordenat, arrModuleDimension, arrCriticalModulesIndex, mCritical, 6);

            /////////////////////////////////////////////////////////////calculating aspect ratio before simulated annealing ////////////////////////////////////////

            aspectRatioOld = aspectRatio(arrCoordenat, arrModuleDimension, noOfModules);


            ///////////////////////////////////////////////////////////coefficients of simulated annealling cost function////////////////////////////////////////////////

            float aold = 10;
            float bold = 0.2;
            float cold = 0.1;  ////// fe bug lama 2a3mel optimization 3al thermal distance bs
            float dold = 0;

            //  cout << endl << " Lnorm=" << endl << Lnorm << endl << "  Anorm=" << endl << Anorm << endl << "  Tnorm=" << endl << Tnorm << endl << "  ASPnorm=" << endl << ASPnorm;

            float costOld = aold * Lold + bold * areaBefore + cold * thermalConst + dold * aspectRatioOld;

            // cout << endl << " Lold=" << Lold << endl << " Area before= " << areaBefore << " ThermalConst= "  << thermalConst << " Aspect= "  << aspectRatioOld<<endl;

            //float costOld = aold * Lnorm + bold * Anorm + cold * Tnorm + dold * ASPnorm;

              ///////////////////////////////////////////////////// stimulated annealing/////////////////////////////////////////////////////////////////

            float T = 1001;
            float Tmin = 0.1;
            float alpha = 0.9;
            float numIterations = 2000;


            int d = 0;
            Point lgen1 = { 0,0 }, rgen1 = { 0,0 }, lq1 = { 0,0 }, rq1 = { 0,0 };
            Point lgen2 = { 0,0 }, rgen2 = { 0,0 }, lq2 = { 0,0 }, rq2 = { 0,0 };
            Point lgen = { 0,0 }, rgen = { 0,0 }, lq = { 0,0 }, rq = { 0,0 };
            int ctest = 0;

            double newThermalConst = 0;

            float mybestHpwl = 0;
            float lSum = 0;
            float areaSum = 0;
            float thermalSum = 0;

            c1 = 0;
            c2 = 0;
            c3 = 1;


            if (t == 0) {
                Lavg = 0;
                Aavg = 0;
                Tavg = 0;
                minSol = costOld;
                areaMin = 0;
                Lmin = 0;
                chosenThermalConst = 0;
                chosenAspectRatio = 0;
            }

            while (T > Tmin) {

                for (int i = 0; i < numIterations; i++) {

                    //////////////////// perturbing the intial random placement by chosing one module and changing its coordinates ///////////////////////////////////////////////////////////

                    randModuleSelection1 = rand() % noOfModules;

                    randomXForModule = rand() % xGrid;
                    randomYForModule = rand() % yGrid;


                    randomModuleSelectionX = arrCoordenat[randModuleSelection1][0];
                    randomModuleSelectionY = arrCoordenat[randModuleSelection1][1];

                    arrCoordenat[randModuleSelection1][0] = randomXForModule;
                    arrCoordenat[randModuleSelection1][1] = randomYForModule;

                    ////////////////////////////checking if the perturbed module overlap with other and if it overlap it will reperturbe untill no overlap ////////////////////////////////////////////////////////////////////////////

                    while (1) {
                        ctest = 0;
                        for (int q = 0; q < noOfModules; q++)
                        {

                            if (q != randModuleSelection1) {
                                lgen1 = { arrCoordenat[randModuleSelection1][0],arrCoordenat[randModuleSelection1][1] + arrModuleDimension[randModuleSelection1][1] };
                                rgen1 = { arrCoordenat[randModuleSelection1][0] + arrModuleDimension[randModuleSelection1][0] , arrCoordenat[randModuleSelection1][1] };
                                lq1 = { arrCoordenat[q][0],arrCoordenat[q][1] + arrModuleDimension[q][1] };
                                rq1 = { arrCoordenat[q][0] + arrModuleDimension[q][0] , arrCoordenat[q][1] };

                                if (doOverlap(lgen1, rgen1, lq1, rq1)) {
                                    ctest++;
                                }
                            }
                        }
                        if (ctest != 0)
                        {
                            randnumx = rand() % xGrid;
                            randnumy = rand() % yGrid;

                            arrCoordenat[randModuleSelection1][0] = randnumx;
                            arrCoordenat[randModuleSelection1][1] = randnumy;
                        }
                        else {
                            break;



                        }

                    }


                    /////////////////////////////////////////////mapping the pins after SA////////////////////////////////////////////////////////////////
                    for (int i = 0; i < mulPin; i++) {

                        convertArraysPinCoordinates(arrGeneratePinCombinations, arrGenerateCombinations, arrPinsCoordinates, arrPinNewCoordinates, noOfModules, AllPinsNumber, w, i);
                        /*  if (w>0 && i==0) { cout << endl << " arrPinCheckCoordinates i=0 =" << endl;
                          printArray(arrPinNewCoordinates, pins, 4);
                          }
                          if (w > 0 && i == 1) {
                              cout << endl << " arrPinCheckCoordinates i=1=" << endl;
                              printArray(arrPinNewCoordinates, pins, 4);
                          }*/

                        mappingPinsToModules(arrMappedPinsCoordinates, arrPinNewCoordinates, arrCoordenat, pins);

                        /////////////////////////////////////////////calculating new hpwl after SA////////////////////////////////////////////////////////////////

                        lengthOfPinsPattern[i][0] = calculateSummitionHpwl(arrConnection, arrMappedPinsCoordinates, arrNetPinsCoordinates, netPriority, noOfModules, nets, pins);
                        // cout << endl << "Lnew = " << Lnew << endl;
                      /*  if (w > 0) {
                            cout << endl << " length of p1 and p2 =" << endl;
                        printArray(lengthOfPinsPattern, mulPin, 1);
                    }*/
                    }

                    indexLengthPattern = findSmallestPatternShapesIndex(lengthOfPinsPattern, mulPin);
                    Lnew = lengthOfPinsPattern[indexLengthPattern][0];

                    /////////////////////////////////////////////calculating new Area after SA////////////////////////////////////////////////////////////////

                    areaAfter = (double)totalArea(arrCoordenat, arrModuleDimension, noOfModules);
                    // cout << endl << "areaAfter = " << areaAfter << endl;

                     /////////////////////////////////////////calculating new (1/thermal distance) after SA//////////////////////////////////////////////////

                    newThermalConst = 1 / ThermalDistanceConstrain(arrCoordenat, arrModuleDimension, arrCriticalModulesIndex, mCritical, 6);

                    /////////////////////////////////////////calculating new Aspect ratio after SA//////////////////////////////////////////////////

                    aspectRatioNew = aspectRatio(arrCoordenat, arrModuleDimension, noOfModules);
                    if (T == 1001) {
                        lSum += Lnew;
                        areaSum += areaAfter;
                        thermalSum += newThermalConst;
                        Lavg = (lSum / numIterations);
                        Aavg = (areaSum / numIterations);
                        Tavg = (thermalSum / numIterations);
                    }


                    Lnormn = (Lnew / Lavg) * 100;
                    Anormn = (areaAfter / Aavg) * 100;
                    Tnormn = (newThermalConst / Tavg) * 100;
                    //   ASPnormn = (1.0 - (aspectRatioOld - aspectRatioNew) / (aspectRatioOld));



                   //  costNew = aold * Lnew + bold * areaAfter + cold * newThermalConst + dold * aspectRatioNew;

                    //cout << endl << " Lnew= " << Lnew  << " Area= " << areaAfter << " ThermalConst= " << newThermalConst << " Aspect= " << aspectRatioNew<<endl;

                    //cout << endl << " Lavg= " << Lavg << " Area avg= " << Aavg << " ThermalConst avg= " << Tnormn <<endl;

                    //cout << endl << " Lnormalized= " << aold*Lnormn << " Area normalized= " << bold*Anormn << " ThermalConst normalized= " << cold*Tnormn << endl;


                    costNew = aold * Lnormn + bold * Anormn + cold * Tnormn + dold * aspectRatioNew;


                    deltaCost = costNew - costOld;

                    //  if (t != 0) {

                      //    cout << endl << "/////////////////////////////////////////////////////////////////////////////////////////////////////////"<<endl<<costOld<<endl<<costNew;

                      //}

                    if (deltaCost < 0) {

                        costOld = costNew;

                        if (T != 1001) {



                            if (costNew < minSol) {
                                if (t != 0) {
                                    c2++;
                                    cout << endl << "/////////////////////////////////////////////////////////////////////////////////////////////////////////";

                                }
                                minIndexLengthPattern = indexLengthPattern;
                                minSol = costNew;
                                Lmin = Lnew;
                                // if (mul > 0) {
                                  //   cout << endl << " length accepted =" << endl<<Lmin;

                                 //}
                                chosenThermalConst = newThermalConst;
                                chosenAspectRatio = aspectRatioNew;
                                for (int i = 0; i < noOfModules; i++)
                                {
                                    arrMinCoordinatesArray[i][0] = arrCoordenat[i][0];
                                    arrMinCoordinatesArray[i][1] = arrCoordenat[i][1];
                                }
                                //    printArray(arrMinCoordinatesArray,noOfModules,2);
                                areaMin = totalArea(arrMinCoordinatesArray, arrModuleDimension, noOfModules);
                            }


                        }
                    }

                    else
                    {

                        if (((double)rand() / RAND_MAX) < exp(-deltaCost / T))
                        {
                            costOld = costNew;



                        }
                        else
                        {
                            ////////////////////////////reverse swap//////////////////////////////
                            arrCoordenat[randModuleSelection1][0] = randomModuleSelectionX;
                            arrCoordenat[randModuleSelection1][1] = randomModuleSelectionY;


                        }

                    }

                }



                T *= alpha; // Decreases T, cooling phase 

            }




            cout << endl << "Mapped pins coordinates array = " << endl;
            convertArraysPinCoordinates(arrGeneratePinCombinations, arrGenerateCombinations, arrPinsCoordinates, arrPinNewCoordinates, noOfModules, AllPinsNumber, w, minIndexLengthPattern);

            mappingPinsToModules(arrMappedPinsCoordinates, arrPinNewCoordinates, arrMinCoordinatesArray, pins);
            printArray(arrMappedPinsCoordinates, pins, 4);
            cout << endl << "Min blocks coordinates array = " << endl;
            printArray(arrMinCoordinatesArray, noOfModules, 2);
            cout << endl << "Min Cost = " << minSol << endl << "Min Area = " << areaMin << endl << "MinHpwl = " << Lmin << endl << "ChosenThermalConst = " << 1 / chosenThermalConst << endl << "ChosenAspectRatio = " << chosenAspectRatio;

            //cout << endl << mybestHpwl;
            for (int t = 0; t < noOfModules; t++)
            {
                dramRectangle(renderer, arrMinCoordinatesArray[t][0], arrMinCoordinatesArray[t][1], arrModuleDimension[t][0], arrModuleDimension[t][1]);
            }


            int moduleOne;
            int moduleTwo;
            int moduleOnePin;
            int moduleTwoPin;
            int x1 = 0, x2 = 0, y1 = 0, y2 = 0;

            for (int i = 0; i < nets; i++) {
                moduleOne = arrConnection[i][0];
                moduleTwo = arrConnection[i][1];
                moduleOnePin = arrConnection[i][2];
                moduleTwoPin = arrConnection[i][3];

                for (int j = 0; j < pins; j++) {
                    if ((arrMappedPinsCoordinates[j][0] == moduleOne) && (arrMappedPinsCoordinates[j][1] == moduleOnePin)) {
                        x1 = arrMappedPinsCoordinates[j][2];
                        y1 = arrMappedPinsCoordinates[j][3];
                        arrDrawingConnection[i][0] = x1;
                        arrDrawingConnection[i][1] = y1;
                    }
                    if ((arrMappedPinsCoordinates[j][0] == moduleTwo) && (arrMappedPinsCoordinates[j][1] == moduleTwoPin)) {
                        x2 = arrMappedPinsCoordinates[j][2];
                        y2 = arrMappedPinsCoordinates[j][3];
                        arrDrawingConnection[i][2] = x2;
                        arrDrawingConnection[i][3] = y2;
                    }


                }

                drawLine(renderer, arrDrawingConnection[i][0], arrDrawingConnection[i][1], arrDrawingConnection[i][2], arrDrawingConnection[i][3], netPriority[i][0]);

            }
            cout << endl;
            // printArray(arrDrawingConnection, nets, 4);

            SDL_Delay(10000);
            SDL_RenderClear(renderer);


            if (t == 0) {
                for (int p = 0; p < noOfModules; p++) {
                    arrMinCoordinatesArrayAll[z][0] = arrMinCoordinatesArray[p][0];
                    arrMinCoordinatesArrayAll[z][1] = arrMinCoordinatesArray[p][1];
                    z++;

                }
                arrMinCostArrayAll[U][0] = minSol;
                arrMinAreaArrayAll[U][0] = areaMin;
                arrMinHpwlArrayAll[U][0] = Lmin;
                arrMinAspectRatioArrayAll[U][0] = chosenAspectRatio;
                arrMinThermalDistanceArrayAll[U][0] = 1 / chosenThermalConst;
                U++;
                costCompare = minSol;
            }
            else {
                if (minSol < costCompare) {
                    z = z - noOfModules;
                    U = U - 1;

                    for (int p = 0; p < noOfModules; p++) {
                        arrMinCoordinatesArrayAll[z][0] = arrMinCoordinatesArray[p][0];
                        arrMinCoordinatesArrayAll[z][1] = arrMinCoordinatesArray[p][1];
                        z++;

                    }
                    arrMinCostArrayAll[U][0] = minSol;
                    arrMinAreaArrayAll[U][0] = areaMin;
                    arrMinHpwlArrayAll[U][0] = Lmin;
                    arrMinAspectRatioArrayAll[U][0] = chosenAspectRatio;
                    arrMinThermalDistanceArrayAll[U][0] = 1 / chosenThermalConst;
                    U++;
                    costCompare = minSol;

                }




            }




        }




    } ///////////////// ba2fel behaaa 2el for loop 2el kebera 5ales (w<mul)

    cout << endl << "Min Coordinates array all = " << endl;

    printArray(arrMinCoordinatesArrayAll, noOfModules * mul, 2);

    cout << endl << "Min cost array all = " << endl;
    printArray(arrMinCostArrayAll, mul, 1);

    cout << endl << "Min area array all = " << endl;

    printArray(arrMinAreaArrayAll, mul, 1);

    cout << endl << "Min Hpwl array all = " << endl;

    printArray(arrMinHpwlArrayAll, mul, 1);

    cout << endl << " Best shapes pattern = " << endl;
    for (int i = 0; i < noOfModules; i++) {
        cout << arrGenerateCombinations[findSmallestPatternShapesIndex(arrMinCostArrayAll, mul)][i] << " , ";
    }
    //  cout << endl << " Best pins pattern = " << endl;

    cout << endl << "no of enhancing iterations = " << endl;
    cout << endl << c2 << endl;
}