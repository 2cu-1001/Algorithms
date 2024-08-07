#include <bits/stdc++.h>
using namespace std;
typedef struct Player {
    int x, y, lv, atk, def, cur_hp, max_hp, 
        exp, weapon, armour, orn_cnt, orn[7];
    string killed_by;
}Player;
typedef struct Mob {
    int x, y, atk, def, cur_hp, max_hp, exp;
    string name;
}Mob;
typedef struct Box {
    int x, y, num;
    string item_type, orn_type;
}Box;

int N, M, mob_cnt, box_cnt, turn_cnt, arr[110][110], is_boss_down,
is_end, is_dead, mob_idx[110][110], box_idx[110][110];
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };
pair<int, int> startpos;
string command;
Player player;
vector<Mob> mobs;
vector<Box> boxs;

void lv_up()
{
    player.exp = 0; player.lv++;
    player.max_hp = player.cur_hp = player.max_hp + 5;
    player.atk += 2; player.def += 2;
}
void combat(int nx, int ny, int is_boss)
{
    Mob* mob = &mobs[mob_idx[nx][ny]];
    if (player.orn[5] && is_boss) player.cur_hp = player.max_hp;
    bool is_win = false;
    for (int i = 1; player.cur_hp > 0 && mob->cur_hp > 0; i++)
    {
        if (i == 1 && player.orn[2] && player.orn[4])
            mob->cur_hp -= max(3 * (player.atk + player.weapon) - mob->def, 1);
        else if (i == 1 && player.orn[2])
            mob->cur_hp -= max(2 * (player.atk + player.weapon) - mob->def, 1);
        else mob->cur_hp -= max((player.atk + player.weapon) - mob->def, 1);

        if (mob->cur_hp <= 0) {
            is_win = true;
            break;
        }
        else {
            if (i == 1 && player.orn[5] && is_boss) continue;
            player.cur_hp -= max(mob->atk - (player.def + player.armour), 1);
        }
    }

    if (is_win)
    {
        int gain_exp = mob->exp;
        if (player.orn[0])
            player.cur_hp = min(player.max_hp, player.cur_hp + 3);
        if (player.orn[3]) gain_exp = (floor)(mob->exp * 1.2);
        player.exp += gain_exp;
        if (player.exp >= player.lv * 5) lv_up();
        if (is_boss) {
            is_boss_down = true;
            is_end = 1;
        }
        arr[nx][ny] = '.';
        player.x = nx; player.y = ny;
    }
    else if (!is_win)
    {
        if (player.orn[1]) {
            player.cur_hp = player.max_hp;
            player.x = startpos.first; 
            player.y = startpos.second;
            mob->cur_hp = mob->max_hp;
            player.orn[1] = 0;
            player.orn_cnt--;
        }
        else {
            is_end = 1; is_dead = 1;
            player.killed_by = mob->name;
        }     
    }
}
void open_box(int nx, int ny)
{
    Box* box = &boxs[box_idx[nx][ny]];
    if (box->item_type == "W") {
        player.weapon = box->num;
    }
    else if (box->item_type == "A") {
        player.armour = box->num;
    }
    else
    {
        if (player.orn_cnt < 4)
        {
            if (box->orn_type == "HR") {
                if (!player.orn[0]) {
                    player.orn[0] = 1;
                    player.orn_cnt++;
                }
            }
            else if (box->orn_type == "RE") {
                if (!player.orn[1]) {
                    player.orn[1] = 1;
                    player.orn_cnt++;
                }
            }
            else if (box->orn_type == "CO") {
                if (!player.orn[2]) {
                    player.orn[2] = 1;
                    player.orn_cnt++;
                }
            }
            else if (box->orn_type == "EX") {
                if (!player.orn[3]) {
                    player.orn[3] = 1;
                    player.orn_cnt++;
                }
            }
            else if (box->orn_type == "DX") {
                if (!player.orn[4]) {
                    player.orn[4] = 1;
                    player.orn_cnt++;
                }
            }
            else if (box->orn_type == "HU") {
                if (!player.orn[5]) {
                    player.orn[5] = 1;
                    player.orn_cnt++;
                }
            }
            else if (box->orn_type == "CU") {
                if (!player.orn[6]) {
                    player.orn[6] = 1;
                    player.orn_cnt++;
                }
            }
        } 
    }
    arr[nx][ny] = '.';
    player.x = nx; player.y = ny;
}
void step_on_trap(int nx, int ny)
{
    if (player.orn[4]) player.cur_hp -= 1;
    else player.cur_hp -= 5;

    if (player.cur_hp <= 0) {
        if (player.orn[1]) {
            player.cur_hp = player.max_hp;
            player.x = startpos.first;
            player.y = startpos.second;
            player.orn[1] = 0;
            player.orn_cnt--;
        }
        else {
            is_end = 1; is_dead = 1;
            player.killed_by = "SPIKE TRAP";
        }   
    }
    else {
        player.x = nx; player.y = ny;
    }
}
void init()
{
    player.atk = player.def = 2;
    player.cur_hp = player.max_hp = 20;
    player.lv = 1; player.exp = 0;
    player.weapon = player.armour = 0;
    player.orn_cnt = 0;
    for (int i = 0; i <= 6; i++) player.orn[i] = 0;
}
void process()
{
    for (int i = 0; i < command.size(); i++)
    {
        if (is_end || is_boss_down || is_dead) break;

        char cur_dir = command[i];
        int nx, ny, cx, cy;
        cx = player.x; cy = player.y;
        if (cur_dir == 'U') {
            nx = dx[0] + player.x;
            ny = dy[0] + player.y;
        }
        else if (cur_dir == 'R') {
            nx = dx[1] + player.x;
            ny = dy[1] + player.y;
        }
        else if (cur_dir == 'D') {
            nx = dx[2] + player.x;
            ny = dy[2] + player.y;
        }
        else if (cur_dir == 'L') {
            nx = dx[3] + player.x;
            ny = dy[3] + player.y;
        }

        if (nx < 1 || nx > N || ny < 1 || ny > M ||
            arr[nx][ny] == '#') {
            if (arr[cx][cy] == '^') step_on_trap(cx, cy);
            turn_cnt++; continue;
        }

        if (arr[nx][ny] == '.') {
            player.x = nx; player.y = ny;
        }
        else if (arr[nx][ny] == 'B') open_box(nx, ny);
        else if (arr[nx][ny] == '^') step_on_trap(nx, ny);
        else if (arr[nx][ny] == '&' || arr[nx][ny] == 'M')
            combat(nx, ny, (arr[nx][ny] == 'M') ? 1 : 0);
        turn_cnt++;
    }
}
void input()
{
    cin >> N >> M;
    for (int i = 1; i <= N; i++) {
        string s; cin >> s;
        for (int j = 1; j <= M; j++)
        {
            arr[i][j] = s[j - 1];
            if (arr[i][j] == '@') {
                player.x = i; player.y = j;
                startpos = { i, j };
                arr[i][j] = '.';
            }
            else if (arr[i][j] == '&' || arr[i][j] == 'M')
                mob_cnt++;
            else if (arr[i][j] == 'B') box_cnt++;
        }
    }
    cin >> command;
    for (int i = 0; i < mob_cnt; i++)
    {
        Mob mob;
        cin >> mob.x >> mob.y >> mob.name >> mob.atk
            >> mob.def >> mob.max_hp >> mob.exp;
        mob.cur_hp = mob.max_hp;
        mobs.push_back(mob);
        mob_idx[mob.x][mob.y] = i;
    }
    for (int i = 0; i < box_cnt; i++)
    {
        Box box; string s;
        cin >> box.x >> box.y >> s;
        if (s == "W" || s == "A") cin >> box.num;
        else cin >> box.orn_type;
        box.item_type = s;
        boxs.push_back(box);
        box_idx[box.x][box.y] = i;
    }
}
void output()
{
    for (int i = 1; i <= N; i++) {
        for (int j = 1; j <= M; j++) {
            if (player.x == i && player.y == j && !is_dead) cout << '@';
            else cout << (char)arr[i][j];
        }
        cout << "\n";
    }
    cout << "Passed Turns : " << turn_cnt << "\n";
    cout << "LV : " << player.lv << "\n";
    cout << "HP : " << ((player.cur_hp > 0) ? player.cur_hp : 0) << "/" << player.max_hp << "\n";
    cout << "ATT : " << player.atk << "+" << player.weapon << "\n";
    cout << "DEF : " << player.def << "+" << player.armour << "\n";
    cout << "EXP : " << player.exp << "/" << player.lv * 5 << "\n";
    if (is_boss_down) cout << "YOU WIN!\n";
    else if (is_dead) cout << "YOU HAVE BEEN KILLED BY " << player.killed_by << "..\n";
    else cout << "Press any key to continue.\n";
}
int main()
{
    ios_base::sync_with_stdio(0);
    cin.tie(0); cout.tie(0);
    input();
    init();
    process();
    output();
}