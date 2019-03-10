//
//  main.cpp
//  Elevator
//
//  Created by Hugo De Moraes on 11/6/18.
//  Copyright © 2018 Hugo De Moraes. All rights reserved.
//

#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

//--------------------------------------------------------------CLASS DEFENITION-------------------------------------------------------------

class List
{
private:
    struct node
    {
        int floorNum;
        int getOnFlrNum;
        int getOffFlrNum;
        node* next;
        node* previous;
    };
    node* head;
    node* tail;
    
public:
    List()
    {
        head = NULL;
        tail = NULL;
    }
    
    bool menu()
    {
        int choice;
        cout << "To Start Operation please enter \"0\"" << endl;
        cin >> choice;
        cout << endl;
        
        if(choice == 0)
        {
            return true;
        }
        else return false;
    }
    
    node* createEmptyNode()
    {
        node* temp = new node;
        return temp;
    }
    
    node* createGetOnNode(int getOnFlrNum, int getOffFlrNum) //Create a "Get On Node" with Two Floor Values
    {
        node* newNode = createEmptyNode();
        newNode->floorNum = getOnFlrNum;
        newNode->getOnFlrNum = getOnFlrNum;
        newNode->getOffFlrNum = getOffFlrNum;
        newNode->next = NULL;
        newNode->previous = NULL;
        return newNode;
    }
    
    node* createGetOffNode(int getOffFlrNum) //Create a "Get Off Node" with first value == NULL and "Get Off Value"
    {
        node* newNode = createEmptyNode();
        newNode->floorNum = getOffFlrNum;
        newNode->getOnFlrNum = 0;
        newNode->getOffFlrNum = getOffFlrNum;
        newNode->next = NULL;
        newNode->previous = NULL;
        return newNode;
    }
    
    void getOn(int getOnFlrNum, int getOffFlrNum)
    {
        insert(createGetOnNode(getOnFlrNum, getOffFlrNum));
    }
    
    void insert(node* newNode)
    {
        node* temp = createEmptyNode();
        temp = head;
        
        if(temp == NULL)
        {
            head = newNode;
            tail = newNode;
        }
        else if(temp->floorNum > newNode->floorNum)
        {
            newNode->next = temp;
            temp->previous = newNode;
            head = newNode;
            tail = temp;
        }
        else if(temp->floorNum < newNode->floorNum)
        {
            while(temp->next != NULL && temp->next->floorNum < newNode->floorNum)
            {
                temp = temp->next;
            }
            if(temp->next == NULL)
            {
                temp->next = newNode;
                newNode->previous = temp;
                tail = newNode;
            }
            if(temp->next->floorNum > newNode->floorNum)
            {
                temp->next->previous = newNode;
                newNode->next = temp->next;
                newNode->previous = temp;
                temp->next = newNode;
            }
        }
        else if(temp->floorNum == newNode->floorNum)
        {
            temp = newNode;
        }
    }
    
    void setTempToZero(node* temp)
    {
        temp->floorNum = 0;
        temp->getOnFlrNum = 0;
        temp->getOffFlrNum = 0;
    }
    
    void move()
    {
     
        //Go through list, perform correct operation(s) at each node
        node* temp = createEmptyNode();
        temp = head;
    
        if(menu() == true)
        {
            if(temp->floorNum != 1)
            {
            cout << "Going Up..." << endl << endl;
            }
        }
        else
        {
            exit(1);
        }
        
        do
        {
            if(temp->floorNum != 0)
            {
                cout << "Floor:         " << temp->floorNum << endl << endl;
            }
            
            if(temp->getOnFlrNum != 0)
            {
                cout << "Getting On..." << endl << endl;
                insert(createGetOffNode(temp->getOffFlrNum));
            }
            else if(temp->getOffFlrNum != 0)
            {
                cout << "Getting Off..." << endl << endl;
            }
            if(temp->floorNum != 0)
            {
                cout << "Going Up..." << endl << endl;
            }
            setTempToZero(temp);
            temp = temp->next;
        }
        while(temp != tail && temp != NULL);
        
        do
        {
            if(temp->floorNum != 0)
            {
                cout << "Floor:         " << temp->floorNum << endl << endl;
            }
            
            if(temp->getOnFlrNum != 0)
            {
                cout << "Getting On..." << endl << endl;
                insert(createGetOffNode(temp->getOffFlrNum));
            }
            else if(temp->getOffFlrNum != 0)
            {
                cout << "Getting Off..." << endl << endl;
            }
            if(temp->floorNum != 0)
            {
               cout << "Going Down..." << endl << endl;
            }
            setTempToZero(temp);
            temp = temp->previous;
        }
        while(temp != head && temp != NULL);
    }
    
    void displayAll()
    {
        node *temp = createEmptyNode();
        temp = head;
        while(temp != NULL)
        {
            cout << temp->getOnFlrNum << endl;
            temp = temp->next;
        }
    }
    
    void deleteList()
    {
        node* current;
        node* next;
        current = head;
        while (current != NULL)
        {
            next = current->next;
            current = NULL;
            current = next;
        }
        head = NULL;
    }
    

};
void intro()
{
    cout << ":: Elevator ::" << endl << endl;
}

int main()
{
    List* Elevator = new List;
    
    intro();
    
    Elevator->getOn(4, 6);
    Elevator->move();
    Elevator->deleteList();

    Elevator->getOn(8, 2);
    Elevator->getOn(1, 5);
    Elevator->getOn(9, 3);
    Elevator->move();
    Elevator->deleteList();
    
    Elevator->getOn(10, 2);
    Elevator->getOn(1, 7);
    Elevator->move();
    Elevator->deleteList();
    
    Elevator->getOn(1, 7);
    Elevator->move();
    Elevator->deleteList();
    
    cout << endl;
    return 0;
}
