#include "vdp_rend.h"
#include "blit.h"
void
Blit_Scale2x (unsigned char *Dest, int pitch, int x, int y, int offset) 
{
  
int i, j;
  

int B, D, E, F, H;
  
int E0, E1, E2, E3;
  

    // A B C
    // D E F
    // G H I
  
int ScrWdth, ScrAdd;
  
int SrcOffs, DstOffs;
  

ScrAdd = offset >> 1;
  
ScrWdth = x + ScrAdd;
  

SrcOffs = 8;
  
DstOffs = 0;
  

for (i = 0; i < y; i++)
    
    {
      
E = MD_Screen[SrcOffs - 1];
      
F = MD_Screen[SrcOffs];
      

DstOffs = i * pitch * 2;
      

for (j = 0; j < x; j++)
	
	{
	  
D = E; E = F;
	  
B = MD_Screen[SrcOffs - ScrWdth];
	  
H = MD_Screen[SrcOffs + ScrWdth];
	  
F = MD_Screen[++SrcOffs];
	  

E0 = D == B && B != F && D != H ? D : E;
	  
E1 = B == F && B != D && F != H ? F : E;
	  
E2 = D == H && D != B && H != F ? D : E;
	  
E3 = H == F && D != H && B != F ? F : E;
	  

	    // E0
	    Dest[DstOffs] = E0;
	  
Dest[DstOffs + 1] = E0 >> 8;
	  
	    // E1
	    Dest[DstOffs + 2] = E1;
	  
Dest[DstOffs + 3] = E1 >> 8;
	  
	    // E2
	    Dest[DstOffs + pitch] = E2;
	  
Dest[DstOffs + pitch + 1] = E2 >> 8;
	  
	    // E3
	    Dest[DstOffs + pitch + 2] = E3;
	  
Dest[DstOffs + pitch + 3] = E3 >> 8;
	  

DstOffs += 4;
	
}
      
SrcOffs += ScrAdd;
    
}

}


/** This convert a RGB 16bits buffer (Src) into a RGBA 32 bits buffer (Dest) */
/* size is the number of pixels (short) of Src*/
void Gens_2_RGBA_BYTE (unsigned long *Dest, const unsigned short * Src, unsigned int size)
{
  unsigned int iter_pixel;
  
  const unsigned short * source = Src;
  unsigned char * destination = (unsigned char * )Dest;

  for (iter_pixel = 0;iter_pixel < size ; ++iter_pixel)
    {
      //R
      destination[0] = ((char *)source)[1] & 0xF8;//0b11111000 *8;
      //G
      destination[1] = (*source & 0x7E0)>>3; //0b0000011111100000 >>5 *4
      //B
      destination[2] = (((char *)source)[0] & 0x1F)<<3; //0b00011111 *8
      //A
      destination[3]=0xFF;
      ++source;
      destination+=4;
    }
}
