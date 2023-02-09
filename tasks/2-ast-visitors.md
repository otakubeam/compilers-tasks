
# 2. AST и Visitor-ы

В предыдующем задании мы научились преобразовывать поток символов в поток
токенов. Следующая фаза компилятора — синтакскический анализ, т.е. парсинг.

Парсер преобразует плоский поток токенов в более богатое предстваление — AST, абстрактное синтаксическое дерево.

Все последующие этапы компилятора оперируют с некой формой AST.

Данное задание о том, как представлять код и обращаться с ним алгоритмически.

## О грамматике языка Étude

В грамматике языка есть 5 видов правил (сейчас нас интересуют три из них):

| Category    | Examples                                   |
|-------------|--------------------------------------------|
| Declaration | `Function Declaration`                     |
| Statement   | `Assignment`, `Expression-Statement`       |
| Expression  | `Literal`, `Variable`, `If`, `Block`       |
|             | `Function Call`, `Unary`, `Binary`, etc... |

Étude — **expression-oriented** language. Это значит, что большинство конструкций
языка являются выражениями.

По-другому: в грамматке языка сделаны несколько устоявшихся, но, возможно,
непривычных, выборов относительно категорий синтаксических конструкций.

Например, `<if-expression> ::= if <expr> then? <expr> else <expr>` принадлежит
синтаксической категории выражений.

Это позволяет писать выражения следующего вида:

```kotlin
var candidate = if node_value < val {
    &tree->left
} else {
    &tree->right
};
```

Блоки в языке Étude также поволяют возвращать значения. Это удобно, когда
необходимо последовательно исполнить несколько утверждений и вернуть значение.

Конструкции, контролиующие поток исполнения, такие как `return <expr>` и `yield
<expr>`, являются выражениями, возвращающими **! — never type**. Мы вернёмся к
этому вопросу при обсуждении системы типов.

В итоге в грамматике языка оказывается лишь два правила, принадлежащих
категории **statement**.

См. **Appendix A** для текущей версии грамматики! В будущем она обрастёт новыми
правилами, но фундаментально всё останется так же.

### Declarations

Первый набор правил, с которыми мы встретимся — **объявления**. 

```

<file> ::= <declaration>*

<declaration> ::= <function-definition>
                | <variable-declaration>

<function-declaration> ::= fun <identifier> <parameter-list> = <expression> ;
      <parameter-list> ::= <identifier>*

<variable-declaration> ::= var <identifier> = <expression> ;

```

Файл для нас сейчас представляет последовательность объявлений, каждое из
которых является либо функцией, либо переменной. Например, так:

```etude
# File: main.et

fun main argc argv = {

    var return_value = 0;
    
    return_value
};
```

Базовая структура AST представляет собой контейнер для содежащихся в правиле
данных. В будущем мы, вероятно, захотим хранить дополнительную информацию в
вершинах AST, например, тип для выражений, но пока этого достаточно.

```cpp
class FunDeclStatement : public Declaration {
  // Constructors, Accept, GetLocation, GetName, etc...
  
  lex::Token name_; // Conveniently also stores location
  
  std::vector<lex::Token> formals_;

  Expression* body_;
};
```

### Statements

Всего два правила. 

**Expression Statement** позволяет вычислить выражение и выкинуть результат.

**Assignment Statement** присваивает новое значение переменной содержащейся в
*области видимости* (об этом позже). В языке Си это также является выражением.
А в Go, например, утверждением.

```

<statement> ::= <expression-statement>
              | <assignment-statement>

<expression-statement> ::= <expression> ;

<assignment-statement> ::= <unary-expression> = <expression>

```

### Expressions

Самая громоздкая часть. Про правила подробно поговорим в следующий раз.

```

<expression> ::= <equality-expression>

<equality-expression> ::= <relational-expression>
                        | <equality-expression> == <relational-expression>
                        | <equality-expression> != <relational-expression>

<relational-expression> ::= <shift-expression>
                          | <relational-expression> < <shift-expression>
                          | <relational-expression> > <shift-expression>

<shift-expression> ::= <additive-expression>

<additive-expression> ::= <multiplicative-expression>
                        | <additive-expression> + <multiplicative-expression>
                        | <additive-expression> - <multiplicative-expression>

<multiplicative-expression> ::= <unary-expression>
                              | <multiplicative-expression> * <unary-expression>
                              | <multiplicative-expression> / <unary-expression>
                              
```

Пока достаточно заметить, что многие из них являются простыми бинарными
отношениями: `==`, `>`, `*`, `+`. Для них вы можете сделать несколько типов
данных, где каждый наследник `BinaryNode` или всего один, а тип отличать по
токену операции. А может быть что-то посередине, делайте, как вам нравится =).

**Postfix Expression** — сейчас вызов функции `foo(a, b, c)`

**Compound Expression** — объединяет несколько **объявлений** и **утверждений** с
возвращаемым значением.

| Вопрос                    | Ответ                        |
|---------------------------|------------------------------|
| Почему `<keyword-expression>` принимают `<expression>` ? Они очень похожи на `<unary-expression>` | Они жадные для удобства, чтобы не писать `return (a == b)` | 


...продолжение грамматики

```

<unary-expression> ::= <postfix-expression>
                     | <unary-operator> <unary-expression>

<unary-operator> ::= -
                   | !

<postfix-expression> ::= <primary-expression>
                       | <postfix-expression> ( <expression>,* )

<primary-expression> ::= <identifier>
                       | <constant>
                       | <keyword-expression>
                       | <compound-expression>
                       | ( <expression> )

<compound-expression> ::= { (<declaration> | <statement>)* <expression>? }

<keyword-expression> ::= return <expression>
                       | yield <expression>
                       | <selection-expression>

<selection-expression> ::= if <expression> then? <expression>
                         | if <expression> then? <expression> else <expression>

<constant> ::= <integer-constant>
             | <string>

```

### Tree Node

Для удобства все категории наследуются от общего предка `TreeNode`, содержащёго
виртуальный метод. `GetLocation()`

```

                          +--------------+               
                          |              |               
                          |  Tree Node   |               
                          |              |               
                          +--------------+               
                          /       |      \               
                         /        |       \              
                        /         |        \             
                       /          |         \            
                      -           |          -           
            Expressions      Statements      Declarations
               /                                         
              /                                          
             -                                           
    LvalueExpression

```

## Задание

Вам предлагается разработать структуры данных синтаксического дерева для языка
Étude и реализовать *visitor*-а для распечатки дерева.

1. Прочитайте [Crafting Interpreters: Representing Code](https://craftinginterpreters.com/representing-code.html).
2. Создайте ваши **структуры данных** для преставление AST
3. Создайте **абстрактного визитора** — интерфейс для всех алгоритмов.
4. Создайте **контретного визитора**, реализующего печать дерева рекурсивным обходом.
5. Вручную создайте небольшое дерево и примените к нему `PrintVisitor`.

Цель — создать структуры данных, которые будут результатом работы парсера.  
Цель 2 — научиться работать с представлением программы в виде AST.

## Реализация

### Типы визиторов: `AbortVisitor`, `JustWalkVisitor`, `ReturnVisitor`

- `ReturnVisitor`

  Данный визитор содержит в себе значение, которое по смыслу является
  _возвращаемым значением_ алгоритма. Это очень полезно и часто используется.

  Например: 

  | Domain                    |  Возвращаемое значение         |
  |---------------------------|--------------------------------|
  | Интерпретация             | Представление значения в языке |
  | Проверка типов            | Структура типа в компиляторе   |
  | Перепиывание AST          | Вершина AST                    |

  ```cpp
  template <typename T>
  class ReturnVisitor : public Visitor {
   public:

    T Eval(TreeNode* expr) {
      expr->Accept(this);
      return return_value;
    }
  
   protected:
    T return_value;
  };
  ```

- `AbortVisitor`

  Иногда визитор определён не на всех вершинах дерева. Забегая вперёд, так
  работает, например, `GenAddress`-visitor. Не у всего можно вычислить адрес.
  
  Тогда удобно сделать дополнительную структуру, которая аварийно завершается на всех вершинах AST, а в наследнике переопределять только интересующие нас случаи.
  
  ```cpp
  class AbortVisitor : public Visitor {
    ...
    virtual void VisitFunDecl(FunDeclStatement*) override {
      std::abort();
    }
  
  };
  ```


## Appendix A. Grammar


```

////////////////////////////////////////////////////////////////////////////////////
//!                             Declarations
////////////////////////////////////////////////////////////////////////////////////


<file> ::= <declaration>*

<declaration> ::= <function-definition>
                | <variable-declaration>

<function-declaration> ::= fun <identifier> <parameter-list> = <expression> ;

<variable-declaration> ::= var <identifier> = <expression> ;


////////////////////////////////////////////////////////////////////////////////////
//!                             Expressions
////////////////////////////////////////////////////////////////////////////////////


<expression> ::= <equality-expression>

<equality-expression> ::= <relational-expression>
                        | <equality-expression> == <relational-expression>
                        | <equality-expression> != <relational-expression>

<relational-expression> ::= <shift-expression>
                          | <relational-expression> < <shift-expression>
                          | <relational-expression> > <shift-expression>

<shift-expression> ::= <additive-expression>

<additive-expression> ::= <multiplicative-expression>
                        | <additive-expression> + <multiplicative-expression>
                        | <additive-expression> - <multiplicative-expression>

<multiplicative-expression> ::= <unary-expression>
                              | <multiplicative-expression> * <unary-expression>
                              | <multiplicative-expression> / <unary-expression>

<unary-expression> ::= <postfix-expression>
                     | <unary-operator> <unary-expression>

<unary-operator> ::= -
                   | !

<postfix-expression> ::= <primary-expression>
                       | <postfix-expression> ( {<expression>,}* )

<primary-expression> ::= <identifier>
                       | <constant>
                       | <keyword-expression>
                       | <compound-expression>
                       | ( <expression> )

<compound-expression> ::= { {<declaration> | <statement>}* <expression>? }

<keyword-expression> ::= return <expression>
                       | yield <expression>
                       | <selection-expression>

<selection-expression> ::= if <expression> then? <expression>
                         | if <expression> then? <expression> else <expression>

<constant> ::= <integer-constant>
             | <string>


////////////////////////////////////////////////////////////////////////////////////
//!                             Statements
////////////////////////////////////////////////////////////////////////////////////


<statement> ::= <expression-statement>
              | <assignment-statement>

<expression-statement> ::= <expression> ;

<assignment-statement> ::= <unary-expression> = <expression>


////////////////////////////////////////////////////////////////////////////////////

```
