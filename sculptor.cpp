#include <iostream>
#include <fstream>
#include <cstdlib>
#include "sculptor.h"

Sculptor::Sculptor(int _nx, int _ny, int _nz){
    nx = _nx; // n de planos
    ny = _ny; // n de linhas
    nz = _nz; // n de colunas

    if(nx<=0 || ny<=0 || nz<=0){
        nx=ny=nz=0;
    }

    v = new Voxel**[nx];
    v[0] = new Voxel*[nx*ny];
    v[0][0] = new Voxel[nx*ny*nz];

    for(int i=1; i<nx; i++){
        v[i] = v[i-1] + ny;
    } 

    for(int i=1; i<nx*ny; i++){
        v[0][i] = v[0][i-1] + nz;
    }

    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                v[i][j][k].show = false;
            }
        }
    }

    re=gr=bl=alpha=0;
}

Sculptor::~Sculptor() {
  delete [] v[0][0];
  delete [] v[0];
  delete [] v;
}

void Sculptor::setColor(float r, float g, float b, float a){
    re = r; // cor vermelha
    gr = g; // cor verde
    bl = b; // cor azul
    alpha = a; // transparência

    if(r<0){
        re = 0;
    }
    if(r>255){
        re = 255;
    }
    if(g<0){
        gr = 0;
    }
    if(g>255){
        gr = 255;
    }
    if(b<0){
        bl = 0;
    }
    if(b>255){
        bl = 255;
    }
    if(a<0){
        alpha = 0;
    }
    if(a>255){
        alpha = 255;
    }
}

void Sculptor::putVoxel(int x, int y, int z){
    if(x>=0 && x<nx && y>=0 && y<ny && z>=0 && z<nz){
        v[x][y][z].show = true;
        v[x][y][z].re = re;
        v[x][y][z].gr = gr;
        v[x][y][z].bl = bl;
        v[x][y][z].alpha = alpha;
    }
}

void Sculptor::cutVoxel(int x, int y, int z){
    if(x>=0 && x<nx && y>=0 && y<ny && z>=0 && z<nz){
        v[x][y][z].show = false;
    }
}

void Sculptor::putBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
            for(int k=z0; k<=z1; k++){
                putVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::cutBox(int x0, int x1, int y0, int y1, int z0, int z1){
    for(int i=x0; i<=x1; i++){
        for(int j=y0; j<=y1; j++){
            for(int k=z0; k<=z1; k++){
                cutVoxel(i,j,k);
            }
        }
    }
}

void Sculptor::putSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if((i-xcenter)*(i-xcenter)+(j-ycenter)*(j-ycenter)+(k-zcenter)*(k-zcenter) <= radius*radius){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutSphere(int xcenter, int ycenter, int zcenter, int radius){
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if((i-xcenter)*(i-xcenter)+(j-ycenter)*(j-ycenter)+(k-zcenter)*(k-zcenter) <= radius*radius){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::putEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
 for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if(((float)(i-xcenter)*(i-xcenter)/(rx*rx))+((float)(j-ycenter)*(j-ycenter)/(ry*ry))+((float)(k-zcenter)*(k-zcenter)/(rz*rz)) <= 1.0){
                    putVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::cutEllipsoid(int xcenter, int ycenter, int zcenter, int rx, int ry, int rz){
    for(int i=0; i<nx; i++){
        for(int j=0; j<ny; j++){
            for(int k=0; k<nz; k++){
                if(((float)(i-xcenter)*(i-xcenter)/(rx*rx))+((float)(j-ycenter)*(j-ycenter)/(ry*ry))+((float)(k-zcenter)*(k-zcenter)/(rz*rz)) <= 1.0){
                    cutVoxel(i,j,k);
                }
            }
        }
    }
}

void Sculptor::writeOFF(const char* filename){
    int i, j, k, nVoxels = 0, facecounter = 0;
    std::ofstream fout;
    fout.open(filename);
    if(!fout.is_open()){
        std::cout << "Erro ao abrir o arquivo\n";
        exit(1);
    }

    fout << "OFF" << std::endl;

    //Contar número de voxels não escondidos
    for (int i = 0; i < nx; i++) {
        for (int j = 0; j < ny; j++) {
            for (int k = 0; k < nz; k++) {
                bool NoAllNeighbors = false;

      // Verifica se todos os vizinhos tem show=true
                if (i > 0 && !v[i-1][j][k].show) NoAllNeighbors = true;
                if (i < nx-1 && !v[i+1][j][k].show) NoAllNeighbors = true;
                if (j > 0 && !v[i][j-1][k].show) NoAllNeighbors = true;
                if (j < ny-1 && !v[i][j+1][k].show) NoAllNeighbors = true;
                if (k > 0 && !v[i][j][k-1].show) NoAllNeighbors = true;
                if (k < nz-1 && !v[i][j][k+1].show) NoAllNeighbors = true;

      // Se não tem todos os vizinhos, então incremenda NoAllNeighborsCounter
                if (NoAllNeighbors && v[i][j][k].show) {
                    nVoxels++;
                }
            }
        }
    }
    
    //Escrever o número de vértices, faces e arestas
    fout << 8*nVoxels << " " << 6*nVoxels << " " << 0 << std::endl;

    //Escrever os vértices
    for (i = 0; i < nx; i++) {
        for (j = 0; j < ny; j++) {
            for (k = 0; k < nz; k++) {
                bool NoAllNeighbors = false;

      // Verifica se todos os vizinhos tem show=true
                if (i > 0 && !v[i-1][j][k].show) NoAllNeighbors = true;
                if (i < nx-1 && !v[i+1][j][k].show) NoAllNeighbors = true;
                if (j > 0 && !v[i][j-1][k].show) NoAllNeighbors = true;
                if (j < ny-1 && !v[i][j+1][k].show) NoAllNeighbors = true;
                if (k > 0 && !v[i][j][k-1].show) NoAllNeighbors = true;
                if (k < nz-1 && !v[i][j][k+1].show) NoAllNeighbors = true;

      // Se não tem todos os vizinhos, escreve no arquivo OFF
                if (NoAllNeighbors && v[i][j][k].show) {
                    fout << i-0.5 << " " << j+0.5 << " " << k-0.5 << std::endl;
                    fout << i-0.5 << " " << j-0.5 << " " << k-0.5 << std::endl;
                    fout << i+0.5 << " " << j-0.5 << " " << k-0.5 << std::endl;
                    fout << i+0.5 << " " << j+0.5 << " " << k-0.5 << std::endl;
                    fout << i-0.5 << " " << j+0.5 << " " << k+0.5 << std::endl;
                    fout << i-0.5 << " " << j-0.5 << " " << k+0.5 << std::endl;
                    fout << i+0.5 << " " << j-0.5 << " " << k+0.5 << std::endl;
                    fout << i+0.5 << " " << j+0.5 << " " << k+0.5 << std::endl;
                }
            }
        }
    }
  
    //Escrever as faces
     for (i = 0; i < nx; i++) {
        for (j = 0; j < ny; j++) {
            for (k = 0; k < nz; k++) {
                bool NoAllNeighbors = false;

      // Verifica se todos os vizinhos tem show=true
                if (i > 0 && !v[i-1][j][k].show) NoAllNeighbors = true;
                if (i < nx-1 && !v[i+1][j][k].show) NoAllNeighbors = true;
                if (j > 0 && !v[i][j-1][k].show) NoAllNeighbors = true;
                if (j < ny-1 && !v[i][j+1][k].show) NoAllNeighbors = true;
                if (k > 0 && !v[i][j][k-1].show) NoAllNeighbors = true;
                if (k < nz-1 && !v[i][j][k+1].show) NoAllNeighbors = true;

      // Se não tem todos os vizinhos, escreve no arquivo OFF
                if (NoAllNeighbors && v[i][j][k].show) {
                    fout << "4 " << facecounter*8+0 << " " << facecounter*8+3 << " " << facecounter*8+2 << " " << facecounter*8+1 << " ";
                    fout << v[i][j][k].re << " " << v[i][j][k].gr << " " << v[i][j][k].bl << " " << v[i][j][k].alpha << std::endl;
                    fout << "4 " << facecounter*8+4 << " " << facecounter*8+5 << " " << facecounter*8+6 << " " << facecounter*8+7 << " ";
                    fout << v[i][j][k].re << " " << v[i][j][k].gr << " " << v[i][j][k].bl << " " << v[i][j][k].alpha << std::endl;
                    fout << "4 " << facecounter*8+0 << " " << facecounter*8+1 << " " << facecounter*8+5 << " " << facecounter*8+4 << " ";
                    fout << v[i][j][k].re << " " << v[i][j][k].gr << " " << v[i][j][k].bl << " " << v[i][j][k].alpha << std::endl;
                    fout << "4 " << facecounter*8+0 << " " << facecounter*8+4 << " " << facecounter*8+7 << " " << facecounter*8+3 << " ";
                    fout << v[i][j][k].re << " " << v[i][j][k].gr << " " << v[i][j][k].bl << " " << v[i][j][k].alpha << std::endl;
                    fout << "4 " << facecounter*8+3 << " " << facecounter*8+7 << " " << facecounter*8+6 << " " << facecounter*8+2 << " ";
                    fout << v[i][j][k].re << " " << v[i][j][k].gr << " " << v[i][j][k].bl << " " << v[i][j][k].alpha << std::endl;
                    fout << "4 " << facecounter*8+1 << " " << facecounter*8+2 << " " << facecounter*8+6 << " " << facecounter*8+5 << " ";
                    fout << v[i][j][k].re << " " << v[i][j][k].gr << " " << v[i][j][k].bl << " " << v[i][j][k].alpha << std::endl;
                    facecounter++;
                }
            }
        }
     }
    
    fout.close();

}