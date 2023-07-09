//
// Created by Daryn Smith on 7/8/23.
//

#ifndef RAY_TRACING_VEC3_H
#define RAY_TRACING_VEC3_H

#include <cmath>
#include <iostream>

using std::sqrt;

class vec3 {
  
  private:
  double values[3];
  
  public:
  // constructors
  vec3() : values{0, 0, 0} {}
  
  vec3(double e0, double e1, double e2) : values{e0, e1, e2} {}
  
  // getters
  [[nodiscard]] double x() const { return values[0]; }
  
  [[nodiscard]] double y() const { return values[1]; }
  
  [[nodiscard]] double z() const { return values[2]; }
  
  [[nodiscard]] double length_squared() const {
    return values[0] * values[0] + values[1] * values[1] + values[2] * values[2];
  }
  
  [[nodiscard]] double length() const { return sqrt(length_squared()); }
  
  // operator overloads
  vec3 operator-() const {
    return {-values[0], -values[1], -values[2]};
  }
  
  double operator[](int i) const {
    return values[i];
  }
  
  double &operator[](int i) {
    return values[i];
  }
  
  vec3 &operator+=(const vec3 &other) {
    values[0] += other[0];
    values[1] += other[1];
    values[2] += other[2];
    return *this;
  }
  
  vec3 &operator*=(const double scalar) {
    values[0] *= scalar;
    values[1] *= scalar;
    values[2] *= scalar;
    return *this;
  }
  
  vec3 &operator/=(const double scalar) {
    return *this *= (1 / scalar);
  }
  
};

// utility functions
inline std::ostream &operator<<(std::ostream &output, const vec3 &v) {
  return output << v[0] << ' ' << v[1] << ' ' << v[2];
}

inline vec3 operator+(const vec3 &u, const vec3 &v) {
  return {u[0] + v[0], u[1] + v[1], u[2] + v[2]};
}

inline vec3 operator-(const vec3 &u, const vec3 &v) {
  return {u[0] - v[0], u[1] - v[1], u[2] - v[2]};
}

inline vec3 operator*(const vec3 &u, const vec3 &v) {
  return {u[0] * v[0], u[1] * v[1], u[2] * v[2]};
}

inline vec3 operator*(double scalar, const vec3 &v) {
  return {scalar * v[0], scalar * v[1], scalar * v[2]};
}

inline vec3 operator*(const vec3 &v, double scalar) {
  return scalar * v;
}

inline vec3 operator/(vec3 v, double scalar) {
  return (1 / scalar) * v;
}

inline double dot(const vec3 &u, const vec3 &v) {
  return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 cross(const vec3 &u, const vec3 &v) {
  return {
    u[1] * v[2] - u[2] * v[1],
    u[2] * v[0] - u[0] * v[2],
    u[0] * v[1] - u[1] * v[0]
  };
}

inline vec3 unit_vector(vec3 v) {
  return v / v.length();
}

// type aliases
using point3 = vec3;  // cartesian coordinates
using color = vec3;   // rgb colors

#endif //RAY_TRACING_VEC3_H
