/* file "xopreplace/xopreplace.cpp" */
/*
 *     Copyright (c) 2005, 2006, 2007, 2008, 2009, 2010,
 *                   2011, 2012, 2013, 2014 Nikolaos Kavvadias
 *
 *     This software was written by Nikolaos Kavvadias, Ph.D. candidate
 *     at the Physics Department, Aristotle University of Thessaloniki,
 *     Greece (at the time).
 *
 *     Current affiliation:
 *     Dr. Nikolaos Kavvadias
 *     Independent Consultant -- Research Scientist
 *     Kornarou 12 Rd., Nea Ampliani,
 *     35100 Lamia, Greece
 *
 *     This software is provided under the terms described in
 *     the "machine/copyright.h" include file.
 */

#include <machine/copyright.h>

#ifdef USE_PRAGMA_INTERFACE
#pragma implementation "bbcount/bbcount.h"
#endif

#include <machine/machine.h>
#include <suifvm/suifvm.h>
#include <cfg/cfg.h>

#include <xopreplace/xopreplace.h>
#include "utils.h"

#ifdef USE_DMALLOC
#include <dmalloc.h>
#define new D_NEW
#endif


void
Xopreplace::do_opt_unit(OptUnit *unit)
{
  int mi_opcode;
  //
  static int procedure_count = 0;
  static int global_bb_num = 0;

  IdString name = get_name(get_proc_sym(unit));
  debug(1, "Processing procedure \"%s\"", name.chars());

  // get the body of the OptUnit
  AnyBody *orig_body = get_body(unit);

  if (is_kind_of<InstrList>(orig_body))
      return;		// nothing to do

  claim(is_kind_of<Cfg>(orig_body),
        "expected OptUnit body in Cfg form");

  // print the CFG if debugging verbosely
  if_debug(5)
      fprint(stderr, static_cast<Cfg*>(orig_body), false, true);
      
  Printer *printer = target_printer();
  printer->set_file_ptr(stdout);

  // Report name of the CFG under processing
  const char *cur_proc_name = get_name(unit).chars(); /* was cur_unit */

  // Get the body of the OptUnit
  AnyBody *cur_body = get_body(unit); /* was cur_unit */

  // Create a local copy of the input CFG
  Cfg *cfg = (Cfg *)cur_body;

  canonicalize(cfg,true,true,false);
  remove_unreachable_nodes(cfg);
  merge_node_sequences(cfg);
  optimize_jumps(cfg);


  // Iterate through the nodes of the CFG
  for (CfgNodeHandle cfg_nh=start(cfg); cfg_nh!=end(cfg); ++cfg_nh)
  {
    // Get the current node
    CfgNode* cnode = get_node(cfg, cfg_nh);

    /****************************************************************/
    /********************* INSIDE A CFGNODE *************************/
    /****************************************************************/

    for (InstrHandle h1 = instrs_start(cnode); h1 != instrs_end(cnode); h1++)
    {
      Opnd dst0,src0,src1,src2;

      Instr *mi = *h1;

      if (is_call(mi))
      {
        Sym* abs_target = get_target(mi);

	    fprint(stdout,mi);
	    printer->print_sym(abs_target);

	    ProcSym *proc = to<ProcSym>(abs_target);
	    IdString name = get_name(proc);

        fprintf(stdout,"%s\n",name.chars());

	    // Replace abs() with ABS MachSUIF IR instruction.
	    if (strcmp(name.chars(),"abs")==0)
	    {
          src1 = get_src(mi,1);
	      dst0 = get_dst(mi,0);
	      printer->print_opnd(src1);
	      printer->print_opnd(dst0);

	      Instr *mi_abs;
	      mi_abs = new_instr_alm(dst0, suifvm::ABS, src1);
	      replace(cnode,h1,mi_abs);
	    } 

        // Replace min() with MIN MachSUIF IR instruction.
	    if (strcmp(name.chars(),"min")==0)
        {
	      src1 = get_src(mi,1);
	      src2 = get_src(mi,2);
	      dst0 = get_dst(mi,0);
	      printer->print_opnd(src1);
	      printer->print_opnd(src2);
	      printer->print_opnd(dst0);

          Instr *mi_min;
          mi_min = new_instr_alm(dst0, suifvm::MIN, src1, src2);
          replace(cnode,h1,mi_min);
	    }

        // Replace max() with MAX MachSUIF IR instruction.
	    if (strcmp(name.chars(),"max")==0)
	    {
	      src1 = get_src(mi,1);
	      src2 = get_src(mi,2);
	      dst0 = get_dst(mi,0);
	      printer->print_opnd(src1);
	      printer->print_opnd(src2);
	      printer->print_opnd(dst0);

	      Instr *mi_max;
	      mi_max = new_instr_alm(dst0, suifvm::MAX, src1, src2);
	      replace(cnode,h1,mi_max);
	    }
      }
    }

    /****************************************************************/
    /****************** end of INSIDE A CFGNODE *********************/
    /****************************************************************/

  } // end of for each CFGnode
}
