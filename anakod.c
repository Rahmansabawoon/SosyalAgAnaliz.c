#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// --- Kullanıcı Tanımı ---
typedef struct User {
    char* name;
} User;

// --- Red-Black Tree Düğümü ---
typedef struct RBNode {
    User* user;
    struct RBNode *left, *right, *parent;
    int color;
} RBNode;

// --- Sosyal İlişki Ağaç Düğümü ---
typedef struct RelationNode {
    User* user;
    struct RelationNode* parent;
    struct RelationNode* firstChild;
    struct RelationNode* nextSibling;
    int visited;
} RelationNode;

RBNode* rbTreeRoot = NULL;
RelationNode* relationTreeRoot = NULL;

// --- Kullanıcı Oluştur ---
User* createUser(char* name) {
    User* user = (User*)malloc(sizeof(User));
    user->name = strdup(name);
    return user;
}

// --- Red-Black Tree Basit Ekleme ---
RBNode* rbInsert(RBNode* root, User* user) {
    RBNode* newNode = (RBNode*)malloc(sizeof(RBNode));
    newNode->user = user;
    newNode->left = newNode->right = newNode->parent = NULL;
    newNode->color = 1;

    RBNode* current = root;
    RBNode* parent = NULL;

    while (current != NULL) {
        parent = current;
        if (strcmp(user->name, current->user->name) < 0)
            current = current->left;
        else
            current = current->right;
    }

    newNode->parent = parent;
    if (parent == NULL)
        return newNode;
    else if (strcmp(user->name, parent->user->name) < 0)
        parent->left = newNode;
    else
        parent->right = newNode;

    return root == NULL ? newNode : root;
}

RBNode* rbFindUser(RBNode* root, char* name) {
    RBNode* current = root;
    while (current != NULL) {
        if (strcmp(name, current->user->name) == 0)
            return current;
        else if (strcmp(name, current->user->name) < 0)
            current = current->left;
        else
            current = current->right;
    }
    return NULL;
}

// --- İlişki Ağacı Yapısı ---
RelationNode* addRelationNode(RelationNode* parent, User* user) {
    RelationNode* newNode = (RelationNode*)malloc(sizeof(RelationNode));
    newNode->user = user;
    newNode->parent = parent;
    newNode->firstChild = NULL;
    newNode->nextSibling = NULL;
    newNode->visited = 0;

    if (parent) {
        if (!parent->firstChild) {
            parent->firstChild = newNode;
        } else {
            RelationNode* sibling = parent->firstChild;
            while (sibling->nextSibling) {
                sibling = sibling->nextSibling;
            }
            sibling->nextSibling = newNode;
        }
    }
    return newNode;
}

void addFriendshipToRelationTree(RelationNode* userNode, User* friendUser) {
    addRelationNode(userNode, friendUser);
}

// --- DFS ---
void relationTreeDFS(RelationNode* node, int depth) {
    if (!node || depth < 0 || node->visited) return;
    node->visited = 1;
    printf("%s ", node->user->name);

    RelationNode* child = node->firstChild;
    while (child) {
        relationTreeDFS(child, depth - 1);
        child = child->nextSibling;
    }
}

// --- Ziyaret Sıfırla ---
void resetRelationTreeVisited(RelationNode* root) {
    if (!root) return;
    root->visited = 0;
    RelationNode* child = root->firstChild;
    while (child) {
        resetRelationTreeVisited(child);
        child = child->nextSibling;
    }
}

// ✅ ORTAK ARKADAŞ ANALİZİ
void findCommonFriendsInRelationTree(RelationNode* userNodeA, RelationNode* userNodeB) {
    printf("%s ve %s ortak arkadaşları: ", userNodeA->user->name, userNodeB->user->name);
    RelationNode* friendA = userNodeA->firstChild;
    while (friendA) {
        RelationNode* friendB = userNodeB->firstChild;
        while (friendB) {
            if (strcmp(friendA->user->name, friendB->user->name) == 0) {
                printf("%s ", friendA->user->name);
            }
            friendB = friendB->nextSibling;
        }
        friendA = friendA->nextSibling;
    }
    printf("\n");
}

//  ETKİ ALANI
int calculateInfluenceInRelationTree(RelationNode* node) {
    if (!node || node->visited) return 0;
    node->visited = 1;
    int count = 1;
    RelationNode* child = node->firstChild;
    while (child) {
        count += calculateInfluenceInRelationTree(child);
        child = child->nextSibling;
    }
    return count;
}

// TOPLULUK TESPİTİ
void dfsPrintCommunity(RelationNode* node) {
    if (!node || node->visited) return;
    node->visited = 1;
    printf("%s ", node->user->name);
    RelationNode* child = node->firstChild;
    while (child) {
        dfsPrintCommunity(child);
        child = child->nextSibling;
    }
}

void detectCommunitiesInRelationTree(RelationNode* root) {
    printf("Topluluklar:\n");
    if (!root) return;

    resetRelationTreeVisited(root);
    RelationNode* node = root;
    while (node) {
        if (!node->visited) {
            printf("- ");
            dfsPrintCommunity(node);
            printf("\n");
        }
        node = node->nextSibling; // Ana ağacın kardeşleri de olabilir
    }
}

int main() {
    // Kullanıcılar
    User* zeynep = createUser("Zeynep");
    User* ahmet = createUser("Ahmet");
    User* mehmet = createUser("Mehmet");
    User* elif = createUser("Elif");
    User* leyla = createUser("Leyla");

    // RB Ağacı
    rbTreeRoot = rbInsert(rbTreeRoot, zeynep);
    rbTreeRoot = rbInsert(rbTreeRoot, ahmet);
    rbTreeRoot = rbInsert(rbTreeRoot, mehmet);
    rbTreeRoot = rbInsert(rbTreeRoot, elif);
    rbTreeRoot = rbInsert(rbTreeRoot, leyla);

    // İlişki Ağacı
    relationTreeRoot = addRelationNode(NULL, zeynep);
    RelationNode* ahmetNode = addRelationNode(relationTreeRoot, ahmet);
    RelationNode* elifNode = addRelationNode(relationTreeRoot, elif);
    RelationNode* leylaNode = addRelationNode(ahmetNode, leyla);
    RelationNode* mehmetNode = addRelationNode(elifNode, mehmet);

    // Arkadaşlık ilişkileri
    addFriendshipToRelationTree(relationTreeRoot, ahmet->name);
    addFriendshipToRelationTree(relationTreeRoot, elif->name);
    addFriendshipToRelationTree(ahmetNode, leyla->name);
    addFriendshipToRelationTree(elifNode, mehmet->name);

    // DFS
    printf("DFS (Zeynep, mesafe 2): ");
    resetRelationTreeVisited(relationTreeRoot);
    relationTreeDFS(relationTreeRoot, 2);
    printf("\n");

    // Ortak Arkadaşlar
    findCommonFriendsInRelationTree(relationTreeRoot, elifNode);

    // Etki Alanı
    resetRelationTreeVisited(relationTreeRoot);
    printf("Etki alanı (Zeynep): %d kişi\n", calculateInfluenceInRelationTree(relationTreeRoot));

    // Topluluklar
    detectCommunitiesInRelationTree(relationTreeRoot);

    return 0;
}
