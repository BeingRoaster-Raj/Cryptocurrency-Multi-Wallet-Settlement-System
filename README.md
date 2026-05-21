# Cryptocurrency Multi-Wallet Settlement System

## 📌 Introduction
The **Cryptocurrency Multi-Wallet Settlement System** is a C++17 program that minimizes the number of transactions required to settle debts between multiple crypto wallets.

If two wallets do not support the same cryptocurrency, a **Central Exchange Wallet** acts as an intermediary for settlement.

---

## 🎯 Features
- Net balance calculation
- Optimized transaction settlement
- Multi-cryptocurrency support
- Smart exchange routing
- Bidirectional transaction cancellation
- Detailed settlement report
- No external libraries required

---

## 🔄 Working

### Net Balance
```text
Net Balance = Total Received - Total Sent
```

- Negative → Debtor
- Positive → Creditor

### Settlement Logic
- Direct transfer if wallets share a cryptocurrency
- Otherwise:
```text
Wallet A → Exchange → Wallet B
```

---

## 📥 Input Format

```text
<number_of_wallets>

<wallet_name> <number_of_cryptos> <crypto_list>

<number_of_transactions>

<sender> <receiver> <amount>
```

### Example Input
```text
4
Exchange 2 BTC ETH
Alice 1 BTC
Bob 2 BTC ETH
Charlie 1 ETH
3
Alice Bob 5
Bob Charlie 10
Charlie Alice 8
```

---

## 📤 Output Format

```text
1. Alice transfers 5 BTC to Bob
2. Bob transfers 10 ETH to Charlie

Total Optimized Transactions: X
```

---

## 🚀 Compilation & Execution

### Compile
```bash
g++ -std=c++17 crypto_settlement.cpp -o crypto_settlement
```

### Run
```bash
./crypto_settlement
```

---

## 🔑 Main Functions

| Function | Purpose |
|----------|----------|
| `getMinIndex()` | Finds maximum debtor |
| `getSimpleMaxIndex()` | Finds maximum creditor |
| `getMaxIndex()` | Finds compatible creditor |
| `minimizeCashFlow()` | Main settlement algorithm |
| `printAns()` | Prints optimized transactions |

---

## 📈 Complexity

| Operation | Complexity |
|-----------|-------------|
| Net Balance Calculation | O(W²) |
| Matching Process | O(W²) |
| Overall Complexity | O(W³) |

---

## 💡 Applications
- Investment clubs
- DeFi settlements
- DAO treasury balancing
- Trading groups
- Crypto cooperatives

---

## ⚠️ Production Notes
Before production use:
- Add security verification
- Include gas fee calculations
- Support exchange rates
- Handle failed transactions
- Maintain transaction logs

---

## 🎉 Quick Start

```bash
# Compile
g++ -std=c++17 crypto_settlement.cpp -o crypto_settlement

# Run
./crypto_settlement
```

**Language:** C++17  
**Version:** 1.0  
**Use Case:** Educational & Testing
