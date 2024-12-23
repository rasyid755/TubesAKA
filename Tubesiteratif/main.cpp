#include <iostream>
#include <string>


struct Video {
    std::string title;
    int views;
    int likes;
    int comments;
    int shares;
    double trendScore;


    Video() : views(0), likes(0), comments(0), shares(0), trendScore(0.0) {}

    Video(std::string t, int v, int l, int c, int s) {
        title = t;
        views = v;
        likes = l;
        comments = c;
        shares = s;
        trendScore = calculateTrendScore();
    }


    double calculateTrendScore() {
        return 0.5 * likes + 0.3 * comments + 0.2 * shares;
    }
};


void merge(Video videos[], int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;


    Video* L = new Video[n1];
    Video* R = new Video[n2];


    for (int i = 0; i < n1; ++i) {
        L[i] = videos[left + i];
    }
    for (int j = 0; j < n2; ++j) {
        R[j] = videos[mid + 1 + j];
    }


    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].trendScore >= R[j].trendScore) {
            videos[k] = L[i];
            ++i;
        } else {
            videos[k] = R[j];
            ++j;
        }
        ++k;
    }


    while (i < n1) {
        videos[k] = L[i];
        ++i;
        ++k;
    }
    while (j < n2) {
        videos[k] = R[j];
        ++j;
        ++k;
    }


    delete[] L;
    delete[] R;
}


void mergeSortIterative(Video videos[], int n) {

    for (int size = 1; size < n; size *= 2) {
        for (int left = 0; left < n - size; left += 2 * size) {
            int mid = std::min(left + size - 1, n - 1);
            int right = std::min(left + 2 * size - 1, n - 1);

            merge(videos, left, mid, right);
        }
    }
}

int main() {

    const int n = 5;


    Video videos[n] = {
        Video("Tutorial C++", 1000, 150, 20, 10),
        Video("Review Gadget", 800, 100, 50, 30),
        Video("Travel Vlog", 1500, 200, 60, 40),
        Video("Cooking Recipe", 1200, 180, 40, 20),
        Video("Gaming Highlights", 900, 170, 30, 15)
    };

    std::cout << "Data video awal sebelum disorting:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << videos[i].title << " - Views: " << videos[i].views
                  << ", Likes: " << videos[i].likes
                  << ", Comments: " << videos[i].comments
                  << ", Shares: " << videos[i].shares
                  << ", Trend Score: " << videos[i].trendScore << "\n";
    }


    mergeSortIterative(videos, n);

    std::cout << "\nData video setelah disorting berdasarkan urutan trennya:\n";
    for (int i = 0; i < n; ++i) {
        std::cout << videos[i].title << " - Views: " << videos[i].views
                  << ", Likes: " << videos[i].likes
                  << ", Comments: " << videos[i].comments
                  << ", Shares: " << videos[i].shares
                  << ", Trend Score: " << videos[i].trendScore << "\n";
    }

    return 0;
}
