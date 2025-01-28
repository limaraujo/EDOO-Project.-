#include "Parser.h"

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(nullptr);
    std::cout.tie(nullptr);

    int cases; std::cin >> cases;
    std::cin.ignore();

    for (int i = 1; i <= cases; i++) {
        std::string input; 
        std::getline(std::cin, input);

        try {
            if (input.empty()) {
                throw std::invalid_argument("Empty expression.");
            }

            Lexer lexer(input); 
            Parser parser(lexer);

            auto result = parser.evaluate();
            if (std::holds_alternative<int>(result)) {
                std::cout << std::get<int>(result) << '\n';
            } else if (std::holds_alternative<bool>(result)) {
                std::cout << (std::get<bool>(result) ? "true" : "false") << '\n';
            }

        } catch (std::exception&) {
            std::cout << "error" << '\n';
        }
    }
    return 0;
}