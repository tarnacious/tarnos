#ifndef INTERRUPT_H
#define INTERRUPT_H

void enable_interrupts(void);
void disable_interrupts(void);
void handle_pic_int(void);
void handle_cpu_int(void);
void handle_interrupt(void);
void handle_cpu_interrupt(void);

#endif /* INTERRUPT_H */
