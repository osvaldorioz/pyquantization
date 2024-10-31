#include <pybind11/pybind11.h>
#include <pybind11/stl.h>
#include <pybind11/complex.h>
#include <pybind11/functional.h>
#include <pybind11/chrono.h>
#include <vector>
#include <cmath>

//g++ -O2 -Wall -shared -std=c++20 -fPIC `python3.12 -m pybind11 --includes` quantization.cpp -o quantization`python3.12-config --extension-suffix`

namespace py = pybind11;

// Función para cuantizar un vector de datos
std::vector<double> quantize(const std::vector<double>& data, int num_levels) {
    if (num_levels <= 1) {
        throw std::invalid_argument("El número de niveles debe ser mayor que 1.");
    }

    // Encontrar el valor mínimo y máximo en los datos
    double min_val = *std::min_element(data.begin(), data.end());
    double max_val = *std::max_element(data.begin(), data.end());

    // Paso de cuantización
    double step = (max_val - min_val) / (num_levels - 1);

    std::vector<double> quantized_data;
    quantized_data.reserve(data.size());

    // Cuantización de cada valor en el vector
    for (double value : data) {
        // Cuantización a los niveles más cercanos
        double quantized_value = std::round((value - min_val) / step) * step + min_val;
        quantized_data.push_back(quantized_value);
    }

    return quantized_data;
}

// Exponer la función al módulo de Python usando pybind11
PYBIND11_MODULE(quantization, m) {
    m.def("quantize", &quantize, "Función para cuantizar un vector de datos en un número dado de niveles");
}
