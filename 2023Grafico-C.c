
#include "Render2023-v1.h"
const unsigned int COLOR_A = 0xff282814;
const unsigned int COLOR_B = 0xff505028;
const unsigned int Ancho   = 640;
const unsigned int Alto    = 480;
static unsigned int ROT    = 0;
const unsigned char sinTab[91] = {
0,4,8,13,17,22,26,31,35,39,44,48,53,57,61,65,70,74,78,83,87,91,95,99,103,107,111,115,119,123,
127,131,135,138,142,146,149,153,156,160,163,167,170,173,177,180,183,186,189,192,195,198,200,203,206,208,211,213,216,218,
220,223,225,227,229,231,232,234,236,238,239,241,242,243,245,246,247,248,249,250,251,251,252,253,253,254,254,254,254,254,
255
};

static const int fastSin(int i){
  while(i<0) i+=360;
  while(i>=360) i-=360;
  if(i<90)  return(sinTab[i]); else
  if(i<180) return(sinTab[180-i]); else
  if(i<270) return(-sinTab[i-180]); else
            return(-sinTab[360-i]);
}


void Bucle( register unsigned int *BufferVideo, int DeltaTime ){
	int x,y,xx,yy, xo,yo;
	xo = ( 32 * fastSin( 4 * (ROT>>1) ) >> 8 ) + 50;
	yo = ( 32 * fastSin( 5 * (ROT>>1) ) >> 8 ) + 50;
	for(y=0;y<Alto;y++){
		yy = (y+yo) & 63;
		for(x=0;x<Ancho;x++){
			xx = (x+xo) & 63,
			*BufferVideo++ = ((xx<32 && yy<32) || (xx>32 && yy>32)) ? COLOR_A : COLOR_B;
		}
	}
	if(ROT>=360) ROT=0;
	ROT++;
}


int main(void){
    CrearScreen( Ancho,Alto );
    SetLoop(Bucle);
    StartLoop();
    return 0;
}