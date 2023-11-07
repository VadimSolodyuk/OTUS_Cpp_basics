// Read files and prints top k word by frequency

#include <algorithm>
#include <chrono>
#include <fstream>
#include <future>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <map>
#include <mutex>
#include <string>
#include <vector>

const size_t TOPK = 10;

std::mutex mutex;

using Counter = std::map<std::string, std::size_t>;

thread_local Counter counters_words;

std::string tolower(const std::string &);

void count_words_thread(const std::vector<std::string> &vec_srt, Counter &main_counter, std::mutex &mut);

void merge_counter(Counter &main_counter, const std::pair<std::string, std::size_t> &pair, std::mutex &mut);

void print_topk(std::ostream &stream, const Counter &counter);

void reading_words (int argc, char **name_file, std::vector<std::vector<std::string> > &allWords);

int main(int argc, char *argv[]){

    if (argc < 2){
        std::cerr << "Usage: " << argv[0] << " [FILES...]\n";
        return EXIT_FAILURE;
    }

    auto start = std::chrono::high_resolution_clock::now();
    
    size_t n_threads = std::thread::hardware_concurrency();

    std::vector<std::vector<std::string> > allWords;
    allWords.resize(n_threads);
    
    reading_words (argc, argv, allWords);

    Counter main_counter;

    std::vector<std::future<void> > threads_counters;
    threads_counters.reserve(allWords.size());

    for (size_t i = 0; i < allWords.size(); ++i){
        threads_counters.emplace_back(
            std::async(std::launch::async,
             count_words_thread, std::ref(allWords[i]), std::ref(main_counter), std::ref(mutex))
        );
    }
    for (auto &c: threads_counters){
        c.get();
    }

    print_topk(std::cout, main_counter);
    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - start);
    std::cout << "Elapsed time is " << elapsed_ms.count() << " us\n";
}

void reading_words (int argc, char **name_file, std::vector<std::vector<std::string> > &allWords){
    for (int i{1}; i < argc; ++i){
        std::ifstream input{name_file[i]};
        if (!input.is_open()){
            std::cerr << "Failed to open file " << name_file[i] << '\n';
            return;
        }
        size_t index{0};
        std::for_each(std::istream_iterator<std::string>(input),
                        std::istream_iterator<std::string>(),
                        [&allWords, &index](const std::string &s){ 
                            allWords[index].emplace_back(s);
                            if (index == allWords.size() - 1) index = 0;
                            else ++index;
                        }
        );
    }
}

std::string tolower(const std::string &str)
{
    std::string lower_str;
    std::transform(std::cbegin(str), std::cend(str),
                   std::back_inserter(lower_str),
                   [](unsigned char ch)
                   { return std::tolower(ch); });
    return lower_str;
}

void merge_counter(Counter &main_counter, const std::pair<std::string, std::size_t> &pair, std::mutex &mut)
{
    std::lock_guard<std::mutex> lock(mut);
    if (main_counter.find(pair.first) == main_counter.end())
    {
        main_counter.insert(pair);
    }
    else main_counter.find(pair.first)->second += pair.second;
}

void count_words_thread(const std::vector<std::string> &vec_srt, Counter &main_counter, std::mutex &mut)
{
    std::for_each(vec_srt.begin(), vec_srt.begin() + vec_srt.size(),
                  [](const std::string &s)
                  { ++counters_words[tolower(s)]; });

    std::vector<Counter::const_iterator> words;
    words.reserve(counters_words.size());
    for (auto it = std::begin(counters_words); it != std::end(counters_words); ++it)
    {
        words.push_back(it);
    }
    std::partial_sort
    (
        std::begin(words), std::begin(words) + TOPK, std::end(words),
        [](auto lhs, auto &rhs)
        { return lhs->second > rhs->second; }
    );

    std::for_each
    (
        std::begin(words), std::begin(words) + TOPK,
        [&main_counter, &mut](auto &pair)mutable
        {
            merge_counter(main_counter, *pair, mut);
        }
    );
}

void print_topk(std::ostream &stream, const Counter &counter)
{
    std::vector<Counter::const_iterator> words;
    words.reserve(counter.size());
    for (auto it = std::cbegin(counter); it != std::cend(counter); ++it)
    {
        words.push_back(it);
    }

    std::partial_sort(
        std::begin(words), std::begin(words) + TOPK, std::end(words),
        [](auto lhs, auto &rhs)
        { return lhs->second > rhs->second; });

    std::for_each(
        std::begin(words), std::begin(words) + TOPK,
        [&stream](const Counter::const_iterator &pair)
        {
            stream << std::setw(4) << pair->second << " " << pair->first
                   << '\n';
        });
}
