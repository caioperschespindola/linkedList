#include <iostream>

class Node{
    public:

        Node(Node* previous = nullptr, int value = 0, Node* next = nullptr){

            this->setPrevious(previous);
            this->setValue(value);
            this->setNext(next);

        }

        int getValue(){ // Returns element currently stored in this node

            return this->value;

        }

        Node* getNext(){ // Returns pointer to next node in list

            return this->next;

        }

        Node* getPrevious(){ // Returns pointer to previous node in list

            return this->previous;

        }

        void setValue(int new_value){ // Sets element stored in this node

            this->value = new_value;

        }

        void setNext(Node* new_next){ // Sets pointer to a new next node

            this->next = new_next;

        }

        void setPrevious(Node* new_previous){ // Sets pointer to a new previous node

            this->previous = new_previous;

        }

        void unsetNext(){ // Sets next node to null pointer

            this->next = nullptr;

        }

        void unsetPrevious(){ // Sets previous node to null pointer

            this->previous = nullptr;

        }

    private:

        int value;
        Node* previous;
        Node* next;

};

class List{
    public:

        List(){

            this->first_node = nullptr;
            this->length = 0;

        }

        int len(){ // Returns list length

            return this->length;

        }

        bool isEmpty(){ // Returns true if list is empty

            return (this->len() == 0);

        }

        void clear(){ // Deletes all nodes in the list

            Node* p_last = this->getNode(this->len() - 1);
            Node* p_previous = p_last->getPrevious();

            for (int i = this->len() - 1; i > 0; i--){
                delete p_last;

                p_last = p_previous;
                p_previous = p_previous->getPrevious();
            }

            delete this->first_node;
            
        }

        int get(int index){ // Returns the value stored at a given index

            if (index >= this->length || index < 0){
                throw "ArrayIndexOutOfBounds";
            } else if (this->isEmpty()){
                return NULL;
            }

            Node* p_target = this->getNode(index);
            return p_target->getValue();

        }

        void set(int value, int index){ // Stores a value in an existing node
            
            if (index >= this->len() || index < 0){
                throw "ArrayIndexOutOfBounds";
            }

            Node* p_target = this->getNode(index);
            p_target->setValue(value);

        }

        void remove(int index){ // Removes a node, pulling back all subsequent nodes

            if (index >= this->len() || index < 0){
                throw "ArrayIndexOutOfBounds";
            }

            Node* p_target = this->getNode(index);

            if (this->len() == 1){

                delete this->first_node;

            } else if (index == 0){

                Node* p_next = p_target->getNext();
                this->first_node = p_next;
                this->first_node->setPrevious(nullptr);

                delete p_target;
                this->length--;
                return;

            } else if (index == this->len() - 1){

                Node previous = *(p_target->getPrevious());
                previous.setNext(nullptr);

                delete p_target;
                this->length--;
                return;

            }

            Node* p_previous = p_target->getPrevious();
            Node* p_next = p_target->getNext();

            p_previous->setNext(p_next);
            p_next->setPrevious(p_previous);

            delete p_target;

            this->length--;
        }

        void add(int value){ // Adds a node with a given value to the end of the list

            if (this->isEmpty()){

                this->first_node = new Node(nullptr, value, nullptr);
                this->length++;
                return;

            }

            Node* p_last = this->getNode(this->len() - 1);
            Node* p_added_node = new Node(p_last, value);

            p_last->setNext(p_added_node);

            this->length++;
            
        }

        void add(int value, int index){ // Adds a node with a given value to any point of the list

            if (this->isEmpty() && index == 0){

                this->add(value);
                return;

            } else if ((this->isEmpty() && index != 0) || index >= this->len() || index < 0){

                throw "ArrayIndexOutOfBounds";

            } else if (index == 0){

                Node* p_target = this->getNode(index);
                Node* p_added = new Node(nullptr, value, p_target);

                this->first_node = p_added;
                p_target->setPrevious(p_added);

                this->length++;
                return;

            }

            Node* p_target = this->getNode(index);
            Node* p_previous = p_target->getPrevious();
            Node* p_added = new Node(p_previous, value, p_target);

            this->length++;

            p_previous->setNext(p_added);
            p_target->setPrevious(p_added);
        
        }

    private:

        Node* first_node;
        int length;

        Node* getNode(int index){ // Returns a pointer to the node at the given index

            if (index >= this->len() || index < 0){
                return nullptr;
            }

            Node* p_current = this->first_node;

            for (int i = 0; i < index; i++){

                p_current = p_current->getNext();

            }

            return p_current;

        }

};