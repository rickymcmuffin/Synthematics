# Synthematics
Welcome to Synthematics!

## What is Synthematics?
Synthematics is a Wavetable Synth audio plugin.

## How does it work?
You type in an expression with relation to x, and it creates sound!

## Why do I want to use Synthematics. Wouldn't it be easier to use other Synths?
Synthematics' biggest advantage is learning. You can put in any expression with any frequency and hear what it sounds like. It gives you a better understanding of how sound works and basic DSP. But that doesn't mean you can't make some beautiful music with it. Play around with it and find a sound you like.

## How do I get started?
Well first you're gonna download it from the releases seciton. Then you're gonna input an expression to get some sound. Here's some examples to get you started:

### Sin wave
```
sin(f*2*3.14*x)
```

### Sawtooth wave
```
2*(mod(f*x,1))-1
```

### Triangle wave
```
4*abs(mod(f*x,1)-0.5)-1
```

### Square Wave
```
sign(sin(f*2*3.14*x))
```

## What functions can I use?
Synthematics supports a variety of functions. Here's a list:

Returns the sine of x.
```
sin(x)
```

Returns the cosine of x.
```
cos(x)
```

Returns base^pow.
```
pow(base, pow)
```

If x is greater than 0, returns 1. Else, returns -1.
```
sign(x)
```

Returns x mod interval
```
mod(x, interval)
```

Returns absolute value of x
```
abs(x)
```


