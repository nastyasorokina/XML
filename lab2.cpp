#include <iostream>
#include <fstream>
#include <libxml++/libxml++.h>

struct Sinfo_parking{
    Glib::ustring number,
            address,
            type,
            parking_space,
            area,
            district_city,
            nearest_subway_station,
            note;
};

class Parser : public xmlpp::SaxParser
{
public:
    Parser(Glib::ustring _district_city, Glib::ustring _nearest_subway_station)
            : xmlpp::SaxParser()
    {
        district_city = _district_city;
        nearest_subway_station = _nearest_subway_station;
        f = "";
    }

    ~Parser()
    {
    }

    void print_info(){
        std::cout << std::stoi(sparking.parking_space) << std::endl;
    }

protected:
    void on_start_element(const Glib::ustring& name,
                          const AttributeList& attributes)
    {
        f = name;
    }

    void on_end_element(const Glib::ustring& name)
    {
        f = "";
        if (name  == "info_parking" ){
            if (sbuffer.district_city == district_city &&
                sbuffer.nearest_subway_station == nearest_subway_station){
                sparking = sbuffer;
            }
        }
    }

    void on_characters(const Glib::ustring& text)
    {
        if (f == "number")  {sbuffer.number = text;}
        else if (f == "address")  {sbuffer.address = text;}
        else if (f == "type")  {sbuffer.type = text; }
        else if (f == "parking_space")  {sbuffer.parking_space = text; }
        else if (f == "area")  {sbuffer.area = text;}
        else if (f == "district_city")  {sbuffer.district_city = text;}
        else if (f == "nearest_subway_station")  {sbuffer.nearest_subway_station = text;}
        else if (f == "note")  {sbuffer.note = text;}
    }
private:
    Glib::ustring district_city, nearest_subway_station, f;
    Sinfo_parking sbuffer, sparking;
};

int main(int argc, char* argv[]){
    std::locale::global(std::locale(""));
    Glib::ustring district_city_cus("Viborgski"),
            nearest_subway_station_cus("Parnas");
    std::string filepath;

    if(argc >= 3){
        filepath = argv[1];
        district_city_cus = argv[2];
        nearest_subway_station_cus = argv[3];
    }
    else{
        filepath = "park.xml";
    }

    try
    {
        Parser parser(district_city_cus, nearest_subway_station_cus);
        parser.set_substitute_entities(true);
        parser.parse_file(filepath);
        parser.print_info();
    }
    catch(const xmlpp::exception& ex)
    {
        std::cout << "libxml++ exception: " << ex.what() << std::endl;
    }
    return 0;
    }
