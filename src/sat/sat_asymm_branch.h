/*++
Copyright (c) 2011 Microsoft Corporation

Module Name:

    sat_asymm_branch.h

Abstract:

    SAT solver asymmetric branching

Author:

    Leonardo de Moura (leonardo) 2011-05-30.

Revision History:

--*/
#ifndef SAT_ASYMM_BRANCH_H_
#define SAT_ASYMM_BRANCH_H_

#include "sat/sat_types.h"
#include "sat/sat_scc.h"
#include "util/statistics.h"
#include "util/params.h"

namespace sat {
    class solver;
    class scoped_detach;

    class asymm_branch {
        struct report;
        
        solver &   s;
        params_ref m_params;
        int64      m_counter;
        random_gen m_rand;
        unsigned   m_calls;
        
        // config
        bool       m_asymm_branch;
        bool       m_asymm_branch_all;
        int64      m_asymm_branch_limit;

        // stats
        unsigned   m_elim_literals;

        literal_vector m_pos, m_neg; // literals (complements of literals) in clauses sorted by discovery time (m_left in scc).
        literal_vector m_to_delete;
       
        struct compare_left;

        void sort(scc & scc, clause const& c);

        bool uhle(scoped_detach& scoped_d, scc & scc, clause & c);

        bool uhte(scc & scc, clause & c);

        bool re_attach(scoped_detach& scoped_d, clause& c, unsigned new_sz);

        bool process(clause & c);

        bool process2(scc& scc, clause & c);

        void process(clause_vector & c);
        
        bool process_all(clause & c);
        
        bool flip_literal_at(clause const& c, unsigned flip_index, unsigned& new_sz);
        
        bool cleanup(scoped_detach& scoped_d, clause& c, unsigned skip_index, unsigned new_sz);

        bool propagate_literal(clause const& c, literal l);

        void setup_big();

    public:
        asymm_branch(solver & s, params_ref const & p);

        void operator()(bool force = false);

        void updt_params(params_ref const & p);
        static void collect_param_descrs(param_descrs & d);

        void collect_statistics(statistics & st) const;
        void reset_statistics();

        void init_search() { m_calls = 0; }

        inline void dec(unsigned c) { m_counter -= c; }
    };

};

#endif
