#ifndef CONVEX_HULL_
#define CONVEX_HULL_

#include "point2d.h"
#include "vector.h"
#include "stack.h"
#include "quicksort.h"

#include <cmath>
#include <limits>
#include <iostream>

namespace stuff
{
    class convex_hull
    {
        vector<point2d> points_;

        public:
        void add_point(const point2d &p)
        {
            points_.append(p);
        }

        void add_point(double x, double y)
        {
            points_.append(point2d(x, y));
        }

        vector<point2d> calculate_graham()
        {
            vector<point2d> ret;
            vector_stack<point2d> st;

            // get the bottom most y point (ties by x)
            quicksort<point2d>(points_, [](const point2d &a, const point2d &b) {
                                               if (fabs(a.y() - b.y()) < std::numeric_limits<double>::epsilon())
                                                   return a.x() < b.x();
                                                return a.y() < b.y();
                                           });

            // sort by angle orientation based on the bottom y point
            auto compare = [this](const point2d &a, const point2d &b) {
                return compare_polar(points_[0], a, b);
            };
            quicksort<point2d>(points_, compare);

            // add the two most extreme points into the stack
            st.push(points_[0]);
            st.push(points_[1]);

            // add points counterclockwise
            for (size_t i = 2; i < points_.size(); i++) {
                point2d p = st.pop();
                while (st.peek().orientation(p, points_[i]) !=
                        point2d::orientation_t::COUNTERCLOCKWISE)
                    p = st.pop();

                st.push(p);
                st.push(points_[i]);
            }

            // print points
            while (!st.is_empty()) {
                point2d p = st.pop();
                std::cout << "x: " << p.x() << ", y: " << p.y() << std::endl;
            }

            return ret;
        }
    };
}

#endif
