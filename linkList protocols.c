
// 1) Initialization
// 2) Build out the node chain
// 3) Add pages to nodes
// 2) AND 3) Combined node adding and page adding
// 4) Free pages from nodes
// 5) Destroy the node chain 


// 1 of 5: Initialization
// template piece START 1
    // At initialization, always set the node count to ZERO and call the
    // node initializer.
    struct st_node *lines = malloc(sizeof(struct st_node));
    lines->total_nodes = ZERO;
    lines = cs_node_intializer(lines);
// template piece END



// 2 of 5: Build out the node chain
// This can be within a data preparation loop that is for a new page to be added to a new link
// template piece START 2
    // Link a list of nodes together
    int index = 0; // start index at zero.
    // node_quantity is the number of nodes to add.
    while (index < node_quantity)
    {
	    lines = cs_add(lines); // <--- This is the essential part of the loop
	    ++index;
    }
    index = 0;
    lines = cs_element_at(lines, index); // Probably want to go back to node zero
// template piece END



// 3 of 5: Add pages to nodes
// This step can be combined with step 2.
// template piece START 3
    // Add the links to the nodes
    lines = cs_element_at(lines, 0);
    index = 0;
    while (index < lines->total_nodes)
    {

        // Part 1: These two lines are what is essential within the page adding loop.
        struct st_number *number = malloc(sizeof(struct st_number));
        lines->page = number;


        // Part 2: Data manipulation can occur within the loop
        ((struct st_number*)lines->page)->number = lines->index * 100;

        // Part 3: Make sure to go to the next node to add a new page.
        // In a loop that combines steps 2 and 3, this can simply be done by adding
        // a new node to the chain before a page is added to the node.
        ++index;
        if (index < lines->total_nodes)
            lines = cs_element_at(lines, index);
    }
    index = 0;
    lines = cs_element_at(lines, index); // Probably want to go back to node zero
// template piece END


// Link protocols 2 of 5 AND 3 of 5: combined node adding and page adding
    int index = 0;
    int pages_needed = 10; // <--- how ever many nodes and pages are needed to be added to the linked list.
    while (index < pages_needed)
    {
        // From step 2.
	    lines = cs_add(lines); // Removes need for check of step 3, but step 3 depends a prepared chain.


        // From step 3.
        struct st_number *number = malloc(sizeof(struct st_number));
        lines->page = number;

        // Data manipulation can be performed after this.
        ++index;
    }



// 4 of 5: Free pages from the nodes
// template piece START 4
    // Clear links
    index = ZERO;
    while(index < lines->total_nodes)
    {
        lines = cs_element_at(lines, index);
        free((struct st_number*)lines->page);
        ++index;
    }
    index = 0;
    lines = cs_element_at(lines, index); // Probably want to go back to node zero
// template piece END


// 5 of 5: Destroy the node chain
// Test to see if I need the '*' symbol later
cs_clear_nodes(lines);
free(lines);


