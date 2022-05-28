//
// Created by Bruce Jia on 2022/5/28.
//

// This file is for demonstration of CRTP - Curiously Recurring Template Pattern
// https://www.fluentcpp.com/2017/05/12/curiously-recurring-template-pattern/

#include <iostream>
#include <string>


struct FeatureA {
    std::string featureName() const {
        return "feature A";
    }
};

struct FeatureB {
    std::string featureName() const {
        return "feature B";
    }
};

template<typename OptionalFeature>
struct CoreProduct : OptionalFeature {
    virtual std::string who_am_i () const {
        return "core";
    }

    std::string details() const {
        //NOTE: "this->" below is a MUST. Otherwise, the compiler will raise error
        // because it cannot resolve function call "featureName". Can "concept" be used to address this?
        return who_am_i() + " with feature " + this->featureName();
    }
};

template<class OptionalFeature>
struct FancyProduct : CoreProduct<OptionalFeature> {
    std::string who_am_i() const override {
        return "fancy";
    }

    std::string even_more_details() const {
        return "hi, I'm a fancy product derived from core product " + this->details();
    }
};

// Another usage - CRTP
template<class HouseType>
struct WithDoor {

    std::string details() {
        HouseType * self = static_cast<HouseType *>(this);
        return " with a fancy door added to " + self->name();
    }
};

template<class HouseType>
struct WithRoof {

    std::string details() {
        HouseType * self = static_cast<HouseType *>(this);

        return " with a roof added to " + self->name();
    }
};

struct Apartment : WithDoor<Apartment> {

    std::string name() const {
        return "apartment";
    }
};

struct Restroom : WithRoof<Restroom> {
    std::string name() const {
        return "restroom";
    }

    // use a friend to access private members
    friend std::ostream & operator << (std::ostream & os, Restroom & rr) {
        os << rr.details() << "(id=" << rr._id << ")";
        return os;
    }

private:
    int _id;
};

struct SuperApartment : WithRoof<SuperApartment>, WithDoor<SuperApartment> {
    typedef SuperApartment SELF_TYPE;

    std::string name() {
        return "super apartment";
    }

    std::string details() {
        auto * withRoof = static_cast<WithRoof<SELF_TYPE> *>(this);
        auto * withDoor = static_cast<WithDoor<SELF_TYPE> *>(this);

        return withRoof->details() + ";" + withDoor->details();
    }
};

// free function
std::ostream & operator << (std::ostream & os, SuperApartment & sa) {
    return (os << sa.details());
}

int main() {
    auto aProduct = CoreProduct<FeatureA>();
    auto bProduct = CoreProduct<FeatureB>();

    std::cout << "aProduct is " << aProduct.details() << std::endl;
    std::cout << "bProduct is " << bProduct.details() << std::endl;

    auto fancyProduct = FancyProduct<FeatureA>{};
    std::cout << fancyProduct.even_more_details() << std::endl;
    std::cout << fancyProduct.details() << std::endl;
    std::cout << "Who am I? " << fancyProduct.who_am_i();

    std::cout << std::endl;
    Apartment a;
    std::cout << a.details() << std::endl;

    SuperApartment sa;
    std::cout << sa << std::endl;

    Restroom rr;
    std::cout << rr << std::endl;
}
