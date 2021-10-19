#include <iostream>
#include <vector>
#include <utility>

template <typename T>
using majority_pair = std::pair<bool, std::pair<unsigned, T>>;

template <typename T>
majority_pair<T> haveMajority(std::vector<T>& data);

int main()
{
  std::vector<int> data = {1, 3, 5, 5, 5};

  if (haveMajority(data).first == true)
  {
    std::cout << "The majority of this array: " << haveMajority(data).second.second;
  }
  else std::cout << "There isn't majority in this array!";

  return 0;
}

template <typename T>
majority_pair<T> haveMajority(std::vector<T>& data)
{
  bool result = false;

  if (data.size() == 1)
  {
    result = true;
    return std::make_pair(result, std::make_pair(1, data[0]));
  }

  std::vector<T> data_1(data.begin(), data.begin() + data.size() / 2);
  std::vector<T> data_2(data.begin() + data.size() / 2, data.end());

  auto m1 = haveMajority<T>(data_1);

  if (m1.first)
  {
    for (auto i = 0u; i < data_2.size(); ++i)
    {
      if (data_2[i] == m1.second.second) ++(m1.second.first);
    }

    if (m1.second.first > data.size() / 2) return m1;
  }

  auto m2 = haveMajority<T>(data_2);

  if (m2.first)
  {
    for (auto i = 0u; i < data_1.size(); ++i)
    {
      if (data_1[i] == m2.second.second) ++(m2.second.first);
    }

    if (m2.second.first > data.size() / 2) return m2;
  }

  return std::make_pair(result, std::make_pair(0, T()));
}
