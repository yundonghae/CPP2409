#include <iostream>
#include <vector>
using namespace std;

class Movie {
public:
    string title;
    double rating;

    Movie(string n, double r) : title(n), rating(r) {}
};

int main() {
    // 영화 목록
    vector<Movie> movies = {
        Movie("titanic", 9.9),
        Movie("gone with the wind", 9.6),
        Movie("terminator", 9.7)
    };

    // 영화 정보 출력
    cout << "입력된 영화 정보:\n";
    for (auto& movie : movies) {
        cout << movie.title << ": " << movie.rating << endl;
    }

    return 0;
}