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
  
  vec3(double x, double y, double z) : values{x, y, z} {}
  
  
  // getters
  [[nodiscard]] double x() const { return values[0]; }
  
  [[nodiscard]] double y() const { return values[1]; }
  
  [[nodiscard]] double z() const { return values[2]; }
  
  [[nodiscard]] double length_squared() const {
    return values[0] * values[0] + values[1] * values[1] + values[2] * values[2];
  }
  
  [[nodiscard]] double length() const { return sqrt(length_squared()); }
  
  [[nodiscard]] inline static vec3 random() { return {random_double(), random_double(), random_double()}; }
  
  [[nodiscard]] inline static vec3 random(const double min, const double max) {
    return {random_double(min, max), random_double(min, max), random_double(min, max)};
  }
  
  
  // operator overloads
  vec3 operator-() const {
    return {-values[0], -values[1], -values[2]};
  }
  
  double operator[](int i) const {
    return values[i];
  }
  
  double& operator[](int i) {
    return values[i];
  }
  
  vec3& operator+=(const vec3& other) {
    values[0] += other[0];
    values[1] += other[1];
    values[2] += other[2];
    return *this;
  }
  
  vec3& operator*=(const double scalar) {
    values[0] *= scalar;
    values[1] *= scalar;
    values[2] *= scalar;
    return *this;
  }
  
  vec3& operator/=(const double scalar) {
    return *this *= (1 / scalar);
  }
  
  [[nodiscard]] bool near_zero() const {
    const double minimum = 1e-8;
    return fabs(values[0]) < minimum && fabs(values[1]) < minimum && fabs(values[2]) < minimum;
  }
  
};

// utility functions
inline std::ostream& operator<<(std::ostream& output, const vec3& vector) {
  return output << vector[0] << ' ' << vector[1] << ' ' << vector[2];
}

inline vec3 operator+(const vec3& u, const vec3& v) {
  return {u[0] + v[0], u[1] + v[1], u[2] + v[2]};
}

inline vec3 operator-(const vec3& u, const vec3& v) {
  return {u[0] - v[0], u[1] - v[1], u[2] - v[2]};
}

inline vec3 operator*(const vec3& u, const vec3& v) {
  return {u[0] * v[0], u[1] * v[1], u[2] * v[2]};
}

inline vec3 operator*(double scalar, const vec3& vector) {
  return {scalar * vector[0], scalar * vector[1], scalar * vector[2]};
}

inline vec3 operator*(const vec3& vector, double scalar) {
  return scalar * vector;
}

inline vec3 operator/(vec3 vector, double scalar) {
  return (1 / scalar) * vector;
}

inline double dot(const vec3& u, const vec3& v) {
  return u[0] * v[0] + u[1] * v[1] + u[2] * v[2];
}

inline vec3 cross(const vec3& u, const vec3& v) {
  return {
    u[1] * v[2] - u[2] * v[1],
    u[2] * v[0] - u[0] * v[2],
    u[0] * v[1] - u[1] * v[0]
  };
}

inline vec3 unit_vector(vec3 vector) {
  return vector / vector.length();
}

inline vec3 reflect(const vec3 incident, const vec3 normal) {
  return incident - (2 * dot(incident, normal) * normal);
}

vec3 random_in_unit_sphere() {
  while (true) {
    vec3 random = vec3::random(-1, 1);
    if (random.length_squared() >= 1) continue;
    return random;
  }
}

vec3 random_unit_vector() {
  return unit_vector(random_in_unit_sphere());
}

vec3 random_in_hemisphere(const vec3 normal) {
  vec3 random = random_in_unit_sphere();
  if (dot(random, normal) > 0) return random;
  else return -random;
}

// type aliases
using point3 = vec3;  // cartesian coordinates
using color = vec3;   // rgb colors

#endif //RAY_TRACING_VEC3_H
