# nimiq-vanity-miner
A native miner for Nimiq vanity addresses.

## Installation (Linux/macOS)
The code does not have to be installed.
Just clone the repository and compile it.

```
git clone https://github.com/paberr/nimiq-vanity-miner.git
cd nimiq-vanity-miner
make
```

## Usage
`Usage: vanity_generate prefix [max_rounds] [--exact-match]`

There are three command line arguments you can pass to `vanity_generate`:

1. `prefix`: This argument is non-optional and defines the prefix your address should have.
Important: The longer the prefix, the longer it takes until an address is found.
2. `max_rounds`: Using this option, you can limit the number of tries the program makes before giving up.
3. `--exact-match`: By default, the program uses a mapping (see below) to find similar prefixes. If you activate this option, the program accepts only an exact match of the prefix.

The program will output the current number of tries every 10000 steps.
If a match is found, it will first output the beginning of the address and then a hex dump of the corresponding private key.

## Mapping
By default, the program uses a mapping to represent missing or similar characters in the adress alphabet.
A Nimiq address consists of only the following characters: `0123456789ABCDEFGHJKLMNPQRSTUVXY`.
The program then maps the numbers 0 to 7 to its closest letters in order to find similar matches.
The mapping is as follows:

- 0 -> O
- 1 -> I
- 2 -> Z
- 3 -> E
- 4 -> A
- 5 -> S
- 6 -> G
- 7 -> T
- L -> 1

That means that searching for the prefix `TEST` will also match addresses like `7E5T`.
