/*
 * abbNode.h
 *
 *  Created on: Sep 2, 2022
 *      Author: jsaavedr
 */

#ifndef ABBNODE_HPP_
#define ABBNODE_HPP_

#include <string>

namespace trees {

class ABBNode {
private:
	ABBNode* ptrLeft;
	std::string data;
	ABBNode* ptrRight;
	int size;
public:
	ABBNode();
	ABBNode(std::string val);
	void setLeft(ABBNode* node);
	void setRight(ABBNode* node);
	void setData(std::string val);
	void setSize(int s);
	ABBNode* getLeft();
	ABBNode* getRight();
	std::string getData();
	int getSize();
	virtual ~ABBNode();
};

} /* namespace trees */

#endif /* ABBNODE_H_ */