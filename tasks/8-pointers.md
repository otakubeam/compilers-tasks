#  8. Pointers

> Указатели позволяют нам работать с нелокальными данными.

--  **Капитан**

Кроме того, с их помощью мы сможем строить более сложные **структуры данных**.

```etude
export {
    type Tree = struct {
        value: Int,
        left: *Tree,
        right: *Tree,
    };
}
```

## Синтаксис

### AddressOfExpr `&` + DerefExpr `*`

- Для того, чтобы **взять адрес переменной**, используется оператор `&`.
- Для того, чтобы **получить доступ** к ячейке памяти, используется оператор `*`.

```etude
of Int -> *String -> ()
fun main argc argv = {

    of Struct var s = { .field = 123 };

    of *Struct var s_ptr = &s;     <<------ 1. Take an address

    of Struct var copy = *s_ptr;   <<------ 2. Read the contents

    *s_ptr = { .field = 124 };     <<------ 3. Overwrite the contents

    0
};
```

**Вопрос для вас**: как связаны указатели и массивы? Всегда ли указатель валиден?
Должны ли знания о типах `Optional` и `Span` быть встроены в язык?

https://ziglang.org/documentation/master/#Pointers

### NewExpr + IndexExpr

- `NewExpr`  **динамически выделяет память**,
- `IndexExpr` предоставляет **доступ к элементам** по их номеру.

```etude
of Int -> *String -> ()
fun main argc argv = {
    var ptr = new [10] Struct;
    ptr[1] = ptr[2];
};
```

## Стадии компиляции

### Лексер

Новые *токены:*

  | Token Type                 | Source                     |
  | -----------                | -------                    |
  | `ADDR`                     | `&`                        |
  | `NEW`                      | `new`                      |
  | `LEFT_SBRACE`              | `[`                        |
  | `RIGHT_SBRACE`             | `]`                        |

### AST + Parser

Новые вершины: *Indirect-Field-Access, Address-Of, New-Expression,
Deref-Expression, Index-Expression*.

```diff
*** grammar-v3.txt    2023-02-25 12:08:06.247157444 +0300
--- grammar-v4.txt    2023-02-25 12:35:13.528570009 +0300
***************
*** 54,57 ****
--- 54,59 ----

  <unary-expression> ::= <postfix-expression>
+                      | & <unary-expression>
+                      | * <unary-expression>
                       | <unary-operator> <unary-expression>

***************
*** 61,64 ****
--- 63,68 ----
  <postfix-expression> ::= <primary-expression>
                         | <postfix-expression> . <identifier>
+                        | <postfix-expression> -> <identifier>
+                        | <postfix-expression> [ <integer> ]
                         | <postfix-expression> ( {<expression>,}* )

***************
*** 74,79 ****
--- 78,87 ----
  <keyword-expression> ::= return <expression>
                         | yield <expression>
+                        | <new-expression>
                         | <selection-expression>

+ <new-expression> ::= new <type-expression>
+                    | new [ <integer> ] <type-expression>
+
  <selection-expression> ::= if <expression> then? <expression>
                           | if <expression> then? <expression> else <expression>
```

###  Проверка типов

Нужно добавить новый конструктор типа -- `*`.  
В отличие от Си, звёздочка ставится перед типом.

### Codegen

Нужно создать новый алгортим -- `GenAddr`, который позволит **вычислить адрес**
выражения. Здесь возникает три случая: 
- локальная переменная, 
- параметр функции,
- материализованная структура.

В `NewExpression` вызывайте `malloc`.

##  Реализация

Два измерения:

- Чтение / Запись указателя
- Структура / Примитивный тип

---

  * *Deref Expresssion* (`*`) **на структурах** поялвляется в двух сочетаниях:
    - `*my_string = { ... };` -- на запись
    - `*my_string` -- на чтение

    Я предлагаю обрабатывать *запись* с помощью алгоритмов `GenAddr` и `GenAt`.
   *Чтение* выполняется по-разному в зависимости от того, читаем ли мы
   структуру или нет. Помните, что в IR **со структурой** следует обращаться
   **как с указателем**.

### Nullptr

Добавьте в язык литерал, представляющий *nullptr*. Например, можете
использовать `()`.

**Вопрос:** почему создание *nullptr* называют великой ошибкой в дизайне языков
программирования? Что с ним не так?
