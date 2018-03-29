/*
 * Static object pool libary 
 * Copyright (C) 2018 Dao Minh Thuc 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef __POOL_HPP
#define __POOL_HPP
#include <array>
#include <memory>
using namespace std;

enum class Is_available: bool {yes, no};
template <class T, size_t N> 
class Pool {
public:
    template<class ...Args>
    Pool(Args&& ...args) noexcept
        :storage_{}, num_of_avail_(N), status_{}
    {
        storage_.fill(T{std::forward<Args>(args)...});
        status_.fill(Is_available::yes);
    }

    Pool(const Pool& other) = delete;
    Pool(Pool&& other) = delete; 
    Pool& operator = (const Pool& other) = delete; 
    Pool& operator = (Pool&& other) = delete; 

    auto acquire() noexcept
    {
        auto deleter = [this] (const T* obj) {
            if (nullptr == obj)
                return;
            status_[obj-&storage_[0]] = Is_available::yes;
        };

        if (0 == num_of_avail_)
            return unique_ptr<T, decltype(deleter)>(nullptr,deleter); 
        for (size_t i = 0; i < status_.size(); ++i) {
            if (Is_available::yes == status_[i]) {
                status_[i] = Is_available::no;
                --num_of_avail_;
                return unique_ptr<T, decltype(deleter)>(&storage_[i],deleter); 
            }
        }
    }

    size_t num_of_avail() const noexcept {return num_of_avail_;};
private:
    size_t num_of_avail_;
    std::array<T,N> storage_; 
    std::array<Is_available, N> status_;
};

#endif

