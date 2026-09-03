> *This project has been created as part of the 42 curriculum by samaouch and ale-guel.*
<!-- Custom fonts -->
<!-- 𝔸 𝔹 ℂ 𝔻 𝔼 𝔽 𝔾 ℍ 𝕀 𝕁 𝕂 𝕃 𝕄 ℕ 𝕆 ℙ ℚ ℝ 𝕊 𝕋 𝕌 𝕍 𝕎 𝕏 𝕐 ℤ -->
<!-- 𝕒 𝕓 𝕔 𝕕 𝕖 𝕗 𝕘 𝕙 𝕚 𝕛 𝕜 𝕝 𝕞 𝕟 𝕠 𝕡 𝕢 𝕣 𝕤 𝕥 𝕦 𝕧 𝕨 𝕩 𝕪 𝕫  -->

<b><font size="2">*end*[^1]</b></font>

<p align="center">
  <img src="https://capsule-render.vercel.app/api?type=waving&color=gradient&height=300&section=header&text=Cub3D&fontSize=120&animation=scaleIn&fontAlignY=42&fontAlign=48&desc=2.5D%20RPG%20GAME&descAlignY=60&descAlign=74" alt="Cub3D"/>
</p>

---

<details open>
	<summary>
		<h4>📑 𝕊ummary</h4> 
	</summary>
<blockquote>

- [𝔽onctionnalités Clés](#function)
- [𝔽onctionnalités de Gameplay](#game)
	-[𝕃e Système de Magie](#spell)
	- [𝔹estiaire & Évolution du Monde](#mob)
	- [ℂollectibles & Artefacts Magiques](#object)
	- [𝕀mmersion, Audio & Mécanique](#immersion)
	- [𝕀nterface & Personnalisation](#interface)
	- [𝔽in de partie & Les 4 Coalition](#end)
- [𝕀nstallation et Commandes](#setup)
- [ℂonfiguration de la Map](#map)
</blockquote>
</details>

---


# 🪄 Cub3D - Le Tournoi des Quatre Sorciers

Un FPS rétro en Raycasting (moteur personnalisé en C) entièrement inspiré de l'univers d'Harry Potter. Affrontez un labyrinthe dynamique, maîtrisez un arsenal de sorts complexes, survivez à des créatures mythiques et menez votre coalition à la victoire pour remporter la Coupe de Feu.

<video src="https://github.com/user-attachments/assets/fd5752ee-a53a-4969-9ca0-c20d6a1dede9" autoplay loop muted playsinline width="100%"></video>

---

<details id= "function">
	<summary>
		<h1> ⚡ 𝔽onctionnalités Clés </h1>
	</summary>

<blockquote>

*   **Système de combat magique avancé** : 26 sorts uniques (soins, éléments, malédictions, contrôle des foules, boucliers...).
*   **IA Prédictive & Traque** : Ennemis dotés d'une IA inspirée de l'algorithme $A^*$ avec gestion du champ de vision et mémoire à court terme.
*   **Génération et Leveling Évolutifs** : Le monde s'adapte dynamiquement à votre niveau. Plus vous êtes puissant, plus les menaces sont redoutables.
*   **Atmosphère immersive** : Audio spatialisé, musiques stressantes, messages ensanglantés aléatoires sur les murs et gestion de la lumière en temps réel.

</blockquote>
</details>

---

<details id= "game">
	<summary>
		<h1>🎮 𝔽onctionnalités de Gameplay</h1>
	</summary>

<blockquote>

<dl><dd>
<details id= "spell">
	<summary>
		<h2> 🔮 𝕃e Système de Magie </h2>
	</summary>

<blockquote>

Pour ouvrir le grimoire / menu des sorts, appuyez sur la touche **[N]**.

<img src="ressource/README_asset/spell.png">

Les sorts sont répartis en plusieurs catégories stratégiques :
*   **Élémentaires** (Feu, Eau, etc.)
*   **Soins & Protections** (Protego, régénérations...)
*   **Malédictions & Altérations**
*   **Contrôle de foule** (Déplacement et repousse des ennemis)
*   **Lumos (Interaction)** : Indispensable pour explorer. Ce sort génère une source de lumière intense qui décroît avec le temps. 
    > 🚪 **Portes dynamiques :** Les portes du labyrinthe s'ouvrent *uniquement* sous l'effet de Lumos. La vitesse d'ouverture de la porte est directement proportionnelle à l'intensité lumineuse du sort au moment de l'impact !

	<video src="https://github.com/user-attachments/assets/2d96d127-fecc-42e9-8d4b-9cc3dfa62dd1" autoplay loop muted playsinline width="100%"></video>

	<p align="center">
  <video src="https://github.com/user-attachments/assets/8a5597bb-cd97-4501-b9dc-ed36469d9d8d" autoplay loop muted playsinline width="100%"></video>
</p>

</blockquote>
</details>
</dd></dl>

---

<dl><dd>
<details id= "mob">
	<summary>
		<h2> 🐺 𝔹estiaire & Évolution du Monde</h2>
	</summary>

<blockquote>

Le labyrinthe est peuplé de 5 types de créatures classées par ordre de difficulté :
1. **Spider** (Faible face au sort *Anti-araignée*)
2. **Élémentaire de Feu** (Immunisé au feu, vulnérable à l'eau)
3. **Détraqueur** (Possède des faiblesses spécifiques)
4. **Loup-Garou** (Aucune faiblesse élémentaire)
5. **Sorcier** (L'élite adverse, aucune faiblesse)

### 📈 Courbe d'XP et Équilibrage Dynamique
*   **Difficulté adaptative** : Le ratio de spawn des ennemis dangereux augmente proportionnellement au niveau du joueur.
*   **Rendement décroissant** : Plus votre niveau s'élève, plus le palier d'XP requis pour monter de niveau est grand. De plus, les monstres les plus faibles rapportent de moins en moins d'XP et finissent par cesser de spawner.
*   **Intelligence Artificielle** : Les ennemis patrouillent de manière aléatoire. S'ils détectent le joueur (cible prioritaire) ou un autre monstre, ils engagent la traque via un algorithme de pathfinding ($A^*$). Si vous brisez la ligne de vue, le monstre continuera à vous suivre pendant un court laps de temps, simulant le fait qu'il sait que vous êtes passé par ce chemin du labyrinthe.

	<video src="https://github.com/user-attachments/assets/3b3dffb0-5985-48fb-85a0-d84d3ebddc81" autoplay loop muted playsinline width="100%"></video>

	<video src="https://github.com/user-attachments/assets/2e21959b-fecd-42d7-a6d6-5ddf4cd83ebd" autoplay loop muted playsinline width="100%"></video>

</blockquote>
</details>
</dd></dl>

---

<dl><dd>
<details id= "object">
	<summary>
		<h2> 🎒 ℂollectibles & Artefacts Magiques</h2>
	</summary>

<blockquote>

| Objet | Effet |
| :--- | :--- |
| **Potion de Vie** | Restaure instantanément vos points de vie. |
| **Potion de Bouclier** | Augmente vos défenses magiques. |
| **Poudre de Cheminette** | Permet de voyager rapidement via le réseau des cheminées. |
| **Cape d'Invisibilité** | Fragmentée. Nécessite 4 morceaux minimum pour être activée. |

### 🪵 Réseau de Cheminées (Téléportation)
Utilisez la poudre à proximité d'une cheminée pour l'allumer (modification visuelle de la texture). En entrant à l'intérieur, la carte globale s'ouvre, vous permettant de cliquer sur n'importe quelle autre cheminée préalablement activée pour vous y téléporter instantanément.

### 👥 Cape d'Invisibilité
*   Inutile seule, collectez au moins **4 fragments** pour déclencher son pouvoir et devenir totalement invisible aux yeux des ennemis.
*   **Interface dynamique** : La texture de la cape dans votre inventaire s'assombrit en cercle pour représenter le temps d'effet restant.
*   **Cumul et Bonus** : Posséder plus de 4 fragments augmente proportionnellement la durée totale de l'invisibilité. Ramasser un fragment pendant que la cape est active rallonge directement le timer en cours en fonction du nombre de fragments récoltés.

<video src="https://github.com/user-attachments/assets/46e67e87-fd93-4219-9780-f24d2a6b8887" autoplay loop muted playsinline width="100%"></video>


</blockquote>
</details>
</dd></dl>

---

<dl><dd>
<details id= "immersion">
	<summary>
		<h2> 🩸 𝕀mmersion, Audio & Mécanique</h2>
	</summary>

<blockquote>

*   **Indicateur de Santé Visceral** : Plus votre santé décline, plus une bordure rouge (vignette de sang) apparaît sur les contours de l'écran et grandit vers le centre, simulant une vision troublée et un état de choc.
*   **Battements de Cœur** : Un effet sonore de rythme cardiaque s'active en fond. Sa vitesse s'accélère de manière exponentielle en fonction de la vie manquante du joueur.
*   **Messages Ensanglantés** : De manière aléatoire, des messages de sang apparaissent dynamiquement sur les murs pour former des phrases (3 phrases distinctes qui tournent en boucle), renforçant l'ambiance stressante.
*   **Audio Réactif** : Chaque sort lancé, chaque ennemi et chaque action contextuelle génère un effet sonore unique lié à l'environnement.

<video src="https://github.com/user-attachments/assets/32993db9-4bb6-4744-9124-26e193066fb7" autoplay loop muted playsinline width="100%"></video>

</blockquote>
</details>
</dd></dl>

---

<dl><dd>
<details id= "interface">
	<summary>
		<h2> 🗺️ 𝕀nterface & Personnalisation</h2>
	</summary>

<blockquote>

*   **Carte Interactive** : Ouvrable via une touche dédiée ou automatiquement lors d'une téléportation. Vous pouvez zoomer/dézoomer avec la molette de la souris et vous déplacer sur la carte au clavier ou en maintenant le clic de la souris.
*   **Menu Pause** : Permet de suspendre le jeu et d'ajuster précisément la sensibilité de la souris.
*   **Collection de Baguettes (Skins)** : À leur mort, les monstres ont une faible chance de faire tomber un skin cosmétique qui change l'apparence de votre baguette. Le taux est de **1%** sur les monstres classiques et grimpe à **10%** sur les Sorciers. Changez de skin à la volée en utilisant la molette de la souris en jeu.

<video src="https://github.com/user-attachments/assets/c4dd8691-acf8-4423-be3b-dbccc028ad50" autoplay loop muted playsinline width="100%"></video>

<video src="https://github.com/user-attachments/assets/ac32c7ea-2789-493c-bacf-027de2eca320" autoplay loop muted playsinline width="100%"></video>

<video src="https://github.com/user-attachments/assets/011f3794-0538-4b14-bdc2-4b43e11e0e70" autoplay loop muted playsinline width="100%"></video>


</blockquote>
</details>
</dd></dl>

---

<dl><dd>
<details id="end">
	<summary>
		<h2> 🏆 𝔽in de partie & Les 4 Coalitions</h2>
	</summary>

<blockquote>

Au début de votre aventure, vous devez choisir votre camp parmi l'une des **4 coalitions**. Les 3 restantes seront représentées par les membres du staff (qui possèdent chacun un sort spécial redoutable).

### 🥇 Conditions de Victoire
1. Atteindre le **Niveau 15**.
2. Trouver et ramasser la **Coupe des Quatre Sorciers**. Elle apparaît aléatoirement dans le labyrinthe une fois le niveau 15 atteint (sauf si elle a été explicitement placée à l'avance via le fichier de configuration `.cub`).

*   **Écran de Victoire** : Un tableau des scores stylisé sous forme de **4 sabliers géants** (style Harry Potter) s'affiche. Le score de chaque coalition augmente en fonction du nombre d'ennemis qu'elle a tués.
*   **Écran de Défaite (Mort)** : Un menu Game Over vous propose instantanément de rejouer ou de quitter le jeu.

<video src="https://github.com/user-attachments/assets/38b8236c-1ff1-476d-b2b9-8ab5b3cd427a" autoplay loop muted playsinline width="100%"></video>

</blockquote>
</details>
</dd></dl>
</blockquote>
</details>

---

<details id= "setup">
	<summary>
		<h1> 🛠️ 𝕀nstallation </h2>
	</summary>

<blockquote>

```bash
# Cloner le projet
git clone https://github.com/Unde21/Cub3D.git
cd Cub3D

# Compiler le projet
make bonus

# Lancer le jeu avec une map
./cub3D maps/bonus/valid/1.cub
```
</blockquote>
</details>

---

<details id= "map">
	<summary>
		<h1> 🗺️ ℂonfiguration de la Map</h2>
	</summary>

<blockquote>
<dl><dd>

Le programme prend en paramètre un fichier de configuration `.cub` qui doit respecter scrupuleusement la syntaxe suivante sous peine de gestion d'erreur stricte (sans *leak* ni *crash*).

### Structure du fichier :

```text
NO ./path_to_textures/north_wall.xpm
SO ./path_to_textures/south_wall.xpm
WE ./path_to_textures/west_wall.xpm
EA ./path_to_textures/east_wall.xpm

F 220,100,0     # Couleur du sol (RGB)
C 135,206,235   # Couleur du plafond (RGB)

111111111111
100001000001
10N00P00M001
1000010000C1
111111111111
```

### 📋 Légende des Éléments de la Map :

* **`1`** : Mur de pierre magique (utilise les textures directionnelles `NO`, `SO`, `WE`, `EA`).
* **`0`** / **`Espace`** : Zones de couloir praticables / Vide extérieur du labyrinthe.
* **`N` / `S` / `E` / `W`** : Position initiale du joueur et orientation de sa caméra au départ.

#### 🚪 Portes Magiques :
* **`D`** : Porte dynamique (sensible au sortilège *Lumos*). Le moteur calcule automatiquement si la porte est horizontale ou verticale pour l'ouvrir selon les bons repères géométriques.

#### 🪵 Réseau & Téléportation :
* **`F`** : **Cheminée magique** 🔥 (Point de téléportation lié au réseau de la Poudre de Cheminette).

#### 🎒 Artefacts & Collectibles :
* **`z`** : Potion de Soin (*Heal Potion*).
* **`x`** : Potion de Bouclier (*Shield Potion*).
* **`c`** : Poudre de Cheminette (*Floo Powder*).
* **`v`** : Fragment de la Cape d'Invisibilité (*Invisibility Fragment*).
* **`f`** : **La Coupe des Quatre Sorciers / Portkey** 🏆 Objectif final.

#### 🐺 Bestiaire (Ennemis) :
* **`.`** : Détraqueur (*Dementor*).
* **`,`** : Araignée (*Spider*).
* **`<`** : Loup-Garou (*Wolf*).
* **`>`** : Élémentaire (*Elem*).
* **`;`** : Oiseau / (*Bird*).
* **`:`** : Serpent  (*Snake*).
* **`2`** à **`9`** / **`m`** : Identifiants spécifiques réservés aux membres du staff

</dd></dl>
</details>

[^1]:*begin*
