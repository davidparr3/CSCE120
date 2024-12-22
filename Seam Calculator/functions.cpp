#include <iostream>
#include <sstream>
#include <fstream>
#include <cmath>
#include "functions.h"

using std::cout, std::endl, std::string;

void initializeImage(Pixel image[][MAX_HEIGHT]) {
  // iterate through columns
  for (unsigned int col = 0; col < MAX_WIDTH; col++) {
    // iterate through rows
    for (unsigned int row = 0; row < MAX_HEIGHT; row++) {
      // initialize pixel
      image[col][row] = {0, 0, 0};
    }
  }
}

void loadImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int& height) {
// define vals
  std::ifstream inFS(filename);
  std::string ftype;
  std::string maxcolor;
  //std::string spce;
  int wnum, hnum;
  int pr, pg, pb;
  short r, g, b;
  int over;
  
//check if file open  
   if (!inFS.is_open()) {
      throw std::runtime_error("Failed to open " + filename);
   }

//check file type
  inFS >> ftype;
  if(ftype != "p3" && ftype != "P3"){
    throw std::runtime_error("Invalid type " + ftype);
  }

// get int diminsions
  if(!(inFS >> wnum) || !(inFS >> hnum)){
    throw std::runtime_error("Invalid dimensions");
  }

// varify diminsions
  if(wnum < 0 || wnum > 1920 || hnum < 0 || hnum > 1080){
    throw std::runtime_error("Invalid dimensions");
  }
  width = wnum;
  height = hnum;

// varify maxcolor
  inFS >> maxcolor;
  if(maxcolor != "255"){
    throw std::runtime_error("Invalid max color value");
  }

//read pixels
for(unsigned int i = 0; i < height; i++){
  for(unsigned int j = 0; j < width; j++){

    //check for enough ppm color vals
    if(!(inFS >> pr) || !(inFS >> pg) || !(inFS >> pb)){
      throw std::runtime_error("Not enough values");
    }

    // varify correct color vals
    if((pr < 0 || pr > 255) || (pg < 0 || pg > 255) || (pb < 0 || pb > 255)){
      throw std::runtime_error("Invalid color value");
    }

    //load rgb into image array
    r = pr;
    g = pg;
    b = pb;

    image[j][i] = {r, g, b};
    
  }
}

//check for too many color vals
if(inFS >> over){
  throw std::runtime_error("Too many values");
}

// close file
inFS.close();
}

void outputImage(string filename, Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height) {
  // TODO: implement (part 1)
  std::ofstream outFS(filename);

  // create int vars
  int outr, outg, outb;

  //check if file open  
   if (!outFS.is_open()) {
      throw std::runtime_error("Failed to open " + filename);
   }

  // write in file
  outFS << "P3" << endl;
  outFS << width << " " << height << endl;
  outFS << 255 << endl;
  for(unsigned int i = 0; i < height; i++){
    for(unsigned int j = 0; j < width; j++){
      outr = image[j][i].r;
      outg = image[j][i].g;
      outb = image[j][i].b;
      outFS << outr << " " << outg << " " << outb << " ";
    }
    outFS << endl;
  }

  //close file
  outFS.close();
}

unsigned int energy(Pixel image[][MAX_HEIGHT], unsigned int x, unsigned int y, unsigned int width, unsigned int height) {
  // TODO: implement (part 1)
  //define vars
  short rx, ry, gx, gy, bx, by;
  unsigned int energy;

  unsigned int ygradu, ygradd, xgradl, xgradr;

//find edge case
if(x == 0){
  xgradl = width - 1;
  xgradr = x + 1;
}
if(x == width - 1){
  xgradl = x - 1;
  xgradr = 0;
}
if(y == 0){
  ygradu = height - 1;
  ygradd = y + 1;
}
if(y == height - 1){
  ygradu = y - 1;
  ygradd = 0;
}
if(x != 0 && x != width - 1){
  xgradl = x - 1;
  xgradr = x + 1;
}
if(y != 0 && y != height - 1){
  ygradu = y - 1;
  ygradd = y + 1;
}


//xy components
rx = image[xgradr][y].r - image[xgradl][y].r;
ry = image[x][ygradd].r - image[x][ygradu ].r;
gx = image[xgradr][y].g - image[xgradl][y].g;
gy = image[x][ygradd].g - image[x][ygradu].g;
bx = image[xgradr][y].b - image[xgradl][y].b;
by = image[x][ygradd].b - image[x][ygradu].b;

//final calc
energy = ((rx * rx) + (gx * gx) + (bx * bx) + (ry * ry) + (gy * gy) + (by * by));
return energy;
}

// Part 2

unsigned int loadVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_col, unsigned int width, unsigned int height, unsigned int seam[]) {
   //define vars
   unsigned int y = 1;
   unsigned int x = start_col;
   seam[0] = start_col;
   unsigned int energy_tot = energy(image, x, 0, width, height);

   while(y < height){
    //reset e vars
    unsigned int e1 = 2147483647; 
    unsigned int e2 = 2147483647;
    unsigned int e3 = 2147483647;
    //find each energy
    if(x > 0){
      e1 = energy(image, x - 1, y, width, height); //check left
    }

    e2 = energy(image, x, y, width, height); //check below

    if(x != width - 1){
      e3 = energy(image, x + 1, y, width, height); //check right
    }

    // check for least energy
      // three way tie
      if((e1 == e2) && (e2 == e3)){
        energy_tot += e2;
        x = x;
      }
      // e1 and e3 tie
      else if((e1 == e3) && e1 < e2){
          energy_tot += e3;
          x = x + 1;
        }
      // e1 and e2 tie
      else if((e1 == e2) && e2 < e3){
          energy_tot += e2;
          x = x;
        }
      // e1 
      else if (e1 <= e2 && e1 <= e3) {
        
        energy_tot += e1;
        x = x - 1;
      } 
      // e2 
      else if (e2 <= e1 && e2 <= e3) {
        energy_tot += e2;
        x = x;
      } 
      //e3
      else {
        energy_tot += e3;
        x = x + 1;
      }

    // add x to seam array
    seam[y] = x;
    y++;
    }

   return energy_tot;
}

unsigned int loadHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int start_row, unsigned int width, unsigned int height, unsigned int seam[]) {
//define vars
   unsigned int x = 1;
   unsigned int y = start_row;
   seam[0] = start_row;
   unsigned int energy_tot = energy(image, 0, y, width, height);

   while(x < width){
    //reset e vars
    unsigned int e1 = 2147483647; 
    unsigned int e2 = 2147483647;
    unsigned int e3 = 2147483647;
    //find each energy
    if(y > 0){
      e3 = energy(image, x, y - 1, width, height); //check left
    }

    e2 = energy(image, x, y, width, height); //check below

    if(y != height - 1){
      e1 = energy(image, x, y + 1, width, height); //check right
    }

    // check for least energy
      // three way tie
      if((e1 == e2) && (e2 == e3)){
        energy_tot += e2;
        y = y;
      }
      // e1 and e3 tie
      else if((e1 == e3) && e1 < e2){
          energy_tot += e3;
          y = y - 1;
        }
      // e1 and e2 tie
      else if((e1 == e2) && e2 < e3){
          energy_tot += e2;
          y = y;
        }
      // e1 
      else if (e1 <= e2 && e1 <= e3) {
        
        energy_tot += e1;
        y = y + 1;
      } 
      // e2 
      else if (e2 <= e1 && e2 <= e3) {
        energy_tot += e2;
        y = y;
      } 
      //e3
      else {
        energy_tot += e3;
        y = y - 1;
      }

    // add x to seam array
    seam[x] = y;
    x++;
    }

   return energy_tot;
}

 void findMinVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
  //define vars
  unsigned int oldenergy = 2147483647;
  unsigned int newseam[MAX_HEIGHT];

  //compare all seams
  for(unsigned x = 0; x < width; x++){
    unsigned newenergy = loadVerticalSeam(image, x, width, height, seam);
    if(newenergy < oldenergy){
      oldenergy = newenergy;
      for(unsigned int y =0; y < height; y++){
        newseam[y] = seam[y];
      }
    }
  }

  //update vertical seam
  for(unsigned int y = 0; y < height; y++){
    seam[y] = newseam[y];
  }

}

// void findMinHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int height, unsigned int seam[]) {
//   // TODO: implement (part 2)
// }

void removeVerticalSeam(Pixel image[][MAX_HEIGHT], unsigned int& width, unsigned int height, unsigned int verticalSeam[]) {
  //Define vars
  width--; // set new width

  //appened pixels into newimage 
  for(unsigned int y = 0; y < height; y++){
    for(unsigned int x = verticalSeam[y]; x < width; x++){
      image[x][y] = image[x + 1][y];
    }
  }

}

// void removeHorizontalSeam(Pixel image[][MAX_HEIGHT], unsigned int width, unsigned int& height, unsigned int horizontalSeam[]) {
//   // TODO: implement (part 2)
// }
