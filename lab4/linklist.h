/* Vraj Shah */

int deleteSome(void *head, bool (*criteriaFunc)(void *), void (*actionFunc)(void *), int text);
bool insert(void *head, void *data, bool (*comparisonFunc)(void *, void *), int text);
void iterate(void *head , void (*actionFunc)(void *));
void sort(void *head, bool (*comparisonFunc)(void *, void *));
