#include "include/Location.h"

Location::Location(int id, const std::string& name, const std::string& type, int parentId)
    : id(id), name(name), type(type), parentId(parentId) {}

int Location::getId() const {
    return id;
}

std::string Location::getName() const {
    return name;
}

std::string Location::getType() const {
    return type;
}

int Location::getParentId() const {
    return parentId;
}
