#pragma once

#include <vector>
#include "Edge.h"
#include "Node.h"
#include <queue>


//обычный поиск в ширину в простр состояний
using namespace std;

class search_width
{
private:
	vector<Node> all_nodes;
	vector<Edge> edges;
	queue<Node> open_nodes;
	vector<Node> close_nodes;
	Node start_node;
	Node target_node;
	bool flag_solve = 1;//пока не решили
	bool flag_not_solve = 1; // флаг нет решения

public:
	/*~search_width();*/
	int sample_search(Node current_node_);
	void organization_search();
	void show_queue();
	bool find_vert(int);

	search_width(vector<Edge> edges_, Node start_node_, Node target_node_, vector<Node> close_nodes_);

};