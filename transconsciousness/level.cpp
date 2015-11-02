#include "level.h"

Level::Level() : p_alloc(nullptr)//, p_init(nullptr), p_update(nullptr), p_dealloc(nullptr)
{
}

//Level::Level(level_function p_alloc, level_function p_init, level_function p_update, level_function p_dealloc) : p_alloc(p_alloc), p_init(p_init), p_update(p_update), p_dealloc(p_dealloc)
//{
//}

Level::Level(level_function p_alloc) : p_alloc(p_alloc)
{
}
