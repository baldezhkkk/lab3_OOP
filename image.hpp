#pragma once

#include "image.h"
#include <stdexcept>
#include <initializer_list>

// ==== Базові конструктори ====

template<typename T>
Image<T>::Image() : width(0), height(0) {}

template<typename T>
Image<T>::Image(size_t h, size_t w, const T& def) : width(w), height(h), data(h, std::vector<T>(w, def)) {}

template<typename T>
Image<T>::Image(const Image<T>& other) : width(other.width), height(other.height), data(other.data) {}

template<typename T>
template<typename U>
Image<T>::Image(const Image<U>& other) : width(other.getWidth()), height(other.getHeight()), data(height, std::vector<T>(width)) {
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            data[i][j] = static_cast<T>(other.getPixel(i, j));
}

// ==== Методи виводу ====

template<typename T>
void Image<T>::print() const {
    for (const auto& row : data) {
        for (const auto& val : row) std::cout << std::setw(4) << val;
        std::cout << '\n';
    }
}

template<typename T>
void Image<T>::input() {
    std::cout << "Width: "; std::cin >> width;
    std::cout << "Height: "; std::cin >> height;
    data.resize(height, std::vector<T>(width));
    std::cout << "Enter " << width * height << " values:\n";
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            std::cin >> data[i][j];
}

// ==== Доступ ====

template<typename T>
T& Image<T>::pixel(int r, int c) {
    if (r < 0) r += height;
    if (c < 0) c += width;
    return data.at(r).at(c);
}

template<typename T>
const T& Image<T>::pixel(int r, int c) const {
    if (r < 0) r += height;
    if (c < 0) c += width;
    return data.at(r).at(c);
}

template<typename T>
void Image<T>::setPixel(size_t r, size_t c, const T& val) {
    data[r][c] = val;
}

template<typename T>
T Image<T>::getPixel(size_t r, size_t c) const {
    return data[r][c];
}

template<typename T>
size_t Image<T>::getHeight() const { return height; }

template<typename T>
size_t Image<T>::getWidth() const { return width; }

// ==== Доповнення: convert ====

template<typename T>
template<typename U>
Image<U> Image<T>::convert() const {
    Image<U> result(height, width);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            result.setPixel(i, j, static_cast<U>(data[i][j]));
    return result;
}

// ==== Доповнення: upscale<ScaleH, ScaleW> ====

template<typename T>
template<int ScaleH, int ScaleW>
Image<T> Image<T>::upscale() const {
    Image<T> result(height * ScaleH, width * ScaleW);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            for (int dy = 0; dy < ScaleH; ++dy)
                for (int dx = 0; dx < ScaleW; ++dx)
                    result.setPixel(i * ScaleH + dy, j * ScaleW + dx, data[i][j]);
    return result;
}

// ==== Об'єднання по горизонталі ====

template<typename T>
template<typename U>
Image<typename std::common_type<T, U>::type> Image<T>::concatHorizontal(const Image<U>& other) const {
    using CT = typename std::common_type<T, U>::type;
    if (height != other.getHeight())
        throw std::invalid_argument("Images must have the same height for horizontal concatenation");

    Image<CT> result(height, width + other.getWidth());
    for (size_t i = 0; i < height; ++i) {
        // Copy this image's row
        for (size_t j = 0; j < width; ++j)
            result.setPixel(i, j, static_cast<CT>(data[i][j]));
        // Copy other's row
        for (size_t j = 0; j < other.getWidth(); ++j)
            result.setPixel(i, width + j, static_cast<CT>(other.getPixel(i, j)));
    }
    return result;
}

// ==== Об'єднання по вертикалі ====

template<typename T>
template<typename U>
Image<typename std::common_type<T, U>::type> Image<T>::concatVertical(const Image<U>& other) const {
    using CT = typename std::common_type<T, U>::type;
    if (width != other.getWidth())
        throw std::invalid_argument("Images must have the same width for vertical concatenation");
    Image<CT> result(height + other.getHeight(), width);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            result.setPixel(i, j, static_cast<CT>(data[i][j]));
    for (size_t i = 0; i < other.getHeight(); ++i)
        for (size_t j = 0; j < width; ++j)
            result.setPixel(height + i, j, static_cast<CT>(other.getPixel(i, j)));
    return result;
}

// ==== Арифметика між зображеннями ====

template<typename T>
template<typename U>
Image<typename std::common_type<T, U>::type> Image<T>::operator+(const Image<U>& other) const {
    using CT = typename std::common_type<T, U>::type;
    if (height != other.getHeight() || width != other.getWidth())
        throw std::invalid_argument("Images must have the same dimensions for addition");
    Image<CT> result(height, width);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            result.setPixel(i, j, static_cast<CT>(data[i][j]) + static_cast<CT>(other.getPixel(i, j)));
    return result;
}

template<typename T>
template<typename U>
Image<typename std::common_type<T, U>::type> Image<T>::operator-(const Image<U>& other) const {
    using CT = typename std::common_type<T, U>::type;
    if (height != other.getHeight() || width != other.getWidth())
        throw std::invalid_argument("Images must have the same dimensions for subtraction");
    Image<CT> result(height, width);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            result.setPixel(i, j, static_cast<CT>(data[i][j]) - static_cast<CT>(other.getPixel(i, j)));
    return result;
}

template<typename T>
template<typename U>
Image<typename std::common_type<T, U>::type> Image<T>::operator*(const Image<U>& other) const {
    using CT = typename std::common_type<T, U>::type;
    if (height != other.getHeight() || width != other.getWidth())
        throw std::invalid_argument("Images must have the same dimensions for multiplication");
    Image<CT> result(height, width);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            result.setPixel(i, j, static_cast<CT>(data[i][j]) * static_cast<CT>(other.getPixel(i, j)));
    return result;
}

template<typename T>
template<typename U>
Image<typename std::common_type<T, U>::type> Image<T>::operator/(const Image<U>& other) const {
    using CT = typename std::common_type<T, U>::type;
    if (height != other.getHeight() || width != other.getWidth())
        throw std::invalid_argument("Images must have the same dimensions for division");
    Image<CT> result(height, width);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j) {
            CT otherPixel = static_cast<CT>(other.getPixel(i, j));
            if (otherPixel == 0) throw std::invalid_argument("Division by zero in image operation");
            result.setPixel(i, j, static_cast<CT>(data[i][j]) / otherPixel);
        }
    return result;
}

// ==== Арифметика зі скалярами ====

template<typename T>
template<typename Scalar>
Image<typename std::common_type<T, Scalar>::type> Image<T>::operator+(Scalar value) const {
    using CT = typename std::common_type<T, Scalar>::type;
    Image<CT> result(height, width);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            result.setPixel(i, j, static_cast<CT>(data[i][j]) + static_cast<CT>(value));
    return result;
}

template<typename T>
template<typename Scalar>
Image<typename std::common_type<T, Scalar>::type> Image<T>::operator-(Scalar value) const {
    using CT = typename std::common_type<T, Scalar>::type;
    Image<CT> result(height, width);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            result.setPixel(i, j, static_cast<CT>(data[i][j]) - static_cast<CT>(value));
    return result;
}

template<typename T>
template<typename Scalar>
Image<typename std::common_type<T, Scalar>::type> Image<T>::operator*(Scalar value) const {
    using CT = typename std::common_type<T, Scalar>::type;
    Image<CT> result(height, width);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            result.setPixel(i, j, static_cast<CT>(data[i][j]) * static_cast<CT>(value));
    return result;
}

template<typename T>
template<typename Scalar>
Image<typename std::common_type<T, Scalar>::type> Image<T>::operator/(Scalar value) const {
    using CT = typename std::common_type<T, Scalar>::type;
    if (value == 0) throw std::invalid_argument("Division by zero with a scalar");
    Image<CT> result(height, width);
    for (size_t i = 0; i < height; ++i)
        for (size_t j = 0; j < width; ++j)
            result.setPixel(i, j, static_cast<CT>(data[i][j]) / static_cast<CT>(value));
    return result;
}


// ==== Subimage ====

template<typename T>
Image<T> Image<T>::subimageDynamic(int r1, int r2, int c1, int c2) const {
    if (r1 < 0 || r2 >= height || c1 < 0 || c2 >= width || r1 > r2 || c1 > c2)
        throw std::out_of_range("Invalid cropping coordinates");
    
    Image<T> result(r2 - r1 + 1, c2 - c1 + 1);
    for (int i = r1; i <= r2; ++i)
        for (int j = c1; j <= c2; ++j)
            result.setPixel(i - r1, j - c1, data[i][j]);
    return result;
}

// ==== Утиліта: об'єднання довільної кількості зображень ====

template<typename First, typename... Rest>
auto unite_horizontal(const First& first, const Rest&... rest) {
    if constexpr (sizeof...(rest) == 0) {
        return first;
    } else {
        return first.concatHorizontal(unite_horizontal(rest...));
    }
}

// ==== make_image<H, W, T, ...> ====

template<int H, int W, typename T, typename... Args>
Image<T> make_image(Args... args) {
    static_assert(sizeof...(Args) == H * W, "Wrong number of arguments");
    Image<T> result(H, W);
    T values[] = { static_cast<T>(args)... };
    size_t index = 0;
    for (int i = 0; i < H; ++i)
        for (int j = 0; j < W; ++j)
            result.setPixel(i, j, values[index++]);
    return result;
}