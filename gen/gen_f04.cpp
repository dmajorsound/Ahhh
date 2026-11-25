// GENERATED
#include "gen.h"
namespace rs {
double Gen::F_srcitem(double l_yy) {
  double l_k = 0.0, l_ri = 0.0, l_top = 0.0; 
  return ((void)((l_ri = (-1.0))), (void)((l_k = 0.0)), (void)([&]() -> double { int n_ = rt_i32(13.0); if (n_ > 1048576) n_ = 1048576; double c_srcih = g_srcih, c_srcmy = g_srcmy; for (; n_ > 0; --n_) { (void)(((void)((l_top = ((((c_srcmy + 4.0) + (l_k * c_srcih)) + (((l_k > 0.0) ? 1.0 : 0.0) * 5.0)) + (((l_k > 4.0) ? 1.0 : 0.0) * 5.0)))), (void)((((l_yy >= l_top) && (l_yy < (l_top + c_srcih))) ? (double)(l_ri = l_k) : 0.0)), (l_k += 1.0))); } return 0.0; }()), l_ri);
}

double Gen::F_srcname(double l_k) {
  
  return (EQ(l_k, 0.0) ? (double)11729.0 : (double)(EQ(l_k, 1.0) ? (double)11245.0 : (double)(EQ(l_k, 2.0) ? (double)11730.0 : (double)(EQ(l_k, 3.0) ? (double)11731.0 : (double)(EQ(l_k, 4.0) ? (double)11715.0 : (double)(EQ(l_k, 5.0) ? (double)11732.0 : (double)(EQ(l_k, 6.0) ? (double)11721.0 : (double)(EQ(l_k, 7.0) ? (double)11733.0 : (double)(EQ(l_k, 8.0) ? (double)11734.0 : (double)(EQ(l_k, 9.0) ? (double)11735.0 : (double)(EQ(l_k, 10.0) ? (double)11736.0 : (double)(EQ(l_k, 11.0) ? (double)11737.0 : (double)11717.0))))))))))));
}

double Gen::F_srcpill(double l_x, double l_y) {
  double l_dpw = 0.0, l_hit = 0.0, l_nf = 0.0, l_on = 0.0; 
  return ((void)((l_on = ((sl[110] >= 0.5) ? 1.0 : 0.0))), (void)(F_col(g_csurf, 0.92)), (void)(F_rr(l_x, l_y, 136.0, 20.0, 7.0)), (void)(F_col(g_cbord, 1.0)), (void)(F_rro(l_x, l_y, 136.0, 20.0, 7.0)), (void)(F_col(g_csrtt, 1.0)), (void)(F_rr((l_x + 6.0), (l_y + 5.0), 3.0, 10.0, 1.5)), (void)((B(F_tgl((l_x + 6.0), (l_y + 3.0), l_on, g_csrtt)) ? (double)((void)(ASG(sl[110], (B(l_on) ? (double)0.0 : (double)1.0))), (void)(F_sauto1(110.0)), (g_click = 0.0)) : 0.0)), (void)(F_col((B(l_on) ? g_ctext : g_cmuted), 1.0)), (void)(gfx_setfont({7.0})), (void)(F_txt(11738.0, (l_x + 31.0), (l_y + 10.0), 0.0)), (void)(F_tipbox((l_x + 6.0), l_y, 48.0, 20.0, (B(l_on) ? (double)11739.0 : (double)11740.0))), (void)(F_swfmt()), (void)(ASG(g_kdim, ((B(l_on) || B(g_devm)) ? 1.0 : 0.0))), (void)((l_nf = F_hsl(86.0, (l_x + 60.0), (l_y + 1.0), 36.0, 10120.0, 10120.0, (sl[98] / 200.0), 0.5, ((B(l_on) || B(g_devm)) ? g_cdim : g_csrtt)))), (void)((g_kdim = 0.0)), (void)(F_col(((B(l_on) || B(g_devm)) ? g_cdim2 : g_ctext), 1.0)), (void)(gfx_setfont({7.0})), (void)(F_txt(90005.0, (l_x + 131.0), (l_y + 10.0), 2.0)), (void)((l_hit = F_inbox((l_x + 55.0), l_y, 80.0, 20.0))), (void)((((l_x + 200.0) <= (g_vx + (g_vw - 8.0))) ? (double)((void)((B(F_chip((l_x + 142.0), (l_y + 3.0), 58.0, 14.0, 11741.0, ((M((g_vopt + 51.0)) < 0.5) ? 1.0 : 0.0), g_csrtt)) ? (double)((void)(ASG(M((g_vopt + 51.0)), ((M((g_vopt + 51.0)) >= 0.5) ? (double)0.0 : (double)1.0))), (g_click = 0.0)) : 0.0)), F_tipbox((l_x + 142.0), (l_y + 3.0), 58.0, 14.0, ((M((g_vopt + 51.0)) < 0.5) ? (double)11742.0 : (double)11743.0))) : 0.0)), (void)((l_dpw = (((l_x + 264.0) <= (g_vx + (g_vw - 8.0))) ? (double)58.0 : (double)44.0))), (void)(((((l_x + 206.0) + l_dpw) <= (g_vx + (g_vw - 8.0))) ? (double)((void)((B(F_chip((l_x + 206.0), (l_y + 3.0), l_dpw, 14.0, ((l_dpw > 50.0) ? (double)11031.0 : (double)11744.0), ((sl[135] < 0.5) ? 1.0 : 0.0), g_csrtt)) ? (double)((void)(ASG(sl[135], ((sl[135] >= 0.5) ? (double)0.0 : (double)1.0))), (void)(slider_automate_idx({135.0})), (g_click = 0.0)) : 0.0)), F_tipbox((l_x + 206.0), (l_y + 3.0), l_dpw, 14.0, ((sl[135] < 0.5) ? (double)11745.0 : (double)11746.0))) : 0.0)), (void)(((B(g_kchg) && (!(B(l_on) || B(g_devm)))) ? (double)F_setp(98.0, (l_nf * 200.0)) : 0.0)), (void)((g_kchg = 0.0)), (void)(((B(l_hit) && NE(v_mouse_wheel, 0.0)) ? (double)(v_mouse_wheel = 0.0) : 0.0)), F_tipbox((l_x + 55.0), l_y, 80.0, 20.0, (B(g_devm) ? (double)11747.0 : (double)(B(l_on) ? (double)11748.0 : (double)11749.0))));
}

double Gen::F_srcsign(double l_fz) {
  double l_w = 0.0, l_x = 0.0, l_y = 0.0; 
  return ((void)(gfx_setfont({6.0})), (void)(sprintf({90054.0, 11750.0, F_srcname(l_fz)})), (void)((l_w = (F_tws(90054.0) + 34.0))), (void)((l_x = (g_vx + ((g_vw - 16.0) - l_w)))), (void)((l_y = (g_vy + ((g_vh - 26.0) - 26.0)))), (void)(((l_x < (g_vx + 204.0)) ? (double)(l_y -= 30.0) : 0.0)), (void)(F_col(g_csurf, 0.94)), (void)(F_rr(l_x, l_y, l_w, 20.0, 6.0)), (void)(F_col(g_csrc, 1.0)), (void)(F_rro(l_x, l_y, l_w, 20.0, 6.0)), (void)((g_icol = 1.0)), (void)(F_srcicon(l_fz, (l_x + 13.0), (l_y + 15.5), 0.55, g_ctext, g_csurf)), (void)((g_icol = 0.0)), (void)(F_col(g_ctext, 1.0)), (void)(gfx_setfont({6.0})), F_txt(90054.0, (l_x + 26.0), (l_y + 10.0), 0.0));
}

double Gen::F_srcsub(double l_k) {
  
  return (EQ(l_k, 0.0) ? (double)11751.0 : (double)(EQ(l_k, 1.0) ? (double)11752.0 : (double)(EQ(l_k, 2.0) ? (double)11753.0 : (double)(EQ(l_k, 3.0) ? (double)11754.0 : (double)(EQ(l_k, 4.0) ? (double)11755.0 : (double)(EQ(l_k, 5.0) ? (double)11756.0 : (double)(EQ(l_k, 6.0) ? (double)11757.0 : (double)(EQ(l_k, 7.0) ? (double)11758.0 : (double)(EQ(l_k, 8.0) ? (double)11759.0 : (double)(EQ(l_k, 9.0) ? (double)11760.0 : (double)(EQ(l_k, 10.0) ? (double)11761.0 : (double)(EQ(l_k, 11.0) ? (double)11762.0 : (double)11763.0))))))))))));
}

double Gen::F_srcsub2(double l_k) {
  
  return (EQ(l_k, 0.0) ? (double)11764.0 : (double)(EQ(l_k, 1.0) ? (double)11765.0 : (double)(EQ(l_k, 2.0) ? (double)11766.0 : (double)(EQ(l_k, 3.0) ? (double)11767.0 : (double)(EQ(l_k, 4.0) ? (double)11768.0 : (double)(EQ(l_k, 5.0) ? (double)11769.0 : (double)(EQ(l_k, 6.0) ? (double)11770.0 : (double)(EQ(l_k, 7.0) ? (double)11771.0 : (double)(EQ(l_k, 8.0) ? (double)11772.0 : (double)(EQ(l_k, 9.0) ? (double)11773.0 : (double)(EQ(l_k, 10.0) ? (double)11604.0 : (double)(EQ(l_k, 11.0) ? (double)11774.0 : (double)11775.0))))))))))));
}

double Gen::F_srlayout() {
  
  return ((void)(ASG(g_maxin, (rt_ceil((v_srate * 2.2)) + 8.0))), (void)(ASG(g_linemax, (rt_ceil((v_srate * 0.3)) + 8.0))), (void)(ASG(g_apmax, (rt_ceil((v_srate * 0.06)) + 8.0))), (void)(ASG(g_fdnbase, (g_ibuf + g_maxin))), (void)(ASG(g_apbase, (g_fdnbase + (8.0 * g_linemax)))), (void)(ASG(g_fdn2base, (g_apbase + (4.0 * g_apmax)))), (void)(ASG(g_dlmax, (rt_ceil((v_srate * ((v_srate > 192000.0) ? (double)1.02 : (double)4.05))) + 8.0))), (void)(ASG(g_dlmax, rt_min(g_dlmax, rt_floor((((4194240.0 - (g_fdn2base + (4.0 * g_linemax))) - g_maxin) / 2.0))))), (void)(ASG(g_dll, (g_fdn2base + (4.0 * g_linemax)))), (void)(ASG(g_dlr, (g_dll + g_dlmax))), ASG(g_sbuf, (g_dlr + g_dlmax)));
}

double Gen::F_srsetup() {
  double l_k = 0.0; 
  return ((void)((g_srini = v_srate)), (void)(F_srlayout()), (void)(memset(g_ibuf, 0.0, (g_dll - g_ibuf))), (void)(memset(g_dll, 0.0, ((2.0 * g_dlmax) + g_maxin))), (void)(ASG(g_moddep, (0.00015 * v_srate))), (void)(ASG(g_edl0, rt_min((g_edn - 1.0), rt_floor((0.0043 * v_srate))))), (void)(ASG(g_edl1, rt_min((g_edn - 1.0), rt_floor((0.0067 * v_srate))))), (void)(ASG(g_edl2, rt_min((g_edn - 1.0), rt_floor((0.0049 * v_srate))))), (void)(ASG(g_edl3, rt_min((g_edn - 1.0), rt_floor((0.0079 * v_srate))))), (void)(memset(g_edb0, 0.0, (4.0 * g_edn))), (void)(ASG(g_sm, (1.0 - rt_exp(((-1.0) / (0.03 * v_srate)))))), (void)(ASG(g_smm, (1.0 - rt_exp(((-1.0) / (0.012 * v_srate)))))), (void)(ASG(g_grk, rt_pow(10.0, (0.15 / (v_srate / 1000.0))))), (void)(ASG(g_smf, (1.0 - rt_exp(((-1.0) / (0.15 * v_srate)))))), (void)(ASG(g_smu, (1.0 - rt_exp(((-1.0) / (0.12 * v_srate)))))), (void)(ASG(g_dlsm, (1.0 - rt_exp(((-1.0) / (0.08 * v_srate)))))), (void)((g_smd = g_sm)), (void)((g_smfd = g_smf)), (void)(ASG(g_dwr1, (6.283185307179586 * (0.53 / v_srate)))), (void)(ASG(g_dwr2, (6.283185307179586 * (0.61 / v_srate)))), (void)(ASG(g_dwr3, (6.283185307179586 * (6.1 / v_srate)))), (void)(ASG(g_dwr4, (6.283185307179586 * (6.7 / v_srate)))), (void)(ASG(g_dwa, (0.001 * v_srate))), (void)(ASG(g_dfa, (8e-05 * v_srate))), (void)(ASG(g_pmdec, rt_exp(((-1.0) / (0.15 * v_srate))))), (void)(ASG(g_sm5, (1.0 - rt_exp(((-1.0) / (0.005 * v_srate)))))), (void)(ASG(g_lfc, (1.0 - rt_exp(((-6.283185307179586) * (250.0 / v_srate)))))), (void)(ASG(g_dirc, (1.0 - rt_exp(((-6.283185307179586) * (3000.0 / v_srate)))))), (void)(ASG(g_dircb, (1.0 - rt_exp(((-6.283185307179586) * (250.0 / v_srate)))))), (void)(ASG(g_xfstep, (1.0 / (0.08 * v_srate)))), (void)(ASG(g_jthr, (v_srate / 343.0))), (void)(ASG(g_jthrf, (0.003 * v_srate))), (void)(ASG(g_jts, (0.0005 * v_srate))), (void)(ASG(g_fzdr, (1.0 - (6.283185307179586 * (20.0 / v_srate))))), (void)(ASG(g_fzrel, rt_exp(((-1.0) / (0.05 * v_srate))))), (void)(ASG(g_lmla, rt_min(590.0, rt_max(1.0, rt_floor(((0.0015 * v_srate) + 0.5)))))), (void)(ASG(g_lmn, (g_lmla + 1.0))), (void)(ASG(g_lmq, (g_lmn + 2.0))), (void)((g_lmdl = g_lmb)), (void)(ASG(g_lmdr, (g_lmdl + g_lmla))), (void)(ASG(g_lmw, (g_lmdr + g_lmla))), (void)(ASG(g_lmqv, (g_lmw + g_lmn))), (void)(ASG(g_lmqt, (g_lmqv + g_lmq))), (void)(memset(g_lmdl, 0.0, (2.0 * g_lmla))), (void)((l_k = 0.0)), (void)([&]() -> double { int n_ = rt_i32(g_lmn); if (n_ > 1048576) n_ = 1048576; double c_lmw = g_lmw; for (; n_ > 0; --n_) { (void)(((void)((M((c_lmw + l_k)) = 1.0)), (l_k += 1.0))); } g_lmw = c_lmw; return 0.0; }()), (void)((g_lmsum = g_lmn)), (void)(ASG(g_lmqh, (g_lmqn = 0.0))), (void)((g_lmt = 0.0)), (void)((g_lmd = 0.0)), (void)((g_lmdd = 0.0)), (void)((g_lmr = 1.0)), (void)((g_lmga = 1.0)), (void)(ASG(g_lmrel, (1.0 - rt_exp(((-1.0) / (0.15 * v_srate)))))), (void)(ASG(v_pdc_delay, (g_lmla + 1.0))), (void)(ASG(g_crk, rt_exp(((-1.0) / (0.3 * v_srate))))), (void)(ASG(g_smq, (1.0 - rt_exp(((-1.0) / (0.005 * v_srate)))))), (void)(ASG(g_xfri, (1.0 / (0.003 * v_srate)))), (void)(ASG(g_smab, (1.0 - rt_exp(((-1.0) / (0.25 * v_srate)))))), (void)(F_fdesign(g_stc, (g_stc + 40.0), 0.0, 250.0, 2.0)), (void)(memcpy((g_stc + 5.0), g_stc, 5.0)), (void)(F_fdesign((g_stc + 10.0), (g_stc + 40.0), 1.0, 250.0, 2.0)), (void)(memcpy((g_stc + 15.0), (g_stc + 10.0), 5.0)), (void)((g_last_pkey = (-1.0))), (void)((g_last_mdkey = (-1.0))), (void)((g_last_mfp = (-1.0))), (void)((g_last_gkey = (-1.0))), (void)((g_last_gkey2 = (-1.0))), (void)((g_lastfz = (-1.0))), (void)((g_lastfzo = (-1.0))), (void)((g_lastfzn = (-1.0))), (void)(ASG(g_lastbr, (g_lastdk = (-1000.0)))), (void)(ASG(g_lastlc, (g_lasthc = (-1.0)))), (void)((g_dllkey = (-1.0))), (void)((g_fpanic = 1.0)), (g_snap = 1.0));
}

double Gen::F_sset(double l_i, double l_v) {
  
  return ((void)((((l_i >= 10.0) && (l_i <= 15.0)) ? (double)(g_gandirty = 1.0) : 0.0)), (void)((EQ(l_i, 1.0) ? (double)(sl[1] = l_v) : 0.0)), (void)((EQ(l_i, 2.0) ? (double)(sl[2] = l_v) : 0.0)), (void)((EQ(l_i, 3.0) ? (double)(sl[3] = l_v) : 0.0)), (void)((EQ(l_i, 4.0) ? (double)(sl[4] = l_v) : 0.0)), (void)((EQ(l_i, 5.0) ? (double)(sl[5] = l_v) : 0.0)), (void)((EQ(l_i, 6.0) ? (double)(sl[6] = l_v) : 0.0)), (void)((EQ(l_i, 7.0) ? (double)(sl[7] = l_v) : 0.0)), (void)((EQ(l_i, 8.0) ? (double)(sl[8] = l_v) : 0.0)), (void)((EQ(l_i, 9.0) ? (double)(sl[9] = l_v) : 0.0)), (void)((EQ(l_i, 10.0) ? (double)(sl[10] = l_v) : 0.0)), (void)((EQ(l_i, 11.0) ? (double)(sl[11] = l_v) : 0.0)), (void)((EQ(l_i, 12.0) ? (double)(sl[12] = l_v) : 0.0)), (void)((EQ(l_i, 13.0) ? (double)(sl[13] = l_v) : 0.0)), (void)((EQ(l_i, 14.0) ? (double)(sl[14] = l_v) : 0.0)), (void)((EQ(l_i, 15.0) ? (double)(sl[15] = l_v) : 0.0)), (void)((EQ(l_i, 16.0) ? (double)(sl[16] = l_v) : 0.0)), (void)((EQ(l_i, 17.0) ? (double)(sl[17] = l_v) : 0.0)), (void)((EQ(l_i, 18.0) ? (double)(sl[18] = l_v) : 0.0)), (void)((EQ(l_i, 19.0) ? (double)(sl[19] = l_v) : 0.0)), (void)((EQ(l_i, 20.0) ? (double)(sl[20] = l_v) : 0.0)), (void)((EQ(l_i, 21.0) ? (double)(sl[21] = l_v) : 0.0)), (void)((EQ(l_i, 22.0) ? (double)(sl[22] = l_v) : 0.0)), (void)((EQ(l_i, 23.0) ? (double)(sl[23] = l_v) : 0.0)), (void)((EQ(l_i, 24.0) ? (double)(sl[24] = l_v) : 0.0)), (void)((EQ(l_i, 25.0) ? (double)(sl[25] = l_v) : 0.0)), (void)((EQ(l_i, 26.0) ? (double)(sl[26] = l_v) : 0.0)), (void)((EQ(l_i, 27.0) ? (double)(sl[27] = l_v) : 0.0)), (void)((EQ(l_i, 28.0) ? (double)(sl[28] = l_v) : 0.0)), (void)((EQ(l_i, 29.0) ? (double)(sl[29] = l_v) : 0.0)), (void)((EQ(l_i, 30.0) ? (double)(sl[30] = l_v) : 0.0)), (void)((EQ(l_i, 31.0) ? (double)(sl[31] = l_v) : 0.0)), (void)((EQ(l_i, 32.0) ? (double)(sl[32] = l_v) : 0.0)), (void)((EQ(l_i, 33.0) ? (double)(sl[33] = l_v) : 0.0)), (void)((EQ(l_i, 34.0) ? (double)(sl[34] = l_v) : 0.0)), (void)((EQ(l_i, 35.0) ? (double)(sl[35] = l_v) : 0.0)), (void)((EQ(l_i, 36.0) ? (double)(sl[36] = l_v) : 0.0)), (void)((EQ(l_i, 37.0) ? (double)(sl[37] = l_v) : 0.0)), (void)((EQ(l_i, 38.0) ? (double)(sl[38] = l_v) : 0.0)), (void)((EQ(l_i, 39.0) ? (double)(sl[39] = l_v) : 0.0)), (void)((EQ(l_i, 40.0) ? (double)(sl[40] = l_v) : 0.0)), (void)((EQ(l_i, 41.0) ? (double)(sl[41] = l_v) : 0.0)), (void)((EQ(l_i, 42.0) ? (double)(sl[42] = l_v) : 0.0)), (void)((EQ(l_i, 43.0) ? (double)(sl[43] = l_v) : 0.0)), (void)((EQ(l_i, 44.0) ? (double)(sl[44] = l_v) : 0.0)), (void)((EQ(l_i, 45.0) ? (double)(sl[45] = l_v) : 0.0)), (void)((EQ(l_i, 46.0) ? (double)(sl[46] = l_v) : 0.0)), (void)((EQ(l_i, 47.0) ? (double)(sl[47] = l_v) : 0.0)), (void)((EQ(l_i, 48.0) ? (double)(sl[48] = l_v) : 0.0)), (void)((EQ(l_i, 49.0) ? (double)(sl[49] = l_v) : 0.0)), (void)((EQ(l_i, 50.0) ? (double)(sl[50] = l_v) : 0.0)), (void)((EQ(l_i, 51.0) ? (double)(sl[51] = l_v) : 0.0)), (void)((EQ(l_i, 52.0) ? (double)(sl[52] = l_v) : 0.0)), (void)((EQ(l_i, 53.0) ? (double)(sl[53] = l_v) : 0.0)), (void)((EQ(l_i, 54.0) ? (double)(sl[54] = l_v) : 0.0)), (void)((EQ(l_i, 55.0) ? (double)(sl[55] = l_v) : 0.0)), (void)((EQ(l_i, 56.0) ? (double)(sl[56] = l_v) : 0.0)), (void)((EQ(l_i, 57.0) ? (double)(sl[57] = l_v) : 0.0)), (void)((EQ(l_i, 58.0) ? (double)(sl[58] = l_v) : 0.0)), (void)((EQ(l_i, 59.0) ? (double)(sl[59] = l_v) : 0.0)), (void)((EQ(l_i, 60.0) ? (double)(sl[60] = l_v) : 0.0)), (void)((EQ(l_i, 61.0) ? (double)(sl[61] = l_v) : 0.0)), (void)((EQ(l_i, 62.0) ? (double)(sl[62] = l_v) : 0.0)), (void)((EQ(l_i, 63.0) ? (double)(sl[63] = l_v) : 0.0)), (void)((EQ(l_i, 64.0) ? (double)(sl[64] = l_v) : 0.0)), (void)((EQ(l_i, 65.0) ? (double)(sl[65] = l_v) : 0.0)), (void)((EQ(l_i, 66.0) ? (double)(sl[66] = l_v) : 0.0)), (void)((EQ(l_i, 67.0) ? (double)(sl[67] = l_v) : 0.0)), (void)((EQ(l_i, 68.0) ? (double)(sl[68] = l_v) : 0.0)), (void)((EQ(l_i, 69.0) ? (double)(sl[69] = l_v) : 0.0)), (void)((EQ(l_i, 70.0) ? (double)(sl[70] = l_v) : 0.0)), (void)((EQ(l_i, 71.0) ? (double)(sl[71] = l_v) : 0.0)), (void)((EQ(l_i, 72.0) ? (double)(sl[72] = l_v) : 0.0)), (void)((EQ(l_i, 73.0) ? (double)(sl[73] = l_v) : 0.0)), (void)((EQ(l_i, 74.0) ? (double)(sl[74] = l_v) : 0.0)), (void)((EQ(l_i, 75.0) ? (double)(sl[75] = l_v) : 0.0)), (void)((EQ(l_i, 76.0) ? (double)(sl[76] = l_v) : 0.0)), (void)((EQ(l_i, 77.0) ? (double)(sl[77] = l_v) : 0.0)), (void)((EQ(l_i, 78.0) ? (double)(sl[78] = l_v) : 0.0)), (void)((EQ(l_i, 79.0) ? (double)(sl[79] = l_v) : 0.0)), (void)((EQ(l_i, 80.0) ? (double)(sl[80] = l_v) : 0.0)), (void)((EQ(l_i, 81.0) ? (double)(sl[81] = l_v) : 0.0)), (void)((EQ(l_i, 82.0) ? (double)(sl[82] = l_v) : 0.0)), (void)((EQ(l_i, 83.0) ? (double)(sl[83] = l_v) : 0.0)), (void)((EQ(l_i, 84.0) ? (double)(sl[84] = l_v) : 0.0)), (void)((EQ(l_i, 85.0) ? (double)(sl[85] = l_v) : 0.0)), (void)((EQ(l_i, 86.0) ? (double)(sl[86] = l_v) : 0.0)), (void)((EQ(l_i, 87.0) ? (double)(sl[87] = l_v) : 0.0)), (void)((EQ(l_i, 88.0) ? (double)(sl[88] = l_v) : 0.0)), (void)((EQ(l_i, 89.0) ? (double)(sl[89] = l_v) : 0.0)), (void)((EQ(l_i, 90.0) ? (double)(sl[90] = l_v) : 0.0)), (void)((EQ(l_i, 91.0) ? (double)(sl[91] = l_v) : 0.0)), (void)((EQ(l_i, 92.0) ? (double)(sl[92] = l_v) : 0.0)), (void)((EQ(l_i, 93.0) ? (double)(sl[93] = l_v) : 0.0)), (void)((EQ(l_i, 94.0) ? (double)(sl[94] = l_v) : 0.0)), (void)((EQ(l_i, 95.0) ? (double)(sl[95] = l_v) : 0.0)), (void)((EQ(l_i, 96.0) ? (double)(sl[96] = l_v) : 0.0)), (void)((EQ(l_i, 97.0) ? (double)(sl[97] = l_v) : 0.0)), (void)((EQ(l_i, 98.0) ? (double)(sl[98] = l_v) : 0.0)), (void)((EQ(l_i, 99.0) ? (double)(sl[99] = l_v) : 0.0)), (void)((EQ(l_i, 100.0) ? (double)(sl[100] = l_v) : 0.0)), (void)((EQ(l_i, 101.0) ? (double)(sl[101] = l_v) : 0.0)), (void)((EQ(l_i, 102.0) ? (double)(sl[102] = l_v) : 0.0)), (void)((EQ(l_i, 103.0) ? (double)(sl[103] = l_v) : 0.0)), (void)((EQ(l_i, 104.0) ? (double)(sl[104] = l_v) : 0.0)), (void)((EQ(l_i, 105.0) ? (double)(sl[105] = l_v) : 0.0)), (void)((EQ(l_i, 106.0) ? (double)(sl[106] = l_v) : 0.0)), (void)((EQ(l_i, 107.0) ? (double)(sl[107] = l_v) : 0.0)), (void)((EQ(l_i, 108.0) ? (double)(sl[108] = l_v) : 0.0)), (void)((EQ(l_i, 109.0) ? (double)(sl[109] = l_v) : 0.0)), (void)((EQ(l_i, 110.0) ? (double)(sl[110] = l_v) : 0.0)), (void)((EQ(l_i, 111.0) ? (double)(sl[111] = l_v) : 0.0)), (void)((EQ(l_i, 112.0) ? (double)(sl[112] = l_v) : 0.0)), (void)((EQ(l_i, 113.0) ? (double)(sl[113] = l_v) : 0.0)), (void)((EQ(l_i, 114.0) ? (double)(sl[114] = l_v) : 0.0)), (void)((EQ(l_i, 115.0) ? (double)(sl[115] = l_v) : 0.0)), (void)((EQ(l_i, 116.0) ? (double)(sl[116] = l_v) : 0.0)), (void)((EQ(l_i, 117.0) ? (double)(sl[117] = l_v) : 0.0)), (void)((EQ(l_i, 118.0) ? (double)(sl[118] = l_v) : 0.0)), (EQ(l_i, 119.0) ? (double)(sl[119] = l_v) : 0.0));
}

double Gen::F_stcol(double l_q) {
  
  return (EQ(l_q, 7.0) ? g_cmott : (EQ(l_q, 1.0) ? g_cfltt : (EQ(l_q, 2.0) ? g_csrtt : (EQ(l_q, 3.0) ? g_cdltt : (EQ(l_q, 4.0) ? g_crmtt : (EQ(l_q, 5.0) ? g_cbartt : g_ciott))))));
}

double Gen::F_stip(double l_q) {
  
  return (EQ(l_q, 7.0) ? (double)11776.0 : (double)(EQ(l_q, 0.0) ? (double)11777.0 : (double)(EQ(l_q, 1.0) ? (double)11778.0 : (double)(EQ(l_q, 2.0) ? (double)11779.0 : (double)(EQ(l_q, 3.0) ? (double)11780.0 : (double)(EQ(l_q, 4.0) ? (double)11781.0 : (double)(EQ(l_q, 5.0) ? (double)11782.0 : (double)11783.0)))))));
}

double Gen::F_stname(double l_q) {
  
  return (EQ(l_q, 7.0) ? (double)11624.0 : (double)(EQ(l_q, 0.0) ? (double)11619.0 : (double)(EQ(l_q, 1.0) ? (double)11620.0 : (double)(EQ(l_q, 2.0) ? (double)11621.0 : (double)(EQ(l_q, 3.0) ? (double)11622.0 : (double)(EQ(l_q, 4.0) ? (double)11623.0 : (double)(EQ(l_q, 5.0) ? (double)11635.0 : (double)11626.0)))))));
}

double Gen::F_ston(double l_q) {
  
  return (EQ(l_q, 7.0) ? (double)((sl[100] >= 0.5) ? 1.0 : 0.0) : (double)(EQ(l_q, 1.0) ? (double)((sl[39] < 0.5) ? 1.0 : 0.0) : (double)(EQ(l_q, 2.0) ? (double)((sl[85] >= 0.5) ? 1.0 : 0.0) : (double)(EQ(l_q, 3.0) ? (double)((sl[65] >= 0.5) ? 1.0 : 0.0) : (double)(EQ(l_q, 4.0) ? (double)((sl[36] < 0.5) ? 1.0 : 0.0) : (double)(EQ(l_q, 5.0) ? (double)((sl[41] >= 0.5) ? 1.0 : 0.0) : (double)1.0))))));
}

double Gen::F_strtob(double l_st, double l_b) {
  double l_i = 0.0, l_n = 0.0; 
  return ((void)((l_n = rt_min(63.0, strlen(l_st)))), (void)((l_i = 0.0)), (void)([&]() -> double { int n_ = rt_i32(l_n); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)(ASG(M((l_b + l_i)), str_getchar({l_st, l_i, 25461.0}))), (l_i += 1.0))); } return 0.0; }()), (void)((M((l_b + l_n)) = 0.0)), l_b);
}

double Gen::F_stsolo(double l_q) {
  
  return (EQ(l_q, 2.0) ? (double)1.0 : (double)(EQ(l_q, 3.0) ? (double)2.0 : (double)(EQ(l_q, 4.0) ? (double)3.0 : (double)0.0)));
}

double Gen::F_ststat(double l_q) {
  double l_e = 0.0, l_i = 0.0, l_t = 0.0; 
  return (EQ(l_q, 7.0) ? (double)F_mtstat() : (double)(EQ(l_q, 0.0) ? (double)((void)(((sl[40] <= (-71.9)) ? (double)strcpy(90016.0, 11784.0) : (double)((std::fabs(sl[40]) < 0.05) ? (double)strcpy(90016.0, 10230.0) : (double)sprintf({90016.0, 10501.0, sl[40]})))), ((sl[110] >= 0.5) ? (double)((std::fabs(sl[40]) < 0.05) ? (double)strcpy(90016.0, 11738.0) : (double)strcat(90016.0, 11785.0)) : 0.0)) : (double)(EQ(l_q, 1.0) ? (double)((sl[39] >= 0.5) ? (double)strcpy(90016.0, 10063.0) : (double)(((sl[24] >= 0.5) && (sl[27] >= 0.5)) ? (double)sprintf({90016.0, 10487.0, sl[25], (sl[28] / 1000.0)}) : (double)((sl[24] >= 0.5) ? (double)sprintf({90016.0, 10488.0, sl[25]}) : (double)((sl[27] >= 0.5) ? (double)sprintf({90016.0, 10489.0, (sl[28] / 1000.0)}) : (double)strcpy(90016.0, 11786.0))))) : (double)(EQ(l_q, 2.0) ? (double)((sl[85] < 0.5) ? (double)strcpy(90016.0, 10063.0) : (double)((void)(strcpy(90016.0, F_srcname(g_fzsel))), (void)((l_e = 0.0)), (void)((l_i = 47.0)), (void)([&]() -> double { int n_ = rt_i32(13.0); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)(((std::fabs(SL(l_i)) > 0.0005) ? (double)(l_e = 1.0) : 0.0)), (l_i += 1.0))); } return 0.0; }()), (void)((B(l_e) ? (double)strcat(90016.0, 10310.0) : 0.0)), (((g_fzsel > 0.0) && ((((sl[111] > 0.05) || (sl[112] > 0.05)) || (sl[113] > 0.05)) || (sl[114] >= 0.5))) ? (double)strcat(90016.0, 11787.0) : 0.0))) : (double)(EQ(l_q, 3.0) ? (double)((sl[65] < 0.5) ? (double)strcpy(90016.0, 10063.0) : (double)((void)((l_t = F_dpmatch())), ((l_t >= 0.0) ? (double)strcpy(90016.0, F_dpname(l_t)) : (double)(B(g_gdtm) ? (double)((void)(strcpy(90016.0, 10804.0)), (void)(strcat(90016.0, F_dnname(sl[72]))), (void)(strcat(90016.0, 10805.0)), strcat(90016.0, F_dnname((B(g_gdlt) ? sl[72] : sl[73])))) : (double)sprintf({90016.0, 10807.0, g_gtl, g_gtr}))))) : (double)(EQ(l_q, 4.0) ? (double)((sl[36] >= 0.5) ? (double)strcpy(90016.0, 10063.0) : (double)strcpy(90016.0, 90011.0)) : (double)(EQ(l_q, 5.0) ? (double)((void)((l_t = rt_floor((sl[41] + 0.5)))), (EQ(l_t, 0.0) ? (double)strcpy(90016.0, 10063.0) : (double)(EQ(l_t, 1.0) ? (double)strcpy(90016.0, 10017.0) : (double)((sl[43] >= 0.5) ? (double)sprintf({90016.0, (EQ(l_t, 2.0) ? (double)11788.0 : (double)11789.0), (sl[43] * 0.9)}) : (double)strcpy(90016.0, (EQ(l_t, 2.0) ? (double)10016.0 : (double)10018.0)))))) : (double)((sl[22] <= (-71.9)) ? (double)strcpy(90016.0, 11784.0) : (double)((std::fabs(sl[22]) < 0.05) ? (double)strcpy(90016.0, 10230.0) : (double)sprintf({90016.0, 10501.0, sl[22]}))))))))));
}

double Gen::F_sttog(double l_q) {
  
  return ((void)((EQ(l_q, 1.0) ? (double)((void)(ASG(sl[39], ((sl[39] >= 0.5) ? (double)0.0 : (double)1.0))), F_sauto1(39.0)) : 0.0)), (void)((EQ(l_q, 2.0) ? (double)((void)(ASG(sl[85], ((sl[85] >= 0.5) ? (double)0.0 : (double)1.0))), F_sauto1(85.0)) : 0.0)), (void)((EQ(l_q, 3.0) ? (double)((void)(ASG(sl[65], ((sl[65] >= 0.5) ? (double)0.0 : (double)1.0))), F_sauto1(65.0)) : 0.0)), (void)((EQ(l_q, 4.0) ? (double)((void)(ASG(sl[36], ((sl[36] >= 0.5) ? (double)0.0 : (double)1.0))), F_sauto1(36.0)) : 0.0)), (void)((EQ(l_q, 5.0) ? (double)F_bartog() : 0.0)), (EQ(l_q, 7.0) ? (double)F_setp(100.0, ((sl[100] >= 0.5) ? (double)0.0 : (double)1.0)) : 0.0));
}

double Gen::F_swfmt() {
  
  return ((void)(((M((g_vopt + 50.0)) >= 0.5) ? (double)sprintf({90005.0, 10288.0, (sl[98] / 100.0)}) : (double)sprintf({90005.0, 10189.0, sl[98]}))), F_kmap(0.0, 0.0, 200.0, 1.0));
}

double Gen::F_swunit(double l_x, double l_y) {
  double l_u = 0.0; 
  return ((void)((l_u = ((M((g_vopt + 50.0)) >= 0.5) ? 1.0 : 0.0))), (void)((B(F_chip(l_x, l_y, 14.0, 11.0, 11790.0, ((!B(l_u)) ? 1.0 : 0.0), g_csrtt)) ? (double)((void)((M((g_vopt + 50.0)) = 0.0)), (g_click = 0.0)) : 0.0)), (void)((B(F_chip((l_x + 16.0), l_y, 14.0, 11.0, 11791.0, l_u, g_csrtt)) ? (double)((void)((M((g_vopt + 50.0)) = 1.0)), (g_click = 0.0)) : 0.0)), F_tipbox(l_x, l_y, 30.0, 11.0, 11792.0));
}

double Gen::F_tabc(double l_id) {
  
  return (EQ(l_id, 15.0) ? g_cfftt : (EQ(l_id, 1.0) ? g_crmtt : (EQ(l_id, 3.0) ? g_csrtt : (EQ(l_id, 4.0) ? g_cwaltt : (EQ(l_id, 5.0) ? g_cbartt : (EQ(l_id, 6.0) ? g_cfltt : (EQ(l_id, 7.0) ? g_ciott : (EQ(l_id, 14.0) ? g_cmott : g_cdltt))))))));
}

double Gen::F_tabname(double l_id) {
  
  return (EQ(l_id, 15.0) ? (double)10415.0 : (double)(EQ(l_id, 1.0) ? (double)10694.0 : (double)(EQ(l_id, 3.0) ? (double)10602.0 : (double)(EQ(l_id, 4.0) ? (double)(B(g_isfree) ? (double)10890.0 : (double)10891.0) : (double)(EQ(l_id, 5.0) ? (double)10423.0 : (double)(EQ(l_id, 6.0) ? (double)10926.0 : (double)(EQ(l_id, 7.0) ? (double)10159.0 : (double)(EQ(l_id, 14.0) ? (double)10965.0 : (double)10798.0))))))));
}

double Gen::F_taborder() {
  double l_n = 0.0; 
  return ((void)((l_n = 0.0)), (void)(((sl[30] < 0.5) ? (double)((void)((M((g_tbo + l_n)) = 6.0)), (l_n += 1.0)) : 0.0)), (void)((M((g_tbo + l_n)) = 3.0)), (void)((M((g_tbo + (l_n + 1.0))) = 10.0)), (void)((M((g_tbo + (l_n + 2.0))) = 1.0)), (void)((M((g_tbo + (l_n + 3.0))) = 15.0)), (void)((M((g_tbo + (l_n + 4.0))) = 4.0)), (void)((M((g_tbo + (l_n + 5.0))) = 5.0)), (void)((l_n += 6.0)), (void)((M((g_tbo + l_n)) = 14.0)), (void)((l_n += 1.0)), (void)(((sl[30] >= 0.5) ? (double)((void)((M((g_tbo + l_n)) = 6.0)), (l_n += 1.0)) : 0.0)), (void)((M((g_tbo + l_n)) = 7.0)), (l_n + 1.0));
}

double Gen::F_tabq(double l_id) {
  
  return (EQ(l_id, 1.0) ? (double)4.0 : (double)(EQ(l_id, 3.0) ? (double)2.0 : (double)(EQ(l_id, 5.0) ? (double)5.0 : (double)(EQ(l_id, 6.0) ? (double)1.0 : (double)(EQ(l_id, 10.0) ? (double)3.0 : (double)(EQ(l_id, 14.0) ? (double)7.0 : (double)0.0))))));
}

double Gen::F_tabref(double l_id) {
  
  return (EQ(l_id, 15.0) ? (double)11793.0 : (double)(EQ(l_id, 1.0) ? (double)10029.0 : (double)(EQ(l_id, 3.0) ? (double)11245.0 : (double)(EQ(l_id, 4.0) ? (double)11794.0 : (double)(EQ(l_id, 5.0) ? (double)11795.0 : (double)(EQ(l_id, 6.0) ? (double)11796.0 : (double)(EQ(l_id, 7.0) ? (double)11797.0 : (double)(EQ(l_id, 14.0) ? (double)11798.0 : (double)11799.0))))))));
}

double Gen::F_tabrow() {
  double t_stw2 = 0.0, t_tbcut = 0.0, t_tbendx = 0.0, t_tbmin = 0.0, t_tbnv = 0.0, t_tbnw = 0.0, t_tbtot = 0.0; double l_act = 0.0, l_c = 0.0, l_cy = 0.0, l_dhit = 0.0, l_hit = 0.0, l_i = 0.0, l_id = 0.0, l_n = 0.0, l_nw = 0.0, l_on = 0.0, l_q = 0.0, l_shit = 0.0, l_sq = 0.0, l_sx = 0.0, l_tdq = 0.0, l_w = 0.0, l_x = 0.0; 
  return ((void)((l_n = F_taborder())), (void)((l_cy = (g_tby + ((g_tbh / 2.0) - 1.0)))), (void)((l_x = ASG(g_tbx0, rt_max(8.0, (((g_goxz - g_goxn) / g_gsn) + 0.2))))), (void)((l_i = 0.0)), (void)((t_tbtot = 0.0)), (void)((t_tbmin = 0.0)), (void)([&]() -> double { int n_ = rt_i32(l_n); if (n_ > 1048576) n_ = 1048576; double c_tbo = g_tbo; for (; n_ > 0; --n_) { (void)(((void)((l_id = M((c_tbo + l_i)))), (void)(gfx_setfont({7.0})), (void)((t_stw2 = [&]() -> double { const double a0_ = F_tabref(l_id); return F_tws(a0_); }())), (void)(gfx_setfont({2.0})), (void)((t_tbnw = rt_max([&]() -> double { const double a0_ = F_tabname(l_id); return F_tws(a0_); }(), t_stw2))), (void)((t_tbtot += (((((28.0 + t_tbnw) + (([&]() -> double { const double a0_ = F_tabq(l_id); return F_stsolo(a0_); }() > 0.0) ? (double)22.0 : (double)0.0)) + 2.0) + 3.0) + 7.0))), (void)((t_tbmin += rt_max(0.0, (t_tbnw - [&]() -> double { const double a0_ = F_tabname(l_id); return F_tws(a0_); }())))), (l_i += 1.0))); } return 0.0; }()), (void)((t_tbcut = rt_min(1.0, (rt_max(0.0, ((t_tbtot - 7.0) - (((g_wt - 8.0) - g_tbx0) - ((g_stpwt > 0.0) ? (double)(g_stpwt + 30.0) : (double)0.0)))) / rt_max(1.0, t_tbmin))))), (void)((l_i = 0.0)), (void)([&]() -> double { int n_ = rt_i32(l_n); if (n_ > 1048576) n_ = 1048576; double c_camb = g_camb, c_cbord = g_cbord, c_cctlon = g_cctlon, c_cdim2 = g_cdim2, c_chair = g_chair, c_click = g_click, c_cline = g_cline, c_cmuted = g_cmuted, c_csurf = g_csurf, c_ctext = g_ctext, c_snlast = g_snlast, c_solom = g_solom, c_szoom = g_szoom, c_tabsel = g_tabsel, c_tay = g_tay, c_tbaw = g_tbaw, c_tbax = g_tbax, c_tbh = g_tbh, c_tbo = g_tbo, c_tby = g_tby, c_tipforce = g_tipforce, c_tipon = g_tipon, c_tipstr = g_tipstr, c_tipx = g_tipx, c_tipy = g_tipy; for (; n_ > 0; --n_) { (void)(((void)((l_id = M((c_tbo + l_i)))), (void)((l_q = F_tabq(l_id))), (void)((l_c = F_tabc(l_id))), (void)((l_act = (EQ(l_id, c_tabsel) ? 1.0 : 0.0))), (void)((l_on = (EQ(l_id, 15.0) ? (double)g_isfree : (double)((EQ(l_id, 4.0) && B(g_isfree)) ? (double)(((M((g_vopt + (g_rfb + 14.0))) < 0.5) && ((M((g_vopt + g_rfb)) >= 0.5) || (M((g_vopt + (g_rfb + 6.0))) >= 0.5))) ? 1.0 : 0.0) : (double)((l_q > 0.0) ? (double)(EQ(l_id, 1.0) ? (double)((B(F_ston(l_q)) && (!B(g_isfree))) ? 1.0 : 0.0) : (double)F_ston(l_q)) : (double)1.0))))), (void)((l_sq = ((l_q > 0.0) ? (double)F_stsolo(l_q) : (double)0.0))), (void)((l_tdq = ((((l_q > 0.0) || EQ(l_id, 15.0)) || (EQ(l_id, 4.0) && B(g_isfree))) ? 1.0 : 0.0))), (void)(((l_q > 0.0) ? (double)F_ststat((EQ(l_q, 6.0) ? (double)6.0 : (double)l_q)) : (double)(EQ(l_id, 7.0) ? (double)F_ststat(6.0) : (double)(EQ(l_id, 14.0) ? (double)F_mtstat() : (double)(EQ(l_id, 15.0) ? (double)strcpy(90016.0, (B(g_isfree) ? (double)11793.0 : (double)10063.0)) : (double)((EQ(l_id, 4.0) && B(g_isfree)) ? (double)sprintf({90016.0, 11800.0, F_rflname(M((g_vopt + g_rfb))), F_rflname(M((g_vopt + (g_rfb + 6.0))))}) : (double)strcpy(90016.0, 90022.0))))))), (void)(gfx_setfont({7.0})), (void)((t_stw2 = [&]() -> double { const double a0_ = F_tabref(l_id); return F_tws(a0_); }())), (void)(gfx_setfont({2.0})), (void)((l_nw = rt_max([&]() -> double { const double a0_ = F_tabname(l_id); return F_tws(a0_); }(), t_stw2))), (void)((l_nw -= ((l_nw - [&]() -> double { const double a0_ = F_tabname(l_id); return F_tws(a0_); }()) * t_tbcut))), (void)((l_w = (((28.0 + l_nw) + ((l_sq > 0.0) ? (double)22.0 : (double)0.0)) + 2.0))), (void)((l_hit = F_inbox(l_x, (c_tby + 2.0), l_w, c_tbh))), (void)((l_dhit = ((B(l_tdq) && ((rt_sqr((g_mx - (l_x + 12.0))) + rt_sqr((g_my - l_cy))) < 56.0)) ? 1.0 : 0.0))), (void)((l_sx = (l_x + (l_w - 24.0)))), (void)((l_shit = (((l_sq > 0.0) && B(F_inbox((l_sx - 2.0), (l_cy - 9.0), 20.0, 18.0))) ? 1.0 : 0.0))), (void)((B(l_act) ? (double)((void)((c_tbax = l_x)), (void)((c_tbaw = l_w)), (void)(F_col(l_c, 1.0)), (B(c_cctlon) ? (double)((void)(F_rr((l_x - 1.2), (c_tby - 1.2), (l_w + 2.4), (c_tbh + 6.6), 7.2)), (void)([&]() -> double { const double a0_ = (B(c_szoom) ? (double)c_csurf : (double)F_mixc(c_csurf, l_c, (EQ(c_cctlon, 2.0) ? (double)0.22 : (double)0.16))); return F_col(a0_, 1.0); }()), (void)(F_rr(l_x, c_tby, l_w, (c_tbh + 6.0), 6.0)), F_r(l_x, (c_tay - 2.0), l_w, 6.0)) : (double)((void)(F_rr((l_x - 1.6), (c_tby - 1.6), (l_w + 3.2), (c_tbh + 7.0), 7.4)), (void)(F_col(c_csurf, 1.0)), (void)(F_rr(l_x, c_tby, l_w, (c_tbh + 6.0), 6.0)), F_r(l_x, (c_tay - 2.0), l_w, 6.0)))) : (double)((void)(F_col((B(l_hit) ? c_chair : c_cline), 1.0)), F_rr(l_x, (c_tby + 3.0), l_w, (c_tbh - 3.0), 6.0)))), (void)((B(l_tdq) ? (double)(B(l_on) ? (double)((void)(F_col(l_c, 1.0)), F_ci((l_x + 12.0), l_cy, 4.8, 1.0)) : (double)((void)(F_col(c_csurf, 1.0)), (void)(F_ci((l_x + 12.0), l_cy, 4.8, 1.0)), (void)(F_col((B(l_dhit) ? c_ctext : c_cdim2), 1.0)), (void)(F_ci((l_x + 12.0), l_cy, 4.8, 0.0)), F_ci((l_x + 12.0), l_cy, 4.0, 0.0))) : (double)((void)(F_col(l_c, 1.0)), F_rr((l_x + 9.5), (l_cy - 6.0), 3.0, 12.0, 1.5)))), (void)(F_col((B(l_act) ? c_ctext : (B(l_on) ? c_cmuted : c_cdim2)), 1.0)), (void)(gfx_setfont({2.0})), (void)([&]() -> double { const double a0_ = F_tabname(l_id); const double a1_ = (l_x + 24.0); const double a2_ = (l_cy - 5.0); return F_txt(a0_, a1_, a2_, 0.0); }()), (void)(F_col((B(l_on) ? c_cmuted : c_cdim2), 1.0)), (void)(gfx_setfont({7.0})), (void)(F_txtfit(90016.0, (l_x + 24.0), (l_cy + 7.0), l_nw)), (void)(((l_sq > 0.0) ? (double)((void)((EQ(c_solom, l_sq) ? (double)((void)(F_col(c_camb, 1.0)), (void)(F_rr(l_sx, (l_cy - 7.0), 16.0, 14.0, 4.0)), F_col(16777215.0, 1.0)) : (double)((void)(F_col((B(l_shit) ? c_ctext : c_cbord), 1.0)), (void)(F_rro(l_sx, (l_cy - 7.0), 16.0, 14.0, 4.0)), F_col((B(l_shit) ? c_ctext : c_cmuted), 1.0)))), (void)(gfx_setfont({6.0})), F_txt(10158.0, (l_sx + 8.0), l_cy, 1.0)) : 0.0)), (void)(((B(c_click) && (B(l_shit) || ((B(l_hit) && B(rt_and(v_mouse_cap, 24.0))) && (l_sq > 0.0)))) ? (double)((void)((EQ(c_solom, l_sq) ? (c_solom = 0.0) : ((void)(((!B((EQ(l_id, 1.0) ? (double)F_ston(l_q) : (double)l_on))) ? (double)F_sttog(l_q) : 0.0)), (c_solom = l_sq)))), (c_click = 0.0)) : (double)((B(c_click) && B(l_dhit)) ? (double)((void)(((EQ(l_id, 4.0) && B(g_isfree)) ? (double)(B(l_on) ? (double)(M((g_vopt + (g_rfb + 14.0))) = 1.0) : (double)((void)((M((g_vopt + (g_rfb + 14.0))) = 0.0)), (((M((g_vopt + g_rfb)) < 0.5) && (M((g_vopt + (g_rfb + 6.0))) < 0.5)) ? (double)F_rflset(0.0, 1.0) : 0.0))) : (double)((EQ(l_id, 15.0) || (EQ(l_id, 1.0) && B(g_isfree))) ? (double)((void)(F_modeset(((EQ(l_id, 15.0) && B(g_isfree)) ? (double)0.0 : (double)(EQ(l_id, 1.0) ? (double)0.0 : (double)1.0)))), (c_snlast = 0.0)) : (double)F_sttog(l_q)))), (c_click = 0.0)) : (double)((B(c_click) && B(l_hit)) ? (double)((void)((M((g_vopt + 46.0)) = l_id)), (c_click = 0.0)) : 0.0)))), (void)((B(l_shit) ? (double)((void)((c_tipon = 1.0)), (void)((c_tipforce = 0.0)), (void)(ASG(c_tipx, (l_sx + 8.0))), (void)(ASG(c_tipy, (c_tby - 12.0))), ASG(c_tipstr, (EQ(c_solom, l_sq) ? (double)11801.0 : (double)(EQ(l_sq, 1.0) ? (double)11802.0 : (double)(EQ(l_sq, 2.0) ? (double)11803.0 : (double)11804.0))))) : (double)(B(l_dhit) ? (double)((void)((c_tipon = 1.0)), (void)((c_tipforce = 0.0)), (void)(ASG(c_tipx, (l_x + 12.0))), (void)(ASG(c_tipy, (c_tby - 12.0))), ASG(c_tipstr, ((EQ(l_id, 4.0) && B(g_isfree)) ? (double)(B(l_on) ? (double)11805.0 : (double)11806.0) : (double)(EQ(l_id, 15.0) ? (double)(B(g_isfree) ? (double)10810.0 : (double)11807.0) : (double)((EQ(l_id, 1.0) && B(g_isfree)) ? (double)11808.0 : (double)(B(l_on) ? (double)11809.0 : (double)11810.0)))))) : (double)(B(l_hit) ? (double)((void)((c_tipon = 1.0)), (void)(ASG(c_tipx, (l_x + (l_w / 2.0)))), (void)(ASG(c_tipy, (c_tby - 12.0))), ASG(c_tipstr, ((l_sq > 0.0) ? (double)11811.0 : (double)11812.0))) : 0.0)))), (void)((l_x += (l_w + 3.0))), (void)(((l_i < (l_n - 1.0)) ? (double)((void)(F_col(c_cdim2, 1.0)), (void)(gfx_setfont({6.0})), (void)(F_txt((EQ(l_id, 4.0) ? (double)11813.0 : (double)(EQ(l_id, 15.0) ? (double)11279.0 : (double)(EQ(l_id, 1.0) ? (double)11814.0 : (double)(EQ(l_id, 7.0) ? (double)11815.0 : (double)11279.0)))), (l_x + 2.0), l_cy, 1.0)), (l_x += 7.0)) : 0.0)), (l_i += 1.0))); } g_click = c_click; g_snlast = c_snlast; g_solom = c_solom; g_tbaw = c_tbaw; g_tbax = c_tbax; g_tipforce = c_tipforce; g_tipon = c_tipon; g_tipstr = c_tipstr; g_tipx = c_tipx; g_tipy = c_tipy; return 0.0; }()), (void)((t_tbendx = l_x)), (void)(((g_stpwt > 0.0) ? (double)((void)(gfx_setfont({7.0})), (void)((l_x = ((((g_wt - 14.0) - F_tws(11816.0)) - 14.0) - g_stpwt))), (void)(F_col(g_camb, 1.0)), (void)(F_rr(l_x, (l_cy - 8.0), g_stpwt, 16.0, 8.0)), (void)(F_col(16777215.0, 1.0)), (void)(gfx_setfont({6.0})), (void)(F_txt(90015.0, (l_x + 9.0), l_cy, 0.0)), (void)(F_lnw((l_x + (g_stpwt - 13.0)), (l_cy - 2.5), (l_x + (g_stpwt - 8.0)), (l_cy + 2.5), 1.3)), (void)(F_lnw((l_x + (g_stpwt - 13.0)), (l_cy + 2.5), (l_x + (g_stpwt - 8.0)), (l_cy - 2.5), 1.3)), (void)(((B(g_click) && B(F_inbox(l_x, (l_cy - 9.0), g_stpwt, 18.0))) ? (double)((void)(((g_solom > 0.0) ? (g_solom = 0.0) : (M((g_vopt + 18.0)) = 0.0))), (g_click = 0.0)) : 0.0)), F_tipbox(l_x, (l_cy - 9.0), g_stpwt, 18.0, ((g_solom > 0.0) ? (double)11817.0 : (double)11818.0))) : 0.0)), (void)(sprintf({90055.0, 11819.0, ((v_pdc_delay / v_srate) * 1000.0)})), (void)(gfx_setfont({7.0})), (void)((((t_tbendx + 12.0) < ((g_wt - 14.0) - F_tws(90055.0))) ? (double)((void)(F_col(g_cmuted, 1.0)), (void)(F_txt(90055.0, (g_wt - 14.0), l_cy, 2.0)), [&]() -> double { const double a0_ = ((g_wt - 14.0) - F_tws(90055.0)); const double a1_ = (g_tby + 2.0); const double a2_ = F_tws(90055.0); return F_tipbox(a0_, a1_, a2_, g_tbh, 11820.0); }()) : 0.0)), (void)((l_hit = (((((((!B(g_vhid)) && (!B(g_vgone))) && (g_my >= (g_vy + g_vh))) && (g_my < g_tby)) && (g_mx >= g_vx)) && (g_mx < (g_vx + g_vw))) ? 1.0 : 0.0))), (void)(((B(g_click) && B(l_hit)) ? (double)((void)((((time_precise() - g_tbdt) < 0.35) ? ((void)((M((g_vopt + 47.0)) = 0.0)), (void)((M((g_vopt + 48.0)) = 0.0)), (void)((M((g_vopt + 35.0)) = 0.0)), (g_tbdrag = 0.0)) : ((void)((g_tbdrag = 1.0)), ASG(g_tbdy, (g_my - g_vh))))), (void)(ASG(g_tbdt, time_precise())), (g_click = 0.0)) : 0.0)), (void)((B(g_tbdrag) ? (double)(B(rt_and(v_mouse_cap, 1.0)) ? (double)((void)((t_tbnv = rt_floor((rt_max((g_vfh + 30.0), rt_min(g_tabmax, (g_my - g_tbdy))) + 0.5)))), ((((M((g_vopt + 48.0)) >= 0.5) || (M((g_vopt + 35.0)) >= 0.99)) && (std::fabs((t_tbnv - g_vh)) < 1.0)) ? (double)0.0 : (double)((void)((M((g_vopt + 47.0)) = t_tbnv)), (void)((M((g_vopt + 35.0)) = 0.0)), (M((g_vopt + 48.0)) = 0.0)))) : (double)(g_tbdrag = 0.0)) : 0.0)), (void)((((!B(g_vhid)) && (!B(g_vgone))) ? (double)((void)(F_col(((B(l_hit) || B(g_tbdrag)) ? g_ctext : g_cdim2), 1.0)), F_rr((g_vx + ((g_vw / 2.0) - 18.0)), ((g_vy + g_vh) + 4.0), 36.0, 3.0, 1.5)) : 0.0)), (B(l_hit) ? (double)((void)((g_tipon = 1.0)), (void)(ASG(g_tipx, (g_vx + (g_vw / 2.0)))), (void)(ASG(g_tipy, (g_tby - 14.0))), (g_tipstr = 11821.0)) : 0.0));
}

double Gen::F_tabstep(double l_d) {
  double l_i = 0.0, l_k = 0.0, l_n = 0.0; 
  return ((void)((l_n = F_taborder())), (void)((l_k = 0.0)), (void)((l_i = 0.0)), (void)([&]() -> double { int n_ = rt_i32(l_n); if (n_ > 1048576) n_ = 1048576; double c_tabsel = g_tabsel, c_tbo = g_tbo; for (; n_ > 0; --n_) { (void)(((void)((EQ(M((c_tbo + l_i)), c_tabsel) ? (double)(l_k = l_i) : 0.0)), (l_i += 1.0))); } return 0.0; }()), ASG(M((g_vopt + 46.0)), M((g_tbo + rt_mod(((l_k + l_d) + l_n), l_n)))));
}

double Gen::F_tgl(double l_x, double l_y, double l_on, double l_c) {
  double l_cx = 0.0, l_cy = 0.0, l_hit = 0.0; 
  return (((void)((B(g_cctlon) ? (double)(l_c = (B(l_on) ? g_cacto : g_cctl)) : 0.0)), (void)((l_hit = F_inbox((l_x - 3.0), (l_y - 3.0), 32.0, 20.0))), (void)((l_cx = (l_x + 15.0))), (void)((l_cy = (l_y + 7.0))), (void)((B(l_on) ? (double)((void)(F_col(l_c, 1.0)), (void)(F_sddisc(l_cx, l_cy, 7.0)), F_col((B(g_monoon) ? (double)g_cbg : (double)((B(g_cctlon) && B(g_darkmode)) ? (double)925491.0 : (double)16777215.0)), 1.0)) : (double)((void)((B(l_hit) ? (double)((void)(F_col(g_chair, 1.0)), F_sddisc(l_cx, l_cy, 7.0)) : 0.0)), (void)(F_col((B(l_hit) ? g_cdim2 : g_cbord), 1.0)), (void)(F_arcs(l_cx, l_cy, 6.5, 0.0, 6.283185307179586, 0.9)), F_col((B(l_hit) ? g_ctext : g_cdim2), 1.0)))), (void)(F_sdb0()), (void)(F_sdarc(l_cx, (l_cy + 0.45), 3.3, 0.72, 5.5631853071795865)), (void)(F_sdseg(l_cx, (l_cy - 4.1), l_cx, (l_cy - 0.8))), (void)(F_sddraw(1.05)), (B(g_click) && B(l_hit))) ? 1.0 : 0.0);
}

double Gen::F_thf(double l_u) {
  double l_e = 0.0; 
  return ((void)((l_e = rt_exp(rt_min(40.0, rt_max((-40.0), (2.0 * l_u)))))), ((l_e - 1.0) / (l_e + 1.0)));
}

double Gen::F_tileicon(double l_i, double l_x, double l_y) {
  
  return (EQ(l_i, 0.0) ? (double)((void)(F_lnw(l_x, (l_y + 10.0), (l_x + 16.0), (l_y + 10.0), 1.0)), (void)(F_lnw((l_x + 2.0), (l_y + 10.0), (l_x + 4.5), (l_y + 4.0), 1.0)), (void)(F_lnw((l_x + 4.5), (l_y + 4.0), (l_x + 11.0), (l_y + 4.0), 1.0)), (void)(F_lnw((l_x + 11.0), (l_y + 4.0), (l_x + 14.0), (l_y + 10.0), 1.0)), (void)(F_cif((l_x + 4.5), (l_y + 11.5), 1.8, 0.0)), F_cif((l_x + 11.5), (l_y + 11.5), 1.8, 0.0)) : (double)(EQ(l_i, 1.0) ? (double)((void)(F_lnw((l_x + 1.0), (l_y + 3.0), (l_x + 1.0), (l_y + 13.0), 1.0)), (void)(F_lnw((l_x + 1.0), (l_y + 13.0), (l_x + 15.0), (l_y + 13.0), 1.0)), (void)(F_lnw((l_x + 1.0), (l_y + 9.0), (l_x + 15.0), (l_y + 9.0), 1.0)), (void)(F_lnw((l_x + 15.0), (l_y + 9.0), (l_x + 15.0), (l_y + 13.0), 1.0)), F_rro((l_x + 3.0), (l_y + 6.0), 4.0, 3.0, 1.0)) : (double)(EQ(l_i, 2.0) ? (double)((void)(F_rro((l_x + 1.0), (l_y + 7.0), 14.0, 5.0, 1.5)), (void)(F_lnw((l_x + 3.0), (l_y + 7.0), (l_x + 3.0), (l_y + 3.5), 1.0)), (void)(F_lnw((l_x + 3.0), (l_y + 3.5), (l_x + 13.0), (l_y + 3.5), 1.0)), (void)(F_lnw((l_x + 13.0), (l_y + 3.5), (l_x + 13.0), (l_y + 7.0), 1.0)), (void)(F_lnw((l_x + 3.0), (l_y + 12.0), (l_x + 3.0), (l_y + 14.0), 1.0)), F_lnw((l_x + 13.0), (l_y + 12.0), (l_x + 13.0), (l_y + 14.0), 1.0)) : (double)(EQ(l_i, 3.0) ? (double)((void)(F_lnbox((l_x + 2.0), l_y, 12.0, 7.5, 0.9)), (void)(F_lnw((l_x + 4.5), (l_y + 3.0), (l_x + 9.0), (l_y + 3.0), 0.8)), (void)(F_lnw((l_x + 4.5), (l_y + 5.0), (l_x + 7.5), (l_y + 5.0), 0.8)), (void)(F_lnw((l_x + 1.0), (l_y + 11.0), (l_x + 15.0), (l_y + 11.0), 1.0)), (void)(F_lnw((l_x + 3.0), (l_y + 11.0), (l_x + 3.0), (l_y + 14.0), 0.9)), F_lnw((l_x + 13.0), (l_y + 11.0), (l_x + 13.0), (l_y + 14.0), 0.9)) : (double)(EQ(l_i, 4.0) ? (double)((void)(F_lnbox(l_x, l_y, 16.0, 14.0, 0.9)), (void)(F_lnbox((l_x + 5.5), (l_y + 4.5), 5.0, 5.0, 0.8)), (void)(F_lnw(l_x, l_y, (l_x + 5.5), (l_y + 4.5), 0.8)), (void)(F_lnw((l_x + 16.0), l_y, (l_x + 10.5), (l_y + 4.5), 0.8)), (void)(F_lnw(l_x, (l_y + 14.0), (l_x + 5.5), (l_y + 9.5), 0.8)), F_lnw((l_x + 16.0), (l_y + 14.0), (l_x + 10.5), (l_y + 9.5), 0.8)) : (double)(EQ(l_i, 5.0) ? (double)((void)(F_lnw((l_x + 0.5), (l_y + 8.0), (l_x + 15.5), (l_y + 8.0), 1.0)), (void)(F_lnw((l_x + 1.5), (l_y + 8.0), (l_x + 3.0), (l_y + 12.5), 1.0)), (void)(F_lnw((l_x + 3.0), (l_y + 12.5), (l_x + 13.0), (l_y + 12.5), 1.0)), (void)(F_lnw((l_x + 13.0), (l_y + 12.5), (l_x + 14.5), (l_y + 8.0), 1.0)), (void)(F_lnw((l_x + 4.0), (l_y + 12.5), (l_x + 3.5), (l_y + 14.0), 0.9)), (void)(F_lnw((l_x + 12.0), (l_y + 12.5), (l_x + 12.5), (l_y + 14.0), 0.9)), (void)(F_lnw((l_x + 3.0), (l_y + 8.0), (l_x + 3.0), (l_y + 1.5), 0.9)), (void)(F_lnw((l_x + 3.0), (l_y + 1.5), (l_x + 6.5), (l_y + 1.5), 0.9)), (void)(F_lnw((l_x + 6.5), (l_y + 1.5), (l_x + 6.5), (l_y + 3.0), 0.9)), F_cif((l_x + 6.5), (l_y + 4.8), 0.6, 1.0)) : (double)(EQ(l_i, 6.0) ? (double)((void)(F_lnw(l_x, (l_y + 14.0), l_x, (l_y + 6.0), 1.0)), (void)(F_lnw((l_x + 16.0), (l_y + 14.0), (l_x + 16.0), (l_y + 6.0), 1.0)), (void)(F_lnw(l_x, (l_y + 14.0), (l_x + 16.0), (l_y + 14.0), 1.0)), (void)(F_lnw(l_x, (l_y + 6.0), (l_x + 5.3), (l_y + 2.0), 1.0)), (void)(F_lnw((l_x + 5.3), (l_y + 2.0), (l_x + 5.3), (l_y + 6.0), 1.0)), (void)(F_lnw((l_x + 5.3), (l_y + 6.0), (l_x + 10.6), (l_y + 2.0), 1.0)), (void)(F_lnw((l_x + 10.6), (l_y + 2.0), (l_x + 10.6), (l_y + 6.0), 1.0)), (void)(F_lnw((l_x + 10.6), (l_y + 6.0), (l_x + 16.0), (l_y + 2.0), 1.0)), F_lnw((l_x + 16.0), (l_y + 2.0), (l_x + 16.0), (l_y + 6.0), 1.0)) : (double)((void)(F_lnw((l_x + 1.0), (l_y + 14.0), (l_x + 1.0), (l_y + 6.5), 1.0)), (void)(F_lnw((l_x + 15.0), (l_y + 14.0), (l_x + 15.0), (l_y + 6.5), 1.0)), (void)(F_lnw((l_x - 0.5), (l_y + 14.0), (l_x + 16.5), (l_y + 14.0), 1.0)), (void)(F_arcs((l_x + 8.0), (l_y + 6.5), 7.0, (-1.5707963267948966), 1.5707963267948966, 1.0)), (void)(F_lnw((l_x + 6.0), (l_y + 14.0), (l_x + 6.0), (l_y + 10.5), 0.9)), (void)(F_lnw((l_x + 10.0), (l_y + 14.0), (l_x + 10.0), (l_y + 10.5), 0.9)), (void)(F_arcs((l_x + 8.0), (l_y + 10.5), 2.0, (-1.5707963267948966), 1.5707963267948966, 0.9)), (void)(F_lnw((l_x + 4.0), (l_y + 7.0), (l_x + 4.0), (l_y + 10.0), 0.9)), F_lnw((l_x + 12.0), (l_y + 7.0), (l_x + 12.0), (l_y + 10.0), 0.9)))))))));
}

double Gen::F_tipbox(double l_x, double l_y, double l_w, double l_h, double l_s) {
  
  return (B(F_inbox(l_x, l_y, l_w, l_h)) ? (double)((void)((g_tipon = 1.0)), (void)((g_tipstr = l_s)), (void)(ASG(g_tipx, (l_x + (l_w / 2.0)))), ASG(g_tipy, ((l_y < 60.0) ? (double)((l_y + l_h) + 12.0) : (double)(l_y - 12.0)))) : 0.0);
}

double Gen::F_tnc(double l_k) {
  
  return (EQ(l_k, 0.0) ? (double)5.0 : (double)(EQ(l_k, 1.0) ? (double)8.0 : (double)(EQ(l_k, 2.0) ? (double)6.0 : (double)(EQ(l_k, 3.0) ? (double)10.0 : (double)(EQ(l_k, 4.0) ? (double)11.0 : (double)9.0)))));
}

double Gen::F_tnname(double l_k) {
  
  return (EQ(l_k, 0.0) ? (double)10072.0 : (double)(EQ(l_k, 1.0) ? (double)10075.0 : (double)(EQ(l_k, 2.0) ? (double)11822.0 : (double)(EQ(l_k, 3.0) ? (double)11823.0 : (double)(EQ(l_k, 4.0) ? (double)10078.0 : (double)11824.0)))));
}

double Gen::F_tnr(double l_u) {
  
  return ((void)((l_u = rt_min(3.0, rt_max((-3.0), l_u)))), (l_u * ((27.0 + (l_u * l_u)) / (27.0 + ((9.0 * l_u) * l_u)))));
}

double Gen::F_tpapply(double l_code, double l_bpm) {
  double l_nb = 0.0, l_wasms = 0.0; 
  return ((void)(F_snap_take()), (void)((l_wasms = ((sl[67] < 0.5) ? 1.0 : 0.0))), (void)(((l_bpm >= 0.0) ? (double)(sl[74] = l_bpm) : 0.0)), (void)((l_nb = ((sl[74] > 0.5) ? (double)sl[74] : (double)((v_tempo > 1.0) ? (double)v_tempo : (double)120.0)))), (void)((((B(l_wasms) && (sl[68] < 0.5)) && EQ(g_tptg, 0.0)) ? (double)ASG(sl[73], F_tpnear(sl[71], l_nb)) : 0.0)), (void)((((B(l_wasms) && (sl[68] < 0.5)) && EQ(g_tptg, 1.0)) ? (double)ASG(sl[72], F_tpnear(sl[70], l_nb)) : 0.0)), (void)(((B(l_wasms) && (l_code < 0.0)) ? (double)((void)(ASG(sl[72], F_tpnear(sl[70], l_nb))), ASG(sl[73], F_tpnear(sl[71], l_nb))) : 0.0)), (void)((sl[67] = 1.0)), (void)(((l_code >= 0.0) ? (double)((void)((NE(g_tptg, 1.0) ? (double)(sl[72] = l_code) : 0.0)), (void)((NE(g_tptg, 0.0) ? (double)(sl[73] = l_code) : 0.0)), (EQ(g_tptg, 1.0) ? (double)(sl[68] = 0.0) : 0.0)) : 0.0)), F_snap_notify());
}

double Gen::F_tpmot(double l_code) {
  double l_q = 0.0; 
  return ((void)((l_q = (EQ(l_code, 0.0) ? (double)4.0 : (double)(EQ(l_code, 2.0) ? (double)5.0 : (double)(EQ(l_code, 5.0) ? (double)6.0 : (double)(EQ(l_code, 8.0) ? (double)7.0 : (double)(EQ(l_code, 11.0) ? (double)8.0 : (double)(-1.0)))))))), ((l_q > 0.0) ? (double)F_setp(108.0, l_q) : 0.0));
}

double Gen::F_tpnear(double l_ms, double l_bpm) {
  double l_b = 0.0, l_bd = 0.0, l_d = 0.0, l_n = 0.0; 
  return ((void)((l_b = 8.0)), (void)((l_bd = 1000000000.0)), (void)((l_n = 0.0)), (void)([&]() -> double { int n_ = rt_i32(13.0); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)((l_d = std::fabs(rt_log((rt_max(1.0, (F_g_dnote(l_n) * (60000.0 / l_bpm))) / rt_max(1.0, l_ms)))))), (void)(((l_d < l_bd) ? (double)((void)((l_bd = l_d)), (l_b = l_n)) : 0.0)), (l_n += 1.0))); } return 0.0; }()), l_b);
}

double Gen::F_tpuse(double l_code, double l_bpm) {
  
  return (EQ(g_tpctx, 14.0) ? (double)((void)(((l_bpm >= 0.0) ? (double)F_setp(74.0, l_bpm) : 0.0)), (EQ(rt_floor((sl[108] + 0.5)), 0.0) ? (double)F_setp(108.0, 4.0) : 0.0)) : (double)F_tpapply(l_code, l_bpm));
}

double Gen::F_tws(double l_s) {
  double l_th2 = 0.0, l_tw2 = 0.0; 
  return ((void)(gfx_measurestr(l_s, l_tw2, l_th2)), (l_tw2 / g_gs));
}

double Gen::F_txt(double l_s, double l_x, double l_yc, double l_al) {
  double l_px = 0.0, l_py = 0.0, l_th2 = 0.0, l_tw2 = 0.0; 
  return ((B(g_gclp) && ((((l_x < g_clx0) || (l_x > g_clx1)) || (l_yc < g_cly0)) || (l_yc > g_cly1))) ? (double)0.0 : (double)((void)(gfx_measurestr(l_s, l_tw2, l_th2)), (void)((l_px = (g_gox + (l_x * g_gs)))), (void)((l_py = (g_goy + (l_yc * g_gs)))), (void)(ASG(v_gfx_x, rt_floor(((EQ(l_al, 1.0) ? (double)(l_px - (l_tw2 / 2.0)) : (double)(EQ(l_al, 2.0) ? (double)(l_px - l_tw2) : (double)l_px)) + 0.5)))), (void)(ASG(v_gfx_y, rt_floor(((l_py - (l_th2 / 2.0)) + 0.5)))), gfx_drawstr({l_s})));
}

double Gen::F_txtbox(double l_s, double l_cx, double l_cy, double l_w, double l_h, double l_fi) {
  double l_k = 0.0, l_th2 = 0.0, l_tw2 = 0.0; 
  return ((void)(gfx_setfont({l_fi})), (void)(gfx_measurestr(l_s, l_tw2, l_th2)), (void)((l_k = rt_min(1.0, rt_min(((l_w - 4.0) * (g_gs / rt_max(1.0, l_tw2))), ((l_h - 1.0) * (g_gs / rt_max(1.0, l_th2))))))), (void)(((l_k < 0.999) ? (double)gfx_setfont({9.0, 10231.0, (F_fsz(l_fi) * l_k), (B(F_fbd(l_fi)) ? (double)98.0 : (double)0.0)}) : 0.0)), F_txt(l_s, l_cx, l_cy, 1.0));
}

double Gen::F_txtboxr(double l_s, double l_cx, double l_cy, double l_w, double l_h, double l_fi) {
  double l_k = 0.0, l_th2 = 0.0, l_tr = 0.0, l_tw2 = 0.0; 
  return ((void)(gfx_setfont({l_fi})), (void)(gfx_measurestr(11825.0, l_tr, l_th2)), (void)(gfx_measurestr(l_s, l_tw2, l_th2)), (void)((l_k = rt_min(1.0, rt_min(((l_w - 4.0) * (g_gs / rt_max(1.0, rt_max(l_tw2, l_tr)))), ((l_h - 1.0) * (g_gs / rt_max(1.0, l_th2))))))), (void)(((l_k < 0.999) ? (double)gfx_setfont({9.0, 10231.0, (F_fsz(l_fi) * l_k), (B(F_fbd(l_fi)) ? (double)98.0 : (double)0.0)}) : 0.0)), F_txt(l_s, l_cx, l_cy, 1.0));
}

double Gen::F_txtc(double l_s, double l_x, double l_y) {
  double l_th2 = 0.0, l_tw2 = 0.0; 
  return ((void)(gfx_measurestr(l_s, l_tw2, l_th2)), (void)(ASG(v_gfx_x, rt_floor(((rt_floor(((g_gox + (l_x * g_gs)) + 0.5)) + (0.5 - (l_tw2 / 2.0))) + 0.5)))), (void)(ASG(v_gfx_y, rt_floor(((rt_floor(((g_goy + (l_y * g_gs)) + 0.5)) + (0.5 - (l_th2 / 2.0))) + 0.5)))), gfx_drawstr({l_s}));
}

double Gen::F_txtfit(double l_s, double l_x, double l_yc, double l_w) {
  double l_n = 0.0; 
  return ((void)(strcpy(90056.0, l_s)), (void)(((F_tws(90056.0) > l_w) ? (double)((void)((l_n = strlen(90056.0))), (void)([&]() -> double { int c_ = 1048576; while (((void)((l_n -= 1.0)), (void)(str_setlen(90056.0, l_n)), (void)(strcpy(90057.0, 90056.0)), (void)(strcat(90057.0, 11404.0)), ((l_n > 1.0) && (F_tws(90057.0) > l_w)))) { if (--c_ <= 0) break; } return 0.0; }()), strcpy(90056.0, 90057.0)) : 0.0)), F_txt(90056.0, l_x, l_yc, 0.0));
}

double Gen::F_txtplate(double l_s, double l_x, double l_yc, double l_al) {
  double l_h = 0.0, l_tb = 0.0, l_tg = 0.0, l_tr = 0.0, l_w = 0.0, l_x0 = 0.0; 
  return ((void)((l_tr = v_gfx_r)), (void)((l_tg = v_gfx_g)), (void)((l_tb = v_gfx_b)), (void)((l_w = (F_tws(l_s) + 8.0))), (void)((l_h = 14.0)), (void)((l_x0 = (EQ(l_al, 1.0) ? (double)(l_x - (l_w / 2.0)) : (double)(EQ(l_al, 2.0) ? (double)(l_x - l_w) : (double)l_x)))), (void)(F_col(g_csurf, 0.88)), (void)(F_rr(l_x0, (l_yc - (l_h / 2.0)), l_w, l_h, 4.0)), (void)((v_gfx_r = l_tr)), (void)((v_gfx_g = l_tg)), (void)((v_gfx_b = l_tb)), (void)((v_gfx_a = 1.0)), F_txt(l_s, (l_x0 + 4.0), l_yc, 0.0));
}

double Gen::F_uapply(double l_b) {
  double l_i = 0.0; 
  return ((void)(F_snap_take()), (void)((l_i = 1.0)), (void)([&]() -> double { int n_ = rt_i32(g_nsl); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)(F_sset(l_i, M((l_b + l_i)))), (l_i += 1.0))); } return 0.0; }()), (void)(F_rfput((l_b + 126.0))), (void)(F_snap_notify()), (void)((((g_mte > 0.001) || (sl[100] >= 0.5)) ? (double)((void)(ASG(g_mtc0x, M((l_b + 120.0)))), (void)(ASG(g_mtc0y, M((l_b + 121.0)))), (void)(ASG(g_mtc0z, M((l_b + 122.0)))), (void)(ASG(g_mtc1x, M((l_b + 123.0)))), (void)(ASG(g_mtc1y, M((l_b + 124.0)))), ASG(g_mtc1z, M((l_b + 125.0)))) : 0.0)), F_ucopy(g_ubs));
}

double Gen::F_ucommit() {
  
  return ((void)((B(F_udiff(g_ubs)) ? (double)((void)((B(g_ugest) ? (double)((void)(ASG(g_unn, F_upush(g_unb, g_unn))), (g_rdn = 0.0)) : 0.0)), F_ucopy(g_ubs)) : 0.0)), (g_ugest = 0.0));
}

double Gen::F_ucopy(double l_b) {
  double l_i = 0.0; 
  return ((void)(F_rfget((l_b + 126.0))), (void)((l_i = 1.0)), (void)([&]() -> double { int n_ = rt_i32(g_nsl); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)([&]() -> double& { double& r_ = M((l_b + l_i)); r_ = dnf(SL(l_i)); return r_; }()), (l_i += 1.0))); } return 0.0; }()), (void)((M((l_b + 120.0)) = g_mtc0x)), (void)((M((l_b + 121.0)) = g_mtc0y)), (void)((M((l_b + 122.0)) = g_mtc0z)), (void)((M((l_b + 123.0)) = g_mtc1x)), (void)((M((l_b + 124.0)) = g_mtc1y)), (M((l_b + 125.0)) = g_mtc1z));
}

double Gen::F_udiff(double l_b) {
  double l_d = 0.0, l_i = 0.0, l_mr = 0.0; 
  return ((void)((l_d = 0.0)), (void)((l_mr = (((g_mte > 0.001) || (sl[100] >= 0.5)) ? 1.0 : 0.0))), (void)((l_i = 1.0)), (void)([&]() -> double { int n_ = rt_i32(g_nsl); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)((((!((B(l_mr) && (l_i >= 10.0)) && (l_i <= 15.0))) && (std::fabs((SL(l_i) - M((l_b + l_i)))) > 1e-09)) ? (double)(l_d = 1.0) : 0.0)), (l_i += 1.0))); } return 0.0; }()), (void)((((((std::fabs((g_mtc0x - M((l_b + 120.0)))) + std::fabs((g_mtc0y - M((l_b + 121.0))))) + std::fabs((g_mtc1x - M((l_b + 123.0))))) + std::fabs((g_mtc1y - M((l_b + 124.0))))) > 1e-09) ? (double)(l_d = 1.0) : 0.0)), (void)((l_i = 0.0)), (void)([&]() -> double { int n_ = rt_i32(15.0); if (n_ > 1048576) n_ = 1048576; double c_vopt = g_vopt; for (; n_ > 0; --n_) { (void)(((void)(((std::fabs((M((c_vopt + (52.0 + l_i))) - M((l_b + (126.0 + l_i))))) > 1e-09) ? (double)(l_d = 1.0) : 0.0)), (l_i += 1.0))); } return 0.0; }()), l_d);
}

double Gen::F_udo() {
  
  return ((void)(F_ucommit()), (void)(((g_unn > 0.0) ? (double)((void)(ASG(g_rdn, F_upush(g_rdb, g_rdn))), (void)((g_unn -= 1.0)), F_uapply((g_unb + (g_unn * g_ustr)))) : 0.0)), (g_ugest = 0.0));
}

double Gen::F_updnote(double l_ty) {
  double l_h = 0.0, l_w = 0.0, l_x = 0.0; 
  return (B(g_updav) ? (double)((void)(gfx_setfont({7.0})), (void)((l_x = ((12.0 + F_tws(90021.0)) + 8.0))), (void)(sprintf({90058.0, 11826.0, 1000.0})), (void)((l_w = (F_tws(90058.0) + 14.0))), (void)((l_h = F_inbox(l_x, (l_ty - 6.0), l_w, 12.0))), (void)(F_col(g_cact, (B(l_h) ? (double)0.85 : (double)1.0))), (void)(F_rr(l_x, (l_ty - 6.0), l_w, 12.0, 6.0)), (void)(F_col(g_cactx, 1.0)), (void)(gfx_setfont({7.0})), (void)(F_txt(90058.0, (l_x + (l_w / 2.0)), l_ty, 1.0)), (void)((B(l_h) ? (double)((void)(sprintf({90059.0, 11827.0, 1000.0})), (void)(F_tipbox(l_x, (l_ty - 6.0), l_w, 12.0, 90059.0)), (g_tipforce = 1.0)) : 0.0)), ((B(l_h) && B(g_click)) ? (double)((void)((g_updgo = 1.0)), (g_click = 0.0)) : 0.0)) : 0.0);
}

double Gen::F_upush(double l_st, double l_n) {
  
  return ((void)(((l_n >= g_unmax) ? (double)((void)(memcpy(l_st, (l_st + g_ustr), ((g_unmax - 1.0) * g_ustr))), (l_n = (g_unmax - 1.0))) : 0.0)), (void)(memcpy((l_st + (l_n * g_ustr)), g_ubs, g_ustr)), (l_n + 1.0));
}

double Gen::F_urcatname(double l_c) {
  
  return ((l_c < 6.0) ? (double)F_roomcatname(l_c) : (double)11828.0);
}

double Gen::F_urcount() {
  double l_n = 0.0, l_u = 0.0; 
  return ((void)((l_n = 0.0)), (void)((l_u = 0.0)), (void)([&]() -> double { int n_ = rt_i32(g_urm); if (n_ > 1048576) n_ = 1048576; double c_urb = g_urb, c_url = g_url; for (; n_ > 0; --n_) { (void)(((void)((B(M((c_urb + (l_u * c_url)))) ? (double)(l_n += 1.0) : 0.0)), (l_u += 1.0))); } return 0.0; }()), l_n);
}

double Gen::F_urdel(double l_u) {
  double l_v = 0.0; 
  return ((void)((l_v = l_u)), (void)([&]() -> double { int n_ = rt_i32(((g_urm - 1.0) - l_u)); if (n_ > 1048576) n_ = 1048576; double c_urb = g_urb, c_url = g_url; for (; n_ > 0; --n_) { (void)(((void)(memcpy((c_urb + (l_v * c_url)), (c_urb + ((l_v + 1.0) * c_url)), c_url)), (l_v += 1.0))); } return 0.0; }()), memset((g_urb + ((g_urm - 1.0) * g_url)), 0.0, g_url));
}

double Gen::F_uredo() {
  
  return ((void)(F_ucommit()), (void)(((g_rdn > 0.0) ? (double)((void)(ASG(g_unn, F_upush(g_unb, g_unn))), (void)((g_rdn -= 1.0)), F_uapply((g_rdb + (g_rdn * g_ustr)))) : 0.0)), (g_ugest = 0.0));
}

double Gen::F_urfind(double l_nb) {
  double l_eq = 0.0, l_f = 0.0, l_i = 0.0, l_u = 0.0; 
  return ((void)((l_f = (-1.0))), (void)((l_u = 0.0)), (void)([&]() -> double { int n_ = rt_i32(g_urm); if (n_ > 1048576) n_ = 1048576; double c_urb = g_urb, c_url = g_url; for (; n_ > 0; --n_) { (void)(((void)(((B(M((c_urb + (l_u * c_url)))) && (l_f < 0.0)) ? (double)((void)((l_eq = 1.0)), (void)((l_i = 0.0)), (void)([&]() -> double { int n_ = rt_i32(24.0); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)((NE(M((c_urb + (((l_u * c_url) + 2.0) + l_i))), M((l_nb + l_i))) ? (double)(l_eq = 0.0) : 0.0)), (l_i += 1.0))); } return 0.0; }()), (B(l_eq) ? (double)(l_f = l_u) : 0.0)) : 0.0)), (l_u += 1.0))); } return 0.0; }()), l_f);
}

double Gen::F_urload(double l_u) {
  double l_b = 0.0, l_hz = 0.0, l_i = 0.0, l_kb = 0.0, l_kp = 0.0, l_sp = 0.0; 
  return ((void)((l_b = (g_urb + (l_u * g_url)))), (void)((l_kp = ((M((g_vopt + 16.0)) >= 0.5) ? 1.0 : 0.0))), (void)((l_kb = ((M((g_vopt + 17.0)) >= 0.5) ? 1.0 : 0.0))), (void)(F_snap_take()), (void)((l_i = 0.0)), (void)([&]() -> double { int n_ = rt_i32(g_urp); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)((l_sp = F_urparam(l_i))), (void)(((!((B(l_kp) && ((((l_sp >= 10.0) && (l_sp <= 17.0)) || EQ(l_sp, 61.0)) || EQ(l_sp, 63.0))) || (B(l_kb) && ((((l_sp >= 41.0) && (l_sp <= 46.0)) || EQ(l_sp, 92.0)) || (l_sp >= 95.0))))) ? (double)F_sset(l_sp, ((EQ(l_sp, 97.0) && (M((l_b + (26.0 + l_i))) < 1.0)) ? (double)100.0 : (double)M((l_b + (26.0 + l_i))))) : 0.0)), (l_i += 1.0))); } return 0.0; }()), (void)((B(l_kp) ? (double)((void)((l_hz = ((sl[4] * sl[31]) - 0.1))), (void)(ASG(sl[10], rt_min(rt_max(sl[10], 0.1), (sl[2] - 0.1)))), (void)(ASG(sl[11], rt_min(rt_max(sl[11], 0.1), (sl[3] - 0.1)))), (void)(ASG(sl[12], rt_min(rt_max(sl[12], 0.1), l_hz))), (void)(ASG(sl[13], rt_min(rt_max(sl[13], 0.1), (sl[2] - 0.1)))), (void)(ASG(sl[14], rt_min(rt_max(sl[14], 0.1), (sl[3] - 0.1)))), ASG(sl[15], rt_min(rt_max(sl[15], 0.1), l_hz))) : 0.0)), (void)((B(l_kb) ? (double)((void)(ASG(sl[42], rt_min(rt_max(sl[42], 0.3), (sl[3] - 0.3)))), ASG(sl[45], rt_min(rt_max(sl[45], 0.0), sl[2]))) : 0.0)), (void)((g_selw = 0.0)), F_snap_notify());
}

double Gen::F_urmatch(double l_u) {
  double l_b = 0.0, l_i = 0.0, l_ok = 0.0; 
  return ((void)((l_b = (g_urb + (l_u * g_url)))), (void)((l_ok = ((M(l_b) > 0.0) ? 1.0 : 0.0))), (void)((l_i = 0.0)), (void)([&]() -> double { int c_ = 1048576; double c_urp = g_urp; while (B(((B(l_ok) && (l_i < c_urp)) ? (double)((void)((((NE(l_i, 32.0) && NE(l_i, 34.0)) && (std::fabs((SL(F_urparam(l_i)) - ((EQ(l_i, 39.0) && (M((l_b + (26.0 + l_i))) < 1.0)) ? (double)100.0 : (double)M((l_b + (26.0 + l_i)))))) > 0.001)) ? (double)(l_ok = 0.0) : 0.0)), (void)((l_i += 1.0)), 1.0) : (double)0.0))) { if (--c_ <= 0) break; } return 0.0; }()), l_ok);
}

double Gen::F_urover(double l_u) {
  double l_b = 0.0, l_i = 0.0; 
  return ((void)((l_b = (g_urb + (l_u * g_url)))), (void)((l_i = 0.0)), [&]() -> double { int n_ = rt_i32(g_urp); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)([&]() -> double& { double& r_ = M((l_b + (26.0 + l_i))); r_ = dnf(SL(F_urparam(l_i))); return r_; }()), (l_i += 1.0))); } return 0.0; }());
}

double Gen::F_urparam(double l_i) {
  
  return ((l_i < 17.0) ? (double)(l_i + 1.0) : (double)(EQ(l_i, 17.0) ? (double)19.0 : (double)(EQ(l_i, 18.0) ? (double)20.0 : (double)(EQ(l_i, 19.0) ? (double)21.0 : (double)((l_i < 24.0) ? (double)(l_i + 11.0) : (double)(EQ(l_i, 24.0) ? (double)36.0 : (double)(EQ(l_i, 25.0) ? (double)38.0 : (double)((l_i < 32.0) ? (double)(l_i + 15.0) : (double)(EQ(l_i, 32.0) ? (double)61.0 : (double)(EQ(l_i, 33.0) ? (double)62.0 : (double)(EQ(l_i, 34.0) ? (double)63.0 : (double)(EQ(l_i, 35.0) ? (double)91.0 : (double)(EQ(l_i, 36.0) ? (double)92.0 : (double)(EQ(l_i, 37.0) ? (double)95.0 : (double)(EQ(l_i, 38.0) ? (double)96.0 : (double)97.0)))))))))))))));
}

double Gen::F_ursave() {
  double l_b = 0.0, l_i = 0.0, l_u = 0.0; 
  return ((void)((l_u = F_urfind(g_rsnb))), (void)(((l_u < 0.0) ? (double)((void)((l_u = 0.0)), [&]() -> double { int c_ = 1048576; double c_urb = g_urb, c_url = g_url, c_urm = g_urm; while (B((((l_u < c_urm) && B(M((c_urb + (l_u * c_url))))) ? (double)((void)((l_u += 1.0)), 1.0) : (double)0.0))) { if (--c_ <= 0) break; } return 0.0; }()) : 0.0)), ((l_u < g_urm) ? (double)((void)((l_b = (g_urb + (l_u * g_url)))), (void)((M(l_b) = 1.0)), (void)((M((l_b + 1.0)) = g_rscat)), (void)((l_i = 0.0)), (void)([&]() -> double { int n_ = rt_i32(24.0); if (n_ > 1048576) n_ = 1048576; double c_rsnb = g_rsnb; for (; n_ > 0; --n_) { (void)(((void)(ASG(M((l_b + (2.0 + l_i))), M((c_rsnb + l_i)))), (l_i += 1.0))); } return 0.0; }()), (void)((l_i = 0.0)), (void)([&]() -> double { int n_ = rt_i32(g_urp); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)([&]() -> double& { double& r_ = M((l_b + (26.0 + l_i))); r_ = dnf(SL(F_urparam(l_i))); return r_; }()), (l_i += 1.0))); } return 0.0; }()), 1.0) : (double)0.0));
}

double Gen::F_veddraw(double l_cx, double l_yc, double l_w) {
  double l_bw = 0.0; 
  return ((void)((l_bw = rt_max(l_w, 54.0))), (void)(F_col(g_cink, 0.14)), (void)(F_rr(((l_cx - (l_bw / 2.0)) + 1.0), (l_yc - 8.0), l_bw, 17.0, 4.0)), (void)(F_col(g_csurf, 1.0)), (void)(F_rr((l_cx - (l_bw / 2.0)), (l_yc - 9.0), l_bw, 17.0, 4.0)), (void)(F_col(((g_kcol > 0.0) ? g_kcol : g_ctext), 1.0)), (void)(F_rro((l_cx - (l_bw / 2.0)), (l_yc - 9.0), l_bw, 17.0, 4.0)), (void)(((B(g_vednew) && B(strlen(90060.0))) ? (double)((void)(F_col(((g_kcol > 0.0) ? g_kcol : g_ctext), 0.18)), (void)(gfx_setfont({2.0})), [&]() -> double { const double a0_ = ((l_cx - (F_tws(90060.0) / 2.0)) - 2.0); const double a1_ = (l_yc - 6.0); const double a2_ = (F_tws(90060.0) + 4.0); return F_rr(a0_, a1_, a2_, 12.0, 2.0); }()) : 0.0)), (void)(F_col(g_ctext, 1.0)), (void)(gfx_setfont({2.0})), (void)(F_txt(90060.0, l_cx, l_yc, 1.0)), (void)(((EQ(rt_and(rt_floor(((time_precise() - g_vedt0) * 2.0)), 1.0), 0.0) && (!B(g_vednew))) ? (double)((void)(gfx_setfont({2.0})), [&]() -> double { const double a0_ = ((l_cx + (F_tws(90060.0) / 2.0)) + 1.5); const double a1_ = (l_yc - 5.0); const double a2_ = ((l_cx + (F_tws(90060.0) / 2.0)) + 1.5); const double a3_ = (l_yc + 5.0); return F_lnw(a0_, a1_, a2_, a3_, 1.0); }()) : 0.0)), (void)(ASG(g_vedpx0, (g_gox + ((l_cx - (l_bw / 2.0)) * g_gs)))), (void)(ASG(g_vedpx1, (g_gox + ((l_cx + (l_bw / 2.0)) * g_gs)))), (void)(ASG(g_vedpy0, (g_goy + ((l_yc - 9.0) * g_gs)))), (void)(ASG(g_vedpy1, (g_goy + ((l_yc + 8.0) * g_gs)))), (g_tipon = 0.0));
}

double Gen::F_vedmap(double l_v) {
  
  return ((void)((l_v /= rt_max(1e-06, g_kmaps))), (void)(((((((EQ(g_kmapt, 1.0) && (!B(g_vedk))) && (g_kmapa >= 20.0)) && (l_v < g_kmapa)) && ((l_v * 1000.0) >= g_kmapa)) && ((l_v * 1000.0) <= g_kmapb)) ? (double)(l_v *= 1000.0) : 0.0)), (void)((EQ(g_kmapt, 0.0) ? (double)ASG(L_vedmap_f, ((l_v - g_kmapa) / (g_kmapb - g_kmapa))) : 0.0)), (void)((EQ(g_kmapt, 1.0) ? (double)ASG(L_vedmap_f, (rt_log((rt_max(g_kmapa, l_v) / g_kmapa)) / rt_log((g_kmapb / g_kmapa)))) : 0.0)), (void)((EQ(g_kmapt, 2.0) ? (double)((void)((l_v = rt_min(24.0, rt_max((-72.0), l_v)))), ASG(L_vedmap_f, ((l_v <= (-24.0)) ? (double)(0.25 * ((l_v + 72.0) / 48.0)) : (double)(0.25 + (0.75 * ((l_v + 24.0) / 48.0)))))) : 0.0)), (void)((EQ(g_kmapt, 3.0) ? (double)((void)((l_v = rt_min(48.0, rt_max((-72.0), l_v)))), ASG(L_vedmap_f, ((l_v <= (-24.0)) ? (double)(0.25 * ((l_v + 72.0) / 48.0)) : (double)(0.25 + (0.75 * ((l_v + 24.0) / 72.0)))))) : 0.0)), rt_min(1.0, rt_max(0.0, L_vedmap_f)));
}

double Gen::F_vedopen(double l_id, double l_vs) {
  double l_c = 0.0, l_i = 0.0, l_n = 0.0; 
  return ((void)((g_vedit = l_id)), (void)((g_vednew = 1.0)), (void)(strcpy(90060.0, 10120.0)), (void)((l_n = strlen(l_vs))), (void)((l_i = 0.0)), (void)([&]() -> double { int n_ = rt_i32(l_n); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)((l_c = str_getchar({l_vs, l_i}))), (void)((((((((l_c >= 48.0) && (l_c <= 57.0)) || EQ(l_c, 46.0)) || EQ(l_c, 45.0)) || EQ(l_c, 44.0)) || EQ(l_c, 107.0)) ? (double)((void)(sprintf({90061.0, 11677.0, l_c})), strcat(90060.0, 90061.0)) : 0.0)), (l_i += 1.0))); } return 0.0; }()), (void)(ASG(g_vedt0, time_precise())), (void)((g_kdrag = 0.0)), (g_vedjust = 1.0));
}

double Gen::F_vedparse(double l_st) {
  double l_c = 0.0, l_fr = 0.0, l_i = 0.0, l_k1 = 0.0, l_n = 0.0, l_sg = 0.0, l_v = 0.0, l_vany = 0.0, l_vdp = 0.0; 
  return ((void)((l_n = strlen(l_st))), (void)((l_i = 0.0)), (void)((l_v = 0.0)), (void)((l_sg = 1.0)), (void)((l_fr = 1.0)), (void)((l_vdp = 0.0)), (void)((l_k1 = 0.0)), (void)((l_vany = 0.0)), (void)([&]() -> double { int n_ = rt_i32(l_n); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)((l_c = str_getchar({l_st, l_i}))), (void)((EQ(l_c, 45.0) ? (double)(l_sg = (-1.0)) : (double)((EQ(l_c, 46.0) || EQ(l_c, 44.0)) ? (double)(l_vdp = 1.0) : (double)((EQ(l_c, 107.0) || EQ(l_c, 75.0)) ? (double)(l_k1 = 1.0) : (double)(((l_c >= 48.0) && (l_c <= 57.0)) ? (double)((void)((l_vany = 1.0)), (B(l_vdp) ? ((void)((l_fr *= 0.1)), (l_v += ((l_c - 48.0) * l_fr))) : (l_v = ((l_v * 10.0) + (l_c - 48.0))))) : 0.0))))), (l_i += 1.0))); } return 0.0; }()), (void)((g_vedok = l_vany)), (void)((g_vedk = l_k1)), ((l_sg * l_v) * (B(l_k1) ? (double)1000.0 : (double)1.0)));
}

double Gen::F_vedplace(double l_cx, double l_yc, double l_w) {
  
  return ((void)((g_vedcx = l_cx)), (void)((g_vedcy = l_yc)), (void)((g_vedw = l_w)), (void)((g_vedgs = g_gs)), (void)((g_vedgx = g_gox)), (void)((g_vedgy = g_goy)), (void)((g_vedkc = g_kcol)), (g_vedseen = 1.0));
}

double Gen::F_viewgrp(double l_vgx, double l_vgd) {
  double l_gk = 0.0, l_gq = 0.0, l_nv = 0.0, l_von = 0.0, l_vtx = 0.0; 
  return ((void)(F_col(g_ctext, 1.0)), (void)(gfx_setfont({2.0})), (void)(F_txt(11829.0, l_vgx, (17.0 + l_vgd), 0.0)), (void)(((B(g_click) && B(F_inbox((l_vgx - 2.0), (7.0 + l_vgd), 26.0, 20.0))) ? (double)((void)((l_nv = (B(g_showinfo) ? (double)0.0 : (double)1.0))), (void)(((!B(g_basic)) ? (double)((void)((M((g_vopt + 1.0)) = l_nv)), (M((g_vopt + 2.0)) = l_nv)) : 0.0)), (void)((M((g_vopt + 3.0)) = l_nv)), (M((g_vopt + 6.0)) = l_nv)) : 0.0)), (void)(F_tipbox((l_vgx - 2.0), (7.0 + l_vgd), 26.0, 20.0, (B(g_basic) ? (double)11830.0 : (double)11831.0))), (void)((l_gk = 0.0)), [&]() -> double { int n_ = rt_i32((B(g_basic) ? (double)2.0 : (double)5.0)); if (n_ > 1048576) n_ = 1048576; double c_basic = g_basic, c_click = g_click, c_cmuted = g_cmuted, c_crmtt = g_crmtt, c_ctext = g_ctext, c_hidew = g_hidew, c_showdirect = g_showdirect, c_showpaths = g_showpaths, c_tipson = g_tipson, c_vopt = g_vopt, c_waveson = g_waveson; for (; n_ > 0; --n_) { (void)(((void)((l_gq = (B(c_basic) ? (double)(EQ(l_gk, 0.0) ? (double)0.0 : (double)3.0) : (double)l_gk))), (void)((l_vtx = ((l_vgx + 26.0) + (l_gk * 30.0)))), (void)((l_von = (EQ(l_gq, 0.0) ? (double)c_tipson : (double)(EQ(l_gq, 1.0) ? (double)c_showpaths : (double)(EQ(l_gq, 2.0) ? (double)c_showdirect : (double)(EQ(l_gq, 3.0) ? (double)c_waveson : (double)((!B(c_hidew)) ? 1.0 : 0.0))))))), (void)(F_col((B(l_von) ? c_ctext : c_cmuted), 1.0)), (void)(gfx_setfont({(B(l_von) ? (double)6.0 : (double)4.0)})), (void)(F_txt((EQ(l_gq, 0.0) ? (double)11832.0 : (double)(EQ(l_gq, 1.0) ? (double)11833.0 : (double)(EQ(l_gq, 2.0) ? (double)10836.0 : (double)(EQ(l_gq, 3.0) ? (double)11834.0 : (double)10891.0)))), (l_vtx + 13.0), (17.0 + l_vgd), 1.0)), (void)((B(l_von) ? (double)((void)(F_col(c_crmtt, 1.0)), F_lnw((l_vtx + 3.0), (24.0 + l_vgd), (l_vtx + 23.0), (24.0 + l_vgd), 1.4)) : 0.0)), (void)(((B(c_click) && B(F_inbox(l_vtx, (7.0 + l_vgd), 28.0, 20.0))) ? (double)((void)((EQ(l_gq, 0.0) ? (double)ASG(M((c_vopt + 3.0)), ((!B(c_tipson)) ? 1.0 : 0.0)) : 0.0)), (void)((EQ(l_gq, 1.0) ? (double)ASG(M((c_vopt + 1.0)), ((!B(c_showpaths)) ? 1.0 : 0.0)) : 0.0)), (void)((EQ(l_gq, 2.0) ? (double)ASG(M((c_vopt + 2.0)), ((!B(c_showdirect)) ? 1.0 : 0.0)) : 0.0)), (void)((EQ(l_gq, 3.0) ? (double)ASG(M((c_vopt + 6.0)), ((!B(c_waveson)) ? 1.0 : 0.0)) : 0.0)), (EQ(l_gq, 4.0) ? (double)ASG(M((c_vopt + 10.0)), ((!B(c_hidew)) ? 1.0 : 0.0)) : 0.0)) : 0.0)), (void)(F_tipbox(l_vtx, (7.0 + l_vgd), 28.0, 20.0, (EQ(l_gq, 0.0) ? (double)11835.0 : (double)(EQ(l_gq, 1.0) ? (double)11836.0 : (double)(EQ(l_gq, 2.0) ? (double)11837.0 : (double)(EQ(l_gq, 3.0) ? (double)11838.0 : (double)(B(c_hidew) ? (double)11839.0 : (double)11840.0))))))), (l_gk += 1.0))); } g_vopt = c_vopt; return 0.0; }());
}

double Gen::F_vzfbox() {
  double l_a = 0.0, l_hl = 0.0, l_k = 0.0, l_o = 0.0, l_r = 0.0, l_ux = 0.0, l_uy = 0.0, l_z = 0.0; 
  return ((void)(ASG(g_vzbx0, (g_vzby0 = 100000.0))), (void)(ASG(g_vzbx1, (g_vzby1 = (-100000.0)))), (void)((l_k = 0.0)), (void)([&]() -> double { int n_ = rt_i32(((B(g_isfree) || B(g_planv)) ? (double)4.0 : (double)8.0)); if (n_ > 1048576) n_ = 1048576; double c_roomd = g_roomd, c_roomh = g_roomh, c_roomw = g_roomw, c_vzbx0 = g_vzbx0, c_vzbx1 = g_vzbx1, c_vzby0 = g_vzby0, c_vzby1 = g_vzby1; for (; n_ > 0; --n_) { (void)(((void)((l_z = ((l_k >= 4.0) ? (double)c_roomh : (double)0.0))), (void)(F_pj((B(rt_and(l_k, 1.0)) ? (double)c_roomw : (double)0.0), (B(rt_and(l_k, 2.0)) ? (double)c_roomd : (double)0.0), l_z)), (void)(ASG(c_vzbx0, rt_min(c_vzbx0, g_qx))), (void)(ASG(c_vzbx1, rt_max(c_vzbx1, g_qx))), (void)(ASG(c_vzby0, rt_min(c_vzby0, g_qy))), (void)(ASG(c_vzby1, rt_max(c_vzby1, g_qy))), (l_k += 1.0))); } g_vzbx0 = c_vzbx0; g_vzbx1 = c_vzbx1; g_vzby0 = c_vzby0; g_vzby1 = c_vzby1; return 0.0; }()), ((B(g_isfree) && (M((g_vopt + (g_rfb + 14.0))) < 0.5)) ? (double)((void)((l_r = 0.0)), [&]() -> double { int n_ = rt_i32(2.0); if (n_ > 1048576) n_ = 1048576; double c_planv = g_planv, c_rfb = g_rfb, c_vopt = g_vopt, c_vzbx0 = g_vzbx0, c_vzbx1 = g_vzbx1, c_vzby0 = g_vzby0, c_vzby1 = g_vzby1; for (; n_ > 0; --n_) { (void)(((void)((l_o = (c_rfb + (l_r * 6.0)))), (void)(((M((c_vopt + l_o)) >= 0.5) ? (double)((void)((l_a = (M((c_vopt + (l_o + 3.0))) * 0.017453292519943295))), (void)((l_ux = rt_cos(l_a))), (void)((l_uy = rt_sin(l_a))), (void)((l_hl = (0.5 * M((c_vopt + (l_o + 4.0)))))), (void)((l_k = 0.0)), [&]() -> double { int n_ = rt_i32((B(c_planv) ? (double)2.0 : (double)4.0)); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)(F_pj((M((c_vopt + (l_o + 1.0))) + ((B(rt_and(l_k, 1.0)) ? (double)l_ux : (double)(-l_ux)) * l_hl)), (M((c_vopt + (l_o + 2.0))) + ((B(rt_and(l_k, 1.0)) ? (double)l_uy : (double)(-l_uy)) * l_hl)), (B(rt_and(l_k, 2.0)) ? (double)M((c_vopt + (l_o + 5.0))) : (double)0.0))), (void)(ASG(c_vzbx0, rt_min(c_vzbx0, g_qx))), (void)(ASG(c_vzbx1, rt_max(c_vzbx1, g_qx))), (void)(ASG(c_vzby0, rt_min(c_vzby0, g_qy))), (void)(ASG(c_vzby1, rt_max(c_vzby1, g_qy))), (l_k += 1.0))); } return 0.0; }()) : 0.0)), (l_r += 1.0))); } g_vzbx0 = c_vzbx0; g_vzbx1 = c_vzbx1; g_vzby0 = c_vzby0; g_vzby1 = c_vzby1; return 0.0; }()) : 0.0));
}

double Gen::F_vzfit() {
  double l_cx = 0.0, l_cy = 0.0, l_f = 0.0, l_x0 = 0.0, l_x1 = 0.0, l_y0 = 0.0, l_y1 = 0.0; 
  return ((void)(F_vzfbox()), (void)((l_cx = (g_vx + (g_vw / 2.0)))), (void)((l_cy = (g_vy + (g_vh / 2.0)))), (void)((l_x0 = (l_cx + (((g_vzbx0 - l_cx) - g_vzox) / g_vzf)))), (void)((l_x1 = (l_cx + (((g_vzbx1 - l_cx) - g_vzox) / g_vzf)))), (void)((l_y0 = (l_cy + (((g_vzby0 - l_cy) - g_vzoy) / g_vzf)))), (void)((l_y1 = (l_cy + (((g_vzby1 - l_cy) - g_vzoy) / g_vzf)))), (void)((l_f = rt_min(5.0, rt_max(0.1, rt_min(((g_vw - 96.0) / rt_max(1.0, (l_x1 - l_x0))), ((g_vh - 100.0) / rt_max(1.0, (l_y1 - l_y0)))))))), (void)(ASG(g_vzox, (g_vx + (((g_vw / 2.0) - l_cx) - ((((l_x0 + l_x1) / 2.0) - l_cx) * l_f))))), (void)(ASG(g_vzoy, ((g_vy + 46.0) + ((((g_vh - 100.0) / 2.0) - l_cy) - ((((l_y0 + l_y1) / 2.0) - l_cy) * l_f))))), (g_vzf = l_f));
}

double Gen::F_wallcol(double l_a, double l_al) {
  
  return ((void)(ASG(v_gfx_r, ((120.0 + (g_wlift - (90.0 * l_a))) / 255.0))), (void)(ASG(v_gfx_g, (((120.0 + g_wlift) + (40.0 * l_a)) / 255.0))), (void)(ASG(v_gfx_b, ((120.0 + (g_wlift - (20.0 * l_a))) / 255.0))), (void)((v_gfx_a = l_al)), F_gmono());
}

double Gen::F_wmata(double l_k) {
  
  return (EQ(l_k, 0.0) ? (double)0.02 : (double)(EQ(l_k, 1.0) ? (double)0.03 : (double)(EQ(l_k, 2.0) ? (double)0.04 : (double)(EQ(l_k, 3.0) ? (double)0.05 : (double)(EQ(l_k, 4.0) ? (double)0.08 : (double)(EQ(l_k, 5.0) ? (double)0.1 : (double)(EQ(l_k, 6.0) ? (double)0.45 : (double)(EQ(l_k, 7.0) ? (double)0.7 : (double)0.85))))))));
}

double Gen::F_wmatd(double l_k) {
  
  return (EQ(l_k, 0.0) ? (double)45.0 : (double)(EQ(l_k, 1.0) ? (double)28.0 : (double)(EQ(l_k, 2.0) ? (double)65.0 : (double)(EQ(l_k, 3.0) ? (double)80.0 : (double)(EQ(l_k, 4.0) ? (double)20.0 : (double)(EQ(l_k, 5.0) ? (double)70.0 : (double)(EQ(l_k, 6.0) ? (double)80.0 : (double)(EQ(l_k, 7.0) ? (double)85.0 : (double)90.0))))))));
}

double Gen::F_wmatname(double l_k) {
  
  return (EQ(l_k, 0.0) ? (double)10043.0 : (double)(EQ(l_k, 1.0) ? (double)10037.0 : (double)(EQ(l_k, 2.0) ? (double)10044.0 : (double)(EQ(l_k, 3.0) ? (double)10036.0 : (double)(EQ(l_k, 4.0) ? (double)10038.0 : (double)(EQ(l_k, 5.0) ? (double)10039.0 : (double)(EQ(l_k, 6.0) ? (double)10040.0 : (double)(EQ(l_k, 7.0) ? (double)10041.0 : (double)10042.0))))))));
}

double Gen::F_wmattip(double l_k) {
  
  return (EQ(l_k, 0.0) ? (double)11841.0 : (double)(EQ(l_k, 1.0) ? (double)11842.0 : (double)(EQ(l_k, 2.0) ? (double)11843.0 : (double)(EQ(l_k, 3.0) ? (double)11844.0 : (double)(EQ(l_k, 4.0) ? (double)11845.0 : (double)(EQ(l_k, 5.0) ? (double)11846.0 : (double)(EQ(l_k, 6.0) ? (double)11847.0 : (double)(EQ(l_k, 7.0) ? (double)11848.0 : (double)11849.0))))))));
}

double Gen::F_wmgeo() {
  
  return ((void)((g_wmih = 16.0)), (void)(ASG(g_wmn, (EQ(g_wmenu, 1.0) ? (double)6.0 : (double)9.0))), (void)(ASG(g_wmh, ((g_wmn * g_wmih) + 8.0))), (void)(ASG(g_wmxx, (EQ(g_wmenu, 1.0) ? g_wsx : g_wmx2))), (void)(ASG(g_wmw, (EQ(g_wmenu, 1.0) ? g_wdw : g_wdw2))), (void)(F_mfit((EQ(g_wmenu, 1.0) ? g_wsx : g_wmx2), (EQ(g_wmenu, 1.0) ? g_wdy1 : g_wdy2), g_wmw, (EQ(g_wmenu, 1.0) ? (double)15.0 : (double)g_wdh), g_wmw, g_wmh, 0.0)), (void)((g_wmxx = g_mfx)), (void)((g_wmy = g_mfy)), (g_wmk = g_mfk));
}

double Gen::F_wrapt(double l_s, double l_x, double l_y, double l_w, double l_lnh) {
  double l_c = 0.0, l_i = 0.0, l_ly = 0.0, l_n = 0.0; 
  return ((void)(strcpy(90062.0, l_s)), (void)((l_n = strlen(90062.0))), (void)(strcpy(90063.0, 10120.0)), (void)(strcpy(90064.0, 10120.0)), (void)((l_ly = l_y)), (void)((l_i = 0.0)), (void)([&]() -> double { int n_ = rt_i32((l_n + 1.0)); if (n_ > 1048576) n_ = 1048576; for (; n_ > 0; --n_) { (void)(((void)((l_c = ((l_i < l_n) ? (double)str_getchar({90062.0, l_i}) : (double)32.0))), (void)((EQ(l_c, 32.0) ? (double)((void)(strcpy(90065.0, 90063.0)), (void)(((strlen(90065.0) > 0.0) ? (double)strcat(90065.0, 11850.0) : 0.0)), (void)(strcat(90065.0, 90064.0)), (void)((((F_tws(90065.0) > l_w) && (strlen(90063.0) > 0.0)) ? (double)((void)(F_txt(90063.0, l_x, l_ly, 0.0)), (void)((l_ly += l_lnh)), strcpy(90063.0, 90064.0)) : (double)strcpy(90063.0, 90065.0))), strcpy(90064.0, 10120.0)) : (double)((void)(sprintf({90066.0, 11677.0, l_c})), strcat(90064.0, 90066.0)))), (l_i += 1.0))); } return 0.0; }()), (void)(((strlen(90063.0) > 0.0) ? (double)((void)(F_txt(90063.0, l_x, l_ly, 0.0)), (l_ly += l_lnh)) : 0.0)), (l_ly - l_y));
}

double Gen::F_wring(double l_cx, double l_cy, double l_cz, double l_wrr, double l_y0, double l_y1, double l_al, double l_c) {
  double l_a0 = 0.0, l_a1 = 0.0, l_f = 0.0, l_hx = 0.0, l_hy = 0.0, l_i = 0.0, l_n = 0.0, l_wxa = 0.0, l_wxb = 0.0, l_wxm = 0.0, l_wya = 0.0, l_wyb = 0.0, l_wym = 0.0; 
  return ((void)((l_n = rt_max(16.0, rt_min(72.0, rt_floor((l_wrr * (g_ps / 4.0))))))), (void)((l_i = 0.0)), [&]() -> double { int n_ = rt_i32(l_n); if (n_ > 1048576) n_ = 1048576; double c_bon = g_bon, c_roomw = g_roomw, c_yb = g_yb; for (; n_ > 0; --n_) { (void)(((void)((l_a0 = (6.283185307179586 * (l_i / l_n)))), (void)((l_a1 = (6.283185307179586 * ((l_i + 1.0) / l_n)))), (void)((l_wxa = (l_cx + (l_wrr * rt_cos(l_a0))))), (void)((l_wya = (l_cy + (l_wrr * rt_sin(l_a0))))), (void)((l_wxb = (l_cx + (l_wrr * rt_cos(l_a1))))), (void)((l_wyb = (l_cy + (l_wrr * rt_sin(l_a1))))), (void)((l_wxm = (0.5 * (l_wxa + l_wxb)))), (void)((l_wym = (0.5 * (l_wya + l_wyb)))), (void)((((((l_wxm >= 0.0) && (l_wxm <= c_roomw)) && (l_wym >= l_y0)) && (l_wym <= l_y1)) ? (double)((void)((l_f = ((B(c_bon) && (((l_wym - c_yb) * (l_cy - c_yb)) < 0.0)) ? (double)0.22 : (double)1.0))), (void)(F_col(l_c, (l_al * l_f))), (void)(F_pj(l_wxa, l_wya, l_cz)), (void)((l_hx = g_qx)), (void)((l_hy = g_qy)), (void)(F_pj(l_wxb, l_wyb, l_cz)), F_lnw(l_hx, l_hy, g_qx, g_qy, 1.3)) : 0.0)), (l_i += 1.0))); } return 0.0; }());
}

double Gen::F_wsurfname(double l_k) {
  
  return (EQ(l_k, 0.0) ? (double)11851.0 : (double)(EQ(l_k, 1.0) ? (double)11852.0 : (double)(EQ(l_k, 2.0) ? (double)11853.0 : (double)(EQ(l_k, 3.0) ? (double)11854.0 : (double)(EQ(l_k, 4.0) ? (double)11855.0 : (double)10894.0)))));
}

double Gen::F_wthick(double l_a) {
  
  return ((l_a < 0.035) ? (double)11856.0 : (double)((l_a < 0.07) ? (double)11857.0 : (double)((l_a < 0.15) ? (double)11858.0 : (double)((l_a < 0.25) ? (double)11859.0 : (double)((l_a < 0.38) ? (double)11860.0 : (double)((l_a < 0.52) ? (double)11861.0 : (double)((l_a < 0.65) ? (double)11862.0 : (double)((l_a < 0.78) ? (double)11863.0 : (double)((l_a < 0.92) ? (double)11864.0 : (double)11865.0)))))))));
}

double Gen::F_wtip(double l_s, double l_a) {
  
  return ((void)(sprintf({90067.0, 11866.0, l_s, F_wthick(l_a)})), 90067.0);
}

double Gen::F_xpname(double l_k) {
  
  return (EQ(l_k, 0.0) ? (double)10798.0 : (double)(EQ(l_k, 1.0) ? (double)10926.0 : (double)(EQ(l_k, 2.0) ? (double)11867.0 : (double)(EQ(l_k, 3.0) ? (double)11868.0 : (double)(EQ(l_k, 4.0) ? (double)10854.0 : (double)(EQ(l_k, 5.0) ? (double)11869.0 : (double)(EQ(l_k, 6.0) ? (double)11870.0 : (double)(EQ(l_k, 7.0) ? (double)10601.0 : (double)(EQ(l_k, 8.0) ? (double)11871.0 : (double)(EQ(l_k, 9.0) ? (double)11872.0 : (double)(EQ(l_k, 10.0) ? (double)11873.0 : (double)(EQ(l_k, 11.0) ? (double)10159.0 : (double)(EQ(l_k, 12.0) ? (double)11874.0 : (double)(EQ(l_k, 13.0) ? (double)10835.0 : (double)(EQ(l_k, 14.0) ? (double)11875.0 : (double)10965.0)))))))))))))));
}
}
