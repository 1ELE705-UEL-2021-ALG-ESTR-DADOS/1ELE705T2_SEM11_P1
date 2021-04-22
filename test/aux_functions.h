#pragma once
#ifndef AUX_FUNCTIONS_H
#define AUX_FUNCTIONS_H

#include "gtest/gtest.h"
#include <cstdint>

extern "C"
{
#include "../src/main.h"
}

template<size_t size>
::testing::AssertionResult ArraysMatch(const uint8_t(&expected)[size],
    const uint8_t(&actual)[size])
{
    for (size_t i(0); i < size; ++i)
    {
        if (expected[i] != actual[i])
        {
            return ::testing::AssertionFailure() <<
                "expected[" << i << "] ("
                << print_uint8_hex(expected[i]) <<
                ") != actual[" << i << "] ("
                << print_uint8_hex(actual[i]) << ")";
        }
    }

    return ::testing::AssertionSuccess();
}

template<size_t size>
::testing::AssertionResult ArraysMatch(const uint64_t(&expected)[size],
    const uint64_t(&actual)[size])
{
    for (size_t i(0); i < size; ++i)
    {
        if (expected[i] != actual[i])
        {
            return ::testing::AssertionFailure() <<
                "expected[" << i << "] ("
                << print_uint64_hex(expected[i]) <<
                ") != actual[" << i << "] ("
                << print_uint64_hex(actual[i]) << ")";
        }
    }

    return ::testing::AssertionSuccess();
}

template<size_t size>
::testing::AssertionResult ArraysMatch(const Card(&expected)[size],
    const Card(&actual)[size])
{
    for (size_t i(0); i < size; ++i)
    {
        if ((expected[i].face != actual[i].face) ||
            (expected[i].suit != actual[i].suit) ||
            (expected[i].face_number != actual[i].face_number) ||
            (expected[i].suit_number != actual[i].suit_number))
        {
            char erro[1024];
            sprintf(
                erro,
                "professor[%d] (face_number = %d, suit_number = %d)"
                " != aluno[%d] (face_number = %d, suit_number = %d)",
                (int)i, expected[i].face_number, expected[i].suit_number,
                (int)i, actual[i].face_number, actual[i].suit_number);
            return ::testing::AssertionFailure() << erro;
        }
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult ArraysMatch(const Card* expected,
    const Card* actual,
    size_t size)
{
    for (size_t i(0); i < size; ++i)
    {
        if ((expected[i].face != actual[i].face) ||
            (expected[i].suit != actual[i].suit) ||
            (expected[i].face_number != actual[i].face_number) ||
            (expected[i].suit_number != actual[i].suit_number))
        {
            char erro[1024];
            sprintf(
                erro,
                "professor[%d] (face_number = %d, suit_number = %d)"
                " != aluno[%d] (face_number = %d, suit_number = %d)",
                (int)i, expected[i].face_number, expected[i].suit_number,
                (int)i, actual[i].face_number, actual[i].suit_number);
            return ::testing::AssertionFailure() << erro;
        }
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult CartNear(Cart expected, Cart actual, double tolerance)
{
    if (fabs(expected.a - actual.a) > tolerance || fabs(expected.b - actual.b) > tolerance)
    {
        return ::testing::AssertionFailure() <<
                "expected (" << expected.a << " + j*" << expected.b << 
                ") != actual (" << actual.a << " + j*" << actual.b <<
                ")";
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult PolNear(Pol expected, Pol actual, double tolerance)
{
    if (fabs(expected.r - actual.r) > tolerance || fabs(expected.g - actual.g) > tolerance)
    {
        return ::testing::AssertionFailure() <<
            "expected (" << expected.r << " <_" << expected.g <<
            ") != actual (" << actual.r << " <_" << actual.g <<
            ")";
    }

    return ::testing::AssertionSuccess();
}

::testing::AssertionResult ComplexNumberNear(CplxNum expected, CplxNum actual, double tolerance)
{
    if (strcmp(expected.mode, cartesian) == 0 && strcmp(actual.mode, cartesian) == 0) {
        if (fabs(expected.s.cart.a - actual.s.cart.a) > tolerance || fabs(expected.s.cart.b - actual.s.cart.b) > tolerance)
        {
            return ::testing::AssertionFailure() <<
                "expected (" << expected.s.cart.a << " + j*" << expected.s.cart.b <<
                ") != actual (" << actual.s.cart.a << " + j*" << actual.s.cart.b <<
                ")";
        }
    }
    else if (strcmp(expected.mode, polar) == 0 && strcmp(actual.mode, polar) == 0) {
        if (fabs(expected.s.pol.r - actual.s.pol.r) > tolerance || fabs(expected.s.pol.g - actual.s.pol.g) > tolerance)
        {
            return ::testing::AssertionFailure() <<
                "expected (" << expected.s.pol.r << " <_" << expected.s.pol.g <<
                ") != actual (" << actual.s.pol.r << " <_" << actual.s.pol.g <<
                ")";
        }
    }
    else {
        // falha
        return ::testing::AssertionFailure() << "(expected.mode == " << expected.mode
            << " != " << "actual.mode == " << actual.mode << " )";
    }

    return ::testing::AssertionSuccess();
}

#endif // AUX_FUNCTIONS_H
