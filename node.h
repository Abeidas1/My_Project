struct tree_node
{
    struct tree_node *children;
    int least_present_number;
    int greatest_present_number;
    struct list_node *greatest_element;
    struct list_node *least_element;

};
struct list_node
{
    int data;
    int occurrences;
    struct list_node *previous;
    struct list_node *next;
};
//    printf("root.least present number = %d\n", root.least_present_number);
//    printf("root.greatest present number = %d\n", root.greatest_present_number);
//    printf("root.children[2].least present number = %d\n", root.children[2].least_present_number);
//    printf("root.children[2].greatest present number = %d\n", root.children[2].greatest_present_number);
//    printf("root.children[2].children[0].least present number = %d\n", root.children[2].children[0].least_present_number);
//    printf("root.children[2].children[0].greatest present number = %d\n", root.children[2].children[0].greatest_present_number);
//    printf("root.children[2].children[0].children[0].least present number = %d\n", root.children[2].children[0].children[0].least_present_number);
//    printf("root.children[2].children[0].children[0].greatest present number = %d\n", root.children[2].children[0].children[0].greatest_present_number);
//    printf("root.children[2].children[0].children[0].children[0].least present number = %d\n", root.children[2].children[0].children[0].children[0].least_present_number);
//    printf("root.children[2].children[0].children[0].children[0].greatest present number = %d\n", root.children[2].children[0].children[0].children[0].greatest_present_number);
