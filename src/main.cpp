#include "raylib.h"
#include <vector>

#define BLOCK_SIZE 50

struct Location{
    float x;
    float y;
};

struct Block{
    struct Location location;
    std::string name;
    struct connections *conn_to;
    struct connections *conn_from;
    float setup_time;
    float propogation_time;
    float processing_time;
    int inventory_space;
    int inventory_status;
};


struct connections{
    int n_conn;
    std::vector<Block *> block;
};


std::vector<Block> blocks;

void add_block(std::string name, Location location, float setup_time, float propogation_time, float processing_time, int inventory_space){
    Block new_block;
    new_block.name = name;
    new_block.location = location;
    new_block.setup_time = setup_time;
    new_block.propogation_time = propogation_time;
    new_block.processing_time = processing_time;
    new_block.inventory_space = inventory_space;
    new_block.inventory_status = 0;
    new_block.conn_to = new connections;
    new_block.conn_from = new connections;
    blocks.push_back(new_block);
}

void make_connection(Block *block1, Block *block2){
    block1->conn_to->block.push_back(block2);
    block1->conn_to->n_conn++;
    block2->conn_from->block.push_back(block1);
    block2->conn_from->n_conn++;
}

void Draw_Blocks(){
    for (auto &block : blocks){
        DrawRectangle(block.location.x-BLOCK_SIZE/2, block.location.y-BLOCK_SIZE/2, BLOCK_SIZE, BLOCK_SIZE, RED);
    }
}

bool in_range(float block_pos, float mouse_pos){
    if (mouse_pos<=(block_pos + BLOCK_SIZE/2) && mouse_pos>=(block_pos - BLOCK_SIZE/2)){
        return true;
    }
    return false;
}

void remove_block(Vector2 mouse_pos){
    for (auto &block : blocks){
        if (in_range(block.location.x, mouse_pos.x) && in_range(block.location.y, mouse_pos.y)){
            DrawRectangle(block.location.x-BLOCK_SIZE/2, block.location.y-BLOCK_SIZE/2, 10, 10, BLACK);
        }
    }
}

void highlight_block(Vector2 mouse_pos){
    for (auto &block : blocks){
        if (in_range(block.location.x, mouse_pos.x) && in_range(block.location.y, mouse_pos.y)){
            DrawRectangle(block.location.x-BLOCK_SIZE/2 -2, block.location.y-BLOCK_SIZE/2 -2, BLOCK_SIZE+4, BLOCK_SIZE+4, BLUE);
        }
    }
}

int main(void){
    const int screenWidth = 800;
    const int screenHeight = 450;
    InitWindow(screenWidth, screenHeight, "Raylib - Basic White Window");
    SetTargetFPS(60);

    while (!WindowShouldClose()){
        Vector2 mouse_pos = GetMousePosition();
        BeginDrawing();
        ClearBackground(WHITE);
        highlight_block(mouse_pos);
        Draw_Blocks();

        if (IsKeyPressed(KEY_A)){
            add_block("Block", {mouse_pos.x, mouse_pos.y}, 1.0f, 0.5f, 0.2f, 10);
        }else if(IsKeyPressed(KEY_X)){
            remove_block(mouse_pos);
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}
