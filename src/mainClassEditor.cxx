/*
Copyright (c) 2023 Daren Kostov

This file is part of SGDT

SGDT is free software: you can redistribute it and/or modify it under the terms
of the GNU General Public License as published by the Free Software Foundation,
either version 3 of the License, or (at your option) any later version.

SGDT is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY;
without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR
PURPOSE. See the GNU General Public License for more details.

You should have received a copy of the GNU General Public License along with SGDT
If not, see <https://www.gnu.org/licenses/>.
*/

#include "mainClass.hxx"
#include <SFML/Graphics/Color.hpp>
#include <regex>





MainClass::ErrorMessage MainClass::addNode(Node* in){
  //does the node even exist?
  if(in==nullptr)
    return inputted_node_nullptr;


  //does this node already exist?
  if(nodes.find(in)==nodes.end())
    return node_already_exists;
  
  haveWeMadeAnyChanges=true;
  
  
  
  //add the new node and a new row for it
  //make sure every link associated with this node is nullptr
  nodes.insert(in);
  links[in]=std::unordered_map<Node*, Link*>();
  for(auto& row : links){
    links[in][row.first]=nullptr;
    links[row.first][in]=nullptr;
  }

  return success;
}


MainClass::ErrorMessage MainClass::removeNode(Node* in){
  //does the node even exist?
  if(in==nullptr)
    return inputted_node_nullptr;
  haveWeMadeAnyChanges=true;
  
  nodes.erase(in);

  //delete the links associated with this node
  for(auto& row : links){
    delete links[in][row.first];
    delete links[row.first][in];
  }
  
  //remove the others' possible connections to this mode
  for(auto& row : links){
    links[row.first].erase(in);
  }
  links.erase(in);

  //delete node  
  delete in;

  return success;

}


MainClass::ErrorMessage MainClass::addLink(Node* from, Node* to, Link* connector){
  //do the nodes and link even exist?
  if(from==nullptr || to==nullptr || connector==nullptr)
    return inputted_nullptr;

  //we are not connecting a node to itself right?
  if(from==to)
    return connecting_node_to_self;
  
  //we are not rewriting a link right?
  if(links[from][to]!=nullptr)
    return rewriting_existing_link;
  
  haveWeMadeAnyChanges=true;

  links[from][to]=connector;
  return success;
}

MainClass::ErrorMessage MainClass::linkNodes(Node* node1, Node* node2, Link* link1){
  return addLink(node1, node2, link1);
}


MainClass::ErrorMessage MainClass::removeLink(Link* in){
  //does the link even exist?
  if(in==nullptr)
    return inputted_link_nullptr;

  for(auto& row : links){
    for(auto& column : row.second){
      // if(links[row.first][column.first]==in){
      //   links[row.first][column.first]=nullptr;
      // }
      if(column.second==in){
        haveWeMadeAnyChanges=true;
        delete column.second;
        column.second=nullptr;
        return success;
      }
    }
  }

  return link_does_not_exist;
}



MainClass::ErrorMessage MainClass::severLink(Node* from, Node* to){
    
  //do the nodes even exist?
  if(from==nullptr || to==nullptr)
    return inputted_node_nullptr;

  //does the link even exist?
  if(links[from][to]==nullptr)
    return link_between_nodes_does_not_exist;

  haveWeMadeAnyChanges=true;
  delete links[from][to];
  links[from][to]=nullptr;

  return success;
}


Node* MainClass::giveMeNewNodeBasedOnSettings(){
  Node* newNode=new Node();
  return newNode;
}

Link* MainClass::giveMeNewLinkBasedOnSettings(){
  Link* newLink=new Link();
  return newLink;
}

MainClass::ErrorMessage MainClass::eraseEverything(){

    //delete every link
    for(auto& row : links) {
      for(auto& column : row.second) {
        if(column.second!=nullptr){
          delete column.second;
        }
      }
      row.second.clear();
    }
    links.clear();

    //delete every node
    while(!nodes.empty()){
      delete *(nodes.begin());
      nodes.erase(nodes.begin());
    }

  return success;
}


MainClass::ErrorMessage MainClass::saveToFile(std::string path){
  return success;
}

MainClass::ErrorMessage MainClass::loadFromFile(std::string path){
  return success;
}
