
#define __TEST_MACRO_int1  -100
#define __TEST_MACRO_int2  100
#define __TEST_MACRO_int3  0b001
#define __TEST_MACRO_int4  -0b001
#define __TEST_MACRO_int5  0xFF
#define __TEST_MACRO_int6  -0xFF

#define __TEST_MACRO_uint1  123u
#define __TEST_MACRO_uint2  0b001u
#define __TEST_MACRO_uint3  -1u
#define __TEST_MACRO_uint4  0xFFu
#define __TEST_MACRO_uint5   'X'

#define __TEST_MACRO_float1   14.66
#define __TEST_MACRO_float2   -14.66
#define __TEST_MACRO_float3   14.
#define __TEST_MACRO_float4   -14.
#define __TEST_MACRO_float5   .14
#define __TEST_MACRO_float6   -.14
#define __TEST_MACRO_float7   6.3e5
#define __TEST_MACRO_float8   -6.3e5
#define __TEST_MACRO_float9   0xA.Cp5
#define __TEST_MACRO_float10  -0xA.Cp5
#define __TEST_MACRO_float11   6.3e-5
#define __TEST_MACRO_float12   -6.3e-5
#define __TEST_MACRO_float13   0xA.Cp-5
#define __TEST_MACRO_float14  -0xA.Cp-5

#define __TEST_MACRO_string1  "dfasf"

#define __TEST_MACRO_kstring2 "attr.att"k

int __iArr1[] = {-100, 100, 0b001, -0b001, 0xFF, -0xFF, __TEST_MACRO_int1, __TEST_MACRO_int2, __TEST_MACRO_int3, __TEST_MACRO_int4,  __TEST_MACRO_int5,  __TEST_MACRO_int6, };

uint __uArr2[] = {123u, 0b001u, -1u, 'X', __TEST_MACRO_uint1, __TEST_MACRO_uint2, __TEST_MACRO_uint3, __TEST_MACRO_uint4,  __TEST_MACRO_uint5, };

float __fArr2[] = {14.66, -14.66, 14., -14., .14, -.14, 6.3e5, -6.3e5, 0xA.Cp5, -0xA.Cp5, 6.3e-5, -6.3e-5, 0xA.Cp-5, -0xA.Cp-5, __TEST_MACRO_float1, __TEST_MACRO_float2, __TEST_MACRO_float3, __TEST_MACRO_float4, __TEST_MACRO_float5, __TEST_MACRO_float6, __TEST_MACRO_float7, __TEST_MACRO_float8, __TEST_MACRO_float9, __TEST_MACRO_float10, __TEST_MACRO_float11, __TEST_MACRO_float12, __TEST_MACRO_float13,  __TEST_MACRO_float14,};

string __sArr4[] = {"dfasf", __TEST_MACRO_string1};

kstring __ksArr5[] = {"attr.att"k};

void test__decl()
{
    int i1 = 100, i2 = -100, i3 = 0b01, i4 = -0b01, i5 = 0xFF, i6 = -0xFF;
    uint u1 = 123u, u2 = 0b01u, u3 = 0xFFu;
    uint u4 = 'Д';
    float f1 = 14.66, f2 = -14.66, f3 = 14., f4 = -14., f5 = .14, f6 = -.14, f7 = 6.3e5, f8 = -6.3e5, f9 = 0xA.Cp5, f10 = -0xA.Cp5, f11 = 6.3e-5, f12 = -6.3e-5, f13 = 0xA.Cp-5, f14 = -0xA.Cp-5;
    string s1 = "fds";
    kstring ks1 = "attr.att"k;
    assert(typeid(100) == typeid(int));
    assert(typeid(-100) == typeid(int));
    assert(typeid(0b01) == typeid(int));
    assert(typeid(-0b01) == typeid(int));
    assert(typeid(0xFF) == typeid(int));

    assert(typeid('Д') == typeid(uint));
	assert(typeid(123u) == typeid(uint));
	assert(typeid(0b01u) == typeid(uint));
	assert(typeid(0xFFu) == typeid(uint));

    assert(typeid(14.66) == typeid(float));
    assert(typeid(-14.66) == typeid(float));
    assert(typeid(14.) == typeid(float));
    assert(typeid(-14.) == typeid(float));
    assert(typeid(.14) == typeid(float));
    assert(typeid(-.14) == typeid(float));
    assert(typeid(6.3e5) == typeid(float));
    assert(typeid(-6.3e5) == typeid(float));
    assert(typeid(0xA.Cp5) == typeid(float));
    assert(typeid(-0xA.Cp5) == typeid(float));
    assert(typeid(6.3e-5) == typeid(float));
    assert(typeid(-6.3e-5) == typeid(float));
    assert(typeid(0xA.Cp-5) == typeid(float));
    assert(typeid(-0xA.Cp-5) == typeid(float));

    assert(typeid("fds") == typeid(string));

    assert(typeid("fds"k) == typeid(kstring));
}

void test__kstring_perf()
{
    object ob;
    string sAttr = "attr1.attr2.attr3.attr4.attr5.attr6.attr7.attr8.attr9.attr10";
    kstring ksAttr = "attr1.attr2.attr3.attr4.attr5.attr6.attr7.attr8.attr9.attr10"k;
    int i, iRDTSC1, iRDTSC2, iRDTSC3;
    iRDTSC1 = RDTSC_B();
    for(i = 0; i < 10000; i++) ob.(sAttr) = "value";
    iRDTSC1 = RDTSC_E(iRDTSC1);
    iRDTSC2 = RDTSC_B();
    for(i = 0; i < 10000; i++) ob.(ksAttr) = "value";
    iRDTSC2 = RDTSC_E(iRDTSC2);
    iRDTSC3 = RDTSC_B();
    for(i = 0; i < 10000; i++) ob.attr1.attr2.attr3.attr4.attr5.attr6.attr7.attr8.attr9.attr10 = "value";
    iRDTSC3 = RDTSC_E(iRDTSC3);
    // trace("pure: " + iRDTSC3 + ", kstring: " + iRDTSC2 + ", string: " + iRDTSC1);
    assert(iRDTSC3 < iRDTSC1);
	assert(iRDTSC2 < iRDTSC1);
}

void test__kstring()
{
    object ob;
    ob.attr = "val";
    aref ar = &ob.attr;
    string s = "val";
    kstring ks = "par.ch";
    assert(ks + s == "par.ch.val"k  && typeid(ks + s)  == typeid(kstring));
    assert(ks + ar == "par.ch.val"k && typeid(ks + ar) == typeid(kstring));
    assert(s + ks == "val.par.ch"k  && typeid(s  + ks) == typeid(kstring));
    assert(ar + ks == "val.par.ch"k && typeid(ar + ks) == typeid(kstring));
    assert(s + ks + s == ar + ks + ar);
    ks += ar;
    assert(ks == "par.ch.val"k && ks == "par.ch.val");
    ks += s;
    assert(ks == "par.ch.val.val"k && ks == "par.ch.val.val");
}

void test__arrslice()
{
    int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int b[] = a[0 .. 3];
    assert(b == {0,1,2});
    assert(__111CheckArray(&b));
    assert(__111CheckArray(a[0 .. 3]));
}
bool __111CheckArray(ref rArr)
{
    return rArr == {0,1,2};
}

void test__123arr()
{
    int a = 5;
    int b[] = {5, &a, int(&a)};
}

void test__123switch()
{
    assert(tstswiiitch(1) == 3);
    assert(tstswiiitch(2) == 1);
    assert(tstswiiitch(3) == 2);
    assert(tstswiiitch(4) == 2);
    assert(tstswiiitch(5) == 3);
    assert(tstswiiitch(6) == 1);
    assert(tstswiiitch(7) == 3);
    assert(tstswiiitch(8) == 2);
    assert(tstswiiitch(9) == 2);
}
int tstswiiitch(ref a)
{
    switch (a)
    {
        case 1:
        case 5:
        case 7:
            return 3;
        default:
        case 4:
        case 3:
            return 2;
        case 2:
        case 6:
            return 1;
    }
    return 0;
}

void test__nuullll()
{
    ref rEmpty;
    aref arEmpty;
    ref rEmptyA = &arEmpty;

    // rEmpty
    assert(rEmpty == nullptr);
    assert(rEmpty != aref(nullptr));
    assert(rEmpty is nullptr);
    assert(rEmpty !is aref);
    assert(typeid(rEmpty) == typeid(nullptr));

    // arEmpty
    assert(arEmpty == nullptr);
    assert(arEmpty == aref(nullptr));
    assert(arEmpty !is nullptr);
    assert(arEmpty is aref);
    assert(typeid(arEmpty) == typeid(aref));

    // rEmptyA
    assert(rEmptyA != nullptr);
    assert(rEmptyA == aref(nullptr));
    assert(rEmptyA !is nullptr);
    assert(rEmptyA is aref);
    assert(typeid(rEmptyA) == typeid(aref));

    // aref(nullptr)
    assert(aref(nullptr) == nullptr);
    assert(aref(nullptr) == aref(nullptr));
    assert(aref(nullptr) !is nullptr);
    assert(aref(nullptr) is aref);
    assert(typeid(aref(nullptr)) == typeid(aref));

    object ob;
    ob.attr = "abc";
    rEmptyA = &ob.attr;
    assert(arEmpty == &ob.attr);
    rEmptyA = aref(nullptr);
    assert(arEmpty == nullptr);
    arEmpty = &ob.attr;
    assert(rEmptyA == &ob.attr);
    rEmptyA = nullptr;
    assert(arEmpty == &ob.attr);
    assert(rEmptyA == rEmpty && rEmpty == nullptr);

    assert(&ob.attr == "abc");
    rEmptyA = &arEmpty;
    assert(rEmptyA == "abc");
    rEmptyA = "";
    assert(&ob.attr == "");
    assert(arEmpty == "");
    rEmptyA += "qwerty";
    assert(&ob.attr == "qwerty");
    assert(arEmpty == "qwerty");

    assert("qwerty" + 111 == rEmptyA + "111");
}
