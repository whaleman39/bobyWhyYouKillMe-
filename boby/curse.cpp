#include <iostream>
#include <ctime>
#include <random>
/*
1. Создана структура dOD
2. Добавлена подстройка под dOD std::istream (std::cin)
3. Добавлена функция преобразования день.месяц.год в unix
4. Добавлена возможность генерации данных в структуру (любое кол-во, с любого номера элемента)
5. Добавлена возможность вывода OD_OutputData
   1. Передано: mOD, N 
   2. Передано: mOD, N, predicate
6. Добавлена возмондость ввода
   1. Передано: mOD - Всегда только элемент 0.
   2. Передано: mOD, N - Полностью ручной ввод от 0 до N элементов
   3. Передано: mOD, N, Nstart - Ручной ввод от N до Nstart
7. Сортировка пузырьком OD_SortData (вообще по любому параметру, представлен в комментарии пример)
8. main()
   1. Получение N и выдача памяти на mOD
   2. (Вариант полного ручного ввода)
   2. Ручной ввод первого
   3. Ручной ввод N-2 кол-ва (внутри проверка на больше нуля)
   4. Ввод оставшихся (2-а) через генерацию
   5. Вывод всех данных
   6. Сортировка
   7. Вывод всех в отсортированном вмде
   8. Вывод по критерию
*/
//+++++OD_InputData - внесение данных (всех) без перегрузки
//+++++OD_OutputData - вывод всех данных без перегрузкм
//+++++Далее сказано использовать перегрузку для OD_InputData
//+++++OD_SortData Сортировка по первому полю структуры 
//+++++OD_OutputData - Вывод данных по критерию

struct dOD{
	struct dateOD{
		int day;
		int month;
		int year;
	};
	
	struct infOD{
		std::string protocol;	
		std::string person;
		std::time_t time_problem;
		int count_problem;
		int rating_problem;
		double earn_money;
	};
   dateOD dateFI;
   infOD infFI;
};

//Перегрузка std::cin
std::istream& operator>>(std::istream& in, dOD& m) {
    std::cout << "Day=";           in >> m.dateFI.day;
    std::cout << "Month=";         in >> m.dateFI.month;
    std::cout << "Year=";          in >> m.dateFI.year;
    std::cout << "Protocol=";      in >> m.infFI.protocol;
    std::cout << "Person (AnalyticLogs, Architect, Pentester, Engineer)=";        in >> m.infFI.person;
    std::cout << "TimeProblem=";   in >> m.infFI.time_problem;
    std::cout << "CountProblem=";  in >> m.infFI.count_problem;
    std::cout << "RatingProblem="; in >> m.infFI.rating_problem;

    std::string* arrayPersons = new std::string[4]{"AnalyticLogs", "Architect", "Pentester", "Engineer"};
	int* arrayTarif = new int[4]{25, 20, 15, 10};
	int number = 0;
    for (int i=0; i<4; i++){
        if (m.infFI.person == arrayPersons[i]){number = i; break;}
	}
	m.infFI.earn_money = arrayTarif[number] * m.infFI.count_problem;
    std::cout << "EarnMoney=" << m.infFI.earn_money;

	delete[] arrayTarif; delete[] arrayPersons;
    return in;
}

std::time_t convert_to_unix(int day, int month, int year) {
    std::tm time_info = {}; //new struct time unix
    
    time_info.tm_mday = day;    
    time_info.tm_mon = month - 1; //start with 0 
    time_info.tm_year = year - 1900; 
    
    time_info.tm_hour = 0;
    time_info.tm_min = 0;
    time_info.tm_sec = 0;
    time_info.tm_isdst = -1; //summer or winter time - auto 
    
    return std::mktime(&time_info);
}

void generation_data(dOD* &mOD, int N, int Nstart){
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<double> distrib(0.4, 4); 
	std::uniform_int_distribution<int> distrib2(0, 4);
	std::uniform_int_distribution<int> distrib3(0, 3);
	double random1; int random2; int random3;
		
	std::string* arrayProtocols = new std::string[4]{"MQTT", "HTTP", "IP", "DNS"};
	std::string* arrayPersons = new std::string[4]{"AnalyticLogs", "Architect", "Pentester", "Engineer"};
	int* arrayTarif = new int[4]{25, 20, 15, 10};
	
	for (int i = Nstart; i<N; i++){
		random1 = distrib(gen);
		random2 = distrib2(gen);
		random3 = distrib3(gen);
		
		dOD& m = mOD[i];
		m.dateFI.day = random1 * 7.5;
		m.dateFI.month = random1 * 3;
		m.dateFI.year = 2024 + random1;
		
		m.infFI.person = arrayPersons[random3];
		m.infFI.time_problem = convert_to_unix(m.dateFI.day,m.dateFI.month,m.dateFI.year);
		m.infFI.count_problem = random2+1;
		m.infFI.rating_problem = (random2+1)*2.5;
		m.infFI.earn_money = arrayTarif[random3] * m.infFI.count_problem;
        random3 = distrib3(gen);
        m.infFI.protocol = arrayProtocols[random3];
	}
	delete[] arrayPersons;
	delete[] arrayProtocols;
	delete[] arrayTarif; 

	std::cout<<"--------------GeneratedData-------------"<<std::endl;
}

//---------------------OD_OutputData-----------------------------
//Это просто вывод
void OD_OutputData(dOD* mOD, int N){
   std::cout<<"--------------Output-------------"<<std::endl;
   for (int i=0; i<N; i++){
      dOD& m = mOD[i];
	  std::cout<<"Element number "<<i<<std::endl;
      std::cout<<"Day="<<m.dateFI.day<<std::endl;
      std::cout<<"Month="<<m.dateFI.month<<std::endl;
   	  std::cout<<"Year="<<m.dateFI.year<<std::endl;
	  std::cout<<"Protocol="<<m.infFI.protocol<<std::endl;
	  std::cout<<"Person="<<m.infFI.person<<std::endl;
      std::cout<<"TimeProblem="<<m.infFI.time_problem<<std::endl;
	  std::cout<<"CountProblem="<<m.infFI.count_problem<<std::endl;
	  std::cout<<"RatingProblem="<<m.infFI.rating_problem<<std::endl;
	  std::cout<<"EarnMoney="<<m.infFI.earn_money<<std::endl;
	  for (int i=0;i<10; i++){std::cout<<"-";}
	  std::cout<<std::endl;
   }
}
//Вывод по критерию, через параметр
template<typename T> 
void OD_OutputData(dOD* mOD, int N, T predicate){
   std::cout<<"--------------OutputWithParametr-------------"<<std::endl;
   for (int i=0; i<N; i++){
      dOD& m = mOD[i];
	  if (!predicate(m)){continue;}
	  std::cout<<"Element number "<<i<<std::endl;
      std::cout<<"Day="<<m.dateFI.day<<std::endl;
      std::cout<<"Month="<<m.dateFI.month<<std::endl;
   	  std::cout<<"Year="<<m.dateFI.year<<std::endl;
	  std::cout<<"Protocol="<<m.infFI.protocol<<std::endl;
	  std::cout<<"Person="<<m.infFI.person<<std::endl;
      std::cout<<"TimeProblem="<<m.infFI.time_problem<<std::endl;
	  std::cout<<"CountProblem="<<m.infFI.count_problem<<std::endl;
	  std::cout<<"RatingProblem="<<m.infFI.rating_problem<<std::endl;
	  std::cout<<"EarnMoney="<<m.infFI.earn_money<<std::endl;
	  for (int i=0;i<10; i++){std::cout<<"-";}
	  std::cout<<std::endl;
   }
}
//----------------------OD_InputData----------------------------
// Перегрузка для одного элемента (без цикла)
void OD_InputData(dOD* mOD) {
	std::cout<<"--------------InputFirstElement-------------"<<std::endl;
	dOD& m = mOD[0];
	std::cout<<"Element number "<<0<<std::endl;

    std::cout << "Day=";           std::cin >> m.dateFI.day;
    std::cout << "Month=";         std::cin >> m.dateFI.month;
    std::cout << "Year=";          std::cin >> m.dateFI.year;
    std::cout << "Protocol=";      std::cin >> m.infFI.protocol;
    std::cout << "Person (AnalyticLogs, Architect, Pentester, Engineer)=";        std::cin >> m.infFI.person;
    std::cout << "TimeProblem=";   std::cin >> m.infFI.time_problem;
    std::cout << "CountProblem=";  std::cin >> m.infFI.count_problem;
    std::cout << "RatingProblem="; std::cin >> m.infFI.rating_problem;
    
	std::string* arrayPersons = new std::string[4]{"AnalyticLogs", "Architect", "Pentester", "Engineer"};
	int* arrayTarif = new int[4]{25, 20, 15, 10};
	int number = 0;
    for (int i=0; i<4; i++){
        if (m.infFI.person == arrayPersons[i]){number = i; break;}
	}
	m.infFI.earn_money = arrayTarif[number] * m.infFI.count_problem;
    std::cout << "EarnMoney=" << m.infFI.earn_money;

	delete[] arrayTarif; delete[] arrayPersons;
	std::cout<<std::endl;
}

void OD_InputData(dOD* mOD, int N){
	std::cout<<"--------------Input-------------"<<std::endl;
   for (int i=0; i<N; i++){
	  //Возможна замена всего этого блока на прописанрый std::cin>>mOD[i]
	  dOD& m = mOD[i];
      std::cout<<"Element number "<<i<<std::endl;
      
      std::cout<<"Day=";           std::cin>>m.dateFI.day;
      std::cout<<"Month=";         std::cin>>m.dateFI.month;
      std::cout<<"Year=";          std::cin>>m.dateFI.year;
      std::cout<<"Protocol=";      std::cin>>m.infFI.protocol;
      std::cout<<"Person (AnalyticLogs, Architect, Pentester, Engineer)=";        std::cin>>m.infFI.person;
      std::cout<<"TimeProblem=";   std::cin>>m.infFI.time_problem;
      std::cout<<"CountProblem=";  std::cin>>m.infFI.count_problem;
      std::cout<<"RatingProblem="; std::cin>>m.infFI.rating_problem;

      std::string* arrayPersons = new std::string[4]{"AnalyticLogs", "Architect", "Pentester", "Engineer"};
	  int* arrayTarif = new int[4]{25, 20, 15, 10};
	  int number = 0;
      for (int i=0; i<4; i++){
          if (m.infFI.person == arrayPersons[i]){number = i; break;}
      }
	  m.infFI.earn_money = arrayTarif[number] * m.infFI.count_problem;
      std::cout << "EarnMoney=" << m.infFI.earn_money;

	  delete[] arrayTarif; delete[] arrayPersons;
      
      for (int j=0; j<10; j++){ std::cout<<"+"; }
      std::cout<<std::endl;
   }
}

void OD_InputData(dOD* mOD, int N, int Nstart) {
	if (N == 0){return;}
	std::cout<<"--------------Input-------------"<<std::endl;
    for (int i = Nstart; i < N; i++) {
        std::cout << "Element number " << i << std::endl;
        std::cin >> mOD[i];
        
		std::cout<<std::endl;
        for (int j = 0; j < 10; j++) { std::cout << "-"; }
        std::cout << std::endl;
    }
}
//--------------------------------------------------------------

void OD_SortData(dOD* &mOD, int N) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N-i-1; j++) {
            int current_idx = j;
            int next_idx = j + 1;
            
          if (mOD[current_idx].dateFI.day > mOD[next_idx].dateFI.day) {
          //if (mOD[current_idx].infFI.time_problem > mOD[next_idx].infFI.time_problem) {
                dOD buffer = mOD[current_idx];
                mOD[current_idx] = mOD[next_idx];
                mOD[next_idx] = buffer;
            }
        }
    } 
   std::cout<<std::endl<<"-------------Sorted!---------------"<<std::endl<<std::endl;
}

int main(){
	//Get array information, N-element
	std::cout<<"How many elements in mOD array?";
	int N; std::cin>>N; std::cout<<std::endl;
	
	dOD* mOD = new dOD[N];
    int Nstart = 0; 
    
	//OD_InputData(mOD, N); Nstart = N; //Полностью ручной ввод
	OD_InputData(mOD); Nstart ++;
	if (Nstart != N){
		OD_InputData(mOD, N-2, Nstart); Nstart =+ N-2;//-2 гарантирует, что для функции генерации останутся слоты
		generation_data(mOD, N, Nstart); //вообще его нужно вынести из цикла. А вообще убрать из кода
	}

    OD_OutputData(mOD, N);
    OD_SortData(mOD, N);
    OD_OutputData(mOD, N);
	OD_OutputData(mOD, N, [](dOD& m){return m.dateFI.day > 14;});
}
