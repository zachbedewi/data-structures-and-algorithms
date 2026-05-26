  class Solution {
  public:
      long long countOfSubstrings(string word, int k) {
          return atLeast(word, k) - atLeast(word, k + 1);
      }

  private:
      long long atLeast(const string& word, int k) {
        const int n = word.size();

        array<int, 5> vowelCount = {};
        int numConsonants = 0;
        int numUniqueVowels = 0;

        long long res = 0;
          for (int left = 0, right = 0; right < n; right++) {
              int vi = vowelIdx(word[right]);
              if (vi >= 0) {
                if (++vowelCount[vi] == 1) {
                    ++numUniqueVowels;
                }
              } else {
                ++numConsonants;
              }

              while (numUniqueVowels == 5 && numConsonants >= k) {
                  int lvi = vowelIdx(word[left]);
                  if (lvi >= 0) {
                    if (--vowelCount[lvi] == 0) {
                        --numUniqueVowels;
                    }
                  } else {
                      --numConsonants;
                  }
                  left++;
              }

              res += left;
          }

          return res;
      }

      int vowelIdx(char c) {
          switch (c) {
              case 'a': return 0;
              case 'e': return 1;
              case 'i': return 2;
              case 'o': return 3;
              case 'u': return 4;
              default: return -1;
          }
      }
  };
