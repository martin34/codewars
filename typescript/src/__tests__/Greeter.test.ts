import { Greeter, multiply, myUpperCaseImpl } from '../index';

test('My Greeter', () => {
  expect(Greeter('Carl')).toBe('Hello Carl');
});

test('Multiply', () => {
  expect(multiply(3, 4)).toBe(12);
});

test('log', () => {
  const car: { type: string; model: string; year: number } = {
    type: 'Toyota',
    model: 'Corolla',
    year: 2009,
  };
  console.log(car);
});

test('UpperCaseString', () => {
  let aString: string = 'abc';
  expect(myUpperCaseImpl(aString)).toBe('ABC string');
});
test('UpperCaseNumber', () => {
  let aNumber = 1.2;
  expect(myUpperCaseImpl(aNumber)).toBe('1.2 number');
});
