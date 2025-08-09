#ifndef IMAGE_H
#define IMAGE_H

#include <vector>
#include <iostream>
#include <iomanip>
#include <type_traits>


template<typename T>
class Image {
public:
    using value_type = T;

private:
    std::vector<std::vector<T>> data;
    size_t width;
    size_t height;

public:
    Image();
    Image(size_t height, size_t width, const T& defaultValue = T());
    Image(const Image<T>& other);

    template<typename U>
    Image(const Image<U>& other);

    // Основні методи
    void input();
    void print() const;

    void setPixel(size_t row, size_t col, const T& value);
    T getPixel(size_t row, size_t col) const;
    T& pixel(int row, int col);
    const T& pixel(int row, int col) const;

    size_t getHeight() const;
    size_t getWidth() const;

    // Арифметика між зображеннями
    template<typename U>
    Image<typename std::common_type<T, U>::type> operator+(const Image<U>& other) const;

    template<typename U>
    Image<typename std::common_type<T, U>::type> operator-(const Image<U>& other) const;

    template<typename U>
    Image<typename std::common_type<T, U>::type> operator*(const Image<U>& other) const;

    template<typename U>
    Image<typename std::common_type<T, U>::type> operator/(const Image<U>& other) const;

    // Арифметика зі скалярами
    template<typename Scalar>
    Image<typename std::common_type<T, Scalar>::type> operator+(Scalar value) const;

    template<typename Scalar>
    Image<typename std::common_type<T, Scalar>::type> operator-(Scalar value) const;

    template<typename Scalar>
    Image<typename std::common_type<T, Scalar>::type> operator*(Scalar value) const;

    template<typename Scalar>
    Image<typename std::common_type<T, Scalar>::type> operator/(Scalar value) const;

    // Об'єднання
    template<typename U>
    Image<typename std::common_type<T, U>::type> concatHorizontal(const Image<U>& other) const;

    template<typename U>
    Image<typename std::common_type<T, U>::type> concatVertical(const Image<U>& other) const;

    template<int RowStart, int RowEnd, int ColStart, int ColEnd>
    Image<T> subimage() const;

    Image<T> subimageDynamic(int rowStart, int rowEnd, int colStart, int colEnd) const;

    // Додаткові можливості
    template<typename U>
    Image<U> convert() const;

    template<int ScaleH, int ScaleW>
    Image<T> upscale() const;
};

// Утилітарні шаблонні функції

// Об'єднання довільної кількості зображень по горизонталі

template<typename First, typename... Rest>
auto unite_horizontal(const First& first, const Rest&... rest);

// Побудова зображення за набором значень

template<int H, int W, typename T, typename... Args>
Image<T> make_image(Args... args);

#include "image.hpp"

#endif