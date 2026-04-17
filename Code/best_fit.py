def best_fit(items, capacity):
    bins = []
    for item in items:
        min_space = capacity + 1
        best_bin = None

        for b in bins:
            space = capacity - sum(b)
            if space >= item and space - item < min_space:
                min_space = space - item
                best_bin = b

        if best_bin:
            best_bin.append(item)
        else:
            bins.append([item])
    return bins
