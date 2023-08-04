#include "hittable_list.h"

#include <memory>
#include <vector>


hittable_list::hittable_list() {}
hittable_list::hittable_list(std::shared_ptr<hittable> obj) { add(obj); }

void hittable_list::clear() { objs.clear(); }
void hittable_list::add(std::shared_ptr<hittable> obj) { objs.push_back(obj); }

bool hittable_list::hit(const ray &r, const double t_min, const double t_max, hit_record &rec) const {
    hit_record temp_rec;
    bool hit_any = false;
    double closest = t_max;

    for (const auto &obj : objs) {
        if (obj->hit(r,t_min, closest, temp_rec)) {
            hit_any = true;
            closest = temp_rec.t;
            rec = temp_rec;
        }
    }

    return hit_any;
}