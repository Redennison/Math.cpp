#include<utility>
#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<math.h>

using namespace std;

class Polynomial {
    public:
        vector<pair<double, double>> points;
        int V;
        string lc;
        int num_points; 
        int degree;
        void get_function();
    
    private:
        void get_points();
        void get_lc();
        bool calc_degree();
        bool check_constant(double diff[], int num_diff);
};

// Calculates leading coefficient
void Polynomial::get_lc() {
    int n = 1;
    for (int i=degree;i>1;i--)
        n *= i;
    if (V%n == 0) 
        lc = to_string(V/n);
    else {
        int gcd = __gcd(V, n);
        if (((V<0) && (n>0)) || ((V>0) && (n<0)))
            lc = "(-" + to_string(abs(V/gcd)) + "/" + to_string(abs(n/gcd)) + ")";
        else 
            lc = "(" + to_string(abs(V/gcd)) + "/" + to_string(abs(n/gcd)) + ")";
    }
}

// Gets x/y values of points
void Polynomial::get_points() {
    double x, y;
    cout << "Input # of points (degree + 2): ";
    cin >> num_points;
    for (int i=1;i<num_points+1;i++) {
        cout << "x" << i << ": ";
        cin >> x;
        cout << "y" << i << ": ";
        cin >> y;
        points.push_back(make_pair(x, y));
    }
    // Sorts vector by x values
    sort(points.begin(), points.end());
}

// Determines whether differences are constant
bool Polynomial::check_constant(double diff[], int num_diff) {
    for (int i=1;i<num_diff;i++) {
        if (diff[i] != diff[i-1])
            return false;
    }
    return true;
}

// Calculates degree of polynomial 
// Returns true if successfull/false if unsuccessful
bool Polynomial::calc_degree() {
    double diff[num_points];
    int num_diff = num_points; 
    for (int i=0;i<num_points;i++) {
        diff[i] = points[i].second; 
        cout << diff[i] << "\n";
    }

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
        if (degree == 0) 
            cout << "f(x) = " << lc << "\n"; 
        else if (degree == 1) {
            lc == "1" ? cout << "f(x) = " << "x" << "\n" : cout << "f(x) = " << lc << "x" << "\n";
        } else {
            lc == "1" ? cout << "f(x) = " << "x^" << degree << "\n" : cout << "f(x) = " << lc << "x^" << degree << "\n";               
        }
    } 
}

int main() {
    Polynomial poly;
    poly.get_function();
}