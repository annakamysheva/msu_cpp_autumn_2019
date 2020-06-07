#include <stdio.h>
#include <stdint.h>
#include <assert.h>
#include <vector>
#include <string>
#include <algorithm>
#include <thread>
#include <cmath>
#pragma once 

using namespace std;

template <typename T>
size_t check_sorted(FILE *f)
{
	fseek(f, 0, SEEK_SET);
	T prev = 0;
	size_t i = 0;

	while (!feof(f)){
		T v;
		size_t read = fread(&v, sizeof(v), 1, f);
		if (v < prev)
			return i;
		prev = v;
		i++;
	}
	return -1;
}

template <typename T>
void partial_sort(FILE *f, FILE *tmp, size_t chunk_size, size_t nthreads)
{
	T *buf = new T[nthreads*chunk_size];
	size_t read = 0;

	fseek(f, 0, SEEK_SET);
	do{
		thread last;
		read = fread(buf, sizeof(T), nthreads*chunk_size, f);
		if (read == 0)break;

		size_t n = min(nthreads, (read + chunk_size - 1) / chunk_size);
		
		for (size_t i = 0; i < n; ++i){

			thread t([&tmp](T *buf, int size, thread prev)
			{
				sort(buf, buf + size);

				
				if (prev.joinable())prev.join();

				fwrite(buf, sizeof(T), size, tmp);
			}, buf + i*chunk_size, min(chunk_size, read - i*chunk_size), move(last));
			last = move(t);
		}
		if (last.joinable())last.join();
	} while (read > 0);

	delete[] buf;
}


template<typename readIt, typename writeIt>
void merge(readIt &begin0, readIt end0, readIt &begin1, readIt end1, writeIt &begin, writeIt end)
{
	while (begin != end && begin0 != end0 && begin1 != end1){
		while (begin != end && begin0 != end0 && *begin0 <  *begin1)
			*begin++ = *begin0++;
		while (begin != end && begin1 != end1 && *begin0 >= *begin1)
			*begin++ = *begin1++;
	}
	while (begin != end && begin0 != end0)
		*begin++ = *begin0++;
	while (begin != end && begin1 != end1)
		*begin++ = *begin1++;
}

template<typename T>
void overlapped_copy(T *write, const T *begin, const T *end)
{
	if (write == begin)return;

	while (begin != end)*write++ = *begin++;
}

template <typename T>
void partial_merge(FILE *in, FILE *out, size_t chunk_size, size_t file_size, size_t merge_size)
{
	assert(chunk_size < file_size);
	assert(merge_size <= chunk_size);

	T *mergebuf = new T[merge_size];
	T *partbuf0 = new T[merge_size];
	T *partbuf1 = new T[merge_size];

	fseek(out, 0, SEEK_SET);

	
	for (size_t i = 0; i < file_size; i += 2 * chunk_size){
		
		size_t offset0 = 0;
		size_t offset1 = 0;

		
		size_t bufsize0 = 0;
		size_t bufsize1 = 0;

		
		size_t size0 = min(merge_size, file_size - i);
		size_t size1 = min(merge_size, file_size - i - chunk_size);

		do{
			if (size0 > 0){
				fseek(in, (i + offset0)*sizeof(T), SEEK_SET);
				size_t read = fread(partbuf0 + bufsize0, sizeof(T), size0, in);
				bufsize0 += read;
				offset0 += read;
			}
			
			if (size1 > 0){
				fseek(in, (i + chunk_size + offset1)*sizeof(T), SEEK_SET);
				size_t read = fread(partbuf1 + bufsize1, sizeof(T), size1, in);
				bufsize1 += read;
				offset1 += read;
			}

			const T *start0 = partbuf0;
			const T *start1 = partbuf1;
			T *start = mergebuf;

			merge(start0, start0 + bufsize0, start1, start1 + bufsize1, start, mergebuf + merge_size);
			
			fwrite(mergebuf, sizeof(T), start - mergebuf, out);

			overlapped_copy(partbuf0, start0, partbuf0 + bufsize0);
			overlapped_copy(partbuf1, start1, partbuf1 + bufsize1);

			bufsize0 -= size_t(start0 - partbuf0);
			bufsize1 -= size_t(start1 - partbuf1);

			size0 = min(merge_size - bufsize0, chunk_size - offset0);
			size1 = min(merge_size - bufsize1, chunk_size - offset1);
		} while (bufsize0 + bufsize1 > 0);
	}

	delete[] mergebuf;
	delete[] partbuf0;
	delete[] partbuf1;
}