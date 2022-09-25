## Первая стадия: лексер

0. Изучите структуру проекта, что конкретно собирается, что с чем линкуется, какие директории есть

1. Установитe библиотеку для форматирования `fmt` 

2. Установитe библиотеку для тестрирования `catch2`

   Если будут проблемы с установкой, можно сделать докер-контейнер. Пишите!

3. `cmake -B build` 

   Команда выполняется из корня проекта
   
   Далее следует настроить **автодополнение**. Напишите, если с этом возникнут
   сложности. Автодополнение __должно быть__.

4. `make -j8` 
   
   Команда выполняется из директории `build` 

5. `./tests/test` 

   - Для запуска тестов
   - Из директории build 

6. `./app/repl`
   
   - Для интерактива: вы набираете текст и смотрите, какие типы токенов
     разпознаёт лекскер

## Задание

1. Дописать недостающие функции, чтобы [Lexer::GetNextToken()](https://git.sr.ht/~orazov_ae/compilers-tasks/tree/master/item/src/lex/lexer.cpp#L12) заработал (проходил тесты)

   В частности:

   - MatchOperators
   - MatchLiterls
   - MatchNumericLiteral
   - MatchStringLiteral
   - MatchWords (keywords)
   - IdentTable::Lookup

     [Здесь](https://git.sr.ht/~orazov_ae/compilers-tasks/tree/master/item/src/lex/ident_table.hpp#L16)

Разумеется, это только один из способов. Вы можете выразить `GetNextToken`
через другие функции. Также можете изменять значения ключевых слов и типы
токенов по желанию.

2. Сделайте так, чтобы Scanner записывал все встретившиеся ему символы в
   буффер. Это пригодится для обработки ошибок: помимо локации мы сможем
   указать прямо на строчку кода, где допущена ошибка.

   Тогда имеет смысл, чтобы `struct Location` указывала на свою позицию в этом
   буфере.

### Examples

Изучите чужие реализации: 

- [Crafting Interpreters Book](https://craftinginterpreters.com/scanning.html)

- [Лексер языка Hare](https://git.sr.ht/~sircmpwn/harec/tree/master/item/src/lex.c)

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

- Вероятно, самый продвинутый в мире JIT компилятор v8 [scanner](https://github.com/v8/v8/blob/main/src/parsing/scanner.h)

- Clang [lexer](https://github.com/llvm/llvm-project/blob/main/clang/lib/Lex/Lexer.cpp)

Последние скорее для устрашения =). Лучше напишите очень простой код.
