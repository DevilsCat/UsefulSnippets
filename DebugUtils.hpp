#ifndef DEBUG_UTILS_H
#define DEBUG_UTILS_H

#define DEBUG

#ifdef DEBUG
#define ASSERT(cond) do {assert(cond);} while(0)
#else
#define ASSERT(cond) do {} while(0)
#endif


#ifdef DEBUG
#define DEBUG_INFO(func) do{ func;}while(0)
#else
#define DEBUG_INFO(func) do{}while(0)
#endif

//
//This mutex is used to guarentee correct printing format for each  
//area's schedule.
//
extern std::mutex printLock;

namespace console {
    inline
    std::string left(const std::string s, const int w, const char delimiter) {
        std::stringstream ss, spaces;
        int padding = w - s.size() - 1;  // count excess room to pad
        for (int i = 0; i<padding; ++i)
            spaces << delimiter;
        ss << s << spaces.str();  // format with padding
        return ss.str();
    }

    inline
    std::string left(const std::string s, const int w, const char delimiter) {
        std::stringstream ss, spaces;
        int padding = w - s.size() - 1;                 // count excess room to pad
        for (int i = 0; i<padding; ++i)
            spaces << delimiter;
        ss << s << spaces.str();                    // format with padding
        return ss.str();
    }

    inline
    std::string truncate(const std::string& s, size_t w, bool show_ellipsis = true) {
        const std::string sEllipsis = "...";
        if (s.length() > w)
            return show_ellipsis ? s.substr(0, w - sEllipsis.size()) + sEllipsis : s.substr(0, w);
        return s;
    }
}

namespace utils {
  template <typename T>
  int indexAt(const T& target, const vector<T>& vec) {
    auto it = find(vec.begin(), vec.end(), target);
    return it == vec.end() ? -1 : it - vec.begin();
  }
}

#endif
