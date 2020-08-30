#include <bits/stdc++.h>
using namespace std;




// В очередной онлайн игре игроки, как обычно, сражаются с монстрами и набирают опыт. Для того, чтобы сражаться с монстрами, они объединяются в кланы. После победы над монстром, всем участникам клана, победившего его, добавляется одинаковое число единиц опыта. Особенностью этой игры является то, что кланы никогда не распадаются и из клана нельзя выйти. Единственная доступная операция — объединение двух кланов в один.

// Поскольку игроков стало уже много, вам поручили написать систему учета текущего опыта игроков.
// Входные данные

// В первой строке входного файла содержатся числа n и m (1 ≤ n, m ≤ 2·105) — число зарегистрированных игроков и число запросов.

// В следующих m строках содержатся описания запросов. Запросы бывают трех типов:

//     join X Y — объединить кланы, в которые входят игроки X и Y (если они уже в одном клане, то ничего не меняется).
//     add X V — добавить V единиц опыта всем участникам клана, в который входит игрок X (1 ≤ V ≤ 100).
//     get X — вывести текущий опыт игрока X. 

// Изначально у всех игроков 0 опыта и каждый из них состоит в клане, состоящем из него одного.
// Выходные данные

// Для каждого запроса get X выведите текущий опыт игрока X на отдельной строке.




struct node{
    int idx;
    int parent;
    int exp;
    int dept;
    int size;
};


node updateParent(int x, vector<node> &nums){

    if( nums[x].idx == nums[x].parent){
        //we call leader
        return nums[x];
    }

    node me = nums[x];
    node par = nums[me.parent];
    if( par.idx == par.parent ){
        //we call son of leader
        return par;
    }

    int newExp = par.exp + me.exp - me.dept;
    int newDept = par.dept;
    int newPar = par.parent;

    nums[x].exp = newExp;
    nums[x].dept = newDept;
    nums[x].parent = newPar;

    return updateParent(x, nums);

}

void print(vector<node> &nums){
    cout << "-------------------------\n\n";
    for(int step = 0; step < nums.size(); ++step ){
        cout << step + 1 << " " << nums[step].parent + 1 << " " << nums[step].exp << " " << nums[step].dept << "\n";
    }
    cout << "-------------------------\n\n";
}



int main() {

    std::ios_base::sync_with_stdio(false);
	std::cin.tie(NULL);

    int n, m;
    cin >> n >> m;
    vector<node> nums(n);
    for(int i = 0; i < n; ++i){
        nums[i].idx = i;
        nums[i].parent = i;
        nums[i].exp = 0;
        nums[i].dept = 0;
        nums[i].size = 1;
    }

    for(int i = 0; i < m; ++i){
        string s;
        int u, v;
        cin >> s;
        if( s[0] == 'j'){
            cin >> u >> v;
            --u;
            --v;
            int leaderU = updateParent(u, nums).idx;
            int leaderV = updateParent(v, nums).idx;
            if( leaderU == leaderV ){
                continue;
            }
            if( nums[leaderU].size < nums[leaderV].size ){
                
                nums[leaderV].size += nums[leaderU].size;
                nums[leaderU].parent = nums[leaderV].idx;
                nums[leaderU].dept = nums[leaderV].exp;
            }
            else{

                nums[leaderU].size += nums[leaderV].size;
                nums[leaderV].parent = nums[leaderU].idx;
                nums[leaderV].dept = nums[leaderU].exp;
            }
        }

        if( s[0] == 'a' ){
            int value;
            cin >> u >> value;
            --u;
            int leader = updateParent(u, nums).idx;
            nums[leader].exp += value;
        }

        if( s[0] == 'g' ){
            cin >> u;
            --u;
            int leader = updateParent(u, nums).idx;
            int answer = 0;
            if( u == leader ){
                answer = nums[leader].exp;
            }
            else{
                answer = nums[leader].exp + nums[u].exp - nums[u].dept;
            }
            cout << answer << "\n";
        }

        // print(nums);

    }


    return 0;
}
