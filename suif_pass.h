/* file "xopreplace/suif_pass.h" */
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

#ifndef XOPREPLACE_SUIF_PASS_H
#define XOPREPLACE_SUIF_PASS_H

#include <machine/copyright.h>

#ifdef USE_PRAGMA_INTERFACE
#pragma interface "xopreplace/suif_pass.h"
#endif

#include <machine/pass.h>
#include <machine/machine.h>

#include <xopreplace/xopreplace.h>

class XopreplaceSuifPass : public PipelinablePass {
  protected:
    Xopreplace xopreplace;			// the OPI-pass object

    // command-line arguments
    OptionString *file_names;	    // names of input and/or output files
    IdString o_fname;		        // optional output file name

  public:
    XopreplaceSuifPass(SuifEnv* suif_env, const IdString &name = "xopreplace");
    ~XopreplaceSuifPass(void);

    // We only need a single copy of this pass, since we should never
    // need more than one cfg2il pass in any compiler.
    Module* clone() const { return (Module*)this; }

    void initialize();
    bool parse_command_line(TokenStream* command_line_stream);
    void execute();

    void do_file_set_block(FileSetBlock*);
    void do_file_block(FileBlock*);
    void do_procedure_definition(ProcedureDefinition*);

    void finalize();
};

extern "C" void init_xopreplace(SuifEnv *suif_env);

#endif /* XOPREPLACE_SUIF_PASS_H */
