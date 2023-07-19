#pragma once

#define CheckNull(p){ if(p == NULL) return;}
#define CheckNullResult(p, result){ if(p == NULL) return result; }

#define CheckTrue(p){ if(p == true) return;}
#define CheckTrueResult(p, result){ if(p == true) return result; }

#define CheckFalse(p){ if(p == false) return;}
#define CheckFalseResult(p, result){ if(p == false) return result; }

#define CAST(Type, Var) static_cast<Type>(Var)

#define MAIN_PARTICLE 0
#define END_PARTICLE 1
#define SUB_PARTICLE 2