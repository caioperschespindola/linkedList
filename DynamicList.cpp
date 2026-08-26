#include <iostream>

class Node{
    public:

        Node(Node* previous = nullptr, int value = 0, Node* next = nullptr){
            this->setPrevious(previous);
            this->setValue(value);
            this->setNext(next);
        }

        int getValue(){
            return this->value;
        }

        Node* getNext(){
            return this->next;
        }

        Node* getPrevious(){
            return this->previous;
        }

        void setValue(int new_value){
            this->value = new_value;
        }

        void setNext(Node* new_next){

            this->next = new_next;

        }

        void setPrevious(Node* new_previous){

            this->previous = new_previous;

        }

        void unsetNext(){
            this->next = nullptr;
        }

        void unsetPrevious(){
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
            this->first_node = new Node();
            this->length = 1;
        }

        int len(){
            return this->length;
        }

        bool isEmpty(){
            return (this->len() == 0);
        }

        void clear(){

            Node* p_last = this->getNode(this->len() - 1);
            Node* p_previous = p_last->getPrevious();

            for (int i = this->len() - 1; i > 0; i--){
                delete p_last;

                p_last = p_previous;
                p_previous = p_previous->getPrevious();
            }

            this->set(0, 0);
            
        }

        int get(int index){

            if (index >= this->length || index < 0){
                throw "ArrayIndexOutOfBounds";
            }

            Node* p_target = this->getNode(index);
            return p_target->getValue();

        }

        void set(int value, int index){
            
            if (index > this->length || index < 0){
                throw "ArrayIndexOutOfBounds";
            } else if (index == this->length){
                this->add(value);
            }

            Node* p_target = this->getNode(index);
            p_target->setValue(value);

        }

        void remove(int index){

            if (index > this->length || index < 0){
                throw "ArrayIndexOutOfBounds";
            }

            Node* p_target = this->getNode(index);

            if (index == 0){

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

        void add(int value){

            Node* p_last = this->getNode(this->len() - 1);
            Node* p_added_node = new Node(p_last, value);

            p_last->setNext(p_added_node);

            this->length++;
            
        }

        void add(int value, int index){

            // std::cout << "1-" << "\n";

            if (index == 0){

                Node* p_target = this->getNode(index);
                this->length++;
                Node* p_added = new Node(nullptr, value, p_target);
                this->first_node = p_added;
                p_target->setPrevious(p_added);


            } else if (index == this->len() - 1){

                this->add(value);

            }
            else{

            Node* p_target = this->getNode(index);
            Node* p_previous = p_target->getPrevious();

            this->length++;
            Node* p_added = new Node(p_previous, value, p_target);

            p_previous->setNext(p_added);

            p_target->setPrevious(p_added);
        }

        }

    private:

        Node* first_node;
        int length;

        Node* getNode(int index){

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

int main(){
    List my_list;

    my_list.set(10, 0);
    my_list.add(20);
    my_list.add(30);
    my_list.add(40);

    for (int i = 0; i < my_list.len(); i++){
        std::cout << my_list.get(i) << "\n";
    }

    my_list.remove(1);

    my_list.add(200, 1);

    std::cout << my_list.get(1) << "\n";

    return 0;
}