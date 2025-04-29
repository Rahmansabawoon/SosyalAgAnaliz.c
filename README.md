# Sosyal Ağ Modelleme - C Programı

Bu proje, sosyal ağ kullanıcılarını ve aralarındaki ilişkileri modellemek için C dilinde geliştirilmiş bir simülasyon programıdır. Kullanıcılar, Red-Black Tree (RB Tree) yapısında saklanırken, ilişkileri ağaç (tree) yapısı ile temsil edilmektedir. Program; DFS araması, ortak arkadaş analizi, etki alanı hesaplaması ve topluluk tespiti gibi analizler gerçekleştirmektedir.

## Özellikler

- 🧑‍🤝‍🧑 **Kullanıcı Temsili:** Her kullanıcı `User` yapısı ile temsil edilir.
- 🌳 **Red-Black Tree:** Kullanıcılar isme göre dengeli bir arama ağacında saklanır.
- 👥 **İlişki Ağacı (Relation Tree):** Arkadaşlık ilişkileri ağaç yapısında modellenmiştir.
- 🔍 **DFS Araması:** Belirli bir kullanıcıdan başlayarak derinlik sınırlı gezinme yapılabilir.
- 🤝 **Ortak Arkadaş Analizi:** İki kullanıcının ortak arkadaşları listelenebilir.
- 🌐 **Etki Alanı Hesaplama:** Bir kullanıcının etkilediği tüm kullanıcı sayısı hesaplanır.
- 🏘 **Topluluk Tespiti:** Ağ içinde ayrık alt gruplar (topluluklar) tespit edilir.

## Derleme ve Çalıştırma

```bash
gcc -o sosyal_ag sosyal_ag.c
./sosyal_ag
