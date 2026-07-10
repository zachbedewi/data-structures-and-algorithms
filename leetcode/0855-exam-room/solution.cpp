class ExamRoom {
  public:
    ExamRoom(int n) : capacity_{n}, seats_{} {}

    int seat() {
        int choice = 0;

        if (!seats_.empty()) {
            int maxDist = -1;

            int first = *seats_.begin();
            if (first > maxDist) {
                maxDist = first;
                choice = 0;
            }

            auto prevIt = seats_.begin();
            for (auto it = next(seats_.begin()); it != seats_.end(); ++it) {
                int midDist = (*it - *prevIt) / 2;
                if (midDist > maxDist) {
                    maxDist = midDist;
                    choice = *prevIt + midDist;
                }
                prevIt = it;
            }

            int last = *seats_.rbegin();
            if ((capacity_ - 1) - last > maxDist) {
                choice = capacity_ - 1;
            }
        }

        seats_.insert(choice);
        return choice;
    }

    void leave(int p) { seats_.erase(p); }

  private:
    std::set<int> seats_;
    int capacity_;
};
