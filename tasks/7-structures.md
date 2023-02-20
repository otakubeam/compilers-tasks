  
#  7. Structures

Давайте добавим ***структуры*** в наш язык. Одним **маленьким шажком** для
компилятора мы значительно **повысим выразительность** нашего языка.

Для этого нам *снова придётся пройти все этапы компилятора*, но сначала
обсудим, что мы от них ожидаем.

###  Объявление структуры

В *Étude* структуры не содержат в себе методов. Тип `struct` — это просто
хранилище для данных.

```etude
type NewType = struct {
    field1: Int,
    field2: Bool,
    field3: *NewType,
};
```

### Использование в качестве аргумента

Всё функции являются *свободными*. Они работают над данными, которые
пользователь определяет с помощью объявления  типа.

```etude
of NewType -> Int
fun get_field struct_ = struct_.field1;
```

### Конструирование литерала

Синтаксис `{ .field = <value> }` используется для конструирования структуры.  
Также доступен *short-hand* синтаксис `.field <value>`, но он обычно
используется для типов суммы.

```etude
of Int -> *String -> ()
fun main argc argv = {

    get_field({.field1 = 123, 
                .field2 = true});

    0
};
```

### Создание переменной

Если вы хотите создать переменную, то **явно указывайте её тип**.

```etude
of Int -> *String -> ()
fun main argc argv = {

    of NewType
    var str = { .field1 = 123, 
                .field2 = true };

    0
};
```

## Стадии компиляции

### Лексер

Нужно добавить новые типы токенов:

  | Token Type                 | Source                     |
  | -----------                | -------                    |
  | `TYPE`                     | `type`                     |
  | `TY_STRUCT`                | `struct`                   |
  | `COLON`                    | `:`                        |
  
### AST + Parser 

Нужно добавить новые вершины **AST** и научиться их *парсить*.

Новые вершины: *TypeDeclaration, FieldAccess, StructConstruction*.

```diff
*** grammar-v2.txt	2023-02-20 11:56:10.785563149 +0300
--- grammar-v3.txt	2023-02-20 11:56:04.075536574 +0300
***************
*** 4,7 ****
--- 4,8 ----
  <declaration> ::= <function-definition>
                  | <variable-declaration>
+                 | <type-declaration>
  
  
***************
*** 18,21 ****
--- 19,25 ----
  
  
+ <type-declaration> ::= type <identifier> = <type-expression> ;
+ 
+ 
  
  
***************
*** 56,63 ****
--- 60,69 ----
  
  <postfix-expression> ::= <primary-expression>
+                        | <postfix-expression> . <identifier>
                         | <postfix-expression> ( {<expression>,}* )
  
  <primary-expression> ::= <identifier>
                         | <constant>
+                        | <structure-literal>
                         | <keyword-expression>
                         | <compound-expression>
***************
*** 77,80 ****
--- 83,90 ----
  
  
+ <structure-literal> ::= .<identifier> <expression>
+                       | { {.<identifier> = <expression>}+ }
+ 
+ 
  
  
***************
*** 86,92 ****
--- 96,106 ----
  <constructor-types> ::= 
                        | * <constructor-types> 
+                       | struct { <typed-field>* } 
                        | <primitive-types>
+                       | <identifier>

  
  
+     <typed-field> ::= <identifier> : <type-expression>
+ 
+ 
  <primitive-types> ::= Int | Bool | String | Char | Unit | ()  
```

###  Построение таблицы символов

Нужно добавить *новый класс символов* в вашей таблице — `Type`

###  Проверка типов

У вас могут возникнуть проблемы с проверкой типа выражения `{ .field1 = 123 }`,
потому что, строго говоря, мы про него знаем мало. 

- Можете заменить его на `Str:{ .field = 123 }`, т.е. явно указывать тип. 
- Вы также можете сделать функцию `IsCompatible(Type* expected, Type* given)`.
  Она не сравнивает типы в точности, а проверяет, что один **совместим** с
  другим. Это отношение несимметричное, возможно, будет чуть сложнее.

В конечном итоге в *Étude* будет реализована система **автоматического вывода
типов**, где это проблема уйдёт сама собой.


### Codegen

#### Как QBE обращается со структурами

Большое достоинство QBE в том, что он реализует за нас **полный ABI языка Си**.
Не все бэкэнды умеют это делать.

Сперва нужно **определить типы данных**:
https://c9x.me/compile/doc/il-v1.1.html#Aggregate-Types

Ментальная модель, которую следует держать в голове, — с аггрегатными типами
нужно обращаться *как с указателями*:

- При обработке **литерала структуры** память под неё следует *выделить на
  стеке*, затем *заполнить*, затем *вернуть указатель* на неё. 
- При обращении к переменной мы раньше загружали её из памяти; структуры же
  просто возвращают указатель на память.
- При виде `%.1 = :Struct call $id(:Struct %s)` опять же вспоминаем, что это
  просто указатель.

Как использовать структуры **в функциях**:
https://c9x.me/compile/doc/il-v1.1.html#Functions

#### GenAtVisitor

Создайте *визитора* **GenAt**, который будет генерировать какое-то выражение в
указанной области памяти. 

`GenAt(Expr* address, Expr* value)` — внутри себя он поддерживает текущую
позицию внутри `value`,

Это позволяет удобнее обращаться со слуедующими конструкциями:

```etude
*str_ptr = { .f0 = 3, 
             .f1 = { .f2 = true }, };
var t = *str_ptr;
var i = 123;
```

С левой строны у нас здесь единообразно какая-то **память**, а с правой —
**значение**, возможно большое, которое в эту память требуется поместить.

#### Alignment

[Stackoverflow: Purpose of Memory Alignment](https://stackoverflow.com/questions/381244/purpose-of-memory-alignment?rq=1)

> If you don't understand and address alignment issues in your software, the
> following scenarios, in increasing order of severity, are all possible:
> 
> Your software will run slower.
> Your application will lock up.
> Your operating system will crash.
> Your software will silently fail, yielding incorrect results.

[IBM Developer: Articles/pa-dalign](https://developer.ibm.com/articles/pa-dalign/)

- Как найти **общий alignment** структуры?
- Как найти **offset поля** с учётом **alignment**?

##  Реализация

Посмотрите, как реализованы кодогенераторы в [cproc:qbe.c](https://github.com/michaelforney/cproc/blob/master/qbe.c) и [hare:
gen.{h, c}](https://git.sr.ht/~sircmpwn/harec/tree/master/item/include/gen.h)
