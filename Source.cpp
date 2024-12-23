#include <iostream>
#include <random>
#include <vector>
#include <fstream>

using namespace std;

struct stats {
	size_t comparison_count = 0;
	size_t copy_count = 0;
	stats operator+(const stats& other) const {
		stats result;
		result.comparison_count = comparison_count + other.comparison_count;
		result.copy_count = copy_count + other.copy_count;
		return result;
	}
};

vector<int> ordered_vector(int n) {
	vector<int> vector;
	for (int i = 1; i <= n; i++) {
		vector.push_back(i);
	}
	return vector;
}

vector<int> reversed_ordered_vector(int n) {
	vector<int> vector;
	for (int i = n; i > 0; i--) {
		vector.push_back(i);
	}
	return vector;
}

vector<int> random_vector(int n, int seed) {
	vector<int> res(n);
	mt19937 generator(seed); 
	uniform_int_distribution<int> valueDistribution(0, 100);
	for (int i = 0; i < n; i++) {
		res.push_back(valueDistribution(generator));
	}
	return res;
}

void swap(int& a, int& b, stats& stats) {
	int temp = a;
	a = b;
	b = temp;
	stats.copy_count += 3;
}

stats insert_sort(vector<int>& arr) { 
	stats cur_stat;
	size_t n = arr.size();
	for (int i = 1; i < n; ++i) {
		int key = arr[i];
		int j = i - 1;
		while (j >= 0) {
			cur_stat.comparison_count++;
			if (arr[j] > key) {
				arr[j + 1] = arr[j];
				cur_stat.copy_count++;
				--j;
			}
			else {
				break;
			}
		}
		arr[j + 1] = key;
		cur_stat.copy_count++;
	}
	return cur_stat;
}

stats comb_sort(std::vector<int>& arr) {
	stats statistics;
	int n = arr.size();
	int gap = n;
	bool swapped = true;
	const double shrink_factor = 1.3;

	while (gap > 1 || swapped) {
		gap = static_cast<int>(gap/shrink_factor);
		if (gap < 1) gap = 1;
		swapped = false;
		for (int i = 0; i + gap < n; ++i) {
			statistics.comparison_count++;
			if (arr[i] > arr[i + gap]) {
				swap(arr[i], arr[i + gap]);
				statistics.copy_count += 3;
				swapped = true;
			}
		}
	}
	return statistics;
}

void heapify(std::vector<int>& arr, int n, int i, stats& stats) {
	int largest = i;
	int left = 2 * i + 1;
	int right = 2 * i + 2;

	stats.comparison_count++;
	if (left < n && arr[left] > arr[largest])
		largest = left;

	stats.comparison_count++;
	if (right < n && arr[right] > arr[largest])
		largest = right;

	if (largest != i) {
		swap(arr[i], arr[largest]);
		stats.copy_count += 3;
		heapify(arr, n, largest, stats);
	}
}

stats heap_sort(std::vector<int>& arr) {
	stats stats;
	int n = arr.size();

	for (int i = n / 2 - 1; i >= 0; --i)
		heapify(arr, n, i, stats);

	for (int i = n - 1; i > 0; --i) {
		swap(arr[0], arr[i]);
		stats.copy_count += 3;
		heapify(arr, i, 0, stats);
	}
	return stats;
}

void write_to_file(const vector<int>& lengths, const vector<vector<stats>>& stat, const string& name) {
	std::ofstream out_file(name);
	
	for (size_t i = 0; i < stat.size(); ++i) {
		size_t num_runs=1;
		double avg_comparisons_insert = static_cast<double>(stat[i][0].comparison_count) / num_runs;
		double avg_copies_insert = static_cast<double>(stat[i][0].copy_count) / num_runs;

		double avg_comparisons_comb = static_cast<double>(stat[i][1].comparison_count) / num_runs;
		double avg_copies_comb = static_cast<double>(stat[i][1].copy_count) / num_runs;

		double avg_comparisons_heap = static_cast<double>(stat[i][2].comparison_count) / num_runs;
		double avg_copies_heap = static_cast<double>(stat[i][2].copy_count) / num_runs;

		out_file << lengths[i] << "     ";

		out_file << avg_comparisons_insert << " ";
		out_file << avg_copies_insert << "    ";

		out_file << avg_comparisons_comb << " ";
		out_file << avg_copies_comb << "    ";

		out_file << avg_comparisons_heap << " ";
		out_file << avg_copies_heap << " " << "\n";
	}

	out_file.close();
	std::cout << "Written to '" << name << "'.\n";
}


int main() {
	std::vector<int> lengths = {1000, 2000, 3000, 4000, 5000, 10000, 25000, 50000};
	std::vector<std::vector<stats>> sorting_stats;
	int num_runs = 1;

	for (int len : lengths) {
		std::cout << len << "\n";
		vector<stats> alg_stats(3, { 0, 0 });
		
		for (int i = 0; i < num_runs; ++i) {
			auto random_arr = random_vector(len, i);
			vector<int> arr_insert = random_arr;
			vector<int> arr_comb = random_arr;
			vector<int> arr_heap = random_arr;

			alg_stats[0] = alg_stats[0] + insert_sort(arr_insert);
			alg_stats[1] = alg_stats[1] + comb_sort(arr_comb);
			alg_stats[2] = alg_stats[2] + heap_sort(arr_heap);
		}
		for (auto& s : alg_stats) {
			s.comparison_count /= num_runs;
			s.copy_count /= num_runs;
		}
		sorting_stats.push_back(alg_stats);
	}

	write_to_file(lengths, sorting_stats, "sorting_stats1.txt");
	return 0;
}