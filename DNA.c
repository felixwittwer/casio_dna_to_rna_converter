/*****************************************************************/
/*                                                               */
/*   Casio DNA to RNA converter                                  */
/*                                                               */
/*   File name : DNATORNA.c                                      */
/*                                                               */
/*   Copyright (c) 2023 Felix Wittwer                            */
/*                                                               */
/*****************************************************************/
#include "fxlib.h"
#include <stdio.h>

void RenderStrand(int x, int y, int marker, int ends, char symbols[], int line){
    //int x ; int y are for the position
    //int marker specifies in which direction and how long the markers get rendered
    //int ends defines how the ends of the stands should be labeled
    //chat symbols[] is a list of the rendered characters 

    int iteration = 0;
    int xaddition;
    unsigned char buffer[12];

    if(line==1){
        Bdisp_DrawLineVRAM(x,y,x+102,y);

        // function just for this specific program  shortend because of storage
        if(ends==3 && marker<0){
            PrintMini(x-7,y-4,(unsigned char*)"3'", MINI_OVER);
            PrintMini(x+104,y-4,(unsigned char*)"5'", MINI_OVER);
        }else if(ends==5 && marker>0){
            PrintMini(x-7,y,(unsigned char*)"5'", MINI_OVER);
            PrintMini(x+104,y,(unsigned char*)"3'", MINI_OVER);
        }
    }

    while(iteration<15){
        xaddition = (iteration)*5+(7*((iteration)/3))+2;

        if(line==1){
            Bdisp_DrawLineVRAM(x+xaddition,y,x+xaddition,y+marker);
        }

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

RenderPointer(int x, int y, int pointer, int render){
    int xaddition;
    xaddition = (pointer)*5+(7*((pointer)/3))+2;
    if(render==1){
        Bdisp_DrawLineVRAM(x+xaddition-1,y,x+xaddition+1,y);
    }else if(render==0){
        Bdisp_ClearLineVRAM(x+xaddition-1,y,x+xaddition+1,y);
    }
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
    int iteration = 0;
    int pointer = 1;
    char dnaone [15] = "ATGTCGGTGCTGTAT";
    char dnatwo [15] = "";
    char mrna [15] = "";
    char trna [15] = "";

    Bdisp_AllClr_DDVRAM();

    while(1){
        GetKey(&key);

        //clear last pointer
        RenderPointer(12, 11, pointer-1, 0);
        
        //input for first DNA strand
        if(key==KEY_CHAR_1){
            dnaone[pointer-1] = 'T';
        }else if(key==KEY_CHAR_4){
            dnaone[pointer-1] = 'A';
        }else if(key==KEY_CHAR_3){
            dnaone[pointer-1] = 'C';
        }else if(key==KEY_CHAR_6){
            dnaone[pointer-1] = 'G';
        }else if(key==KEY_CTRL_DEL){
            dnaone[pointer-1] = ' ';
        }

        while(iteration<15){
            if(dnaone[iteration]=='T'){
                dnatwo[iteration]='A';
            }else if(dnaone[iteration]=='A'){
                dnatwo[iteration]='T';
            }else if(dnaone[iteration]=='G'){
                dnatwo[iteration]='C';
            }else if(dnaone[iteration]=='C'){
                dnatwo[iteration]='G';
            }else if(dnaone[iteration]==' '){
                dnatwo[iteration]=' ';
            }

            //copy dnaone to mrna
            if(dnaone[iteration] != 'T'){
                mrna[iteration] = dnaone[iteration];
            }else if(dnaone[iteration]=='T'){
                mrna[iteration] = 'U';
            }

            if(dnatwo[iteration] != 'T'){
                trna[iteration] = dnatwo[iteration];
            }else if(dnatwo[iteration]=='T'){
                trna[iteration] = 'U';
            }
            iteration = iteration + 1;
        }
        iteration = 0;

        //if strand changed pointer + 1
        if(key==KEY_CHAR_1||key==KEY_CHAR_3||key==KEY_CHAR_4||key==KEY_CHAR_6){
            pointer = pointer + 1;
        }

        //move pointer with arrowkeys
        if(key==KEY_CTRL_RIGHT){
            pointer = pointer + 1;
        }else if(key==KEY_CTRL_LEFT){
            pointer = pointer - 1;
        }

        //dont move pointer out of range
        if(pointer < 1){
            pointer = 15;
        }else if(pointer > 15){
            pointer = 1;
        }
        
        RenderPointer(12, 11, pointer-1, 1);

        //display strands
        RenderStrand(12,2,1,5, dnaone,1);
        RenderStrand(12,20,-1,3, dnatwo,1);
        RenderStrand(12,22,1,5, mrna,1);
        RenderStrand(12,29,1,5, trna,0);

        RenderPointer(12, 11, pointer-1, 1);

        //displa tRNA
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

