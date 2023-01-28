/*****************************************************************/
/*                                                               */
/*   CASIO fx-9860G SDK Library                                  */
/*                                                               */
/*   File name : [ProjectName].c                                 */
/*                                                               */
/*   Copyright (c) 2006 CASIO COMPUTER CO., LTD.                 */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include <stdio.h>

void RenderStrand(int x, int y, int marker, int ends, char symbols[]){
    int iteration = 0;
    int xaddition;
    unsigned char buffer[12];

    Bdisp_DrawLineVRAM(x,y,x+102,y);

    // function just for this specific program  shortend because of storage
    if(ends==3 && marker<0){
        PrintMini(x-7,y-4,(unsigned char*)"3'", MINI_OVER);
        PrintMini(x+104,y-4,(unsigned char*)"5'", MINI_OVER);
    }else if(ends==5 && marker>0){
        PrintMini(x-7,y,(unsigned char*)"5'", MINI_OVER);
        PrintMini(x+104,y,(unsigned char*)"3'", MINI_OVER);
    }

    while(iteration<15){
        xaddition = (iteration)*5+(7*((iteration)/3))+2;

        Bdisp_DrawLineVRAM(x+xaddition,y,x+xaddition,y+marker);

        sprintf(buffer, "%c", symbols[iteration]);
        if(marker>0){
            PrintMini(x+xaddition-1,y+3, buffer, MINI_OVER);
        }else if(marker<0){
            PrintMini(x+xaddition-1,y-7, buffer, MINI_OVER);
        }


        iteration = iteration + 1;
    }
}

void RendertRNA(int x, int y){
    Bdisp_DrawLineVRAM(x-5,y,x-5,y+1);
    Bdisp_DrawLineVRAM(x,y,x,y+2);
    Bdisp_DrawLineVRAM(x+5,y,x+5,y+1);
    Bdisp_DrawLineVRAM(x-5,y+1,x+5,y+1);

}

//****************************************************************************
//  AddIn_main (Sample program main function)
//
//  param   :   isAppli   : 1 = This application is launched by MAIN MENU.
//                        : 0 = This application is launched by a strip in eACT application.
//
//              OptionNum : Strip number (0~3)
//                         (This parameter is only used when isAppli parameter is 0.)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int AddIn_main(int isAppli, unsigned short OptionNum)
{
    unsigned int key;
    char dnaone [15] = "ATGTCGGTGCTGTAT";
    char dnatwo [15] = "";
    char mrna [15] = "";

    Bdisp_AllClr_DDVRAM();


    while(1){
        GetKey(&key);

        RenderStrand(12,2,1,5, dnaone);
        RenderStrand(12,19,-1,3, dnatwo);
        RenderStrand(12,21,1,5, mrna);

        RendertRNA(19,38);
        RendertRNA(41,38);
        RendertRNA(63,38);
        RendertRNA(85,38);
        RendertRNA(107,38);

    }

    return 1;
}




//****************************************************************************
//**************                                              ****************
//**************                 Notice!                      ****************
//**************                                              ****************
//**************  Please do not change the following source.  ****************
//**************                                              ****************
//****************************************************************************


#pragma section _BR_Size
unsigned long BR_Size;
#pragma section


#pragma section _TOP

//****************************************************************************
//  InitializeSystem
//
//  param   :   isAppli   : 1 = Application / 0 = eActivity
//              OptionNum : Option Number (only eActivity)
//
//  retval  :   1 = No error / 0 = Error
//
//****************************************************************************
int InitializeSystem(int isAppli, unsigned short OptionNum)
{
    return INIT_ADDIN_APPLICATION(isAppli, OptionNum);
}

#pragma section

