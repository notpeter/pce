/*****************************************************************************
 * pce                                                                       *
 *****************************************************************************/

/*****************************************************************************
 * File name:     src/ibmpc/mda.h                                            *
 * Created:       2003-04-13 by Hampa Hug <hampa@hampa.ch>                   *
 * Last modified: 2003-08-23 by Hampa Hug <hampa@hampa.ch>                   *
 * Copyright:     (C) 2003 by Hampa Hug <hampa@hampa.ch>                     *
 *****************************************************************************/

/*****************************************************************************
 * This program is free software. You can redistribute it and / or modify it *
 * under the terms of the GNU General Public License version 2 as  published *
 * by the Free Software Foundation.                                          *
 *                                                                           *
 * This program is distributed in the hope  that  it  will  be  useful,  but *
 * WITHOUT  ANY   WARRANTY,   without   even   the   implied   warranty   of *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU  General *
 * Public License for more details.                                          *
 *****************************************************************************/

/* $Id: mda.h,v 1.3 2003/08/23 02:57:38 hampa Exp $ */


#ifndef PCE_MDA_H
#define PCE_MDA_H 1


typedef struct {
  mem_blk_t     *mem;
  mem_blk_t     *reg;

  unsigned char crtc_reg[16];

  unsigned      crtc_pos;

  terminal_t    *trm;
} mda_t;


mda_t *mda_new (terminal_t *trm);
void mda_del (mda_t *mda);

void mda_clock (mda_t *mda);

void mda_prt_state (mda_t *mda, FILE *fp);

mem_blk_t *mda_get_mem (mda_t *mda);

mem_blk_t *mda_get_reg (mda_t *mda);

void mda_mem_set_uint8 (mda_t *mda, unsigned long addr, unsigned char val);
void mda_mem_set_uint16 (mda_t *mda, unsigned long addr, unsigned short val);

void mda_reg_set_uint8 (mda_t *mda, unsigned long addr, unsigned char val);
void mda_reg_set_uint16 (mda_t *mda, unsigned long addr, unsigned short val);

unsigned char mda_reg_get_uint8 (mda_t *mda, unsigned long addr);
unsigned short mda_reg_get_uint16 (mda_t *mda, unsigned long addr);


#endif
