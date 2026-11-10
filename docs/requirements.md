# Software Requirements

Each requirement has a stable ID. Tests reference IDs with `// @verifies <ID>`,
and `tools/trace.py` builds the traceability matrix from those tags. CI fails if
a requirement has no test or a test names an unknown ID.

| ID | Requirement | Safety | Verification |
|----|-------------|--------|--------------|
| REQ-CRC-001 | The CRC module shall compute CRC-8 SAE J1850 (polynomial 0x1D, initial value 0xFF, final XOR 0xFF). | QM | Unit test |
| REQ-CRC-002 | The CRC module shall return the CRC of an empty block, without dereferencing, when the data pointer is NULL. | QM | Unit test |
| REQ-CRC-003 | The CRC module shall support chained calculation, so that splitting a block across calls gives the same result as one call. | QM | Unit test |
| REQ-RB-001 | The ring buffer shall have a compile-time capacity and shall not use dynamic memory. | QM | Unit test, review |
| REQ-RB-002 | The ring buffer shall reject a push when full and keep existing data unchanged. | QM | Unit test |
| REQ-RB-003 | The ring buffer shall return an empty result when popped while empty. | QM | Unit test |
| REQ-RB-004 | The ring buffer shall return elements in FIFO order, including across index wrap-around. | QM | Unit test |
