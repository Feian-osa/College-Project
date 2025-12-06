# How the 5 Modules Work - Beginner's Guide

## Think of It Like a Restaurant Kitchen 🍽️

Imagine you're running a restaurant. Here's how each module is like a different job in the kitchen:

---

## **Module 1: Inventory (The Main Warehouse)**

### What It Does
**Keeps track of all your stuff** - like a notebook that lists everything you have.

### Real-World Example
You walk into your pantry:
- 50 boxes of pasta 🍝
- 30 bottles of olive oil 🫒
- 10 bags of flour 🌾

### The 5 Jobs It Does (CRUD)

| Job | What It Means | Example |
|-----|--------------|---------|
| **C** - CREATE | Add something new | "We got 50 new pasta boxes today, add them!" |
| **R** - READ | Look at what you have | "Show me all items we have" |
| **U** - UPDATE | Change the amount | "We used 5 pasta boxes, update to 45" |
| **D** - DELETE | Remove something | "We don't sell pasta anymore, remove it" |
| **Stock IN/OUT** | Add or remove items | Adding = stock IN 📥, Using = stock OUT 📤 |

### Data It Stores
```
Item ID:      ITM001
Item Name:    Pasta Boxes
Category:     Food
Quantity:     50 boxes
Reorder Level: 10 boxes (alert when it goes below this)
Price:        $2.50 per box
Date Added:   2025-12-04
```

### Where It Saves
📁 **`inventory.txt`** - A simple text file with a list of everything

---

## **Module 2: ReportWriter (The Manager's Reports)**

### What It Does
**Creates reports** - like when your boss asks "give me a summary of what we have."

### Real-World Example
Your manager says:
- "What's our total inventory value?" 💰
- "Which items are running low?" ⚠️
- "Group items by category" 📊
- "How much money do we have tied up in inventory?" 💸

### The 5 Types of Reports It Generates

| Report Type | What It Shows | Example Output |
|------------|--------------|----------------|
| **Inventory Report** | All items + totals | "We have 50 pasta, 30 oil, 10 flour... Total: $500 value" |
| **Low Stock Report** | Items below reorder level | "Flour is low! Only 10 left, need 20" ⚠️ |
| **Value Report** | Money value of each item | "Pasta = $125, Oil = $75, Flour = $25" 💰 |
| **Category Report** | Items grouped by type | Food: 3 items, Drinks: 2 items 📦 |
| **Quick Summary** | Fast facts on screen | "Total items: 90, Total value: $225" ✅ |

### Where Reports Go
📁 **`Reports/`** - A folder that saves all reports with today's date
- Example: `Inventory_Report_2025-12-04.txt`

---

## **Module 3: LowStockAlert (The Alarm System)**

### What It Does
**Warns you when you're running low** - like an alarm that goes off when supplies are getting scarce.

### Real-World Example
You set a rule: "Alert me when we have less than 10 items"

When you check:
- Pasta: 50 ✅ (plenty, no alarm)
- Olive oil: 15 ✅ (OK, no alarm)
- Flour: 8 🔴 **ALERT!** (only 8, but need 10)

### The 3 Urgency Levels

| Level | What It Means | Symbol | Example |
|-------|--------------|--------|---------|
| **NORMAL** | Low but manageable | ⚠️ | "We have 10 flour, should reorder soon" |
| **CRITICAL** | Very low, urgent! | 🔴 | "We have 5 flour, MUST reorder NOW" |
| **OUT OF STOCK** | ZERO items left! | ⛔ | "NO flour left! Can't serve customers!" |

### 2 Ways It Checks

1. **Default Check** - Uses the default level (10 units)
   - "Show me items below 10"

2. **Custom Check** - You set your own level
   - "Show me items below 20" (different threshold)

### Why It's Useful
Imagine you're closed on Sundays. You check alerts on Friday:
- 🔴 Flour is critical (2 left)
- ✅ Pasta is fine (50 left)

So you order flour NOW, not on Monday when you need it!

---

## **Module 4: TransactionLogger (The Diary/Logbook)**

### What It Does
**Records EVERYTHING that happens** - like a diary that writes down every action, who did it, when, and why.

### Real-World Example
You're an auditor checking the books. You want to know:
- "What happened to the pasta?" 🔍
- "Who deleted the flour item?" 👤
- "When did we add olive oil?" 📅

### What It Records

Each transaction (action) stores:
```
Transaction ID:  TXN0001 (like a receipt number)
Timestamp:       2025-12-04 14:30:45 (date + exact time)
Type:            ADD (what action was it?)
Item ID:         ITM001 (which item?)
Item Name:       Pasta Boxes
Quantity:        50 (how many?)
Description:     "New shipment from supplier" (why?)
```

### The 5 Types of Actions It Logs

| Action | When It Happens | Example |
|--------|-----------------|---------|
| **ADD** | New item created | "Added Pasta to inventory" ✅ |
| **UPDATE** | Item details changed | "Changed pasta price to $2.50" ✏️ |
| **DELETE** | Item removed | "Deleted discontinued flour" ❌ |
| **IN** | Stock added (new shipment) | "Received 50 pasta boxes" 📥 |
| **OUT** | Stock used/sold | "Sold 5 pasta boxes" 📤 |

### Why It Matters
Imagine your boss asks: "Where did all the flour go?"
- You look at the log and see:
  - TXN0001: Added 100 flour on Dec 1
  - TXN0002: Sold 50 flour on Dec 2
  - TXN0003: Sold 40 flour on Dec 3
  - TXN0004: Sold 10 flour on Dec 4
  - Total: 100 - 50 - 40 - 10 = 0 left ✅ (explains everything!)

---

## **Module 5: Utilities (The Helper/Tools Box)**

### What It Does
**Provides helper functions** - like a toolkit with common tools everyone uses.

### Real-World Example
It's like having:
- A clock 🕐 to get the current date
- Scissors ✂️ to cut things
- A marker 🖍️ to write neatly
- A ruler 📏 for measurements

### The 4 Main Helper Tools

| Tool | What It Does | Example |
|------|--------------|---------|
| **getCurrentDate()** | Gets today's date | Returns: "2025-12-04" |
| **getCurrentDateTime()** | Gets date AND time | Returns: "2025-12-04 14:30:45" |
| **toLower()** | Converts to lowercase | "PASTA" → "pasta" (for comparing) |
| **printHeader()** | Makes pretty titles | Shows: `====== TITLE ======` |
| **printSeparator()** | Makes dividing lines | Shows: `========================` |

### Why It's Useful
Instead of every module writing its own date function, they all share ONE tool.
- Saves time ⏰
- No duplicates 🚫
- Easier to fix if something breaks 🔧

---

## How They All Work Together 🔄

### Picture This Scenario:

**Time: Monday 9:00 AM**

```
YOU (User)
   ↓
[INVENTORY Module]  ← You add 100 pasta boxes
   ↓
[TRANSACTION Logger] ← Records: "TXN0001: Added 100 pasta, 2025-12-04 09:00"
   ↓
[LOW STOCK ALERT] ← Checks: "We have 100 pasta, reorder level is 10... ALL GOOD ✅"
   ↓
[UTILITIES] ← Gets the date "2025-12-04" using getCurrentDate()
```

---

**Time: Wednesday 3:00 PM**

```
YOU (User)
   ↓
[INVENTORY Module] ← You sell 95 pasta boxes (update quantity to 5)
   ↓
[TRANSACTION Logger] ← Records: "TXN0002: OUT 95 pasta, 2025-12-04 15:00"
   ↓
[LOW STOCK ALERT] ← Checks: "Only 5 left, but need 10... CRITICAL! 🔴"
   ↓
[UTILITIES] ← Gets the time "2025-12-04 15:00:00" using getCurrentDateTime()
```

---

**Time: Thursday Morning**

```
YOU (User)
   ↓
[REPORT WRITER] ← Boss asks "Show me what's low"
   ↓
[LOW STOCK ALERT] ← Provides list of low items
   ↓
[REPORT WRITER] ← Creates file: "LowStock_Report_2025-12-04.txt"
   ↓
[UTILITIES] ← Gets date to put in filename
   ↓
📄 Report saved!
```

---

## Simple Flow Chart

```
                     ┌──────────────┐
                     │   YOU        │
                     │  (Menu UI)   │
                     └──────┬───────┘
                            │
          ┌─────────────────┼─────────────────┐
          │                 │                 │
          ↓                 ↓                 ↓
    ┌──────────────┐ ┌──────────────┐ ┌──────────────┐
    │  INVENTORY   │ │   REPORTS    │ │   ALERTS     │
    │  (CRUD Ops)  │ │  (Generate)  │ │  (Monitor)   │
    └──────┬───────┘ └──────┬───────┘ └──────┬───────┘
           │                │                │
           └────────────────┼────────────────┘
                            │
                     ┌──────▼───────┐
                     │ TRANSACTION  │
                     │   LOGGER     │
                     │ (Records All)│
                     └──────┬───────┘
                            │
                     ┌──────▼───────┐
                     │  UTILITIES   │
                     │ (Helpers)    │
                     └──────────────┘
```

---

## Let's Say You're Making Pizza 🍕

### Start of Day
1. **INVENTORY** - Check your ingredients: "I have 20 flour, 10 cheese, 5 tomato sauce"
2. **LOW STOCK ALERT** - See that tomato sauce is low (only 5, need 10)
3. **UTILITIES** - System gets today's date "2025-12-04"

### During Service
4. **INVENTORY** - Customer orders 3 pizzas: Update flour from 20 → 17
5. **TRANSACTION LOGGER** - Records: "OUT 3 flour portions at 12:30 PM"

### End of Day
6. **REPORT WRITER** - Creates report: "Today we sold 30 pizzas, used 30 flour, 15 cheese, 10 tomato sauce"
7. **TRANSACTION LOGGER** - Boss checks: "Show me all OUT transactions (everything we sold)"
8. **LOW STOCK ALERT** - System warns: "We're low on tomato sauce (0 left)! Order more!"

---

## Quick Comparison

| Module | Like What? | Main Job |
|--------|-----------|----------|
| **INVENTORY** | Your shopping list 📝 | Keep track of everything |
| **REPORT WRITER** | Your boss's summary 📊 | Create reports & analysis |
| **LOW STOCK ALERT** | Your phone alarm ⏰ | Warn when things are low |
| **TRANSACTION LOGGER** | Your diary 📔 | Record everything that happened |
| **UTILITIES** | Your toolbox 🧰 | Provide common helper tools |

---

## Why This Design?

**Instead of ONE HUGE program that does everything:**
```
❌ Messy - can't find anything
❌ Confusing - too much to understand
❌ Hard to fix - break one thing, break everything
```

**We split into 5 separate modules:**
```
✅ Clean - each module has one job
✅ Easy - you understand each part separately
✅ Safe - fix one, don't break others
✅ Reusable - can use same module in different programs
```

---

## Summary: The 5 Modules in One Sentence Each

1. **INVENTORY** 📦 - Keeps a list of all your stuff and lets you add/edit/delete items
2. **REPORT WRITER** 📊 - Creates reports (summaries) about your inventory
3. **LOW STOCK ALERT** ⚠️ - Warns you when items are running low
4. **TRANSACTION LOGGER** 📔 - Records every single action that happens
5. **UTILITIES** 🧰 - Provides helper tools that everyone uses

---

## Still Confused? Ask Yourself This 🤔

**Q: What do I use if I want to ADD pasta to inventory?**  
A: INVENTORY module

**Q: What do I use if I want to SEE a report of all low stock items?**  
A: REPORT WRITER module (which uses LOW STOCK ALERT to get data)

**Q: What do I use if I want to know WHEN I added something and WHO did it?**  
A: TRANSACTION LOGGER module

**Q: What do I use if I want TODAY'S DATE?**  
A: UTILITIES module

**Q: What do I use to get an ALERT that something is low?**  
A: LOW STOCK ALERT module

---

## Real Example: The Full Journey of One Pasta Order

```
9:00 AM - SUPPLIER DELIVERS 100 PASTA BOXES
├─ YOU: Choose "Add New Item" → INVENTORY module activates
├─ INVENTORY: Saves ITM001 | Pasta | 100 units
├─ TRANSACTION LOGGER: Records TXN0001 | ADD | Pasta | 100 | 2025-12-04 09:00
├─ UTILITIES: Gets date "2025-12-04" for the timestamp
└─ LOW STOCK ALERT: Checks (100 > 10) ✅ ALL GOOD

2:00 PM - YOU SELL 95 PASTA BOXES
├─ YOU: Choose "Adjust Stock" → INVENTORY module activates
├─ INVENTORY: Updates quantity from 100 → 5
├─ TRANSACTION LOGGER: Records TXN0002 | OUT | Pasta | 95 | 2025-12-04 14:00
├─ UTILITIES: Gets date+time "2025-12-04 14:00:00"
└─ LOW STOCK ALERT: Checks (5 < 10) 🔴 CRITICAL! NEED TO REORDER!

3:00 PM - BOSS ASKS FOR A REPORT
├─ YOU: Choose "Generate Low Stock Report" → REPORT WRITER activates
├─ REPORT WRITER: Gets list from LOW STOCK ALERT
├─ REPORT WRITER: Creates file "LowStock_Report_2025-12-04.txt"
├─ TRANSACTION LOGGER: Records TXN0003 | REPORT | Pasta | N/A | "Report generated"
├─ UTILITIES: Gets date for filename
└─ FILE SAVED! Boss can now see which items need reordering

5:00 PM - AUDITOR CHECKS WHAT HAPPENED
├─ YOU: Choose "View Transaction History" → TRANSACTION LOGGER activates
├─ TRANSACTION LOGGER: Shows:
│   TXN0001 | 2025-12-04 09:00 | ADD | 100 pasta
│   TXN0002 | 2025-12-04 14:00 | OUT | 95 pasta
│   TXN0003 | 2025-12-04 15:00 | REPORT generated
└─ AUDITOR: Nods "Perfect! Everything is recorded correctly!"
```

---

## Key Takeaway 🎯

**All 5 modules work together like a TEAM:**

- **INVENTORY** is like the warehouse worker (stores & retrieves items)
- **REPORT WRITER** is like the manager (creates summaries)
- **LOW STOCK ALERT** is like the warning system (alerts when low)
- **TRANSACTION LOGGER** is like the accountant (records everything)
- **UTILITIES** is like the assistant (helps everyone with common tasks)

Together, they create a **complete inventory system** that keeps track of everything! 🎉

---

**Hope this helps you understand!** If you have questions about any specific module, just ask! 😊

