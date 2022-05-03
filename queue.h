struct DataNode {
    DataNode *next; 
    DataNode *prev;
    char data;
    unsigned long freq;
};

class Queue {
    public:
        Queue(unsigned int, DataNode*);
        void enqueue(DataNode*);
        DataNode* dequeue();
        DataNode *head;
        DataNode *tail;
};

Queue::Queue(unsigned int char_count, DataNode *array) {
    this->head = 0;
    this->tail = 0;
}

void Queue::enqueue(DataNode* n) {
    if (this->head == 0) {
        this->head = n;
        n->prev = 0;
    } else {
        n->prev = this->tail;
        n->prev->next = n;
    }
    this->tail = n;
    n->next = 0;
}

DataNode* Queue::dequeue() {
    if (this->tail == 0) {
        return 0;
    } else {
        DataNode *ret_node = this->tail;
        this->tail = this->tail->prev;
        if (this->tail != 0) {
            this->tail->next = 0;
        }
    }
}