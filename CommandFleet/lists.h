#ifndef LISTS_H
#define LISTS_H
#include<iostream>
#include<string>
#include<fstream>
struct vehicle
{
	std::string type = "";
	std::string brand = "";
	std::string model = "";
	std::string licens = "";
	vehicle* next = nullptr;
};
struct driver
{
	std::string name = "";
	std::string surrname = "";
	std::string licens = "";
	driver* next = nullptr;
};

vehicle* add_new_vehicle(vehicle** beg, vehicle** end, vehicle* tmp);
void delete_vehicle(vehicle** beg, vehicle** end);

driver* add_new_driver(driver** beg, driver** end, driver* tmp);
void delete_driver(driver** beg, driver** end);

bool load_vehicle_list(std::string name, vehicle** beg, vehicle** end);
bool load_driver_list(std::string name, driver** beg, driver** end);

vehicle* filter_vehicles(vehicle** g_filter);
bool vehicle_display_flag(vehicle* curr, vehicle* filter);
driver* filter_drivers(driver** g_filter);
bool  driver_display_flag(driver* curr, driver* filter);

void show_filtred_vehicle_list(vehicle* beg, vehicle* filter);
void show_filtred_drivers_list(driver* beg, driver* filter);

void generate_report(vehicle* v_beg, driver* d_beg, vehicle* v_filter, driver* d_filter);
void save_database(vehicle* v_beg, driver* d_beg, std::string d_name, std::string v_name);
void clear(vehicle** v_beg, driver** d_beg, vehicle** v_end, driver** d_end);
#endif