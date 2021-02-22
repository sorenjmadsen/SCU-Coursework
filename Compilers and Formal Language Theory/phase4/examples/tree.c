/*
 * tree.c, or I've always thought structures were overrated, didn't you?
 *
 * Structures? We ain't got no structures.  We don't need no structures.
 * I don't have to show you any stinkin' structures!
 *
 * Believe it or not, your compiler will be able to generate assembly code
 * for this program.  Scary, huh?
 */

int printf();
void *malloc(), *null;

void *insert(void **root, void *data)
{
    if (!root) {
	root = malloc(3 * sizeof root);
	root[0] = data;
	root[1] = null;
	root[2] = null;
    } else if (data < root[0])
	root[1] = insert(root[1], data);
    else if (data > root[0])
	root[2] = insert(root[2], data);

    return root;
}

int search(void **root, void *data)
{
    if (!root)
	return 0;

    if (data < root[0])
	return search(root[1], data);

    if (data > root[0])
	return search(root[2], data);

    return 1;
}

void preorder(void **root)
{
    if (root) {
	int *p;
	p = root[0];
	printf("%d\n", *p);
	preorder(root[1]);
	preorder(root[2]);
    }
}

void inorder(void **root)
{
    if (root) {
	int *p;
	p = root[0];
	inorder(root[1]);
	printf("%d\n", *p);
	inorder(root[2]);
    }
}

int main(void)
{
    void **root;
    int a[10], i;

    i = 0;

    while (i < 8) {
	a[i] = i;
	i = i + 1;
    }

    root = null;
    root = insert(root, &a[7]);
    root = insert(root, &a[4]);
    root = insert(root, &a[1]);
    root = insert(root, &a[0]);
    root = insert(root, &a[5]);
    root = insert(root, &a[2]);
    root = insert(root, &a[3]);
    root = insert(root, &a[6]);
    printf("preorder traversal:\n");
    preorder(root);
    printf("inorder traversal:\n");
    inorder(root);
}
