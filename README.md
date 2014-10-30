# Название:
Умный Словарь -- SmartDict.

# Цель:
Выучить английские слова и устойчивые выражения.

# Задача:
Выдать список предложений из литературы, в которых содержится запрос.

# План реализации (альфа-версия):
* Back-end
  1. Индексатор(С++): Получает на вход текст (тексты) и строит инвертированный индекс.
     - Парсер текста (выделение предложений и слов)
        class TParser
          void SplitText(const string& text, vector<string>& sentences) const;
          void SplitSentence(const string& sentence, vector<string>& words) const;
          
     - ** version 2.0 ** Сделать предфильтр. Он будет выкидывать из индексируемого текста заведомо сложные предложения.

     - Хранение данных: Два файла. Один в памяти -- map<word, block_id>. Второй на диске, состоит из блоков. Блок -- набор предложений.
        class TIndexer
          bool IndexSentence(const string& word, const string& sentence);
          bool LoadFromDisk();
          bool SaveToDisk();

       ** version 2.0 **
        class TLemmer
          void GetLemma(const string& word, string& lemma); // Example: going -> go, chairs -> chair
        
  2. Поиск(С++): Получает слово -- возвращает блок.
        class TSearcher
          bool InitIndex(const string& indexFile);
          void Find(const string& word, vector<string>& sentences) const;
        
     ** version 2.0 **
     Получает набор слов. Тогда надо будет пересекать блоки. Для этого надо хранить каждый блок сортированным.
          void FindPhrase(const string& phrase, vector<string>& sentences) const;
     
  3. Библиотека для ранжирования(С++): Должна уметь вычислять сложность слов и сложность предложений.
      - Заранее обработать корпус текстов для получения частотностей слов. (Python)
      - На основе частотностей слов, написать библиотеку, которая будет вычислять сложность слова и сложность предложения.
        class TRanker
          double GetWordDifficulty(const string& word) const;
          double GetSentenceDifficulty(const string& sentence) const;
            
  4. Веб-сервер, предоставляющий API поиска.

* Front-end(HTML)
  - Для начала будет очень простым -- поисковая строка и результаты.

