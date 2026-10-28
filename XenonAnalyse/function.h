#pragma once

#include <cstddef>
#include <unordered_map>
#include <vector>

#ifdef _DEBUG
#define DEBUG(X) X
#else
#define DEBUG(X)
#endif

struct Function
{
    struct Block
    {
        size_t base{};
        size_t size{};
        size_t projectedSize{ static_cast<size_t>(-1) }; // scratch
        DEBUG(size_t parent{});

        Block() 
        {
        }

        Block(size_t base, size_t size)
            : base(base), size(size) 
        {
        }

        Block(size_t base, size_t size, size_t projectedSize) 
            : base(base), size(size), projectedSize(projectedSize)
        {
        }
    };

    size_t base{};
    size_t size{};
    std::vector<Block> blocks{};

    Function()
    {
    }

    Function(size_t base, size_t size)
        : base(base), size(size)
    {
    }
    
    size_t SearchBlock(size_t address) const;

    // switchTables maps the address where a jump table sequence starts to the
    // table's labels. With it, functions that have no .pdata entry are no longer
    // cut short at the bctr of a jump table.
    static Function Analyze(const void* code, size_t size, size_t base,
        const std::unordered_map<size_t, std::vector<size_t>>* switchTables = nullptr);
};
