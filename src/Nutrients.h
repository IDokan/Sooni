/******************************************************************************
Copyright (C)
File Name:   Nutrients.h
Author
	- sinil.kang	rtd99062@gmail.com
Creation Date: 06.25.2024
	Header file for Nutrients.
	A structure contains information about nutrients.
******************************************************************************/
#ifndef NUTRIENTS_H
#define NUTRIENTS_H

#include <godot_cpp/core/math.hpp>

namespace godot {

class Nutrients {

public:
	Nutrients();
	~Nutrients();

    int32_t get_calories() const;
    void set_calories(int32_t _calories);
    
    int32_t get_total_fat() const;
    void set_total_fat(int32_t _total_fat);

    int32_t get_saturated_fat() const;
    void set_saturated_fat(int32_t _saturated_fat);
    
    int32_t get_trans_fat() const;
    void set_trans_fat(int32_t _trans_fat);

    int32_t get_colesterol() const;
    void set_colesterol(int32_t _colesterol);
    
    int32_t get_sodium() const;
    void set_sodium(int32_t _sodium);

    int32_t get_total_carbohydrate() const;
    void set_total_carbohydrate(int32_t _total_carbohydrate);
    
    int32_t get_dietary_fiber() const;
    void set_dietary_fiber(int32_t _dietary_fiber);

    int32_t get_sugars() const;
    void set_sugars(int32_t _sugars);
    
    int32_t get_protein() const;
    void set_protein(int32_t _protein);

private:
    int32_t calories;
    int32_t total_fat;
    int32_t saturated_fat;
    int32_t trans_fat;
    int32_t colesterol;
    int32_t sodium;
    int32_t total_carbohydrate;
    int32_t dietary_fiber;
    int32_t sugars;
    int32_t protein;
};

}

#endif