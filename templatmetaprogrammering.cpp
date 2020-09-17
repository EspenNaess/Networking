//
//  templatmetaprogrammering.cpp
//
//  Created by Espen Næss on 02.05.15.
//  Copyright (c) 2015 Espen Næss. All rights reserved.
//

class Testklasse {
public:
    explicit Testklasse(int s, int d) {
        cout << "konstruert: " << s << endl;
    }
    int d;
};

int main(int argc, const char * argv[]) {
    cout << Har_Constructor<Testklasse>::verdi;

    std::cout << er_i_typesettet<int, short, long, double, float>::resultat << std::endl;

    std::cout << Har_Contructor<int>::verdi << std::endl;

    return 0;
}
