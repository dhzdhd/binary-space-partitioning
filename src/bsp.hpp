#pragma once

#include "raylib.h"

struct Node
{
    Node *left;
    Node *right;
    Vector2 data;
};

void addNode(Node *left, Node *right, Vector2 data);
void deleteNode(Node *node);
