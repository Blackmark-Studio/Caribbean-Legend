
// WAZAR SCRIPTING LANGUAGE

// Set RunTests = 1 in engine.ini [script] section
// See tests.log and error.log for results after game start

// If possible, add the syntax highlighting (to basic C syntax):
// INSTRUCTION WORD: call new in is typeid exec
// TYPE WORD: string native ref aref object
// LITERALS: true false nullptr
// OPERATOR: @
// STRING: ``

// Note: while there is no optimization in the engine for transferring arrays, objects (not just an attribute reference, but a real object) and strings, it is advisable to transfer them by reference (with & or by ref-variable) to the appropriate operators (@, in, is, typeid, explicit casts).
// Otherwise, a full copy of the variable will be created (and then deleted!) on the stack.
// When the optimization appears, this note and tests will be fixed (@ -> @ and etc).

// Macros can now be used in initializing global arrays
#define __TEST_MACRO 100
int __tstarr[] = {__TEST_MACRO, 1, __TEST_MACRO, };
int __tstarr2[2] = {__TEST_MACRO, __TEST_MACRO};

void test__array()
{
    // Use @ instead GetArraySize
    assert(@__tstarr == GetArraySize(&__tstarr));
    assert((@__tstarr == 3) && (@__tstarr2 == 2));

    // Assigning any arrays via {}
    string arr1[] = {"a", "bb", "ccc"}; // @arr1 == 3
    string arr2[3] = {"a", "bb", "ccc", };

    arr1 = {"a", "b"};
    assert(@arr1 == 2);
    SetArraySize(&arr1, 0);
    assert(@arr1 == 0);

    // Forget SetArraySize (via @)
    @arr1 = 4;
    assert(@arr1 == 4);
    @arr1++;
    @arr1 += 5;
    assert(@arr1 == 10);
    @arr1--;
    assert(@arr1 == 9);
    @arr1 -= 9;
    assert(@arr1 == 0);
    // TO_DO: * *=

    // Concatenating variables
    string arr3[];
    assert((@arr3 == 0) && !@arr3);
    arr3 += "sss";
    assert(@arr3 == 1);
    assert(arr3[0] == "sss");

    // Concatenating array expression
    arr3 += {"sa", "fds"};
    assert(@arr3 == 3);
    assert((arr3[1] == "sa") && (arr3[2] == "fds"));
    arr3 += {"sf", };
    assert((arr3[3] == "sf") && (@arr3 == 4));

    // Comparing arrays
    assert(arr3 != arr1);
    arr3 = arr1; // Assigning by array
    assert((&arr3) == (&arr1));
    assert({1, 2} == {1, 2, });
    assert({1, 2} != {1, 3});

    // Working with array cells inside a function
    int arr5[] = {1, 2, 3, 4, 5};
    ShuffleArray(&arr5);

    // Passing array literals to the function
    assert(__CheckFive(&arr5));
    assert(__CheckFive({1, 2, 5}));
    assert(!__CheckFive({1, 2, 3}));
    assert(!__CheckFive({})); // Will pass a nullptr
    assert(!__CheckFive({rand(1), rand(2), rand(3)}));
}
bool __CheckFive(ref arr)
{
    for (int i = 0; i < @arr; i++){if (arr[i] == 5) return true;}
    return false;
}

void test__smartsort()
{
    // See sorting.c
    // TO_DO
}

void test__arr_shuffle()
{
    // TO_DO
}

bool __TrFu(){ return true; }
bool __FlFu(){ return false; }
bool test__bracket_parsing()
{
    // Multi initialization
    bool Tr1 = true, Tr2 = true, Fl1 = false, bTmp, bM[] = {false, true};

    // Bracket recursive parsing
    if ((Tr1 && Tr2) || Fl1) assert(true);
    else assert(false);

    bTmp = ((false && bM[1]) || false) || ((bM[0] && __FlFu()) || false || __TrFu() || false);
    assert(bTmp);

    return (bTmp && false) || __FlFu() || __TrFu();
}

bool test__ternar()
{
    // Ternary operator
    assert(__TrFu() ? (false ? true ? false : false : true) : (rand(1) ? true: true));
    bool bTmp = 1 ? 1 : 0, bM[] = false ? {} : {false ? false : true, true ? false ? false : true : false};
    assert(bTmp);
    assert(bM[0] == 1 && bM[1] == true);
    if (__TrFu() ? __TrFu() ? false ? false : true : true : __TrFu() ? 0 : 0)
        assert(true);
    else
        assert(false);
    if (__TrFu() ? (__TrFu() ? (false ? false : (true ? 0 : 1) ? 0 : 1) : false) : false)
        assert(true);
    else
        assert(false);

    // Ternary conditional operator is disallowed in non-expression scope
    // Both operands must also be expressions, not pure statements

    return bTmp ? true : false;
}

// If you create a reference to a local variable 
// or to a temporary global one from a segment that will then be unloaded,
// then after exiting its scope, you do not need to use such a reference (UB)

void test__case_default_size_operator()
{
    // Default case in switch
    // Strictly at the end of the switch and with break operator
    // Don't rely on semantics from C (so far, but it may be fixed in the future)

    // Don't use the "default" keyword in other places
    // But "Default" is acceptable, since tokens are case-sensitive

    // Cases of negative numbers are now handled correctly

    int i, cnt = 0;
    int iArray[] = {1, -1, 2, 3, 5, -100};
    for(i = 0; i < @iArray; i++)
    {
        cnt++;
        switch (iArray[i])
        {
            case 4: assert(false); break;
            case 5: assert(true); break;
            case -100: assert(true); break;
            default:
                if (iArray[i] == 5 || iArray[i] == -100) assert(false);
                else assert(true);
                break; // so far, a break is required, just like with regular cases in this scripts
        }
        // Bad example 1 (so far)
        switch (iArray[i])
        {
			default:
                if (iArray[i] == 5 || iArray[i] == -100) assert(false);
                else assert(true);
                break; // so far, a break is required, just like with regular cases in this scripts
            case 4: assert(false); break;
            case 5: assert(true); break;
            case -100: assert(true); break;
        }
        // Bad example 2 (so far)
        switch (iArray[i])
        {
            case 4: assert(false); break;
            case 5: assert(true); break;
			default:
                if (iArray[i] == 5 || iArray[i] == -100) assert(false);
                else assert(true);
                break; // so far, a break is required, just like with regular cases in this scripts
            case -100: assert(true); break;
        }
    }
    assert(cnt == 6);
    assert(cnt == @iArray);

    // Array sizes testing
    // Forget GetArraySize
    int biba[] = {3, 2}, boba[], booba[4];
    assert(@biba == 2 && @boba == 0 && !@boba && @booba == 4);
    biba = &boba;
    booba = {0, };
    assert(@biba == 0 && @booba == 1);
    booba += 1;
    booba += {3, 2} + {4, 5};
    assert(@booba == 6);
    int boobs;
    assert(@boobs == 0 && !@boobs); // scalar (and not attribute)
    cnt = 0;
    for(i = 0; i < @booba; i++)
    {
        cnt++;
        booba = {3, 2, int(__TrFu())};
    }
    assert(cnt == 3); // because booba changed size
    assert(@{} == 0);
    assert(@{1, 2} == 2);

    // Attributes sizes testing
    // Forget GetAttributesNum
    object bob;
    bob.attr1 = "";
    bob.attr2 = "";
    assert(@bob == 2);
    DeleteAttribute(&bob, "attr1");
    assert(@bob == 1);
    DeleteAttribute(&bob, "");
    assert(@bob == 0);
    bob.attr1.attr1 = "";
    bob.attr1.attr2 = "";
    bob.attr1.attr3 = "";
    aref bibs = &bob.attr1;
    assert(@bibs == 3);
    DeleteAttribute(bibs, "attr2");
    assert(@bibs == 2);
    DeleteAttribute(&bob, "");
    //assert(@bibs == 0); // This UB
    bob.attr1 = "";
    bob.attr2 = "";
    bob.attr3 = "";
    bob.attr4 = "";
    bob.attr5 = "";
    bob.attr6 = "";
    cnt = 0;
    for(i = 0; i < @bob; i++)
    {
        cnt++;
        DeleteAttribute(&bob, "attr" + (6 - i));
    }
    assert(cnt == 3); // because bob changed size
    assert(cnt == @bob);
    int aa[4], bb[5];
    assert(@(true ? &aa : &bb) == 4);
    ref ra = &aa, rb = &bb;
    assert(@(false ? ra : rb) == 5);
}

void test__is_in_nullptr()
{
    // Quick and easy attribute check
    // Forget CheckAttribute
    // But keep in mind that in almost all cases, an object / array / string must be passed by reference (including for new operators), otherwise its entire structure will be copied to the stack and then deleted, which is a PERFORMANCE FUNERAL for some bulky objects like Characters[]

    object biba, bulba;
    biba.attr = "";

    assert(CheckAttribute(&biba, "attr") == ("attr" in &biba));
    assert(!CheckAttribute(&biba, "attr") == ("attr" !in &biba));
    assert("attr" in &biba);
    assert("attr" !in bulba);
    aref boba;
    assert("attr" !in boba);
    boba = &biba;
    assert("attr" in boba);
    aref boba2;
    makearef(boba2, biba);
    assert("attr" in boba2);
    ref boba3 = &biba;
    assert("attr" in boba3);
    DeleteAttribute(&biba, "attr");
    assert(CheckAttribute(&biba, "attr") == ("attr" in &biba));
    assert(!CheckAttribute(&biba, "attr") == ("attr" !in &biba));
    assert("attr" !in boba);
    assert("attr" !in boba2);
    assert("attr" !in boba3);

    // Type checking
    bool bbiba;
    assert(bbiba is bool); // The bool-cake is a lie (so far)
    int ibiba, iboba[];
    assert(ibiba is int);
    assert(ibiba !is int[]);
    assert((&iboba) !is int);
    assert((&iboba) is int[]);
    iboba += 0;
    assert(iboba[0] is int);
    assert(iboba[0] !is int[]);
    assert(ibiba !is ref); // is ref always false (nullptr is nullptr will be true)
    assert(1 is int);
    assert(1.0 !is int);
    assert({1, 2} is int[]);
    assert(`boobs` is string); // string literal with forced escape sequence processing
    assert("boobs" is string);
    ref rTmp;
    assert(rTmp is nullptr);
    assert(nullptr is nullptr);
    rTmp = &ibiba;
    assert(rTmp is int);
    assert(rTmp !is ref); // is ref always false
    rTmp = &iboba;
    assert(rTmp is int[]);
    assert(rTmp !is int);
    ref rTmpArr[];
    assert(rTmpArr is ref[]); // is ref[] can be true
    rTmp = &rTmpArr;
    assert(rTmp is ref[]);
    object obj;
    assert((&obj) is object);
    assert((&obj) !is aref);
    aref arTmp;     assert(arTmp is aref);
    arTmp = obj;    assert(arTmp is aref);
    arTmp = &obj;   assert(arTmp is aref);
//  makearef(arTmp, &obj); assert(arTmp is aref); TO_DO CE
    rTmp = &obj;
    makearef(arTmp, rTmp);  assert(arTmp is aref);
    arTmp = rTmp;           assert(arTmp is aref);
    makearef(arTmp, obj);   assert(arTmp is aref);
    arTmp = nullptr;        assert(arTmp is aref);
    assert(rTmp is object);
    rTmp = nullptr;
    assert(rTmp is nullptr);
    int iii; float fff; string sss[];
    rTmpArr += &iii;
    rTmpArr += &fff;
    rTmpArr += &sss;
    assert(rTmpArr[0] is int);
    assert(rTmpArr[1] is float);
    assert(rTmpArr[2] is string[]);
}

void test__bits()
{
    // New operations: ^,  |,  &,  >>,  <<
    //                 ^=, |=, &=, >>=, <<=
    //                 ~
    // See bits defines in NumberUtilities.c (BIT_8, LBITS_3, INT_MIN, etc)
    // Please dont use and() or() tokens. They are redundant and will be deleted.
    // Keep in mind that the shl() shr() tokens make arithmetic shifts (SAL, SAR),
    // and << >> logical shifts (SHL, SHR). We will rename the tokens in the future.
    // Operations will be performed on bits as if they were a unsigned type, but
    // the result is stored/displayed as signed int.
    // There will be no UB from shifts by an amount greater than sizeof(int) * CHAR_BIT.
    // Priority for operators as in C.

    int bTmp;
    int a, b, BitMask;

    // BLOCK I: Stupid tests:
    assert((1 | 1)  == 1); assert((1 | 0)  == 1); assert((0 | 1)  == 1); assert((0 | 0)  == 0);
    assert((1 ^ 1) == 0);  assert((1 ^ 0) == 1);  assert((0 ^ 1) == 1);  assert((0 ^ 0) == 0);
    assert((1 & 1)  == 1); assert((1 & 0)  == 0); assert((0 & 1)  == 0); assert((0 & 0)  == 0);
    assert(1 >> 1 == 0);   assert(1 >> 0 == 1);   assert(0 >> 1 == 0);   assert(0 >> 0 == 0);
    assert(1 << 1 == 2);   assert(1 << 0 == 1);   assert(0 << 1 == 0);   assert(0 << 0 == 0);
    assert(~1 == -2);      assert(~0 == -1);
    a = rand(INT_MAX);
    assert(~a == -1-a);
    BitMask = 0;         // 00000000 00000000 00000000 00000000
    BitMask = ~BitMask;  // 11111111 11111111 11111111 11111111
    assert(BitMask == -1);
    // Shifts > 63 testing temporary disabled (TO_DO)
    BitMask >>= 64;      // 00000000 00000000 00000000 00000000
    assert(BitMask == 0);
    BitMask = 1;         // 00000000 00000000 00000000 00000001
    BitMask <<= 63;      // 10000000 00000000 00000000 00000000
    assert(BitMask == INT_MIN);
    BitMask <<= 1;
    assert(!BitMask);
    BitMask |= (1 << 7); // 00000000 00000000 00000000 10000000
    assert(BitMask == BIT_8);
    BitMask |= (1 << 1); // 00000000 00000000 00000000 10000010
    assert(BitMask == (BIT_8 | BIT_2));
    BitMask &= LBITS_3;  // 00000000 00000000 00000000 00000010
    assert(BitMask == BIT_2);
    BitMask <<= 63;
    assert(!BitMask);

    // BLOCK II: Чуть менее stupid tests:
    // Первое упражнение из Шеня
    a = 228;
	b = -322;
    a ^= b;
    b ^= a;
    a ^= b;
    assert((a == -322) && (b == 228));

    // Counting bits set
    BitMask = 1351687204; // 01010000 10010001 00011100 00100100
    for (a = 0; BitMask; a++) BitMask &= BitMask - 1;
    assert(a == 10);

    // Determining if an integer is a power of two
    a = INT_MAX;
    bTmp = a && !(a & (a - 1));
    assert(!bTmp);
    a = (1 << 28);
    bTmp = a && !(a & (a - 1));
    assert(bTmp);

    // Compute the integer absolute value without branching
    a = -322;
    BitMask = -(a >> 63);
    b = (a ^ BitMask) - BitMask;
    assert(b == 322);
    a = INT_MAX;
    BitMask = -(a >> 63);
    b = (a ^ BitMask) - BitMask;
    assert(b == INT_MAX);

    // Clear the lower n bits
    BitMask = 2519349767; // 10010110 00101010 00111010 00000111 (with overflow, but its ok)
    BitMask &= ~((1 << 16) - 1); // 10010110 00101010 00000000 00000000
    assert(BitMask == 2519334912);

    // Determine if a word has a zero byte
    b = 2519349767; // 10010110 00101010 00111010 00000111
	bTmp = (~((((b & 2139062143) + 2139062143) | b) | 2139062143)) & (-1 >> 32); // 2139062143 == 0x7F7F7F7F
    assert(!bTmp);
    b = 2519334913; // 10010110 00101010 00000000 00000001
    bTmp = ~((((b & 2139062143) + 2139062143) | b) | 2139062143);
    assert(bTmp);

    // Simple hash
    // Note: Dont forget that bit operations treat values as unsigned bitmasks,
    // but the result is stored/displayed as signed int
    b = 1234567890; // 01001001 10010110 00000010 11010010
    // b >> 16 is      00000000 00000000 01001001 10010110
    b ^= b >> 16;   // 01001001 10010110 01001011 01000100
    b *= 31;        // 11101001 00110011 00011101 00111100
    // b >> 11 is      00000000 00011101 00100110 01100011
    b ^= b >> 11;   // 11101001 00101110 00111011 01011111
    assert(b == 38255082335, "hash test failed!");

    // Reverse bits
	// Reverse bits
	b = 355427305; // 00000000 00000000 00000000 00000000 00010101 00101111 01100011 11101001
	a = 32;
	BitMask = -1;
	while (a)
	{
		BitMask ^= (BitMask << a);
		b = ((b >> a) & BitMask) | ((b << a) & ~BitMask);
		a >>= 1;
	}
	assert(b == -7510046326202040320); // 10010111 11000110 11110100 10101000 00000000 00000000 00000000 00000000

    // BLOCK III: Bacchanalia test
    int tst = 10;
    assert(~~tst == tst);
    assert(!!~~tst == 1);
    tst = ~!@tst;
    assert(tst == -2);
    tst = !~&tst;
    assert(tst == 0);
    tst = 1234567890987654321;
    tst = ~((tst >> 11) ^ (tst << (!@tst ? 4 : 6)) | 32578 + (6457 * tst ^^ 2)); // ^^ is pow
    assert(tst == -9199639678823690204);
}

void test__arithmetic_edits()
{
    assert(2 ^^ 3 ^^ 2 == 512); // right-associative
    int i = 4;
    i ^^= 3;
    assert(i == 64);
    i %= 3;
    assert(i == 1);
}

void test__aref_linking()
{
    ref rtst;
    object obj, obMassive[4];
    aref ar;
    ar = obj;  assert(ar is aref);
    ar = &obj; assert(ar is aref);
    makearef(ar, obj);  assert(ar is aref);
//  makearef(ar, &obj); assert(ar is aref); TO_DO CE
    ar = obMassive[2];  assert(ar is aref);
    ar = &obMassive[2]; assert(ar is aref);
    makearef(ar, obMassive[2]);  assert(ar is aref);
//  makearef(ar, &obMassive[2]); assert(ar is aref); TO_DO CE
    rtst = &obj; ar = rtst; assert(ar is aref);
    makearef(ar, rtst);     assert(ar is aref);
    obj.attr.attr1 = "";
    obMassive[2].attr.attr2 = "";
    rtst.attr.attr3 = "";
    // Now expressions like &obj.attr are aref (previously Invalid Expression)
    ar = &obj.attr; assert(ar is aref);
    assert("attr1" in ar); assert("attr3" in ar);
    ar = &obMassive[2].attr; assert(ar is aref);
    assert("attr2" in ar); assert("attr3" !in ar);
    __tstaref(&obj.attr);
}
void __tstaref(aref biba)
{
    assert("attr1" in biba);
}

string __sa1[];
void test__tensors_operator_new()
{
    ref matrix2x2[2];
    int row1[2] = {1, 0}, row2[2] = {0, 1};
    matrix2x2[0] = &row1;
    matrix2x2[1] = &row2;
    assert((&matrix2x2) is ref[]);
    assert(matrix2x2[0] is int[]);
    assert((&matrix2x2) is ref[]);
    assert((&matrix2x2[0]) is int[]);
    assert(matrix2x2[0][0] is int);
    assert(!matrix2x2[0][1]);
    assert(matrix2x2[1][1] == 1);

    ref tensor[];
    __MakeNxNxN(&tensor, 3, typeid(int));
    assert((&tensor) is ref[]);
    assert((&tensor[0]) is ref[]);
    assert((&tensor[0][0]) is int[]);
    assert((&tensor[0][0][0]) is int);
    tensor[0][0] = {1, 2, 3};
    assert(tensor[0][0][1] == 2);
    tensor[0][1] = {1, 2, 3};
    assert((&tensor[0][1]) == (&tensor[0][0]));
    assert(tensor[0][1][1] == tensor[0][0][1]);

    // Operator new returns ref with type[]
    __sa1 = new string[0]; // If the value returned by the operator new is not accepted as a reference, then dereference and copying will occur, which is correct, but by accepting copying as a reference, you can avoid it
    assert(__sa1 is string[]);
    assert(@__sa1 == 0);
    SetArraySize(&__sa1, 3);
    __sa1[0] = "b";
    assert(__sa1[0] is string);
}
void __MakeNxNxN(ref rArr, int N, int type)
{
    if (rArr !is ref[]) return;
    @rArr = N;

    int i, j;
    for(i = 0; i < N; i++)
    {
        rArr[i] = new ref[N];
        for (j = 0; j < N; j++)
        {
            switch (type)
            {
                case typeid(int):   rArr[i][j] = new int[true ? N : 0]; break;
                case typeid(float): rArr[i][j] = new float[N]; break;
                case typeid(ref):   rArr[i][j] = new ref[N];   break;
                // ...
            }
        }
    }
}

// Until there is a GC for such cases, circular references will lead to leaks
// Please don't create circular ref yet
// NO MEMORY LEAK:
// ref r1, r2;  nullptr, nullptr
// r1 = r2;     r1 = nullptr
// r2 = r1;     r2 = nullptr
// NO MEMORY LEAK:
// ref r1 = new ref(nullptr); r1 = nullptr
// MEMORY LEAK:
// ref r = new ref[1];
// r[0] = &r;
// MEMORY LEAK:
// ref r1[] = new ref[1], r2[] = new ref[1];
// r1[0] = &r2; r2[0] = &r1;

void test__advanced_string_literals()
{
    /*
    \a  0x07    Alert/Bell          Звуковой сигнал (не работает)
    \b  0x08    Backspace           Возврат курсора на символ
    \f  0x0C    Form feed           Перевод страницы
    \n  0x0A    Newline             Перевод строки
    \r  0x0D    Carriage return     Возврат каретки
    \t  0x09    Tab                 Горизонтальная табуляция
    \v  0x0B    Vertical tab        Вертикальная табуляция
    \\  \       Backslash           Обратный слэш
    \`  `       Backtick            Обратная кавычка
    \?  ?       Question mark       Вопросительный знак
    \xNN        Hex byte            Произвольный байт (2 hex-цифры)
    \uNNNN      Unicode BMP         Codepoint U+0000 – U+FFFF (4 hex-цифры)
    \UNNNNNNNN  Unicode full        Codepoint U+00000000 – U+FFFFFFFF (8 hex-цифр)
    */

    // See compile.log
    trace("--------------------------");
    string str = `"" \? \x41 \u0042 \U0001F600 \n \t boba`;
    trace(str);
    trace(`\\ \` \v \n biba \x0A boba`);
    trace("--------------------------");
    assert(str is string);

    // Forget NewStr()
/*  str = `\n`;
    string str2 = "\n";
    assert(str  == NewStr());
    assert(str2 != NewStr()); */
}

object __gob99;
string __gcode;
int __global_biba = 0, __gcnt1 = 0;
void test__exec()
{
    // exec is very expensive, use it only for debugging purposes
    // There are significant restrictions on the code that can be passed to it
    // For example, you might not be able to allocate variables on the stack

    int local_biba = 0;
    // exec executes code in a global context, not the current scope
    // exec("local_biba = 5;"); // Fail
    exec("__global_biba = 5;"); // Good
    assert(__global_biba == 5);
    int i = 5;
    exec("__global_biba = (12 + 15);");
	exec("i = 21;");
    assert(__global_biba == 27 && i == 21);
    string code = "12;";
    i = exec(code);
    assert(i == 12);

    /*code = "for(__gcnt1 = 0; __gcnt1 < 10; __gcnt1++) __global_biba++;
            return __global_biba";
    i = exec(code);
    assert(i == 37);

    __gcnt1 = 0;
    __gcode = "__gcnt1++; if (__gcnt1 < 10) exec(__gcode);";
    exec(__gcode);
    assert(__gcnt1 == 10);

    __gob99.code = `__gob99.code.cnt = int(__gob99.code.cnt) + 1;
                    if (__gob99.code.cnt != "10")
                  //{
                        exec(__gob99.code);
                  //}
                    `;
    __gob99.code.cnt = 0;
    exec(__gob99.code);
    assert(__gob99.code.cnt == "10");*/
}

void test__variadic_default_args()
{
    string res;
    __tstfunc1(&res, "gooooo:", 1, 2, 3, 5.0, "dsfdsf", 4, 5);
    assert(res == "gooooo:123oops 5oops 645");
}
void __tstfunc1(ref str, string boba = "go:", ...)
{
    int i, qty = GetArgCount();
    string boobs[] = {boba};
    for (i = 2; i < qty; i++)
    {
        ref rArg = GetArg(i);
        if (rArg is int) boobs += string(rArg);
        else boobs += "oops " + i;
    }
    for (i = 0; i < @boobs; i++) str += boobs[i];
}

#define __TST_MACRO_1 ""
#define __TST_MACRO_2 1
#define __TST_MACRO_3 1.0
void test__typeid()
{
    bool   b, ba[]; assert(typeid(b) == typeid(bool));    assert(typeid(&ba) == typeid(bool[]));
    int    i, ia[]; assert(typeid(i) == typeid(int));    assert(typeid(&ia) == typeid(int[]));
    float  f, fa[]; assert(typeid(f) == typeid(float));  assert(typeid(&fa) == typeid(float[]));
    string s, sa[]; assert(typeid(s) == typeid(string)); assert(typeid(&sa) == typeid(string[]));
    ref    r, ra[]; assert(typeid(r) == typeid(ref));    assert(typeid(&ra) == typeid(ref[]));
    aref   a, aa[]; assert(typeid(a) == typeid(aref));   assert(typeid(&aa) == typeid(aref[]));
    object o, oa[]; assert(typeid(o) == typeid(object)); assert(typeid(&oa) == typeid(object[]));

    bool check1 = (r is ref);
    bool check2 = (typeid(r) == typeid(ref));
    assert(!check1);
    assert(check2);
    assert(r is nullptr);
    assert(typeid(nullptr) == typeid(ref));

    r = &s;
    switch (typeid(r))
    {
        case typeid(string): assert(true); break;
        default: assert(false); break;
    }

    assert(typeid(__TST_MACRO_1) == typeid(string));
    assert(typeid(__TST_MACRO_2) == typeid(int));
    assert(typeid(__TST_MACRO_3) == typeid(float));
}

void test__explicit_cast()
{
    // Forget: its, int, float, int, float, etc
    // fts makes sense, as it allows you to specify the number of characters

    float f = -11.9999;
    assert(typeid(string(f)) == typeid(string));
    switch (int(f))
    {
        case -11: assert(true); break;
        default:  assert(false); break;
    }
    switch (int(false ? -25.55543 : -5.776))
    {
        case -5: assert(true); break;
        default: assert(false); break;
    }

    object ob;
    ob.attr = "";
    aref ar;
//  ar = aref(ob); Нельзя, потому что объект копирует, будет ссылка на копию,
//  которая потом уничтожится
    ar = aref(&ob); // So far don't do aref(ob)!
    assert("attr" in ar);
    assert(ar is aref);
}

void test__additions()
{
    // Number attributes now work correctly
    object ob;
    ob.222.111 = "";
    assert("222" in (&ob));
    aref ar = &ob.222;
    assert("111" in ar);

    ref tensor[];
    __MakeNxNxN(&tensor, 3, typeid(int));
    tensor[0][1][2] = 5;
    tensor[0][1][2]++;
    tensor[0][1][2] += 3;
    assert(tensor[0][1][2] == 9);

    aref attr;
    assert(attr !is nullptr); // Both!
    assert(aref(nullptr) !is nullptr);

//  ref r = attr; // Так нельзя, должна быть именно ссылка
    ref r = &attr;
    attr = &ob.222.111;
    r = nullptr; // r became nullptr, but not aref, which she referred to
    assert(attr !is nullptr);
    r = &ar;
    r = aref(nullptr);
    assert(ar !is nullptr);
	ref r2 = &ar;
	assert(r2 !is nullptr);
	assert(r2 != nullptr);
	assert(r2 == aref(nullptr));

    // The operator ! applied to float now works correctly
    if (0.99)
	{

	}
	else
	{
		assert(false);
	}
    assert(!0.99 == false);
    assert(!!0.99);

    // Array clearing QoL
    int biba[] = {1,2,3,4,5,6,7};
    biba = {};
    assert(@biba == 0);

    assert(typeid(__returnzero()) == typeid(float));

    // Assigning attributes value via aref
    attr = &ob.222; // ~!~ Пояснение про = ob.222
    attr = "sss";
    assert(ob.222 == "sss");
    attr = 12434; // implicit conversion to string
    assert(ob.222 == "12434");

    // Shared owning on data
    ref rArr = new int[11];
    rArr = {0,1,2,3,4,5,6,7,8,9,10};
    ref rBibs = rArr;
    assert(rBibs[3] == 3);
    assert(rArr[3] == 3);
    rArr = new int[5];
    // rArr no longer owns the old data, but it is still alive
    // as it was owned by another reference
    rArr[3] = 6;
    assert(rBibs[3] == 3);
    assert(@rBibs == 11);
    // rBibs = &ob.222 Не выйдет, потому что слева aref, а не ref
    // & применяется к символам, но не к выражениям,
    // поэтому написать что-то вроде rBibs = &&ob.222 или rBibs = &(&ob.222) тоже нельзя
    rBibs = &attr; // Only at this moment will the data from the first new be released

    // Оператор new type[] возвращает ref на type[]
    // Это значение лучше всего принять в ссылку, но можно и в соответствующий массив,
    // что приведёт к более дорогому копированию

    // Не стоит путать массив ссылок ref[] и обычную ссылку ref
    // ref[] это отдельный тип, который не имеет семантики динамической типизации, как у ref
    // Ссылка может сослаться на ref-массив, например, через амперсанд   r = &rArr
    // Ссылка может сослаться на переменную другой ссылки без амперсанда r = r2
    // Но написать r = rArr не выйдет, rArr это массив ссылок, а не ссылка
    // Если сделать r = new ref[10], то ссылка r будет ссылаться на массив ссылок (и владеть им)
    // Тогда r = rArr уже сработает, но будет присвоением одного массива другому, а не заменой ссылки

    // Multitype collection and scalar new
    ref collection[] = new ref[3];
    collection[0] = new int(10);
    collection[1] = new string("biba");
    string str = collection[0] + collection[1];
    assert(str == "10biba");

    // TO_DO: Инициализация по умолчанию в scalar new
    /*collection[2] = new object();
    collection[2].attr = "boba";
    assert(collection[2].attr == "boba");*/

    // Note: В скриптах отсутствует comma operator ','
    // Та запятая, что есть, используется лишь как разделитель в списках инициализации
    // и в списках аргументов функции, не является оператором, не имеет сишной семантики,
    // не предназначена для использования вне этих случаев
}
float __returnzero()
{
    // return 0.0;
    return 0; // Now there is no RE, there will be an implicit conversion
}
