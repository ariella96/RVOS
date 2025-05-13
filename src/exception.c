void handle_exception(unsigned long cause) {
  switch (cause) {
    case 0: // Instruction address misaligned
      break;
    case 1: // Instruction access fault
      break;
    case 2: // Illegal instruction
      break;
    case 3: // Breakpoint
      break;
    case 4: // Load address misaligned
      break;
    case 5: // Load access fault
      break;
    case 6: // Store address misaligned
      break;
    case 7: // Store access fault
      break;
    case 11: // Environment call from M-mode
      break;
    default:
      break;
  }
    
  return;
}