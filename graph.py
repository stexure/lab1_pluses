import matplotlib.pyplot as plt
import numpy as np
import pandas as pd

# Считываем файлы с результатми в виде DataFrame'ов
search = pd.read_csv(r"asimptotic\search.csv") 
sum_of_two = pd.read_csv(r"asimptotic\sum_of_two.csv")
frequently_used_element = pd.read_csv(r"asimptotic\frequently_used_element.csv")

# Создаем фигуры
fig_average_bin = plt.figure()
fig_average_lin = plt.figure()
fig_worst_possible_bin = plt.figure()
fig_worst_possible_lin = plt.figure()
fig_quad_sum = plt.figure()
fig_lin_sum = plt.figure()
fig_A_uniform = plt.figure()
fig_B_uniform = plt.figure()
fig_C_uniform = plt.figure()
fig_A_binomial = plt.figure()
fig_B_binomial = plt.figure()
fig_C_binomial = plt.figure()

# Создаем в них координатные плоскости
plt_average_bin = fig_average_bin.add_subplot()
plt_average_lin = fig_average_lin.add_subplot()
plt_worst_possible_bin = fig_worst_possible_bin.add_subplot()
plt_worst_possible_lin = fig_worst_possible_lin.add_subplot()
plt_quad_sum = fig_quad_sum.add_subplot()
plt_lin_sum = fig_lin_sum.add_subplot()
plt_A_uniform = fig_A_uniform.add_subplot()
plt_B_uniform = fig_B_uniform.add_subplot()
plt_C_uniform = fig_C_uniform.add_subplot()
plt_A_binomial = fig_A_binomial.add_subplot()
plt_B_binomial = fig_B_binomial.add_subplot()
plt_C_binomial = fig_C_binomial.add_subplot()

point_size = 3 # Задаем размер точек

# Наносим точки на график, если надо модифицируем оси
plt_average_bin.scatter(np.log(search["number_of_elements"]), search["average_bin"], point_size, 'k')
plt_average_lin.scatter(search["number_of_elements"], search["average_lin"], point_size, 'k')
plt_worst_possible_bin.scatter(np.log(search["number_of_elements"]), search["worst_possible_bin"], point_size, 'k')
plt_worst_possible_lin.scatter(search["number_of_elements"], search["worst_possible_lin"], point_size, 'k')
plt_quad_sum.scatter(sum_of_two["number_of_elements"] ** 2, sum_of_two["quad_sum"], point_size, 'k')
plt_lin_sum.scatter(sum_of_two["number_of_elements"], sum_of_two["lin_sum"], point_size, 'k')
plt_A_uniform.scatter(frequently_used_element["number_of_elements"], frequently_used_element["A_uniform"], point_size, 'k')
plt_B_uniform.scatter(frequently_used_element["number_of_elements"], frequently_used_element["B_uniform"], point_size, 'k')
plt_C_uniform.scatter(frequently_used_element["number_of_elements"], frequently_used_element["C_uniform"], point_size, 'k')
plt_A_binomial.scatter(frequently_used_element["number_of_elements"], frequently_used_element["A_binomial"], point_size, 'k')
plt_B_binomial.scatter(frequently_used_element["number_of_elements"], frequently_used_element["B_binomial"], point_size, 'k')
plt_C_binomial.scatter(frequently_used_element["number_of_elements"], frequently_used_element["C_binomial"], point_size, 'k')

# Именуем оси ординат
plt_average_bin.set_ylabel("Time passed, microseconds")
plt_average_lin.set_ylabel("Time passed, microseconds")
plt_worst_possible_bin.set_ylabel("Time passed, microseconds")
plt_worst_possible_lin.set_ylabel("Time passed, microseconds")
plt_quad_sum.set_ylabel("Time passed, microseconds")
plt_lin_sum.set_ylabel("Time passed, microseconds")
plt_A_uniform.set_ylabel("Time passed, microseconds")
plt_B_uniform.set_ylabel("Time passed, microseconds")
plt_C_uniform.set_ylabel("Time passed, microseconds")
plt_A_binomial.set_ylabel("Time passed, microseconds")
plt_B_binomial.set_ylabel("Time passed, microseconds")
plt_C_binomial.set_ylabel("Time passed, microseconds")

# Именуем оси абсцисс
plt_average_bin.set_xlabel("ln(Number of elements)")
plt_average_lin.set_xlabel("Number of elements")
plt_worst_possible_bin.set_xlabel("ln(Number of elements)")
plt_worst_possible_lin.set_xlabel("Number of elements")
plt_quad_sum.set_xlabel("(Number of elements) ^ 2")
plt_lin_sum.set_xlabel("Number of elements")
plt_A_uniform.set_xlabel("Number of elements")
plt_B_uniform.set_xlabel("Number of elements")
plt_C_uniform.set_xlabel("Number of elements")
plt_A_binomial.set_xlabel("Number of elements")
plt_B_binomial.set_xlabel("Number of elements")
plt_C_binomial.set_xlabel("Number of elements")

# Сохраняем фигуры
fig_average_bin.savefig(r"asimptotic\average_bin.png")
fig_average_lin.savefig(r"asimptotic\average_lin.png")
fig_worst_possible_bin.savefig(r"asimptotic\worst_possible_bin.png")
fig_worst_possible_lin.savefig(r"asimptotic\worst_possible_lin.png")
fig_quad_sum.savefig(r"asimptotic\quad_sum.png")
fig_lin_sum.savefig(r"asimptotic\lin_sum.png")
fig_A_uniform.savefig(r"asimptotic\A_uniform.png")
fig_B_uniform.savefig(r"asimptotic\B_uniform.png")
fig_C_uniform.savefig(r"asimptotic\C_uniform.png")
fig_A_binomial.savefig(r"asimptotic\A_binomial.png")
fig_B_binomial.savefig(r"asimptotic\B_binomial.png")
fig_C_binomial.savefig(r"asimptotic\C_binomial.png")