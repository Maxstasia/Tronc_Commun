### **C’est quoi une classe en C++ ?**
Une classe, c’est comme une **boîte magique** où tu mets des données (attributs) et des actions (méthodes) qui vont ensemble. Imagine que tu crées un "modèle" pour un objet, comme une voiture : elle a des caractéristiques (couleur, vitesse) et des trucs qu’elle peut faire (rouler, klaxonner).

**Exemple simple** :
```cpp
class Voiture {
public:
    // Attributs (les données)
    string couleur;
    int vitesse;

    // Méthodes (les actions)
    void klaxonner() {
        cout << "Bip bip !" << endl;
    }
};
```

Ici, `Voiture` est une classe avec deux attributs (`couleur` et `vitesse`) et une méthode (`klaxonner`). Le mot `public` dit que tout le monde peut accéder à ces trucs.

---

### **Comment on utilise une classe ?**
Une classe, c’est juste un plan. Pour l’utiliser, tu crées un **objet**, qui est une instance de la classe.

```cpp
int main() {
    Voiture maVoiture; // Création d'un objet
    maVoiture.couleur = "Rouge"; // On donne une couleur
    maVoiture.vitesse = 120; // On donne une vitesse
    maVoiture.klaxonner(); // On appelle la méthode -> Affiche "Bip bip !"
    return 0;
}
```

---

### **Les délires possibles avec les classes**
Maintenant, on va voir les trucs cool que tu peux faire avec les classes en C++ !

#### **1. Public, private, protected : les niveaux d’accès**
Les classes ont des "serrures" pour protéger leurs données :
- **`public`** : Tout le monde peut y toucher (comme ci-dessus).
- **`private`** : Seulement la classe peut accéder aux attributs/méthodes. Les autres doivent passer par des méthodes publiques.
- **`protected`** : Comme `private`, mais les classes dérivées (héritage, on en parle après) y ont accès.

**Exemple** :
```cpp
class Voiture {
private:
    string codeSecret = "1234"; // Inaccessible de l'extérieur
public:
    string couleur;
    void klaxonner() {
        cout << "Bip bip ! Secret : " << codeSecret << endl;
    }
};

int main() {
    Voiture maVoiture;
    maVoiture.couleur = "Bleu"; // OK, c'est public
    // maVoiture.codeSecret = "0000"; // ERREUR ! C'est private
    maVoiture.klaxonner(); // OK, la méthode est publique
}
```

#### **2. Constructeurs : initialiser comme un boss**
Un **constructeur** est une méthode spéciale qui s’appelle automatiquement quand tu crées un objet. Il sert à initialiser les attributs.

```cpp
class Voiture {
public:
    string couleur;
    int vitesse;

    // Constructeur
    Voiture(string c, int v) {
        couleur = c;
        vitesse = v;
    }

    void klaxonner() {
        cout << "Bip bip ! Je suis " << couleur << " et je vais à " << vitesse << " km/h !" << endl;
    }
};

int main() {
    Voiture maVoiture("Verte", 150); // Le constructeur est appelé
    maVoiture.klaxonner(); // Affiche : Bip bip ! Je suis Verte et je vais à 150 km/h !
}
```

**Délire bonus** : Tu peux avoir plusieurs constructeurs (surcharge) :
```cpp
class Voiture {
public:
    string couleur;
    int vitesse;

    Voiture() { // Constructeur par défaut
        couleur = "Inconnue";
        vitesse = 0;
    }

    Voiture(string c, int v) { // Constructeur avec paramètres
        couleur = c;
        vitesse = v;
    }
};
```

#### **3. Destructeur : nettoyer avant de partir**
Un **destructeur** s’appelle automatiquement quand un objet est détruit (fin de programme ou fin de portée). Il sert à libérer des ressources (comme la mémoire).

```cpp
class Voiture {
public:
    string couleur;
    Voiture(string c) {
        couleur = c;
        cout << "Voiture créée !" << endl;
    }
    ~Voiture() { // Destructeur
        cout << "Voiture détruite, snif !" << endl;
    }
};

int main() {
    Voiture maVoiture("Jaune"); // Affiche : Voiture créée !
    // Fin du main -> Affiche : Voiture détruite, snif !
}
```

#### **4. Héritage : la famille des classes**
Une classe peut **hériter** d’une autre pour réutiliser ses attributs et méthodes. Par exemple, une `VoitureDeCourse` peut hériter de `Voiture`.

```cpp
class Voiture {
public:
    string couleur;
    void klaxonner() {
        cout << "Bip bip !" << endl;
    }
};

class VoitureDeCourse : public Voiture { // Héritage
public:
    int nitro;
    void utiliserNitro() {
        cout << "VROOOM ! Nitro activé !" << endl;
    }
};

int main() {
    VoitureDeCourse ferrari;
    ferrari.couleur = "Rouge";
    ferrari.nitro = 100;
    ferrari.klaxonner(); // Hérité de Voiture
    ferrari.utiliserNitro(); // Propre à VoitureDeCourse
}
```

#### **5. Polymorphisme : changer les comportements**
Le polymorphisme permet à une classe dérivée de **redéfinir** une méthode de la classe de base. Pour ça, on utilise `virtual`.

```cpp
class Voiture {
public:
    virtual void klaxonner() { // virtual permet la redéfinition
        cout << "Bip bip standard !" << endl;
    }
};

class VoitureDeCourse : public Voiture {
public:
    void klaxonner() override { // Redéfinition
        cout << "BROUM BROUM de course !" << endl;
    }
};

int main() {
    Voiture* voiture = new VoitureDeCourse(); // Pointeur de type Voiture
    voiture->klaxonner(); // Affiche : BROUM BROUM de course !
    delete voiture;
}
```

#### **6. Encapsulation : garder les secrets**
L’encapsulation, c’est cacher les détails internes et n’exposer que ce qui est nécessaire via des **getters** et **setters**.

```cpp
class Voiture {
private:
    string couleur;
public:
    void setCouleur(string c) { // Setter
        couleur = c;
    }
    string getCouleur() { // Getter
        return couleur;
    }
};

int main() {
    Voiture maVoiture;
    maVoiture.setCouleur("Noir");
    cout << maVoiture.getCouleur() << endl; // Affiche : Noir
}
```

#### **7. Surcharge des opérateurs : rendre tout stylé**
Tu peux redéfinir des opérateurs comme `+` ou `==` pour tes classes.

```cpp
class Voiture {
public:
    int vitesse;
    Voiture(int v) : vitesse(v) {}
    Voiture operator+(const Voiture& autre) { // Surcharge de +
        return Voiture(vitesse + autre.vitesse);
    }
};

int main() {
    Voiture v1(100), v2(50);
    Voiture v3 = v1 + v2; // Additionne les vitesses
    cout << v3.vitesse << endl; // Affiche : 150
}
```

#### **8. Classes abstraites et interfaces**
Une classe avec une méthode **purement virtuelle** (`= 0`) est une classe abstraite. Tu ne peux pas créer d’objets de cette classe, mais tu peux l’utiliser comme base.

```cpp
class Vehicule {
public:
    virtual void klaxonner() = 0; // Méthode purement virtuelle
};

class Voiture : public Vehicule {
public:
    void klaxonner() override {
        cout << "Bip bip !" << endl;
    }
};

int main() {
    // Vehicule v; // ERREUR : classe abstraite
    Voiture maVoiture;
    maVoiture.klaxonner(); // OK
}
```

---

### **Résumé ultra simple**
- Une **classe** = données + actions.
- **Attributs** : ce que l’objet a (ex. couleur).
- **Méthodes** : ce que l’objet fait (ex. klaxonner).
- **Public/private** : contrôle qui peut accéder à quoi.
- **Constructeur/destructeur** : pour créer et nettoyer.
- **Héritage** : réutiliser du code entre classes.
- **Polymorphisme** : redéfinir des comportements.
- **Encapsulation** : protéger les données.
- **Surcharge d’opérateurs** : rendre les opérations stylées.
- **Classes abstraites** : des plans qu’on ne peut pas instancier.

