#include "sort.h"



int main(int argc, char **argv)
{
	string filename;
	string output;
	size_t chunk_size = 4096;
	bool verify = false;
	size_t nthreads = 2;

	for (int i = 1; i < argc; ++i){
		if (string(argv[i]) == "-i")filename = argv[++i];
		if (string(argv[i]) == "-o")output = argv[++i];
		else if (string(argv[i]) == "-c")chunk_size = (atoi(argv[++i]) << 10) / sizeof(uint32_t);
		else if (string(argv[i]) == "-v")verify = true;
		else if (string(argv[i]) == "-t")nthreads = atoi(argv[++i]);
		else if (string(argv[i]) == "-a")printf("artec!\n");
	}

	if (filename.length() == 0 || output.length() == 0){
		printf("usage: filesort -i <filename> -o <filename> [-c #] [-v] [-t #]\n"
			"-c # initial sorting chunk size in kilobytes (default 8)\n"
			"-t # number of threads to use (default is 2)\n"
			"-v verify output file\n");
		return 1;
	}

	FILE *f = fopen(filename.c_str(), "rb+");
	if (!f){
		printf("fail to open file \n");
		return -1;
	}

	FILE *tmp = tmpfile();
	if (!tmp){
		printf("fail to open temp file \n");
		return -2;
	}

	FILE *out = fopen(output.c_str(), "wb+");
	if (!out){
		printf("fail to open file \n");
		return -1;
	}

	fseek(f, 0, SEEK_END);
	size_t filesize = ftell(f) / sizeof(uint32_t);

	size_t total_written = 0;
	size_t merge_chunk = chunk_size;

	int idx = int(log2(filesize / merge_chunk)) % 2;
	FILE *interim[2] = { tmp, out };

	partial_sort<uint32_t>(f, interim[idx], chunk_size, nthreads);

	do{
		partial_merge<uint32_t>(interim[idx], interim[idx ^ 1], merge_chunk, filesize, chunk_size);
		merge_chunk += merge_chunk;
		idx ^= 1;
	} while (merge_chunk < filesize);


	assert(idx == 1);
	
	fclose(out);
	fclose(tmp);
	fclose(f);

	if (verify){
		FILE *f = fopen(output.c_str(), "rb");
		size_t i = check_sorted<uint32_t>(f);
		fclose(f);
		if (i == UINT32_MAX){
			printf("pass\n");
		}
		else{
			printf("check failed\n");
		}
	}

	return 0;
}