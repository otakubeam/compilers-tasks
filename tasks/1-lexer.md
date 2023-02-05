# 1. Лексер

Непосредственно перед парсингом исходный текст программы разбивается на
отдельные лексемы (токены).

С каждым токеном ассоциирована его позиция в тексте программы и, возможно,
семантическая информация.  Например,

`fun main = 0;`
  
```
  fun  => TK_FUN         (no semantic info)  loc = {line: 1, col: 1}
  main => TK_IDENTIFIER  ("main")            loc = {line: 1, col: 5}
   =   => TK_ASSIGN      (no semantic info)  loc = {line: 1, col: 10}
   0   => TK_NUM         (0)                 loc = {line: 1, col: 12}
   ;   => TK_SEMICOLON   (no semantic info)  loc = {line: 1, col: 13}
```

В итоге лексер преобразует поток символов в поток токенов (более выскоий
уровень абстракции), изолируя парсер от работы с символами.

## Задание

Вам предлагается разработать лексер для языка Étude.

1. Прочитайте [Crafting Interpreters: Scanning](https://craftinginterpreters.com/scanning.html).
2. Заполните `enum TokenType` всеми возможными типами токенов.
3. Создайте структуру `Token`, содержащую
   -  позицию токена в тексте, 
   -  семантическую информацю о токене,
   -  его тип
4. Реализуйте `IdentTable` — отображение `string_view → TokenType`
5. Реализуйте `Scanner`
   - **Считывание данных** в буффер
   - **Отслеживание позиции** в тексте
   - Просмотр **текущего символа**
6. Восполните пробелы в реализации класса `Lexer`
   - Научите лексер обрабатывать **числа**
   - Научите лексре распознавать **операторы** языка
   - Научите лексер распознавать **строки**
   - Пропускайте **комментарии**
   - Реализуйте метод `Matches`

Цель — создать простой фреймворк для работы с текском, позволяющий без труда 
добавлять ключевые слова и операторы в дальнейшем (сейчас список намеренно
небольшой).
    
## Реализация

В директории `src` лежит заготовка. Компиляция происходит так:

```
cmake -B build
cd build && make -j8
```

Протестируйте вашу реализацию. Примеры тестов написаны в директории `tests`.

Класс `Scanner` позволяет отделить механику чтения из потока и обработки
позиции в тексте от непосредственной работы с символами. Для простоты вам
предлагается считывать файл в буффер целиком.

Для ссылки на позиции в тексте используйте `std::string_view`

Для поддержания семантической информации о токене используйте `std::variant`
или C—style `union`



## Appendix A. Token Types

  | Token Type                 | Source                     |
  | -----------                | -------                    |
  | `NUMBER`                   | `(0..9)+`                  |
  | `STRING`                   | `" <any char except">* "`  |
  | `IDENTIFIER`               | `ALPHA ( ALPHA..DIGIT )*`  |
  | `TRUE`                     | `true`                     |
  | `FALSE`                    | `false`                    |
  | `PLUS`                     | `+`                        |
  | `MINUS`                    | `-`                        |
  | `STAR`                     | `*`                        |
  | `DIV`                      | `/`                        |
  | `ASSIGN`                   | `=`                        |
  | `EQUALS`                   | `==`                       |
  | `NOT_EQ`                   | `!=`                       |
  | `NOT`                      | `!`                        |
  | `LT`                       | `<`                        |
  | `GT`                       | `>`                        |
  | `LEFT_PAREN`               | `(`                        |
  | `RIGHT_PAREN`              | `)`                        |
  | `LEFT_CBRACE`              | `{`                        |
  | `RIGHT_CBRACE`             | `}`                        |
  | `COMMA`                    | `,`                        |
  | `COLON`                    | `;`                        |
  | `FUN`                      | `fun`                      |
  | `VAR`                      | `var`                      |
  | `IF`                       | `if`                       |
  | `THEN`                     | `then`                     |
  | `ELSE`                     | `else`                     |
  | `RETURN`                   | `return`                   |
  | `TOKEN_EOF`                | EOF                        |

### Examples

Изучите чужие реализации: 

- [Hare](https://git.sr.ht/~sircmpwn/harec/tree/master/item/src/lex.c)
- Язык Go
  - [Token](https://go.dev/src/go/token/token.go)
  - [Scanner](https://go.dev/src/go/scanner/scanner.go)
- Компилятор языка C `cproc` [scan](https://github.com/michaelforney/cproc/blob/master/scan.c)
- Документация компилятора rustc [Lexing and Parsing](https://rustc-dev-guide.rust-lang.org/the-parser.html)

  > rustc_lexer crate is responsible for breaking a &str into chunks
  > constituting tokens. Although it is popular to implement lexers as
  > generated finite state machines, the lexer in rustc_lexer is
  > hand-written.
  
  - [Token](https://doc.rust-lang.org/nightly/nightly-rustc/src/rustc_lexer/lib.rs.html#41-44)

- V8 [scanner.h](https://github.com/v8/v8/blob/main/src/parsing/scanner.h)
- Clang [Lexer.cpp](https://github.com/llvm/llvm-project/blob/main/clang/lib/Lex/Lexer.cpp)
