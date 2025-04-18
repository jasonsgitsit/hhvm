/*
   +----------------------------------------------------------------------+
   | HipHop for PHP                                                       |
   +----------------------------------------------------------------------+
   | Copyright (c) 2010-present Facebook, Inc. (http://www.facebook.com)  |
   +----------------------------------------------------------------------+
   | This source file is subject to version 3.01 of the PHP license,      |
   | that is bundled with this package in the file LICENSE, and is        |
   | available through the world-wide-web at the following url:           |
   | http://www.php.net/license/3_01.txt                                  |
   | If you did not receive a copy of the PHP license and are unable to   |
   | obtain it through the world-wide-web, please send a note to          |
   | license@php.net so we can mail you a copy immediately.               |
   +----------------------------------------------------------------------+
*/

#pragma once

#include <string>

#include "hphp/runtime/base/types.h"
#include "hphp/util/portability.h"

namespace HPHP {

struct FuncEmitter;
struct UnitEmitter;

namespace Verifier {

struct Graph;
struct Block;

/**
 * Pretty print the control flow graph to stdout.
 */
void printBlocks(const FuncEmitter*, const UnitEmitter*, const Graph*);

/**
 * Print one instr to stdout.  The format is similar to Unit.prettyPrint(),
 * except we annotate instructions with their flags (C|T|F).
 */
void printInstr(const UnitEmitter*, PC pc);

/**
 * Dump one whole block to a string with a header showing its out-edges,
 * and rpo_id.
 */
std::string blockToString(const Block* b, const Graph* g, const FuncEmitter* u);

/**
 * Generate a GML-format file for every Func in this unit.  The filename
 * is <md5>.gml and contains one subgraph for each Func.  GML is similar to
 * dot format, but supported by yEd, which supports interactive graph
 * browsing/editing/layout.
 * http://www.yworks.com/en/products_yed_about.html
 */
void printGml(const UnitEmitter*);

/**
 * Pretty print FuncEmitter fe in a similar fashion to pretty printing a Func.
 */
void pretty_print(const FuncEmitter* fe, const UnitEmitter* ue, std::ostream& out);

/*
 * Called to indicate a verification error.
 *
 * Currently just prints to stderr, but we might eventually want to
 * support other ways of reporting the error.
 *
 * The Func* may be nullptr.
 */
void verify_error(const UnitEmitter*, const FuncEmitter*, bool throws,
  ATTRIBUTE_PRINTF_STRING const char* fmt, ...) ATTRIBUTE_PRINTF(4,5);

}}
