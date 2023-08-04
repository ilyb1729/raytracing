#ifndef HITTABLE_LIST_H
#define HITTABLE_LIST_H

#include "hittable.h"

#include <memory>
#include <vector>

class hittable_list: public hittable {
    std::vector<std::shared_ptr<hittable>> objs;
public:
    hittable_list();
    hittable_list(std::shared_ptr<hittable> obj);

    void clear();
    void add(std::shared_ptr<hittable> obj);

    bool hit(const ray &r, const double t_min, const double t_max, hit_record &rec) const override;
};

#endif