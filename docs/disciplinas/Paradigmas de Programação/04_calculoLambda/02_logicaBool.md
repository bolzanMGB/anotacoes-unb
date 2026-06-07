# Lógica Booleana no Cálculo Lambda

## 1. Definições

### 1.1 True e False

Em Cálculo Lambda, True é retornar o primeiro, enquanto False é retornar o segundo.

$$\mathbf{T \equiv \lambda xy.x}$$

$$\mathbf{F \equiv \lambda xy.y}$$

### 1.2 Condicionais

$$\mathbf{I_F \equiv \lambda pab.pab}$$

$$\mathbf{- p: \,  True \,  ou \,  False.}$$

**Exemplos:** 


$$\mathbf{If \, True \equiv (I_F)Tab \equiv Tab \equiv a}$$

$$\mathbf{If \, False \equiv (I_F)Fab \equiv Fab \equiv b}$$

### 1.3 Operadores Lógicos

#### 1.3.1 AND

$$\mathbf{AND(xy)  \equiv \lambda xy.xyx}$$

**Exemplo:**
$$\mathbf{AND(TT)/AND(TF) → AND(Ty)  \equiv (\lambda xy.xyx)Ty \equiv T(yT) \equiv (\lambda ab.a) yT \equiv y}$$

#### 1.3.2 OR

$$\mathbf{OR(xy)  \equiv \lambda xy.xxy}$$

**Exemplo:**
$$\mathbf{OR(FT)  \equiv (\lambda xy.xxy)FT \equiv F(FT) \equiv (\lambda ab.b) FT \equiv T}$$

#### 1.3.3 NOT

$$\mathbf{NOT(x)  \equiv \lambda x.xFT}$$

**Exemplo:**
$$\mathbf{NOT(F)  \equiv (\lambda x.xFT)F \equiv F(FT) \equiv (\lambda ab.b) FT \equiv T}$$
