#include "read_usb_data.hpp"
#include "data_adjustment.hpp"
#include "parameter_vars.hpp"
#include <asio.hpp>
#include <exception>

void read_data_dirct(std::atomic<float> & v,struct parameters_varibles & pv){
    asio::io_context io;
    asio::serial_port serial(io, "/dev/ttyUSB0");
    float f_adj = 0;//!!!!!!
    // Configure serial parameters: 115200 baud, 8 data bits, no parity, 1 stop bit
    serial.set_option(asio::serial_port_base::baud_rate(115200));
    serial.set_option(asio::serial_port_base::character_size(8));
    serial.set_option(asio::serial_port_base::parity(asio::serial_port_base::parity::none));
    serial.set_option(asio::serial_port_base::stop_bits(asio::serial_port_base::stop_bits::one));
    serial.set_option(asio::serial_port_base::flow_control(asio::serial_port_base::flow_control::none));
    char Serial_data;
    std::string serial_data_str;
    bool it_dig = 1;
    float data_value = 0;

    while(1){
        asio::read(serial,asio::buffer(&Serial_data, 1));
        //std::cout<<Serial_data<<'\n';
        if(Serial_data!=';' && Serial_data!= '\n' && Serial_data!= '\r'){
            serial_data_str+=Serial_data;
        }
        else{
            for(char c : serial_data_str)
                if(!std::isdigit(c)){ 
                    it_dig = 0;
                    if(c=='.'||c=='-')it_dig = 1;
                }
            if(it_dig){
                //std::cout<<serial_data_str<<'\n';
                pv.is_read = true;
                    try{
                        data_value = std::stof(serial_data_str);
                    }
                    catch(std::invalid_argument &e){
                        //std::cout<<">>>"<<(std::string(e.what())==std::string("stof"))<<'\n';
                        if(std::string(e.what())==std::string("stof"))pv.is_read = false;
                        else pv.is_read = false;
                      //  std::cout<<e.what()<<"\n";
                   }
                f_adj = first_adjustment(data_value,pv.wave_size,pv.pos);
                v =  f_adj;//! 
                //it_dig = 1;
            }
            //std::cout<<"STR , INT : "<<serial_data_str<<','<<data_value<<','<<v<<','<<f_adj<<'\n';
            serial_data_str="";
        }
    }
}