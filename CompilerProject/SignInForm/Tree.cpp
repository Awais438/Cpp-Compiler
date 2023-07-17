#include "MyForm.h"
using namespace SignInForm;

enum TokenType_Abdullah
{
    // Token types declaration
    IF_049,
    ELSE_049,
    WHILE_049,
    DO_049,
    FOR_049,
    RoundBracketOpen_049,
    RoundBracketClose_049,
    OPR,
    ID_049,
    FLOAT_049,
    NUM_049,
    MINUS_049,
    OR_049,
    AND_049,
    NOTEQUAL_049,
    NOT_049,
    RIGHTSHIFT_049,
    LEFTSHIFT_049,
    MODULUS_049,
    LCB_049,
    RCB_049,
    MINUSEQ_049,
    DIV_049,
    BEGIN_049,
    END_049,
    MULTIEQ_049,
    LSB_049,
    RSB_049,
    PLUSPLUS_049,
    PLUS_049,
    PLUSEQ_049,
    EQEQ_049,
    EQUAL_049,
    SEMICOLON_049,
    COLON_049,
    COMMA_049,
    COMMENT_049,
    MINUSMINUS_049,
    LESS_049,
    MULTI_049,
    LESSEQ_049,
    GREATER_049,
    GREATEREQ_049,
    INT_049,
    STRING_049,
    CHAR_049,
    DOUBLE_049
};

struct Token
{
    TokenType_Abdullah tokenType; // Enum representing the token number
    string Value;                 // String representing the type of token
    int integerValue = 0;         // Integer value associated with the token (initialized to 0)

} Abdullah, currentToken, nextToken; // Two instances of the Token_Abdullah struct: Abdullah and current_token

typedef enum
{
    opk,
    constk,
    idk
} expkind;
typedef enum
{
    ifk,
    assignk,
    dok,
    whilek
} stmtkind;
typedef enum
{
    stmtk,
    expk
} nodekind1;

struct treenode
{
    expkind expk;
    nodekind1 nodek;
    stmtkind stmtk;
    TokenType_Abdullah Tok1;
    int value;
    string name;
    treenode *leftchild = NULL;
    treenode *rightchild = NULL;
    treenode *middlechild = NULL;
    treenode *sibling = NULL;
};

// Function Prototypes
void unGet();
Token getToken();
Token Lexical();
treenode *expression();
treenode *term();
treenode *factor();
void printTree(treenode *, int, string);
int evaluateExpression(treenode *);

bool boolFLAG = 0;
ifstream inputFILE;
ofstream outFILE("TreeGen.txt");
ofstream evaluateFile("EvaluateExp.txt");

// -- puBack funtion to set boolFLAG for token.
void unGet()
{
    boolFLAG = 1;
}

// getToken Function
Token getToken()
{
    if (boolFLAG == 0) // Check if boolFLAG is 0
    {
        currentToken = Lexical(); // Call Lexical function to obtain a new token
        return currentToken;      // Return the new token
    }
    else
    {
        boolFLAG = 0;        // Set boolFLAG to 0
        return currentToken; // Return the previously obtained token
    }
}

// Lexical function: Generates and returns the next token based on the input source code.
Token Lexical()
{
    char inputChar;
    string st = "";
    while (!inputFILE.eof())
    {
        inputFILE.get(inputChar);
        if (inputChar == '(')
        {
            Abdullah.tokenType = RoundBracketOpen_049;
            Abdullah.Value = "Round Bracket Open";
            return Abdullah;
        }
        else if (inputChar == ')')
        {
            Abdullah.tokenType = RoundBracketClose_049;
            Abdullah.Value = "Round Bracket Close";
            return Abdullah;
        }
        else if (inputChar == '[')
        {
            Abdullah.tokenType = LSB_049;
            Abdullah.Value = "Left Square Bracket";
            return Abdullah;
        }
        else if (inputChar == ']')
        {
            Abdullah.tokenType = RSB_049;
            Abdullah.Value = "Right Square Bracket";
            return Abdullah;
        }
        else if (inputChar == '{')
        {
            Abdullah.tokenType = LCB_049;
            Abdullah.Value = "Left Curly Bracket";
            return Abdullah;
        }
        else if (inputChar == '}')
        {
            Abdullah.tokenType = RCB_049;
            Abdullah.Value = "Right Curly Bracket";
            return Abdullah;
        }
        else if (inputChar == ';')
        {
            Abdullah.tokenType = SEMICOLON_049;
            Abdullah.Value = "Semi Colon";
            return Abdullah;
        }
        else if (inputChar == ':')
        {
            Abdullah.tokenType = COLON_049;
            Abdullah.Value = "Colon";
            return Abdullah;
        }
        else if (inputChar == ',')
        {
            Abdullah.tokenType = COMMA_049;
            Abdullah.Value = "Comma";
            return Abdullah;
        }
        else if (inputChar == '%')
        {
            Abdullah.tokenType = MODULUS_049;
            Abdullah.Value = "Modulus";
            return Abdullah;
        }
        else if (inputChar == '|')
        {
            inputFILE.get(inputChar);
            if (inputChar == '|')
            {
                Abdullah.tokenType = OR_049;
                Abdullah.Value = "OR";
                return Abdullah;
            }
            else
            {
                inputFILE.unget();
            }
        }
        else if (inputChar == '&')
        {
            inputFILE.get(inputChar);
            if (inputChar == '&')
            {
                Abdullah.tokenType = AND_049;
                Abdullah.Value = "AND";
                return Abdullah;
            }
            else
            {
                inputFILE.unget();
            }
        }
        else if (inputChar == '!')
        {
            inputFILE.get(inputChar);
            if (inputChar == '=')
            {
                Abdullah.tokenType = NOTEQUAL_049;
                Abdullah.Value = "NOT Equal";
                return Abdullah;
            }
            else
            {
                inputFILE.unget();
                Abdullah.tokenType = NOT_049;
                Abdullah.Value = "NOT";
                return Abdullah;
            }
        }
        else if (inputChar == '/')
        {
            // Check if the next character is '/'
            if (inputFILE.peek() == '/')
            {
                cout << "Singleline comment found // \n";
                do
                {
                    inputFILE.get(inputChar);
                } while (inputChar != '\n');
            }
            // Check if the next character is '*'
            else if (inputFILE.peek() == '*')
            {
                cout << "Multiline comment found /*.... */\n";
                while (1)
                {
                    inputFILE.get(inputChar);
                    if (inputChar == '*')
                    {
                        inputFILE.get(inputChar);
                        if (inputChar == '/')
                        {
                            break;
                        }
                    }
                }
            }
            // If neither '/' nor '*', assume it's a division operator
            else
            {
                Abdullah.tokenType = DIV_049;
                Abdullah.Value = "DIV";
                return Abdullah;
            }
        }
        else if (inputChar == '*')
        {
            if (inputChar == '/')
            {
                Abdullah.tokenType = COMMENT_049;
                Abdullah.Value = "Comment";
                return Abdullah;
            }
            else if (inputChar == '=')
            {
                Abdullah.tokenType = MULTIEQ_049;
                Abdullah.Value = "Multiply Equal";
                return Abdullah;
            }
            else
            {
                Abdullah.tokenType = MULTI_049;
                Abdullah.Value = "Multiply";
                return Abdullah;
            }
        }

        else if (inputChar == '+')
        {
            inputFILE.get(inputChar);
            if (inputChar == '=')
            {
                Abdullah.tokenType = PLUSEQ_049;
                Abdullah.Value = "Plus Equal";
                return Abdullah;
            }
            else if (inputChar == '+')
            {
                Abdullah.tokenType = PLUSPLUS_049;
                Abdullah.Value = "Plus Plus";
                return Abdullah;
            }
            else
            {
                inputFILE.unget();
                Abdullah.tokenType = PLUS_049;
                Abdullah.Value = "Plus";
                return Abdullah;
            }
        }

        else if (inputChar == '-')
        {
            inputFILE.get(inputChar);
            if (inputChar == '=')
            {
                Abdullah.tokenType = MINUSEQ_049;
                Abdullah.Value = "Minus Equal";
                return Abdullah;
            }
            else if (inputChar == '-')
            {
                Abdullah.tokenType = MINUSMINUS_049;
                Abdullah.Value = "Minus Minus";
                return Abdullah;
            }
            else
            {
                inputFILE.unget();
                Abdullah.tokenType = MINUS_049;
                Abdullah.Value = "Minus";
                return Abdullah;
            }
        }

        else if (inputChar == '=')
        {
            inputFILE.get(inputChar);
            if (inputChar == '=')
            {
                Abdullah.tokenType = EQEQ_049;
                Abdullah.Value = "Equal Equal";
                return Abdullah;
            }
            else
            {
                inputFILE.unget();
                Abdullah.tokenType = EQUAL_049;
                Abdullah.Value = "Equal";
                return Abdullah;
            }
        }

        else if (inputChar == '<')
        {
            inputFILE.get(inputChar);
            if (inputChar == '=')
            {
                Abdullah.tokenType = LESSEQ_049;
                Abdullah.Value = "Less Equal";
                return Abdullah;
            }
            else if (inputChar == '<')
            {
                Abdullah.tokenType = LEFTSHIFT_049;
                Abdullah.Value = "Left Shift";
                return Abdullah;
            }
            else
            {
                inputFILE.unget();
                Abdullah.tokenType = LESS_049;
                Abdullah.Value = "Less";
                return Abdullah;
            }
        }

        else if (inputChar == '>')
        {
            inputFILE.get(inputChar);
            if (inputChar == '=')
            {
                Abdullah.tokenType = GREATEREQ_049;
                Abdullah.Value = "Greater Equal";
                return Abdullah;
            }
            else if (inputChar == '>')
            {
                Abdullah.tokenType = RIGHTSHIFT_049;
                Abdullah.Value = "Right Shift";
                return Abdullah;
            }
            else
            {
                inputFILE.unget();
                Abdullah.tokenType = GREATER_049;
                Abdullah.Value = "Greater";
                return Abdullah;
            }
        }

        else if (isdigit(inputChar))
        {
            string word = "";

            while (isdigit(inputChar))
            {
                word += inputChar;
                if (inputFILE.peek() == EOF)
                    break;
                inputFILE.get(inputChar);
            }
            inputFILE.seekg(-1, ios::cur);
            Abdullah.tokenType = NUM_049;
            Abdullah.Value = "Number";
            Abdullah.integerValue = stoi(word);
            return Abdullah;
        }

        else if (((int)inputChar >= 65 && (int)inputChar <= 99) || ((int)inputChar >= 97 && (int)inputChar <= 122))
        {
            st = "";
            do
            {
                st += inputChar;
                inputFILE.get(inputChar);
            } while (isalnum(inputChar) && st != "END");
            if (st != "END")
            {
                inputFILE.unget();
            }
            char v;
            if (st == "int")
            {
                string b = "";
                do
                {
                    inputFILE.get(inputChar);
                    v = inputChar;
                } while (v != '=');
                inputFILE.get(inputChar);
                do
                {
                    b += inputChar;
                    inputFILE.get(inputChar);
                } while (isdigit(inputChar));
                Abdullah.tokenType = INT_049;
                Abdullah.Value = "Integer";
                return Abdullah;
            }
            else if (st == "string")
            {
                string b = "", v1, x;
                do
                {
                    inputFILE.get(inputChar);
                    v1 = inputChar;
                } while (v1 != "=");
                inputFILE.get(inputChar);
                do
                {
                    b += inputChar;
                    inputFILE.get(inputChar);
                    x = inputChar;
                } while (x != "'");
                Abdullah.tokenType = STRING_049;
                Abdullah.Value = "String";
                return Abdullah;
            }
            else if (st == "for")
            {
                Abdullah.tokenType = FOR_049;
                Abdullah.Value = "For";
                return Abdullah;
            }
            else if (st == "while")
            {
                Abdullah.tokenType = WHILE_049;
                Abdullah.Value = "While";
                return Abdullah;
            }
            else if (st == "BEGIN")
            {
                Abdullah.tokenType = BEGIN_049;
                Abdullah.Value = "Begin";
                return Abdullah;
            }
            else if (st == "END")
            {
                Abdullah.tokenType = END_049;
                Abdullah.Value = "End";
                return Abdullah;
            }
            else if (st == "do")
            {
                Abdullah.tokenType = DO_049;
                Abdullah.Value = "Do";
                return Abdullah;
            }
            else if (st == "if")
            {
                Abdullah.tokenType = IF_049;
                Abdullah.Value = "If";
                return Abdullah;
            }
            else if (st == "else")
            {
                Abdullah.tokenType = ELSE_049;
                Abdullah.Value = "Else";
                return Abdullah;
            }
            else if (st == "float")
            {
                Abdullah.tokenType = FLOAT_049;
                Abdullah.Value = "Float";
                return Abdullah;
            }
            else if (st == "double")
            {
                Abdullah.tokenType = DOUBLE_049;
                Abdullah.Value = "Double";
                return Abdullah;
            }
            else
            {
                Abdullah.tokenType = ID_049;
                Abdullah.Value = "Variable";
                return Abdullah;
            }
        }
    }
    return Abdullah;
}

treenode *expression()
{
    treenode *t = nullptr;
    treenode *p = nullptr;
    int boolFLAGe = 0;
    do
    {
        t = term();
        if (boolFLAGe)
        {
            p->rightchild = t;
            boolFLAGe = 0;
            t = p;
        }
        Abdullah = getToken();
        if (Abdullah.tokenType == PLUS_049 || Abdullah.tokenType == MINUS_049)
        {
            p = new treenode;
            p->expk = opk;
            p->Tok1 = Abdullah.tokenType;
            p->leftchild = t;
            boolFLAGe = 1;
        }
    } while (Abdullah.tokenType == PLUS_049 || Abdullah.tokenType == MINUS_049);
    unGet();
    return (t);
}

treenode *term()
{
    treenode *t = nullptr;
    treenode *p = nullptr;
    int boolFLAGe = 0;
    do
    {
        t = factor();
        if (boolFLAGe)
        {
            p->rightchild = t;
            boolFLAGe = 0;
            t = p;
        }
        Abdullah = getToken();
        if (Abdullah.tokenType == MULTI_049 || Abdullah.tokenType == DIV_049 || Abdullah.tokenType == MODULUS_049)
        {
            p = new treenode;
            p->expk = opk;
            p->Tok1 = Abdullah.tokenType;
            p->leftchild = t;
            boolFLAGe = 1;
        }
    } while (Abdullah.tokenType == MULTI_049 || Abdullah.tokenType == DIV_049 || Abdullah.tokenType == MODULUS_049);
    unGet();
    return t;
}

treenode *factor()
{
    treenode *t;
    Abdullah = getToken();
    switch (Abdullah.tokenType)
    {
    case NUM_049:
        t = new treenode();
        t->expk = constk;
        t->value = Abdullah.integerValue;
        t->Tok1 = Abdullah.tokenType;
        t->name = "Num";
        t->leftchild = NULL;
        t->rightchild = NULL;
        return t;
        break;

    case ID_049:
        t = new treenode();
        t->expk = idk;
        t->value = Abdullah.integerValue;
        t->Tok1 = Abdullah.tokenType;
        t->name = "ID";
        t->leftchild = NULL;
        t->rightchild = NULL;
        return t;
        break;

    case RoundBracketOpen_049:
        t = expression();
        nextToken = getToken();
        if (nextToken.tokenType != RoundBracketClose_049)
        {
            cout << "\nInvalid Input\nexiting...";
            exit(0);
        }
        return t;
    default:
        cout << "\nInvalid Input\nexiting...";
        exit(0);
        return t;
        break;
    }
}

void printTree(treenode *node, int indent = 0, string childType = "", int prevOperator = -1)
{
    ofstream outputFILE("TreeGen.txt", ios::app);

    // Check if the file was opened successfully
    if (!outputFILE.is_open())
    {
        cout << "Failed to open TreeGen.txt" << endl;
        return;
    }

    if (node == NULL)
        return;

    if (node->expk == opk)
    {
        outputFILE << setw(indent) << ""
                   << "+- Operator (" << childType << "): ";

        switch (node->Tok1)
        {
        case PLUS_049:
            outputFILE << "PLUS" << endl;
            break;

        case MINUS_049:
            outputFILE << "MINUS" << endl;
            break;

        case MULTI_049:
            outputFILE << "MULTIPLY" << endl;
            break;

        case DIV_049:
            outputFILE << "DIVIDE" << endl;
            break;

        case MODULUS_049:
            outputFILE << "MOD" << endl;
            break;

        default:
            outputFILE << "Unknown operator" << endl;
            break;
        }
    }
    else if (node->expk == constk)
    {
        outputFILE << setw(indent) << ""
                   << "+- Constant (" << childType << "): " << node->value << endl;
    }
    else if (node->expk == idk)
    {
        outputFILE << setw(indent) << ""
                   << "+- Identifier (" << childType << "): " << node->name << endl;
    }

    // Process left child
    if (node->leftchild != NULL)
    {
        outputFILE << setw(indent) << ""
                   << "|";
        printTree(node->leftchild, indent + 4, "LeftChild", node->Tok1);
    }

    // Process right child only if the operator is different from the previous one
    if (node->rightchild != NULL && node->Tok1 != prevOperator)
    {
        outputFILE << setw(indent) << ""
                   << "|";
        printTree(node->rightchild, indent + 4, "RightChild", node->Tok1);
    }
}

treenode *statement()
{
    treenode *t1;
    treenode *tree;
    Abdullah = getToken();
    if (Abdullah.tokenType == ID_049)
    {
        tree = new treenode; // node for statement
        tree->nodek = stmtk;
        tree->stmtk = assignk;

        /* identifierNode = new treenode;
         identifierNode->kind = Identifier;
         identifierNode->name = token.name;
         identifierNode->leftchild = nullptr;
         identifierNode->rightchild = nullptr;*/

        Abdullah = getToken();
        if (Abdullah.tokenType == EQUAL_049)
        {

            /*tree = new treenode;
            tree->kind = ooperator;
            tree->name = token.name;
            operatorNode->leftchild = nullptr;
            operatorNode->rightchild = nullptr;

            Link the operator node as the left child of the identifier node
            identifierNode->leftchild = operatorNode;*/

            if ((t1 = expression()))
            {
                tree->leftchild = t1;
                Abdullah = getToken();
                if (Abdullah.tokenType == SEMICOLON_049)
                    return (tree);
            }
        }
    }
    return nullptr;
}

treenode *statement_list() // statement list
{
    treenode *stree;
    treenode *prevtree;
    treenode *stmttree;
    if ((prevtree = statement()))
    {
        prevtree->sibling = NULL;
        stmttree = prevtree;
        stmttree->sibling = NULL;
        do
        {
            Abdullah = getToken();
            if (Abdullah.tokenType == IF_049 || Abdullah.tokenType == DO_049 || Abdullah.tokenType == ID_049)
            {
                unGet();
                if ((stree = statement()) == NULL) // NOT TRUE
                    return NULL;

                stree->sibling = NULL;
                prevtree->sibling = stree;
                prevtree = stree;
            }
            else
            {
                unGet();
                break;
            }

        } while (1);
        // return true; // if , not, uid not equal then may be else
        return (stmttree);
    }
    return NULL; // otherwise false
}

bool program()
{
    treenode *fulltree;
    Abdullah = getToken();
    if (Abdullah.tokenType == BEGIN_049)
    {
        if ((fulltree = statement_list()) != NULL)
        {
            Abdullah = getToken();
            if (Abdullah.tokenType == END_049)
                return true;
        }
    }
    return false;
}

int evaluateExpression(treenode *root)
{
    if (root == nullptr)
    {
        return 0;
    }

    switch (root->expk)
    {
    case opk:
        switch (root->Tok1)
        {
        case PLUS_049:
            return evaluateExpression(root->leftchild) + evaluateExpression(root->rightchild);
        case MINUS_049:
            return evaluateExpression(root->leftchild) - evaluateExpression(root->rightchild);
        case MULTI_049:
            return evaluateExpression(root->leftchild) * evaluateExpression(root->rightchild);
        case DIV_049:
            return evaluateExpression(root->leftchild) / evaluateExpression(root->rightchild);
        default:
            return 0;
        }
    case constk:
        return root->value;
    case idk:
        // You can handle variable evaluation here if needed
        return 0;
    default:
        return 0;
    }
}

void startProgram()
{
    inputFILE.open("TreeExp.txt");
    if (!inputFILE)
    {
        cout << "Unable to open file." << endl;
    }
    treenode *expressionTree = expression();
    //	// Print the expression tree
    printTree(expressionTree, 0, "Root", -1);

    int result = evaluateExpression(expressionTree);
    evaluateFile << result << endl;

    evaluateFile.close();
    inputFILE.close();
    outFILE.close();
}

//// -- Driver Program
// int main() {
//     inputFILE.open("Abdullah049.txt");
//     if (!inputFILE) {
//         cout << "Unable to open file." << endl;
//         return 0;
//     }
//     treenode* expressionTree = expression();
//     // Print the expression tree
//     printTree(expressionTree, 0, "Root", -1);
//
//     int result = evaluateExpression(expressionTree);
//     cout << "The Result is: " << result << endl;
//
//
//     inputFILE.close();
//     system("pause");
//     return 0;
// }