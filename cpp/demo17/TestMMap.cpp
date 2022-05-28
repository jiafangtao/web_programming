//
// Created by Bruce Jia on 2022/5/23.
//

#include "TestMMap.h"
#include <map>
#include <string>
#include <iostream>


namespace demo {
    void TestMMap::testMap() {
        std::map<int, std::string> m;
        auto ret = m.insert(std::make_pair(0, "0"));
        std::cout << "value of the element is (" << ret.first->first << ", " << ret.first->second <<  "); inserted: " << ret.second << std::endl;

        ret = m.insert(std::make_pair(1, "1"));
        std::cout << "value of the element is (" << ret.first->first << ", " << ret.first->second <<  "); inserted: " << ret.second << std::endl;

        ret = m.insert(std::make_pair(2, "2"));
        std::cout << "value of the element is (" << ret.first->first << ", " << ret.first->second <<  "); inserted: " << ret.second << std::endl;

        // This won't change the map because the key already exists.
        // ret.second is false to indicate no insertion happened.
        ret = m.insert(std::make_pair(0, "000"));
        std::cout << "value of the element is (" << ret.first->first << ", " << ret.first->second <<  "); inserted: " << ret.second << std::endl;

        std::cout << "test is done" << std::endl;
    }

    void TestMMap::testMMap() {
        std::multimap<int, std::string> mm;

        mm.insert(std::make_pair(9, "99"));

        auto ret = mm.insert(std::make_pair(0, "0"));
        std::cout << "ret " << ret->first << "; " << ret->second << std::endl;

        mm.insert(std::make_pair(8, "8"));

        ret = mm.insert(std::make_pair(0, "00"));
        std::cout << "ret " << ret->first << "; " << ret->second << std::endl;

        mm.insert(std::make_pair(7, "7"));

        // find returns any of the elements if there are more.
        auto it = mm.find(0);
        std::cout << "find in multimap: " << it->second << std::endl;

        // use equal_range to loop through all matched elements
        auto range = mm.equal_range(0);
        for (auto p = range.first; p != range.second; ++p) {
            std::cout << p->first << " => " << p->second << std::endl;
        }

        const auto pStart = mm.lower_bound(0);
        const auto pEnd = mm.upper_bound(0);
        for (auto p = pStart; p != pEnd; ++p) {
            std::cout << "mm[" << p->first << "] = " << p->second << std::endl;
        }
    }
} // demo
