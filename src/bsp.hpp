#pragma once

#include "raylib.h"
#include "sim.hpp"

struct Node
{
    Node *left;
    Node *right;
    Rect data;
};

void addNode(Node *left, Node *right, Rect data);
void deleteNode(Node *node);
