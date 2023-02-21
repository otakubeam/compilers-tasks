# Compilers course: building compilers is fun and easy

This is the repo containing tasks for the compilers course at MIPT.

> Compilers are perceived to be magical artifacts, carefully crafted by the
> wizards, and unfathomable by the mere mortals. Books on compilers are
> better described as wizard-talk: written by and for a clique of
> all-knowing practitioners. Real-life compilers are too complex to serve
> as an educational tool. And the gap between real-life compilers and the
> educational toy compilers is too wide. The novice compiler writer stands
> puzzled facing an impenetrable barrier, “better write an interpreter
> instead.”

В течение курса студенты будут иметь _возможность_ своими руками потрогать,
продумать и реализовать все аспекты современного компилятора. Начиная с
грамматики и парсинга, продолжая системой типов, семантикой языка, модулями,
преобразованием в промежуточное представление и поддержкой рантайма языка.


Курс создавался с опорой на реализациию компилятора языка
[Etude](https://github.com/otakubeam/etude/), а также многих других:

- [Hare](https://harelang.org)
- Rust
- [Cproc](https://github.com/michaelforney/cproc/)
- [Myrrdin](https://eigenstate.org/myrddin/)
- [Chibicc](https://github.com/rui314/chibicc/tree/main/)
- [Tinycc](https://bellard.org/tcc/)
- GHC
- Go
- [Ante](http://antelang.org/)
- and others...

Стоит отметить компиляторы Hare, Cproc, Chibicc, которые имеют очень
доступную кодовую базу

Rust и GHC имеют очень хорошие и понятные wiki и статьи  
[rustc-dev-guide](https://rustc-dev-guide.rust-lang.org/)  
[The GHC Commentary](https://gitlab.haskell.org/ghc/ghc/-/wikis/commentary/#the-ghc-commentary)

Основной книгой в начале курса является
[Crafting Interpreters](https://craftinginterpreters.com/) by Robert Nystrom.

Я также рекомендую слудующие книги:

- Compilers: Principles, Techniques, and Tools — dragonbook
- A Retargetable C Compiler Design and Implementation — lcc book
- The Implementation of Functional Programming Languages — miranda book 
- Basics of Compiler Design (Torben Ægidius Mogensen)
- Introduction to Compilers and Language Design (Prof. Douglas Thain) University of Notre Dame
- [Modern Compiler Implementation in ML](https://annas-archive.org/search?lang=&content=&ext=&sort=&q=modern+compiler+implementation+in+ML) 


В своей идее курс содержит два подхода

Во-первых: дать человеку возможность продумать **всё** самому и погрузиться в
грубокие дебри. Это может быть супер весело, но также очень трудозатратно.

Во-вторых: дописывать смысловые части _уже готовой реализации_. Если сделать
всё правильно, то это тоже может быть достаточно интересно и информативно, и
гораздо быстрее.

## Tasks:
- [Lexer](./tasks/1-lexer.md)
- [Ast and Visitors](./tasks/2-ast-visitors.md)
- [Parser](./tasks/3-parser.md)
- [Symbol Table](./tasks/4-symbol-tables.md)
- [Static Types](./tasks/5-static-types.md)
- [Gen QBE IR](./tasks/6-qbe-ir.md)
- [Structures](./tasks/7-structures.md)
