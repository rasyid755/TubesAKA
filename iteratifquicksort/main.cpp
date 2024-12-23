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


int partition(Video videos[], int low, int high) {

    double pivot = videos[high].trendScore;
    int i = (low - 1);

    for (int j = low; j < high; ++j) {
        if (videos[j].trendScore >= pivot) {
            ++i;
            std::swap(videos[i], videos[j]);
        }
    }
    std::swap(videos[i + 1], videos[high]);
    return (i + 1);
}


void quickSortIterative(Video videos[], int low, int high) {
    int* lowStack = new int[high - low + 1];
    int* highStack = new int[high - low + 1];

    int top = -1;

    lowStack[++top] = low;
    highStack[top] = high;

    while (top >= 0) {
        high = highStack[top];
        low = lowStack[top--];

        int pi = partition(videos, low, high);


        if (pi - 1 > low) {
            lowStack[++top] = low;
            highStack[top] = pi - 1;
        }


        if (pi + 1 < high) {
            lowStack[++top] = pi + 1;
            highStack[top] = high;
        }
    }

    delete[] lowStack;
    delete[] highStack;
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


    quickSortIterative(videos, 0, n - 1);

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
