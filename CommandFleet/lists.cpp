#include "lists.h"

vehicle* crate_vehicle_list(vehicle** beg)
{
	*beg = new vehicle;
	return *beg;
}
void write_to_vehicle(vehicle** destiny, const vehicle* source)
{
	vehicle* curr = *destiny;
	curr->type = source->type;
	curr->brand = source->brand;
	curr->model = source->model;
	curr->licens = source->licens;
	curr->next = nullptr;
}
vehicle* add_new_vehicle(vehicle** beg, vehicle** end, vehicle* tmp)
{
	vehicle* curr = *beg;
	if (curr == nullptr)
	{
		*beg = crate_vehicle_list(beg);
		write_to_vehicle(beg, tmp);
		*end = *beg;
		return *beg;
	}
	else
	{
		curr = *end;
		curr->next = crate_vehicle_list(&curr->next);
		*end = curr->next;
		write_to_vehicle(&curr->next, tmp);
		return *end;
	}
}
void delete_vehicle(vehicle** beg, vehicle** end)
{
	vehicle* to_delete = *beg;
	vehicle* to_delete_data = new vehicle;
	filter_vehicles(&to_delete_data);
	if (to_delete_data->type == "" || to_delete_data->brand == "" || to_delete_data->model == "" || to_delete_data->licens == "")
	{
		std::cout << "Plese fill in all cells" << std::endl;
		delete to_delete_data;
		system("pause");
		return;
	}
	if (*beg == nullptr)
	{
		delete to_delete_data;
		return;
	}
	if (vehicle_display_flag(to_delete, to_delete_data))
	{
		if (to_delete->next == nullptr)
		{
			delete to_delete;
			delete to_delete_data;
			return;
		}
		else
		{
			*beg = to_delete->next;
			delete to_delete;
			delete to_delete_data;
			return;
		}
	}
	while (!vehicle_display_flag(to_delete->next, to_delete_data))
	{
		to_delete = to_delete->next;
		if (to_delete->next == nullptr)
		{
			system("cls");
			std::cout << "Vehicle you want to delete, don't exist!" << std::endl;
			delete to_delete_data;
			system("pause");
			return;
		}
	}
	vehicle* to_delete_prev = to_delete;
	to_delete = to_delete->next;
	vehicle* to_delete_next = to_delete->next;
	delete to_delete;
	to_delete_prev->next = to_delete_next;
	if (to_delete_prev->next == nullptr)
	{
		*end = to_delete_prev;
		delete to_delete_data;
		return;
	}
	else
	{
		*end = to_delete_prev->next;
		delete to_delete_data;
		return;
	}
	
}

bool load_vehicle_list(std::string name, vehicle** beg, vehicle** end)
{
	std::ifstream file(name);
	if (file.good() == false)
	{
		return false;
	}
	vehicle* tmp = nullptr;
	crate_vehicle_list(&tmp);
	while (file >> tmp->type)
	{
		file >> tmp->brand;
		file >> tmp->model;
		file >> tmp->licens;
		add_new_vehicle(beg, end, tmp);
	}
	file.close();
	return true;
}

vehicle* filter_vehicles(vehicle** g_filter)
{
	char choice = ' ';
	std::string trash;
	vehicle* filter = *g_filter;
	while (choice != 'e')
	{
		system("cls");
		std::cout << "Fill in filter parameters:" << std::endl;
		std::cout << "[1]Vehicle type: " << filter->type << std::endl;
		std::cout << "[2]Vehicle brand: " << filter->brand << std::endl;
		std::cout << "[3]Vehicle model: " << filter->model << std::endl;
		std::cout << "[4]Vehicle licens: " << filter->licens << std::endl;
		std::cout << "[r]reset" << std::endl;
		std::cout << "[e]Subbmit" << std::endl;
		std::cin >> choice;
		std::getline(std::cin, trash);
		switch (choice)
		{
		case '1':
			system("cls");
			std::cout << "Write vehicle type: ";
			std::cin >> filter->type;
			break;
		case '2':
			system("cls");
			std::cout << "Write vehicle brand: ";
			std::cin >> filter->brand;
			break;
		case '3':
			system("cls");
			std::cout << "Write vehicle model: ";
			std::cin >> filter->model;
			break;
		case '4':
			system("cls");
			std::cout << "Write vehicle licens: ";
			std::cin >> filter->licens;
			break;
		case 'r':
			filter->type = "";
			filter->brand = "";
			filter->model = "";
			filter->licens = "";
			break;
		case 'e':
			break;
		default:
			system("cls");
			std::cout << "Invalid flag" << std::endl;
			system("pause");
			break;
		}
	}
	return *g_filter;
}
bool vehicle_display_flag(vehicle* curr, vehicle* filter)
{
	if (curr == nullptr)
	{
		return true;
	}
	if (filter->type != "")
	{
		if (curr->type != filter->type)
		{
			return false;
		}
	}
	if (filter->brand != "")
	{
		if (curr->brand != filter->brand)
		{
			return false;
		}
	}
	if (filter->model != "")
	{
		if (curr->model != filter->model)
		{
			return false;
		}
	}
	if (filter->licens != "")
	{
		if (curr->licens != filter->licens)
		{
			return false;
		}
	}
	return true;
}

void delete_sorted_v(vehicle** beg)
{
	vehicle* first = *beg;
	while (first->next != nullptr)
	{
		vehicle* curr = *beg;
		vehicle* prev = nullptr;
		while (curr->next != nullptr)
		{
			prev = curr;
			curr = curr->next;
		}
		delete curr;
		prev->next = nullptr;
	}
	delete* beg;
	return;

}
int sort_vehicles_by()
{
	char choice = ' ';
	std::string trash;
	while (choice != 'e')
	{
		system("cls");
		std::cout << "Sort by:" << std::endl;
		std::cout << "[1]Vehicle Type" << std::endl;
		std::cout << "[2]Vehicle Brand" << std::endl;
		std::cout << "[3]Vehicle Model" << std::endl;
		std::cout << "[4]Vehicle licens" << std::endl;
		std::cout << "[e]Exit" << std::endl;
		std::cin >> choice;
		std::getline(std::cin, trash);
		switch (choice)
		{
		case '1':
			system("cls");
			return 1;
			break;
		case '2':
			system("cls");
			return 2;
			break;
		case '3':
			system("cls");
			return 3;
			break;
		case '4':
			system("cls");
			return 4;
			break;
		case 'e':
			system("cls");
			return 0;
			break;
		default:
			system("cls");
			std::cout << "Invalid flag" << std::endl;
			system("pause");
			break;
		}
	}
	return 0;
}
bool is_grater(std::string s1, std::string s2)
{
	int max;
	if (s1.length() > s2.length())
	{
		max = s1.length();
	}
	else
	{
		max = s2.length();
	}
	for (int i = 0; i < max; i++)
	{
		if (s1[i] < s2[i])
		{
			return true;
		}
		if (s2[i] < s1[i])
		{
			return false;
		}
	}
	return true;
}
bool is_less(std::string s1, std::string s2)
{
	int max;
	if (s1.length() > s2.length())
	{
		max = s1.length();
	}
	else
	{
		max = s2.length();
	}
	for (int i = 0; i < max; i++)
	{
		if (s1[i] > s2[i])
		{
			return true;
		}
		if (s2[i] > s1[i])
		{
			return false;
		}
	}
	return true;
}
void find_place_by_Type_i(vehicle** sorted_list, vehicle* base_next)
{
	vehicle* curr = *sorted_list;
	vehicle* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_grater(base_next->type, curr->type))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_vehicle_list(&curr_prev);
				write_to_vehicle(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_vehicle_list(&curr_prev->next);
			write_to_vehicle(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_vehicle_list(&curr_prev->next);
	write_to_vehicle(&curr_prev->next, base_next);
	return;
}
void find_place_by_Brand_i(vehicle** sorted_list, vehicle* base_next)
{
	vehicle* curr = *sorted_list;
	vehicle* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_grater(base_next->brand, curr->brand))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_vehicle_list(&curr_prev);
				write_to_vehicle(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_vehicle_list(&curr_prev->next);
			write_to_vehicle(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_vehicle_list(&curr_prev->next);
	write_to_vehicle(&curr_prev->next, base_next);
	return;
}
void find_place_by_Model_i(vehicle** sorted_list, vehicle* base_next)
{
	vehicle* curr = *sorted_list;
	vehicle* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_grater(base_next->model, curr->model))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_vehicle_list(&curr_prev);
				write_to_vehicle(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_vehicle_list(&curr_prev->next);
			write_to_vehicle(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_vehicle_list(&curr_prev->next);
	write_to_vehicle(&curr_prev->next, base_next);
	return;
}
void find_place_by_licens_i(vehicle** sorted_list, vehicle* base_next)
{
	vehicle* curr = *sorted_list;
	vehicle* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_grater(base_next->licens, curr->licens))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_vehicle_list(&curr_prev);
				write_to_vehicle(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_vehicle_list(&curr_prev->next);
			write_to_vehicle(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_vehicle_list(&curr_prev->next);
	write_to_vehicle(&curr_prev->next, base_next);
	return;
}
void find_place_by_Type_d(vehicle** sorted_list, vehicle* base_next)
{
	vehicle* curr = *sorted_list;
	vehicle* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_less(base_next->type, curr->type))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_vehicle_list(&curr_prev);
				write_to_vehicle(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_vehicle_list(&curr_prev->next);
			write_to_vehicle(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_vehicle_list(&curr_prev->next);
	write_to_vehicle(&curr_prev->next, base_next);
	return;
}
void find_place_by_Brand_d(vehicle** sorted_list, vehicle* base_next)
{
	vehicle* curr = *sorted_list;
	vehicle* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_less(base_next->brand, curr->brand))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_vehicle_list(&curr_prev);
				write_to_vehicle(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_vehicle_list(&curr_prev->next);
			write_to_vehicle(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_vehicle_list(&curr_prev->next);
	write_to_vehicle(&curr_prev->next, base_next);
	return;
}
void find_place_by_Model_d(vehicle** sorted_list, vehicle* base_next)
{
	vehicle* curr = *sorted_list;
	vehicle* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_less(base_next->model, curr->model))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_vehicle_list(&curr_prev);
				write_to_vehicle(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_vehicle_list(&curr_prev->next);
			write_to_vehicle(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_vehicle_list(&curr_prev->next);
	write_to_vehicle(&curr_prev->next, base_next);
	return;
}
void find_place_by_licens_d(vehicle** sorted_list, vehicle* base_next)
{
	vehicle* curr = *sorted_list;
	vehicle* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_less(base_next->licens, curr->licens))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_vehicle_list(&curr_prev);
				write_to_vehicle(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_vehicle_list(&curr_prev->next);
			write_to_vehicle(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_vehicle_list(&curr_prev->next);
	write_to_vehicle(&curr_prev->next, base_next);
	return;
}
vehicle* sort_vehicles(vehicle* base) 
{
	vehicle* sorted_list = crate_vehicle_list(&sorted_list);
	write_to_vehicle(&sorted_list, base);
	vehicle* base_next = base->next;
	std::string trash;
	system("cls");
	char tmp;
	std::cout << "[1]Incrising" << std::endl;
	std::cout << "[2]Decrising" << std::endl;
	std::cin >> tmp;
	std:getline(std::cin, trash);
	if (tmp != '1' && tmp != '2')
	{

		return nullptr;
	}
	int choice = sort_vehicles_by();
	switch (choice)
	{
		case 1:
			if (tmp == '1')
			{
				while (base_next != nullptr)
				{
					find_place_by_Type_i(&sorted_list, base_next);
					base_next = base_next->next;
				}
			}
			if (tmp == '2')
			{
				while (base_next != nullptr)
				{
					find_place_by_Type_d(&sorted_list, base_next);
					base_next = base_next->next;
				}
			}
			break;
		case 2:
			if (tmp == '1')
			{
				while (base_next != nullptr)
				{
					find_place_by_Brand_i(&sorted_list, base_next);
					base_next = base_next->next;
				}
			}
			if (tmp == '2')
			{
				while (base_next != nullptr)
				{
					find_place_by_Brand_d(&sorted_list, base_next);
					base_next = base_next->next;
				}
			}
		break;
		case 3:
			if (tmp == '1')
			{
				while (base_next != nullptr)
				{
					find_place_by_Model_i(&sorted_list, base_next);
					base_next = base_next->next;
				}
			}
			if (tmp == '2')
			{
				while (base_next != nullptr)
				{
					find_place_by_Model_d(&sorted_list, base_next);
					base_next = base_next->next;
				}
			}
		break;
		case 4:
			if (tmp == '1')
			{
				while (base_next != nullptr)
				{
					find_place_by_licens_i(&sorted_list, base_next);
					base_next = base_next->next;
				}
			}
			if (tmp == '2')
			{
				while (base_next != nullptr)
				{
					find_place_by_licens_d(&sorted_list, base_next);
					base_next = base_next->next;
				}
			}
		break;
		case 0:
			system("cls");
			return nullptr;
		break;
	}
	return sorted_list;
}

void show_filtred_vehicle_list(vehicle* beg, vehicle* filter)
{
	vehicle* curr;
	vehicle* tmp_curr;
	char choice = ' ';
	std::string trash;
	while (choice != '1' || choice != '2' || choice != 'e')
	{
		curr = beg;
		system("cls");
		std::cout << "Show:" << std::endl;
		std::cout << "[1]Just show" << std::endl;
		std::cout << "[2]Sort and show" << std::endl;
		std::cout << "[e]exit" << std::endl;
		std::cin >> choice;
		std::getline(std::cin, trash);
		switch (choice)
		{
		case '1':
			system("cls");
			while (curr != nullptr)
			{
				if (vehicle_display_flag(curr, filter))
				{
					std::cout << curr->type << " " << curr->brand << " " << curr->model << " " << curr->licens << std::endl;
				}
				curr = curr->next;
			}
			system("pause");
			break;
		case '2':
			system("cls");
			curr = sort_vehicles(beg);
			if (curr == nullptr)
			{
				std::cout << "Insert valid option number" << std::endl;
				system("pasue");
				return;
			}
			tmp_curr = curr;
			while (curr != nullptr)
			{
				if (vehicle_display_flag(curr, filter))
				{
					std::cout << curr->type << " " << curr->brand << " " << curr->model << " " << curr->licens << std::endl;
				}
				curr = curr->next;
			}
			curr = tmp_curr;
			delete_sorted_v(&curr);
			system("pause");
			break;
		case 'e':
			system("cls");
			return;
			break;
		default:
			system("cls");
			std::cout << "Invalid flag" << std::endl;
			system("pause");
			break;
		}
		system("cls");
	}
}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
driver* crate_driver_list(driver** beg)
{
	*beg = new driver;
	return *beg;
}
void write_to_driver(driver** destiny, const driver* source)
{
	driver* curr = *destiny;
	curr->name = source->name;
	curr->surrname = source->surrname;
	curr->licens = source->licens;
	curr->next = nullptr;
}
driver* add_new_driver(driver** beg, driver** end, driver* tmp)
{
	driver* curr = *beg;
	if (curr == nullptr)
	{
		*beg = crate_driver_list(beg);
		write_to_driver(beg, tmp);
		*end = *beg;
		return *beg;
	}
	else
	{
		curr = *end;
		curr->next = crate_driver_list(&curr->next);
		*end = curr->next;
		write_to_driver(&curr->next, tmp);
		return *end;
	}
}
void delete_driver(driver** beg, driver** end)
{
	driver* to_delete = *beg;
	driver* to_delete_data = new driver;
	filter_drivers(&to_delete_data);
	if (to_delete_data->name == "" || to_delete_data->surrname == "" || to_delete_data->licens == "")
	{
		std::cout << "Plese fill in all cells" << std::endl;
		system("pause");
		return;
	}
	if (*beg == nullptr)
	{
		return;
	}
	if (driver_display_flag(to_delete, to_delete_data))
	{
		if (to_delete->next == nullptr)
		{
			delete to_delete;
			return;
		}
		else
		{
			*beg = to_delete->next;
			delete to_delete;
			return;
		}
	}
	while (!driver_display_flag(to_delete->next, to_delete_data))
	{
		to_delete = to_delete->next;
		if (to_delete->next == nullptr)
		{
			std::cout << "Driver you want to delete, don't exist!" << std::endl;
			system("pause");
			return;
		}
	}
	driver* to_delete_prev = to_delete;
	to_delete = to_delete->next;
	driver* to_delete_next = to_delete->next;
	delete to_delete;
	to_delete_prev->next = to_delete_next;
	if (to_delete_prev->next == nullptr)
	{
		*end = to_delete_prev;
		return;
	}
	else
	{
		*end = to_delete_prev->next;
		return;
	}
}

bool load_driver_list(std::string name, driver** beg, driver** end)
{
	std::fstream file(name);
	if (file.good() == false) {
		return false;
	}
	driver* tmp = nullptr;
	crate_driver_list(&tmp);
	while (file >> tmp->name)
	{
		file >> tmp->surrname;
		file >> tmp->licens;
		add_new_driver(beg, end, tmp);
	}
	file.close();
	return true;
}

driver* filter_drivers(driver** g_filter)
{
	char choice = ' ';
	std::string trash;
	driver* filter = *g_filter;
	while (choice != 'e')
	{
		system("cls");
		std::cout << "Fill in filter parameters:" << std::endl;
		std::cout << "[1]Driver Name: " << filter->name << std::endl;
		std::cout << "[2]Driver Surrname: " << filter->surrname << std::endl;
		std::cout << "[3]Driver licens: " << filter->licens << std::endl;
		std::cout << "[r]reset" << std::endl;
		std::cout << "[e]Subbmit" << std::endl;
		std::cin >> choice;
		std::getline(std::cin, trash);
		switch (choice)
		{
		case '1':
			system("cls");
			std::cout << "Write driver name: ";
			std::cin >> filter->name;
			break;
		case '2':
			system("cls");
			std::cout << "Write driver surrname: ";
			std::cin >> filter->surrname;
			break;
		case '3':
			system("cls");
			std::cout << "Write driver licens: ";
			std::cin >> filter->licens;
			break;
		case 'r':
			filter->name = "";
			filter->surrname = "";
			filter->licens = "";
			break;
		case 'e':
			break;
		default:
			system("cls");
			std::cout << "Invalid flag";
			system("pause");
			break;
		}
		system("cls");
	}
	return *g_filter;
}
bool  driver_display_flag(driver* curr, driver* filter)
{
	if (curr == nullptr)
	{
		return true;
	}
	if (filter->name != "")
	{
		if (curr->name != filter->name)
		{
			return false;
		}
	}
	if (filter->surrname != "")
	{
		if (curr->surrname != filter->surrname)
		{
			return false;
		}
	}
	if (filter->licens != "")
	{
		if (curr->licens != filter->licens)
		{
			return false;
		}
	}
	return true;
}

void delete_sorted_list(driver** beg)
{
	driver* first = *beg;
	while (first->next != nullptr)
	{
		driver* curr = *beg;
		driver* prev = nullptr;
		while (curr->next != nullptr)
		{
			prev = curr;
			curr = curr->next;
		}
		delete curr;
		prev->next = nullptr;
	}
	delete* beg;
	return;

}
int sort_drivers_by()
{
	char choice = ' ';
	std::string trash;
	while (choice != 'e')
	{
		system("cls");
		std::cout << "Sort by:" << std::endl;
		std::cout << "[1]Driver Name" << std::endl;
		std::cout << "[2]Driver Surrname" << std::endl;
		std::cout << "[3]Driver licens" << std::endl;
		std::cout << "[e]Exit" << std::endl;
		std::cin >> choice;
		std::getline(std::cin, trash);
		switch (choice)
		{
		case '1':
			system("cls");
			return 1;
			break;
		case '2':
			system("cls");
			return 2;
			break;
		case '3':
			system("cls");
			return 3;
			break;
		case 'e':
			system("cls");
			return 0;
			break;
		default:
			system("cls");
			std::cout << "Invalid flag" << std::endl;
			system("pause");
			break;
		}
	}
	return 0;
}
void find_place_by_name_i(driver** sorted_list, driver* base_next)
{
	driver* curr = *sorted_list;
	driver* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_grater(base_next->name, curr->name))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_driver_list(&curr_prev);
				write_to_driver(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_driver_list(&curr_prev->next);
			write_to_driver(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_driver_list(&curr_prev->next);
	write_to_driver(&curr_prev->next, base_next);
	return;
}
void find_place_by_surrname_i(driver** sorted_list, driver* base_next)
{
	driver* curr = *sorted_list;
	driver* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_grater(base_next->surrname, curr->surrname))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_driver_list(&curr_prev);
				write_to_driver(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_driver_list(&curr_prev->next);
			write_to_driver(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_driver_list(&curr_prev->next);
	write_to_driver(&curr_prev->next, base_next);
	return;
}
void find_place_by_licens_i(driver** sorted_list, driver* base_next)
{
	driver* curr = *sorted_list;
	driver* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_grater(base_next->licens, curr->licens))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_driver_list(&curr_prev);
				write_to_driver(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_driver_list(&curr_prev->next);
			write_to_driver(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_driver_list(&curr_prev->next);
	write_to_driver(&curr_prev->next, base_next);
	return;
}
void find_place_by_name_d(driver** sorted_list, driver* base_next)
{
	driver* curr = *sorted_list;
	driver* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_less(base_next->name, curr->name))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_driver_list(&curr_prev);
				write_to_driver(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_driver_list(&curr_prev->next);
			write_to_driver(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_driver_list(&curr_prev->next);
	write_to_driver(&curr_prev->next, base_next);
	return;
}
void find_place_by_surrname_d(driver** sorted_list, driver* base_next)
{
	driver* curr = *sorted_list;
	driver* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_less(base_next->surrname, curr->surrname))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_driver_list(&curr_prev);
				write_to_driver(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_driver_list(&curr_prev->next);
			write_to_driver(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_driver_list(&curr_prev->next);
	write_to_driver(&curr_prev->next, base_next);
	return;
}
void find_place_by_licens_d(driver** sorted_list, driver* base_next)
{
	driver* curr = *sorted_list;
	driver* curr_prev = nullptr;
	while (curr != nullptr)
	{
		if (is_less(base_next->licens, curr->licens))
		{
			if (curr_prev == nullptr)
			{
				curr_prev = crate_driver_list(&curr_prev);
				write_to_driver(&curr_prev, base_next);
				curr_prev->next = curr;
				*sorted_list = curr_prev;
				return;
			}
			curr_prev->next = crate_driver_list(&curr_prev->next);
			write_to_driver(&curr_prev->next, base_next);
			curr_prev->next->next = curr;
			return;
		}
		curr_prev = curr;
		curr = curr->next;
	}
	if (curr_prev->next == nullptr)
	{
		curr = *sorted_list;
		while (curr->next != nullptr)
		{
			curr = curr->next;
		}
		curr_prev = curr;
	}
	curr_prev->next = crate_driver_list(&curr_prev->next);
	write_to_driver(&curr_prev->next, base_next);
	return;
}
driver* sort_drivers(driver* base)
{
	driver* sorted_list = crate_driver_list(&sorted_list);
	write_to_driver(&sorted_list, base);
	driver* base_next = base->next;
	std::string trash;
	system("cls");
	char tmp;
	std::cout << "[1]Incrising" << std::endl;
	std::cout << "[2]Decrising" << std::endl;
	std::cin >> tmp;
	std:getline(std::cin, trash);
	if (tmp != '1' && tmp != '2')
	{
		return nullptr;
	}
	int choice = sort_drivers_by();
	switch (choice)
	{
	case 1:
		if (tmp == '1')
		{
			while (base_next != nullptr)
			{
				find_place_by_name_i(&sorted_list, base_next);
				base_next = base_next->next;
			}
		}
		if (tmp == '2')
		{
			while (base_next != nullptr)
			{
				find_place_by_name_d(&sorted_list, base_next);
				base_next = base_next->next;
			}
		}
		break;
	case 2:
		if (tmp == '1')
		{
			while (base_next != nullptr)
			{
				find_place_by_surrname_i(&sorted_list, base_next);
				base_next = base_next->next;
			}
		}
		if (tmp == '2')
		{
			while (base_next != nullptr)
			{
				find_place_by_surrname_d(&sorted_list, base_next);
				base_next = base_next->next;
			}
		}
		break;
	case 3:
		if (tmp == '1')
		{
			while (base_next != nullptr)
			{
				find_place_by_licens_i(&sorted_list, base_next);
				base_next = base_next->next;
			}
		}
		if (tmp == '2')
		{
			while (base_next != nullptr)
			{
				find_place_by_licens_d(&sorted_list, base_next);
				base_next = base_next->next;
			}
		}
		break;
	case 0:
		return nullptr;
		break;
	}
	return sorted_list;
}

void show_filtred_drivers_list(driver* beg, driver* filter)
{
	driver* curr;
	driver* tmp_curr;
	char choice = ' ';
	std::string trash;
	while ((choice != '1') || (choice != '2') || (choice != 'e'))
	{
		curr = beg;
		system("cls");
		std::cout << "Show:" << std::endl;
		std::cout << "[1]Just show" << std::endl;
		std::cout << "[2]Sort and show" << std::endl;
		std::cout << "[e]exit" << std::endl;
		std::cin >> choice;
		std::getline(std::cin, trash);
		switch (choice)
		{
		case '1':
			system("cls");
			while (curr != nullptr)
			{
				if (driver_display_flag(curr, filter))
				{
					std::cout << curr->name << " " << curr->surrname << " " << curr->licens << std::endl;
				}
				curr = curr->next;
			}
			system("pause");
			break;
		case '2':
			system("cls");
			curr = sort_drivers(beg);
			if (curr == nullptr)
			{
				std::cout << "Insert valid option number" << std::endl;
				system("pasue");
				return;
			}
			tmp_curr = curr;
			while (curr != nullptr)
			{
				if (driver_display_flag(curr, filter))
				{
					std::cout << curr->name << " " << curr->surrname << " " << curr->licens << std::endl;
				}
				curr = curr->next;
			}
			curr = tmp_curr;
			delete_sorted_list(&curr);
			system("pause");
			break;
		case 'e':
			system("cls");
			return;
			break;
		default:
			system("cls");
			std::cout << "Invalid flag" << std::endl;
			system("pause");
			break;
		}
		system("cls");
	}

}
/////////////////////////////////////////////////////////////////////////////////////////////////////////////
bool can_drive(driver* c_driver, vehicle* c_vehicle)
{
	if ((c_vehicle->licens == "AM") && (c_driver->licens != ""))
	{
		return true;
	}
	if (c_driver->licens == "A1")
	{
		if (c_vehicle->licens == "A1")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (c_driver->licens == "A2")
	{
		if ((c_vehicle->licens == "A2") || (c_vehicle->licens == "A1"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (c_driver->licens == "A")
	{
		if ((c_vehicle->licens == "A2") || (c_vehicle->licens == "A1") || (c_vehicle->licens == "A"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (c_driver->licens == "B1")
	{
		if (c_vehicle->licens == "B1")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	//mog¹ ci¹gnikiem jeŸdziæ
	if (c_driver->licens == "B")
	{
		if ((c_vehicle->licens == "A2") || (c_vehicle->licens == "A1") || (c_vehicle->licens == "B") || (c_vehicle->licens == "T"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (c_driver->licens == "C1")
	{

		if (c_vehicle->licens == "C1" || (c_vehicle->licens == "T"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (c_driver->licens == "C")
	{

		if ((c_vehicle->licens == "A2") || (c_vehicle->licens == "C1") || (c_vehicle->licens == "B") || (c_vehicle->licens == "C") || (c_vehicle->licens == "T"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (c_driver->licens == "D1")
	{
		if ((c_vehicle->licens == "D1") || (c_vehicle->licens == "T"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (c_driver->licens == "D")
	{
		if ((c_vehicle->licens == "D") || (c_vehicle->licens == "T") || (c_vehicle->licens == "D1"))
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	if (c_driver->licens == "T")
	{
		if (c_vehicle->licens == "T")
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	return false;
}

void generate_report(vehicle* v_beg, driver* d_beg, vehicle* v_filter, driver* d_filter)
{
	driver* d_curr = d_beg;
	vehicle* v_curr = v_beg;
	while (d_curr != nullptr)
	{
		if (driver_display_flag(d_curr, d_filter))
		{
			std::cout << d_curr->name << " " << d_curr->surrname << " " << d_curr->licens << ": " << std::endl;
			vehicle* v_curr = v_beg;
			while (v_curr != nullptr)
			{
				if (vehicle_display_flag(v_curr, v_filter) && can_drive(d_curr, v_curr))
				{
					std::cout << "    " << v_curr->type << " " << v_curr->brand << " " << v_curr->model << " " << v_curr->licens << std::endl;
				}
				v_curr = v_curr->next;
			}
		}
		d_curr = d_curr->next;
	}
	system("pause");
}
void save_database(vehicle* v_beg, driver* d_beg, std::string d_name, std::string v_name)
{
	std::ofstream d_file(d_name);
	while (d_beg != nullptr)
	{
		d_file << d_beg->name << " " << d_beg->surrname << " " << d_beg->licens << std::endl;
		d_beg = d_beg->next;
	}
	d_file.close();
	std::ofstream v_file(v_name);
	while (v_beg != nullptr)
	{
		v_file << v_beg->type << " " << v_beg->brand << " " << v_beg->model << " " << v_beg->licens << std::endl;
		v_beg = v_beg->next;
	}
	v_file.close();
}
void clear(vehicle** v_beg, driver** d_beg, vehicle** v_end, driver** d_end) //te¿ problemy
{
	while (*v_end != *v_beg)
	{
		vehicle* v_tmp = *v_beg;
		vehicle* v_prev = nullptr;
		while (v_tmp->next != nullptr)
		{
			v_prev = v_tmp;
			v_tmp = v_tmp->next;
		}
		delete v_tmp;
		v_prev->next = nullptr;
		*v_end = v_prev;
	}
	delete* v_beg;
	while (*d_end != *d_beg)
	{
		driver* d_tmp = *d_beg;
		driver* d_prev = nullptr;
		while (d_tmp->next != nullptr)
		{
			d_prev = d_tmp;
			d_tmp = d_tmp->next;
		}
		delete d_tmp;
		d_prev->next = nullptr;
		*d_end = d_prev;
	}
	delete* d_beg;
}
