#include "parser.cpp"

int main() {
    // should be correct
    Parser parser1("((41 + 378) * (19 / (54 - 6)))");
    parser1.parse();
    parser1.getResult()->print("");

    // should be correct
    Parser parser2("   (   (  (6/5    )+    12345)-(34      *16)  ) ");
    parser2.parse();
    parser2.getResult()->print("");

    // should fail
    Parser parser3("(((3+)4");
    parser3.parse();
}