export const Greeter = (name: string) => `Hello ${name}`;

export function multiply(a: number, b: number) {
  return a * b;
}

export function myUpperCaseImpl(aInput: string | number) {
  if (typeof aInput === 'string') {
    return `${aInput.toUpperCase()} string`;
  }
  return `${aInput} number`;
}
