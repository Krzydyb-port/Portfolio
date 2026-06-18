#include "lists.h"

int main(int argc, char** argv) 
{
	std::string v_file_name = "";
	std::string d_file_name = "";
	if (argc != 5)
	{
		system("cls");
		std::cout << "Invalid number of arguments!" << std::endl;
		std::cout << "Usege: CommandFleet.exe -v <vehicles list> -d <drivers list>";
		return -1;
	}
	for (int i = 1; i < argc; i++)
	{
		if (!strcmp(argv[i], "-v"))
		{
			if (i == argc-1)
			{
				system("cls");
				std::cout << "Invalid flags!" << std::endl;
				std::cout << "Usege: CommandFleet.exe -v <vehicles list> -d <drivers list>";
				return -1;
			}
			v_file_name = argv[i+1];
		}
		if (!strcmp(argv[i], "-d"))
		{
			if (i == argc-1)
			{
				system("cls");
				std::cout << "Invalid flags!" << std::endl;
				std::cout << "Usege: FleetDatabase.exe -v <vehicles list> -d <drivers list>";
				return -1;
			}
			d_file_name = argv[i+1];
		}
	}
	std::string trash;
	vehicle* v_beg = nullptr;
	vehicle* v_end = nullptr;
	vehicle* v_tmp = new vehicle;
	vehicle* gv_filter = new vehicle;
	driver* d_beg = nullptr;
	driver* d_end = nullptr;
	driver* d_tmp = new driver;
	driver* gd_filter = new driver;
	char choice = ' ';
	bool loaded_v = load_vehicle_list(v_file_name, &v_beg, &v_end);
	if (loaded_v == false)
	{
		std::cout << "Plese insert vehicles list file in same folder as commandfleet.exe";
		std::cout << "or insert patch to these file" << std::endl;
		std::cout << "Remember to write file name with extention.txt";
		return -1;
	}
	bool loaded_d = load_driver_list(d_file_name, &d_beg, &d_end);
	if (loaded_d == false)
	{
		std::cout << "Plese insert drivers list file in same folder as commandfleet.exe";
		std::cout << "or insert patch to these file" << std::endl;
		std::cout << "Remember to write file name with extention.txt";
		return -1;
	}
	while (choice != 'e')
	{
		system("cls");
		std::cout << "[1] Add vehicle" << std::endl;
		std::cout << "[2] Add driver" << std::endl;
		std::cout << "[3] Delete vehicle" << std::endl;
		std::cout << "[4] Delete driver" << std::endl;
		std::cout << "[5] Show vehicle list" << std::endl;
		std::cout << "[6] Set vehicle filter" << std::endl;
		std::cout << "[7] Show driver list" << std::endl;
		std::cout << "[8] Set driver filter" << std::endl;
		std::cout << "[9] Generate Report" << std::endl;
		std::cout << "[e] Exit" << std::endl;
		std::cout << "Choice: ";
		std::cin >> choice;
		std::getline(std::cin, trash);
		switch (choice)
		{
		case '1':
			system("cls");
			std::cout << "<Type> <Brand> <Model> <Licens>" << std::endl;
			std::cin >> v_tmp->type >> v_tmp->brand >> v_tmp->model >> v_tmp->licens;
			add_new_vehicle(&v_beg, &v_end, v_tmp);
			break;
		case '2':
			system("cls");
			std::cout << "<Name> <Surrname> <Licens>" << std::endl;
			std::cin >> d_tmp->name >> d_tmp->surrname >> d_tmp->licens;
			add_new_driver(&d_beg, &d_end, d_tmp);
			break;
		case '3':
			system("cls");
			delete_vehicle(&v_beg, &v_end);
			break;
		case '4':
			system("cls");
			delete_driver(&d_beg, &d_end);
			break;
		case '5':
			system("cls");
			show_filtred_vehicle_list(v_beg, gv_filter);
			break;
		case '6':
			system("cls");
			filter_vehicles(&gv_filter);
			break;
		case '7':
			system("cls");
			show_filtred_drivers_list(d_beg, gd_filter);
			break;
		case '8':
			system("cls");
			filter_drivers(&gd_filter);
			break;
		case '9':
			system("cls");
			generate_report(v_beg, d_beg, gv_filter, gd_filter);
			break;
		case 'e':
			system("cls");
			std::cout << "Have a good day!";
			save_database(v_beg, d_beg, d_file_name, v_file_name);
			clear(&v_beg, &d_beg, &v_end, &d_end);
			delete gv_filter;
			delete gd_filter;
			delete v_tmp;
			delete d_tmp;
			return 0;
			break;
		default:
			system("cls");
			std::cout << "Invalid flag, plese choose number from menu" << std::endl;
			system("pause");
			break;
		}
		system("cls");
	}
}