#include <iostream>
#include <queue>
#include <map>
using namespace std;

// 构造哈夫曼树
struct Node {
  char val; 
  int freq; //频率
  Node* left; 
  Node* right; 

  
  Node(char val, int freq, Node* left = nullptr, Node* right = nullptr) {
    this->val = val;
    this->freq = freq;
    this->left = left;
    this->right = right;
  }
};


class Compare {
public:
  bool operator()(Node* a, Node* b) {
    
    return a->freq > b->freq;
  }
};

//建树
Node* buildHuffmanTree(char* input, int* freq, int n) {
  //优先队列存储节点
  priority_queue<Node*, vector<Node*>, Compare> Q;

  
  for (int i = 0; i < n; i++) {
    Q.push(new Node(input[i], freq[i]));
  }

  
  while (Q.size() > 1) {
    
    Node* left = Q.top();
    Q.pop();
    Node* right = Q.top();
    Q.pop();

    
    Node* parent = new Node('\0', left->freq + right->freq, left, right);

    Q.push(parent);
  }

  return Q.top();
}

void getCodes(Node* root, string code, map<char, string>& codes) {
  
  if (root->val != '\0') {
    codes[root->val] = code;
    return;
  }

  getCodes(root->left, code + "0", codes);

  
  getCodes(root->right, code + "1", codes);
}


string encode(char* input, int n, map<char, string>& codes) {
  string encoded = "";
  
  for (int i = 0; i < n; i++) {
    
    encoded += codes[input[i]];
  }
  return encoded;
}


string decode(string encoded, Node* root) {
  string decoded = "";
  Node* curr = root; 

  
  for (int i = 0; i < encoded.length(); i++) {
    
    if (encoded[i] == '0') {
      curr = curr->left;
    }
    else {
      curr = curr->right;
    }

    if (curr->val != '\0') {
      decoded += curr->val;
      curr = root; //回溯到根节点
    }
  }
  return decoded;
}

void printCodes(map<char, string>& codes) {
  cout << "Character\tCode\n";
  for (auto pair : codes) {
    cout << pair.first << "\t\t" << pair.second << "\n";
  }
}

// Driver code
int main() {
  char input[] = {'A', 'B', 'C', 'D', 'E', 'F'};
  int freq[] = {14, 9, 8, 12, 10, 5};
  int n = sizeof(input) / sizeof(input[0]);

  Node* root = buildHuffmanTree(input, freq, n);

  
  map<char, string> codes;
  getCodes(root, "", codes);

  
  printCodes(codes);

  string encoded = encode(input, n, codes);
  cout << "Encoded message: " << encoded << "\n";

  string decoded = decode(encoded, root);
  cout << "Decoded message: " << decoded << "\n";

  return 0;
}