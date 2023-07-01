#include "repository.h"

//Constructor
Repository::Repository() {}

//Destructor
Repository::~Repository() {}

//Sets DTO object pointers inside its container if they don't already exists
void Repository::setList(std::unique_ptr<DTO> newDTO) {
    if (newDTO == nullptr) {
        throw std::invalid_argument("Invalid argument: invalid pointer");
    }
    bool found = false;
    for (const auto& dtoPtr : list) {
        if (dtoPtr->getName() == newDTO->getName()) {
            found = true;
            break;
        }
    }
    if (!found) {
        list.emplace_back(std::move(newDTO));
    }
}

//getter function
const std::vector<std::unique_ptr<DTO>>& Repository::getList() const {
    return list;
}
