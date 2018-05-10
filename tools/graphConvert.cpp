#include<iostream>
#include<fstream>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <malloc.h>
#include <errno.h>
#include <assert.h>
#include <string.h>

#include <string>
#include <vector>
#include <thread>

#include "core/constants.hpp"
#include "core/type.hpp"
#include "core/filesystem.hpp"
#include "core/queue.hpp"
#include "core/partition.hpp"
#include "core/time.hpp"
#include "core/atomic.hpp"



int main(int argc, char ** argv) {
	int opt;
	std::string input = "";
	std::string output = "";
	VertexId vertices = -1;
	int partitions = -1;
	int edge_type = 0;
	while ((opt = getopt(argc, argv, "i:o:e:p:")) != -1) {
		switch (opt) {
		case 'i':
			input = optarg;
			break;
		case 'o':
			output = optarg;
			break;
		case 'e':
			edge_type = atoi(optarg);
			break;
		case 'p':
			partitions = atoi(optarg);
			break;
		}
	}
	if (input=="" || output=="") {
		fprintf(stderr, "usage: %s -i [input path] -o [output path] -e [edge type: 0=unweighted, 1=weighted]\n", argv[0]);
		exit(-1);
	}

  /** Convert binary edge-list to edge-list **/

  std::ofstream outStream(output);
  for(int i = 0; i < partitions; i++){
    for(int j = 0; j < partitions; j++){
      std::string blockName = input + "/block-" + std::to_string(i) + "-" + std::to_string(j);
      std::cout << blockName << "\n";
      std::ifstream inStream(blockName, std::ifstream::ate |  std::ios::binary);
      if(inStream.is_open()){
        size_t filesize = inStream.tellg();
        inStream.seekg(0);
        std::cout << blockName << " : " << filesize << "\n";
        std::cout << file_size(blockName) << "\n";
        if(edge_type == 0){
          int edge_unit = sizeof(VertexId) * 2;
          size_t edges = filesize/edge_unit;
          std::cout << "Number of Edges : " << edges << "\n";
          std::vector<VertexId> edgesVec(edges*2);
          inStream.read(reinterpret_cast<char*>(edgesVec.data()), sizeof(VertexId)*filesize);
          for(auto k = 0; k < edgesVec.size(); k+=2){
            outStream << edgesVec[k] << " " << edgesVec[k+1] << "\n";
          }
        } else {
          /** Not finished yet WIP**/
          int edge_unit = sizeof(VertexId) * 2;
          size_t edges = filesize/edge_unit;
        }
      }
    }
  }

  return 0;
}

