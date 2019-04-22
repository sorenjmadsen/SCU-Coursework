//
//  poly.cpp
//  Polyomials
//
//  Created by soren j madsen on 1/31/19.
//  Copyright © 2019 SCU. All rights reserved.
//

#include <stdio.h>
#include <cassert>
#include <math.h>
#include "poly.h"
#include <iomanip>

using namespace coen79_lab4;



namespace coen79_lab4 {
    // CONSTRUCTOR
    polynomial::polynomial(double c, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        
        for (unsigned int i = 0; i <= MAXIMUM_DEGREE; i++){
            coef[i] = 0;
        }
        coef[exponent] = c;
        current_degree = exponent;
    }
    
    // MODIFICATION MEMBER FUNCTIONS
    void polynomial::assign_coef(double coefficient, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        coef[exponent] = (double)coefficient;
        current_degree = (exponent > degree()) ? exponent : degree();
    }
    void polynomial::add_to_coef(double amount, unsigned int exponent){
        assert(exponent <= MAXIMUM_DEGREE);
        coef[exponent] += amount;
        current_degree = (exponent > degree()) ? exponent : degree();
    }
    void polynomial::clear(){
        for (unsigned int i = 0; i <= MAXIMUM_DEGREE; i++){
            coef[i] = 0.0;
        }
        current_degree = 0;
    }
    
    // CONSTANT MEMBER FUNCTIONS
    polynomial polynomial::antiderivative( ) const{
        assert(degree() <= MAXIMUM_DEGREE);
        polynomial temp;
        for(unsigned int i = MAXIMUM_DEGREE - 1; i >= 0; i--){
            if(coefficient(i) != 0){
                temp.assign_coef(coefficient(i)/(i+1), i + 1);
            }
            if(i == 0) break;
        }
        return temp;
    }
    double polynomial::coefficient(unsigned int exponent) const{
        assert(exponent <= MAXIMUM_DEGREE);
        return coef[exponent];
    }
    double polynomial::definite_integral(double x0, double x1) const{
        polynomial integral = this->antiderivative();
        double left  = 0;
        double right = 0;
        
        for (unsigned int i = 0; i <= MAXIMUM_DEGREE; i++){
            left  += integral.coefficient(i) * pow(x0, i);
            right += integral.coefficient(i) * pow(x1, i);
        }
        return right - left;
    }
    unsigned int polynomial::degree( ) const{
        return current_degree;
    }
    polynomial polynomial::derivative( ) const{
        polynomial temp;
        for(unsigned int i = 1; i <= MAXIMUM_DEGREE; i++){
            if(coefficient(i) != 0){
                temp.assign_coef(coefficient(i) * i, i - 1);
            }
        }
        temp.current_degree = degree() - 1;
        return temp;
    }
    double polynomial::eval(double x) const{
        double sum = coefficient(0);
        for(unsigned int i = 1; i <= MAXIMUM_DEGREE; i++){
            sum += coefficient(i) * pow(x,i);
        }
        return sum;
    }
    bool polynomial::is_zero( ) const{
        return current_degree == 0;
    }
    unsigned int polynomial::next_term(unsigned int e) const{
        for(unsigned int i = e + 1; i <= MAXIMUM_DEGREE; i++){
            if(coefficient(i) != 0) return i;
        }
        return 0;
    }
    unsigned int polynomial::previous_term(unsigned int e) const{
        if(e == 0) return UINT_MAX;
        for(unsigned int i = e; i > 0 ; i--){
            if(coefficient(i - 1) != 0) return i - 1;
        }
        return UINT_MAX;
    }
    
    double polynomial::operator( ) (double x) const{
        return eval(x);
    }
    
    // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2){
        polynomial temp;
        
        for(unsigned int i = 0; i <= (p1.degree() > p2.degree() ? p1.degree() : p2.degree()); i++){
            temp.assign_coef(p1.coefficient(i) + p2.coefficient(i), i);
        }
        return temp;
    }
    polynomial operator -(const polynomial& p1, const polynomial& p2){
        polynomial temp;
        
        for(unsigned int i = 0; i <= (p1.degree() > p2.degree() ? p1.degree() : p2.degree()); i++){
            temp.assign_coef(p1.coefficient(i) - p2.coefficient(i), i);
        }
        return temp;
    }
    polynomial operator *(const polynomial& p1, const polynomial& p2){
        assert(p1.degree() + p2.degree() <= polynomial::MAXIMUM_DEGREE);
        polynomial temp;
        for(unsigned int i = 0; i <= p1.degree(); i++){
            for(unsigned int j = 0; j <= p2.degree(); j++){
                temp.add_to_coef(p1.coefficient(i) * p2.coefficient(j), i + j);
            }
        }
        return temp;
    }
    
    
    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p){
        bool first = true;
        std::setprecision(2);
        for (unsigned int i = polynomial::MAXIMUM_DEGREE; i > 0; i--){
            if(p.coefficient(i) != 0.0){
                if(first){
                    if(i == 1) out << p.coefficient(i) << "x";
                    else out << (double)p.coefficient(i) << "x^" << i;
                    first = false;
                }
                else if(i == 1){
                    out << ((p.coefficient(i) > 0) ? " + " : " - ") << abs((double)p.coefficient(i)) << "x";
                }
                else out << ((p.coefficient(i) > 0) ? " + " : " - ") << abs((double)p.coefficient(i)) << "x^" << i;
            }
        }
        if(p.coefficient(0) != 0){
            if(first) out << (double)p.coefficient(0);
            else out << ((p.coefficient(0) > 0) ? " + " : " - ") << abs((double)p.coefficient(0));
        }
        return out;
    }
}
