#include <cctype>
#include <iostream>
#include <raylib.h>
#include <string>
#include <vector>
#include <thread>
#include <atomic>
#include "read_usb_data.hpp"
#include "parameter_vars.hpp"
#define RAYGUI_IMPLEMENTATION
#include "raygui.h"
int wave_size = 1;
int main(){
    std::vector<float> amp_v;
    std::vector<float> time_v;
    std::vector<float> amp_v_p;
    std::vector<float> time_v_p;
    std::atomic<float> data_value = 0;
    struct parameters_varibles pv;
    bool is_puase = false;
    //std::thread reading_data_thread(read_data_dirct,std::ref(data_value),std::ref(pv));
    //reading_data_thread.detach();

    const int screenWidth = 1200;
    const int screenHeight = 500;
    int x_mov = -1;
    int y = 0;
    int base = 0; //!
    bool is_shfit = 0;
    InitWindow(screenWidth, screenHeight, "WAVE SCAN"); // NAME !
    SetTargetFPS(60); //!
    
    while(!WindowShouldClose()){
        if(!is_puase){
            x_mov++;
            amp_v.push_back(data_value);
        }
        pv.V_mean = sqrt(pow(pv.V_mean+int(amp_v[amp_v.size()-1]),2)/amp_v.size()); //!; 
        pv.V_max = (pv.V_max<=amp_v[amp_v.size()-1])?amp_v[amp_v.size()-1]:pv.V_max;
        pv.V_min = (pv.V_min>=amp_v[amp_v.size()-1])?amp_v[amp_v.size()-1]:pv.V_min;
        time_v.push_back(x_mov);
        if(x_mov==900){
            x_mov=0;
            is_shfit = true;
        }
        if(is_shfit)base++;
        std::cout<<"X,Y,b,s = "<<x_mov<<','<<data_value<<','<<base<<','<<amp_v.size()<<'\n';
        BeginDrawing();
            ClearBackground(RAYWHITE);
            
            int spinner_amp =  GuiSpinner(Rectangle{950,10,200,100},"Zoom",&pv.wave_size,-10,10,false);
            int spinner_pos =  GuiSpinner(Rectangle{950,110,200,100},"Pos",&pv.pos,-250,250,true);
            GuiLabel(Rectangle{950,200,200,100},"MEAN = ");
            GuiLabel(Rectangle{1000,200,200,100},std::to_string(pv.V_mean).c_str());
            GuiLabel(Rectangle{1050,200,200,100},"MAX = ");
            GuiLabel(Rectangle{1100,200,200,100},std::to_string(pv.V_max).c_str());
            GuiLabel(Rectangle{950,210,200,100},"MIN = ");
            GuiLabel(Rectangle{1000,210,200,100},std::to_string(pv.V_max).c_str());
            if(GuiButton(Rectangle{950,320,100,100},"CLEAR")){
                amp_v.clear();
                time_v.clear();
                base = 0;
                x_mov = 0;
            }
            if(GuiButton(Rectangle{1070,320,100,100},"PUASE")){
                is_puase=!is_puase;
                is_shfit = false;
                if(!is_puase){
                    amp_v.clear();
                    time_v.clear();
                    base = 0;
                    x_mov = 0;
                }
            }
            if(GuiButton(Rectangle{950,430,220,70},"READ")){
                std::cout<<pv.is_read<<'\n';
                if(pv.is_read==false){
                    std::thread reading_data_thread(read_data_dirct,std::ref(data_value),std::ref(pv));
                    reading_data_thread.detach();
                }
            }
            for(int i = 0;i<500;i=i+50){
                DrawRectangle(0,500-i,900,2,BLACK);
            }
            for(int i = 0;i<900;i=i+50){
                DrawRectangle(900-i,0,2,500,BLACK);
            }
            //DrawRectangle(0,250-50,900,5,BLACK);
            //DrawRectangle(0,250-100,900,5,BLACK);
            DrawRectangle(450,0,2,500,RED);
            DrawRectangle(0,250,900,2,RED);
            for(int i = base;i<amp_v.size();i++){
              //  DrawRectangle(time_v[i-base],150,5,5,GREEN);
                //DrawRectangle(time_v[i-base],amp_v[i],5,5,DARKBLUE);
                if(i+1!=amp_v.size()){
                    int c = 5;
                    for(int j = -c;j<(c+1);j++){
                        DrawLine(time_v[i-base],amp_v[i]+j,time_v[(i+1)-base],amp_v[i+1]+j,DARKBLUE); 
                    }
                }

                //DrawCircle(time_v[i-base],amp_v[i],5,RED);//!
                //DrawPixel(time_v[i-base],amp_v[i],RED);
                //DrawPixel(time_v[i-base],amp_v[i]+1,RED);
                //DrawPixel(time_v[i-base],amp_v[i]+2,RED);
                //DrawPixel(time_v[i-base],amp_v[i]+3,RED);
            }
            
        EndDrawing();
    }
    return 0;    
}