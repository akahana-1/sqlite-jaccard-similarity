import array

def jaccard(s, b, col):
    """
    @args s : 対象とする半角スペース区切り文章
    @args b : matchinfoの出力('pcx')
    @args col : 対象とするcolumnの番号(most left column = 0)
    """
    word_size = len(set(s.split()))
    info = array.array('I', b)
    match_count = 0

    P_OFFSET = 0
    C_OFFSET = 1
    X_OFFSET = 2

    p = info[P_OFFSET]
    c = info[C_OFFSET]

    for i in range(p):
        idx = X_OFFSET + 3 * i * c + col
        phrase_match_count = info[idx]

        if phrase_match_count > 0:
            match_count += 1

    return match_count / (p + word_size - match_count)
