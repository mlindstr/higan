//legend:
//  a   = register A
//  c   = condition
//  e   = relative operand
//  in  = (operand)
//  inn = (operand-word)
//  irr = (register-word)
//  o   = opcode bits
//  n   = operand
//  nn  = operand-word
//  r   = register

auto Z80::ADD(uint8 x, uint8 y, bool c) -> uint8 {
  uint9 z = x + y + c;

  CF = z.bit(8);
  NF = 0;
  VF = ~(x ^ y) & (x ^ z) & 0x80;
  XF = z.bit(3);
  HF = (x ^ y ^ z) & 0x10;
  YF = z.bit(5);
  ZF = (uint8)z == 0;
  SF = z.bit(7);

  return z;
}

auto Z80::AND(uint8 x, uint8 y) -> uint8 {
  uint8 z = x & y;

  CF = 0;
  NF = 0;
  PF = parity(z);
  XF = z.bit(3);
  HF = 1;
  YF = z.bit(5);
  ZF = z == 0;
  SF = z.bit(7);

  return z;
}

auto Z80::BIT(uint3 bit, uint8 x) -> void {
  NF = 0;
  HF = 1;
  ZF = (x & 1 << bit) == 0;
}

auto Z80::DEC(uint8 x) -> uint8 {
  uint8 z = x - 1;

  NF = 1;
  VF = z == 0x7f;
  XF = z.bit(3);
  HF = z.bits(0,3) == 0x0f;
  YF = z.bit(5);
  ZF = z == 0;
  SF = z.bit(7);

  return z;
}

auto Z80::INC(uint8 x) -> uint8 {
  uint8 z = x + 1;

  NF = 0;
  VF = z == 0x80;
  XF = z.bit(3);
  HF = z.bits(0,3) == 0x00;
  YF = z.bit(5);
  ZF = z == 0;
  SF = z.bit(7);

  return z;
}

auto Z80::OR(uint8 x, uint8 y) -> uint8 {
  uint8 z = x | y;

  CF = 0;
  NF = 0;
  PF = parity(z);
  XF = z.bit(3);
  HF = 0;
  YF = z.bit(5);
  ZF = z == 0;
  SF = z.bit(7);

  return z;
}

auto Z80::RES(uint3 bit, uint8 x) -> uint8 {
  x &= ~(1 << bit);
  return x;
}

auto Z80::RL(uint8 x) -> uint8 {
  bool c = x.bit(7);
  x = x << 1 | CF;

  CF = c;
  NF = 0;
  PF = parity(x);
  XF = x.bit(3);
  HF = 0;
  YF = x.bit(5);
  ZF = x == 0;
  SF = x.bit(7);

  return x;
}

auto Z80::RLC(uint8 x) -> uint8 {
  x = x << 1 | x >> 7;

  CF = x.bit(0);
  NF = 0;
  PF = parity(x);
  XF = x.bit(3);
  HF = 0;
  YF = x.bit(5);
  ZF = x == 0;
  SF = x.bit(7);

  return x;
}

auto Z80::RR(uint8 x) -> uint8 {
  bool c = x.bit(0);
  x = x >> 1 | CF << 7;

  CF = c;
  NF = 0;
  PF = parity(x);
  XF = x.bit(3);
  HF = 0;
  YF = x.bit(5);
  ZF = x == 0;
  SF = x.bit(7);

  return x;
}

auto Z80::RRC(uint8 x) -> uint8 {
  x = x >> 1 | x << 7;

  CF = x.bit(7);
  NF = 0;
  PF = parity(x);
  XF = x.bit(3);
  HF = 0;
  YF = x.bit(5);
  ZF = x == 0;
  SF = x.bit(7);

  return x;
}

auto Z80::SET(uint3 bit, uint8 x) -> uint8 {
  x |= (1 << bit);
  return x;
}

auto Z80::SLA(uint8 x) -> uint8 {
  bool c = x.bit(7);
  x = x << 1;

  CF = c;
  NF = 0;
  PF = parity(x);
  XF = x.bit(3);
  HF = 0;
  YF = x.bit(5);
  ZF = x == 0;
  SF = x.bit(7);

  return x;
}

auto Z80::SLL(uint8 x) -> uint8 {
  bool c = x.bit(7);
  x = x << 1 | 1;

  CF = c;
  NF = 0;
  PF = parity(x);
  XF = x.bit(3);
  HF = 0;
  YF = x.bit(5);
  ZF = x == 0;
  SF = x.bit(7);

  return x;
}

auto Z80::SRA(uint8 x) -> uint8 {
  bool c = x.bit(0);
  x = (int8)x >> 1;

  CF = c;
  NF = 0;
  PF = parity(x);
  XF = x.bit(3);
  HF = 0;
  YF = x.bit(5);
  ZF = x == 0;
  SF = x.bit(7);

  return x;
}

auto Z80::SRL(uint8 x) -> uint8 {
  bool c = x.bit(0);
  x = x >> 1;

  CF = c;
  NF = 0;
  PF = parity(x);
  XF = x.bit(3);
  HF = 0;
  YF = x.bit(5);
  ZF = x == 0;
  SF = x.bit(7);

  return x;
}

auto Z80::SUB(uint8 x, uint8 y, bool c) -> uint8 {
  uint9 z = x - y - c;

  CF = z.bit(8);
  NF = 1;
  VF = (x ^ y) & (x ^ z) & 0x80;
  XF = z.bit(3);
  HF = (x ^ y ^ z) & 0x10;
  YF = z.bit(5);
  ZF = (uint8)z == 0;
  SF = z.bit(7);

  return z;
}

auto Z80::XOR(uint8 x, uint8 y) -> uint8 {
  uint8 z = x ^ y;

  CF = 0;
  NF = 0;
  PF = parity(z);
  XF = z.bit(3);
  HF = 0;
  YF = z.bit(5);
  ZF = z == 0;
  SF = z.bit(7);

  return z;
}

//

auto Z80::instructionADC_a_irr(uint16& x) -> void {
  A = ADD(A, read(displace(x)), CF);
}

auto Z80::instructionADC_a_r(uint8& x) -> void {
  A = ADD(A, x, CF);
}

auto Z80::instructionADD_a_irr(uint16& x) -> void {
  A = ADD(A, read(displace(x)));
}

auto Z80::instructionADD_a_r(uint8& x) -> void {
  A = ADD(A, x);
}

auto Z80::instructionADD_rr_rr(uint16& x, uint16& y) -> void {
  wait(4);
  x.byte(0) = ADD(x.byte(0), y.byte(0));
  wait(3);
  x.byte(1) = ADD(x.byte(1), y.byte(1), CF);
}

auto Z80::instructionAND_a_irr(uint16& x) -> void {
  A = AND(A, read(displace(x)));
}

auto Z80::instructionAND_a_r(uint8& x) -> void {
  A = AND(A, x);
}

auto Z80::instructionBIT_o_irr(uint3 bit, uint16& x) -> void {
  BIT(bit, read(displace(x)));
}

auto Z80::instructionBIT_o_r(uint3 bit, uint8& x) -> void {
  BIT(bit, x);
}

auto Z80::instructionCCF() -> void {
  CF = !CF;
  NF = 0;
  HF = !CF;
}

auto Z80::instructionCP_a_irr(uint16& x) -> void {
  SUB(A, read(displace(x)));
}

auto Z80::instructionCP_a_n() -> void {
  SUB(A, operand());
}

auto Z80::instructionCP_a_r(uint8& x) -> void {
  SUB(A, x);
}

auto Z80::instructionCPD() -> void {
  auto data = read(_HL--);
  SUB(A, data);
  VF = --BC > 0;
  wait(5);
}

auto Z80::instructionCPDR() -> void {
  instructionCPD();
  if(!VF || ZF) return;
  wait(5);
  PC -= 2;
}

auto Z80::instructionCPI() -> void {
  auto data = read(_HL++);
  SUB(A, data);
  VF = --BC > 0;
  wait(5);
}

auto Z80::instructionCPIR() -> void {
  instructionCPI();
  if(!VF || ZF) return;
  wait(5);
  PC -= 2;
}

auto Z80::instructionCPL() -> void {
  A = ~A;

  NF = 1;
  XF = A.bit(3);
  HF = 1;
  YF = A.bit(5);
}

auto Z80::instructionDEC_irr(uint16& x) -> void {
  auto addr = displace(x);
  auto data = read(addr);
  wait(1);
  write(addr, DEC(data));
}

auto Z80::instructionDEC_r(uint8& x) -> void {
  x = DEC(x);
}

auto Z80::instructionDEC_rr(uint16& x) -> void {
  wait(2);
  x--;
}

auto Z80::instructionDI() -> void {
  r.iff1 = 0;
  r.iff2 = 0;
}

auto Z80::instructionEI() -> void {
  r.iff1 = 1;
  r.iff2 = 1;
}

auto Z80::instructionEX_rr_rr(uint16& x, uint16& y) -> void {
  auto z = x;
  x = y;
  y = z;
}

auto Z80::instructionHALT() -> void {
  r.halt = 1;
}

auto Z80::instructionIM_o(uint2 code) -> void {
  wait(4);
  r.im = code;
}

auto Z80::instructionIN_a_in() -> void {
  A = in(operand());
}

auto Z80::instructionINC_irr(uint16& x) -> void {
  auto addr = displace(x);
  auto data = read(addr);
  wait(1);
  write(addr, INC(data));
}

auto Z80::instructionINC_r(uint8& x) -> void {
  x = INC(x);
}

auto Z80::instructionINC_rr(uint16& x) -> void {
  wait(2);
  x++;
}

//note: should be T(4,5,3,4); is instead T(4,4,4,4)
auto Z80::instructionIND() -> void {
  auto data = in(C);
  write(_HL--, data);
  NF = 0;
  ZF = --BC > 0;
  wait(4);
}

auto Z80::instructionINDR() -> void {
  instructionIND();
  if(!ZF) return;
  wait(5);
  PC -= 2;
}

//note: should be T(4,5,3,4); is instead T(4,4,4,4)
auto Z80::instructionINI() -> void {
  auto data = in(C);
  write(_HL++, data);
  NF = 0;
  ZF = --BC > 0;
  wait(4);
}

auto Z80::instructionINIR() -> void {
  instructionINI();
  if(!ZF) return;
  wait(5);
  PC -= 2;
}

auto Z80::instructionJP_c_nn(bool c) -> void {
  auto pc = operands();
  if(c) r.pc = pc;
}

auto Z80::instructionJR_c_e(bool c) -> void {
  auto e = operand();
  if(c) wait(5), r.pc += (int8)e;
}

auto Z80::instructionLD_a_inn() -> void {
  A = read(operands());
}

auto Z80::instructionLD_a_irr(uint16& x) -> void {
  A = read(displace(x));
}

auto Z80::instructionLD_inn_a() -> void {
  write(operands(), A);
}

auto Z80::instructionLD_inn_rr(uint16& x) -> void {
  auto addr = operands();
  write(addr + 0, x >> 0);
  write(addr + 1, x >> 8);
}

auto Z80::instructionLD_irr_a(uint16& x) -> void {
  write(displace(x), A);
}

auto Z80::instructionLD_irr_n(uint16& x) -> void {
  auto addr = displace(x);
  write(addr, operand());
}

auto Z80::instructionLD_irr_r(uint16& x, uint8& y) -> void {
  write(displace(x), y);
}

auto Z80::instructionLD_r_n(uint8& x) -> void {
  x = operand();
}

auto Z80::instructionLD_r_irr(uint8& x, uint16& y) -> void {
  x = read(displace(y));
}

auto Z80::instructionLD_r_r(uint8& x, uint8& y) -> void {
  x = y;
}

auto Z80::instructionLD_rr_inn(uint16& x) -> void {
  auto addr = operands();
  x.byte(0) = read(addr + 0);
  x.byte(1) = read(addr + 1);
}

auto Z80::instructionLD_rr_nn(uint16& x) -> void {
  x = operands();
}

auto Z80::instructionLDD() -> void {
  auto data = read(_HL--);
  write(DE--, data);
  wait(2);
  NF = 0;
  VF = --BC > 0;
  HF = 0;
}

auto Z80::instructionLDDR() -> void {
  instructionLDD();
  if(!VF) return;
  wait(5);
  PC -= 2;
}

auto Z80::instructionLDI() -> void {
  auto data = read(_HL++);
  write(DE++, data);
  wait(2);
  NF = 0;
  VF = --BC > 0;
  HF = 0;
}

auto Z80::instructionLDIR() -> void {
  instructionLDI();
  if(!VF) return;
  wait(5);
  PC -= 2;
}

auto Z80::instructionNOP() -> void {
}

auto Z80::instructionOR_a_irr(uint16& x) -> void {
  A = OR(A, read(displace(x)));
}

auto Z80::instructionOR_a_r(uint8& x) -> void {
  A = OR(A, x);
}

auto Z80::instructionOTDR() -> void {
  instructionOUTD();
  if(!ZF) return;
  wait(5);
  PC -= 2;
}

auto Z80::instructionOTIR() -> void {
  instructionOUTI();
  if(!ZF) return;
  wait(5);
  PC -= 2;
}

//note: should be T(4,5,3,4); instead is T(4,4,4,4)
auto Z80::instructionOUTD() -> void {
  auto data = read(_HL--);
  out(C, data);
  NF = 1;
  ZF = --BC > 0;
}

//note: should be T(4,5,3,4); instead is T(4,4,4,4)
auto Z80::instructionOUTI() -> void {
  auto data = read(_HL++);
  out(C, data);
  NF = 1;
  ZF = --BC > 0;
}

auto Z80::instructionRES_o_irr(uint3 bit, uint16& x) -> void {
  auto addr = displace(x);
  write(addr, RES(bit, read(addr)));
}

auto Z80::instructionRES_o_r(uint3 bit, uint8& x) -> void {
  x = RES(bit, x);
}

auto Z80::instructionRL_irr(uint16& x) -> void {
  auto addr = displace(x);
  write(addr, RL(read(addr)));
}

auto Z80::instructionRL_r(uint8& x) -> void {
  x = RL(x);
}

auto Z80::instructionRLA() -> void {
  bool c = A.bit(7);
  A = A << 1 | CF;

  CF = c;
  NF = 0;
  XF = A.bit(3);
  HF = 0;
  YF = A.bit(5);
}

auto Z80::instructionRLC_irr(uint16& x) -> void {
  auto addr = displace(x);
  write(addr, RLC(read(addr)));
}

auto Z80::instructionRLC_r(uint8& x) -> void {
  x = RLC(x);
}

auto Z80::instructionRLCA() -> void {
  bool c = A.bit(7);
  A = A << 1 | c;

  CF = c;
  NF = 0;
  XF = A.bit(3);
  HF = 0;
  YF = A.bit(5);
}

auto Z80::instructionRR_irr(uint16& x) -> void {
  auto addr = displace(x);
  write(addr, RR(read(addr)));
}

auto Z80::instructionRR_r(uint8& x) -> void {
  x = RR(x);
}

auto Z80::instructionRRA() -> void {
  bool c = A.bit(0);
  A = CF << 7 | A >> 1;

  CF = c;
  NF = 0;
  XF = A.bit(3);
  HF = 0;
  YF = A.bit(5);
}

auto Z80::instructionRRC_irr(uint16& x) -> void {
  auto addr = displace(x);
  write(addr, RRC(read(addr)));
}

auto Z80::instructionRRC_r(uint8& x) -> void {
  x = RRC(x);
}

auto Z80::instructionRRCA() -> void {
  bool c = A.bit(0);
  A = c << 7 | A >> 1;

  CF = c;
  NF = 0;
  XF = A.bit(3);
  HF = 0;
  YF = A.bit(5);
}

auto Z80::instructionSBC_a_irr(uint16& x) -> void {
  A = SUB(A, read(displace(x)), CF);
}

auto Z80::instructionSBC_a_r(uint8& x) -> void {
  A = SUB(A, x, CF);
}

auto Z80::instructionSCF() -> void {
  CF = 1;
  NF = 0;
  HF = 0;
}

auto Z80::instructionSET_o_irr(uint3 bit, uint16& x) -> void {
  auto addr = displace(x);
  write(addr, SET(bit, read(addr)));
}

auto Z80::instructionSET_o_r(uint3 bit, uint8& x) -> void {
  x = SET(bit, x);
}

auto Z80::instructionSLA_irr(uint16& x) -> void {
  auto addr = displace(x);
  write(addr, SLA(read(addr)));
}

auto Z80::instructionSLA_r(uint8& x) -> void {
  x = SLA(x);
}

auto Z80::instructionSLL_irr(uint16& x) -> void {
  auto addr = displace(x);
  write(addr, SLL(read(addr)));
}

auto Z80::instructionSLL_r(uint8& x) -> void {
  x = SLL(x);
}

auto Z80::instructionSRA_irr(uint16& x) -> void {
  auto addr = displace(x);
  write(addr, SRA(read(addr)));
}

auto Z80::instructionSRA_r(uint8& x) -> void {
  x = SRA(x);
}

auto Z80::instructionSRL_irr(uint16& x) -> void {
  auto addr = displace(x);
  write(addr, SRL(read(addr)));
}

auto Z80::instructionSRL_r(uint8& x) -> void {
  x = SRL(x);
}

auto Z80::instructionSUB_a_irr(uint16& x) -> void {
  A = SUB(A, read(displace(x)));
}

auto Z80::instructionSUB_a_r(uint8& x) -> void {
  A = SUB(A, x);
}

auto Z80::instructionXOR_a_irr(uint16& x) -> void {
  A = XOR(A, read(displace(x)));
}

auto Z80::instructionXOR_a_r(uint8& x) -> void {
  A = XOR(A, x);
}
