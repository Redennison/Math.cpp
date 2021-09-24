#include<utility>
#include<iostream>
#include<vector>
#include<algorithm>
#include<math.h>

using namespace std;

class Polynomial {
    public:
        vector<pair<int, int> > points;
        int V;
        int lc;
        int num_points; 
        int degree;
        void get_function();
    
    private:
        void get_base_equations(int num_vars);
        void get_points();
        void get_lc();
        void iso_vars();
        bool calc_degree();
        bool check_constant(int diff[], int num_diff);
};

void Polynomial::get_lc() {
    int n = 1;
    for (int i=1;i<=degree;i++)
        n *= i;
    lc = V/n;
}

void Polynomial::get_points() {
    int x, y;
    cout << "Input # of points: ";
    cin >> num_points;
    // get x/y values of points
    for (int i=1;i<num_points+1;i++) {
        cout << "x" << i << ": ";
        cin >> x;
        cout << "y" << i << ": ";
        cin >> y;
        points.push_back(make_pair(x, y));
    }
    // sorts vector by x values
    sort(points.begin(), points.end());
}

bool Polynomial::check_constant(int diff[], int num_diff) {
    for (int i=1;i<num_diff;i++) {
        if (diff[i] != diff[i-1])
            return false;
    }
    return true;
}

// Calculates degree of polynomial 
// Returns true if successfull/false if unsuccessful
bool Polynomial::calc_degree() {
    int diff[num_points], num_diff = num_points; 
    for (int i=0;i<num_points;i++)
        diff[i] = points[i].second; 

    // if all y's the same at start then line is horizontal
    while ((!check_constant(diff, num_diff)) and (num_diff > 1)) {
        for (int i=0;i<num_diff-1;i++)
            diff[i] = diff[i+1]-diff[i];
        num_diff--;
    }

    if (num_diff > 1) {
        V = diff[0];
        degree = num_points-num_diff;
        return true;
    } else {
        cout << "Function unable to be determined. Please try again.";
        return false;
    }
}

void Polynomial::get_function() {
    get_points();
    if (calc_degree()) {
        get_lc();
        if (degree == 1) {
            if (lc == 1)
                cout << "f(x) = " << "x" << "\n";     
            else 
                cout << "f(x) = " << lc << "x" << "\n";
        } else if (degree == 0) 
            cout << "f(x) = " << lc << "\n"; 
        else {
            if (lc == 1)
                cout << "f(x) = " << "x^" << degree << "\n"; 
            else 
                cout << "f(x) = " << lc << "x^" << degree << "\n";               
        }
    } 
}

int main() {
    Polynomial poly;
    poly.get_function();
}