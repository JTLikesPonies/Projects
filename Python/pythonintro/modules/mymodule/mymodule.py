def count_vowels(sentence:str) -> dict:
    """Return list of vowels found in sentence"""
    vowels = set('aeiou')
    vowels = ['a', 'e', 'i', 'o', 'u']
    vowel_count = {}
    
    for ch in list(sentence):
        if ch in vowels:
            vowel_count.setdefault(ch,0)
            vowel_count[ch] += 1
        
    return str(sorted(vowel_count.items()))

def find_common_letters(sentence:str, letters:str='python') -> set:
    """Return set of characters common to both arguments"""
    return str(sorted(set(sentence).intersection(set(letters))))
