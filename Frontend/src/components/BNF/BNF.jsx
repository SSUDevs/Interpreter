import "./BNF.css";
export default function BNF() {
  return (
    <div
      className="WordSection1"
      style={{ padding: "50px", backgroundColor: "white", color: "black" }}
    >
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;CHARACTER&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::=&nbsp;&nbsp; | ! | # | $ | % | &amp; | ( | ) | * | + | , | - | . |
          / | 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | : | ; | &lt; | = | &gt; |
          ? | @ | A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P
          | Q | R | S | T | U | V | W | X | Y | Z | [ | ] | ^ | _ | ` | a | b |
          c | d | e | f | g | h | i | j | k | l | m | n | o | p | q | r | s | t
          | u | v | w | x | y | z | {"{"} | | |{"}"} | ˜
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;ESCAPED_CHARACTER&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= \a | \b | \f | \n | \r | \t | \v | \\ | \? | \' | \" |
          \x&lt;HEX_DIGIT&gt; | \x&lt;HEX_DIGIT&gt;&lt;HEX_DIGIT&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;LETTER&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= A | B | C | D | E | F | G | H | I | J | K | L | M | N | O | P | Q
          | R | S | T | U | V | W | X | Y | Z | a | b | c | d | e | f | g | h |
          i | j | k | l | m | n | o | p | q | r | s | t | u | v | w | x | y | z
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;DIGIT&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;HEX_DIGIT&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= 0 | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | A | B | C | D | E | F | a
          | b | c | d | e | f
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;L_PAREN&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= (</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;R_PAREN&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= )</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;L_BRACKET&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= [</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;R_BRACKET&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= ]</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;L_BRACE&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= {"{"}</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;R_BRACE&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= {"}"}</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;DOUBLE_QUOTE&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= "</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;SINGLE_QUOTE&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= '</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;SEMICOLON&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= ;</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;COMMA&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= ,</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;ASSIGNMENT_OPERATOR&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= =</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;PLUS&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= +</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;MINUS&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= -</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;ASTERISK&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= *</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;DIVIDE&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= \</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;MODULO&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= %</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;CARET&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= ^</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;LT&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= &lt;</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;GT&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= &gt;</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;LT_EQUAL&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= &lt;=</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;GT_EQUAL&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= &gt;=</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;BOOLEAN_AND&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= &amp;&amp;</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;BOOLEAN_OR&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= ||</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;BOOLEAN_NOT&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= !</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;BOOLEAN_EQUAL&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= ==</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;BOOLEAN_NOT_EQUAL&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= !=</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;BOOLEAN_TRUE&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= TRUE</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;BOOLEAN_FALSE&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= FALSE</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;STRING&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;CHARACTER | &lt;ESCAPED_CHARACTER&gt; | &lt;CHARACTER&gt;
          &lt;STRING&gt; | &lt;ESCAPED_CHARACTER&gt; &lt;STRING&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;DOUBLE_QUOTED_STRING&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;DOUBLE_QUOTE&gt; &lt;STRING&gt; &lt;DOUBLE_QUOTE&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;SINGLE_QUOTED_STRING&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;SINGLE_QUOTE&gt; &lt;STRING&gt; &lt;SINGLE_QUOTE&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;LETTER_UNDERSCORE&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= &lt;LETTER&gt; | _</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;LETTER_DIGIT_UNDERSCORE&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;LETTER&gt; | &lt;DIGIT&gt; | _
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;WHOLE_NUMBER&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;DIGIT&gt; | &lt;DIGIT&gt; &lt;WHOLE_NUMBER&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;INTEGER&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;WHOLE_NUMBER&gt; | &lt;PLUS&gt; &lt;WHOLE_NUMBER&gt; |
          &lt;MINUS&gt; &lt;WHOLE_NUMBER&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;IDENTIFIER&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;LETTER_UNDERSCORE&gt; | &lt;LETTER_UNDERSCORE&gt;
          &lt;LETTER_DIGIT_UNDERSCORE&gt; | &lt;LETTER_UNDERSCORE&gt;
          &lt;LETTER_DIGIT_UNDERSCORE&gt; &lt;IDENTIFIER&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;IDENTIFIER_LIST&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;IDENTIFIER&gt; | &lt;IDENTIFIER&gt; &lt;COMMA&gt; |
          &lt;IDENTIFIER_LIST&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;IDENTIFIER_ARRAY_LIST&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;IDENTIFIER&gt; &lt;L_BRACKET&gt; &lt;WHOLE_NUMBER&gt;
          &lt;R_BRACKET&gt; | &lt;IDENTIFIER&gt; &lt;L_BRACKET&gt;
          &lt;WHOLE_NUMBER&gt; &lt;R_BRACKET&gt; &lt;COMMA&gt;
          &lt;IDENTIFIER_ARRAY_LIST&gt;{" "}
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;IDENTIFIER_LIST&gt; | &lt;IDENTIFIER_ARRAY_LIST&gt; |
          &lt;IDENTIFIER_LIST&gt; &lt;IDENTIFIER_ARRAY_LIST&gt; |
          &lt;IDENTIFIER_ARRAY_LIST&gt; &lt;IDENTIFIER_LIST&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;DATATYPE_SPECIFIER&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}> ::= char | bool | int</span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;NUMERICAL_OPERAND&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;IDENTIFIER&gt; | &lt;INTEGER&gt; | &lt;GETCHAR_FUNCTION&gt; |
          &lt;USER_DEFINED_FUNCTION&gt; | &lt;SINGLE_QUOTE&gt; &lt;CHARACTER&gt;
          &lt;SINGLE_QUOTE&gt; | &lt;SINGLE_QUOTE&gt; &lt;ESCAPED_CHARACTER&gt;
          &lt;SINGLE_QUOTE&gt; | &lt;DOUBLE_QUOTE&gt; &lt;CHARACTER&gt;
          &lt;DOUBLE_QUOTE&gt; | &lt;DOUBLE_QUOTE&gt; &lt;ESCAPED_CHARACTER&gt;
          &lt;DOUBLE_QUOTE&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;NUMERICAL_OPERATOR&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;PLUS&gt; | &lt;MINUS&gt; | &lt;ASTERISK&gt; | &lt;DIVIDE&gt; |
          &lt;MODULO&gt; | &lt;CARET&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;BOOLEAN_OPERATOR&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;BOOLEAN_AND_OPERATOR&gt; | &lt;BOOLEAN_OR_OPERATOR&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;EQUALITY_EXPRESSION&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;BOOLEAN_EQUAL&gt; | &lt;BOOLEAN_NOT_EQUAL&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;RELATIONAL_EXPRESSION&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;LT&gt; | &lt;LT_EQUAL&gt; | &lt;GT&gt; | &lt;GT_EQUAL&gt; |
          &lt;BOOLEAN_EQUAL&gt; | &lt;BOOLEAN_NOT_EQUAL&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;NUMERICAL_EXPRESSION&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;NUMERICAL_OPERAND&gt; | &lt;L_PAREN&gt;
          &lt;NUMERICAL_OPERAND&gt; &lt;R_PAREN&gt; | &lt;NUMERICAL_OPERAND&gt;
          &lt;NUMERICAL_OPERATOR&gt; &lt;NUMERICAL_EXPRESSION&gt; |
          &lt;L_PAREN&gt; &lt;NUMERICAL_OPERAND&gt; &lt;NUMERICAL_OPERATOR&gt;
          &lt;NUMERICAL_EXPRESSION&gt; &lt;R_PAREN&gt; |
          &lt;NUMERICAL_OPERAND&gt; &lt;NUMERICAL_OPERATOR&gt; &lt;L_PAREN&gt;
          &lt;NUMERICAL_EXPRESSION&gt; &lt;R_PAREN&gt; &lt;NUMERICAL_OPERAND&gt;
          &lt;NUMERICAL_OPERATOR&gt; &lt;NUMERICAL_EXPRESSION&gt; |
          &lt;L_PAREN&gt; &lt;NUMERICAL_OPERAND&gt; &lt;NUMERICAL_OPERATOR&gt;
          &lt;NUMERICAL_EXPRESSION&gt; &lt;R_PAREN&gt; |
          &lt;NUMERICAL_OPERAND&gt; &lt;NUMERICAL_OPERATOR&gt; &lt;L_PAREN&gt;
          &lt;NUMERICAL_EXPRESSION&gt; &lt;R_PAREN&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;BOOLEAN_EXPRESSION&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;BOOLEAN_TRUE&gt; | &lt;BOOLEAN_FALSE&gt; | &lt;IDENTIFIER&gt;
          | &lt;IDENTIFIER&gt; &lt;BOOLEAN_OPERATOR&gt;
          &lt;BOOLEAN_EXPRESSION&gt; | &lt;L_PAREN&gt; &lt;IDENTIFIER&gt;
          &lt;BOOLEAN_OPERATOR&gt; &lt;BOOLEAN_EXPRESSION&gt; &lt;R_PAREN&gt; |
          &lt;NUMERICAL_EXPRESSION&gt; &lt;BOOLEAN_EQUAL&gt;
          &lt;NUMERICAL_EXPRESSION&gt; | &lt;NUMERICAL_EXPRESSION&gt;
          &lt;BOOLEAN_NOT_EQUAL&gt; &lt;NUMERICAL_EXPRESSION&gt; |
          &lt;NUMERICAL_EXPRESSION&gt; &lt;LT_EQUAL&gt;
          &lt;NUMERICAL_EXPRESSION&gt; | &lt;NUMERICAL_EXPRESSION&gt;
          &lt;GT_EQUAL&gt; &lt;NUMERICAL_EXPRESSION&gt; |
          &lt;NUMERICAL_EXPRESSION&gt; &lt;LT&gt; &lt;NUMERICAL_EXPRESSION&gt; |
          &lt;NUMERICAL_EXPRESSION&gt; &lt;GT&gt; &lt;NUMERICAL_EXPRESSION&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;INITIALIZATION_EXPRESSION&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;IDENTIFIER&gt; &lt;ASSIGNMENT_OPERATOR&gt; &lt;EXPRESSION&gt;
          | &lt;IDENTIFIER&gt; &lt;ASSIGNMENT_OPERATOR&gt;
          &lt;SINGLE_QUOTED_STRING&gt; | &lt;IDENTIFIER&gt;
          &lt;ASSIGNMENT_OPERATOR&gt; &lt;DOUBLE_QUOTED_STRING&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;EXPRESSION&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;BOOLEAN_EXPRESSION&gt; | &lt;NUMERICAL_EXPRESSION&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;SELECTION_STATEMENT&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= if &lt;L_PAREN&gt; &lt;BOOLEAN_EXPRESSION&gt; &lt;R_PAREN&gt;
          &lt;STATEMENT&gt; | if &lt;L_PAREN&gt; &lt;BOOLEAN_EXPRESSION&gt;
          &lt;R_PAREN&gt; &lt;STATEMENT&gt; else &lt;STATEMENT&gt; | if
          &lt;L_PAREN&gt; &lt;BOOLEAN_EXPRESSION&gt; &lt;R_PAREN&gt;
          &lt;BLOCK_STATEMENT&gt; | if &lt;L_PAREN&gt;
          &lt;BOOLEAN_EXPRESSION&gt; &lt;R_PAREN&gt; &lt;BLOCK_STATEMENT&gt;
          else &lt;STATEMENT&gt; | if &lt;L_PAREN&gt; &lt;BOOLEAN_EXPRESSION&gt;
          &lt;R_PAREN&gt; &lt;BLOCK_STATEMENT&gt; else &lt;BLOCK_STATEMENT&gt; |
          if &lt;L_PAREN&gt; &lt;BOOLEAN_EXPRESSION&gt; &lt;R_PAREN&gt;
          &lt;STATEMENT&gt; else &lt;BLOCK_STATEMENT&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;ITERATION_STATEMENT&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= for &lt;L_PAREN&gt; &lt;INITIALIZATION_EXPRESSION&gt;
          &lt;SEMICOLON&gt; &lt;BOOLEAN_EXPRESSION&gt; &lt;SEMICOLON&gt;
          &lt;EXPRESSION&gt; &lt;R_PAREN&gt; &lt;STATEMENT&gt; | for
          &lt;L_PAREN&gt; &lt;INITIALIZATION_EXPRESSION&gt; &lt;SEMICOLON&gt;
          &lt;BOOLEAN_EXPRESSION&gt; &lt;SEMICOLON&gt; &lt;EXPRESSION&gt;
          &lt;R_PAREN&gt; &lt;BLOCK_STATEMENT&gt; | while &lt;L_PAREN&gt;
          &lt;BOOLEAN_EXPRESSION&gt; &lt;R_PAREN&gt; &lt;STATEMENT&gt; | while
          &lt;L_PAREN&gt; &lt;BOOLEAN_EXPRESSION&gt; &lt;R_PAREN&gt;
          &lt;BLOCK_STATEMENT&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;ASSIGNMENT_STATEMENT&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;IDENTIFIER&gt; &lt;ASSIGNMENT_OPERATOR&gt; &lt;EXPRESSION&gt;
          &lt;SEMICOLON&gt; | &lt;IDENTIFIER&gt; &lt;ASSIGNMENT_OPERATOR&gt;
          &lt;SINGLE_QUOTED_STRING&gt; &lt;SEMICOLON&gt; | &lt;IDENTIFIER&gt;
          &lt;ASSIGNMENT_OPERATOR&gt; &lt;DOUBLE_QUOTED_STRING&gt;
          &lt;SEMICOLON&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;PRINTF_STATEMENT&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= printf &lt;L_PAREN&gt; &lt;DOUBLE_QUOTED_STRING&gt;
          &lt;R_PAREN&gt; &lt;SEMICOLON&gt; | printf &lt;L_PAREN&gt;
          &lt;SINGLE_QUOTED_STRING&gt; &lt;R_PAREN&gt; &lt;SEMICOLON&gt; |
          printf &lt;L_PAREN&gt; &lt;DOUBLE_QUOTED_STRING&gt; &lt;COMMA&gt;
          &lt;IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST&gt; &lt;R_PAREN&gt;
          &lt;SEMICOLON&gt; | printf &lt;L_PAREN&gt;
          &lt;SINGLE_QUOTED_STRING&gt; &lt;COMMA&gt;
          &lt;IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST&gt; &lt;R_PAREN&gt;
          &lt;SEMICOLON&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;GETCHAR_FUNCTION&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= getchar &lt;L_PAREN&gt; &lt;IDENTIFIER&gt; &lt;R_PAREN&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;USER_DEFINED_FUNCTION&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;IDENTIFIER&gt; &lt;L_PAREN&gt;
          &lt;IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST&gt; &lt;R_PAREN&gt; |
          &lt;IDENTIFIER&gt; &lt;L_PAREN&gt; &lt;EXPRESSION&gt; &lt;R_PAREN&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;DECLARATION_STATEMENT&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;DATATYPE_SPECIFIER&gt; &lt;IDENTIFIER&gt; &lt;SEMICOLON&gt; |
          &lt;DATATYPE_SPECIFIER&gt;
          &lt;IDENTIFIER_AND_IDENTIFIER_ARRAY_LIST&gt; &lt;SEMICOLON&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;RETURN_STATEMENT&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= return &lt;EXPRESSION&gt; &lt;SEMICOLON&gt; | return
          &lt;SINGLE_QUOTED_STRING&gt; &lt;SEMICOLON&gt; | return
          &lt;DOUBLE_QUOTED_STRING&gt; &lt;SEMICOLON&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;STATEMENT&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;DECLARATION_STATEMENT&gt; | &lt;ASSIGNMENT_STATEMENT&gt; |
          &lt;ITERATION_STATEMENT&gt; | &lt;SELECTION_STATEMENT&gt; |
          &lt;PRINTF_STATEMENT&gt; | &lt;RETURN_STATEMENT&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;COMPOUND_STATEMENT&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;STATEMENT&gt; | &lt;STATEMENT&gt; &lt;COMPOUND_STATEMENT&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;BLOCK_STATEMENT&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;L_BRACE&gt; &lt;COMPOUND_STATEMENT&gt; &lt;R_BRACE&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;PARAMETER_LIST&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;DATATYPE_SPECIFIER&gt; &lt;IDENTIFIER&gt; |
          &lt;DATATYPE_SPECIFIER&gt; &lt;IDENTIFIER&gt; &lt;PARAMETER_LIST&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;FUNCTION_DECLARATION&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= function &lt;DATATYPE_SPECIFIER&gt; &lt;IDENTIFIER&gt;
          &lt;L_PAREN&gt; &lt;PARAMETER_LIST&gt; &lt;R_PAREN&gt; &lt;
          L_BRACE&gt; &lt;COMPOUND_STATEMENT&gt; &lt;R_BRACE&gt; | function
          &lt;DATATYPE_SPECIFIER&gt; &lt;IDENTIFIER&gt; &lt;L_PAREN&gt; void
          &lt;R_PAREN&gt; &lt; L_BRACE&gt; &lt;COMPOUND_STATEMENT&gt;
          &lt;R_BRACE&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>
            &lt;PROCEDURE_DECLARATION&gt;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= procedure &lt;IDENTIFIER&gt; &lt;L_PAREN&gt;
          &lt;PARAMETER_LIST&gt; &lt;R_PAREN&gt; &lt; L_BRACE&gt;
          &lt;COMPOUND_STATEMENT&gt; &lt;R_BRACE&gt; | procedure
          &lt;IDENTIFIER&gt; &lt;L_PAREN&gt; void &lt;R_PAREN&gt; &lt;
          L_BRACE&gt; &lt;COMPOUND_STATEMENT&gt; &lt;R_BRACE&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;MAIN_PROCEDURE&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= procedure main &lt;L_PAREN&gt; void &lt;R_PAREN&gt;
          &lt;BLOCK_STATEMENT&gt;
        </span>
      </p>
      <p className="MsoNormal">
        <span className="Heading3Char">
          <span style={{ fontSize: "14.0pt" }}>&lt;PROGRAM&gt;</span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          {" "}
          ::= &lt;MAIN_PROCEDURE&gt; | &lt;FUNCTION_DECLARATION&gt;
          &lt;PROGRAM&gt; | &lt;PROCEDURE_DECLARATION&gt; &lt;PROGRAM&gt; |
          &lt;DECLARATION_STATEMENT&gt; &lt;PROGRAM&gt;
        </span>
      </p>
      <h2>The language contains the following datatypes:</h2>
      <p className="MsoListParagraphCxSpFirst">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <b>
          <span
            style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}
          >
            char
          </span>
        </b>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          {" "}
          : holds one character. Strings are implemented by defining an array of
          char of a given size using an array element. For example, char
          my_string[256] would enable one to store strings up to 256 bytes in
          length (accessed as 0 to 255 in the indices).
        </span>
      </p>
      <p className="MsoListParagraphCxSpMiddle">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <b>
          <span
            style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}
          >
            bool
          </span>
        </b>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          {" "}
          : holds the Boolean value TRUE or FALSE.
        </span>
      </p>
      <p className="MsoListParagraphCxSpLast">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <b>
          <span
            style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}
          >
            int
          </span>
        </b>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          {" "}
          : holds a 32-bit signed integer.
        </span>
      </p>
      <h2>Your language must support the following statements:</h2>
      <p className="MsoListParagraphCxSpFirst">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          Declaration statement.
        </span>
      </p>
      <p className="MsoListParagraphCxSpLast">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          Assignment statement.
        </span>
      </p>
      <h2>Selection statement: if-then-else.</h2>
      <p className="MsoListParagraph">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          Iteration statements: for and while.
        </span>
      </p>
      <h2>
        This language has the following built-in input-output subroutines:
      </h2>
      <p className="MsoListParagraphCxSpFirst">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <span className="Heading3Char">
          <span
            style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}
          >
            getchar()
          </span>
        </span>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          {" "}
          : reads one character cast as integer from standard input (keyboard).
          If no character was read from keyboard, -1 is returned.
        </span>
      </p>
      <p className="MsoListParagraphCxSpLast">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <span className="Heading3Char">
          <span
            style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}
          >
            printf()
          </span>
        </span>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          {" "}
          : outputs a formatted string to the screen. Example: printf ("The
          magic number is %d\n", number);
        </span>
      </p>
      <h2>A program must minimally contain the following:</h2>
      <p className="MsoListParagraphCxSpFirst">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          A procedure named "main".
        </span>
      </p>
      <p className="MsoListParagraphCxSpMiddle">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          The main procedure must contain no input parameters. Example:{" "}
        </span>
      </p>
      <p className="MsoListParagraphCxSpLast" style={{ textIndent: "0in" }}>
        <span style={{ fontSize: "14.0pt" }}>
          procedure main (void) {"{"}
          {"}"}
        </span>
      </p>
      <h2>Rules for passing arrays to functions or procedures:</h2>
      <p className="MsoListParagraph">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          Since the language does not support array pointers, arrays of all
          datatypes are pass-by-value rather than pass-by-reference.
        </span>
      </p>
      <h2>
        Examples of passing string variable, char my_string[255] to a function
        or procedure:
      </h2>
      <p className="MsoListParagraphCxSpFirst">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          my_string_function (my_string)
        </span>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          {" "}
          : This will pass the entire 255-byte string to the function(). This
          function or procedure should be declared to accept at least 255 bytes!
        </span>
      </p>
      <p className="MsoListParagraphCxSpMiddle">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          my_string_function (my_string[0])
        </span>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          {" "}
          : This will only send one byte to the function.
        </span>
      </p>
      <p className="MsoListParagraphCxSpLast">
        <span style={{ fontSize: "14.0pt", fontFamily: "Symbol" }}>
          ·
          <span style={{ font: '7.0pt "Times New Roman"' }}>
            &nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
          </span>
        </span>
        <span style={{ fontSize: "14.0pt" }}>
          my_string_function (my_string[14])
        </span>
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          {" "}
          : This will only send one byte to the function.
        </span>
      </p>
      <p className="MsoNormal">
        <span style={{ fontSize: "14.0pt", fontFamily: '"Arial",sans-serif' }}>
          &nbsp;
        </span>
      </p>
    </div>
  );
}
