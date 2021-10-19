#include <iostream>
#include <vector>
#include <algorithm>

using int_vector = std::vector<int>;
using index_pair = std::pair<unsigned, unsigned>;

index_pair split(int_vector& a, int p);
int select(int_vector& a, size_t random);

int main()
{
  try
  {
    std::cout << "Enter the size of the array\n";

    size_t size;
    std::cin >> size;
    if (!std::cin.good())
    {
      throw std::invalid_argument("Incorrect array size!");
    }

    int_vector a(size);

    std::cout << "Enter values:\n";
    for (auto i = 0u; i < size; ++i)
    {
      int temp;
      std::cin >> temp;

      if (std::cin.good())
      {
        a[i] = temp;
      }
      else if (std::cin.fail() && !std::cin.eof())
      {
        std::cin.clear();
        std::cin.ignore(std::numeric_limits<std::streamsize>::max(), ' ');
        --i;
      }
      else if (std::cin.bad())
      {
        throw std::invalid_argument("Critical error of input stream!");
      }
    }

    std::cout << "Enter an element of array:\n";
    int elem;
    std::cin >> elem;
    if (!std::cin.good())
    {
      throw std::invalid_argument("Incorrect elem of array!");
    }

    int_vector b(a);
    index_pair indexes = split(b, elem);

    std::cout << "\nArray: ";
    std::copy(b.begin(), b.end(), std::ostream_iterator<int>(std::cout, " "));
    std::cout << "\nIndexes of " << elem << " is " << indexes.first << ' ' << indexes.second;
    std::cout << "\nMedian: " << select(a, size/2) << std::endl;

  }
  catch (const std::invalid_argument& ex)
  {
    std::cerr << '\n' << ex.what() << '\n';
    return 1;
  }

  return 0;
}

int select(int_vector& a, size_t k)
{
  if (a.size() == 1u) return a.at(0);

  srand(time(NULL));
  size_t random = static_cast<size_t>(rand() % a.size());

  int p = a.at(random);

  index_pair p_index = split(a, p);

  if (k < p_index.first)
  {
    int_vector left(a.begin(), a.begin() + p_index.first);
    return select(left, k);
  }
  else if (k <= p_index.second) return p;
  else
  {
    int_vector right(a.begin() + p_index.second + 1, a.end());
    return select(right, k - p_index.second - 1);
  }
}

index_pair split(int_vector& a, int p)
{
  auto size = a.size();
  for (auto i = 0u; i < size; ++i)
  {

    if (a.at(i) < p)
    {
      a.insert(a.begin(), std::remove_reference_t<int>(a.at(i)));
      a.erase(a.begin() + i + 1);
    }
    else if (a.at(i) > p)
    {
      a.push_back(std::remove_reference_t<int>(a.at(i)));
      a.erase(a.begin() + i);
    }
  }

  auto iters = std::equal_range(a.begin(), a.end(), p);

  return std::make_pair(
    std::distance(a.begin(), iters.first),
    std::distance(a.begin(), iters.second) - 1);
}
