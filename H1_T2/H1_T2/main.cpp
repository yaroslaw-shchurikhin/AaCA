#include <iostream>
#include <vector>
#include <list>
#include <utility>

template <typename T>
using majority_pair = std::pair<bool, std::pair<unsigned, T>>;

template <typename T, 
  template <typename U, typename Allocator = std::allocator<U>> class Container>
majority_pair<T> haveMajority(Container <T> & data);

int main()
{
  std::vector<int> data = { 1, 3, 5, 5, 5 };
  std::list<char> data2 = { 'a', 'c', 'b', 'a', 'b', 'b', 'b'};

  if (haveMajority(data).first == true)
  {
    std::cout << "The majority of this array: " << haveMajority(data).second.second;
  }
  else std::cout << "There isn't majority in this array!";

  return 0;
}

template <typename T, template <typename U, 
  typename Allocator = std::allocator<U>> class Container>
majority_pair<T> haveMajority(Container <T, std::allocator<T>>& data) //Works with any container 
{                                                                     //that supports the size() method and forward iterators
  bool result = false;

  if (data.size() == 1)
  {
    result = true;
    return std::make_pair(result, std::make_pair(1, *data.begin()));
  }

  auto iter_mid = data.begin();
  for (auto i = 0u; i < data.size() / 2; ++i) iter_mid++;
  Container <T> data_1(data.begin(), iter_mid);
  Container <T> data_2(iter_mid, data.end());

  auto m1 = haveMajority<T>(data_1);

  if (m1.first)
  {
    for (auto i = data_2.begin(); i != data_2.end(); ++i)
    {
      if (*i == m1.second.second) ++(m1.second.first);
    }

    if (m1.second.first > data.size() / 2) return m1;
  }

  auto m2 = haveMajority<T>(data_2);

  if (m2.first)
  {
    for (auto i = data_1.begin(); i != data_1.end(); ++i)
    {
      if (*i == m2.second.second) ++(m2.second.first);
    }

    if (m2.second.first > data.size() / 2) return m2;
  }

  return std::make_pair(result, std::make_pair(0, T()));
}
