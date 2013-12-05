#include <iostream>
#include "lecture.h"

int lecture::_static_id =0;

lecture::lecture() : _id_course(-1),_id_prof(-1) {
    _id=_static_id++;
}

lecture::lecture(int id_course, int id_prof, int id_week):
_id_course(id_course),_id_prof(id_prof), _id_week(id_week) {
    _id=_static_id++;
}

int lecture::get_id_course() {
    return _id_course;
}
