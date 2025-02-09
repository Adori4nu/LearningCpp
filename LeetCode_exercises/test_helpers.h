#pragma once

#define TEST_OPERATION(container, operation, ...) \
    do { \
        container.operation(__VA_ARGS__); \
        std::cout << "Content of " << #container << ":\n" << container << "\n"; \
    } while (0);