
# Проект

Вам предлагается выбрать и реализовать какой-то проект.  Это исследовательские
проекты и неотъемлимой их частью является тщательное рассмотрение области. Все
свои находки и идеи записывайте.

**Don't wait — write!** https://www.cis.upenn.edu/~sweirich/icfp-plmw15/slides/peyton-jones.pdf

## 1. Optimizations

- Constant Folding

  Вычилсяем константы при компиляции.        
  https://en.wikipedia.org/wiki/Constant_folding
- Inlining pass

  QBE не совершает *inlining*. К счастью, это можно легко исправить на
  фронтэнде. Реализуйте это.
- Tail Calls Elimination

  Разматываем рекурсию в цикл.
     
## 2. HM + Typeclasses 

Система типов Hindley-Milner позволяет автоматически выводить типы и обобщать
их ( $\forall \alpha$ ). Классы типов позволяют нам накладывать ограничения на
$\alpha$. 

$\tt{compare} :: \forall \alpha. \tt{Ord}\  \alpha \Rightarrow \alpha → \alpha → Bool$ 

https://web.cecs.pdx.edu/~mpj/thih/thih.pdf

## 3. Modules + Serialization

aka *Incremental Compilation*

Если у вас в языке есть модули и дженерики, то хотелось бы, чтобы при изменении
одного модуля все инстанцированные, сгенерированные кусочки кода из других
модулей оставались целы.

https://clang.llvm.org/docs/StandardCPlusPlusModules.html#how-to-produce-a-bmi 

Сериализовать type-inferred деревья в специальный бинарный формат.  
См. myrddin. 

Кэшировать сгенерированный код шаблонных функций.


## 4. Pattern Matching Tree

```
match message {
| .some.ping: ...
| .some msg: ...        <<<----- .some checked again
| .none: ...
```

Самый простой способ делать кодогенерацию pattern-matching-а совершает много
повторных проверок. Конструируйте _decision-tree_, которое позволит выполнять
проверки только один раз. В бонус к этому у вас получится проверка
_exhaustiveness_ и _usefulness_. 

https://julesjacobs.com/notes/patternmatching/patternmatching.pdf
 
## 6. Borrow Checker

Возможно ли реализовать borrow checker своими руками?

https://users.rust-lang.org/t/tutorial-on-implementing-a-borrow-checker-on-a-simplified-language/18791

## 7. Dictionary Passing Style vs VTable

Канонический способ реализации тайпклассов — с помощью словарей (объектов,
содержащих все ссылки на функции). Это позволяет нам генерировать одинаковый
код для полимофных фунций.
 
https://okmij.org/ftp/Computation/typeclass.html

## 8. Address Sanitizer

Инструментируйте все чтения и записи в программе, выделите _shadow region_,
контролируйте состояние памяти.

[AddressSanitizer: A Fast Address Sanity Checker](https://www.usenix.org/system/files/conference/atc12/atc12-final39.pdf)


## 9. LLVM backend

Реализуйте industrial-strength кодогенерацию.

https://llvm.org/docs/tutorial/ + см. код компиляторов

## 10. VM backend (у кого не было Дединского)

Реализуйте свою виртаульную машину и набор инстуркций к ней. Компилируйте ваш
язык в эти инструкции.

Вторая часть книги https://craftinginterpreters.com/contents.html 

## 11. Closures

Реализуйте функции, способные захватывать кусочки своего окружения:


```kotlin
fun makeCounter() {
  var i = 0;
  fun count() {
    i = i + 1;
    print i;
  }

  return count;
}

var counter = makeCounter();
counter(); // "1".
counter(); // "2".
```

Реализуйте escape analysis, который проверяет, что объект closure можно
выделить на стеке. Как  это взаимодействует с другими частями языка?

```
  The venerable master Qc Na was walking with his student, Anton. Hoping
  to prompt the master into a discussion, Anton said "Master, I have
  heard that objects are a very good thing - is this true?" Qc Na looked
  pityingly at his student and replied, "Foolish pupil - objects are
  merely a poor man's closures."

  Chastised, Anton took his leave from his master and returned to his
  cell, intent on studying closures. He carefully read the entire
  "Lambda: The Ultimate..." series of papers and its cousins, and
  implemented a small Scheme interpreter with a closure-based object
  system. He learned much, and looked forward to informing his master of
  his progress.

  On his next walk with Qc Na, Anton attempted to impress his master by
  saying "Master, I have diligently studied the matter, and now
  understand that objects are truly a poor man's closures." Qc Na
  responded by hitting Anton with his stick, saying "When will you
  learn? Closures are a poor man's object." At that moment, Anton became
  enlightened.
```


## 12. Stackless Coroutines 

Нарезайте исполнение в точках _await_ на кусочки, составьте _state-machine_ из
этих кусочков.

## 13. Await runtime

В курсе concurrency мы реализовывали рантайм языка го. Добавьте к нему
синтаксического сахара в виде запуска горутин и передачи сообщений через
каналы.

https://gitlab.com/Lipovsky/await

## 14. LSP

Реализуйте поддерку language-server-protocol;

Требуется принимать запросы и отдавать ответы в формате json

Go-to-definition и отображение ошибок и типов.

https://nickmqb.github.io/2019/11/24/building-a-language-server-for-muon.html


## 15. Garbage collection

Реализуйте сборщик мусора для вашего языка.

- https://craftinginterpreters.com/garbage-collection.html
- https://gchandbook.org/

## 16. Macros

Самые продвинутые системы макросов. Rust + Racket. Какие другие способы
метапрограммирования и compile time codegeneration ещё существуют?

https://serokell.io/blog/introduction-to-template-haskell

## 17. Refinement types

Refinement types: a tutorial https://arxiv.org/pdf/2010.07763.pdf

## 18. Efficient Switching
 
В зависимости от сгруппированности случаев в _switch statement_ мы хотим
генерировать разный код. Если случаи тесно сгруппированы, то это _jump table_.
Если случаи очень отдалены и редки, то имеет смысл пройтись по ним линейно или
бинарным поиском. Реализуйте этот анализ.
