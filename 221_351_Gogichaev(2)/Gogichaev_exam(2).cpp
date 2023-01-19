#include "Game_Gogichaev(2).h"

Game_Gogichaev::Game_Gogichaev()
{
	this->year = 1;
	this->phase = 1;
}

Game_Gogichaev::~Game_Gogichaev()
{
}

// инициализирующий конструктор
Game_Gogichaev::Game_Gogichaev(int gamers_count)
{
	this->year = 1;
	this->phase = 1;
	for (int i = 0; i < gamers_count; i++)
	{
		this->gamers.push_back(Gamer());
		std::cout << "Name >> ";
		std::cin >> this->gamers[i].name;
		this->gamers[i].has_additional_cube = false;
		this->gamers[i].building_tokens = 17;
		this->gamers[i].has_adviser = false;
		this->gamers[i].military_register = 0;
		this->gamers[i].victory_points = 0;
	}
	this->advisers.push_back({ "Jester", "" }); // шут
	this->advisers.push_back({ "Squire", "" }); // сквайр
	this->advisers.push_back({ "Architect", "" }); // зодчий
	this->advisers.push_back({ "Merchant", "" }); // купец
	this->advisers.push_back({ "Sergeant", "" }); // сержант
	this->advisers.push_back({ "Alchemist", "" }); // алхимик
	this->advisers.push_back({ "Astrologer", "" }); // звездочёт
	this->advisers.push_back({ "Treasurer", "" }); // казначей
	this->advisers.push_back({ "Huntress", "" }); // охотница
	this->advisers.push_back({ "General", "" }); // генерал
	this->advisers.push_back({ "Gunsmith", "" }); // оружейник
	this->advisers.push_back({ "Duchess", "" }); // герцогиня
	this->advisers.push_back({ "Hero", "" }); // герой
	this->advisers.push_back({ "Smuggler", "" }); // контрабандист
	this->advisers.push_back({ "Inventor", "" }); // изобретатель
	this->advisers.push_back({ "Wizard", "" }); // волшебник
	this->advisers.push_back({ "Queen", "" }); // королева
	this->advisers.push_back({ "King", "" }); // король
}

// копирующий конструктор
Game_Gogichaev::Game_Gogichaev(const Game_Gogichaev& c_game)
{
	// копирование игроков
	for (int i = 0; i < c_game.gamers.size(); i++)
	{
		if (this->gamers.size() < i + 1) // если это новый объект
			this->gamers.push_back(c_game.gamers[i]);
		else // если существуюший
			this->gamers[i] = c_game.gamers[i];
	}
	// копирование советников
	for (int i = 0; i < 18; i++)
	{
		if (this->advisers.size() < i + 1)
			this->advisers.push_back(c_game.advisers[i]);
		else
			this->advisers[i] = c_game.advisers[i];
	}
	this->year = c_game.year;
	this->phase = c_game.phase;
	this->enemy = c_game.enemy;
}

void Game_Gogichaev::phase1()
{
	std::cout << "##### Year " << this->year << " Phase 1. Help of the king ######" << std::endl;
	if (this->year == 1 && this->phase == 1) {
		// на первой фазе выбираем только товар
		for (int i = 0; i < this->gamers.size(); i++)
		{
			std::string product;
			std::cout << "Gamer " << this->gamers[i].name << ", choose your product: gold/wood/stone" << std::endl;
			std::cin >> product;
			if (product == "gold") this->gamers[i].gold++;
			else if (product == "wood") this->gamers[i].wood++;
			else if (product == "stone") this->gamers[i].stone++;
		}
	}
	else
	{
		// выбираем по меньшему количеству зданий
		std::vector<Gamer> candidates;
		int min_buildings = this->gamers[0].buildings.size();
		for (auto g : this->gamers)
		{
			if (g.buildings.size() < min_buildings)
			{
				min_buildings = g.buildings.size();
				candidates.clear();
				candidates.push_back(g);
			}
			else if (g.buildings.size() == min_buildings)
			{
				candidates.push_back(g);
			}
		}
		// если кандидат один
		if (candidates.size() == 1)
		{
			for (int i = 0; i < this->gamers.size(); i++)
				if (this->gamers[i].name == candidates[0].name) this->gamers[i].has_additional_cube = true;
		}
		// если их несколько то сравниваем по сумме товаров
		else {
			std::vector<Gamer> new_candidates;
			int count = 0;
			int sum_min = candidates[0].gold + candidates[0].wood + candidates[0].stone;
			for (auto c : candidates)
			{
				int sum_p = c.gold + c.wood + c.stone;
				if (sum_p < sum_min)
				{
					sum_min = c.gold + c.wood + c.stone;
					new_candidates.clear();
					new_candidates.push_back(c);
				}
				else if (sum_min == sum_p) new_candidates.push_back(c);
			}
			// если нашёлся кандидат
			if (count == 1)
			{
				for (int i = 0; i < this->gamers.size(); i++)
					if (this->gamers[i].name == new_candidates[0].name) this->gamers[i].has_additional_cube = true;
			}
			else
			{
				// если их несколько то выдаём товары всем
				for (int i = 0; i < this->gamers.size(); i++)
				{
					for (auto nc : new_candidates)
						if (nc.name == this->gamers[i].name)
						{
							std::string product;
							std::cout << "Gamer " << this->gamers[i].name << ", choose your product: gold/wood/stone";
							std::cin >> product;
							if (product == "gold") this->gamers[i].gold++;
							else if (product == "wood") this->gamers[i].wood++;
							else if (product == "stone") this->gamers[i].stone++;
						}
				}
			}
		}
	}
}

void Game_Gogichaev::phase3()
{
	// выдаём ПО тем у кого больше всего зданий
	this->phase++;
	std::cout << "##### Year " << this->year << " Phase 3. Royal award ######" << std::endl;
	std::vector<Gamer> candidates;
	int max_buildings = this->gamers[0].buildings.size();
	// поиск кандидатов
	for (auto g : this->gamers)
	{
		if (g.buildings.size() > max_buildings)
		{
			max_buildings = g.buildings.size();
			candidates.clear();
			candidates.push_back(g);
		}
		else if (g.buildings.size() == max_buildings) candidates.push_back(g);
	}
	// начисление очков
	for (int i = 0; i < this->gamers.size(); i++)
	{
		for (auto c : candidates)
		{
			if (this->gamers[i].name == c.name)
			{
				std::cout << "Gamer " << c.name << " receives victory point" << std::endl;
				this->gamers[i].victory_points++;
			}
		}
	}
}

void Game_Gogichaev::phase5()
{
	// королевский посланник
	this->phase++;
	std::cout << "##### Year " << this->year << " Phase 5. Royal envoy ######" << std::endl;
	// выбираем по меньшему количеству зданий
	std::vector<Gamer> candidates;
	int min_buildings = this->gamers[0].buildings.size();
	for (auto g : this->gamers)
	{
		if (g.buildings.size() < min_buildings)
		{
			min_buildings = g.buildings.size();
			candidates.clear();
			candidates.push_back(g);
		}
		else if (g.buildings.size() == min_buildings)
		{
			candidates.push_back(g);
		}
	}
	// если кандидат один
	if (candidates.size() == 1)
	{
		for (int i = 0; i < this->gamers.size(); i++)
			if (this->gamers[i].name == candidates[0].name) this->gamers[i].has_adviser = true;
	}
	// если их несколько то сравниваем по сумме товаров
	else {
		std::vector<Gamer> new_candidates;
		int count = 0;
		int sum_min = candidates[0].gold + candidates[0].wood + candidates[0].stone;
		for (auto c : candidates)
		{
			int sum_p = c.gold + c.wood + c.stone;
			if (sum_p < sum_min)
			{
				sum_min = c.gold + c.wood + c.stone;
				new_candidates.clear();
				new_candidates.push_back(c);
			}
			else if (sum_min == sum_p) new_candidates.push_back(c);
		}
		// если нашёлся кандидат
		if (count == 1)
		{
			for (int i = 0; i < this->gamers.size(); i++)
				if (this->gamers[i].name == new_candidates[0].name) this->gamers[i].has_adviser = true;
		}
	}
	for (auto g : this->gamers) std::cout << "Gamer " << g.name << " now has royal envoy" << std::endl;
}

void Game_Gogichaev::phase7()
{
	// наём воинов
	this->phase++;
	std::cout << "##### Year " << this->year << " Phase 7. Hiring warriors ######" << std::endl;
	for (int i = 0; i < this->gamers.size(); i++)
	{
		while (true)
		{
			std::cout << "Gamer " << this->gamers[i].name << ", you have:" << std::endl <<
				"Gold: " << this->gamers[i].gold << std::endl <<
				"Wood: " << this->gamers[i].wood << std::endl <<
				"Stone: " << this->gamers[i].stone << std::endl <<
				"What you want to do? Enter HIRE/PASS" << std::endl;
			std::string action;
			std::cin >> action;
			if (action == "PASS") break;
			std::cout << "Gamer " << this->gamers[i].name << ", what items do you want to donate? Enter pair like: gold gold, or stone wood etc." << std::endl;
			std::string first;
			std::cin >> first;
			std::string second;
			std::cin >> second;

			if (first == "gold") this->gamers[i].gold--;
			else if (first == "wood") this->gamers[i].wood--;
			else if (first == "stone") this->gamers[i].stone--;

			if (second == "gold") this->gamers[i].gold--;
			else if (second == "wood") this->gamers[i].wood--;
			else if (second == "stone") this->gamers[i].stone--;

			this->gamers[i].military_register++;
		}
	}
}

void Game_Gogichaev::phase8()
{

}

void Game_Gogichaev::phase246()
{
	this->phase++;
	std::cout << "##### Year " << this->year << " Phase " << this->phase << ". Harvest ######" << std::endl;
	this->phase246_bones();
	this->phase246_advisor();
	//advisor_help();
	//building();
}

void Game_Gogichaev::phase246_bones()
{
	std::vector<int> point_sums;
	for (int i = 0; i < this->gamers.size(); i++)
	{
		// бросаем кости
		this->gamers[i].cube_1 = rand() % 6 + 1;
		this->gamers[i].cube_2 = rand() % 6 + 1;
		this->gamers[i].cube_3 = rand() % 6 + 1;
		if (this->gamers[i].has_additional_cube) this->gamers[i].additional_cube = rand() % 6 + 1;
		// выводим результаты
		std::cout << "Gamer " << this->gamers[i].name << " has points: " <<
			this->gamers[i].cube_1 << " " <<
			this->gamers[i].cube_2 << " " <<
			this->gamers[i].cube_3 << " " <<
			((this->gamers[i].has_additional_cube) ? this->gamers[i].cube_1 : 0);
		// считаем сумму очков
		point_sums.push_back(this->gamers[i].cube_1 + this->gamers[i].cube_2 + this->gamers[i].cube_3 + this->gamers[i].additional_cube);
		std::cout << " ; Sum: " << point_sums.back() << std::endl;
	}
	// расставляем игроков
	sort(point_sums.begin(), point_sums.end());
	std::vector<Gamer> gamers_new_order;
	for (auto points : point_sums)
	{
		for (auto g : gamers)
			if (g.cube_1 + g.cube_2 + g.cube_3 + g.additional_cube == points) gamers_new_order.push_back(g);
	}
	this->gamers = gamers_new_order;
	for (int i = 0; i < this->gamers.size(); i++)
		std::cout << i << ". " << this->gamers[i].name << std::endl;
}

void Game_Gogichaev::phase246_advisor()
{
	int pass_count = 0;
	while (pass_count != this->gamers.size())
	{
		for (int g = 0; g < this->gamers.size(); g++)
		{
			// показываем советников
			std::cout << " - Royal advisers: - " << std::endl;
			for (int i = 0; i < this->advisers.size(); i++)
			{
				std::cout << i + 1 << ". " << this->advisers[i].adviser_name << " : " <<
					((this->advisers[i].gamer_name == "") ? "Free" : this->advisers[i].gamer_name) << std::endl;
			}
			// показываем что есть у игрока
			std::cout << this->gamers[g].name << ", you have: " << std::endl;
			if (this->gamers[g].cube_1 != 0) std::cout << "Cube 1: " << this->gamers[g].cube_1 << std::endl;
			if (this->gamers[g].cube_2 != 0) std::cout << "Cube 2: " << this->gamers[g].cube_2 << std::endl;
			if (this->gamers[g].cube_3 != 0) std::cout << "Cube 3: " << this->gamers[g].cube_3 << std::endl;
			if (this->gamers[g].has_additional_cube) std::cout << "Additional cube: " << this->gamers[g].additional_cube << std::endl;
			if (this->gamers[g].has_adviser) std::cout << "Royal adviser: " << this->gamers[g].additional_cube << std::endl;
			if (this->gamers[g].has_plus_two) std::cout << "+2: " << "yes" << std::endl;
			while (true)
			{
				// выбор
				std::cout << "What are you waht to do? influence/pass" << std::endl;
				std::string action;
				std::cin >> action;
				if (action == "pass") {
					pass_count++;
					break;
				}
				int adviser_number;
				std::cout << "Enter the number of the adviser: ";
				std::cin >> adviser_number;
				if (this->advisers[adviser_number - 1].gamer_name != "" && this->gamers[g].has_adviser == false)
				{
					std::cout << "You do not have royal envoy, choose another adviser or pass" << std::endl;
					continue;
				}
				Gamer saved_gamer = this->gamers[g];
				std::cout << "Enter what you want to use; input count and your choices: 5 cube1 cube2 cube3 add_cube +2" << std::endl;
				int count;
				std::cin >> count;
				std::string choice;
				int sum_points = 0;
				for (int q = 0; q < count; q++)
				{
					std::cin >> choice;
					if (choice == "cube1") { sum_points += this->gamers[g].cube_1; this->gamers[g].cube_1 = 0; }
					if (choice == "cube2") { sum_points += this->gamers[g].cube_2; this->gamers[g].cube_2 = 0; }
					if (choice == "cube3") { sum_points += this->gamers[g].cube_3; this->gamers[g].cube_3 = 0; }
					if (choice == "add_cube") { sum_points += this->gamers[g].additional_cube; this->gamers[g].has_additional_cube = false; }
					if (choice == "+2") { sum_points += 2; this->gamers[g].has_plus_two = false; }
				}
				if (sum_points != adviser_number)
				{
					std::cout << "You did not have enough points to complete this action" << std::endl;
					this->gamers[g] = saved_gamer;
					continue;
				}
				this->advisers[adviser_number - 1].gamer_name = this->gamers[g].name;
				break;
			}
		}
	}
}

void advisor_help(std::string advisor_name, Gamer& gamer)
{

}

void building(std::string building_name, Gamer& gamer)
{

}

bool Game_Gogichaev::load_game(std::string filename)
{
	return true;
}

bool Game_Gogichaev::save_game(std::string filename)
{
	return true;
}
