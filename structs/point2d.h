#ifndef POINT2D_H_
#define POINT2d_H_

#include <utility>
#include <cmath>
#include <limits>

namespace stuff
{
    class point2d
    {
        double x_;
        double y_;

    private:
        friend bool compare_polar(const point2d &a,
                                  const point2d &b,
                                  const point2d &c);

    public:
        enum class orientation_t
        {
            COLINEAR,
            CLOCKWISE,
            COUNTERCLOCKWISE,
        };

    public:
        point2d(double x, double y) :
            x_(x), y_(y)
        {
        }

        point2d() :
            point2d(0.0, 0.0)
        {
        }

        double x() const
        {
            return x_;
        }

        double y() const
        {
            return y_;
        }

        void x(double x)
        {
            x_ = x;
        }

        void y(double y)
        {
            y_ = y;
        }

        double distance_to(const point2d p) const
        {
            return (x_ - p.x_) * (x_ - p.x_) +
                   (y_ - p.y_) * (y_ - p.y_);
        }

        std::pair<double, double> to_polar() const
        {
            double t = atan2(x_, y_);
            double r = sqrt(x_ * x_ + y_ * y_);
            return std::make_pair(r, t);
        }

        void from_polar(double r, double t)
        {
            x_ = r * cos(t);
            y_ = r * sin(t);
        }

        double angle_to(const point2d &p)
        {
            auto dx = p.x_ - x_;
            auto dy = p.y_ - y_;
            return atan2(dx, dy);
        }

        orientation_t orientation(const point2d &q, const point2d &r) const
        {
            double ret = (q.y_ - y_) * (r.x_ - q.x_) -
                         (q.x_ - x_) * (r.y_ - q.y_);

            if (ret < std::numeric_limits<double>::epsilon() &&
                -ret < std::numeric_limits<double>::epsilon()) {
                return orientation_t::COLINEAR;
            }
            else if (ret >= std::numeric_limits<double>::epsilon()) {
                return orientation_t::CLOCKWISE;
            }
            return orientation_t::COUNTERCLOCKWISE;
        }
    };

    bool compare_polar(const point2d &a,
                       const point2d &b,
                       const point2d &c)
    {
        auto orient = a.orientation(b, c);
        if (orient == point2d::orientation_t::COLINEAR)
            return a.distance_to(b) < a.distance_to(c);

        return (orient == point2d::orientation_t::COUNTERCLOCKWISE);
    }
}

#endif
