#include <iostream>
#include <fstream>  
#include <chrono>
#include <random>
#include <algorithm>

using namespace std;

long long int linear_search(long long int array[], long long int array_length, long long int number_to_find) { // Поиск прямым перебором
  for (int idx = 0; idx != array_length; ++idx) {
    if (array[idx] == number_to_find) {
      return idx;
    }
  }
  return -1;
}

long long int binary_search(long long int array[], long long int array_length, long long int number_to_find) { // Бинарный поиск
  long long int lborder = 0, rborder = array_length - 1;
  while (lborder <= rborder) {
    int middle =lborder + (rborder - lborder) / 2;
    if (array[middle] == number_to_find) {
      return middle;
    }
    if (array[middle] < number_to_find) {
      lborder = middle + 1;
    }
    if (array[middle] > number_to_find) {
      rborder = middle - 1;
    }
  }
  return -1;
}

void quadratic_sum(long long int array[], long long int array_length, long long int sum_to_find) { // Прямой перебор для находения элементов с заданной суммой
  for (int i = 0; i < array_length; ++i) {
    for (int j = 0; j < array_length; ++j) {
      if (i != j) {
        if (array[i] +array[j] == sum_to_find) {
          return;
        }
      }
    }
  }
  return;
}

void linear_sum(long long int array[], long long int array_length, long long int sum_to_find) { // Быстрый алгоритм для находения элементов с заданной суммой
  long long int lborder = 0, rborder = array_length - 1;
  while (lborder <= rborder) {
    if (array[lborder] + array[rborder] == sum_to_find) {
      return;
    }
    if (array[lborder] + array[rborder] < sum_to_find) {
      ++lborder;
    }
    if (array[lborder] + array[rborder] > sum_to_find) {
      --rborder;
    }
  }
  return;
}

void strategy_A(long long int array[], long long int index_found) { // Стратегия A (перемещение на первую позицию)
  if (index_found > 0) {
    std::swap(array[0], array[index_found]);
  }
}

void strategy_B(long long int array[], long long int index_found) { // Стратегия B (перемещение на предпоследнюю позицию)
  if (index_found > 0) {
    std::swap(array[index_found - 1], array[index_found]);
  }
}

void strategy_C(long long int array[], long long int counters_array[], long long int index_found){ // Стратегия C (Увеличивает счетчик для найденного элемента и, если необходимо, меняет порядок элементов и их счетчиков)
  if (index_found != -1) {
    counters_array[index_found] += 1;
    if (index_found != 0){
      if (counters_array[index_found] > counters_array[index_found - 1]) {
        std::swap(counters_array[index_found], counters_array[index_found - 1]);
        std::swap(array[index_found], array[index_found - 1]);
      }
    }
  }
}

int main() {

  // Инициализирум переменные для записи в файл
  std::ofstream output_search;
  std::ofstream output_sum_of_two;
  std::ofstream output_frequently_used_element;

  unsigned seed = 1001;
  std::default_random_engine rng(seed);
  
  { // Локализуем переменную array
    output_search.open("search.csv"); // Открываем файл для первого задания 
    output_search << "number_of_elements," << "average_bin," << "average_lin," << "worst_possible_bin," << "worst_possible_lin" << '\n'; // Записываем в файл название столбцов

    long long int *array = new long long int[1000000]; // Инициализирум массив
    for (long long int idx = 0; idx < 90; ++idx) {
      array[idx] = idx + 1; // Заполняем массив натуральными числами
    }

    for (long long int number_of_elements = 100; number_of_elements <= 1000000; number_of_elements += 10) { // Пробегаемся по кол-ву элементов в массиве
      
      for (long long int idx = number_of_elements - 10; idx < number_of_elements; ++idx) {
        array[idx] = idx + 1; //Пополняем массив
      }

      std:uniform_int_distribution<long long int> dstr(1, number_of_elements);

      auto begin_average_bin = std::chrono::steady_clock::now(); // Начинаем отсчет времени
      for (int counter = 0; counter < 100; ++counter) { // Запускаем счётчик
        int number_to_find = dstr(rng); // Берём случайный элемент массива
        binary_search(array, number_of_elements, number_to_find); // Ищем его бин. поиском
      }
      auto end_average_bin = std::chrono::steady_clock::now(); // Останавливаем отсчет времени 
      auto time_span_average_bin = std::chrono::duration_cast < std::chrono::microseconds > (end_average_bin - begin_average_bin);
      int average_bin = time_span_average_bin.count(); // Записываем в переменную прошедшее время

      // Аналогично для поска перебором
      auto begin_average_lin = std::chrono::steady_clock::now();
      for (int counter = 0; counter < 100; ++counter) {
        int number_to_find = dstr(rng);
        linear_search(array, number_of_elements, number_to_find);
      }
      auto end_average_lin = std::chrono::steady_clock::now();
      auto time_span_average_lin = std::chrono::duration_cast < std::chrono::microseconds > (end_average_lin - begin_average_lin);
      int average_lin = time_span_average_lin.count();

      auto begin_worst_possible_bin = std::chrono::steady_clock::now();
      for (int counter = 0; counter < 100; ++counter) {
        int number_to_find = number_of_elements + 1; // Берём элемент не лежащий в массиве
        binary_search(array, number_of_elements, number_to_find);
      }
      auto end_worst_possible_bin = std::chrono::steady_clock::now();
      auto time_span_worst_possible_bin = std::chrono::duration_cast < std::chrono::microseconds > (end_worst_possible_bin - begin_worst_possible_bin);
      int worst_possible_bin = time_span_worst_possible_bin.count();

      auto begin_worst_possible_lin = std::chrono::steady_clock::now();
      for (int counter = 0; counter < 100; ++counter) {
        int number_to_find = number_of_elements + 1;
        linear_search(array, number_of_elements, number_to_find);
      }
      auto end_worst_possible_lin = std::chrono::steady_clock::now();
      auto time_span_worst_possible_lin = std::chrono::duration_cast < std::chrono::microseconds > (end_worst_possible_lin - begin_worst_possible_lin);
      int worst_possible_lin = time_span_worst_possible_lin.count();    

      output_search << number_of_elements << ',' << average_bin << ',' << average_lin << ',' << worst_possible_bin << ',' << worst_possible_lin << '\n'; // Записываем в строку файла кол-во элементов в массиве и полученное время
    }
    
    delete[] array; // Очищаем память
    output_search.close(); // Закрываем файл для первого задания
  }

  /*

  {  
    output_sum_of_two.open("sum_of_two.csv"); // Открываем файл для второго задания
    output_sum_of_two << "number_of_elements," << "quad_sum," << "lin_sum" << "\n"; // Записываем в него названия столбцов

    long long int *array = new long long int[10000];
    for (long long int idx = 0; idx < 90; ++idx) {
      array[idx] = idx + 1; // Заполняем массив натуральными числами
    }

    for (long long int number_of_elements = 100; number_of_elements <= 10000; number_of_elements += 10) { // Пробегаемся по кол-ву элементов в массиве
      
      for (long long int idx = number_of_elements - 10; idx < number_of_elements; ++idx) {
        array[idx]= idx + 1; // Пополняем массив
      }

      std::uniform_int_distribution<long long int> dstr(1, number_of_elements * 2 -1);
      
      auto begin_quad_sum = std::chrono::steady_clock::now(); // Запускаем отсчёт времени
      for (int counter = 0; counter < 100; ++counter) { // Запускаем счетчик
        int sum_to_find = dstr(rng); // Берём случайную возможную сумму 
        quadratic_sum(array, number_of_elements, sum_to_find); // Ищем элементы с заданной суммой быстрым алгоритмом
      }
      auto end_quad_sum = std::chrono::steady_clock::now(); // Останавливаем отсчёт времени
      auto time_span_quad_sum = std::chrono::duration_cast < std::chrono::microseconds > (end_quad_sum - begin_quad_sum);
      int quad_sum = time_span_quad_sum.count(); // Записываем в переменную прошедшее время
      
      // Для прямого перебора аналогично
      auto begin_lin_sum = std::chrono::steady_clock::now();
      for (int counter = 0; counter < 100; ++counter) {
        int sum_to_find = dstr(rng);
        linear_sum(array, number_of_elements, sum_to_find);
      }
      auto end_lin_sum = std::chrono::steady_clock::now();
      auto time_span_lin_sum = std::chrono::duration_cast < std::chrono::microseconds > (end_lin_sum - begin_lin_sum);
      int lin_sum = time_span_lin_sum.count();
      
      output_sum_of_two << number_of_elements << ',' << quad_sum << ',' << lin_sum << "\n"; // Записываем в строку файла кол-во элементов в массиве и полученное время
    }

    delete[] array; // Очищаем память
    output_sum_of_two.close(); // Закрываем файл для второго задания
  }

  */

  {
    output_frequently_used_element.open("frequently_used_element.csv"); // Открываем файл для третьего задания 
    output_frequently_used_element << "number_of_elements," << "A_uniform," << "B_uniform," << "C_uniform," << "A_binomial," << "B_binomial," << "C_binomial" << '\n'; // Записываем в него название столбцов

    for (long long int number_of_elements = 100; number_of_elements <= 1000000; number_of_elements += 10) { // Пробегаемся по кол-ву элементов в массиве
      long long int *array = new long long int[number_of_elements]; // Инициализируем массив с заданным числом элементов
      for (long long int idx = 0; idx < number_of_elements; ++idx) {
        array[idx] = idx + 1; // Заполняем его натуральными числами
      }

      std::uniform_int_distribution<long long int> dstr(1, number_of_elements); // Задаем равномерное распределение в диапазоне от 1 до кол-ва элементов
      
      auto begin_A_uniform = std::chrono::steady_clock::now(); // Запускаем отсчёт времени
      for (int counter = 0; counter < 1000; ++counter) { // Запускаем счетчик
        int number_to_find = dstr(rng); // Выбираем одно из значений распределенных равномерно
        strategy_A(array, linear_search(array, number_of_elements, number_to_find)); // Применяем стратегию A
      }
      auto end_A_uniform = std::chrono::steady_clock::now(); // Останавливаем отсчёт времени
      auto time_span_A_uniform = std::chrono::duration_cast < std::chrono::microseconds > (end_A_uniform - begin_A_uniform);
      int A_uniform = time_span_A_uniform.count(); // Записыываем в переменную прошедшее время

      delete[] array; // Очищаем память

      array = new long long int[number_of_elements]; 

      for (long long int idx = 0; idx < number_of_elements; ++idx) {
        array[idx] = idx + 1; // Перезаполняем массив натуральными числами
      }
      
      // Далее аналогично
      auto begin_B_uniform = std::chrono::steady_clock::now();
      for (int counter = 0; counter < 1000; ++counter) {
        int number_to_find = dstr(rng);
        strategy_B(array, linear_search(array, number_of_elements, number_to_find));
      }
      auto end_B_uniform = std::chrono::steady_clock::now();
      auto time_span_B_uniform = std::chrono::duration_cast < std::chrono::microseconds > (end_B_uniform - begin_B_uniform);
      int B_uniform = time_span_B_uniform.count();

      delete[] array;

      array = new long long int[number_of_elements];
      long long int *counters_array = new long long int[number_of_elements]; // Инициализируем массив счётчиков

      for (long long int idx = 0; idx < number_of_elements; ++idx) {
        array[idx] = idx + 1;
        counters_array[idx] = 0;
      }
      
      auto begin_C_uniform = std::chrono::steady_clock::now();
      for (int counter = 0; counter < 1000; ++counter) {
        int number_to_find = dstr(rng);
        strategy_C(array, counters_array, linear_search(array, number_of_elements, number_to_find));
      }
      auto end_C_uniform = std::chrono::steady_clock::now();
      auto time_span_C_uniform = std::chrono::duration_cast < std::chrono::microseconds > (end_C_uniform - begin_C_uniform);
      int C_uniform = time_span_C_uniform.count();

      delete[] array;
      delete[] counters_array;

      array = new long long int[number_of_elements];
      for (long long int idx = 0; idx < number_of_elements; ++idx) {
        array[idx] = idx + 1;
      }

      std::binomial_distribution<long long int> bin_dstr(dstr(rng), dstr(rng)); //Задаем биномиальное распределение со случайнми параметрами
      
      //Далее аналогично
      auto begin_A_binomial = std::chrono::steady_clock::now();
      for (int counter = 0; counter < 1000; ++counter) {
        int number_to_find = bin_dstr(rng); // Выбираем одно из значений распределенных биномиально
        strategy_A(array, linear_search(array, number_of_elements, number_to_find));
      }
      auto end_A_binomial = std::chrono::steady_clock::now();
      auto time_span_A_binomial = std::chrono::duration_cast < std::chrono::microseconds > (end_A_binomial - begin_A_binomial);
      int A_binomial = time_span_A_binomial.count();

      delete[] array;

      array = new long long int[number_of_elements];

      for (long long int idx = 0; idx < number_of_elements; ++idx) {
        array[idx] = idx + 1;
      }
      
      auto begin_B_binomial = std::chrono::steady_clock::now();
      for (int counter = 0; counter < 1000; ++counter) {
        int number_to_find = bin_dstr(rng);
        strategy_B(array, linear_search(array, number_of_elements, number_to_find));
      }
      auto end_B_binomial = std::chrono::steady_clock::now();
      auto time_span_B_binomial = std::chrono::duration_cast < std::chrono::microseconds > (end_B_binomial - begin_B_binomial);
      int B_binomial = time_span_B_binomial.count();

      delete[] array;

      array = new long long int[number_of_elements];
      counters_array = new long long int[number_of_elements];

      for (long long int idx = 0; idx < number_of_elements; ++idx) {
        array[idx] = idx + 1;
        counters_array[idx] = 0;
      }
      
      auto begin_C_binomial = std::chrono::steady_clock::now();
      for (int counter = 0; counter < 1000; ++counter) {
        int number_to_find = bin_dstr(rng);
        strategy_C(array, counters_array, linear_search(array, number_of_elements, number_to_find));
      }
      auto end_C_binomial = std::chrono::steady_clock::now();
      auto time_span_C_binomial = std::chrono::duration_cast < std::chrono::microseconds > (end_C_binomial - begin_C_binomial);
      int C_binomial = time_span_C_binomial.count();

      delete[] array;
      delete[] counters_array;

      output_frequently_used_element << number_of_elements << ',' << A_uniform << ',' << B_uniform << ',' << C_uniform << ',' << A_binomial << ',' << B_binomial << ',' << C_binomial << '\n'; // Записываем в строку файла кол-во элементов в массиве и полученное время
    }

    output_frequently_used_element.close(); // Закрываем файл для третьего задания
  }

  return 0; 
}
