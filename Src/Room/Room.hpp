#ifndef ROOM_HPP
#define ROOM_HPP

#include <string>
#include "../Utility/Date.hpp"

#define NOT_RESERVED -1

class Room {

public:

    Room(int id_);
    bool is_available(range request_date);
    void reserve(range _reserve_date_);
    void cancel_reserve();
    virtual std::string get_id() = 0;

private:

	range reserve_date_;

protected:

	int id;
};

#endif