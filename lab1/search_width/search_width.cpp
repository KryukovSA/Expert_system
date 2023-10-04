#include "search_widtn.h"
#include <iostream>

search_width::search_width(vector<Edge> edges_, Node start_node_, Node target_node_, vector<Node> all_nodes_) {
    all_nodes = all_nodes_;
    edges = edges_;
    start_node = start_node_;
    target_node = target_node_;

    open_nodes.push(start_node);
    start_node.flag = 1;


}

int search_width::sample_search( Node current_node_) {
    int descendant = 0;//дял подсчета числа потомков
    vector<Edge> tmp_edges = edges;
    int counter_edges = 0;
    while (!tmp_edges.empty()) {
        
        if (current_node_.vert_num == target_node.vert_num) {
            flag_solve = 0;
            return 0; 
        }

        if (tmp_edges.front().start_node == current_node_.vert_num && tmp_edges.front().mark == not_passed) {
            tmp_edges.front().mark = passed;
            edges[counter_edges].mark = passed;

            if (tmp_edges.front().end_node == target_node.vert_num) {
                flag_solve = 0;
                cout << "конечная вершина ребра (" << tmp_edges.front().start_node << ", " <<
                    tmp_edges.front().end_node << " ) равна целевой" << endl;
                return 0;
            }


            if(!find_vert(tmp_edges.front().end_node))//ее пока нет в очереди
                open_nodes.push(tmp_edges.front().end_node);
            descendant++;
        }
        counter_edges++;
        tmp_edges.erase(tmp_edges.begin());

    }
    return descendant;
}

void search_width::organization_search() {
    while (flag_solve && flag_not_solve) {
        Node current_node;
        cout << "текущая очередь" << endl;
        show_queue();

        if(!open_nodes.empty())
            current_node = open_nodes.front();
        else {
            cout << "нет решения" << endl;
            return;
        }
        int j = sample_search(current_node); //число потомков
        close_nodes.push_back(current_node);
        open_nodes.pop();
        if (flag_solve == 0) {
            cout << "нашли решение" << endl;
            return;
        }
        if (j == 0 && open_nodes.empty()) { //мб && flag_not_solve == 0
            cout << "нет решения" << endl;
            return;
        }
    }
}

void search_width::show_queue() {
    queue<Node> copy_queue = open_nodes;
    while (!copy_queue.empty()) {
        Node frontElement = copy_queue.front(); // Получаем первый элемент в копии очереди
        std::cout << frontElement.vert_num << " "; // Выводим его
        copy_queue.pop(); // Извлекаем первый элемент из копии очереди
    }
    cout << endl;
}

bool search_width::find_vert(int node_num) {
    for (int i = 0; i < all_nodes.size(); i++) {
        if (all_nodes[i].vert_num == node_num && all_nodes[i].flag == 0) {
            all_nodes[i].flag = 1;//так как мы ее в очередь добавим
            return false;
        }
    }
    return true;
}